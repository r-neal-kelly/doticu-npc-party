/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "aliases.h"

namespace doticu_npcp { namespace Party { namespace Aliases {

    Range_t<Alias_t**> Aliases(Aliases_t* self, UInt64 begin, UInt64 end)
    {
        if (self) {
            if (self->aliases.count >= begin && self->aliases.count >= end) {
                return {
                    reinterpret_cast<Alias_t**>(self->aliases.entries + begin),
                    reinterpret_cast<Alias_t**>(self->aliases.entries + end)
                };
            } else {
                return {
                    reinterpret_cast<Alias_t**>(self->aliases.entries),
                    reinterpret_cast<Alias_t**>(self->aliases.entries)
                };
            }
        } else {
            return {
                nullptr,
                nullptr
            };
        }
    }

    Alias_t* From_Actor(Aliases_t* self, Actor_t* actor)
    {
        if (self && actor) {
            XAliases_t* xaliases = static_cast<XAliases_t*>(actor->extraData.GetByType(kExtraData_AliasInstanceArray));
            if (xaliases) {
                for (u64 idx = 0, size = xaliases->aliases.count; idx < size; idx += 1) {
                    XAliases_t::AliasInfo* info = xaliases->aliases[idx];
                    if (info && info->quest == self) {
                        return reinterpret_cast<Alias_t*>(info->alias);
                    }
                }
                return nullptr;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

}}}

































#include "skse64/GameRTTI.h"

#include "actor_base2.h"
#include "actor2.h"
#include "aliases.h"
#include "member.h"
#include "papyrus.h"
#include "string2.h"
#include "utils.h"

namespace doticu_npcp { namespace Aliases {

    int Compare_Name(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!alias_a || !alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return alias_b - alias_a;
        }

        Actor *actor_a = Member::Get_Actor(alias_a);
        Actor *actor_b = Member::Get_Actor(alias_b);
        if (!actor_a || !actor_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return actor_b - actor_a;
        }

        BSFixedString str_actor_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
        BSFixedString str_actor_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

        return strcmp(str_actor_a.data, str_actor_b.data);
    }
    int Compare_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!alias_a || !alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return alias_b - alias_a;
        }

        Actor *actor_a = Member::Get_Actor(alias_a);
        Actor *actor_b = Member::Get_Actor(alias_b);
        if (!actor_a || !actor_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return actor_b - actor_a;
        }

        BSFixedString str_actor_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
        BSFixedString str_actor_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

        return _stricmp(str_actor_a.data, str_actor_b.data);
    }
    int Compare_Rating_Name(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!alias_a || !alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return alias_b - alias_a;
        }

        Actor *actor_a = Member::Get_Actor(alias_a);
        Actor *actor_b = Member::Get_Actor(alias_b);
        if (!actor_a || !actor_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return actor_b - actor_a;
        }

