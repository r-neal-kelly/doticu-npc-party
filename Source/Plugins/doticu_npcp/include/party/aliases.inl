/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party.h"
#include "string2.h"

namespace doticu_npcp { namespace Party {

    template <typename Alias>
    Range_t<Alias**> Aliases_t::Aliases(UInt64 begin, UInt64 end)
    {
        if (aliases.count >= begin && aliases.count >= end) {
            return {
                reinterpret_cast<Alias**>(aliases.entries + begin),
                reinterpret_cast<Alias**>(aliases.entries + end)
            };
        } else {
            return {
                reinterpret_cast<Alias**>(aliases.entries),
                reinterpret_cast<Alias**>(aliases.entries)
            };
        }
    }

    template <typename Alias>
    Alias* Aliases_t::From_ID(Int_t unique_id)
    {
        if (unique_id > -1 && unique_id < aliases.count) {
            return reinterpret_cast<Alias*>(aliases.entries[unique_id]);
        } else {
            return nullptr;
        }
    }

    template <typename Alias>
    Alias* Aliases_t::From_Actor(Actor_t* actor)
    {
        if (actor) {
            XAliases_t* xaliases = static_cast<XAliases_t*>(actor->extraData.GetByType(kExtraData_AliasInstanceArray));
            if (xaliases) {
                for (u64 idx = 0, size = xaliases->aliases.count; idx < size; idx += 1) {
                    XAliases_t::AliasInfo* info = xaliases->aliases[idx];
                    if (info && info->quest == this) {
                        return reinterpret_cast<Alias*>(info->alias);
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

    template <typename Alias>
    Alias* Aliases_t::From_Unfilled(Range_t<Alias**> aliases)
    {
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if (alias->Is_Unfilled()) {
                return alias;
            }
        }
        return nullptr;
    }

    template <typename Alias>
    Int_t Aliases_t::Count_If(Range_t<Alias**> aliases, Bool_t(Alias::* Is)())
    {
        Int_t count = 0;
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if ((alias->*Is)()) {
                count += 1;
            }
        }
        return count;
    }

    template <typename Alias>
    Int_t Aliases_t::Count_If(Range_t<Alias**> aliases, Bool_t(Alias::* Is)(), Bool_t(Alias::* Is_Also)())
    {
        Int_t count = 0;
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if ((alias->*Is)() && (alias->*Is_Also)()) {
                count += 1;
            }
        }
        return count;
    }

    template <typename Alias>
    Vector_t<Alias*> Aliases_t::Copy_If(Range_t<Alias**> aliases, Bool_t(Alias::* Is)(), size_t reserve)
    {
        Vector_t<Alias*> copy;
        copy.reserve(reserve);

        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if ((alias->*Is)()) {
                copy.push_back(alias);
            }
        }
        return copy;
    }

    template <typename Alias>
    Vector_t<Alias*> Aliases_t::Copy_If(Range_t<Alias**> aliases, Bool_t(Alias::* Is)(), Bool_t(Alias::* Is_Also)(), size_t reserve)
    {
        Vector_t<Alias*> copy;
        copy.reserve(reserve);

        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if ((alias->*Is)() && (alias->*Is_Also)()) {
                copy.push_back(alias);
            }
        }
        return copy;
    }

