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
        static some<Member_Suitcase_t*> Create();
        static void                     Destroy(some<Member_Suitcase_t*> suitcase);

    public:
        void    Copy_Items(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);
        void    Move_Items(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);
        void    Apply_Items(some<Reference_t*> unto, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);
        void    Remove_Items(maybe<Reference_t*> to, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables);
        void    Remove_All_Items(maybe<Reference_t*> to, Bool_t allow_unplayables);
    };

}}
