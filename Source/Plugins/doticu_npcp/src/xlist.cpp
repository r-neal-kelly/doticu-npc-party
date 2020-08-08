/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "form.h"
#include "object_ref.h"
#include "utils.h"
#include "xdata.h"
#include "xlist.h"

namespace doticu_npcp { namespace XList {

    XList_t *Create() {
        XList_t *xlist = (XList_t *)Heap_Allocate(sizeof(XList_t));
        NPCP_ASSERT(xlist);

        xlist->m_data = NULL;

        xlist->m_presence = (XList_t::PresenceBitfield *)Heap_Allocate(sizeof(XList_t::PresenceBitfield));
        NPCP_ASSERT(xlist->m_presence);

        u64 *bits = (u64 *)xlist->m_presence->bits;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;

        xlist->m_lock = BSReadWriteLock();

        return xlist;
    }

    void Validate(XList_t* xlist)
    {
        NPCP_ASSERT(xlist);

        if (!xlist->m_presence) {
            xlist->m_presence = (XList_t::PresenceBitfield*)Heap_Allocate(sizeof(XList_t::PresenceBitfield));
            NPCP_ASSERT(xlist->m_presence);

            u64* bits = (u64*)xlist->m_presence->bits;
            bits[0] = 0;
            bits[1] = 0;
            bits[2] = 0;

            xlist->m_lock = BSReadWriteLock();
        }
    }

    void Destroy(XList_t *xlist) {
        if (!xlist) {
            return;
        }

        //BSReadAndWriteLocker locker(&xlist->m_lock);

        for (XData_t *xdata = xlist->m_data, *xdata_destroy; xdata != NULL;) {
            xdata_destroy = xdata;
            xdata = xdata->next;
            XData::Destroy(xdata_destroy);
        }

        Heap_Free(xlist->m_presence);
        Heap_Free(xlist);
    }

    // this does copy count
    XList_t *Copy(XList_t *xlist) {
        if (!xlist) {
            _ERROR("XList_t::Copy: Invalids args.");
            return NULL;
        }
        if (Get_Count(xlist) < 1) {
            return NULL;
        }
        if (!Can_Copy(xlist)) {
            return NULL;
        }

        XList_t *xlist_new = Create();

        for (XData_t *xdata = xlist->m_data; xdata != NULL; xdata = xdata->next) {
            if (xdata->GetType() == kExtraData_Health) {
                xlist_new->Add(kExtraData_Health, XData::Copy_Health((ExtraHealth *)xdata, &xlist->m_lock));
            } else if (xdata->GetType() == kExtraData_Enchantment) {
                xlist_new->Add(kExtraData_Enchantment, XData::Copy_Enchantment((ExtraEnchantment *)xdata, &xlist->m_lock));
            } else if (xdata->GetType() == kExtraData_Charge) {
                xlist_new->Add(kExtraData_Charge, XData::Copy_Charge((ExtraCharge *)xdata, &xlist->m_lock));
            } else if (xdata->GetType() == kExtraData_Count) {
                xlist_new->Add(kExtraData_Count, XData::Copy_Count((ExtraCount *)xdata, &xlist->m_lock));
            }
        }

        return xlist_new;
    }

    // certain xdata cannot be moved to another container without creating issues, e.g. worn, leveleditem. Others are just unneeded.
    u64 Clean_For_Move(XList_t *xlist, TESObjectREFR *ref_to) {
        if (!xlist || !Object_Ref::Get_XContainer(ref_to, false)) {
            return 0;
        }
        
        s64 count_xdatas = 0;
        std::vector<XData_t *> vec_xdatas_to_destroy;
        for (XData_t *xdata = xlist->m_data; xdata != NULL; xdata = xdata->next) {
            u64 type = xdata->GetType();

            if (type == kExtraData_ReferenceHandle) {
                ExtraReferenceHandle *xref = (ExtraReferenceHandle *)xdata;
                //BSReadLocker xlist_locker(&xlist->m_lock);
                TESObjectREFR *obj = xref->GetReference();
                //xlist_locker.~BSReadLocker();
                if (!obj) {
                    vec_xdatas_to_destroy.push_back(xdata);
                } else {
                    // CreateRefHandle seems to return an already in use handle if it can, so there is no need to release.
                    // we do not need to IncRef on new container and DecRef on old, that's apparently not how it works.
                    ExtraReferenceHandle *xref_obj = (ExtraReferenceHandle *)obj->extraData.GetByType(kExtraData_ReferenceHandle);
                    if (xref_obj) {
                        //BSReadAndWriteLocker xlist_obj_locker(&obj->extraData.m_lock);
                        xref_obj->handle = ref_to->CreateRefHandle();
                    } else {
                        obj->extraData.Add(kExtraData_ReferenceHandle, XData::Create_Reference_Handle(ref_to));
                    }
                }
            } else if (type == kExtraData_Ownership) {
                ExtraOwnership *xownership = (ExtraOwnership *)xdata;
                //BSReadLocker xlist_locker(&xlist->m_lock);
                if (!xownership->owner) {
                    vec_xdatas_to_destroy.push_back(xdata);
                }
            } else if (type == kExtraData_Worn ||
                       type == kExtraData_WornLeft ||
                       type == kExtraData_OutfitItem ||
                       type == kExtraData_LeveledItem ||
                       type == kExtraData_CannotWear ||
                       type == kExtraData_ShouldWear) {
                // kExtraData_LeveledItemBase?
                vec_xdatas_to_destroy.push_back(xdata);
            }

            count_xdatas += 1;
        }

        for (u64 idx = 0, size = vec_xdatas_to_destroy.size(); idx < size; idx += 1) {
            XData_t *xdata = vec_xdatas_to_destroy[idx];
            xlist->Remove(xdata->GetType(), xdata);
            XData::Destroy(xdata);
        }

        return count_xdatas - vec_xdatas_to_destroy.size();
    }

