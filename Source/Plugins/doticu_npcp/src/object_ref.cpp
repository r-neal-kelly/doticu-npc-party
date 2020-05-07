/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "object_ref.h"

namespace doticu_npcp { namespace Object_Ref {

    TESContainer *Get_Base_Container(TESObjectREFR *ref_object) {
        if (!ref_object || !ref_object->baseForm) {
            return NULL;
        } else {
            return DYNAMIC_CAST(ref_object->baseForm, TESForm, TESContainer);
        }
    }

    ExtraContainerChanges *Get_Ref_Container(TESObjectREFR *ref_object) {
        if (!ref_object) {
            return NULL;
        } else {
            ExtraContainerChanges *container_extra = (ExtraContainerChanges *)ref_object->extraData.GetByType(kExtraData_ContainerChanges);
            if (container_extra && container_extra->data && container_extra->data->objList) {
                return container_extra;
            } else {
                return NULL;
            }
        }
    }

    Items Get_Items(TESObjectREFR *ref_object, bool get_leveled) {
        Items items;

        if (!ref_object) {
            return items;
        }

        TESContainer *container_base = Get_Base_Container(ref_object);
        if (container_base) {
            TESContainer::Entry *entry;
            for (u64 idx = 0; idx < container_base->numEntries; idx += 1) {
                entry = container_base->entries[idx];
                if (entry && entry->form) {
                    if (!get_leveled && entry->form->formType == kFormType_LeveledItem) {
                        continue;
                    }
                    s64 idx_form = Vector::Index_Of(items.forms, entry->form);
                    if (idx_form > -1) {
                        items.counts[idx_form] += entry->count;
                    } else {
                        items.forms.push_back(entry->form);
                        items.counts.push_back(entry->count);
                    }
                }
            }
        }
        
        ExtraContainerChanges *container_extra = Get_Ref_Container(ref_object);
        if (container_extra) {
            InventoryEntryData *entry;
            for (tList<InventoryEntryData>::Iterator it = container_extra->data->objList->Begin(); !it.End(); ++it) {
                entry = it.Get();
                if (entry && entry->type) {
                    if (!get_leveled && entry->type->formType == kFormType_LeveledItem) {
                        continue;
                    }
                    s64 idx_form = Vector::Index_Of(items.forms, entry->type);
                    if (idx_form > -1) {
                        items.counts[idx_form] += entry->countDelta;
                    } else {
                        items.forms.push_back(entry->type);
                        items.counts.push_back(entry->countDelta);
                    }
                }
            }
        }

        Items filtered_items;

        for (u64 idx = 0, size = items.forms.size(); idx < size; idx += 1) {
            if (items.counts[idx] > 0) {
                filtered_items.forms.push_back(items.forms[idx]);
                filtered_items.counts.push_back(items.counts[idx]);
            }
        }

        return filtered_items;
    }

    SInt32 Count_Item(TESObjectREFR *ref_object, TESForm *ref_form) {
        return Count_Base_Item(ref_object, ref_form) + Count_Ref_Item(ref_object, ref_form);
    }

    SInt32 Count_Base_Item(TESObjectREFR *ref_object, TESForm *ref_form) {
        SInt32 count = 0;

        if (!ref_object || !ref_form) {
            return count;
        }

        TESContainer *container_base = Get_Base_Container(ref_object);
        if (container_base) {
            TESContainer::Entry *entry;
            for (u64 idx = 0; idx < container_base->numEntries; idx += 1) {
                entry = container_base->entries[idx];
                if (entry && entry->form ==  ref_form) {
                    count += entry->count;
                }
            }
        }

        return count;
    }

    SInt32 Count_Ref_Item(TESObjectREFR *ref_object, TESForm *ref_form) {
        SInt32 count = 0;

        if (!ref_object || !ref_form) {
            return count;
        }

        ExtraContainerChanges *container_extra = Get_Ref_Container(ref_object);
        if (container_extra) {
            InventoryEntryData *entry;
            for (tList<InventoryEntryData>::Iterator it = container_extra->data->objList->Begin(); !it.End(); ++it) {
                entry = it.Get();
                if (entry && entry->type == ref_form) {
                    count += entry->countDelta;
                }
            }
        }

        return count;
    }

