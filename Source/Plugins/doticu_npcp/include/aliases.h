/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party.h"

namespace doticu_npcp { namespace Party { namespace Aliases {

    Range_t<Alias_t**> Aliases(Aliases_t* self, UInt64 begin, UInt64 end);

    Alias_t* From_ID(Aliases_t* self, Int_t unique_id);
    Alias_t* From_Actor(Aliases_t* self, Actor_t* actor);

    template <typename Alias>
    Int_t Count_If(Range_t<Alias**> aliases, Bool_t(*Is)(Alias*));

    template <typename Alias>
    Int_t Count_If(Range_t<Alias**> aliases, Bool_t(*Is_Filled)(Alias*), Bool_t(*Is_Also)(Alias*));

    template <typename Alias>
    Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases, Bool_t(*Is)(Alias*), size_t reserve);

    template <typename Alias>
    Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases, Bool_t(*Is_Filled)(Alias*), Bool_t(*Is_Also)(Alias*), size_t reserve);

    template <typename Alias, Actor_t* (*Actor)(Alias*), Int_t(*Rating)(Alias*)>
    inline Vector_t<Alias*> Sort(Vector_t<Alias*> aliases, String_t algorithm);

    template <typename Alias, Actor_t* (*Actor)(Alias*)>
    inline int Compare_Names(const void* item_a, const void* item_b);

    template <typename Alias, Actor_t* (*Actor)(Alias*)>
    inline int Compare_Names_Caseless(const void* item_a, const void* item_b);

    template <typename Alias, Actor_t* (*Actor)(Alias*), Int_t(*Rating)(Alias*)>
    inline int Compare_Ratings_Names(const void* item_a, const void* item_b);

    template <typename Alias, Actor_t* (*Actor)(Alias*), Int_t(*Rating)(Alias*)>
    inline int Compare_Ratings_Names_Caseless(const void* item_a, const void* item_b);

    template <typename Alias>
    Vector_t<Alias*> Slice(Vector_t<Alias*> aliases, Int_t begin, Int_t end);

    template <typename Alias>
    Bool_t Has_Head(Range_t<Alias**> aliases, Actor_t* actor, Bool_t(*Has_Same_Head)(Alias*, Actor_t*));

    template <typename Alias>
    Int_t Count_Heads(Range_t<Alias**> aliases, Actor_t* actor, Bool_t(*Has_Same_Head)(Alias*, Actor_t*));

}}}

#include "actor_base2.h"
#include "string2.h"

namespace doticu_npcp { namespace Party { namespace Aliases {

    template <typename Alias>
    Int_t Count_If(Range_t<Alias**> aliases, Bool_t(*Is)(Alias*))
    {
        Int_t count = 0;
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if (Is(alias)) {
                count += 1;
            }
        }
        return count;
    }

    template <typename Alias>
    Int_t Count_If(Range_t<Alias**> aliases, Bool_t(*Is_Filled)(Alias*), Bool_t(*Is_Also)(Alias*))
    {
        Int_t count = 0;
        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if (Is_Filled(alias) && Is_Also(alias)) {
                count += 1;
            }
        }
        return count;
    }

