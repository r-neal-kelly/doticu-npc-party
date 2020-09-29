/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#undef max
#include <numeric>

#include "skse64/PapyrusWornObject.h"

#include "consts.h"
#include "form.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "string2.h"
#include "utils.h"
#include "xdata.h"
#include "xlist.h"

namespace doticu_npcp { namespace Papyrus {

    Int_t XList_t2::operator++()
    {

    }

    Int_t XList_t2::operator++(int)
    {

    }

}}

namespace doticu_npcp { namespace XList {

    XList_t* Create()
    {
        XList_t* xlist = (XList_t*)Heap_Allocate(sizeof(XList_t));
        NPCP_ASSERT(xlist);

        xlist->m_data = NULL;

        xlist->m_presence = (XList_t::PresenceBitfield*)Heap_Allocate(sizeof(XList_t::PresenceBitfield));
        NPCP_ASSERT(xlist->m_presence);

        u64* bits = (u64*)xlist->m_presence->bits;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;

        xlist->m_lock = BSReadWriteLock();

        return xlist;
    }

    void Destroy(XList_t* xlist)
    {
        if (xlist) {
            for (XData_t* xdata = xlist->m_data, *xdata_to_destroy; xdata != nullptr;) {
                xdata_to_destroy = xdata;
                xdata = xdata->next;
                if (xdata_to_destroy->GetType() == kExtraData_Ownership) {
                    static_cast<ExtraOwnership*>(xdata_to_destroy)->owner = nullptr;
                }
                XData::Destroy(xdata_to_destroy);
            }
            Heap_Free(xlist->m_presence);
            Heap_Free(xlist);
        }
    }

    void Validate(XList_t* xlist, Int_t xentry_count, Int_t bentry_count)
    {
        if (xlist) {
            if (!xlist->m_presence) {
                xlist->m_presence = (XList_t::PresenceBitfield*)Heap_Allocate(sizeof(XList_t::PresenceBitfield));
                NPCP_ASSERT(xlist->m_presence);

                xlist->m_lock = BSReadWriteLock();
            }

            u64* bits = (u64*)xlist->m_presence->bits;
            bits[0] = 0;
            bits[1] = 0;
            bits[2] = 0;

            for (XData_t* xdata = xlist->m_data; xdata != nullptr; xdata = xdata->next) {
                xlist->MarkType(xdata->GetType(), false);
            }

            XCount_t* xcount = static_cast<XCount_t*>(xlist->GetByType(kExtraData_Count));
            if (xcount) {
                if (bentry_count < 0) {
                    bentry_count = 0;
                }
                if (xentry_count < 0 - bentry_count + 1) {
                    xentry_count = 0 - bentry_count + 1;
                }
                if (static_cast<Int_t>(xcount->count) > xentry_count + bentry_count ||
                    static_cast<Int_t>(xcount->count) < 0) {
                    xcount->count = 1;
                }
            }
        }
    }

    void Validate_No_Count(XList_t* xlist)
    {
        if (xlist) {
            if (!xlist->m_presence) {
                xlist->m_presence = (XList_t::PresenceBitfield*)Heap_Allocate(sizeof(XList_t::PresenceBitfield));
                NPCP_ASSERT(xlist->m_presence);

                xlist->m_lock = BSReadWriteLock();
            }

            u64* bits = (u64*)xlist->m_presence->bits;
            bits[0] = 0;
            bits[1] = 0;
            bits[2] = 0;

            for (XData_t* xdata = xlist->m_data; xdata != nullptr; xdata = xdata->next) {
                xlist->MarkType(xdata->GetType(), false);
            }
        }
    }

