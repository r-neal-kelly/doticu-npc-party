/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Vars {

    using namespace Papyrus;

    String_t Class_Name();
    Class_Info_t* Class_Info();
    Vars_t* Self();
    Object_t* Object();

    Variable_t* Variable(String_t variable_name);
    Variable_t* Property(String_t property_name);

    String_t String_Variable(String_t variable_name);

    Int_t Display_Count();

    void Log_Variables(Vars_t* self);
    void Log_Properties(Vars_t* self);

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry);

}}}