        SInt32 int_rating_a = Member::Get_Rating(alias_a);
        SInt32 int_rating_b = Member::Get_Rating(alias_b);
        if (int_rating_a != int_rating_b) {
            return int_rating_b - int_rating_a;
        } else {
            BSFixedString str_actor_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
            BSFixedString str_actor_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

            return strcmp(str_actor_a.data, str_actor_b.data);
        }
    }
    int Compare_Rating_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!alias_a || !alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return alias_b - alias_a;
        }

        Actor *actor_a = Member::Get_Actor(alias_a);
        Actor *actor_b = Member::Get_Actor(alias_b);
        if (!actor_a || !actor_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return actor_b - actor_a;
        }

        SInt32 int_rating_a = Member::Get_Rating(alias_a);
        SInt32 int_rating_b = Member::Get_Rating(alias_b);
        if (int_rating_a != int_rating_b) {
            return int_rating_b - int_rating_a;
        } else {
            BSFixedString str_actor_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
            BSFixedString str_actor_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

            return _stricmp(str_actor_a.data, str_actor_b.data);
        }
    }

    int Compare_Race_Names(const void *ptr_item_a, const void *ptr_item_b) {
        return _stricmp((const char *)*(BSFixedString **)ptr_item_a, (const char *)*(BSFixedString **)ptr_item_b);
    }

    bool Has_Head(VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head) {
        if (!base_with_head) {
            return false;
        }

        BGSBaseAlias *alias = NULL;
        for (u64 idx = 0, size = aliases.Length(); idx < size; idx += 1) {
            aliases.Get(&alias, idx);
            if (!alias) {
                continue;
            }

            Actor *actor = Member::Get_Actor(alias);
            if (!actor) {
                continue;
            }

            TESNPC *base = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
            if (Actor_Base2::Has_Same_Head(base, base_with_head)) {
                return true;
            }
        }

        return false;
    }

    SInt32 Count_Heads(VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head, bool do_print) {
        if (!base_with_head) {
            return -1;
        }

        if (do_print) {
            Utils::Print("Count_Heads:");
        }

        SInt32 count = 0;
        BGSBaseAlias *alias = NULL;
        for (u64 idx = 0, size = aliases.Length(); idx < size; idx += 1) {
            aliases.Get(&alias, idx);
            if (!alias) {
                continue;
            }

            Actor *actor = Member::Get_Actor(alias);
            if (!actor) {
                continue;
            }

            TESNPC *base = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
            if (Actor_Base2::Has_Same_Head(base, base_with_head)) {
                count += 1;
                if (do_print) {
                    std::string str_print("    ");
                    str_print.append(Actor2::Get_Name(actor));
                    Utils::Print(str_print.c_str());
                }
            }
        }

        return count;
    }

    VMResultArray<Alias_t *> Sort(VMResultArray<Alias_t *> aliases, const char *algorithm)
    {
        if (String2::Is_Same_Caseless(algorithm, "NAME"))
        {
            qsort(&aliases[0], aliases.size(), sizeof(Alias_t *), Compare_Name);
        }
        else if (String2::Is_Same_Caseless(algorithm, "NAME_CASELESS"))
        {
            qsort(&aliases[0], aliases.size(), sizeof(Alias_t *), Compare_Name_Caseless);
        }
        else if (String2::Is_Same_Caseless(algorithm, "RATING_NAME"))
        {
            qsort(&aliases[0], aliases.size(), sizeof(Alias_t *), Compare_Rating_Name);
        }
        else if (String2::Is_Same_Caseless(algorithm, "RATING_NAME_CASELESS"))
        {
            qsort(&aliases[0], aliases.size(), sizeof(Alias_t *), Compare_Rating_Name_Caseless);
        }
        else
        {
            qsort(&aliases[0], aliases.size(), sizeof(Alias_t *), Compare_Name);
        }

        return aliases;
    }

}}

namespace doticu_npcp { namespace Aliases { namespace Exports {

    VMResultArray<BGSBaseAlias *> Slice(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr, SInt32 idx_from, SInt32 idx_to_ex) {
        return Papyrus::Slice_Array<BGSBaseAlias *>(arr, idx_from, idx_to_ex);
    }

