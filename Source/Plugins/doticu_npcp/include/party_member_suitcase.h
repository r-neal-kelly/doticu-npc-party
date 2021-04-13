/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/reference.h"

#include "intrinsic.h"
#include "party_member_suit_type.h"

namespace doticu_npcp { namespace Party {

    class Member_Suitcase_t :
        public Reference_t
    {
    public:
        class Suit_Entry_t
        {
        public:
            some<Bound_Object_t*>           bound_object;
            Vector_t<some<Extra_List_t*>>   copies;

        public:
            Suit_Entry_t(some<Bound_Object_t*> bound_object);
            Suit_Entry_t(some<Bound_Object_t*> bound_object, Vector_t<some<Extra_List_t*>> copies);
            Suit_Entry_t(const Suit_Entry_t& other) = delete;
            Suit_Entry_t(Suit_Entry_t&& other) noexcept;
            Suit_Entry_t& operator =(const Suit_Entry_t& other) = delete;
            Suit_Entry_t& operator =(Suit_Entry_t&& other) noexcept = delete;
            ~Suit_Entry_t();

        public:
            Bool_t  Has_Copies();
            Bool_t  Destroy_Copy_If_Equals(some<Extra_List_t*> extra_list);
        };

        class Suit_Entries_t
        {
        public:
            Vector_t<Suit_Entry_t> entries;

        public:
            Suit_Entries_t();
            Suit_Entries_t(Vector_t<Suit_Entry_t> entries);
            Suit_Entries_t(const Suit_Entries_t& other) = delete;
            Suit_Entries_t(Suit_Entries_t&& other) noexcept;
            Suit_Entries_t& operator =(const Suit_Entries_t& other) = delete;
            Suit_Entries_t& operator =(Suit_Entries_t&& other) noexcept = delete;
            ~Suit_Entries_t();

        public:
            Bool_t                  Has_Copies();

            size_t                  Count();

            maybe<Suit_Entry_t*>    Maybe_Entry(some<Bound_Object_t*> bound_object);
            some<Suit_Entry_t*>     Some_Entry(some<Bound_Object_t*> bound_object);
        };

    public:
        static some<Member_Suitcase_t*> Create();
        static void                     Destroy(some<Member_Suitcase_t*> suitcase);

    public:
        void    Copy_From(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);

        void    Move_From(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);
        void    Move_To(maybe<Reference_t*> to, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);
        void    Move_All_To(maybe<Reference_t*> to, Bool_t allow_unplayables);

    public:
        Suit_Entries_t  Active_Suit_Entries(some<Member_Suit_Type_e> suit_type,
                                            Bool_t allow_unplayables,
                                            maybe<Outfit_t*> outfit);

        void            Apply_Unto(some<Actor_t*> unto,
                                   some<Member_Suit_Type_e> suit_type,
                                   Bool_t allow_unplayables,
                                   Bool_t do_strict,
                                   maybe<Reference_t*> to);
    };

}}
