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
        private:
            VMClassRegistry * p_ptr_registry;
            IObjectHandlePolicy *p_ptr_policy;
            UInt32 p_type;
            UInt64 p_hnd;

        public:
            // ctors, dtors
            Object_Handle(VMClassRegistry *ptr_registry, IObjectHandlePolicy *ptr_policy, UInt32 type, void *data) {
                p_ptr_registry = ptr_registry;
                p_ptr_policy = ptr_policy;
                p_type = type;
                p_hnd = p_ptr_policy->Create(p_type, data);
            }
            Object_Handle(UInt32 type, void *data) {
                p_ptr_registry = (*g_skyrimVM)->GetClassRegistry();
                p_ptr_policy = p_ptr_registry->GetHandlePolicy();
                p_type = type;
                p_hnd = p_ptr_policy->Create(p_type, data);
            }
            Object_Handle() {
                p_ptr_registry = (*g_skyrimVM)->GetClassRegistry();
                p_ptr_policy = p_ptr_registry->GetHandlePolicy();
                p_type = 0;
                p_hnd = p_ptr_policy->GetInvalidHandle();
            }
            ~Object_Handle() {
                if (Is_Valid()) {
                    p_ptr_policy->Release(p_hnd);
                }
            }

            // Getters
            UInt64 Val() {
                return p_hnd;
            }
            VMClassRegistry *Registry() {
                return p_ptr_registry;
            }
            IObjectHandlePolicy *Policy() {
                return p_ptr_policy;
            }

            // Booleans
            bool Is_Valid() {
                return p_hnd != p_ptr_policy->GetInvalidHandle();
            }

            // Overloads
            operator UInt64() const {
                return p_hnd;
            }
    };

    class Functor_Get_Object_Value : public IForEachScriptObjectFunctor {
        private:
            Object_Handle * p_hnd_object;
            BSFixedString *p_str_variable;
            VMValue p_vm_variable;

        public:
            // ctors, dtors
            Functor_Get_Object_Value(Object_Handle *hnd_object, BSFixedString *str_variable) {
                p_hnd_object = hnd_object;
                p_str_variable = str_variable;
            }
            ~Functor_Get_Object_Value() {
            }

            // Callback
            virtual bool Visit(VMScriptInstance *ptr_script, void *) {
                // as far as I have tested, the iterator does not actually work. it will only ever get the first script it sees
                // on an object, which can be different every time a game is loaded. so this will only work consistently with
                // objects that have just one script on them.
                SInt32 idx_variable = CALL_MEMBER_FN(ptr_script->classInfo, GetVariable)(p_str_variable);
                if (idx_variable > -1) {
                    p_hnd_object->Registry()->ExtractValue(p_hnd_object->Val(), &ptr_script->classInfo->name, idx_variable, &p_vm_variable);
                    return false; // stop iterating
                } else {
                    return true; // keep iterating
                }
            }

            // Getters
            VMValue *Ptr() {
                return &p_vm_variable;
            }
            VMValue Val() {
                return p_vm_variable;
            }
    };

    Actor *Get_Alias_Actor(Object_Handle *hnd_alias) {
        BSFixedString str_variable("p_ref_actor");
        Functor_Get_Object_Value functor(hnd_alias, &str_variable);
        hnd_alias->Registry()->VisitScripts(hnd_alias->Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Identifier) {
            return (Actor *)hnd_alias->Policy()->Resolve(kFormType_Character, vm_actor->data.id->GetHandle());
        } else {
            return NULL;
        }
    }

    UInt64 Alias_Is_Clone(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_clone");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Follower(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_follower");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Settler(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_settler");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Immobile(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_immobile");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Thrall(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_thrall");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Paralyzed(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_paralyzed");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Mannequin(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_mannequin");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    UInt64 Alias_Is_Reanimated(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        BSFixedString str_variable("p_is_reanimated");
        Functor_Get_Object_Value functor(&hnd_alias, &str_variable);
        hnd_alias.Registry()->VisitScripts(hnd_alias.Val(), &functor);

        VMValue *vm_actor = functor.Ptr();
        if (vm_actor->GetUnmangledType() == VMValue::kType_Bool) {
            return vm_actor->data.b ? 1 : 0;
        } else {
            return -1;
        }
    }

    Actor *Get_Alias_Actor(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Get_Alias_Actor(&hnd_alias);
    }

    int Compare_Aliases(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *ptr_alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *ptr_alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!ptr_alias_a || !ptr_alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return ptr_alias_b - ptr_alias_a;
        }

        VMClassRegistry *ptr_registry = (*g_skyrimVM)->GetClassRegistry();
        IObjectHandlePolicy *ptr_policy = ptr_registry->GetHandlePolicy();
        Object_Handle hnd_alias_a(ptr_registry, ptr_policy, kFormType_Alias, ptr_alias_a);
        Object_Handle hnd_alias_b(ptr_registry, ptr_policy, kFormType_Alias, ptr_alias_b);

        Actor *ptr_actor_a = Get_Alias_Actor(&hnd_alias_a);
        Actor *ptr_actor_b = Get_Alias_Actor(&hnd_alias_b);

        BSFixedString str_actor_a = CALL_MEMBER_FN(ptr_actor_a, GetReferenceName)();
        BSFixedString str_actor_b = CALL_MEMBER_FN(ptr_actor_b, GetReferenceName)();

        return strcmp(str_actor_a.data, str_actor_b.data);
    }

    VMResultArray<BGSBaseAlias *> Sort_Aliases(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases) {
        UInt32 idx_aliases = 0;
        UInt32 num_aliases = arr_aliases.Length();
        BGSBaseAlias *ptr_alias;

        VMResultArray<BGSBaseAlias *> arr_return;
        arr_return.reserve(num_aliases);

        while (idx_aliases < num_aliases) {
            arr_aliases.Get(&ptr_alias, idx_aliases);
            arr_return.push_back(ptr_alias);
            idx_aliases += 1;
        }

        qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Aliases);
        return arr_return;
    }

    int Compare_BSFixedStrings(const void *ptr_item_a, const void *ptr_item_b) {
        return _stricmp((const char *)*(BSFixedString **)ptr_item_a, (const char *)*(BSFixedString **)ptr_item_b);
    }

    VMResultArray<BSFixedString> Get_Race_Names(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases) {
        size_t idx_aliases;
        size_t num_aliases;
        BGSBaseAlias *ptr_alias;
        Actor *ptr_actor;
        const char *ptr_race_name;

        VMResultArray<BSFixedString> vec_race_names;
        size_t idx_race_names;
        size_t num_race_names;
        bool has_race_name;

        for (idx_aliases = 0, num_aliases = arr_aliases.Length(); idx_aliases < num_aliases; idx_aliases += 1) {
            arr_aliases.Get(&ptr_alias, idx_aliases);
            ptr_actor = Get_Alias_Actor(ptr_alias);
            if (ptr_actor) {
                ptr_race_name = ptr_actor->race->fullName.name;

                has_race_name = false;
                for (idx_race_names = 0, num_race_names = vec_race_names.size(); idx_race_names < num_race_names; idx_race_names += 1) {
                    if (_stricmp(vec_race_names[idx_race_names].data, ptr_race_name) == 0) {
                        has_race_name = true;
                        break;
                    }
                }

                if (!has_race_name) {
                    vec_race_names.push_back(ptr_race_name);
                }
            }
        }

        qsort(vec_race_names.data(), vec_race_names.size(), sizeof(BSFixedString), Compare_BSFixedStrings);
        return vec_race_names;
    }

    #define Bit_Set(BITS, BIT_IDX) \
        ( (BITS) |=  ( (1llu) << (BIT_IDX) ) )

    #define Bit_Unset(BITS, BIT_IDX) \
        ( (BITS) &= ~( (1llu) << (BIT_IDX) ) )

    #define Bit_Is_Set(BITS, BIT_IDX) \
        ( (1llu) &   ( (BITS) >> (BIT_IDX) ) )

    #define Bit_Toggle(BITS, BIT_IDX) \
        ( (BITS) ^=  ( (1llu) << (BIT_IDX) ) )

    #define Bit_Clear(BITS)\
        ( (BITS) = 0 )

    #define M \
        do {

    #define W \
        } while (0)

    enum {
        IS_ALIVE,
        IS_DEAD,

        IS_ORIGINAL,
        IS_CLONE,

        IS_UNIQUE,
        IS_GENERIC,

        IS_FOLLOWER,
        ISNT_FOLLOWER,

        IS_SETTLER,
        ISNT_SETTLER,

        IS_IMMOBILE,
        ISNT_IMMOBILE,

        IS_THRALL,
        ISNT_THRALL,

        IS_SNEAK,
        ISNT_SNEAK,

        IS_PARALYZED,
        ISNT_PARALYZED,

        IS_MANNEQUIN,
        ISNT_MANNEQUIN,

        IS_REANIMATED,
        ISNT_REANIMATED
    };

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    UInt32 Filter_Flag(StaticFunctionTag *, UInt32 int_flags, BSFixedString str_command, BSFixedString str_flag) {
        s64 idx_flags = -1;
        if (false) {

        } else if (_stricmp(str_flag.data, "IS_ALIVE") == 0) {
            idx_flags = IS_ALIVE;
        } else if (_stricmp(str_flag.data, "IS_DEAD") == 0) {
            idx_flags = IS_DEAD;

        } else if (_stricmp(str_flag.data, "IS_ORIGINAL") == 0) {
            idx_flags = IS_ORIGINAL;
        } else if (_stricmp(str_flag.data, "IS_CLONE") == 0) {
            idx_flags = IS_CLONE;

        } else if (_stricmp(str_flag.data, "IS_UNIQUE") == 0) {
            idx_flags = IS_UNIQUE;
        } else if (_stricmp(str_flag.data, "IS_GENERIC") == 0) {
            idx_flags = IS_GENERIC;

        } else if (_stricmp(str_flag.data, "IS_FOLLOWER") == 0) {
            idx_flags = IS_FOLLOWER;
        } else if (_stricmp(str_flag.data, "ISNT_FOLLOWER") == 0) {
            idx_flags = ISNT_FOLLOWER;

        } else if (_stricmp(str_flag.data, "IS_SETTLER") == 0) {
            idx_flags = IS_SETTLER;
        } else if (_stricmp(str_flag.data, "ISNT_SETTLER") == 0) {
            idx_flags = ISNT_SETTLER;

        } else if (_stricmp(str_flag.data, "IS_IMMOBILE") == 0) {
            idx_flags = IS_IMMOBILE;
        } else if (_stricmp(str_flag.data, "ISNT_IMMOBILE") == 0) {
            idx_flags = ISNT_IMMOBILE;

        } else if (_stricmp(str_flag.data, "IS_THRALL") == 0) {
            idx_flags = IS_THRALL;
        } else if (_stricmp(str_flag.data, "ISNT_THRALL") == 0) {
            idx_flags = ISNT_THRALL;

        } else if (_stricmp(str_flag.data, "IS_SNEAK") == 0) {
            idx_flags = IS_SNEAK;
        } else if (_stricmp(str_flag.data, "ISNT_SNEAK") == 0) {
            idx_flags = ISNT_SNEAK;

        } else if (_stricmp(str_flag.data, "IS_PARALYZED") == 0) {
            idx_flags = IS_PARALYZED;
        } else if (_stricmp(str_flag.data, "ISNT_PARALYZED") == 0) {
            idx_flags = ISNT_PARALYZED;

        } else if (_stricmp(str_flag.data, "IS_MANNEQUIN") == 0) {
            idx_flags = IS_MANNEQUIN;
        } else if (_stricmp(str_flag.data, "ISNT_MANNEQUIN") == 0) {
            idx_flags = ISNT_MANNEQUIN;

        } else if (_stricmp(str_flag.data, "IS_REANIMATED") == 0) {
            idx_flags = IS_REANIMATED;
        } else if (_stricmp(str_flag.data, "ISNT_REANIMATED") == 0) {
            idx_flags = ISNT_REANIMATED;

        }

        if (idx_flags > -1ll) {
            if (false) {

            } else if (_stricmp(str_command.data, "SET") == 0) {
                return Bit_Set(int_flags, idx_flags);
            } else if (_stricmp(str_command.data, "UNSET") == 0) {
                return Bit_Unset(int_flags, idx_flags);
            } else if (_stricmp(str_command.data, "IS_SET") == 0) {
                return Bit_Is_Set(int_flags, idx_flags) > 0 ? 1 : 0;

            } else {
                _MESSAGE("not a command: %s", str_command.data);
                return int_flags;
            }
            
        } else {
            _MESSAGE("not a flag: %s", str_flag.data);
            return int_flags;
        }
    }

    VMResultArray<BGSBaseAlias *> Filter_Aliases(StaticFunctionTag *,
                                                 VMArray<BGSBaseAlias *> arr_aliases,
                                                 BSFixedString str_sex, // "male", "female", "none"
                                                 BSFixedString str_race,
                                                 UInt32 int_flags) {
        // what about style and vitality?

        VMResultArray<BGSBaseAlias *> vec_buffer_a;
        VMResultArray<BGSBaseAlias *> vec_buffer_b;
        VMResultArray<BGSBaseAlias *> *ptr_vec_read = &vec_buffer_a;
        VMResultArray<BGSBaseAlias *> *ptr_vec_write = &vec_buffer_b;
        VMResultArray<BGSBaseAlias *> *ptr_vec_temp;

        BGSBaseAlias *ptr_base_alias;
        TESNPC *ptr_base_actor;
        Actor *ptr_ref_actor;

        #define SWAP_BUFFERS                \
        M                                   \
            ptr_vec_temp = ptr_vec_read;    \
            ptr_vec_read = ptr_vec_write;   \
            ptr_vec_write = ptr_vec_temp;   \
            ptr_vec_write->clear();         \
        W

        for (u64 idx_aliases = 0, num_aliases = arr_aliases.Length(); idx_aliases < num_aliases; idx_aliases += 1) {
            arr_aliases.Get(&ptr_base_alias, idx_aliases);
            ptr_vec_read->push_back(ptr_base_alias);
        }

        // SEX
        if (str_sex && str_sex.data[0] != 0) {
            // the form may not be correct! it would be nice to verify with body model,
            // but I haven't figured that out yet, or if it's even possible in SKSE.

            s64 int_sex_target;
            if (_stricmp(str_sex.data, "male") == 0) {
                int_sex_target = 0;
            } else if (_stricmp(str_sex.data, "female") == 0) {
                int_sex_target = 1;
            } else if (_stricmp(str_sex.data, "none") == 0) {
                int_sex_target = -1;
            } else {
                int_sex_target = -2;
            }

            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Get_Alias_Actor(ptr_base_alias);
                if (ptr_ref_actor) {
                    ptr_base_actor = (TESNPC *)ptr_ref_actor->baseForm;
                    if (CALL_MEMBER_FN(ptr_base_actor, GetSex)() == int_sex_target) {
                        ptr_vec_write->push_back(ptr_base_alias);
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // RACE
        if (str_race && str_race.data[0] != 0) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Get_Alias_Actor(ptr_base_alias);
                if (ptr_ref_actor) {
                    if (_stricmp(ptr_ref_actor->race->fullName.name.data, str_race.data) == 0) {
                        ptr_vec_write->push_back(ptr_base_alias);
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // ALIVE/DEAD
        if (Bit_Is_Set(int_flags, IS_ALIVE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Get_Alias_Actor(ptr_base_alias);
                if (!ptr_ref_actor->IsDead(1)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, IS_DEAD)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Get_Alias_Actor(ptr_base_alias);
                if (ptr_ref_actor->IsDead(1)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // ORIGINAL/CLONE
        if (Bit_Is_Set(int_flags, IS_ORIGINAL)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Clone(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, IS_CLONE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Clone(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // FOLLOWER
        if (Bit_Is_Set(int_flags, IS_FOLLOWER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Follower(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_FOLLOWER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Follower(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // SETTLER
        if (Bit_Is_Set(int_flags, IS_SETTLER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Settler(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_SETTLER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Settler(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // IMMOBILE
        if (Bit_Is_Set(int_flags, IS_IMMOBILE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Immobile(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_IMMOBILE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Immobile(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // THRALL
        if (Bit_Is_Set(int_flags, IS_THRALL)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Thrall(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_THRALL)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Thrall(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // PARALYZED
        if (Bit_Is_Set(int_flags, IS_PARALYZED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Paralyzed(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_PARALYZED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Paralyzed(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // MANNEQUIN
        if (Bit_Is_Set(int_flags, IS_MANNEQUIN)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Mannequin(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_MANNEQUIN)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Mannequin(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // REANIMATED
        if (Bit_Is_Set(int_flags, IS_REANIMATED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Reanimated(ptr_base_alias) == 1) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_REANIMATED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Reanimated(ptr_base_alias) == 0) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        return *ptr_vec_read;

        #undef SWAP_BUFFERS
    }

    VMResultArray<BGSBaseAlias *> Aliases_Slice(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, UInt32 idx_from, UInt32 idx_to_ex) {
        VMResultArray<BGSBaseAlias *> vec_slice;

        if (idx_from < 0) {
            idx_from = 0;
        }

        if (idx_to_ex > arr_aliases.Length() || idx_to_ex < 0) {
            idx_to_ex = arr_aliases.Length();
        }

        u64 num_aliases = idx_to_ex - idx_from;
        if (num_aliases < 1) {
            vec_slice.push_back(NULL);
        } else {
            BGSBaseAlias *ptr_alias;
            vec_slice.reserve(num_aliases);
            for (u64 idx = idx_from, idx_end = idx_to_ex; idx < idx_end; idx += 1) {
                arr_aliases.Get(&ptr_alias, idx);
                vec_slice.push_back(ptr_alias);
            }
        }

        return vec_slice;
    }

    bool Register_Functions(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>(
                "Outfit_Add_Item",
                "doticu_npcp",
                doticu_npcp::Outfit_Add_Item,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>(
                "Outfit_Remove_Item",
                "doticu_npcp",
                doticu_npcp::Outfit_Remove_Item,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>(
                "SetOutfit",
                "Actor",
                doticu_npcp::Actor_Set_Outfit,
                registry)
        );

        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>>(
                "Sort_Aliases",
                "doticu_npcp",
                doticu_npcp::Sort_Aliases,
                registry)
        );

        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BSFixedString>, VMArray<BGSBaseAlias *>>(
                "Get_Race_Names",
                "doticu_npcp",
                doticu_npcp::Get_Race_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, UInt32, UInt32, BSFixedString, BSFixedString>(
                "Filter_Flag",
                "doticu_npcp",
                doticu_npcp::Filter_Flag,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction4 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, BSFixedString, BSFixedString, UInt32>(
                "Filter_Aliases",
                "doticu_npcp",
                doticu_npcp::Filter_Aliases,
                registry)
        );

        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, UInt32, UInt32>(
                "Aliases_Slice",
                "doticu_npcp",
                doticu_npcp::Aliases_Slice,
                registry)
        );

        return true;
    }

}
