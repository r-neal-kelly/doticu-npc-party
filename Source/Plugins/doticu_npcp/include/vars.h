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

    Bool_t Do_Force_Clone_Unique();
    Bool_t Do_Force_Clone_Generic();
    Bool_t Do_Force_Unclone_Unique();
    Bool_t Do_Force_Unclone_Generic();
    Bool_t Do_Fill_Outfit2s();
    Bool_t Do_Auto_Outfit2s();
    Bool_t Do_Auto_Immobile_Outfit2();

    Int_t Member_Limit();
    Int_t Display_Count();
    Int_t Clone_Outfit();
    Int_t Default_Style();
    Int_t Default_Vitality();

    String_t Members_Sort_Algorithm();
    String_t Followers_Sort_Algorithm();

    void Log_Variables(Vars_t* self);
    void Log_Properties(Vars_t* self);

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry);

}}}
