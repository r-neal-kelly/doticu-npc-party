/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "papyrus.inl"

#include "party/party_greeter.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    void Greeter_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Greeter_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
