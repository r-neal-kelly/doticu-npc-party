/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party.h"
#include "party.inl"

namespace doticu_npcp { namespace Party {



}}

#define FORWARD_POINTER(METHOD_) { return self ? self->METHOD_ : nullptr; }
#define FORWARD_BOOL(METHOD_) { return self ? self->METHOD_ : false; }
#define FORWARD_INT(METHOD_) { return self ? self->METHOD_ : 0; }
#define FORWARD_STRING(METHOD_) { return self ? self->METHOD_ : ""; }
#define FORWARD_VECTOR(METHOD_, TYPE_) { return self ? self->METHOD_ : Vector_t<TYPE_>(); }
#define FORWARD_VOID(METHOD_) { self ? self->METHOD_, 1 : 0; }

namespace doticu_npcp { namespace Party { namespace NPCS { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        return true;
    }

}}}}

#undef FORWARD_POINTER
#undef FORWARD_BOOL
#undef FORWARD_INT
#undef FORWARD_STRING
#undef FORWARD_VECTOR
#undef FORWARD_VOID
