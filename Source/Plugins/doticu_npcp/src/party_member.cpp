/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party_member.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    Bool_t Member_t::Is_Valid()
    {
        return
            this->members &&
            this->members->Has_Member(this->member_id) &&
            this->members->Actor(this->member_id) == this->actor;
    }

}}
