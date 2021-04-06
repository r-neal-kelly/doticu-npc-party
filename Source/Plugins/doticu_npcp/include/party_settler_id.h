/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"
#include "doticu_skylib/numeric.h"

#include "intrinsic.h"
#include "party_main.h"
#include "party_member_id.h"

namespace doticu_npcp { namespace Party {

    class Settler_ID_t_data :
        public Numeric_Data_t<size_t>
    {
    public:
        static constexpr value_type _NONE_  = ~0;
        static constexpr value_type _MIN_   = 0;
        static constexpr value_type _MAX_   = Main_t::MAX_SETTLERS - 1;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value >= _MIN_ && value <= _MAX_;
        }
    };

    class Settler_ID_t :
        public Numeric_t<Settler_ID_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Settler_ID_t() = default;

        Settler_ID_t(Member_ID_t member_id) :
            Numeric_t(member_id())
        {
        }

    public:
        operator Member_ID_t() const
        {
            return this->value;
        }
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Settler_ID_t> :
        public none_numeric<doticu_npcp::Party::Settler_ID_t>
    {
    public:
        using none_numeric::none_numeric;

    public:
        operator none<doticu_npcp::Party::Member_ID_t>() const
        {
            return none<doticu_npcp::Party::Member_ID_t>();
        }
    };

    template <>
    class maybe<doticu_npcp::Party::Settler_ID_t> :
        public maybe_numeric<doticu_npcp::Party::Settler_ID_t>
    {
    public:
        using maybe_numeric::maybe_numeric;

    public:
        maybe() = default;

        maybe(doticu_npcp::Party::Member_ID_t member_id) :
            maybe_numeric(member_id())
        {
        }

    public:
        operator maybe<doticu_npcp::Party::Member_ID_t>() const
        {
            return this->value();
        }
    };

    template <>
    class some<doticu_npcp::Party::Settler_ID_t> :
        public some_numeric<doticu_npcp::Party::Settler_ID_t>
    {
    public:
        using some_numeric::some_numeric;

    public:
        some() = delete;

        some(doticu_npcp::Party::Member_ID_t member_id) :
            some_numeric(member_id())
        {
        }

    public:
        operator some<doticu_npcp::Party::Member_ID_t>() const
        {
            return this->value();
        }
    };

}