    UInt32 Get_Count(XList_t *xlist) {
        if (!xlist) {
            return 0;
        }

        ExtraCount *xcount = (ExtraCount *)xlist->GetByType(kExtraData_Count);
        if (xcount) {
            //BSReadLocker locker(&xlist->m_lock);
            return xcount->count;
        } else {
            // it's always assumed to be one if there is no count.
            return 1;
        }
    }

    void Set_Count(XList_t *xlist, UInt32 count) {
        if (!xlist || count < 1) {
            // if the count < 1, then the xlist should be deleted.
            _ERROR("XList_t::Set_Count: Invalids args.");
            return;
        }

        ExtraCount *xcount = (ExtraCount *)xlist->GetByType(kExtraData_Count);
        if (xcount) {
            //BSReadAndWriteLocker(&xlist->m_lock);
            xcount->count = count;
        } else {
            // it's always assumed to be one if there is no count.
            if (count > 1) {
                xlist->Add(kExtraData_Count, XData::Create_Count(count));
            }
        }
    }

    void Inc_Count(XList_t *xlist, UInt32 inc) {
        if (!xlist || inc < 1) {
            return;
        }

        ExtraCount *xcount = (ExtraCount *)xlist->GetByType(kExtraData_Count);
        if (xcount) {
            //BSReadAndWriteLocker(&xlist->m_lock);
            xcount->count += inc;
        } else {
            // it's always assumed to be one if there is no count.
            xlist->Add(kExtraData_Count, XData::Create_Count(inc + 1));
        }
    }

    bool Is_Similar(XList_t *xlist_a, XList_t *xlist_b) {
        if (!xlist_a || !xlist_b) {
            return false;
        }

        if (!XData::Is_Same_Health(
            (ExtraHealth *)xlist_a->GetByType(kExtraData_Health),
            (ExtraHealth *)xlist_b->GetByType(kExtraData_Health),
            &xlist_a->m_lock,
            &xlist_b->m_lock)) {
            return false;
        }
        if (!XData::Is_Same_Enchantment(
            (ExtraEnchantment *)xlist_a->GetByType(kExtraData_Enchantment),
            (ExtraEnchantment *)xlist_b->GetByType(kExtraData_Enchantment),
            &xlist_a->m_lock,
            &xlist_b->m_lock)) {
            return false;
        }
        if (!XData::Is_Same_Charge(
            (ExtraCharge *)xlist_a->GetByType(kExtraData_Charge),
            (ExtraCharge *)xlist_b->GetByType(kExtraData_Charge),
            &xlist_a->m_lock,
            &xlist_b->m_lock)) {
            return false;
        }

        return true;
    }

    bool Can_Copy(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_Health) || xlist->HasType(kExtraData_Enchantment) || xlist->HasType(kExtraData_Charge);
    }

