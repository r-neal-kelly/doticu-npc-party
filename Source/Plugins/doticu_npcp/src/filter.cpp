/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "filter.h"
#include "party.h"
#include "utils.h"

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

    Variable_t* Filter_t::Alive_Dead_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_alive_dead")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Original_Clone_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_original_clone")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Unique_Generic_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_unique_generic")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Mobile_Immobile_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_mobile_immobile")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Settler_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_settler")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Thrall_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_thrall")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Paralyzed_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_paralyzed")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Mannequin_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_mannequin")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Reanimated_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_reanimated")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Follower_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_follower")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Sneak_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_sneak")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Filter_t::Saddler_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_int_saddler")
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
        Int_t flags_1 = 0;

        Int_t alive_dead = Alive_Dead_Variable()->Int();
        if (alive_dead > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_ALIVE);
        } else if (alive_dead < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_DEAD);
        }

        Int_t original_clone = Original_Clone_Variable()->Int();
        if (original_clone > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_ORIGINAL);
        } else if (original_clone < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_CLONE);
        }

        Int_t unique_generic = Unique_Generic_Variable()->Int();
        if (unique_generic > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_UNIQUE);
        } else if (unique_generic < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_GENERIC);
        }

        Int_t mobile_immobile = Mobile_Immobile_Variable()->Int();
        if (mobile_immobile > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_MOBILE);
        } else if (mobile_immobile < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_IMMOBILE);
        }

        Int_t settler = Settler_Variable()->Int();
        if (settler > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_SETTLER);
        } else if (settler < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_SETTLER);
        }

        Int_t thrall = Thrall_Variable()->Int();
        if (thrall > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_THRALL);
        } else if (thrall < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_THRALL);
        }

        Int_t paralyzed = Paralyzed_Variable()->Int();
        if (paralyzed > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_PARALYZED);
        } else if (paralyzed < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_PARALYZED);
        }

        Int_t mannequin = Mannequin_Variable()->Int();
        if (mannequin > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_MANNEQUIN);
        } else if (mannequin < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_MANNEQUIN);
        }

        Int_t reanimated = Reanimated_Variable()->Int();
        if (reanimated > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_REANIMATED);
        } else if (reanimated < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_REANIMATED);
        }

        Int_t follower = Follower_Variable()->Int();
        if (follower > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_FOLLOWER);
        } else if (follower < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_FOLLOWER);
        }

        Int_t sneak = Sneak_Variable()->Int();
        if (sneak > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_SNEAK);
        } else if (sneak < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_SNEAK);
        }

        Int_t saddler = Saddler_Variable()->Int();
        if (saddler > 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::IS_SADDLER);
        } else if (saddler < 0) {
            flags_1 = Utils::Bit_On(flags_1, Party::Filter_Flags_1::ISNT_SADDLER);
        }

        Flags_1_Variable()->Int(flags_1);

        return flags_1;
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
