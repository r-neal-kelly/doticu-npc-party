/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "types.h"
#include "quest.h"
#include "object_ref.h"
#include "member.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest) {
        if (!quest) {
            return "";
        }

        TESFullName *full_name = DYNAMIC_CAST(quest, TESQuest, TESFullName);
        if (!full_name || !full_name->name || !full_name->name.data) {
            return "";
        }

        return full_name->name.data;
    }

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    VMResultArray<BGSBaseAlias *> Get_Used_Aliases(StaticFunctionTag *, TESQuest *ref_quest) {
        VMResultArray<BGSBaseAlias *> vec_aliases;
        if (ref_quest == NULL) {
            return vec_aliases;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        vec_aliases.reserve(ptr_aliases->count);

        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (Member::Is_Created(ptr_alias) && Member::Get_Actor(ptr_alias)) {
                vec_aliases.push_back(ptr_alias);
            }
        }

        while (vec_aliases.size() < ptr_aliases->count) {
            vec_aliases.push_back(NULL);
        }

        return vec_aliases;
    }
    VMResultArray<SInt32> Get_Free_Alias_IDs(StaticFunctionTag *, TESQuest *ref_quest) {
        VMResultArray<SInt32> vec_free;
        if (ref_quest == NULL) {
            return vec_free;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        vec_free.reserve(ptr_aliases->count);

        BGSBaseAlias *ptr_alias;
        for (s64 idx = ptr_aliases->count - 1; idx >= 0; idx -= 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (!Member::Is_Created(ptr_alias) || !Member::Get_Actor(ptr_alias)) {
                vec_free.push_back(ptr_alias->aliasId);
            }
        }

        while (vec_free.size() < ptr_aliases->count) {
            vec_free.push_back(-1);
        }

        return vec_free;
    }

    VMResultArray<BGSBaseAlias *> Get_3D_Loaded_Aliases(StaticFunctionTag *, TESQuest *ref_quest) {
        VMResultArray<BGSBaseAlias *> vec_loaded;

        if (!ref_quest) {
            return vec_loaded;
        }
        
        for (u64 idx = 0, size = ref_quest->aliases.count; idx < size; idx += 1) {
            BGSBaseAlias *alias;
            ref_quest->aliases.GetNthItem(idx, alias);
            if (!alias) {
                continue;
            }

            Actor *actor = Member::Get_Actor(alias);
            if (!actor || !actor->loadedState) {
                continue;
            }

            vec_loaded.push_back(alias);
        }

        return vec_loaded;
    }

    UInt32 Count_Used_Aliases(StaticFunctionTag *, TESQuest *ref_quest) {
        UInt32 count = 0;
        if (ref_quest == NULL) {
            return count;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (Member::Is_Created(ptr_alias) && Member::Get_Actor(ptr_alias)) {
                count += 1;
            }
        }

        return count;
    }
    UInt32 Count_Free_Aliases(StaticFunctionTag *, TESQuest *ref_quest) {
        UInt32 count = 0;
        if (ref_quest == NULL) {
            return count;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (!Member::Is_Created(ptr_alias) || !Member::Get_Actor(ptr_alias)) {
                count += 1;
            }
        }

        return count;
    }
    UInt32 Count_Mannequins(StaticFunctionTag *, TESQuest *ref_quest) {
        UInt32 count = 0;
        if (ref_quest == NULL) {
            return count;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (Member::Is_Created(ptr_alias) && Member::Is_Mannequin(ptr_alias)) {
                count += 1;
            }
        }

        return count;
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, TESQuest *>(
                "Quest_Get_Used_Aliases",
                "doticu_npcp",
                Get_Used_Aliases,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<SInt32>, TESQuest *>(
                "Quest_Get_Free_Alias_IDs",
                "doticu_npcp",
                Get_Free_Alias_IDs,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, TESQuest *>(
                "Quest_Get_3D_Loaded_Aliases",
                "doticu_npcp",
                Get_3D_Loaded_Aliases,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, UInt32, TESQuest *>(
                "Quest_Count_Used_Aliases",
                "doticu_npcp",
                Count_Used_Aliases,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, UInt32, TESQuest *>(
                "Quest_Count_Free_Aliases",
                "doticu_npcp",
                Count_Free_Aliases,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, UInt32, TESQuest *>(
                "Quest_Count_Mannequins",
                "doticu_npcp",
                Count_Mannequins,
                registry)
        );

        _MESSAGE("Added Quest functions.");

        return true;
    }

}}}
