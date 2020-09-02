/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_members.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_members.h"
#include "mcm/mcm_filter.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Filter_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_filter");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Filter_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Filter_t* Filter_t::Self()
    {
        return static_cast<Filter_t*>(Consts::Control_Quest());
    }

    Object_t* Filter_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Filter_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Filter_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Filter_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }

    Variable_t* Filter_t::Run_Filter_Option_Variable() { DEFINE_VARIABLE("p_option_filter"); }

    Variable_t* Filter_t::Sex_Option_Variable() { DEFINE_VARIABLE("p_option_sex"); }
    Variable_t* Filter_t::Sex_Argument_Variable() { DEFINE_VARIABLE("p_str_arg_sex"); }
    Variable_t* Filter_t::Sex_Display_Variable() { DEFINE_VARIABLE("p_str_view_sex"); }

    Variable_t* Filter_t::Race_Option_Variable() { DEFINE_VARIABLE("p_option_race"); }
    Variable_t* Filter_t::Race_Argument_Variable() { DEFINE_VARIABLE("p_str_arg_race"); }
    Variable_t* Filter_t::Race_Display_Variable() { DEFINE_VARIABLE("p_str_view_race"); }

    Variable_t* Filter_t::Search_Option_Variable() { DEFINE_VARIABLE("p_option_search"); }
    Variable_t* Filter_t::Search_Argument_Variable() { DEFINE_VARIABLE("p_str_arg_search"); }

    Variable_t* Filter_t::Style_Option_Variable() { DEFINE_VARIABLE("p_option_style"); }
    Variable_t* Filter_t::Style_Argument_Variable() { DEFINE_VARIABLE("p_int_arg_style"); }
    Variable_t* Filter_t::Style_Display_Variable() { DEFINE_VARIABLE("p_str_view_style"); }

    Variable_t* Filter_t::Vitality_Option_Variable() { DEFINE_VARIABLE("p_option_vitality"); }
    Variable_t* Filter_t::Vitality_Argument_Variable() { DEFINE_VARIABLE("p_int_arg_vitality"); }
    Variable_t* Filter_t::Vitality_Display_Variable() { DEFINE_VARIABLE("p_str_view_vitality"); }

    Variable_t* Filter_t::Outfit2_Option_Variable() { DEFINE_VARIABLE("p_option_outfit2"); }
    Variable_t* Filter_t::Outfit2_Argument_Variable() { DEFINE_VARIABLE("p_int_arg_outfit2"); }
    Variable_t* Filter_t::Outfit2_Display_Variable() { DEFINE_VARIABLE("p_str_view_outfit2"); }

    Variable_t* Filter_t::Rating_Option_Variable() { DEFINE_VARIABLE("p_option_rating"); }
    Variable_t* Filter_t::Rating_Argument_Variable() { DEFINE_VARIABLE("p_int_arg_rating"); }
    Variable_t* Filter_t::Rating_Display_Variable() { DEFINE_VARIABLE("p_str_view_rating"); }

    Variable_t* Filter_t::Relationship_Rank_Option_Variable() { DEFINE_VARIABLE("p_option_relationship"); }
    Variable_t* Filter_t::Relationship_Rank_Argument_Variable() { DEFINE_VARIABLE("p_int_arg_relationship"); }
    Variable_t* Filter_t::Relationship_Rank_Display_Variable() { DEFINE_VARIABLE("p_str_view_relationship"); }

    Variable_t* Filter_t::Is_Alive_Option_Variable() { DEFINE_VARIABLE("p_option_is_alive"); }
    Variable_t* Filter_t::Is_Dead_Option_Variable() { DEFINE_VARIABLE("p_option_is_dead"); }
    Variable_t* Filter_t::Alive_Dead_Ternary_Variable() { DEFINE_VARIABLE("p_int_alive_dead"); }

    Variable_t* Filter_t::Is_Original_Option_Variable() { DEFINE_VARIABLE("p_option_is_original"); }
    Variable_t* Filter_t::Is_Clone_Option_Variable() { DEFINE_VARIABLE("p_option_is_clone"); }
    Variable_t* Filter_t::Original_Clone_Ternary_Variable() { DEFINE_VARIABLE("p_int_original_clone"); }

    Variable_t* Filter_t::Is_Unique_Option_Variable() { DEFINE_VARIABLE("p_option_is_unique"); }
    Variable_t* Filter_t::Is_Generic_Option_Variable() { DEFINE_VARIABLE("p_option_is_generic"); }
    Variable_t* Filter_t::Unique_Generic_Ternary_Variable() { DEFINE_VARIABLE("p_int_unique_generic"); }

    Variable_t* Filter_t::Is_Mobile_Option_Variable() { DEFINE_VARIABLE("p_option_is_mobile"); }
    Variable_t* Filter_t::Is_Immobile_Option_Variable() { DEFINE_VARIABLE("p_option_is_immobile"); }
    Variable_t* Filter_t::Mobile_Immobile_Ternary_Variable() { DEFINE_VARIABLE("p_int_mobile_immobile"); }

    Variable_t* Filter_t::Is_Settler_Option_Variable() { DEFINE_VARIABLE("p_option_is_settler"); }
    Variable_t* Filter_t::Is_Non_Settler_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_settler"); }
    Variable_t* Filter_t::Settler_Ternary_Variable() { DEFINE_VARIABLE("p_int_settler"); }

    Variable_t* Filter_t::Is_Thrall_Option_Variable() { DEFINE_VARIABLE("p_option_is_thrall"); }
    Variable_t* Filter_t::Is_Non_Thrall_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_thrall"); }
    Variable_t* Filter_t::Thrall_Ternary_Variable() { DEFINE_VARIABLE("p_int_thrall"); }

    Variable_t* Filter_t::Is_Paralyzed_Option_Variable() { DEFINE_VARIABLE("p_option_is_paralyzed"); }
    Variable_t* Filter_t::Is_Non_Paralyzed_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_paralyzed"); }
    Variable_t* Filter_t::Paralyzed_Ternary_Variable() { DEFINE_VARIABLE("p_int_paralyzed"); }

    Variable_t* Filter_t::Is_Mannequin_Option_Variable() { DEFINE_VARIABLE("p_option_is_mannequin"); }
    Variable_t* Filter_t::Is_Non_Mannequin_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_mannequin"); }
    Variable_t* Filter_t::Mannequin_Ternary_Variable() { DEFINE_VARIABLE("p_int_mannequin"); }

    Variable_t* Filter_t::Is_Reanimated_Option_Variable() { DEFINE_VARIABLE("p_option_is_reanimated"); }
    Variable_t* Filter_t::Is_Non_Reanimated_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_reanimated"); }
    Variable_t* Filter_t::Reanimated_Ternary_Variable() { DEFINE_VARIABLE("p_int_reanimated"); }

    Variable_t* Filter_t::Is_Follower_Option_Variable() { DEFINE_VARIABLE("p_option_is_follower"); }
    Variable_t* Filter_t::Is_Non_Follower_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_follower"); }
    Variable_t* Filter_t::Follower_Ternary_Variable() { DEFINE_VARIABLE("p_int_follower"); }

    Variable_t* Filter_t::Is_Sneak_Option_Variable() { DEFINE_VARIABLE("p_option_is_sneak"); }
    Variable_t* Filter_t::Is_Non_Sneak_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_sneak"); }
    Variable_t* Filter_t::Sneak_Ternary_Variable() { DEFINE_VARIABLE("p_int_sneak"); }

    Variable_t* Filter_t::Is_Saddler_Option_Variable() { DEFINE_VARIABLE("p_option_is_saddler"); }
    Variable_t* Filter_t::Is_Non_Saddler_Option_Variable() { DEFINE_VARIABLE("p_option_isnt_saddler"); }
    Variable_t* Filter_t::Saddler_Ternary_Variable() { DEFINE_VARIABLE("p_int_saddler"); }

    Variable_t* Filter_t::Flags_1_Variable()
    {
        static const String_t variable_name = String_t("p_int_arg_flags");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Int_t Filter_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Filter_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    void Filter_t::Review_Filter()
    {
        Current_View(CODES::VIEW::FILTER);
    }

    Vector_t<String_t> Filter_t::Strings()
    {
        Vector_t<String_t> strings;
        strings.reserve(3);
        strings.push_back(Sex_Argument_Variable()->String());
        strings.push_back(Race_Argument_Variable()->String());
        strings.push_back(Search_Argument_Variable()->String());
        return strings;
    }

    Vector_t<Int_t> Filter_t::Ints()
    {
        Vector_t<Int_t> ints;
        ints.reserve(5);
        ints.push_back(Style_Argument_Variable()->Int());
        ints.push_back(Vitality_Argument_Variable()->Int());
        ints.push_back(Outfit2_Argument_Variable()->Int());
        ints.push_back(Rating_Argument_Variable()->Int());
        ints.push_back(Relationship_Rank_Argument_Variable()->Int());
        return ints;
    }

    Int_t Filter_t::Flags_1()
    {
        Int_t flags = 0;

        Int_t alive_dead_ternary = Alive_Dead_Ternary_Variable()->Int();
        if (alive_dead_ternary > 0) {
            flags |= 1 << Flags_1::IS_ALIVE;
        } else if (alive_dead_ternary < 0) {
            flags |= 1 << Flags_1::IS_DEAD;
        }

        Int_t original_clone_ternary = Original_Clone_Ternary_Variable()->Int();
        if (original_clone_ternary > 0) {
            flags |= 1 << Flags_1::IS_ORIGINAL;
        } else if (original_clone_ternary < 0) {
            flags |= 1 << Flags_1::IS_CLONE;
        }

        Int_t unique_generic_ternary = Unique_Generic_Ternary_Variable()->Int();
        if (unique_generic_ternary > 0) {
            flags |= 1 << Flags_1::IS_UNIQUE;
        } else if (unique_generic_ternary < 0) {
            flags |= 1 << Flags_1::IS_GENERIC;
        }

        Int_t mobile_immobile_ternary = Mobile_Immobile_Ternary_Variable()->Int();
        if (mobile_immobile_ternary > 0) {
            flags |= 1 << Flags_1::IS_MOBILE;
        } else if (mobile_immobile_ternary < 0) {
            flags |= 1 << Flags_1::IS_IMMOBILE;
        }

        Int_t settler_ternary = Settler_Ternary_Variable()->Int();
        if (settler_ternary > 0) {
            flags |= 1 << Flags_1::IS_SETTLER;
        } else if (settler_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_SETTLER;
        }

        Int_t thrall_ternary = Thrall_Ternary_Variable()->Int();
        if (thrall_ternary > 0) {
            flags |= 1 << Flags_1::IS_THRALL;
        } else if (thrall_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_THRALL;
        }

        Int_t paralyzed_ternary = Paralyzed_Ternary_Variable()->Int();
        if (paralyzed_ternary > 0) {
            flags |= 1 << Flags_1::IS_PARALYZED;
        } else if (paralyzed_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_PARALYZED;
        }

        Int_t mannequin_ternary = Mannequin_Ternary_Variable()->Int();
        if (mannequin_ternary > 0) {
            flags |= 1 << Flags_1::IS_MANNEQUIN;
        } else if (mannequin_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_MANNEQUIN;
        }

        Int_t reanimated_ternary = Reanimated_Ternary_Variable()->Int();
        if (reanimated_ternary > 0) {
            flags |= 1 << Flags_1::IS_REANIMATED;
        } else if (reanimated_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_REANIMATED;
        }

        Int_t follower_ternary = Follower_Ternary_Variable()->Int();
        if (follower_ternary > 0) {
            flags |= 1 << Flags_1::IS_FOLLOWER;
        } else if (follower_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_FOLLOWER;
        }

        Int_t sneak_ternary = Sneak_Ternary_Variable()->Int();
        if (sneak_ternary > 0) {
            flags |= 1 << Flags_1::IS_SNEAK;
        } else if (sneak_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_SNEAK;
        }

        Int_t saddler_ternary = Saddler_Ternary_Variable()->Int();
        if (saddler_ternary > 0) {
            flags |= 1 << Flags_1::IS_SADDLER;
        } else if (saddler_ternary < 0) {
            flags |= 1 << Flags_1::ISNT_SADDLER;
        }
        
        return flags;
    }

    Int_t Filter_t::Flags_2()
    {
        return 0;
    }

    String_t Filter_t::Filter_String()
    {
        std::string params = "";

        auto Concat = [&](std::string param)->void
        {
            if (params == "") {
                params = param;
            } else {
                params += ", " + param;
            }
        };

        String_t sex_arg = Sex_Argument_Variable()->String();
        if (sex_arg && sex_arg.data && sex_arg.data[0]) {
            Concat(Sex_Display_Variable()->String().data);
        }

        String_t race_arg = Race_Argument_Variable()->String();
        if (race_arg && race_arg.data && race_arg.data[0]) {
            Concat(Race_Display_Variable()->String().data);
        }

        Int_t style_arg = Style_Argument_Variable()->Int();
        if (style_arg < 0) {
            Concat(Style_Display_Variable()->String().data);
        }

        Int_t vitality_arg = Vitality_Argument_Variable()->Int();
        if (vitality_arg < 0) {
            Concat(Vitality_Display_Variable()->String().data);
        }

        Int_t outfit2_arg = Outfit2_Argument_Variable()->Int();
        if (outfit2_arg < 0) {
            Concat(Outfit2_Display_Variable()->String().data + std::string(" Outfit"));
        }

        Int_t rating_arg = Rating_Argument_Variable()->Int();
        if (rating_arg > -1) {
            Concat(Rating_Display_Variable()->String().data);
        }

        Int_t relationship_rank_arg = Relationship_Rank_Argument_Variable()->Int();
        if (relationship_rank_arg > -1) {
            Concat(Relationship_Rank_Display_Variable()->String().data);
        }

        String_t search_arg = Search_Argument_Variable()->String();
        if (search_arg && search_arg.data && search_arg.data[0]) {
            Concat(std::string("'") + search_arg.data + "'");
        }

        Int_t alive_dead_ternary = Alive_Dead_Ternary_Variable()->Int();
        if (alive_dead_ternary > 0) {
            Concat("Alive");
        } else if (alive_dead_ternary < 0) {
            Concat("Dead");
        }

        Int_t original_clone_ternary = Original_Clone_Ternary_Variable()->Int();
        if (original_clone_ternary > 0) {
            Concat("Original");
        } else if (original_clone_ternary < 0) {
            Concat("Clone");
        }

        Int_t unique_generic_ternary = Unique_Generic_Ternary_Variable()->Int();
        if (unique_generic_ternary > 0) {
            Concat("Unique");
        } else if (unique_generic_ternary < 0) {
            Concat("Generic");
        }

        Int_t mobile_immobile_ternary = Mobile_Immobile_Ternary_Variable()->Int();
        if (mobile_immobile_ternary > 0) {
            Concat("Mobile");
        } else if (mobile_immobile_ternary < 0) {
            Concat("Immobile");
        }

        Int_t settler_ternary = Settler_Ternary_Variable()->Int();
        if (settler_ternary > 0) {
            Concat("Settler");
        } else if (settler_ternary < 0) {
            Concat("!Settler");
        }

        Int_t thrall_ternary = Thrall_Ternary_Variable()->Int();
        if (thrall_ternary > 0) {
            Concat("Thrall");
        } else if (thrall_ternary < 0) {
            Concat("!Thrall");
        }

        Int_t paralyzed_ternary = Paralyzed_Ternary_Variable()->Int();
        if (paralyzed_ternary > 0) {
            Concat("Paralyzed");
        } else if (paralyzed_ternary < 0) {
            Concat("!Paralyzed");
        }

        Int_t mannequin_ternary = Mannequin_Ternary_Variable()->Int();
        if (mannequin_ternary > 0) {
            Concat("Mannequin");
        } else if (mannequin_ternary < 0) {
            Concat("!Mannequin");
        }

        Int_t reanimated_ternary = Reanimated_Ternary_Variable()->Int();
        if (reanimated_ternary > 0) {
            Concat("Reanimated");
        } else if (reanimated_ternary < 0) {
            Concat("!Reanimated");
        }

        Int_t follower_ternary = Follower_Ternary_Variable()->Int();
        if (follower_ternary > 0) {
            Concat("Follower");
        } else if (follower_ternary < 0) {
            Concat("!Follower");
        }

        Int_t sneak_ternary = Sneak_Ternary_Variable()->Int();
        if (sneak_ternary > 0) {
            Concat("Sneak");
        } else if (sneak_ternary < 0) {
            Concat("!Sneak");
        }

        Int_t saddler_ternary = Saddler_Ternary_Variable()->Int();
        if (saddler_ternary > 0) {
            Concat("Saddler");
        } else if (saddler_ternary < 0) {
            Concat("!Saddler");
        }

        if (params == "") {
            params = " All Members ";
        }

        return params.c_str();
    }

    void Filter_t::Goto_Filter_Members()
    {
        MCM::Members_t* mcm_members = MCM::Members_t::Self();
        Vector_t<String_t> strings = Strings();
        Vector_t<Int_t> ints = Ints();
        mcm_members->View_Filter_Members(
            Party::Members_t::Self()->Filter(&strings, &ints, Flags_1(), Flags_2())
        );
        mcm_members->Build_Page();
    }

    void Filter_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Filter_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("Goto_Filter_Members", 0, void, Goto_Filter_Members);

        #undef METHOD
    }

}}}