    Int_t Count(XList_t* xlist)
    {
        if (xlist) {
            XCount_t* xcount = static_cast<XCount_t*>(xlist->GetByType(kExtraData_Count));
            if (xcount) {
                return xcount->count;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }

    void Count(XList_t* xlist, Int_t count)
    {
        if (xlist && count > 0) {
            XCount_t* xcount = static_cast<XCount_t*>(xlist->GetByType(kExtraData_Count));
            if (xcount) {
                xcount->count = count;
                if (static_cast<Int_t>(xcount->count) < 0) {
                    xcount->count = std::numeric_limits<Int_t>::max();
                }
            } else if (count > 1) {
                xcount = XCount_t::Create(count);
                xlist->Add(kExtraData_Count, xcount);
                if (static_cast<Int_t>(xcount->count) < 0) {
                    xcount->count = std::numeric_limits<Int_t>::max();
                }
            }
        }
    }

    void Increment(XList_t* xlist, Int_t increment)
    {
        if (xlist && increment > 0) {
            XCount_t* xcount = static_cast<XCount_t*>(xlist->GetByType(kExtraData_Count));
            if (xcount) {
                xcount->count += increment;
                if (static_cast<Int_t>(xcount->count) < 0) {
                    xcount->count = std::numeric_limits<Int_t>::max();
                }
            } else {
                xcount = XCount_t::Create(1 + increment);
                xlist->Add(kExtraData_Count, xcount);
                if (static_cast<Int_t>(xcount->count) < 0) {
                    xcount->count = std::numeric_limits<Int_t>::max();
                }
            }
        }
    }

    Int_t Decrement(XList_t* xlist, Int_t decrement)
    {
        Int_t amount_decreased = 0;

        if (xlist && decrement > 0) {
            XCount_t* xcount = static_cast<XCount_t*>(xlist->GetByType(kExtraData_Count));
            if (xcount) {
                if (xcount->count > decrement) {
                    amount_decreased = decrement;
                    xcount->count -= decrement;
                } else {
                    amount_decreased = xcount->count - 1;
                    if (amount_decreased < 0) {
                        amount_decreased = 0;
                    }
                    xcount->count = 1;
                }
            }
        }

        return amount_decreased;
    }

    XList_t *Copy(XList_t *xlist) {
        if (xlist && Can_Copy(xlist)) {
            XList_t* xlist_new = Create();
            for (XData_t* xdata = xlist->m_data; xdata != NULL; xdata = xdata->next) {
                if (xdata->GetType() == kExtraData_Health) {
                    xlist_new->Add(kExtraData_Health, XData::Copy_Health((ExtraHealth*)xdata));
                } else if (xdata->GetType() == kExtraData_Enchantment) {
                    xlist_new->Add(kExtraData_Enchantment, XData::Copy_Enchantment((ExtraEnchantment*)xdata));
                } else if (xdata->GetType() == kExtraData_Charge) {
                    xlist_new->Add(kExtraData_Charge, XData::Copy_Charge((ExtraCharge*)xdata));
                } else if (xdata->GetType() == kExtraData_Ownership) {
                    xlist_new->Add(kExtraData_Ownership, XData::Copy_Ownership((ExtraOwnership*)xdata));
                } else if (xdata->GetType() == kExtraData_Count) {
                    xlist_new->Add(kExtraData_Count, XData::Copy_Count((ExtraCount*)xdata));
                }
            }
            return xlist_new;
        } else {
            return nullptr;
        }
    }

    void Owner(XList_t* xlist, Actor_Base_t* actor_base)
    {
        if (xlist) {
            ExtraOwnership* ownership = static_cast<ExtraOwnership*>
                (xlist->GetByType(kExtraData_Ownership));
            if (ownership) {
                if (actor_base) {
                    ownership->owner = actor_base;
                } else {
                    xlist->Remove(kExtraData_Ownership, ownership);
                }
            } else {
                if (actor_base) {
                    ownership = XData::Create_Ownership(actor_base);
                    xlist->Add(kExtraData_Ownership, ownership);
                }
            }
        }
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
                TESObjectREFR *obj = xref->GetReference();
                if (!obj) {
                    vec_xdatas_to_destroy.push_back(xdata);
                } else {
                    // CreateRefHandle seems to return an already in use handle if it can, so there is no need to release.
                    // we do not need to IncRef on new container and DecRef on old, that's apparently not how it works.
                    ExtraReferenceHandle *xref_obj = (ExtraReferenceHandle *)obj->extraData.GetByType(kExtraData_ReferenceHandle);
                    if (xref_obj) {
                        xref_obj->handle = ref_to->CreateRefHandle();
                    } else {
                        obj->extraData.Add(kExtraData_ReferenceHandle, XData::Create_Reference_Handle(ref_to));
                    }
                }
            } else if (type == kExtraData_Ownership) {
                ExtraOwnership *xownership = (ExtraOwnership *)xdata;
                if (!xownership->owner) {
                    vec_xdatas_to_destroy.push_back(xdata);
                }
            } else if (type == kExtraData_Worn ||
                       type == kExtraData_WornLeft ||
                       type == kExtraData_OutfitItem ||
                       type == kExtraData_LeveledItem ||
                       type == kExtraData_CannotWear ||
                       type == kExtraData_ShouldWear) {
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

    bool Is_Similar(XList_t* xlist_a, XList_t* xlist_b)
    {
        if (xlist_a && xlist_b) {
            return
                XData::Has_Same_Health(
                    static_cast<ExtraHealth*>(xlist_a->GetByType(kExtraData_Health)),
                    static_cast<ExtraHealth*>(xlist_b->GetByType(kExtraData_Health))
                ) &&
                XData::Has_Same_Enchantment(
                    static_cast<ExtraEnchantment*>(xlist_a->GetByType(kExtraData_Enchantment)),
                    static_cast<ExtraEnchantment*>(xlist_b->GetByType(kExtraData_Enchantment))
                ) &&
                XData::Has_Same_Charge(
                    static_cast<ExtraCharge*>(xlist_a->GetByType(kExtraData_Charge)),
                    static_cast<ExtraCharge*>(xlist_b->GetByType(kExtraData_Charge))
                );
        } else {
            return false;
        }
    }

    bool Can_Copy(XList_t *xlist) {
        if (xlist) {
            return
                xlist->HasType(kExtraData_Health) ||
                xlist->HasType(kExtraData_Enchantment) ||
                xlist->HasType(kExtraData_Charge) ||
                xlist->HasType(kExtraData_Ownership);
        } else {
            return false;
        }
    }

    Bool_t Has_Health(XList_t* xlist)
    {
        return xlist->HasType(kExtraData_Health);
    }

    Bool_t Has_Enchantement(XList_t* xlist)
    {
        return xlist->HasType(kExtraData_Enchantment);
    }

    Bool_t Has_Charge(XList_t* xlist)
    {
        return xlist->HasType(kExtraData_Charge);
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

    Bool_t Is_Outfit2_Item(XList_t* xlist, Form_t* owner)
    {
        if (xlist && owner) {
            ExtraOwnership* xownership = static_cast<ExtraOwnership*>
                (xlist->GetByType(kExtraData_Ownership));
            if (xownership && xownership->owner == owner) {
                for (XData_t* xdata = xlist->m_data; xdata != nullptr; xdata = xdata->next) {
                    UInt32 type = xdata->GetType();
                    if (type != kExtraData_Health &&
                        type != kExtraData_Enchantment &&
                        type != kExtraData_Charge &&
                        type != kExtraData_Count &&
                        type != kExtraData_Worn &&
                        type != kExtraData_WornLeft &&
                        type != kExtraData_Ownership) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
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

        TESObjectREFR *ref = xref->GetReference();
        if (!ref) {
            return false;
        }

        return Object_Ref::Is_Quest_Item(ref);
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
                         ((ExtraCount *)xdata)->Count());
            } else if (xdata->GetType() == kExtraData_Ownership) {
                _MESSAGE("%sxdata idx: %i, type: %s, owner: %s",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         Form::Get_Name(((ExtraOwnership*)xdata)->owner));
            } else if (xdata->GetType() == kExtraData_Soul) {
                _MESSAGE("%sxdata idx: %i, type: %s, level: %s",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         static_cast<Extra_Soul_t*>(xdata)->Soul_Level_String());
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