    void Add_Item(TESObjectREFR *ref_object, TESForm *ref_form, SInt32 count) {
        if (!ref_object || !ref_form || count < 1) {
            return;
        }
        if (ref_object == *g_thePlayer) {
            // for right now, we don't work on the player, because I'm not sure about handling totalWeight and armorWeight
            // I know that on NPCs both are set to -1.0
            _MESSAGE("tried to Add_Item to player. not implemented.");
            return;
        }

        ExtraContainerChanges *container_extra = Get_Ref_Container(ref_object);
        if (!container_extra) {
            return;
        }

        // testing has shown that the changes are saved automatically by the engine
        InventoryEntryData *entry = container_extra->data->FindItemEntry(ref_form);
        if (entry) {
            entry->countDelta += count;
        } else {
            entry = InventoryEntryData::Create(ref_form, count);
            container_extra->data->objList->Push(entry);
        }

        if (ref_object == *g_thePlayer) {
            // we need to do weight calc only on the player
            // do both totalWeight and armorWeight
            // see GetTotalItemWeight and GetTotalArmorWeight
        }
    }

    void Remove_Item(TESObjectREFR *ref_object, TESForm *ref_form, SInt32 count) {
        if (!ref_object || !ref_form || count < 1) {
            return;
        }
        if (ref_object == *g_thePlayer) {
            // for right now, we don't work on the player, because I'm not sure about handling totalWeight and armorWeight
            // I know that on NPCs both are set to -1.0
            _MESSAGE("tried to Remove_Item from player. not implemented.");
            return;
        }

        ExtraContainerChanges *container_extra = Get_Ref_Container(ref_object);
        if (!container_extra) {
            return;
        }

        // testing has shown that the changes are saved automatically by the engine
        SInt32 count_base = Count_Base_Item(ref_object, ref_form);
        SInt32 count_reference = Count_Ref_Item(ref_object, ref_form);
        InventoryEntryData *entry = container_extra->data->FindItemEntry(ref_form);
        if (count_base > 0) {
            // we need to make sure that the entry is created, so that we can negate the existing base,
            // but let us not set a count_both that is less than 0 in any case
            if (!entry) {
                if (count > count_base) {
                    count = count_base;
                }
                entry = InventoryEntryData::Create(ref_form, 0 - count);
                container_extra->data->objList->Push(entry);
            } else {
                SInt32 count_both = count_base + count_reference;
                if (count_both >= count) {
                    entry->countDelta -= count;
                } else if (count_both > 0) {
                    entry->countDelta -= count_both;
                }
            }
        } else {
            if (count_reference - count < 1) {
                // we can actually delete here if we achieve zero or less, because there is no base to negate
                class Comparator {
                private:
                    TESForm * p_ref_form;
                public:
                    Comparator(TESForm *ref_form) : p_ref_form(ref_form) { }
                    bool Accept(InventoryEntryData *entry) {
                        if (entry && entry->type == p_ref_form) {
                            entry->Delete();
                            return true; // will remove from list
                        } else {
                            return false; // wont remove from list
                        }
                    }
                } comparator(ref_form);
                container_extra->data->objList->RemoveIf(comparator);
            } else {
                if (entry) {
                    entry->countDelta -= count;
                }
            }
        }

        if (ref_object == *g_thePlayer) {
            // we need to do weight calc only on the player
            // do both totalWeight and armorWeight
            // see GetTotalItemWeight and GetTotalArmorWeight
        }
    }

    void Remove_All_Items(TESObjectREFR *ref_object) {
        if (!ref_object) {
            return;
        }

        ExtraContainerChanges *container_extra = Get_Ref_Container(ref_object);
        if (container_extra) {
            class Comparator {
            public:
                bool Accept(InventoryEntryData *entry) {
                    if (entry) {
                        entry->Delete();
                    }
                    return true; // will remove from list
                }
            } comparator;
            container_extra->data->objList->RemoveIf(comparator);
        }

        TESContainer *container_base = Get_Base_Container(ref_object);
        if (container_base) {
            TESContainer::Entry *entry;
            for (u64 idx = 0; idx < container_base->numEntries; idx += 1) {
                entry = container_base->entries[idx];
                if (entry && entry->form && entry->count > 0) {
                    container_extra->data->objList->Push(InventoryEntryData::Create(entry->form, 0 - entry->count));
                }
            }
        }
    }

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    void Log_Items(StaticFunctionTag *, TESObjectREFR *ref_object) {
        Items items = Get_Items(ref_object);
        _MESSAGE("");
        for (u64 idx = 0, size = items.forms.size(); idx < size; idx += 1) {
            TESForm *ref_form = items.forms[idx];
            _MESSAGE("%s, count: %d, type: %d", Form::Get_Name(ref_form), items.counts[idx], ref_form->formType);
        }
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, TESObjectREFR *>(
                "Object_Ref_Log_Items",
                "doticu_npcp",
                Log_Items,
                registry)
        );

        return true;
    }

}}}
