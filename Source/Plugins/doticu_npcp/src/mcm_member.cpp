/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "commands.h"
#include "consts.h"
#include "funcs.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_player.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_settler.h"
#include "party/party_followers.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_members.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_mannequins.h"
#include "mcm/mcm_followers.h"
#include "mcm/mcm_settlers.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Member_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_member");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Member_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Member_t* Member_t::Self()
    {
        return static_cast<Member_t*>(Consts::Control_Quest());
    }

    Object_t* Member_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Member_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Member_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Member_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }
    Variable_t* Member_t::Party_Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }

    Variable_t* Member_t::Rename_Option_Variable() { DEFINE_VARIABLE("p_option_rename"); }
    Variable_t* Member_t::Back_Option_Variable() { DEFINE_VARIABLE("p_option_back"); }
    Variable_t* Member_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_prev"); }
    Variable_t* Member_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }
    Variable_t* Member_t::Unmember_Option_Variable() { DEFINE_VARIABLE("p_option_unmember"); }
    Variable_t* Member_t::Clone_Option_Variable() { DEFINE_VARIABLE("p_option_clone"); }
    Variable_t* Member_t::Unclone_Option_Variable() { DEFINE_VARIABLE("p_option_unclone"); }
    Variable_t* Member_t::Mobilize_Option_Variable() { DEFINE_VARIABLE("p_option_mobilize"); }
    Variable_t* Member_t::Immobilize_Option_Variable() { DEFINE_VARIABLE("p_option_immobilize"); }
    Variable_t* Member_t::Settle_Option_Variable() { DEFINE_VARIABLE("p_option_settle"); }
    Variable_t* Member_t::Resettle_Option_Variable() { DEFINE_VARIABLE("p_option_resettle"); }
    Variable_t* Member_t::Unsettle_Option_Variable() { DEFINE_VARIABLE("p_option_unsettle"); }
    Variable_t* Member_t::Open_Settler_Option_Variable() { DEFINE_VARIABLE("p_option_open_settler"); }
    Variable_t* Member_t::Enthrall_Option_Variable() { DEFINE_VARIABLE("p_option_enthrall"); }
    Variable_t* Member_t::Unthrall_Option_Variable() { DEFINE_VARIABLE("p_option_unthrall"); }
    Variable_t* Member_t::Paralyze_Option_Variable() { DEFINE_VARIABLE("p_option_paralyze"); }
    Variable_t* Member_t::Unparalyze_Option_Variable() { DEFINE_VARIABLE("p_option_unparalyze"); }
    Variable_t* Member_t::Stylize_Option_Variable() { DEFINE_VARIABLE("p_option_style"); }
    Variable_t* Member_t::Vitalize_Option_Variable() { DEFINE_VARIABLE("p_option_vitalize"); }
    Variable_t* Member_t::Outfit2_Option_Variable() { DEFINE_VARIABLE("p_option_outfit"); }
    Variable_t* Member_t::Pack_Option_Variable() { DEFINE_VARIABLE("p_option_pack"); }
    Variable_t* Member_t::Stash_Option_Variable() { DEFINE_VARIABLE("p_option_stash"); }
    Variable_t* Member_t::Summon_Option_Variable() { DEFINE_VARIABLE("p_option_summon"); }
    Variable_t* Member_t::Goto_Option_Variable() { DEFINE_VARIABLE("p_option_goto"); }
    Variable_t* Member_t::Rating_Option_Variable() { DEFINE_VARIABLE("p_option_rating"); }
    Variable_t* Member_t::Resurrect_Option_Variable() { DEFINE_VARIABLE("p_option_resurrect"); }
    Variable_t* Member_t::Follow_Option_Variable() { DEFINE_VARIABLE("p_option_follow"); }
    Variable_t* Member_t::Unfollow_Option_Variable() { DEFINE_VARIABLE("p_option_unfollow"); }
    Variable_t* Member_t::Sneak_Option_Variable() { DEFINE_VARIABLE("p_option_sneak"); }
    Variable_t* Member_t::Unsneak_Option_Variable() { DEFINE_VARIABLE("p_option_unsneak"); }

    Variable_t* Member_t::Health_Attribute_Option_Variable() { DEFINE_VARIABLE("p_option_health"); }
    Variable_t* Member_t::Magicka_Attribute_Option_Variable() { DEFINE_VARIABLE("p_option_magicka"); }
    Variable_t* Member_t::Stamina_Attribute_Option_Variable() { DEFINE_VARIABLE("p_option_stamina"); }

    Variable_t* Member_t::One_Handed_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_one_handed"); }
    Variable_t* Member_t::Two_Handed_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_two_handed"); }
    Variable_t* Member_t::Block_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_block"); }
    Variable_t* Member_t::Heavy_Armor_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_heavy_armor"); }
    Variable_t* Member_t::Light_Armor_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_light_armor"); }
    Variable_t* Member_t::Smithing_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_smithing"); }

    Variable_t* Member_t::Destruction_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_destruction"); }
    Variable_t* Member_t::Restoration_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_restoration"); }
    Variable_t* Member_t::Conjuration_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_conjuration"); }
    Variable_t* Member_t::Alteration_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_alteration"); }
    Variable_t* Member_t::Illusion_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_illusion"); }
    Variable_t* Member_t::Enchanting_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_enchanting"); }

    Variable_t* Member_t::Marksman_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_marksman"); }
    Variable_t* Member_t::Sneak_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_sneak"); }
    Variable_t* Member_t::Alchemy_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_alchemy"); }
    Variable_t* Member_t::Lockpicking_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_lockpicking"); }
    Variable_t* Member_t::Pickpocket_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_pickpocket"); }
    Variable_t* Member_t::Speechcraft_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_speechcraft"); }

    Variable_t* Member_t::Race_Option_Variable() { DEFINE_VARIABLE("p_option_race"); }
    Variable_t* Member_t::Relationship_Rank_Option_Variable() { DEFINE_VARIABLE("p_option_relationship_rank"); }
    Variable_t* Member_t::Worldspace_Option_Variable() { DEFINE_VARIABLE("p_option_worldspace"); }
    Variable_t* Member_t::Location_Option_Variable() { DEFINE_VARIABLE("p_option_location"); }
    Variable_t* Member_t::Cell_Option_Variable() { DEFINE_VARIABLE("p_option_cell"); }

    Int_t Member_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    Party::Member_t* Member_t::Party_Member()
    {
        return static_cast<Party::Member_t*>(Party_Member_Variable()->Alias());
    }

    void Member_t::View_Members_Member(Party::Member_t* member)
    {
        Current_View_Variable()->Int(CODES::VIEW::MEMBERS_MEMBER);
        Party_Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    void Member_t::View_Followers_Member(Party::Member_t* member)
    {
        Current_View_Variable()->Int(CODES::VIEW::FOLLOWERS_MEMBER);
        Party_Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    void Member_t::View_Filter_Members_Member(Party::Member_t* member)
    {
        Current_View_Variable()->Int(CODES::VIEW::FILTER_MEMBERS_MEMBER);
        Party_Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    void Member_t::View_Mannequins_Member(Party::Member_t* member)
    {
        Current_View_Variable()->Int(CODES::VIEW::MANNEQUINS_MEMBER);
        Party_Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    void Member_t::Build_Commands()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);

        mcm_main->Cursor_Position(4);
        mcm_main->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

        mcm_main->Add_Header_Option("Commands: ");

        Summon_Option_Variable()->Int(mcm_main->Add_Text_Option(" Summon ", ""));
        Goto_Option_Variable()->Int(mcm_main->Add_Text_Option(" Goto ", ""));
        Pack_Option_Variable()->Int(mcm_main->Add_Text_Option(" Pack ", ""));
        Stash_Option_Variable()->Int(mcm_main->Add_Text_Option(" Stash ", ""));
        Outfit2_Option_Variable()->Int(mcm_main->Add_Menu_Option(" Outfit ", ""));

        if (party_member->Is_Mobile()) {
            Mobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Mobilize ", "", MCM::DISABLE));
            Immobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Immobilize ", ""));
        } else {
            Mobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Mobilize ", ""));
            Immobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Immobilize ", "", MCM::DISABLE));
        }

        if (party_member->Is_Settler()) {
            Settle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Settle ", "", MCM::DISABLE));
            Resettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resettle ", ""));
            Unsettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsettle ", ""));
            Open_Settler_Option_Variable()->Int(mcm_main->Add_Text_Option(" Open Settler Menu", ""));
        } else {
            Settle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Settle ", ""));
            Resettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resettle ", "", MCM::DISABLE));
            Unsettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsettle ", "", MCM::DISABLE));
            Open_Settler_Option_Variable()->Int(mcm_main->Add_Text_Option(" Open Settler Menu", "", MCM::DISABLE));
        }

        if (party_member->Is_Paralyzed()) {
            Paralyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Paralyze ", "", MCM::DISABLE));
            Unparalyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unparalyze ", ""));
        } else {
            Paralyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Paralyze ", ""));
            Unparalyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unparalyze ", "", MCM::DISABLE));
        }

        if (party_member->Is_Follower()) {
            Follow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Follow ", "", MCM::DISABLE));
            Unfollow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unfollow ", ""));
            if (party_member->Is_Sneak()) {
                Sneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Sneak ", "", MCM::DISABLE));
                Unsneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsneak ", ""));
            } else {
                Sneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Sneak ", ""));
                Unsneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsneak ", "", MCM::DISABLE));
            }
        } else {
            Follow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Follow ", ""));
            Unfollow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unfollow ", "", MCM::DISABLE));

            Sneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Sneak ", "", MCM::DISABLE));
            Unsneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsneak ", "", MCM::DISABLE));
        }

        Rating_Option_Variable()->Int(mcm_main->Add_Text_Option(" Rating ", party_member->Rating_Stars()));

        Int_t style = party_member->Style();
        if (style == CODES::STYLE::DEFAULT) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Default "));
        } else if (style == CODES::STYLE::WARRIOR) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Warrior "));
        } else if (style == CODES::STYLE::MAGE) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Mage "));
        } else if (style == CODES::STYLE::ARCHER) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Archer "));
        } else if (style == CODES::STYLE::COWARD) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Coward "));
        } else {
            NPCP_ASSERT(false);
        }

        Int_t vitality = party_member->Vitality();
        if (vitality == CODES::VITALITY::MORTAL) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Mortal "));
        } else if (vitality == CODES::VITALITY::PROTECTED) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Protected "));
        } else if (vitality == CODES::VITALITY::ESSENTIAL) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Essential "));
        } else if (vitality == CODES::VITALITY::INVULNERABLE) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Invulnerable "));
        } else {
            NPCP_ASSERT(false);
        }

        if (party_member->Is_Alive()) {
            Resurrect_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resurrect ", "", MCM::DISABLE));
        } else {
            Resurrect_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resurrect ", ""));
        }

        Clone_Option_Variable()->Int(mcm_main->Add_Text_Option(" Clone ", ""));
        if (party_member->Is_Clone()) {
            Unclone_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unclone ", ""));
        } else {
            Unclone_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unclone ", "", MCM::DISABLE));
        }

        if (party_member->Should_Unclone()) {
            Unmember_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unmember ", "", MCM::DISABLE));
        } else {
            Unmember_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unmember ", ""));
        }
    }

    void Member_t::Update_Commands()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);

        mcm_main->Option_Flags(Summon_Option_Variable()->Int(), MCM::NONE, false);
        mcm_main->Option_Flags(Goto_Option_Variable()->Int(), MCM::NONE, false);
        mcm_main->Option_Flags(Pack_Option_Variable()->Int(), MCM::NONE, false);
        mcm_main->Option_Flags(Stash_Option_Variable()->Int(), MCM::NONE, false);
        mcm_main->Option_Flags(Outfit2_Option_Variable()->Int(), MCM::NONE, false);

        if (party_member->Is_Mobile()) {
            mcm_main->Option_Flags(Mobilize_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Immobilize_Option_Variable()->Int(), MCM::NONE, false);
        } else {
            mcm_main->Option_Flags(Mobilize_Option_Variable()->Int(), MCM::NONE, false);
            mcm_main->Option_Flags(Immobilize_Option_Variable()->Int(), MCM::DISABLE, false);
        }

        if (party_member->Is_Settler()) {
            mcm_main->Option_Flags(Settle_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Resettle_Option_Variable()->Int(), MCM::NONE, false);
            mcm_main->Option_Flags(Unsettle_Option_Variable()->Int(), MCM::NONE, false);
            mcm_main->Option_Flags(Open_Settler_Option_Variable()->Int(), MCM::NONE, false);
        } else {
            mcm_main->Option_Flags(Settle_Option_Variable()->Int(), MCM::NONE, false);
            mcm_main->Option_Flags(Resettle_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Unsettle_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Open_Settler_Option_Variable()->Int(), MCM::DISABLE, false);
        }

        if (party_member->Is_Paralyzed()) {
            mcm_main->Option_Flags(Paralyze_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Unparalyze_Option_Variable()->Int(), MCM::NONE, false);
        } else {
            mcm_main->Option_Flags(Paralyze_Option_Variable()->Int(), MCM::NONE, false);
            mcm_main->Option_Flags(Unparalyze_Option_Variable()->Int(), MCM::DISABLE, false);
        }

        if (party_member->Is_Follower()) {
            mcm_main->Option_Flags(Follow_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Unfollow_Option_Variable()->Int(), MCM::NONE, false);
            if (party_member->Is_Sneak()) {
                mcm_main->Option_Flags(Sneak_Option_Variable()->Int(), MCM::DISABLE, false);
                mcm_main->Option_Flags(Unsneak_Option_Variable()->Int(), MCM::NONE, false);
            } else {
                mcm_main->Option_Flags(Sneak_Option_Variable()->Int(), MCM::NONE, false);
                mcm_main->Option_Flags(Unsneak_Option_Variable()->Int(), MCM::DISABLE, false);
            }
        } else {
            mcm_main->Option_Flags(Follow_Option_Variable()->Int(), MCM::NONE, false);
            mcm_main->Option_Flags(Unfollow_Option_Variable()->Int(), MCM::DISABLE, false);

            mcm_main->Option_Flags(Sneak_Option_Variable()->Int(), MCM::DISABLE, false);
            mcm_main->Option_Flags(Unsneak_Option_Variable()->Int(), MCM::DISABLE, false);
        }

        mcm_main->Enable(Rating_Option_Variable()->Int(), false);
        mcm_main->Enable(Stylize_Option_Variable()->Int(), false);
        mcm_main->Enable(Vitalize_Option_Variable()->Int(), false);

        mcm_main->Text_Option_Value(Rating_Option_Variable()->Int(), party_member->Rating_Stars(), false);

        Int_t style = party_member->Style();
        if (style == CODES::STYLE::DEFAULT) {
            mcm_main->Text_Option_Value(Stylize_Option_Variable()->Int(), " Default ", false);
        } else if (style == CODES::STYLE::WARRIOR) {
            mcm_main->Text_Option_Value(Stylize_Option_Variable()->Int(), " Warrior ", false);
        } else if (style == CODES::STYLE::MAGE) {
            mcm_main->Text_Option_Value(Stylize_Option_Variable()->Int(), " Mage ", false);
        } else if (style == CODES::STYLE::ARCHER) {
            mcm_main->Text_Option_Value(Stylize_Option_Variable()->Int(), " Archer ", false);
        } else if (style == CODES::STYLE::COWARD) {
            mcm_main->Text_Option_Value(Stylize_Option_Variable()->Int(), " Coward ", false);
        } else {
            NPCP_ASSERT(false);
        }

        Int_t vitality = party_member->Vitality();
        if (vitality == CODES::VITALITY::MORTAL) {
            mcm_main->Text_Option_Value(Vitalize_Option_Variable()->Int(), " Mortal ", false);
        } else if (vitality == CODES::VITALITY::PROTECTED) {
            mcm_main->Text_Option_Value(Vitalize_Option_Variable()->Int(), " Protected ", false);
        } else if (vitality == CODES::VITALITY::ESSENTIAL) {
            mcm_main->Text_Option_Value(Vitalize_Option_Variable()->Int(), " Essential ", false);
        } else if (vitality == CODES::VITALITY::INVULNERABLE) {
            mcm_main->Text_Option_Value(Vitalize_Option_Variable()->Int(), " Invulnerable ", false);
        } else {
            NPCP_ASSERT(false);
        }

        if (party_member->Is_Alive()) {
            mcm_main->Option_Flags(Resurrect_Option_Variable()->Int(), MCM::DISABLE, false);
        } else {
            mcm_main->Option_Flags(Resurrect_Option_Variable()->Int(), MCM::NONE, false);
        }

        mcm_main->Option_Flags(Clone_Option_Variable()->Int(), MCM::NONE, false);
        if (party_member->Is_Clone()) {
            mcm_main->Option_Flags(Unclone_Option_Variable()->Int(), MCM::NONE, false);
        } else {
            mcm_main->Option_Flags(Unclone_Option_Variable()->Int(), MCM::DISABLE, false);
        }

        if (party_member->Should_Unclone()) {
            mcm_main->Option_Flags(Unmember_Option_Variable()->Int(), MCM::DISABLE, false);
        } else {
            mcm_main->Option_Flags(Unmember_Option_Variable()->Int(), MCM::NONE, false);
        }

        mcm_main->Option_Flags(Rename_Option_Variable()->Int(), MCM::NONE, true);
    }

    void Member_t::Build_Statistics()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);
        Actor_t* actor = party_member->Actor();
        NPCP_ASSERT(actor);
        Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
        NPCP_ASSERT(values);

        mcm_main->Cursor_Position(5);
        mcm_main->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

        mcm_main->Add_Header_Option("Statistics: ");

        auto build_stat = [&](Variable_t* variable, String_t text, Actor_Value_t actor_value) -> void
        {
            Int_t value = static_cast<Int_t>(values->Get_Actor_Value(actor_value));
            variable->Int(mcm_main->Add_Text_Option(text, std::to_string(value).c_str()));
        };

        build_stat(Health_Attribute_Option_Variable(), " Health ", Actor_Value_t::HEALTH);
        build_stat(Magicka_Attribute_Option_Variable(), " Magicka ", Actor_Value_t::MAGICKA);
        build_stat(Stamina_Attribute_Option_Variable(), " Stamina ", Actor_Value_t::STAMINA);

        build_stat(One_Handed_Skill_Option_Variable(), " One Handed ", Actor_Value_t::ONE_HANDED);
        build_stat(Two_Handed_Skill_Option_Variable(), " Two Handed ", Actor_Value_t::TWO_HANDED);
        build_stat(Block_Skill_Option_Variable(), " Block ", Actor_Value_t::BLOCK);
        build_stat(Heavy_Armor_Skill_Option_Variable(), " Heavy Armor ", Actor_Value_t::HEAVY_ARMOR);
        build_stat(Light_Armor_Skill_Option_Variable(), " Light Armor ", Actor_Value_t::LIGHT_ARMOR);
        build_stat(Smithing_Skill_Option_Variable(), " Smithing ", Actor_Value_t::SMITHING);

        build_stat(Destruction_Skill_Option_Variable(), " Destruction ", Actor_Value_t::DESTRUCTION);
        build_stat(Restoration_Skill_Option_Variable(), " Restoration ", Actor_Value_t::RESTORATION);
        build_stat(Conjuration_Skill_Option_Variable(), " Conjuration ", Actor_Value_t::CONJURATION);
        build_stat(Alteration_Skill_Option_Variable(), " Alteration ", Actor_Value_t::ALTERATION);
        build_stat(Illusion_Skill_Option_Variable(), " Illusion ", Actor_Value_t::ILLUSION);
        build_stat(Enchanting_Skill_Option_Variable(), " Enchanting ", Actor_Value_t::ENCHANTING);

        build_stat(Marksman_Skill_Option_Variable(), " Marksman ", Actor_Value_t::MARKSMAN);
        build_stat(Sneak_Skill_Option_Variable(), " Sneak ", Actor_Value_t::SNEAK);
        build_stat(Alchemy_Skill_Option_Variable(), " Alchemy ", Actor_Value_t::ALCHEMY);
        build_stat(Lockpicking_Skill_Option_Variable(), " Lockpicking ", Actor_Value_t::LOCKPICKING);
        build_stat(Pickpocket_Skill_Option_Variable(), " Pickpocket ", Actor_Value_t::PICKPOCKET);
        build_stat(Speechcraft_Skill_Option_Variable(), " Speechcraft ", Actor_Value_t::SPEECHCRAFT);

        Race_Option_Variable()->Int(
            mcm_main->Add_Text_Option(" Race ", party_member->Race())
        );
        Relationship_Rank_Option_Variable()->Int(
            mcm_main->Add_Text_Option(" Relationship Rank ", party_member->Relationship_Rank_String())
        );
        Worldspace_Option_Variable()->Int(
            mcm_main->Add_Text_Option(" Worldspace ", party_member->Worldspace_String())
        );
        Location_Option_Variable()->Int(
            mcm_main->Add_Text_Option(" Location ", party_member->Location_String())
        );
        Cell_Option_Variable()->Int(
            mcm_main->Add_Text_Option(" Cell ", party_member->Cell_String())
        );
    }

    void Member_t::Update_Statistics()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);
        Actor_t* actor = party_member->Actor();
        NPCP_ASSERT(actor);
        Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
        NPCP_ASSERT(values);

        auto update_stat = [&](Variable_t* variable, Actor_Value_t actor_value, Bool_t do_render) -> void
        {
            Int_t value = static_cast<Int_t>(values->Get_Actor_Value(actor_value));
            mcm_main->Text_Option_Value(variable->Int(), std::to_string(value).c_str(), do_render);
        };

        update_stat(Health_Attribute_Option_Variable(), Actor_Value_t::HEALTH, false);
        update_stat(Magicka_Attribute_Option_Variable(), Actor_Value_t::MAGICKA, false);
        update_stat(Stamina_Attribute_Option_Variable(), Actor_Value_t::STAMINA, false);

        update_stat(One_Handed_Skill_Option_Variable(), Actor_Value_t::ONE_HANDED, false);
        update_stat(Two_Handed_Skill_Option_Variable(), Actor_Value_t::TWO_HANDED, false);
        update_stat(Block_Skill_Option_Variable(), Actor_Value_t::BLOCK, false);
        update_stat(Heavy_Armor_Skill_Option_Variable(), Actor_Value_t::HEAVY_ARMOR, false);
        update_stat(Light_Armor_Skill_Option_Variable(), Actor_Value_t::LIGHT_ARMOR, false);
        update_stat(Smithing_Skill_Option_Variable(), Actor_Value_t::SMITHING, false);

        update_stat(Destruction_Skill_Option_Variable(), Actor_Value_t::DESTRUCTION, false);
        update_stat(Restoration_Skill_Option_Variable(), Actor_Value_t::RESTORATION, false);
        update_stat(Conjuration_Skill_Option_Variable(), Actor_Value_t::CONJURATION, false);
        update_stat(Alteration_Skill_Option_Variable(), Actor_Value_t::ALTERATION, false);
        update_stat(Illusion_Skill_Option_Variable(), Actor_Value_t::ILLUSION, false);
        update_stat(Enchanting_Skill_Option_Variable(), Actor_Value_t::ENCHANTING, false);

        update_stat(Marksman_Skill_Option_Variable(), Actor_Value_t::MARKSMAN, false);
        update_stat(Sneak_Skill_Option_Variable(), Actor_Value_t::SNEAK, false);
        update_stat(Alchemy_Skill_Option_Variable(), Actor_Value_t::ALCHEMY, false);
        update_stat(Lockpicking_Skill_Option_Variable(), Actor_Value_t::LOCKPICKING, false);
        update_stat(Pickpocket_Skill_Option_Variable(), Actor_Value_t::PICKPOCKET, false);
        update_stat(Speechcraft_Skill_Option_Variable(), Actor_Value_t::SPEECHCRAFT, false);

        mcm_main->Text_Option_Value(Race_Option_Variable()->Int(), party_member->Race(), false);
        mcm_main->Text_Option_Value(Relationship_Rank_Option_Variable()->Int(), party_member->Relationship_Rank_String(), false);
        mcm_main->Text_Option_Value(Worldspace_Option_Variable()->Int(), party_member->Worldspace_String(), false);
        mcm_main->Text_Option_Value(Location_Option_Variable()->Int(), party_member->Location_String(), false);
        mcm_main->Text_Option_Value(Cell_Option_Variable()->Int(), party_member->Cell_String(), true);
    }

    void Member_t::Go_Back()
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER) {
            MCM::Members_t::Self()->Review_Members();
        } else if (current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Members_t::Self()->Review_Filter_Members();
        } else if (current_view == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Followers_t::Self()->Review_Followers();
        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Mannequins_t::Self()->Review_Mannequins();
        }
        Main()->Reset_Page();
    }

    void Member_t::On_Build_Page()
    {
        Party::Member_t* member = Party_Member();
        if (member) {
            String_t member_name = member->Name();
            Main_t* mcm = Main();

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

            Int_t current_view = Current_View();
            if (current_view == CODES::VIEW::MEMBERS_MEMBER) {
                mcm->Title_Text((std::string("Member: ") + member_name.data).c_str());
            } else if (current_view == CODES::VIEW::FOLLOWERS_MEMBER) {
                mcm->Title_Text((std::string("Follower: ") + member_name.data).c_str());
            } else if (current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
                mcm->Title_Text((std::string("Filtered Member: ") + member_name.data).c_str());
            } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
                mcm->Title_Text((std::string("Mannequin: ") + member_name.data).c_str());
            }

            Rename_Option_Variable()->Int(
                mcm->Add_Input_Option((std::string(member_name.data) + " ").c_str(), " Rename ")
            );
            Back_Option_Variable()->Int(
                mcm->Add_Text_Option("                            Go Back", "")
            );

            if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
                if (Party::Members_t::Self()->Count_Filled() > 1) {
                    Previous_Option_Variable()->Int(
                        mcm->Add_Text_Option("                      Previous Member", "")
                    );
                    Next_Option_Variable()->Int(
                        mcm->Add_Text_Option("                        Next Member", "")
                    );
                } else {
                    Previous_Option_Variable()->Int(
                        mcm->Add_Text_Option("                      Previous Member", "", MCM::DISABLE)
                    );
                    Next_Option_Variable()->Int(
                        mcm->Add_Text_Option("                        Next Member", "", MCM::DISABLE)
                    );
                }
            } else if (current_view == CODES::VIEW::FOLLOWERS_MEMBER) {
                if (Party::Followers_t::Self()->Count_Filled() > 1) {
                    Previous_Option_Variable()->Int(
                        mcm->Add_Text_Option("                      Previous Follower", "")
                    );
                    Next_Option_Variable()->Int(
                        mcm->Add_Text_Option("                        Next Follower", "")
                    );
                } else {
                    Previous_Option_Variable()->Int(
                        mcm->Add_Text_Option("                      Previous Follower", "", MCM::DISABLE)
                    );
                    Next_Option_Variable()->Int(
                        mcm->Add_Text_Option("                        Next Follower", "", MCM::DISABLE)
                    );
                }
            }

            Build_Commands();
            Build_Statistics();
        }
    }

    void Member_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        using namespace Modules::Control;

        MCM::Main_t* mcm = Main();

        Party::Member_t* member = Party_Member();
        if (member) {
            Actor_t* actor = member->Actor();
            if (option == Back_Option_Variable()->Int()) {
                mcm->Disable(option);
                Go_Back();
                mcm->Return_Latent(user_callback);
            } else if (option == Previous_Option_Variable()->Int()) {
                mcm->Disable(option);
                Int_t current_view = Current_View();
                if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
                    MCM::Members_t::Self()->Request_Previous_Member();
                } else if (current_view == CODES::VIEW::FOLLOWERS_MEMBER) {
                    MCM::Followers_t::Self()->Request_Previous_Follower();
                }
                mcm->Reset_Page();
                mcm->Return_Latent(user_callback);
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Disable(option);
                Int_t current_view = Current_View();
                if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
                    MCM::Members_t::Self()->Request_Next_Member();
                } else if (current_view == CODES::VIEW::FOLLOWERS_MEMBER) {
                    MCM::Followers_t::Self()->Request_Next_Follower();
                }
                mcm->Reset_Page();
                mcm->Return_Latent(user_callback);

            } else if (option == Summon_Option_Variable()->Int()) {
                Commands_t::Self()->Summon(actor, false);
                Update_Commands();
                mcm->Flicker(option);
                mcm->Return_Latent(user_callback);
            } else if (option == Goto_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct Callback : public Callback_t<> {
                    Actor_t* actor;
                    UCallback_t* user_callback;
                    Callback(Actor_t* actor, UCallback_t* user_callback) :
                        actor(actor), user_callback(user_callback)
                    {
                    }
                    void operator()()
                    {
                        Commands_t::Self()->Goto(actor);
                        MCM::Main_t::Self()->Return_Latent(user_callback);
                    }
                };
                Main()->Close_Menus(new Callback(actor, user_callback));
            } else if (option == Pack_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct Callback : public Callback_t<> {
                    Actor_t* actor;
                    UCallback_t* user_callback;
                    Callback(Actor_t* actor, UCallback_t* user_callback) :
                        actor(actor), user_callback(user_callback)
                    {
                    }
                    void operator()()
                    {
                        Commands_t::Self()->Open_Pack(actor);
                        MCM::Main_t::Self()->Return_Latent(user_callback);
                    }
                };
                Main()->Close_Menus(new Callback(actor, user_callback));
            } else if (option == Stash_Option_Variable()->Int()) {
                Commands_t::Self()->Stash(actor);
                Update_Commands();
                mcm->Flicker(option);
                mcm->Return_Latent(user_callback);

            } else if (option == Settle_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Settle(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Resettle_Option_Variable()->Int()) {
                Commands_t::Self()->Resettle(actor, false);
                Update_Commands();
                mcm->Flicker(option);
                mcm->Return_Latent(user_callback);
            } else if (option == Unsettle_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Unsettle(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Open_Settler_Option_Variable()->Int()) {
                mcm->Disable(option);
                Settlers_t::Self()->View_Settler(static_cast<Party::Settler_t*>(member));
                mcm->Reset_Page(Main_t::SETTLERS_PAGE);
                mcm->Return_Latent(user_callback);

            } else if (option == Immobilize_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Immobilize(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Mobilize_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Mobilize(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Paralyze_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Paralyze(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Unparalyze_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Unparalyze(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);

            } else if (option == Follow_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct Callback : public Callback_t<Int_t, Party::Follower_t*> {
                    MCM::Member_t* self;
                    UCallback_t* user_callback;
                    Callback(MCM::Member_t* self, UCallback_t* user_callback) :
                        self(self), user_callback(user_callback)
                    {
                    }
                    void operator()(Int_t code, Party::Follower_t* follower)
                    {
                        self->Update_Commands();
                        self->Update_Statistics();
                        MCM::Main_t::Self()->Return_Latent(user_callback);
                    }
                };
                Callback_t<Int_t, Party::Follower_t*>* callback = new Callback(this, user_callback);
                Commands_t::Self()->Follow(actor, &callback);
            } else if (option == Unfollow_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct Callback : public Callback_t<Int_t, Party::Member_t*> {
                    MCM::Member_t* self;
                    UCallback_t* user_callback;
                    Callback(MCM::Member_t* self, UCallback_t* user_callback) :
                        self(self), user_callback(user_callback)
                    {
                    }
                    void operator()(Int_t code, Party::Member_t* member)
                    {
                        Int_t current_view = self->Current_View();
                        if (current_view == CODES::VIEW::FOLLOWERS_MEMBER) {
                            self->Go_Back();
                        } else {
                            self->Update_Commands();
                            self->Update_Statistics();
                        }
                        MCM::Main_t::Self()->Return_Latent(user_callback);
                    }
                };
                Callback_t<Int_t, Party::Member_t*>* callback = new Callback(this, user_callback);
                Commands_t::Self()->Unfollow(actor, &callback);
            } else if (option == Sneak_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Sneak(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Unsneak_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Unsneak(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);

            } else if (option == Rating_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Cycle_Rating(actor, false);
                Update_Commands();
                mcm->Return_Latent(user_callback);
            } else if (option == Stylize_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Cycle_Style(actor, false);
                Update_Commands();
                Update_Statistics();
                mcm->Return_Latent(user_callback);
            } else if (option == Vitalize_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Cycle_Vitality(actor, false);
                Update_Commands();
                Update_Statistics();
                mcm->Return_Latent(user_callback);

            } else if (option == Resurrect_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Resurrect(actor);
                Update_Commands();
                Update_Statistics();
                mcm->Return_Latent(user_callback);

            } else if (option == Clone_Option_Variable()->Int()) {
                Commands_t::Self()->Clone(actor);
                Update_Commands();
                mcm->Flicker(option);
                mcm->Return_Latent(user_callback);
            } else if (option == Unclone_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Unclone(actor);
                Go_Back();
                mcm->Return_Latent(user_callback);
            } else if (option == Unmember_Option_Variable()->Int()) {
                mcm->Disable(option);
                Commands_t::Self()->Unmember(actor);
                Go_Back();
                mcm->Return_Latent(user_callback);
            } else {
                mcm->Return_Latent(user_callback);
            }
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Member_t::On_Option_Menu_Open(Int_t option)
    {
        MCM::Main_t* mcm = Main();

        if (option == Outfit2_Option_Variable()->Int()) {
            Vector_t<String_t> values;
            values.reserve(8);

            values.push_back(" Current ");
            values.push_back(" Member ");
            values.push_back(" Settler ");
            if (Party::Player_t::Self()->Is_Vampire()) {
                values.push_back(" Thrall ");
            }
            values.push_back(" Follower ");
            values.push_back(" Immobile ");
            values.push_back(" Vanilla ");
            values.push_back(" Default ");

            mcm->Menu_Dialog_Values(values);
        }
    }

    void Member_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        MCM::Main_t* mcm = Main();

        if (option == Outfit2_Option_Variable()->Int()) {
            if (idx > -1) {
                Party::Member_t* member = Party_Member();
                if (member) {
                    struct Callback : public Callback_t<> {
                        Party::Member_t* member;
                        Int_t idx;
                        Callback(Party::Member_t* member, Int_t idx) :
                            member(member), idx(idx)
                        {
                        }
                        void operator()()
                        {
                            if (!Party::Player_t::Self()->Is_Vampire() && idx > 2) {
                                idx += 1;
                            }
                            if (idx == 0) {
                                Modules::Control::Commands_t::Self()->Change_Current_Outfit2(member->Actor());
                            } else if (idx == 1) {
                                Modules::Control::Commands_t::Self()->Change_Member_Outfit2(member->Actor());
                            } else if (idx == 2) {
                                Modules::Control::Commands_t::Self()->Change_Settler_Outfit2(member->Actor());
                            } else if (idx == 3) {
                                Modules::Control::Commands_t::Self()->Change_Thrall_Outfit2(member->Actor());
                            } else if (idx == 4) {
                                Modules::Control::Commands_t::Self()->Change_Follower_Outfit2(member->Actor());
                            } else if (idx == 5) {
                                Modules::Control::Commands_t::Self()->Change_Immobile_Outfit2(member->Actor());
                            } else if (idx == 6) {
                                Modules::Control::Commands_t::Self()->Change_Vanilla_Outfit2(member->Actor());
                            } else if (idx == 7) {
                                Modules::Control::Commands_t::Self()->Change_Default_Outfit2(member->Actor());
                            }
                        }
                    };
                    mcm->Close_Menus(new Callback(member, idx));
                }
            }
        }
    }

    void Member_t::On_Option_Slider_Open(Int_t option)
    {
    }

    void Member_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
    }

    void Member_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        MCM::Main_t* mcm = Main();

        if (option == Rename_Option_Variable()->Int()) {
            Party::Member_t* member = Party_Member();
            if (member && value.data && value.data[0]) {
                member->Rename(value);
                mcm->Reset_Page();
            }
        }
    }

    void Member_t::On_Option_Keymap_Change(Int_t option,
                                           Int_t key_code,
                                           String_t conflict,
                                           String_t conflicting_mod,
                                           Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Member_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Member_t::On_Option_Highlight(Int_t option)
    {
        MCM::Main_t* mcm = Main();
        Party::Member_t* member = Party_Member();
        if (member) {
            const char* name = member->Name();

            if (option == Rename_Option_Variable()->Int()) {
                mcm->Info_Text("Rename this member.");
            } else if (option == Back_Option_Variable()->Int()) {
                mcm->Info_Text("Go back to Members");
            } else if (option == Previous_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Previous Member");
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Next Member");

            } else if (option == Summon_Option_Variable()->Int()) {
                mcm->Info_Text("Summon this member to you.");
            } else if (option == Goto_Option_Variable()->Int()) {
                mcm->Info_Text("Goto this member.");
            } else if (option == Pack_Option_Variable()->Int()) {
                mcm->Info_Text("Pack items in this member's inventory.");
            } else if (option == Stash_Option_Variable()->Int()) {
                mcm->Info_Text("Stash all of the items in the member's pack, into community chests.");
            } else if (option == Outfit2_Option_Variable()->Int()) {
                mcm->Info_Text("Choose what this npc will wear in one of their outfits.");

            } else if (option == Settle_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Settle ", name));
            } else if (option == Resettle_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Resettle ", name));
            } else if (option == Unsettle_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Unsettle ", name));
            } else if (option == Open_Settler_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Open ", name, "'s settler menu."));

            } else if (option == Immobilize_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Immobilize ", name));
            } else if (option == Mobilize_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Mobilize ", name));

            } else if (option == Paralyze_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Paralyze ", name));
            } else if (option == Unparalyze_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Unparalyze ", name));

            } else if (option == Follow_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Have ", name, " follow you."));
            } else if (option == Unfollow_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Have ", name, " stop following you."));

            } else if (option == Sneak_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Have ", name, " sneak."));
            } else if (option == Unsneak_Option_Variable()->Int()) {
                mcm->Info_Text(mcm->Concat("Have ", name, " stop sneaking."));

            } else if (option == Resurrect_Option_Variable()->Int()) {
                mcm->Info_Text("Resurrect this dead member.");

            } else if (option == Rating_Option_Variable()->Int()) {
                mcm->Info_Text("Rate this member. Causes them to sort higher, and can be used in the filter.");
            } else if (option == Stylize_Option_Variable()->Int()) {
                mcm->Info_Text("Change the fighting style of this member.");
            } else if (option == Vitalize_Option_Variable()->Int()) {
                mcm->Info_Text("Change how this member lives or dies.");

            } else if (option == Clone_Option_Variable()->Int()) {
                mcm->Info_Text("Clone this member.");
            } else if (option == Unclone_Option_Variable()->Int()) {
                mcm->Info_Text("Unclone and unmember this member.");
            } else if (option == Unmember_Option_Variable()->Int()) {
                mcm->Info_Text("Unmember this member.");
            }
        }
    }

    void Member_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Member_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
