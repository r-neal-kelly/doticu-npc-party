/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Members {

    void Enforce_Loaded(Members_t *members);

    VMResultArray<Member_t *> Get_Loaded(Members_t *members);

}}

namespace doticu_npcp { namespace Members { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
