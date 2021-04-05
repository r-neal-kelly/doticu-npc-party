/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"
#include "doticu_skylib/numeric.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Settler_Duration_Minutes_t_data :
        public Numeric_Data_t<Int_t>
    {
    public:
        static constexpr value_type _NONE_  = -1;
        static constexpr value_type _MIN_   = 0;
        static constexpr value_type _MAX_   = 55;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value >= _MIN_ && value <= _MAX_;
        }
    };

    class Settler_Duration_Minutes_t :
        public Numeric_t<Settler_Duration_Minutes_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Settler_Duration_Minutes_t> :
        public none_numeric<doticu_npcp::Party::Settler_Duration_Minutes_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<doticu_npcp::Party::Settler_Duration_Minutes_t> :
        public maybe_numeric<doticu_npcp::Party::Settler_Duration_Minutes_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<doticu_npcp::Party::Settler_Duration_Minutes_t> :
        public some_numeric<doticu_npcp::Party::Settler_Duration_Minutes_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
