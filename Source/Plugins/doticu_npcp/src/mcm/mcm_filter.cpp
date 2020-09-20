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

    void Filter_t::On_Build_Page()
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t* mcm_members = MCM::Members_t::Self();
            Vector_t<String_t> strings = Strings();
            Vector_t<Int_t> ints = Ints();
            mcm_members->View_Filter_Members(
                Party::Members_t::Self()->Filter(&strings, &ints, Flags_1(), Flags_2())
            );
            mcm_members->On_Build_Page();
        } else {
            Main_t* mcm = Main();

            mcm->Title_Text(" Filter ");

            Run_Filter_Option_Variable()->Int(
                mcm->Add_Text_Option(" Run Filter ", "")
            );
            Search_Option_Variable()->Int(
                mcm->Add_Input_Option(" Search ", Search_Argument_Variable()->String())
            );

            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");

            Sex_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Sex ", Sex_Display_Variable()->String())
            );
            Race_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Race ", Race_Display_Variable()->String())
            );

            Style_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Style ", Style_Display_Variable()->String())
            );
            Vitality_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Vitality ", Vitality_Display_Variable()->String())
            );

            Outfit2_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Outfit ", Outfit2_Display_Variable()->String())
            );
            Rating_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Rating ", Rating_Display_Variable()->String())
            );

            Relationship_Rank_Option_Variable()->Int(
                mcm->Add_Menu_Option(" Relationship Rank ", Relationship_Rank_Display_Variable()->String())
            );
            mcm->Add_Empty_Option();

            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");

            Is_Alive_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Alive ", Alive_Dead_Ternary_Variable()->Int() > 0)
            );
            Is_Dead_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Dead ", Alive_Dead_Ternary_Variable()->Int() < 0)
            );

            Is_Original_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Original ", Original_Clone_Ternary_Variable()->Int() > 0)
            );
            Is_Clone_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Clone ", Original_Clone_Ternary_Variable()->Int() < 0)
            );

            Is_Unique_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Unique ", Unique_Generic_Ternary_Variable()->Int() > 0)
            );
            Is_Generic_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Generic ", Unique_Generic_Ternary_Variable()->Int() < 0)
            );

            Is_Mobile_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Mobile ", Mobile_Immobile_Ternary_Variable()->Int() > 0)
            );
            Is_Immobile_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Immobile ", Mobile_Immobile_Ternary_Variable()->Int() < 0)
            );

            Is_Settler_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Settler ", Settler_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Settler_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Settler ", Settler_Ternary_Variable()->Int() < 0)
            );

            Is_Thrall_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Thrall ", Thrall_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Thrall_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Thrall ", Thrall_Ternary_Variable()->Int() < 0)
            );

            Is_Paralyzed_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Paralyzed ", Paralyzed_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Paralyzed_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Paralyzed ", Paralyzed_Ternary_Variable()->Int() < 0)
            );

            Is_Mannequin_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Mannequin ", Mannequin_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Mannequin_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Mannequin ", Mannequin_Ternary_Variable()->Int() < 0)
            );

            Is_Reanimated_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Reanimated ", Reanimated_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Reanimated_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Reanimated ", Reanimated_Ternary_Variable()->Int() < 0)
            );

            Is_Follower_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Follower ", Follower_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Follower_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Follower ", Follower_Ternary_Variable()->Int() < 0)
            );

            Is_Sneak_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Sneak ", Sneak_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Sneak_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Sneak ", Sneak_Ternary_Variable()->Int() < 0)
            );

            Is_Saddler_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Is Saddler ", Saddler_Ternary_Variable()->Int() > 0)
            );
            Is_Non_Saddler_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Isnt Saddler ", Saddler_Ternary_Variable()->Int() < 0)
            );
        }
    }

    void Filter_t::On_Option_Select(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Select(option);
        } else {
            MCM::Main_t* mcm = Main();

            auto Toggle_Ternary = [&mcm](Variable_t* high_option_variable,
                                         Variable_t* low_option_variable,
                                         Variable_t* ternary_variable,
                                         Bool_t is_high)->void
            {
                if (is_high) {
                    if (ternary_variable->Int() < 1) {
                        ternary_variable->Int(1);
                    } else {
                        ternary_variable->Int(0);
                    }
                } else {
                    if (ternary_variable->Int() > -1) {
                        ternary_variable->Int(-1);
                    } else {
                        ternary_variable->Int(0);
                    }
                }
                mcm->Toggle_Option_Value(high_option_variable->Int(), ternary_variable->Int() > 0, false);
                mcm->Toggle_Option_Value(low_option_variable->Int(), ternary_variable->Int() < 0, true);
            };

            if (option == Run_Filter_Option_Variable()->Int()) {
                mcm->Option_Flags(option, MCM::DISABLE, true);
                Current_View(CODES::VIEW::FILTER_MEMBERS);
                mcm->Reset_Page();

            } else if (option == Is_Alive_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Alive_Option_Variable(), Is_Dead_Option_Variable(), Alive_Dead_Ternary_Variable(), true);
            } else if (option == Is_Dead_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Alive_Option_Variable(), Is_Dead_Option_Variable(), Alive_Dead_Ternary_Variable(), false);

            } else if (option == Is_Original_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Original_Option_Variable(), Is_Clone_Option_Variable(), Original_Clone_Ternary_Variable(), true);
            } else if (option == Is_Clone_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Original_Option_Variable(), Is_Clone_Option_Variable(), Original_Clone_Ternary_Variable(), false);

            } else if (option == Is_Unique_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Unique_Option_Variable(), Is_Generic_Option_Variable(), Unique_Generic_Ternary_Variable(), true);
            } else if (option == Is_Generic_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Unique_Option_Variable(), Is_Generic_Option_Variable(), Unique_Generic_Ternary_Variable(), false);

            } else if (option == Is_Mobile_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Mobile_Option_Variable(), Is_Immobile_Option_Variable(), Mobile_Immobile_Ternary_Variable(), true);
            } else if (option == Is_Immobile_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Mobile_Option_Variable(), Is_Immobile_Option_Variable(), Mobile_Immobile_Ternary_Variable(), false);

            } else if (option == Is_Settler_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Settler_Option_Variable(), Is_Non_Settler_Option_Variable(), Settler_Ternary_Variable(), true);
            } else if (option == Is_Non_Settler_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Settler_Option_Variable(), Is_Non_Settler_Option_Variable(), Settler_Ternary_Variable(), false);

            } else if (option == Is_Thrall_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Thrall_Option_Variable(), Is_Non_Thrall_Option_Variable(), Thrall_Ternary_Variable(), true);
            } else if (option == Is_Non_Thrall_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Thrall_Option_Variable(), Is_Non_Thrall_Option_Variable(), Thrall_Ternary_Variable(), false);

            } else if (option == Is_Paralyzed_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Paralyzed_Option_Variable(), Is_Non_Paralyzed_Option_Variable(), Paralyzed_Ternary_Variable(), true);
            } else if (option == Is_Non_Paralyzed_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Paralyzed_Option_Variable(), Is_Non_Paralyzed_Option_Variable(), Paralyzed_Ternary_Variable(), false);

            } else if (option == Is_Mannequin_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Mannequin_Option_Variable(), Is_Non_Mannequin_Option_Variable(), Mannequin_Ternary_Variable(), true);
            } else if (option == Is_Non_Mannequin_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Mannequin_Option_Variable(), Is_Non_Mannequin_Option_Variable(), Mannequin_Ternary_Variable(), false);

            } else if (option == Is_Reanimated_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Reanimated_Option_Variable(), Is_Non_Reanimated_Option_Variable(), Reanimated_Ternary_Variable(), true);
            } else if (option == Is_Non_Reanimated_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Reanimated_Option_Variable(), Is_Non_Reanimated_Option_Variable(), Reanimated_Ternary_Variable(), false);

            } else if (option == Is_Follower_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Follower_Option_Variable(), Is_Non_Follower_Option_Variable(), Follower_Ternary_Variable(), true);
            } else if (option == Is_Non_Follower_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Follower_Option_Variable(), Is_Non_Follower_Option_Variable(), Follower_Ternary_Variable(), false);

            } else if (option == Is_Sneak_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Sneak_Option_Variable(), Is_Non_Sneak_Option_Variable(), Sneak_Ternary_Variable(), true);
            } else if (option == Is_Non_Sneak_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Sneak_Option_Variable(), Is_Non_Sneak_Option_Variable(), Sneak_Ternary_Variable(), false);

            } else if (option == Is_Saddler_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Saddler_Option_Variable(), Is_Non_Saddler_Option_Variable(), Saddler_Ternary_Variable(), true);
            } else if (option == Is_Non_Saddler_Option_Variable()->Int()) {
                Toggle_Ternary(Is_Saddler_Option_Variable(), Is_Non_Saddler_Option_Variable(), Saddler_Ternary_Variable(), false);
            }
        }
    }

    void Filter_t::On_Option_Menu_Open(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Menu_Open(option);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Sex_Option_Variable()->Int()) {
                Vector_t<String_t> values;
                values.reserve(4);

                values.push_back(" Any ");
                values.push_back(" Male ");
                values.push_back(" Female ");
                values.push_back(" None ");

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);

            } else if (option == Race_Option_Variable()->Int()) {
                Vector_t<String_t> race_names = Party::Members_t::Self()->Race_Names();
                Vector_t<String_t> values;
                values.reserve(race_names.size() + 1);

                values.push_back(" Any ");
                for (size_t idx = 0, count = race_names.size(); idx < count; idx += 1) {
                    values.push_back(race_names[idx]);
                }

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);

            } else if (option == Style_Option_Variable()->Int()) {
                Vector_t<String_t> values;
                values.reserve(6);

                values.push_back(" Any ");
                values.push_back(" Default ");
                values.push_back(" Warrior ");
                values.push_back(" Mage ");
                values.push_back(" Archer ");
                values.push_back(" Coward ");

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);

            } else if (option == Vitality_Option_Variable()->Int()) {
                Vector_t<String_t> values;
                values.reserve(5);

                values.push_back(" Any ");
                values.push_back(" Mortal ");
                values.push_back(" Protected ");
                values.push_back(" Essential ");
                values.push_back(" Invulnerable ");

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);

            } else if (option == Outfit2_Option_Variable()->Int()) {
                Vector_t<String_t> values;
                values.reserve(8);

                values.push_back(" Any ");
                values.push_back(" Member ");
                values.push_back(" Settler ");
                values.push_back(" Thrall ");
                values.push_back(" Immobile ");
                values.push_back(" Follower ");
                values.push_back(" Vanilla ");
                values.push_back(" Default ");

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);

            } else if (option == Rating_Option_Variable()->Int()) {
                Vector_t<String_t> values;
                values.reserve(7);

                values.push_back(" Any ");
                values.push_back(" - ");
                values.push_back(" * ");
                values.push_back(" ** ");
                values.push_back(" *** ");
                values.push_back(" **** ");
                values.push_back(" ***** ");

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);

            } else if (option == Relationship_Rank_Option_Variable()->Int()) {
                Vector_t<String_t> values;
                values.reserve(10);

                values.push_back(" Any ");
                values.push_back(" Lover ");
                values.push_back(" Ally ");
                values.push_back(" Confidant ");
                values.push_back(" Friend ");
                values.push_back(" Acquaintance ");
                values.push_back(" Rival ");
                values.push_back(" Foe ");
                values.push_back(" Enemy ");
                values.push_back(" Archnemesis ");

                mcm->Menu_Dialog_Values(values);
                mcm->Menu_Dialog_Default(0);
            }
        }
    }

    void Filter_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Menu_Accept(option, idx);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Sex_Option_Variable()->Int()) {
                if (idx == 0) {
                    Sex_Argument_Variable()->String("");
                    Sex_Display_Variable()->String(" Any ");
                } else if (idx == 1) {
                    Sex_Argument_Variable()->String("Male");
                    Sex_Display_Variable()->String(" Male ");
                } else if (idx == 2) {
                    Sex_Argument_Variable()->String("Female");
                    Sex_Display_Variable()->String(" Female ");
                } else if (idx == 3) {
                    Sex_Argument_Variable()->String("None");
                    Sex_Display_Variable()->String(" None ");
                }
                mcm->Menu_Option_Value(option, Sex_Display_Variable()->String(), true);

            } else if (option == Race_Option_Variable()->Int()) {
                if (idx < 1) {
                    Race_Argument_Variable()->String("");
                    Race_Display_Variable()->String(" Any ");
                } else {
                    Vector_t<String_t> race_names = Party::Members_t::Self()->Race_Names();
                    if (idx - 1 < race_names.size()) {
                        String_t race_name = race_names[idx - 1];
                        Race_Argument_Variable()->String(race_name);
                        Race_Display_Variable()->String(race_name);
                    } else {
                        Race_Argument_Variable()->String("");
                        Race_Display_Variable()->String(" Any ");
                    }
                }
                mcm->Menu_Option_Value(option, Race_Display_Variable()->String(), true);

            } else if (option == Style_Option_Variable()->Int()) {
                if (idx == 0) {
                    Style_Argument_Variable()->Int(0);
                    Style_Display_Variable()->String(" Any ");
                } else if (idx == 1) {
                    Style_Argument_Variable()->Int(CODES::STYLE::DEFAULT);
                    Style_Display_Variable()->String(" Default ");
                } else if (idx == 2) {
                    Style_Argument_Variable()->Int(CODES::STYLE::WARRIOR);
                    Style_Display_Variable()->String(" Warrior ");
                } else if (idx == 3) {
                    Style_Argument_Variable()->Int(CODES::STYLE::MAGE);
                    Style_Display_Variable()->String(" Mage ");
                } else if (idx == 4) {
                    Style_Argument_Variable()->Int(CODES::STYLE::ARCHER);
                    Style_Display_Variable()->String(" Archer ");
                } else if (idx == 5) {
                    Style_Argument_Variable()->Int(CODES::STYLE::COWARD);
                    Style_Display_Variable()->String(" Coward ");
                }
                mcm->Menu_Option_Value(option, Style_Display_Variable()->String(), true);

            } else if (option == Vitality_Option_Variable()->Int()) {
                if (idx == 0) {
                    Vitality_Argument_Variable()->Int(0);
                    Vitality_Display_Variable()->String(" Any ");
                } else if (idx == 1) {
                    Vitality_Argument_Variable()->Int(CODES::VITALITY::MORTAL);
                    Vitality_Display_Variable()->String(" Mortal ");
                } else if (idx == 2) {
                    Vitality_Argument_Variable()->Int(CODES::VITALITY::PROTECTED);
                    Vitality_Display_Variable()->String(" Protected ");
                } else if (idx == 3) {
                    Vitality_Argument_Variable()->Int(CODES::VITALITY::ESSENTIAL);
                    Vitality_Display_Variable()->String(" Essential ");
                } else if (idx == 4) {
                    Vitality_Argument_Variable()->Int(CODES::VITALITY::INVULNERABLE);
                    Vitality_Display_Variable()->String(" Invulnerable ");
                }
                mcm->Menu_Option_Value(option, Vitality_Display_Variable()->String(), true);

            } else if (option == Outfit2_Option_Variable()->Int()) {
                if (idx == 0) {
                    Outfit2_Argument_Variable()->Int(0);
                    Outfit2_Display_Variable()->String(" Any ");
                } else if (idx == 1) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::MEMBER);
                    Outfit2_Display_Variable()->String(" Member ");
                } else if (idx == 2) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::SETTLER);
                    Outfit2_Display_Variable()->String(" Settler ");
                } else if (idx == 3) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::THRALL);
                    Outfit2_Display_Variable()->String(" Thrall ");
                } else if (idx == 4) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::IMMOBILE);
                    Outfit2_Display_Variable()->String(" Immobile ");
                } else if (idx == 5) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::FOLLOWER);
                    Outfit2_Display_Variable()->String(" Follower ");
                } else if (idx == 6) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::VANILLA);
                    Outfit2_Display_Variable()->String(" Vanilla ");
                } else if (idx == 7) {
                    Outfit2_Argument_Variable()->Int(CODES::OUTFIT2::DEFAULT);
                    Outfit2_Display_Variable()->String(" Default ");
                }
                mcm->Menu_Option_Value(option, Outfit2_Display_Variable()->String(), true);

            } else if (option == Rating_Option_Variable()->Int()) {
                if (idx == 0) {
                    Rating_Argument_Variable()->Int(-1);
                    Rating_Display_Variable()->String(" Any ");
                } else if (idx == 1) {
                    Rating_Argument_Variable()->Int(0);
                    Rating_Display_Variable()->String(" - ");
                } else if (idx == 2) {
                    Rating_Argument_Variable()->Int(1);
                    Rating_Display_Variable()->String(" * ");
                } else if (idx == 3) {
                    Rating_Argument_Variable()->Int(2);
                    Rating_Display_Variable()->String(" ** ");
                } else if (idx == 4) {
                    Rating_Argument_Variable()->Int(3);
                    Rating_Display_Variable()->String(" *** ");
                } else if (idx == 5) {
                    Rating_Argument_Variable()->Int(4);
                    Rating_Display_Variable()->String(" **** ");
                } else if (idx == 6) {
                    Rating_Argument_Variable()->Int(5);
                    Rating_Display_Variable()->String(" ***** ");
                }
                mcm->Menu_Option_Value(option, Rating_Display_Variable()->String(), true);

            } else if (option == Relationship_Rank_Option_Variable()->Int()) {
                if (idx == 0) {
                    Relationship_Rank_Argument_Variable()->Int(-1);
                    Relationship_Rank_Display_Variable()->String(" Any ");
                } else if (idx == 1) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::LOVER));
                    Relationship_Rank_Display_Variable()->String(" Lover ");
                } else if (idx == 2) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::ALLY));
                    Relationship_Rank_Display_Variable()->String(" Ally ");
                } else if (idx == 3) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::CONFIDANT));
                    Relationship_Rank_Display_Variable()->String(" Confidant ");
                } else if (idx == 4) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::FRIEND));
                    Relationship_Rank_Display_Variable()->String(" Friend ");
                } else if (idx == 5) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::ACQUAINTANCE));
                    Relationship_Rank_Display_Variable()->String(" Acquaintance ");
                } else if (idx == 6) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::RIVAL));
                    Relationship_Rank_Display_Variable()->String(" Rival ");
                } else if (idx == 7) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::FOE));
                    Relationship_Rank_Display_Variable()->String(" Foe ");
                } else if (idx == 8) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::ENEMY));
                    Relationship_Rank_Display_Variable()->String(" Enemy ");
                } else if (idx == 9) {
                    Relationship_Rank_Argument_Variable()->Int(static_cast<Int_t>(Relationship_t::Rank_e::ARCHNEMESIS));
                    Relationship_Rank_Display_Variable()->String(" Archnemesis ");
                }
                mcm->Menu_Option_Value(option, Relationship_Rank_Display_Variable()->String(), true);
            }
        }
    }

    void Filter_t::On_Option_Slider_Open(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Slider_Open(option);
        }
    }

    void Filter_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Slider_Accept(option, value);
        }
    }

    void Filter_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Input_Accept(option, value);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Search_Option_Variable()->Int()) {
                Search_Argument_Variable()->String(value);
                mcm->Input_Option_Value(option, value, true);
            }
        }
    }

    void Filter_t::On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        }
    }

    void Filter_t::On_Option_Default(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Default(option);
        }
    }

    void Filter_t::On_Option_Highlight(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            MCM::Members_t::Self()->On_Option_Highlight(option);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Run_Filter_Option_Variable()->Int()) {
                mcm->Info_Text("Execute the filter with all currently selected options.");
            } else if (option == Sex_Option_Variable()->Int()) {
                mcm->Info_Text("Find members with this sex.");
            } else if (option == Race_Option_Variable()->Int()) {
                mcm->Info_Text("Find members with this race.");
            } else if (option == Style_Option_Variable()->Int()) {
                mcm->Info_Text("Find members with this style.");
            } else if (option == Vitality_Option_Variable()->Int()) {
                mcm->Info_Text("Find members with this vitality.");
            } else if (option == Outfit2_Option_Variable()->Int()) {
                mcm->Info_Text("Find members wearing this outfit.");
            } else if (option == Rating_Option_Variable()->Int()) {
                mcm->Info_Text("Find members with this rating.");
            } else if (option == Relationship_Rank_Option_Variable()->Int()) {
                mcm->Info_Text("Find members with this relationship rank.");
            } else if (option == Search_Option_Variable()->Int()) {
                mcm->Info_Text("Find members whose name contains this input.\n"
                               "(If just one character, it only looks at the first letter of the name.)");
            } else if (option == Is_Alive_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are alive.");
            } else if (option == Is_Dead_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are dead.");
            } else if (option == Is_Original_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are originals, as opposed to clones.");
            } else if (option == Is_Clone_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are clones, as opposed to originals.");
            } else if (option == Is_Unique_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are unique.");
            } else if (option == Is_Generic_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are generic.");
            } else if (option == Is_Mobile_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are mobile.");
            } else if (option == Is_Immobile_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are immobile.");
            } else if (option == Is_Settler_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are settlers.");
            } else if (option == Is_Non_Settler_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are not settlers.");
            } else if (option == Is_Thrall_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are thralls.");
            } else if (option == Is_Non_Thrall_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are not thralls.");
            } else if (option == Is_Paralyzed_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are paralyzed.");
            } else if (option == Is_Non_Paralyzed_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are not paralyzed.");
            } else if (option == Is_Mannequin_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are mannequins.");
            } else if (option == Is_Non_Mannequin_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are not mannequins.");
            } else if (option == Is_Reanimated_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are reanimated.");
            } else if (option == Is_Non_Reanimated_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are not reanimated.");
            } else if (option == Is_Follower_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are followers.");
            } else if (option == Is_Non_Follower_Option_Variable()->Int()) {
                mcm->Info_Text("Find members who are not followers.");
            } else if (option == Is_Sneak_Option_Variable()->Int()) {
                mcm->Info_Text("Find followers who are sneaking.");
            } else if (option == Is_Non_Sneak_Option_Variable()->Int()) {
                mcm->Info_Text("Find followers who are not sneaking.");
            } else if (option == Is_Saddler_Option_Variable()->Int()) {
                mcm->Info_Text("Find followers who are riding a horse.");
            } else if (option == Is_Non_Saddler_Option_Variable()->Int()) {
                mcm->Info_Text("Find followers who are not riding a horse.");
            }
        }
    }

    void Filter_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Filter_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