    template <typename Alias>
    Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases, Bool_t(*Is)(Alias*), size_t reserve)
    {
        Vector_t<Alias*> copy;
        copy.reserve(reserve);

        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if (Is(alias)) {
                copy.push_back(alias);
            }
        }
        return copy;
    }

    template <typename Alias>
    Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases, Bool_t(*Is_Filled)(Alias*), Bool_t(*Is_Also)(Alias*), size_t reserve)
    {
        Vector_t<Alias*> copy;
        copy.reserve(reserve);

        for (; aliases.begin < aliases.end; aliases.begin += 1) {
            Alias* alias = *aliases.begin;
            if (Is_Filled(alias) && Is_Also(alias)) {
                copy.push_back(alias);
            }
        }
        return copy;
    }

    template <typename Alias, Actor_t* (*Actor)(Alias*), Int_t(*Rating)(Alias*)>
    inline Vector_t<Alias*> Sort(Vector_t<Alias*> aliases, String_t algorithm)
    {
        if (String2::Is_Same_Caseless(algorithm, "NAME")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Names<Alias, Actor>);
        } else if (String2::Is_Same_Caseless(algorithm, "NAME_CASELESS")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Names_Caseless<Alias, Actor>);
        } else if (String2::Is_Same_Caseless(algorithm, "RATING_NAME")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Ratings_Names<Alias, Actor, Rating>);
        } else if (String2::Is_Same_Caseless(algorithm, "RATING_NAME_CASELESS")) {
            qsort(aliases.data(), aliases.size(), sizeof(Alias*), Compare_Ratings_Names_Caseless<Alias, Actor, Rating>);
        }

        return aliases;
    }

    template <typename Alias, Actor_t* (*Actor)(Alias*)>
    inline int Compare_Names(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = Actor(alias_a);
        Actor_t* actor_b = Actor(alias_b);
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        String_t name_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
        String_t name_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

        return strcmp(name_a, name_b);
    }

    template <typename Alias, Actor_t* (*Actor)(Alias*)>
    inline int Compare_Names_Caseless(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = Actor(alias_a);
        Actor_t* actor_b = Actor(alias_b);
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        String_t name_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
        String_t name_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

        return _stricmp(name_a, name_b);
    }

    template <typename Alias, Actor_t* (*Actor)(Alias*), Int_t(*Rating)(Alias*)>
    inline int Compare_Ratings_Names(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = Actor(alias_a);
        Actor_t* actor_b = Actor(alias_b);
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        Int_t rating_a = Rating(alias_a);
        Int_t rating_b = Rating(alias_b);
        if (rating_a != rating_b) {
            return rating_b - rating_a;
        } else {
            String_t name_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
            String_t name_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

            return strcmp(name_a, name_b);
        }
    }

    template <typename Alias, Actor_t* (*Actor)(Alias*), Int_t(*Rating)(Alias*)>
    inline int Compare_Ratings_Names_Caseless(const void* item_a, const void* item_b)
    {
        Alias* alias_a = *(Alias**)item_a;
        Alias* alias_b = *(Alias**)item_b;
        if (!alias_a || !alias_b) {
            return alias_b - alias_a; // puts nullptr after
        }

        Actor_t* actor_a = Actor(alias_a);
        Actor_t* actor_b = Actor(alias_b);
        if (!actor_a || !actor_b) {
            return actor_b - actor_a; // puts nullptr after
        }

        Int_t rating_a = Rating(alias_a);
        Int_t rating_b = Rating(alias_b);
        if (rating_a != rating_b) {
            return rating_b - rating_a;
        } else {
            String_t name_a = CALL_MEMBER_FN(actor_a, GetReferenceName)();
            String_t name_b = CALL_MEMBER_FN(actor_b, GetReferenceName)();

            return _stricmp(name_a, name_b);
        }
    }

    template <typename Alias>
    Vector_t<Alias*> Slice(Vector_t<Alias*> aliases, Int_t begin, Int_t end)
    {

    }

    template <typename Alias>
    Bool_t Has_Head(Range_t<Alias**> aliases, Actor_t* actor, Bool_t(*Has_Same_Head)(Alias*, Actor_t*))
    {
        if (actor && Has_Same_Head) {
            for (; aliases.begin < aliases.end; aliases.begin += 1) {
                Alias* alias = *aliases.begin;
                if (Has_Same_Head(alias, actor)) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    template <typename Alias>
    Int_t Count_Heads(Range_t<Alias**> aliases, Actor_t* actor, Bool_t(*Has_Same_Head)(Alias*, Actor_t*))
    {
        if (actor && Has_Same_Head) {
            Int_t count = 0;
            for (; aliases.begin < aliases.end; aliases.begin += 1) {
                Alias* alias = *aliases.begin;
                if (Has_Same_Head(alias, actor)) {
                    count += 1;
                }
            }
            return count;
        } else {
            return 0;
        }
    }

}}}













































#include "types.h"

namespace doticu_npcp { namespace Aliases {

    enum Filter_Flags {
        IS_ALIVE, IS_DEAD,
        IS_ORIGINAL, IS_CLONE,
        IS_UNIQUE, IS_GENERIC,
        IS_FOLLOWER, ISNT_FOLLOWER,
        IS_SETTLER, ISNT_SETTLER,
        IS_IMMOBILE, ISNT_IMMOBILE,
        IS_THRALL, ISNT_THRALL,
        IS_SNEAK, ISNT_SNEAK,
        IS_PARALYZED, ISNT_PARALYZED,
        IS_MANNEQUIN, ISNT_MANNEQUIN,
        IS_REANIMATED, ISNT_REANIMATED
    };

    int Compare_Name(const void *ptr_item_a, const void *ptr_item_b);
    int Compare_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b);
    int Compare_Rating_Name(const void *ptr_item_a, const void *ptr_item_b);
    int Compare_Rating_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b);

    VMResultArray<Alias_t *> Sort(VMResultArray<Alias_t *> aliases, const char *algorithm);

}}

namespace doticu_npcp { namespace Aliases { namespace Exports {

    VMResultArray<BGSBaseAlias *> Slice(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr, SInt32 idx_from, SInt32 idx_to_ex);
    VMResultArray<BGSBaseAlias *> Sort(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, BSFixedString str_algorithm);
    VMResultArray<BGSBaseAlias *> Filter(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, VMArray<BSFixedString> arr_strings, VMArray<SInt32> arr_ints);
    UInt32 Filter_Flag(StaticFunctionTag *, UInt32 int_flags, BSFixedString str_command, BSFixedString str_flag);

    bool Register(VMClassRegistry *registry);

}}}
