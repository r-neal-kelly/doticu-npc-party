/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Vars {

    Vars_t* Self();

    Papyrus::Variable_t* Variable(Vars_t* self, Papyrus::String_t variable_name);
    Papyrus::Variable_t* Property(Vars_t* self, Papyrus::String_t property_name);

    void Log_Variables(Vars_t* self);
    void Log_Properties(Vars_t* self);

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry);

}}}
