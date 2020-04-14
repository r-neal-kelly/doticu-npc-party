/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

//#include <algorithm>
#include <cstring>
#include "skse64/GameExtraData.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"
#include "doticu_npcp.h"

namespace doticu_npcp {

    void Outfit_Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
        // changes are NOT lost on load game, but they are lost after changing outfits.
        if (!outfit || !form_item) {
            _MESSAGE("    Outfit_Add_Item: missing param");
            return;
        }

        tArray<TESForm *> *arr_items = &outfit->armorOrLeveledItemArray;
        if (!arr_items) {
            _MESSAGE("    Outfit_Add_Item: outfit is missing armorOrLeveledItemArray");
            return;
        }

        SInt64 idx_item = arr_items->GetItemIndex(form_item);
        if (idx_item < 0) {
            arr_items->Push(form_item);
        }
    }

    void Outfit_Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
        // changes are NOT lost on load game, but they are lost after changing outfits.
        if (!outfit || !form_item) {
            return;
        }

        tArray<TESForm *> *arr_items = &outfit->armorOrLeveledItemArray;
        if (!arr_items) {
            return;
        }

        SInt64 idx_item = arr_items->GetItemIndex(form_item);
        if (idx_item > -1) {
            // as long as it's greater than -1, it should be fine to cast to unsigned
            arr_items->Remove((UInt64)idx_item);
        }
    }

    void Actor_Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit) {
        if (!ref_actor || !outfit) {
            return;
        }

        // this is the leveled/real base which carries the outfits.
        // Thank you to Ian Patterson of SKSE for how to save the outfit!
        // Also, we're doing a dynamic cast, rather than static for TESNPC, because the library does
        TESNPC *base_actor = DYNAMIC_CAST(ref_actor->baseForm, TESForm, TESNPC);
        if (is_sleep_outfit) {
            base_actor->sleepOutfit = outfit;
            base_actor->MarkChanged(0x2000);
        } else {
            base_actor->defaultOutfit = outfit;
            base_actor->MarkChanged(0x1000);
        }

        // passing true keeps items that were previously in inventory.
        // using this does indeed avoid the horrible outfit bug.
        ref_actor->ResetInventory(true);

        tArray<TESForm *> *arr_outfit_items = &outfit->armorOrLeveledItemArray;
        if (!arr_outfit_items) {
            return;
        }

        // we make sure everything in outfit is equipped, because the actor may have better equipment
        UInt64 idx = 0;
        TESForm *form_outfit_item;
        while (idx < arr_outfit_items->count) {
            arr_outfit_items->GetNthItem(idx, form_outfit_item);
            if (form_outfit_item) {
                papyrusActor::EquipItemEx(ref_actor, form_outfit_item, 0, false, false);
            }
            idx += 1;
        }

        // it would be nice to unequip everything that doesn't belong in outfit as well.
        // but that requires looping over actor inventory, out of my knowledge right noe

        return;



        // I'm really surprised how complicated the inventory system is. I'm leaving this here to learn more later.
        // extraData appears to be a list of of BSExtraData, which is a base-class of ExtraContainerChanges.
        // if I understand correctly, this object is used to add stuff in addition to the base container of ref.
        // GetByType finds the BSExtraData in the list that we are looking for in particular.
        ExtraContainerChanges *container_changes = (ExtraContainerChanges *)(ref_actor->extraData.GetByType(kExtraData_ContainerChanges));
        if (!container_changes) {
            return;
        }

        // this is a list of all the different items that are in the extra container, as far as I understand
        tList<InventoryEntryData> *list_entries = container_changes->data->objList;
        if (!list_entries) {
            return;
        }

        // it's interesting that the print out shows some of the forms multiple times.
        // I understand there is some kind of split between items in the inventory, but
        // it is not at all clear to me how that works.
        tList<InventoryEntryData>::Iterator it = list_entries->Begin();
        while (!it.End()) {
            InventoryEntryData *entry = it.Get();
            TESForm *form = entry->type;
            TESFullName *full_name = DYNAMIC_CAST(form, TESForm, TESFullName);

            _MESSAGE("    %s, is_playable: %d", full_name->name.data, form->IsPlayable());

            ++it;
        }

        //InventoryEntryData *entry_data = container_changes->data->FindItemEntry();

        return;
    }

    class Object_Handle {
    public:
        Object_Handle() {};
        Object_Handle(VMClassRegistry *ptr_registry, IObjectHandlePolicy *ptr_policy, UInt32 type, void *data) {
            p_ptr_registry = ptr_registry;
            p_ptr_policy = ptr_policy;
            p_type = type;
            p_hnd = p_ptr_policy->Create(p_type, data);
        }
        ~Object_Handle() {
            if (Is_Valid()) {
                p_ptr_policy->Release(p_hnd);
            }
        }
        UInt64 Val() {
            return p_hnd;
        }
        VMClassRegistry *Registry() {
            return p_ptr_registry;
        }
        IObjectHandlePolicy *Policy() {
            return p_ptr_policy;
        }
        bool Is_Valid() {
            return p_hnd != p_ptr_policy->GetInvalidHandle();
        }
    private:
        VMClassRegistry *p_ptr_registry;
        IObjectHandlePolicy *p_ptr_policy;
        UInt32 p_type;
        UInt64 p_hnd;
    };

    Actor *Get_Alias_Actor(Object_Handle *hnd_object) {
        class Functor_Get_Variable : public IForEachScriptObjectFunctor {
        public:
            Functor_Get_Variable(Object_Handle *hnd_object, BSFixedString *str_variable) {
                p_hnd_object = hnd_object;
                p_str_variable = str_variable;
            }
            ~Functor_Get_Variable() {}
            virtual bool Visit(VMScriptInstance *ptr_script, void *) {
                SInt32 idx_variable = CALL_MEMBER_FN(ptr_script->classInfo, GetVariable)(p_str_variable);
                if (idx_variable > -1) {
                    p_hnd_object->Registry()->ExtractValue(p_hnd_object->Val(), &ptr_script->classInfo->name, idx_variable, &p_vm_variable);
                    return false; // stop iterating
                } else {
                    return true; // keep iterating
                }
            }
            VMValue *Val() {
                return &p_vm_variable;
            }
        private:
            Object_Handle * p_hnd_object;
            BSFixedString *p_str_variable;
            VMValue p_vm_variable;
        };

        BSFixedString str_variable("p_ref_actor");
        Functor_Get_Variable functor(hnd_object, &str_variable);
        hnd_object->Registry()->VisitScripts(hnd_object->Val(), &functor);

        VMValue *vm_actor = functor.Val();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Identifier) {
            return (Actor *)hnd_object->Policy()->Resolve(kFormType_Character, vm_actor->data.id->GetHandle());
        } else {
            return NULL;
        }
    }

    int Compare_Aliases(const void *ptr_alias_a, const void *ptr_alias_b) {
        VMClassRegistry *ptr_registry = (*g_skyrimVM)->GetClassRegistry();
        IObjectHandlePolicy *ptr_policy = ptr_registry->GetHandlePolicy();

        Object_Handle hnd_alias_a(ptr_registry, ptr_policy, kFormType_Alias, *(BGSBaseAlias **)ptr_alias_a);
        Object_Handle hnd_alias_b(ptr_registry, ptr_policy, kFormType_Alias, *(BGSBaseAlias **)ptr_alias_b);

        Actor *ptr_actor_a = Get_Alias_Actor(&hnd_alias_a);
        Actor *ptr_actor_b = Get_Alias_Actor(&hnd_alias_b);

        BSFixedString str_actor_a = CALL_MEMBER_FN(ptr_actor_a, GetReferenceName)();
        BSFixedString str_actor_b = CALL_MEMBER_FN(ptr_actor_b, GetReferenceName)();

        return strcmp(str_actor_a.data, str_actor_b.data);
    }

    VMResultArray<BGSBaseAlias *> Sort_Aliases(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases) {
        UInt32 idx_aliases = 0;
        UInt32 num_aliases = arr_aliases.Length();
        VMResultArray<BGSBaseAlias *> arr_return;
        arr_return.reserve(num_aliases);
        BGSBaseAlias *ptr_alias;
        while (idx_aliases < num_aliases) {
            arr_aliases.Get(&ptr_alias, idx_aliases);
            arr_return.push_back(ptr_alias);
            idx_aliases += 1;
        }
        qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Aliases);

        return arr_return;
    }

    bool Register_Functions(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>("Outfit_Add_Item",
                                                                                  "doticu_npcp",
                                                                                  doticu_npcp::Outfit_Add_Item,
                                                                                  registry));
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>("Outfit_Remove_Item",
                                                                                  "doticu_npcp",
                                                                                  doticu_npcp::Outfit_Remove_Item,
                                                                                  registry));
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>("SetOutfit",
                                                                 "Actor",
                                                                 doticu_npcp::Actor_Set_Outfit,
                                                                 registry));
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>>("Sort_Aliases",
                                                                                                            "doticu_npcp",
                                                                                                            doticu_npcp::Sort_Aliases,
                                                                                                            registry));

        return true;
    }

}
