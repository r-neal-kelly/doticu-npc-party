#pragma once

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "papyrus.h"

namespace doticu_npcp { namespace Party {

    using namespace Papyrus;

    typedef Quest_t             Aliases_t;
    typedef Aliases_t           Members_t;
    typedef Aliases_t           Followers_t;
    typedef Aliases_t           Horses_t;

    typedef Alias_Reference_t   Alias_t;
    typedef Alias_t             Member_t;
    typedef Alias_t             Follower_t;
    typedef Alias_t             Horse_t;

    template <typename Type>
    struct Range_t {
        Type begin;
        Type end;
    };
}}
