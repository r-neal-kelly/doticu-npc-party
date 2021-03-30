/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party_member_rating.h"
#include "strings.h"

namespace doticu_npcp { namespace Party {

    Member_Rating_t::Member_Rating_t(Int_t rating) :
        Member_Rating_t(static_cast<u8>(rating))
    {
    }

    String_t Member_Rating_t::As_String() const
    {
        if (*this == 1)         return Strings_t::RATING_1_STARS;
        else if (*this == 2)    return Strings_t::RATING_2_STARS;
        else if (*this == 3)    return Strings_t::RATING_3_STARS;
        else if (*this == 4)    return Strings_t::RATING_4_STARS;
        else if (*this == 5)    return Strings_t::RATING_5_STARS;
        else                    return Strings_t::RATING_0_STARS;
    }

    Member_Rating_t::operator String_t() const
    {
        return As_String();
    }

}}
