/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "party_member_id.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_ID_t :
        public Member_ID_t
    {
    public:
        using Member_ID_t::Member_ID_t;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Settler_ID_t> :
        public none_numeric<doticu_npcp::Settler_ID_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<doticu_npcp::Settler_ID_t> :
        public maybe_numeric<doticu_npcp::Settler_ID_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<doticu_npcp::Settler_ID_t> :
        public some_numeric<doticu_npcp::Settler_ID_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
