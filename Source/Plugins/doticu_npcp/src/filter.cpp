/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "filter.h"

namespace doticu_npcp { namespace Papyrus {

    String_t Filter_t::Class_Name()
    {
        static const String_t class_name = Utils::Assert(
            String_t("doticu_npcp_mcm_filter")
        );
        return class_name;
    }

    Class_Info_t* Filter_t::Class_Info()
    {
        static Class_Info_t* class_info = Utils::Assert(
            Class_Info_t::Fetch(Class_Name())
        );
        return class_info;
    }

    Filter_t* Filter_t::Self()
    {
        return static_cast<Filter_t*>(Consts::Control_Quest());
    }

    Object_t* Filter_t::Object()
    {
        Object_t* object = Utils::Assert(
            Object_t::Fetch(Self(), Class_Name())
        );
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Filter_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Filter_t::Sex_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_str_arg_sex")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Race_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_str_arg_race")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Search_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_str_arg_search")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Style_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_arg_style")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Vitality_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_arg_vitality")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Outfit2_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_arg_outfit2")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Rating_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_arg_rating")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Flags_1_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_arg_flags")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Vector_t<String_t> Filter_t::Strings()
    {
        Vector_t<String_t> strings;
        strings.reserve(3);
        strings.push_back(Sex_Variable()->String());
        strings.push_back(Race_Variable()->String());
        strings.push_back(Search_Variable()->String());
        return strings;
    }

    Vector_t<Int_t> Filter_t::Ints()
    {
        Vector_t<Int_t> ints;
        ints.reserve(4);
        ints.push_back(Style_Variable()->Int());
        ints.push_back(Vitality_Variable()->Int());
        ints.push_back(Outfit2_Variable()->Int());
        ints.push_back(Rating_Variable()->Int());
        return ints;
    }

    Int_t Filter_t::Flags_1()
    {
        return Flags_1_Variable()->Int();
    }

    Int_t Filter_t::Flags_2()
    {
        return 0;
    }

}}

namespace doticu_npcp { namespace Filter { namespace Exports {

    bool Register(VMClassRegistry* registry)
    {
        return true;
    }

}}}