    bool Is_Worn(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_Worn) || xlist->HasType(kExtraData_WornLeft);
    }

    bool Is_Outfit_Item(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_OutfitItem);
    }

    bool Is_Leveled_Item(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_LeveledItem);
    }

    bool Is_Quest_Item(XList_t *xlist) {
        if (!xlist || !xlist->HasType(kExtraData_ReferenceHandle)) {
            return false;
        }

        ExtraReferenceHandle *xref = (ExtraReferenceHandle *)xlist->GetByType(kExtraData_ReferenceHandle);
        if (!xref) {
            return false;
        }

        //BSReadLocker locker(&xlist->m_lock);
        TESObjectREFR *ref = xref->GetReference();
        if (!ref) {
            return false;
        }

        return Object_Ref::Is_Quest_Item(ref);
    }

    // the idea here is to have a way to recognize items that are part of a doticu_npcp_outfit.
    // every item that is come from the outfit2 will be an xlist with an ownership to the player
    // unless we figure out something better. I don't know how to accurately test setting owner
    // to a base form like blank armor, it could crash the game otherwise I'd do it.
    void Add_Outfit2_Flag(XList_t *xlist) {
        if (!xlist) {
            _ERROR("XList_t::Add_Outfit2_Flag: Invalids args.");
            return;
        }
        
        ExtraOwnership *xownership = (ExtraOwnership *)xlist->GetByType(kExtraData_Ownership);
        if (xownership) {
            //BSReadAndWriteLocker locker(&xlist->m_lock);
            xownership->owner = (*g_thePlayer)->baseForm;
        } else {
            xlist->Add(kExtraData_Ownership, XData::Create_Ownership((*g_thePlayer)->baseForm));
        }
    }
    bool Has_Outfit2_Flag(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        ExtraOwnership *xownership = (ExtraOwnership *)xlist->GetByType(kExtraData_Ownership);
        if (xownership) {
            //BSReadLocker locker(&xlist->m_lock);
            return xownership->owner == (*g_thePlayer)->baseForm;
        } else {
            return false;
        }
    }

    void Log(XList_t *xlist, const std::string str_indent) {
        if (!xlist) {
            return;
        }

        u64 idx_xdata = 0;
        for (XData_t *xdata = xlist->m_data; xdata != NULL; xdata = xdata->next, idx_xdata += 1) {
            if (xdata->GetType() == kExtraData_Count) {
                _MESSAGE("%sxdata idx: %i, type: %s, count: %i",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         ((ExtraCount *)xdata)->count);
            } else if (xdata->GetType() == kExtraData_Ownership) {
                _MESSAGE("%sxdata idx: %i, type: %s, owner: %s",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         Form::Get_Name(((ExtraOwnership *)xdata)->owner));
            } else if (xdata->GetType() == kExtraData_ReferenceHandle) {
                TESObjectREFR* object = ((ExtraReferenceHandle*)xdata)->GetReference();
                if (object) {
                    _MESSAGE("%sxdata idx: %i, type: %s, name: %s, quest-item: %s, off-limits: %s",
                             str_indent.c_str(),
                             idx_xdata,
                             XData::Get_Type_String(xdata),
                             Object_Ref::Get_Name(object),
                             Object_Ref::Is_Quest_Item(object) ? "t" : "f",
                             Object_Ref::Is_Off_Limits(object) ? "t" : "f");
                    XList::Log(&object->extraData, std::string(str_indent).append("    "));
                } else {
                    _MESSAGE("%sxdata idx: %i, type: %s, (null)",
                             str_indent.c_str(),
                             idx_xdata,
                             XData::Get_Type_String(xdata));
                }
            } else if (xdata->GetType() == kExtraData_AliasInstanceArray) {
                ExtraAliasInstanceArray* xaliases = reinterpret_cast<ExtraAliasInstanceArray*>(xdata);
                _MESSAGE("%sxdata idx: %i, type: %s, quest_count: %u",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         xaliases->aliases.count);
            } else if (xdata->GetType() == kExtraData_Interaction) {
                XData::XInteraction* xinteraction = reinterpret_cast<XData::XInteraction*>(xdata);
                if (xinteraction->interaction) {
                    NiPointer<TESObjectREFR> interactee = nullptr;
                    NiPointer<TESObjectREFR> interactor = nullptr;
                    LookupREFRByHandle(xinteraction->interaction->interactee_handle, interactee);
                    LookupREFRByHandle(xinteraction->interaction->interactor_handle, interactor);
                    _MESSAGE("%sxdata idx: %i, type: %s, interacted: %p, interactor: %p, is_synced: %u, interaction %p",
                             str_indent.c_str(),
                             idx_xdata,
                             XData::Get_Type_String(xdata),
                             interactee,
                             interactor,
                             xinteraction->interaction->is_synced,
                             xinteraction->interaction);
                    uintptr_t _vtbl_addr = *(uintptr_t*)xinteraction->interaction;
                    uintptr_t _vtbl_offset = _vtbl_addr - RelocationManager::s_baseAddr;
                    _MESSAGE("            _vtbl: %p, offset: %p, ref_count: %u",
                             _vtbl_addr,
                             _vtbl_offset,
                             xinteraction->interaction->GetRefCount());
                } else {
                    _MESSAGE("%sxdata idx: %i, type: %s, (invalid)",
                             str_indent.c_str(),
                             idx_xdata,
                             XData::Get_Type_String(xdata));
                }
            } else {
                _MESSAGE("%sxdata idx: %i, type: %s",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata));
            }
        }
    }

}}
