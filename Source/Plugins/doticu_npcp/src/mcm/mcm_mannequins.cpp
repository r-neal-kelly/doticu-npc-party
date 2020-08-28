/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_mannequins.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Mannequins_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_mannequins");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Mannequins_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Mannequins_t* Mannequins_t::Self()
    {
        return static_cast<Mannequins_t*>(Consts::Control_Quest());
    }

    Object_t* Mannequins_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Mannequins_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Mannequins_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Mannequins_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }

    Int_t Mannequins_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Mannequins_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    void Mannequins_t::Review_Mannequins()
    {
        Current_View(CODES::VIEW::MANNEQUINS_CELL);
    }

    void Mannequins_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Mannequins_t,          \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