    VMResultArray<BGSBaseAlias *> Sort(StaticFunctionTag *,
                                       VMArray<BGSBaseAlias *> arr_aliases,
                                       BSFixedString str_algorithm // NAME, NAME_CASELESS, RATING_NAME, RATING_NAME_CASELESS
    ) {
        // I want to be able to sort by race next
        // also add reverse options.

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

        if (_stricmp(str_algorithm.data, "NAME") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Name);
        } else if (_stricmp(str_algorithm.data, "NAME_CASELESS") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Name_Caseless);
        } else if (_stricmp(str_algorithm.data, "RATING_NAME") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Rating_Name);
        } else if (_stricmp(str_algorithm.data, "RATING_NAME_CASELESS") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Rating_Name_Caseless);
        } else {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Compare_Name);
        }

        return arr_return;
    }

    VMResultArray<BGSBaseAlias *> Filter(StaticFunctionTag *,
                                         VMArray<BGSBaseAlias *> arr_aliases,
                                         VMArray<BSFixedString> arr_strings,
                                         VMArray<SInt32> arr_ints
    ) {
        // we pack arguments to make the function signature less cluttered and more easily extendable
        BSFixedString str_sex;      // = "" ("male", "female", "none", or "" for any)
        BSFixedString str_race;     // = "" (exposed by game, "" for any)
        BSFixedString str_search;   // = "" (user input, "" for no search)
        SInt32 int_style;           // = 0 (exposed by doticu_npcp_codes, 0+ for any)
        SInt32 int_vitality;        // = 0 (exposed by doticu_npcp_codes, 0+ for any)
        SInt32 int_outfit2;         // = 0 (exposed by doticu_npcp_codes, 0+ for any)
        SInt32 int_rating;          // = -1 (exposed by doticu_npcp_member, -1 or less for any, 0 is no rating)
        UInt32 int_flags;           // = 0 (constructed with Aliases_Filter_Flag, 0 for no flags)

        u64 len_arr_strings = arr_strings.Length();
        if (len_arr_strings > 0) {
            arr_strings.Get(&str_sex, 0);
        }
        if (len_arr_strings > 1) {
            arr_strings.Get(&str_race, 1);
        }
        if (len_arr_strings > 2) {
            arr_strings.Get(&str_search, 2);
        }

        u64 len_arr_ints = arr_ints.Length();
        if (len_arr_ints > 0) {
            arr_ints.Get(&int_style, 0);
        }
        if (len_arr_ints > 1) {
            arr_ints.Get(&int_vitality, 1);
        }
        if (len_arr_ints > 2) {
            arr_ints.Get(&int_outfit2, 2);
        }
        if (len_arr_ints > 3) {
            arr_ints.Get(&int_rating, 3);
        }
        if (len_arr_ints > 4) {
            // just in case of any weirdness when bit-shifting
            SInt32 int_flags_signed;
            arr_ints.Get(&int_flags_signed, 4);
            int_flags = (UInt32)int_flags_signed;
        }

        // we filter the read buffer into the write buffer, and then swap them after each pass.
        // macros keep it more understandable, and less error prone. they are undef'd at the end of func
        VMResultArray<BGSBaseAlias *> vec_buffer_a;
        VMResultArray<BGSBaseAlias *> vec_buffer_b;
        VMResultArray<BGSBaseAlias *> *ptr_vec_read = &vec_buffer_a;
        VMResultArray<BGSBaseAlias *> *ptr_vec_write = &vec_buffer_b;
        VMResultArray<BGSBaseAlias *> *ptr_vec_temp;
        BGSBaseAlias *ptr_base_alias;
        Actor *ptr_ref_actor;

        #define FOR_EACH()                                  \
        for (                                               \
            u64 it_idx = 0, it_size = ptr_vec_read->size(); \
            it_idx < it_size;                               \
            it_idx += 1                                     \
        )

        #define ALIAS ptr_base_alias

        #define ACTOR ptr_ref_actor

        #define READ_ALIAS (                    \
            ALIAS = ptr_vec_read->at(it_idx)    \
        )

        #define READ_ACTOR (                    \
            ACTOR = Member::Get_Actor(ALIAS)    \
        )

        #define WRITE_ALIAS (               \
            ptr_vec_write->push_back(ALIAS) \
        )

        #define SWAP_BUFFERS                \
        M                                   \
            ptr_vec_temp = ptr_vec_read;    \
            ptr_vec_read = ptr_vec_write;   \
            ptr_vec_write = ptr_vec_temp;   \
            ptr_vec_write->clear();         \
        W

        // we copy aliases into read buffer up front to start the pattern without handling VMArray's
        // different methods on first pass. this means we can rearrange filter passes more robustly
        for (u64 idx_aliases = 0, num_aliases = arr_aliases.Length(); idx_aliases < num_aliases; idx_aliases += 1) {
            arr_aliases.Get(&ptr_base_alias, idx_aliases);
            ptr_vec_read->push_back(ptr_base_alias);
        }

        // SEX
        if (str_sex.data && str_sex.data[0] != 0) {
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

            // the form may not be correct! it would be nice to verify with body model,
            // but I haven't figured that out yet, or if it's even possible in SKSE.
            FOR_EACH() {
                READ_ALIAS;
                READ_ACTOR;
                if (ACTOR) {
                    if (CALL_MEMBER_FN((TESNPC *)ACTOR->baseForm, GetSex)() == int_sex_target) {
                        WRITE_ALIAS;
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // RACE
        if (str_race.data && str_race.data[0] != 0) {
            FOR_EACH() {
                READ_ALIAS;
                READ_ACTOR;
                if (ACTOR) {
                    if (_stricmp(ACTOR->race->fullName.name.data, str_race.data) == 0) {
                        WRITE_ALIAS;
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // SEARCH
        if (str_search.data && str_search.data[0] != 0) {
            BSFixedString str_name;
            FOR_EACH() {
                READ_ALIAS;
                READ_ACTOR;
                if (ACTOR) {
                    str_name = CALL_MEMBER_FN(ACTOR, GetReferenceName)();
                    if (strlen(str_search.data) > 1) {
                        if (String2::Contains_Caseless(str_name.data, str_search.data)) {
                            WRITE_ALIAS;
                        }
                    } else {
                        if (String2::Starts_With_Caseless(str_name.data, str_search.data)) {
                            WRITE_ALIAS;
                        }
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // STYLE
        if (int_style < 0) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Get_Style(ALIAS) == int_style) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // VITALITY
        if (int_vitality < 0) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Get_Vitality(ALIAS) == int_vitality) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // OUTFIT
        if (int_outfit2 < 0) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Get_Outfit2(ALIAS) == int_outfit2) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // RATING
        if (int_rating > -1) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Get_Rating(ALIAS) == int_rating) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG ALIVE/DEAD
        if (Bit_Is_Set(int_flags, IS_ALIVE)) {
            FOR_EACH() {
                READ_ALIAS;
                READ_ACTOR;
                if (ACTOR && !ACTOR->IsDead(1)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, IS_DEAD)) {
            FOR_EACH() {
                READ_ALIAS;
                READ_ACTOR;
                if (ACTOR && ACTOR->IsDead(1)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG ORIGINAL/CLONE
        if (Bit_Is_Set(int_flags, IS_ORIGINAL)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Original(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, IS_CLONE)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Clone(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG FOLLOWER
        if (Bit_Is_Set(int_flags, IS_FOLLOWER)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Follower(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_FOLLOWER)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Follower(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG SETTLER
        if (Bit_Is_Set(int_flags, IS_SETTLER)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Settler(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_SETTLER)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Settler(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG IMMOBILE
        if (Bit_Is_Set(int_flags, IS_IMMOBILE)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Immobile(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_IMMOBILE)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Immobile(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG THRALL
        if (Bit_Is_Set(int_flags, IS_THRALL)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Thrall(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_THRALL)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Thrall(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG PARALYZED
        if (Bit_Is_Set(int_flags, IS_PARALYZED)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Paralyzed(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_PARALYZED)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Paralyzed(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG MANNEQUIN
        if (Bit_Is_Set(int_flags, IS_MANNEQUIN)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Mannequin(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_MANNEQUIN)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Mannequin(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        // FLAG REANIMATED
        if (Bit_Is_Set(int_flags, IS_REANIMATED)) {
            FOR_EACH() {
                READ_ALIAS;
                if (Member::Is_Reanimated(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        } else if (Bit_Is_Set(int_flags, ISNT_REANIMATED)) {
            FOR_EACH() {
                READ_ALIAS;
                if (!Member::Is_Reanimated(ALIAS)) {
                    WRITE_ALIAS;
                }
            }
            SWAP_BUFFERS;
        }

        return *ptr_vec_read;

        #undef SWAP_BUFFERS
        #undef WRITE_ALIAS
        #undef READ_ACTOR
        #undef READ_ALIAS
        #undef ACTOR
        #undef ALIAS
        #undef FOR_EACH
    }

    // we use strings to avoid both programs having to know the actual flags, which is more error prone and harder to keep up to date
    UInt32 Filter_Flag(StaticFunctionTag *,
                       UInt32 int_flags,
                       BSFixedString str_command,
                       BSFixedString str_flag
    ) {
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

    VMResultArray<BSFixedString> Get_Race_Names(StaticFunctionTag *,
                                                VMArray<BGSBaseAlias *> arr_aliases
    ) {
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
            ptr_actor = Member::Get_Actor(ptr_alias);
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

        qsort(vec_race_names.data(), vec_race_names.size(), sizeof(BSFixedString), Compare_Race_Names);

        return vec_race_names;
    }

    bool Has_Head(StaticFunctionTag *, VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head) {
        return Aliases::Has_Head(aliases, base_with_head);
    }

    SInt32 Count_Heads(StaticFunctionTag *, VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head, bool do_print) {
        return Aliases::Count_Heads(aliases, base_with_head, do_print);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, SInt32, SInt32>(
                "Aliases_Slice",
                "doticu_npcp",
                Slice,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, BSFixedString>(
                "Aliases_Sort",
                "doticu_npcp",
                Sort,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, VMArray<BSFixedString>, VMArray<SInt32>>(
                "Aliases_Filter",
                "doticu_npcp",
                Filter,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, UInt32, UInt32, BSFixedString, BSFixedString>(
                "Aliases_Filter_Flag",
                "doticu_npcp",
                Filter_Flag,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BSFixedString>, VMArray<BGSBaseAlias *>>(
                "Aliases_Get_Race_Names",
                "doticu_npcp",
                Get_Race_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, bool, VMArray<BGSBaseAlias *>, TESNPC *>(
                "Aliases_Has_Head",
                "doticu_npcp",
                Exports::Has_Head,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, SInt32, VMArray<BGSBaseAlias *>, TESNPC *, bool>(
                "Aliases_Count_Heads",
                "doticu_npcp",
                Exports::Count_Heads,
                registry)
        );

        return true;
    }

}}}


