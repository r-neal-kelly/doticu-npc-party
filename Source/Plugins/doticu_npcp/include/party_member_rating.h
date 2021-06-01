/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

#include "intrinsic.h"
#include "strings.h"

namespace doticu_npcp { namespace Party {

    class Member_Rating_t_data :
        public Numeric_Data_t<u8>
    {
    public:
        static constexpr value_type _NONE_  = 0;
        static constexpr value_type _MAX_   = 5;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value > _NONE_ && value <= _MAX_;
        }
    };

    class Member_Rating_t :
        public Numeric_t<Member_Rating_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Member_Rating_t() = default;

        Member_Rating_t(Int_t rating) :
            Member_Rating_t(static_cast<value_type>(rating))
        {
        }

    public:
        String_t As_String() const
        {
            if (*this == 1)         return Strings_t::RATING_1_STARS;
            else if (*this == 2)    return Strings_t::RATING_2_STARS;
            else if (*this == 3)    return Strings_t::RATING_3_STARS;
            else if (*this == 4)    return Strings_t::RATING_4_STARS;
            else if (*this == 5)    return Strings_t::RATING_5_STARS;
            else                    return Strings_t::RATING_0_STARS;
        }

    public:
        operator String_t() const
        {
            return As_String();
        }
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Member_Rating_t> :
        public none_numeric<doticu_npcp::Party::Member_Rating_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<doticu_npcp::Party::Member_Rating_t> :
        public maybe_numeric<doticu_npcp::Party::Member_Rating_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<doticu_npcp::Party::Member_Rating_t> :
        public some_numeric<doticu_npcp::Party::Member_Rating_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
