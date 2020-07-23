/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace CODES {

    using namespace Papyrus;

    enum : Int_t {

        SUCCESS = 0,
        FAILURE,
        OUT_OF_BOUNDS,

        IS_DISPLAY,
        ISNT_DISPLAY,
        IS_MEMBER,
        ISNT_MEMBER,

        HAS_DISPLAY,
        HASNT_DISPLAY,
        HAS_MEMBER,
        HASNT_MEMBER,

    };

}}

namespace doticu_npcp { namespace CODES { namespace Exports {

    bool Register(Registry_t* registry);

}}}
