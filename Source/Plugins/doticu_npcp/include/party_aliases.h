/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Aliases_t : public Quest_t {
    public:
        template <typename Alias>
        static int Compare_Names(const void* item_a,
                                 const void* item_b);
        template <typename Alias>
        static int Compare_Names_Caseless(const void* item_a,
                                          const void* item_b);
        template <typename Alias>
        static int Compare_Ratings_Names(const void* item_a,
                                         const void* item_b);
        template <typename Alias>
        static int Compare_Ratings_Names_Caseless(const void* item_a,
                                                  const void* item_b);

    public:
        template <typename Alias>
        Range_t<Alias**> Aliases(UInt64 begin, UInt64 end);

        template <typename Alias>
        Alias* From_ID(Int_t unique_id);
        template <typename Alias>
        Alias* From_Actor(Actor_t* actor);
        template <typename Alias>
        Alias* From_Unfilled(Range_t<Alias**> aliases);

        template <typename Alias>
        Int_t Count_If(Range_t<Alias**> aliases,
                       Bool_t(Alias::* Is)());
        template <typename Alias>
        Int_t Count_If(Range_t<Alias**> aliases,
                       Bool_t(Alias::* Is)(),
                       Bool_t(Alias::* Is_Also)());

        template <typename Alias>
        Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases,
                                 Bool_t(Alias::* Is)(),
                                 size_t reserve);
        template <typename Alias>
        Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases,
                                 Bool_t(Alias::* Is)(),
                                 Bool_t(Alias::* Is_Also)(),
                                 size_t reserve);

        template <typename Alias>
        inline Vector_t<Alias*> Sort(Vector_t<Alias*> aliases,
                                     String_t algorithm);

        template <typename Alias>
        Vector_t<Alias*> Slice(Vector_t<Alias*> aliases, Int_t begin, Int_t end);

        template <typename Alias>
        Bool_t Has_Base(Range_t<Alias**> aliases, Actor_t* actor_with_base);
        template <typename Alias>
        Bool_t Has_Head(Range_t<Alias**> aliases, Actor_t* actor);
        template <typename Alias>
        Int_t Count_Base(Range_t<Alias**> aliases, Actor_t* actor_with_base);
        template <typename Alias>
        Int_t Count_Heads(Range_t<Alias**> aliases, Actor_t* actor);

        Vector_t<String_t> Filter_Strings(String_t sex = "",
                                          String_t race = "",
                                          String_t search = "");
        Vector_t<Int_t> Filter_Ints(Int_t style = 0,
                                    Int_t vitality = 0,
                                    Int_t outfit2 = 0,
                                    Int_t rating = -1);
        Int_t Add_Filter_Flag_1(Int_t flags_1, String_t flag_1);
        Int_t Add_Filter_Flag_2(Int_t flags_2, String_t flag_2);
        template <typename Alias>
        Vector_t<Alias*> Filter(Range_t<Alias**> aliases,
                                Vector_t<String_t>* strings = nullptr,
                                Vector_t<Int_t>* ints = nullptr,
                                Int_t flags_1 = 0,
                                Int_t flags_2 = 0);
    };

}}}
