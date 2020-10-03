/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "consts.h"
#include "funcs.h"
#include "main.h"
#include "papyrus.inl"
#include "string2.h"
#include "ui.h"
#include "utils.h"
#include "vars.h"

#include "party/party_members.h"
#include "party/party_followers.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_settings.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Settings_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_settings");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Settings_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Settings_t* Settings_t::Self()
    {
        return static_cast<Settings_t*>(Consts::Control_Quest());
    }

    Object_t* Settings_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Settings_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Settings_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    // General
    Variable_t* Settings_t::Allow_Dialogue_For_All_Option_Variable() { DEFINE_VARIABLE("p_option_allow_dialogue_for_all"); }
    Variable_t* Settings_t::Allow_Chatter_Option_Variable() { DEFINE_VARIABLE("p_option_allow_chatter"); }
    Variable_t* Settings_t::Force_Cleanup_Option_Variable() { DEFINE_VARIABLE("p_option_force_cleanup"); }

    // Members
    Variable_t* Settings_t::Member_Limit_Option_Variable() { DEFINE_VARIABLE("p_option_member_limit"); }
    Variable_t* Settings_t::Member_Display_Limit_Option_Variable() { DEFINE_VARIABLE("p_option_member_display_limit"); }
    Variable_t* Settings_t::Default_Member_Style_Option_Variable() { DEFINE_VARIABLE("p_option_default_member_style"); }
    Variable_t* Settings_t::Default_Member_Vitality_Option_Variable() { DEFINE_VARIABLE("p_option_default_member_vitality"); }

    // Clones
    Variable_t* Settings_t::Force_Clone_Uniques_Option_Variable() { DEFINE_VARIABLE("p_option_force_clone_uniques"); }
    Variable_t* Settings_t::Force_Clone_Generics_Option_Variable() { DEFINE_VARIABLE("p_option_force_clone_generics"); }
    Variable_t* Settings_t::Force_Unclone_Uniques_Option_Variable() { DEFINE_VARIABLE("p_option_force_unclone_uniques"); }
    Variable_t* Settings_t::Force_Unclone_Generics_Option_Variable() { DEFINE_VARIABLE("p_option_force_unclone_generics"); }
    Variable_t* Settings_t::Clone_Outfit_Algorithm_Option_Variable() { DEFINE_VARIABLE("p_option_clone_outfit_algorithm"); }

    // Followers
    Variable_t* Settings_t::Do_Auto_Resurrect_Followers_Option_Variable() { DEFINE_VARIABLE("p_option_do_auto_resurrect_followers"); }
    Variable_t* Settings_t::Do_Level_Followers_Option_Variable() { DEFINE_VARIABLE("p_option_do_level_followers"); }

    // Outfits
    Variable_t* Settings_t::Do_Auto_Change_Outfits_Option_Variable() { DEFINE_VARIABLE("p_option_do_auto_change_outfits"); }
    Variable_t* Settings_t::Do_Auto_Change_Immobile_Outfit_Option_Variable() { DEFINE_VARIABLE("p_option_do_auto_change_immobile_outfit"); }
    Variable_t* Settings_t::Do_Auto_Fill_Outfits_Option_Variable() { DEFINE_VARIABLE("p_option_do_auto_fill_outfits"); }
    Variable_t* Settings_t::Fill_Outfit_Body_Chance_Option_Variable() { DEFINE_VARIABLE("p_option_fill_outfit_body_chance"); }
    Variable_t* Settings_t::Fill_Outfit_Head_Chance_Option_Variable() { DEFINE_VARIABLE("p_option_fill_outfit_head_chance"); }
    Variable_t* Settings_t::Fill_Outfit_Hands_Chance_Option_Variable() { DEFINE_VARIABLE("p_option_fill_outfit_hands_chance"); }
    Variable_t* Settings_t::Fill_Outfit_Feet_Chance_Option_Variable() { DEFINE_VARIABLE("p_option_fill_outfit_feet_chance"); }

    // Sorting
    Variable_t* Settings_t::Member_Sort_Algorithm_Option_Variable() { DEFINE_VARIABLE("p_option_member_sort_algorithm"); }
    Variable_t* Settings_t::Follower_Sort_Algorithm_Option_Variable() { DEFINE_VARIABLE("p_option_follower_sort_algorithm"); }

    void Settings_t::On_Build_Page()
    {
        Vars_t* vars = Vars_t::Self();
        MCM::Main_t* mcm = Main();

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

        mcm->Title_Text(" Settings ");

        mcm->Add_Header_Option(" General ");
        mcm->Add_Empty_Option();
        {
            Allow_Dialogue_For_All_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Allow Dialogue For All ", Consts::Allow_Dialogue_For_All_Global()->value > 0.0f)
            );
            Force_Cleanup_Option_Variable()->Int(
                mcm->Add_Text_Option(" Force Cleanup of Unused Objects ", "")
            );
        }
        //mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Members ");
        mcm->Add_Empty_Option();
        {
            Member_Limit_Option_Variable()->Int(
                mcm->Add_Slider_Option(" Member Limit ", vars->Member_Limit(), " {0} ")
            );
            Member_Display_Limit_Option_Variable()->Int(
                mcm->Add_Slider_Option(" Display Limit ", vars->Member_Display_Limit(), " {0} ")
            );

            Int_t default_style = vars->Default_Member_Style();
            const char* style = "";
            if (default_style == CODES::STYLE::DEFAULT) {
                style = " Default ";
            } else if (default_style == CODES::STYLE::WARRIOR) {
                style = " Warrior ";
            } else if (default_style == CODES::STYLE::MAGE) {
                style = " Mage ";
            } else if (default_style == CODES::STYLE::ARCHER) {
                style = " Archer ";
            } else if (default_style == CODES::STYLE::COWARD) {
                style = " Coward ";
            }
            Default_Member_Style_Option_Variable()->Int(
                mcm->Add_Text_Option(" Default Style ", style)
            );
            
            Int_t default_vitality = vars->Default_Member_Vitality();
            const char* vitality = "";
            if (default_vitality == CODES::VITALITY::MORTAL) {
                vitality = " Mortal ";
            } else if (default_vitality == CODES::VITALITY::PROTECTED) {
                vitality = " Protected ";
            } else if (default_vitality == CODES::VITALITY::ESSENTIAL) {
                vitality = " Essential ";
            } else if (default_vitality == CODES::VITALITY::INVULNERABLE) {
                vitality = " Invulnerable ";
            }
            Default_Member_Vitality_Option_Variable()->Int(
                mcm->Add_Text_Option(" Default Vitality ", vitality)
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Clones ");
        mcm->Add_Empty_Option();
        {
            Force_Clone_Uniques_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Force Clone Unique NPCs ", vars->Force_Clone_Uniques())
            );
            Force_Unclone_Uniques_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Force Unclone Unique NPCs ", vars->Force_Unclone_Uniques())
            ); 
            Force_Clone_Generics_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Force Clone Generic NPCs ", vars->Force_Clone_Generics())
            );
            Force_Unclone_Generics_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Force Unclone Generic NPCs ", vars->Force_Unclone_Generics())
            );

            Int_t clone_outfit_algorithm = vars->Clone_Outfit_Algorithm();
            const char* clone_outfit_display = "";
            if (clone_outfit_algorithm == CODES::OUTFIT::BASE) {
                clone_outfit_display = " Base ";
            } else if (clone_outfit_algorithm == CODES::OUTFIT::REFERENCE) {
                clone_outfit_display = " Reference ";
            }
            Clone_Outfit_Algorithm_Option_Variable()->Int(
                mcm->Add_Text_Option(" New Clone's Outfit ", clone_outfit_display)
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Followers ");
        mcm->Add_Empty_Option();
        {
            Do_Auto_Resurrect_Followers_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Auto Resurrect Followers ", vars->Do_Auto_Resurrect_Followers())
            );
            Do_Level_Followers_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Level Followers ", vars->Do_Level_Followers())
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Outfits ");
        mcm->Add_Empty_Option();
        {
            Bool_t do_auto_change_outfits = vars->Do_Auto_Change_Outfits();
            Do_Auto_Change_Outfits_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Auto Change Outfits ", do_auto_change_outfits)
            );
            Do_Auto_Change_Immobile_Outfit_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Auto Change Immobile Outfit ",
                                       vars->Do_Auto_Change_Immobile_Outfit(),
                                       do_auto_change_outfits ? MCM::NONE : MCM::DISABLE)
            );

            Bool_t do_auto_fill_outfits = vars->Do_Auto_Fill_Outfits();
            Do_Auto_Fill_Outfits_Option_Variable()->Int(
                mcm->Add_Toggle_Option(" Auto Fill Outfits ", do_auto_fill_outfits)
            );
            mcm->Add_Empty_Option();
            Fill_Outfit_Body_Chance_Option_Variable()->Int(
                mcm->Add_Slider_Option(" Fill Body Chance ",
                                       vars->Fill_Outfit_Body_Chance(),
                                       " {0}% ",
                                       do_auto_fill_outfits ? MCM::NONE : MCM::DISABLE)
            );
            Fill_Outfit_Head_Chance_Option_Variable()->Int(
                mcm->Add_Slider_Option(" Fill Head Chance ",
                                       vars->Fill_Outfit_Head_Chance(),
                                       " {0}% ",
                                       do_auto_fill_outfits ? MCM::NONE : MCM::DISABLE)
            );
            Fill_Outfit_Hands_Chance_Option_Variable()->Int(
                mcm->Add_Slider_Option(" Fill Hands Chance ",
                                       vars->Fill_Outfit_Hands_Chance(),
                                       " {0}% ",
                                       do_auto_fill_outfits ? MCM::NONE : MCM::DISABLE)
            );
            Fill_Outfit_Feet_Chance_Option_Variable()->Int(
                mcm->Add_Slider_Option(" Fill Feet Chance ",
                                       vars->Fill_Outfit_Feet_Chance(),
                                       " {0}% ",
                                       do_auto_fill_outfits ? MCM::NONE : MCM::DISABLE)
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Sorting ");
        mcm->Add_Empty_Option();
        {
            Member_Sort_Algorithm_Option_Variable()->Int(
                mcm->Add_Text_Option(" Member Algorithm ", vars->Member_Sort_Algorithm())
            );
            Follower_Sort_Algorithm_Option_Variable()->Int(
                mcm->Add_Text_Option(" Follower Algorithm ", vars->Follower_Sort_Algorithm())
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
    }

    void Settings_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        Modules::Vars_t* vars = Modules::Vars_t::Self();
        MCM::Main_t* mcm = Main();

        if (option == Allow_Dialogue_For_All_Option_Variable()->Int()) { // General
            Bool_t value = !vars->Allow_Dialogue_For_All();
            vars->Allow_Dialogue_For_All(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Force_Cleanup_Option_Variable()->Int()) {
            struct Callback : public Callback_t<Bool_t> {
                Settings_t* self;
                UCallback_t* user_callback;
                Callback(Settings_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Bool_t may_continue)
                {
                    if (may_continue) {
                        Int_t objects_deleted = Modules::Main_t::Self()->Force_Cleanup();
                        struct VCallback : public Virtual_Callback_t {
                            UCallback_t* user_callback;
                            VCallback(UCallback_t* user_callback) :
                                user_callback(user_callback)
                            {
                            }
                            void operator()(Variable_t* result)
                            {
                                MCM::Main_t::Self()->Return_Latent(user_callback);
                            }
                        };
                        std::string str;
                        if (objects_deleted == 1) {
                            str = "Deleted 1 object. ";
                        } else {
                            str = std::string("Deleted ") + std::to_string(objects_deleted) + " objects. ";
                        }
                        str += "It's best to save your game and reload. If the game crashes when you reload, it should be fine after a restart.";
                        UI::Message_Box(str.c_str(), new VCallback(user_callback));
                    } else {
                        MCM::Main_t::Self()->Return_Latent(user_callback);
                    }
                }
            };
            mcm->Show_Message("This will forcefully delete unused objects. NPC Party requests these objects to be deleted "
                              "on game load, but Skyrim doesn't always comply. "
                              "You should save your game before proceeding as it may crash. Continue?",
                              true, " Yes ", " No ", new Callback(this, user_callback));

        } else if (option == Default_Member_Style_Option_Variable()->Int()) { // Members
            Int_t style = vars->Default_Member_Style();
            if (style == CODES::STYLE::DEFAULT) {
                vars->Default_Member_Style(CODES::STYLE::WARRIOR);
                mcm->Text_Option_Value(option, " Warrior ", true);
            } else if (style == CODES::STYLE::WARRIOR) {
                vars->Default_Member_Style(CODES::STYLE::MAGE);
                mcm->Text_Option_Value(option, " Mage ", true);
            } else if (style == CODES::STYLE::MAGE) {
                vars->Default_Member_Style(CODES::STYLE::ARCHER);
                mcm->Text_Option_Value(option, " Archer ", true);
            } else if (style == CODES::STYLE::ARCHER) {
                vars->Default_Member_Style(CODES::STYLE::COWARD);
                mcm->Text_Option_Value(option, " Coward ", true);
            } else if (style == CODES::STYLE::COWARD) {
                vars->Default_Member_Style(CODES::STYLE::DEFAULT);
                mcm->Text_Option_Value(option, " Default ", true);
            } else {
                vars->Default_Member_Style(CODES::STYLE::DEFAULT);
                mcm->Text_Option_Value(option, " Default ", true);
            }
            mcm->Return_Latent(user_callback);
        } else if (option == Default_Member_Vitality_Option_Variable()->Int()) {
            Int_t vitality = vars->Default_Member_Vitality();
            if (vitality == CODES::VITALITY::MORTAL) {
                vars->Default_Member_Vitality(CODES::VITALITY::PROTECTED);
                mcm->Text_Option_Value(option, " Protected ", true);
            } else if (vitality == CODES::VITALITY::PROTECTED) {
                vars->Default_Member_Vitality(CODES::VITALITY::ESSENTIAL);
                mcm->Text_Option_Value(option, " Essential ", true);
            } else if (vitality == CODES::VITALITY::ESSENTIAL) {
                vars->Default_Member_Vitality(CODES::VITALITY::INVULNERABLE);
                mcm->Text_Option_Value(option, " Invulnerable ", true);
            } else if (vitality == CODES::VITALITY::INVULNERABLE) {
                vars->Default_Member_Vitality(CODES::VITALITY::MORTAL);
                mcm->Text_Option_Value(option, " Mortal ", true);
            } else {
                vars->Default_Member_Vitality(CODES::VITALITY::MORTAL);
                mcm->Text_Option_Value(option, " Mortal ", true);
            }
            mcm->Return_Latent(user_callback);

        } else if (option == Force_Clone_Uniques_Option_Variable()->Int()) { // Clones
            Bool_t value = !vars->Force_Clone_Uniques();
            vars->Force_Clone_Uniques(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Force_Unclone_Uniques_Option_Variable()->Int()) {
            Bool_t value = !vars->Force_Unclone_Uniques();
            vars->Force_Unclone_Uniques(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Force_Clone_Generics_Option_Variable()->Int()) {
            Bool_t value = !vars->Force_Clone_Generics();
            vars->Force_Clone_Generics(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Force_Unclone_Generics_Option_Variable()->Int()) {
            Bool_t value = !vars->Force_Unclone_Generics();
            vars->Force_Unclone_Generics(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Clone_Outfit_Algorithm_Option_Variable()->Int()) {
            Int_t clone_outfit_algorithm = vars->Clone_Outfit_Algorithm();
            if (clone_outfit_algorithm == CODES::OUTFIT::BASE) {
                vars->Clone_Outfit_Algorithm(CODES::OUTFIT::REFERENCE);
                mcm->Text_Option_Value(option, " Reference ", true);
            } else if (clone_outfit_algorithm == CODES::OUTFIT::REFERENCE) {
                vars->Clone_Outfit_Algorithm(CODES::OUTFIT::BASE);
                mcm->Text_Option_Value(option, " Base ", true);
            } else {
                vars->Clone_Outfit_Algorithm(CODES::OUTFIT::REFERENCE);
                mcm->Text_Option_Value(option, " Reference ", true);
            }
            mcm->Return_Latent(user_callback);

        } else if (option == Do_Auto_Resurrect_Followers_Option_Variable()->Int()) { // Followers
            Bool_t value = !vars->Do_Auto_Resurrect_Followers();
            vars->Do_Auto_Resurrect_Followers(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Do_Level_Followers_Option_Variable()->Int()) {
            if (vars->Do_Level_Followers()) {
                Party::Followers_t::Self()->Unlevel();
                vars->Do_Level_Followers(false);
                mcm->Toggle_Option_Value(option, false, true);
            } else {
                vars->Do_Level_Followers(true);
                mcm->Toggle_Option_Value(option, true, true);
                Party::Followers_t::Self()->Level();
            }
            mcm->Return_Latent(user_callback);

        } else if (option == Do_Auto_Change_Outfits_Option_Variable()->Int()) { // Outfits
            Bool_t value = !vars->Do_Auto_Change_Outfits();
            vars->Do_Auto_Change_Outfits(value);
            mcm->Toggle_Option_Value(option, value, false);
            if (value) {
                mcm->Enable(Do_Auto_Change_Immobile_Outfit_Option_Variable()->Int(), true);
            } else {
                mcm->Disable(Do_Auto_Change_Immobile_Outfit_Option_Variable()->Int(), true);
            }
            mcm->Return_Latent(user_callback);
        } else if (option == Do_Auto_Change_Immobile_Outfit_Option_Variable()->Int()) {
            Bool_t value = !vars->Do_Auto_Change_Immobile_Outfit();
            vars->Do_Auto_Change_Immobile_Outfit(value);
            mcm->Toggle_Option_Value(option, value, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Do_Auto_Fill_Outfits_Option_Variable()->Int()) {
            Bool_t value = !vars->Do_Auto_Fill_Outfits();
            vars->Do_Auto_Fill_Outfits(value);
            mcm->Toggle_Option_Value(option, value, false);
            if (value) {
                mcm->Enable(Fill_Outfit_Body_Chance_Option_Variable()->Int(), false);
                mcm->Enable(Fill_Outfit_Head_Chance_Option_Variable()->Int(), false);
                mcm->Enable(Fill_Outfit_Hands_Chance_Option_Variable()->Int(), false);
                mcm->Enable(Fill_Outfit_Feet_Chance_Option_Variable()->Int(), true);
            } else {
                mcm->Disable(Fill_Outfit_Body_Chance_Option_Variable()->Int(), false);
                mcm->Disable(Fill_Outfit_Head_Chance_Option_Variable()->Int(), false);
                mcm->Disable(Fill_Outfit_Hands_Chance_Option_Variable()->Int(), false);
                mcm->Disable(Fill_Outfit_Feet_Chance_Option_Variable()->Int(), true);
            }
            mcm->Return_Latent(user_callback);

        } else if (option == Member_Sort_Algorithm_Option_Variable()->Int()) { // Sorting
            String_t sort_algorithm = vars->Member_Sort_Algorithm();
            if (String2::Is_Same_Caseless(sort_algorithm, "NAME")) {
                sort_algorithm = "NAME_CASELESS";
            } else if (String2::Is_Same_Caseless(sort_algorithm, "NAME_CASELESS")) {
                sort_algorithm = "RATING_NAME";
            } else if (String2::Is_Same_Caseless(sort_algorithm, "RATING_NAME")) {
                sort_algorithm = "RATING_NAME_CASELESS";
            } else if (String2::Is_Same_Caseless(sort_algorithm, "RATING_NAME_CASELESS")) {
                sort_algorithm = "NAME";
            } else {
                sort_algorithm = "NAME";
            }
            vars->Member_Sort_Algorithm(sort_algorithm);
            mcm->Text_Option_Value(option, sort_algorithm, true);
            mcm->Return_Latent(user_callback);
        } else if (option == Follower_Sort_Algorithm_Option_Variable()->Int()) {
            String_t sort_algorithm = vars->Follower_Sort_Algorithm();
            if (String2::Is_Same_Caseless(sort_algorithm, "NAME")) {
                sort_algorithm = "NAME_CASELESS";
            } else if (String2::Is_Same_Caseless(sort_algorithm, "NAME_CASELESS")) {
                sort_algorithm = "NAME";
            } else {
                sort_algorithm = "NAME";
            }
            vars->Follower_Sort_Algorithm(sort_algorithm);
            mcm->Text_Option_Value(option, sort_algorithm, true);
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settings_t::On_Option_Menu_Open(Int_t option)
    {
    }

    void Settings_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
    }

    void Settings_t::On_Option_Slider_Open(Int_t option)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        MCM::Main_t* mcm = Main();

        if (option == Member_Limit_Option_Variable()->Int()) { // Members
            Party::Members_t* members = Party::Members_t::Self();
            mcm->Slider_Dialog_Current_Value(vars->Member_Limit());
            mcm->Slider_Dialog_Default_Value(members->Max());
            mcm->Slider_Dialog_Range_Values(members->Count_Filled(), members->Max());
            mcm->Slider_Dialog_Interval_Value(1.0f);
        } else if (option == Member_Display_Limit_Option_Variable()->Int()) {
            mcm->Slider_Dialog_Current_Value(vars->Member_Display_Limit());
            mcm->Slider_Dialog_Default_Value(Party::Members_t::DEFAULT_DISPLAY_LIMIT);
            mcm->Slider_Dialog_Range_Values(Party::Members_t::MIN_DISPLAY_LIMIT, Party::Members_t::MAX_DISPLAY_LIMIT);
            mcm->Slider_Dialog_Interval_Value(1.0f);

        } else if (option == Fill_Outfit_Body_Chance_Option_Variable()->Int()) { // Outfits
            mcm->Slider_Dialog_Current_Value(vars->Fill_Outfit_Body_Chance());
            mcm->Slider_Dialog_Default_Value(Party::Members_t::DEFAULT_OUTFIT_BODY_CHANCE);
            mcm->Slider_Dialog_Range_Values(0.0f, 100.0f);
            mcm->Slider_Dialog_Interval_Value(1.0f);
        } else if (option == Fill_Outfit_Head_Chance_Option_Variable()->Int()) {
            mcm->Slider_Dialog_Current_Value(vars->Fill_Outfit_Head_Chance());
            mcm->Slider_Dialog_Default_Value(Party::Members_t::DEFAULT_OUTFIT_HEAD_CHANCE);
            mcm->Slider_Dialog_Range_Values(0.0f, 100.0f);
            mcm->Slider_Dialog_Interval_Value(1.0f);
        } else if (option == Fill_Outfit_Hands_Chance_Option_Variable()->Int()) {
            mcm->Slider_Dialog_Current_Value(vars->Fill_Outfit_Hands_Chance());
            mcm->Slider_Dialog_Default_Value(Party::Members_t::DEFAULT_OUTFIT_HANDS_CHANCE);
            mcm->Slider_Dialog_Range_Values(0.0f, 100.0f);
            mcm->Slider_Dialog_Interval_Value(1.0f);
        } else if (option == Fill_Outfit_Feet_Chance_Option_Variable()->Int()) {
            mcm->Slider_Dialog_Current_Value(vars->Fill_Outfit_Feet_Chance());
            mcm->Slider_Dialog_Default_Value(Party::Members_t::DEFAULT_OUTFIT_FEET_CHANCE);
            mcm->Slider_Dialog_Range_Values(0.0f, 100.0f);
            mcm->Slider_Dialog_Interval_Value(1.0f);
        }
    }

    void Settings_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        MCM::Main_t* mcm = Main();

        if (option == Member_Limit_Option_Variable()->Int()) { // Members
            vars->Member_Limit(value);
            mcm->Slider_Option_Value(option, value, " {0} ", true);
        } else if (option == Member_Display_Limit_Option_Variable()->Int()) {
            vars->Member_Display_Limit(value);
            mcm->Slider_Option_Value(option, value, " {0} ", true);

        } else if (option == Fill_Outfit_Body_Chance_Option_Variable()->Int()) { // Outfits
            vars->Fill_Outfit_Body_Chance(value);
            mcm->Slider_Option_Value(option, value, " {0}% ", true);
        } else if (option == Fill_Outfit_Head_Chance_Option_Variable()->Int()) {
            vars->Fill_Outfit_Head_Chance(value);
            mcm->Slider_Option_Value(option, value, " {0}% ", true);
        } else if (option == Fill_Outfit_Hands_Chance_Option_Variable()->Int()) {
            vars->Fill_Outfit_Hands_Chance(value);
            mcm->Slider_Option_Value(option, value, " {0}% ", true);
        } else if (option == Fill_Outfit_Feet_Chance_Option_Variable()->Int()) {
            vars->Fill_Outfit_Feet_Chance(value);
            mcm->Slider_Option_Value(option, value, " {0}% ", true);
        }
    }

    void Settings_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
    }

    void Settings_t::On_Option_Keymap_Change(Int_t option,
                                             Int_t key_code,
                                             String_t conflict,
                                             String_t conflicting_mod,
                                             Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Settings_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Settings_t::On_Option_Highlight(Int_t option)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        MCM::Main_t* mcm = Main();

        if (option == Allow_Dialogue_For_All_Option_Variable()->Int()) { // General
            mcm->Info_Text("Enabled: You can access the [NPC Party] menu with any viable NPC.\n"
                           "Disabled: You can only access the [NPC Party] menu with members.\n"
                           "Either way, you can still use hotkeys to quickly add a member and access the menu.");
        /*} else if (option == Allow_Chatter_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: Members will talk more often and comment on the world around them.\n"
                           "Disabled: Members will remain silent unless they are fighting or you talk to them.\n"
                           "This feature is a work in progress, and so you may not notice any difference yet.");*/
        } else if (option == Force_Cleanup_Option_Variable()->Int()) {
            mcm->Info_Text("This will attempt to remove unused objects created by NPC Party from your save file. Use with "
                           "caution, as this may crash your game. You may wish to try it when wrapping up your gaming session.");

        } else if (option == Member_Limit_Option_Variable()->Int()) { // Members
            mcm->Info_Text("This will limit the amount of members you can attain. You can always increase, "
                           "but you may only decrease unto the amount of members you currently have.");
        } else if (option == Member_Display_Limit_Option_Variable()->Int()) {
            mcm->Info_Text("This will limit the number of members whom will be summoned at a time during a display.");
        } else if (option == Default_Member_Style_Option_Variable()->Int()) {
            mcm->Info_Text("This style will be assigned to each new member. "
                           "With Default, they will fight how they wish. "
                           "As a Warrior they will fight with all manner of melee weapons, "
                           "as a Mage with the magic in the palm of their hands, "
                           "as an Archer with their bow an arrow and at a distance, "
                           "and as a Coward they fight not at at all, instead choosing to flee from combat.");
        } else if (option == Default_Member_Vitality_Option_Variable()->Int()) {
            mcm->Info_Text("This vitality will be assigned to each new member. "
                           "As a Mortal, anyone can kill them. "
                           "Protected status will allow only you to kill them, by friendly fire. "
                           "Essential leaves them always alive, even should they need to take a knee. "
                           "Invulnerable makes them unstoppable, and no one will be able to harm them.");

        } else if (option == Force_Clone_Uniques_Option_Variable()->Int()) { // Clones
            mcm->Info_Text("Enabled: Only a clone of a unique npc can become a member, and not the unique npc themself.\n"
                           "Disabled: Any unique npc can become a member, as well as their clones.");
        } else if (option == Force_Unclone_Uniques_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: Forces a clone of a unique npc to be uncloned when unmembered.\n"
                           "Disabled: Allows a clone of a unique npc to be unmembered or uncloned.");
        } else if (option == Force_Clone_Generics_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: Only a clone of a generic npc can become a member, and not the generic npc themself.\n"
                           "Disabled: Any generic npc can become a member, as well as their clones.");
        } else if (option == Force_Unclone_Generics_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: Forces a clone of a generic npc to be uncloned when unmembered.\n"
                           "Disabled: Allows a clone of a generic npc to be unmembered or uncloned.");
        } else if (option == Clone_Outfit_Algorithm_Option_Variable()->Int()) {
            mcm->Info_Text("Base: A clone will receive the base outfit of the original npc.\n"
                           "Reference: A clone will receive the items the original npc is currently wearing.");

        } else if (option == Do_Auto_Resurrect_Followers_Option_Variable()->Int()) { // Followers
            mcm->Info_Text("Enabled: Followers will automatically resurrect after each battle.\n"
                           "Disabled: Followers will not automatically resurrect after each battle.");
        } else if (option == Do_Level_Followers_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: Followers will be dynamically leveled in pace with the player's level.\n"
                           "Disabled: Followers will not be leveled, and their stats will not change.\n"
                           "You can enable and disable leveling freely without losing any progress.");

        } else if (option == Do_Auto_Change_Outfits_Option_Variable()->Int()) { // Outfits
            mcm->Info_Text("Enabled: Members will automatically dress according to their job, e.g. settler, immobile, follower, etc.\n"
                           "Disabled: Members will not automatically dress according to their job.\n"
                           "At some point, we may introduce auto outfitting based on where the member is located as well.");
        } else if (option == Do_Auto_Change_Immobile_Outfit_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: When auto outfitting, members will equip their immobile outfit when applicable.\n"
                           "Disabled: When auto outfitting, members will never equip their immobile outfit even when applicable.");
        } else if (option == Do_Auto_Fill_Outfits_Option_Variable()->Int()) {
            mcm->Info_Text("Enabled: Members will automatically receive items for each outfit they are told to wear.\n"
                           "Disabled: Members will not automatically receive items for each outfit, and will be naked until you equip them.");
        } else if (option == Fill_Outfit_Body_Chance_Option_Variable()->Int()) {
            mcm->Info_Text("The chance that outfits will get items that fit on the body.");
        } else if (option == Fill_Outfit_Head_Chance_Option_Variable()->Int()) {
            mcm->Info_Text("The chance that outfits will get items that fit on the head.");
        } else if (option == Fill_Outfit_Hands_Chance_Option_Variable()->Int()) {
            mcm->Info_Text("The chance that outfits will get items that fit on the hands.");
        } else if (option == Fill_Outfit_Feet_Chance_Option_Variable()->Int()) {
            mcm->Info_Text("The chance that outfits will get items that fit on the feet.");

        } else if (option == Member_Sort_Algorithm_Option_Variable()->Int()) { // Sorting
            mcm->Info_Text("The algorithm that is used to sort members. CASELESS ignores capitals.");
        } else if (option == Follower_Sort_Algorithm_Option_Variable()->Int()) {
            mcm->Info_Text("The algorithm that is used to sort followers. CASELESS ignores capitals.");
        }
    }

    void Settings_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Settings_t,            \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
