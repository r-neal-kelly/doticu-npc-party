/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/reference.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Pack_t :
        public Reference_t
    {
    public:
        static some<Member_Pack_t*> Create();
        static void                 Destroy(some<Member_Pack_t*> pack);

    public:
        void    Clear();
    };

}}