    template <typename Alias>
    inline Vector_t<Alias*> Aliases_t::Sort(Vector_t<Alias*> aliases, String_t algorithm)
    {
        if (String2::Is_Same_Caseless(algorithm, "NAME")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Names<Alias>);
        } else if (String2::Is_Same_Caseless(algorithm, "NAME_CASELESS")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Names_Caseless<Alias>);
        } else if (String2::Is_Same_Caseless(algorithm, "RATING_NAME")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Ratings_Names<Alias>);
        } else if (String2::Is_Same_Caseless(algorithm, "RATING_NAME_CASELESS")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Ratings_Names_Caseless<Alias>);
        }

        return aliases;
    }

    template <typename Alias>
    inline int Aliases_t::Compare_Names(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = alias_a->Actor();
        Actor_t* actor_b = alias_b->Actor();
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        String_t name_a = alias_a->Reference_Name();
        String_t name_b = alias_b->Reference_Name();

        return strcmp(name_a, name_b);
    }

    template <typename Alias>
    inline int Aliases_t::Compare_Names_Caseless(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = alias_a->Actor();
        Actor_t* actor_b = alias_b->Actor();
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        String_t name_a = alias_a->Reference_Name();
        String_t name_b = alias_b->Reference_Name();

        return _stricmp(name_a, name_b);
    }

    template <typename Alias>
    inline int Aliases_t::Compare_Ratings_Names(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = alias_a->Actor();
        Actor_t* actor_b = alias_b->Actor();
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        Int_t rating_a = alias_a->Rating();
        Int_t rating_b = alias_b->Rating();
        if (rating_a != rating_b) {
            return rating_b - rating_a;
        } else {
            String_t name_a = alias_a->Reference_Name();
            String_t name_b = alias_b->Reference_Name();

            return strcmp(name_a, name_b);
        }
    }

    template <typename Alias>
    inline int Aliases_t::Compare_Ratings_Names_Caseless(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = alias_a->Actor();
        Actor_t* actor_b = alias_b->Actor();
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        Int_t rating_a = alias_a->Rating();
        Int_t rating_b = alias_b->Rating();
        if (rating_a != rating_b) {
            return rating_b - rating_a;
        } else {
            String_t name_a = alias_a->Reference_Name();
            String_t name_b = alias_b->Reference_Name();

            return _stricmp(name_a, name_b);
        }
    }

    template <typename Alias>
    Vector_t<Alias*> Aliases_t::Slice(Vector_t<Alias*> aliases, Int_t begin, Int_t end)
    {
        return Papyrus::Slice_Vector(aliases, begin, end);
    }

    template <typename Alias>
    Bool_t Aliases_t::Has_Head(Range_t<Alias**> aliases, Actor_t* actor)
    {
        if (actor) {
            for (; aliases.begin < aliases.end; aliases.begin += 1) {
                if ((*aliases.begin)->Has_Same_Head(actor)) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    template <typename Alias>
    Int_t Aliases_t::Count_Heads(Range_t<Alias**> aliases, Actor_t* actor)
    {
        if (actor) {
            Int_t count = 0;
            for (; aliases.begin < aliases.end; aliases.begin += 1) {
                if ((*aliases.begin)->Has_Same_Head(actor)) {
                    count += 1;
                }
            }
            return count;
        } else {
            return 0;
        }
    }

    template <typename Alias>
    inline Vector_t<Alias*> Aliases_t::Filter(Range_t<Alias**> aliases,
                                              Vector_t<String_t>* strings,
                                              Vector_t<Int_t>* ints,
                                              Int_t flags_1,
                                              Int_t flags_2)
    {
        Vector_t<Alias*> buffer_a;
        Vector_t<Alias*> buffer_b;
        UInt64 max = aliases.end - aliases.begin;
        buffer_a.reserve(max);
        buffer_b.reserve(max / 2);

        Vector_t<Alias*>* read = &buffer_a;
        Vector_t<Alias*>* write = &buffer_b;
        Vector_t<Alias*>* temp = nullptr;
        auto Swap = [&read, &write, &temp]() -> void
        {
            temp = read;
            read = write;
            write = temp;
            write->clear();
        };

        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if (alias && alias->Is_Filled()) {
                read->push_back(alias);
            }
        }

        if (strings != nullptr) {
            size_t strings_size = strings->size();
            String_t sex = strings_size > 0 ? strings->at(0) : ""; // "male", "female", "none", or "" for any
            String_t race = strings_size > 1 ? strings->at(1) : ""; // exposed by game, "" for any
            String_t search = strings_size > 2 ? strings->at(2) : ""; // user input, "" for no search

            if (!String2::Is_Same_Caseless(sex, "")) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (String2::Is_Same_Caseless(alias->Sex(), sex)) {
                        write->push_back(alias);
                    }
                }
                Swap();
            }

            if (!String2::Is_Same_Caseless(race, "")) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (String2::Is_Same_Caseless(alias->Race(), race)) {
                        write->push_back(alias);
                    }
                }
                Swap();
            }

            if (!String2::Is_Same_Caseless(search, "")) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (strlen(search) > 1) {
                        if (String2::Contains_Caseless(alias->Reference_Name(), search)) {
                            write->push_back(alias);
                        }
                    } else {
                        if (String2::Starts_With_Caseless(alias->Reference_Name(), search)) {
                            write->push_back(alias);
                        }
                    }
                }
                Swap();
            }
        }

        if (ints != nullptr) {
            size_t ints_size = ints ? ints->size() : 0;
            Int_t style = ints_size > 0 ? ints->at(0) : 0; // exposed by doticu_npcp_codes, 0+ for any
            Int_t vitality = ints_size > 1 ? ints->at(1) : 0; // exposed by doticu_npcp_codes, 0+ for any
            Int_t outfit2 = ints_size > 2 ? ints->at(2) : 0; // exposed by doticu_npcp_codes, 0+ for any
            Int_t rating = ints_size > 3 ? ints->at(3) : -1; // exposed by doticu_npcp_member, -1 or less for any, 0 is no rating

            if (style < 0) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (alias->Style() == style) {
                        write->push_back(alias);
                    }
                }
                Swap();
            }

            if (vitality < 0) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (alias->Vitality() == vitality) {
                        write->push_back(alias);
                    }
                }
                Swap();
            }

            if (outfit2 < 0) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (alias->Outfit2() == outfit2) {
                        write->push_back(alias);
                    }
                }
                Swap();
            }

            if (rating > -1) {
                for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                    Alias* alias = read->at(idx);
                    if (alias->Rating() == rating) {
                        write->push_back(alias);
                    }
                }
                Swap();
            }
        }

        auto Filter_If = [&Swap, &read, &write](Bool_t(Alias::* is_func)()) -> void
        {
            for (size_t idx = 0, size = read->size(); idx < size; idx += 1) {
                Alias* alias = read->at(idx);
                if ((alias->*is_func)()) {
                    write->push_back(alias);
                }
            }
            Swap();
        };

        if (flags_1 > 0) {
            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_LOADED)) {
                Filter_If(&Alias::Is_Loaded);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_UNLOADED)) {
                Filter_If(&Alias::Is_Unloaded);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_UNIQUE)) {
                Filter_If(&Alias::Is_Unique);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_GENERIC)) {
                Filter_If(&Alias::Is_Generic);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_ALIVE)) {
                Filter_If(&Alias::Is_Alive);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_DEAD)) {
                Filter_If(&Alias::Is_Dead);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_ORIGINAL)) {
                Filter_If(&Alias::Is_Original);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_CLONE)) {
                Filter_If(&Alias::Is_Clone);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_MOBILE)) {
                Filter_If(&Alias::Is_Mobile);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_IMMOBILE)) {
                Filter_If(&Alias::Is_Immobile);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_SETTLER)) {
                Filter_If(&Alias::Is_Settler);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_SETTLER)) {
                Filter_If(&Alias::Isnt_Settler);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_THRALL)) {
                Filter_If(&Alias::Is_Thrall);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_THRALL)) {
                Filter_If(&Alias::Isnt_Thrall);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_PARALYZED)) {
                Filter_If(&Alias::Is_Paralyzed);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_PARALYZED)) {
                Filter_If(&Alias::Isnt_Paralyzed);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_MANNEQUIN)) {
                Filter_If(&Alias::Is_Mannequin);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_MANNEQUIN)) {
                Filter_If(&Alias::Isnt_Mannequin);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_REANIMATED)) {
                Filter_If(&Alias::Is_Reanimated);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_REANIMATED)) {
                Filter_If(&Alias::Isnt_Reanimated);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_FOLLOWER)) {
                Filter_If(&Alias::Is_Follower);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_FOLLOWER)) {
                Filter_If(&Alias::Isnt_Follower);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_SNEAK)) {
                Filter_If(&Alias::Is_Sneak);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_SNEAK)) {
                Filter_If(&Alias::Isnt_Sneak);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_SADDLER)) {
                Filter_If(&Alias::Is_Saddler);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_SADDLER)) {
                Filter_If(&Alias::Isnt_Saddler);
            }

            if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::IS_RETREATER)) {
                Filter_If(&Alias::Is_Retreater);
            } else if (Utils::Is_Bit_On(flags_1, Filter_Flags_1::ISNT_RETREATER)) {
                Filter_If(&Alias::Isnt_Retreater);
            }
        }

        if (flags_2 > 0) {

        }

        return *read;
    }

}}
