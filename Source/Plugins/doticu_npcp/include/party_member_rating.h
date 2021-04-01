/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"
#include "doticu_skylib/numeric.h"

#include "intrinsic.h"

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
        Member_Rating_t(Int_t value);

    public:
        String_t As_String() const;

    public:
        operator String_t() const;
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
