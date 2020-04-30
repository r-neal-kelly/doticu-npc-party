/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "aliases.h"

namespace doticu_npcp {

    VMResultArray<BGSBaseAlias *> Aliases_Slice(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr, UInt32 idx_from, UInt32 idx_to_ex) {
        VMResultArray<BGSBaseAlias *> vec_slice;
        UInt32 len_forms = arr.Length();

        if (idx_from < 0) {
            idx_from = 0;
        }
        if (idx_from > len_forms) {
            idx_from = len_forms;
        }
        if (idx_to_ex > len_forms || idx_to_ex < 0) {
            idx_to_ex = len_forms;
        }

        s64 num_elems = idx_to_ex - idx_from;
        if (num_elems < 1) {
            vec_slice.push_back(NULL); // may want to send back empty vec
        } else {
            BGSBaseAlias *ptr_elem;
            vec_slice.reserve(num_elems);
            for (u64 idx = idx_from, idx_end = idx_to_ex; idx < idx_end; idx += 1) {
                arr.Get(&ptr_elem, idx);
                vec_slice.push_back(ptr_elem);
            }
        }

        return vec_slice;
    }

    VMResultArray<BGSBaseAlias *> Aliases_Sort(StaticFunctionTag *,
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
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Aliases_Sort_Compare_Name);
        } else if (_stricmp(str_algorithm.data, "NAME_CASELESS") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Aliases_Sort_Compare_Name_Caseless);
        } else if (_stricmp(str_algorithm.data, "RATING_NAME") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Aliases_Sort_Compare_Rating_Name);
        } else if (_stricmp(str_algorithm.data, "RATING_NAME_CASELESS") == 0) {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Aliases_Sort_Compare_Rating_Name_Caseless);
        } else {
            qsort(&arr_return[0], num_aliases, sizeof(BGSBaseAlias *), Aliases_Sort_Compare_Name);
        }

        return arr_return;
    }
    int Aliases_Sort_Compare_Name(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *ptr_alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *ptr_alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!ptr_alias_a || !ptr_alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return ptr_alias_b - ptr_alias_a;
        }

        BSFixedString str_actor_a = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_a), GetReferenceName)();
        BSFixedString str_actor_b = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_b), GetReferenceName)();

        return strcmp(str_actor_a.data, str_actor_b.data);
    }
    int Aliases_Sort_Compare_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *ptr_alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *ptr_alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!ptr_alias_a || !ptr_alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return ptr_alias_b - ptr_alias_a;
        }

        BSFixedString str_actor_a = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_a), GetReferenceName)();
        BSFixedString str_actor_b = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_b), GetReferenceName)();

        return _stricmp(str_actor_a.data, str_actor_b.data);
    }
    int Aliases_Sort_Compare_Rating_Name(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *ptr_alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *ptr_alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!ptr_alias_a || !ptr_alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return ptr_alias_b - ptr_alias_a;
        }

        SInt32 int_rating_a = Alias_Get_Rating(ptr_alias_a);
        SInt32 int_rating_b = Alias_Get_Rating(ptr_alias_b);
        if (int_rating_a != int_rating_b) {
            return int_rating_b - int_rating_a;
        } else {
            BSFixedString str_actor_a = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_a), GetReferenceName)();
            BSFixedString str_actor_b = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_b), GetReferenceName)();

            return strcmp(str_actor_a.data, str_actor_b.data);
        }
    }
    int Aliases_Sort_Compare_Rating_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b) {
        BGSBaseAlias *ptr_alias_a = *(BGSBaseAlias **)ptr_item_a;
        BGSBaseAlias *ptr_alias_b = *(BGSBaseAlias **)ptr_item_b;
        if (!ptr_alias_a || !ptr_alias_b) {
            // if just one is NULL, then the non-NULL will be put ahead
            return ptr_alias_b - ptr_alias_a;
        }

        SInt32 int_rating_a = Alias_Get_Rating(ptr_alias_a);
        SInt32 int_rating_b = Alias_Get_Rating(ptr_alias_b);
        if (int_rating_a != int_rating_b) {
            return int_rating_b - int_rating_a;
        } else {
            BSFixedString str_actor_a = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_a), GetReferenceName)();
            BSFixedString str_actor_b = CALL_MEMBER_FN(Alias_Get_Actor(ptr_alias_b), GetReferenceName)();

            return _stricmp(str_actor_a.data, str_actor_b.data);
        }
    }

    VMResultArray<BGSBaseAlias *> Aliases_Filter(StaticFunctionTag *,
                                                 VMArray<BGSBaseAlias *> arr_aliases,
                                                 BSFixedString str_sex, // "male", "female", "none"
                                                 BSFixedString str_race,
                                                 BSFixedString str_search,
                                                 UInt32 int_flags
    ) {
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
                ptr_ref_actor = Alias_Get_Actor(ptr_base_alias);
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
                ptr_ref_actor = Alias_Get_Actor(ptr_base_alias);
                if (ptr_ref_actor) {
                    if (_stricmp(ptr_ref_actor->race->fullName.name.data, str_race.data) == 0) {
                        ptr_vec_write->push_back(ptr_base_alias);
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // SEARCH
        if (str_search && str_search.data[0] != 0) {
            BSFixedString str_name;
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Alias_Get_Actor(ptr_base_alias);
                if (ptr_ref_actor) {
                    str_name = CALL_MEMBER_FN(ptr_ref_actor, GetReferenceName)();
                    if (strlen(str_search.data) > 1) {
                        if (String_Contains_Caseless(str_name.data, str_search.data)) {
                            ptr_vec_write->push_back(ptr_base_alias);
                        }
                    } else {
                        if (String_Starts_With_Caseless(str_name.data, str_search.data)) {
                            ptr_vec_write->push_back(ptr_base_alias);
                        }
                    }
                }
            }
            SWAP_BUFFERS;
        }

        // ALIVE/DEAD
        if (Bit_Is_Set(int_flags, IS_ALIVE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Alias_Get_Actor(ptr_base_alias);
                if (!ptr_ref_actor->IsDead(1)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, IS_DEAD)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                ptr_ref_actor = Alias_Get_Actor(ptr_base_alias);
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
                if (Alias_Is_Original(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, IS_CLONE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Clone(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // FOLLOWER
        if (Bit_Is_Set(int_flags, IS_FOLLOWER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Follower(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_FOLLOWER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Follower(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // SETTLER
        if (Bit_Is_Set(int_flags, IS_SETTLER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Settler(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_SETTLER)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Settler(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // IMMOBILE
        if (Bit_Is_Set(int_flags, IS_IMMOBILE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Immobile(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_IMMOBILE)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Immobile(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // THRALL
        if (Bit_Is_Set(int_flags, IS_THRALL)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Thrall(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_THRALL)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Thrall(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // PARALYZED
        if (Bit_Is_Set(int_flags, IS_PARALYZED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Paralyzed(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_PARALYZED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Paralyzed(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // MANNEQUIN
        if (Bit_Is_Set(int_flags, IS_MANNEQUIN)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Mannequin(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_MANNEQUIN)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Mannequin(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        // REANIMATED
        if (Bit_Is_Set(int_flags, IS_REANIMATED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (Alias_Is_Reanimated(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }
        if (Bit_Is_Set(int_flags, ISNT_REANIMATED)) {
            for (u64 idx = 0, size = ptr_vec_read->size(); idx < size; idx += 1) {
                ptr_base_alias = ptr_vec_read->at(idx);
                if (!Alias_Is_Reanimated(ptr_base_alias)) {
                    ptr_vec_write->push_back(ptr_base_alias);
                }
            }
            SWAP_BUFFERS;
        }

        return *ptr_vec_read;

        #undef SWAP_BUFFERS
    }
    bool String_Starts_With_Caseless(const char *str_a, const char *str_b) {
        char char_a;
        char char_b;
        for (u64 idx = 0; str_b[idx] != 0; idx += 1) {
            char_a = tolower(str_a[idx]);
            char_b = tolower(str_b[idx]);
            if (char_a == 0 || char_a != char_b) {
                return false;
            }
        }

        return true;
    }
    bool String_Contains_Caseless(const char *str_a, const char *str_b) {
        for (u64 idx = 0; str_a[idx] != 0; idx += 1) {
            if (String_Starts_With_Caseless(str_a + idx, str_b)) {
                return true;
            }
        }

        return false;
    }
    UInt32 Aliases_Filter_Flag(StaticFunctionTag *, UInt32 int_flags, BSFixedString str_command, BSFixedString str_flag) {
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

    VMResultArray<BSFixedString> Aliases_Get_Race_Names(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases) {
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
            ptr_actor = Alias_Get_Actor(ptr_alias);
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

        qsort(vec_race_names.data(), vec_race_names.size(), sizeof(BSFixedString), Aliases_Get_Race_Names_Compare);

        return vec_race_names;
    }
    int Aliases_Get_Race_Names_Compare(const void *ptr_item_a, const void *ptr_item_b) {
        return _stricmp((const char *)*(BSFixedString **)ptr_item_a, (const char *)*(BSFixedString **)ptr_item_b);
    }

    VMResultArray<BSFixedString> Aliases_Get_Initial_Letters(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases) {
        BGSBaseAlias *ptr_alias;
        Actor *ptr_actor;
        BSFixedString str_actor_name;
        
        std::vector<char> vec_letters;
        char letter;
        bool has_letter;

        for (u64 idx_aliases = 0, num_aliases = arr_aliases.Length(); idx_aliases < num_aliases; idx_aliases += 1) {
            arr_aliases.Get(&ptr_alias, idx_aliases);

            ptr_actor = Alias_Get_Actor(ptr_alias);
            if (ptr_actor) {
                str_actor_name = CALL_MEMBER_FN(ptr_actor, GetReferenceName)();
                letter = str_actor_name.data[0];

                has_letter = false;
                for (u64 idx_letters = 0, num_letters = vec_letters.size(); idx_letters < num_letters; idx_letters += 1) {
                    if (vec_letters[idx_letters] == letter) {
                        has_letter = true;
                        break;
                    }
                }

                if (!has_letter) {
                    vec_letters.push_back(letter);
                }
            }
        }

        qsort(vec_letters.data(), vec_letters.size(), sizeof(char), Aliases_Get_Initial_Letters_Compare);

        VMResultArray<BSFixedString> vec_initial_letters;
        BSFixedString str_initial_letter;
        vec_initial_letters.reserve(vec_letters.size());
        char str[2] = { 0, 0 };

        for (u64 idx_letters = 0, num_letters = vec_letters.size(); idx_letters < num_letters; idx_letters += 1) {
            str[0] = vec_letters[idx_letters];
            vec_initial_letters.push_back(BSFixedString(str));
        }

        return vec_initial_letters;
    }
    int Aliases_Get_Initial_Letters_Compare(const void *ptr_item_a, const void *ptr_item_b) {
        return *(char *)ptr_item_a - *(char *)ptr_item_b;
    }

    VMResultArray<BGSBaseAlias *> Aliases_Get_Used(StaticFunctionTag *, TESQuest *ref_quest) {
        VMResultArray<BGSBaseAlias *> vec_aliases;
        if (ref_quest == NULL) {
            return vec_aliases;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        vec_aliases.reserve(ptr_aliases->count);

        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (Alias_Is_Created(ptr_alias) && Alias_Get_Actor(ptr_alias)) {
                vec_aliases.push_back(ptr_alias);
            }
        }

        while (vec_aliases.size() < ptr_aliases->count) {
            vec_aliases.push_back(NULL);
        }

        return vec_aliases;
    }

    VMResultArray<SInt32> Aliases_Get_Free_IDs(StaticFunctionTag *, TESQuest *ref_quest) {
        VMResultArray<SInt32> vec_free;
        if (ref_quest == NULL) {
            return vec_free;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        vec_free.reserve(ptr_aliases->count);

        BGSBaseAlias *ptr_alias;
        for (s64 idx = ptr_aliases->count - 1; idx >= 0; idx -= 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (!Alias_Is_Created(ptr_alias) || !Alias_Get_Actor(ptr_alias)) {
                vec_free.push_back(ptr_alias->aliasId);
            }
        }

        while (vec_free.size() < ptr_aliases->count) {
            vec_free.push_back(-1);
        }

        return vec_free;
    }

    UInt32 Aliases_Get_Used_Count(StaticFunctionTag *, TESQuest *ref_quest) {
        UInt32 count = 0;
        if (ref_quest == NULL) {
            return count;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (Alias_Is_Created(ptr_alias) && Alias_Get_Actor(ptr_alias)) {
                count += 1;
            }
        }

        return count;
    }

    UInt32 Aliases_Get_Free_Count(StaticFunctionTag *, TESQuest *ref_quest) {
        UInt32 count = 0;
        if (ref_quest == NULL) {
            return count;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (!Alias_Is_Created(ptr_alias) || !Alias_Get_Actor(ptr_alias)) {
                count += 1;
            }
        }

        return count;
    }

    UInt32 Aliases_Count_Mannequins(StaticFunctionTag *, TESQuest *ref_quest) {
        UInt32 count = 0;
        if (ref_quest == NULL) {
            return count;
        }

        tArray<BGSBaseAlias *> *ptr_aliases = &ref_quest->aliases;
        BGSBaseAlias *ptr_alias;
        for (u64 idx = 0; idx < ptr_aliases->count; idx += 1) {
            ptr_aliases->GetNthItem(idx, ptr_alias);

            if (Alias_Is_Created(ptr_alias) && Alias_Is_Mannequin(ptr_alias)) {
                count += 1;
            }
        }

        return count;
    }

}
