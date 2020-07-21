/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameRTTI.h"

#include "object_ref.h"
#include "quest.h"
#include "types.h"
#include "utils.h"

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

    void Force_Reference_To(Quest_t* quest, UInt32 alias_id, Reference_t* reference)
    {
        static auto force_reference_to = reinterpret_cast
            <UInt32 (*)(Quest_t*, UInt32, Reference_t*)>
            (RelocationManager::s_baseAddr + Offsets::Quest::FORCE_REFERENCE_TO);
        force_reference_to(quest, alias_id, reference);
    }

    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id)
    {
        if (quest) {
            Quest_t2::Hash_Map_t* hash_map = (Quest_t2::Hash_Map_t*)((u8*)quest + 0x070);
            return hash_map->Has_Key(alias_id);
        } else {
            return false;
        }
    }

    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id)
    {
        if (quest) {
            tArray<Reference_Handle_t>* promoted = (tArray<Reference_Handle_t>*)((u8*)quest + 0x250);
            if (promoted) {
                for (size_t idx = 0, count = promoted->count; idx < count; idx += 1) {
                    Reference_Handle_t handle = promoted->entries[idx];
                    Reference_t* reference = Object_Ref::From_Handle(handle);
                    if (reference) {
                        XAliases_t* xaliases = static_cast<XAliases_t*>
                            (reference->extraData.GetByType(kExtraData_AliasInstanceArray));
                        if (xaliases) {
                            for (size_t idx = 0, count = xaliases->aliases.count; idx < count; idx += 1) {
                                XAliases_t::AliasInfo* info = xaliases->aliases.entries[idx];
                                if (info && info->quest == quest && info->alias && info->alias->aliasId == alias_id) {
                                    return static_cast<Actor_t*>(reference);
                                }
                            }
                        }
                    }
                }
            }
        }

        return nullptr;
    }

    void Log_Aliases(Quest_t* quest)
    {
        _MESSAGE("Start Log Aliases: %s {", Get_Name(quest));

        _MESSAGE("Hashmap");
        Quest_t2::Hash_Map_t* hash_map = (Quest_t2::Hash_Map_t*)((u8*)quest + 0x070);
        for (size_t idx = 0, count = hash_map->capacity; idx < count; idx += 1) {
            Quest_t2::Hash_Map_t::Entry_t* entry = hash_map->entries + idx;
            if (entry->chain != nullptr) {
                _MESSAGE("    idx: %zu, key: %u, value: %u", idx, entry->tuple.key, entry->tuple.value);
            }
        }

        _MESSAGE("Promoted");
        tArray<Reference_Handle_t>* arr = (tArray<Reference_Handle_t>*)((u8*)quest + 0x250);
        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            Reference_Handle_t handle = arr->entries[idx];
            if (handle) {
                Reference_t* reference = Object_Ref::From_Handle(handle);
                if (reference) {
                    XAliases_t* xaliases = static_cast<XAliases_t*>
                        (reference->extraData.GetByType(kExtraData_AliasInstanceArray));
                    if (xaliases) {
                        for (size_t idx1 = 0, count = xaliases->aliases.count; idx1 < count; idx1 += 1) {
                            if (xaliases->aliases.entries[idx1]->quest == quest) {
                                UInt16 alias_id = xaliases->aliases.entries[idx1]->alias->aliasId;
                                _MESSAGE("    idx: %zu, handle: %u, ref: %p, id: %u",
                                         idx, handle, reference, alias_id);
                            }
                        }
                    }
                }
            }
        }

        _MESSAGE("}");
    }

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        return true;
    }

}}}
