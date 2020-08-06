/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64_common/Relocation.h"

#include "consts.h"
#include "game.h"
#include "papyrus.h"
#include "utils.h"
#include "vars.h"

#include "papyrus.inl"

using namespace doticu_npcp::Papyrus;

namespace doticu_npcp { namespace Vars {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_vars");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Vars_t* Self()
    {
        return static_cast<Vars_t*>(Consts::Vars_Quest());
    }

    Object_t* Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Property(String_t property_name)
    {
        Object_t* object = Object();
        if (object) {
            return object->Property(property_name);
        } else {
            return nullptr;
        }
    }

    #define VAR(TYPE_, NAME_)                                   \
    M                                                           \
        static const String_t variable_name = String_t(NAME_);  \
        NPCP_ASSERT(variable_name);                             \
        Variable_t* variable = Variable(variable_name);         \
        NPCP_ASSERT(variable);                                  \
        return variable->TYPE_();                               \
    W

    #define BOOL_VAR(NAME_) VAR(Bool, NAME_)

    Bool_t Do_Force_Clone_Unique() { BOOL_VAR("p_force_clone_unique"); }
    Bool_t Do_Force_Clone_Generic() { BOOL_VAR("p_force_clone_generic"); }
    Bool_t Do_Force_Unclone_Unique() { BOOL_VAR("p_force_unclone_unique"); }
    Bool_t Do_Force_Unclone_Generic() { BOOL_VAR("p_force_unclone_generic"); }
    Bool_t Do_Fill_Outfit2s() { BOOL_VAR("p_fill_outfits"); }

    #undef BOOL_VAR

    #define INT_VAR(NAME_) VAR(Int, NAME_)

    Int_t Member_Limit() { INT_VAR("p_max_members"); }
    Int_t Display_Count() { INT_VAR("p_num_display"); }
    Int_t Clone_Outfit() { INT_VAR("p_clone_outfit"); }

    #undef INT_VAR

    #define STRING_VAR(NAME_) VAR(String, NAME_)

    String_t Members_Sort_Algorithm() { STRING_VAR("p_str_sort_members"); }
    String_t Followers_Sort_Algorithm() { STRING_VAR("p_str_sort_followers"); }

    #undef STRING_VAR

    #undef VAR

    void Log_Variables(Vars_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->Log_Variables();
        }
    }

    void Log_Properties(Vars_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->info->Log_Property_Infos();
        }
    }

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_vars", Vars_t,                \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Vars::METHOD_, __VA_ARGS__);      \
        W

        ADD_METHOD("Log_Variables", 0, void, Log_Variables);
        ADD_METHOD("Log_Properties", 0, void, Log_Properties);

        #undef ADD_METHOD

        return true;
    }

}}}
