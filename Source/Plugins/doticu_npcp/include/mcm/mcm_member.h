/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Member_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Member_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable();
        Variable_t* Party_Member_Variable();

        Variable_t* Rename_Option_Variable();
        Variable_t* Back_Option_Variable();
        Variable_t* Previous_Option_Variable();
        Variable_t* Next_Option_Variable();
        Variable_t* Unmember_Option_Variable();
        Variable_t* Clone_Option_Variable();
        Variable_t* Unclone_Option_Variable();
        Variable_t* Mobilize_Option_Variable();
        Variable_t* Immobilize_Option_Variable();
        Variable_t* Settle_Option_Variable();
        Variable_t* Resettle_Option_Variable();
        Variable_t* Unsettle_Option_Variable();
        Variable_t* Enthrall_Option_Variable();
        Variable_t* Unthrall_Option_Variable();
        Variable_t* Paralyze_Option_Variable();
        Variable_t* Unparalyze_Option_Variable();
        Variable_t* Stylize_Option_Variable();
        Variable_t* Vitalize_Option_Variable();
        Variable_t* Outfit2_Option_Variable();
        Variable_t* Pack_Option_Variable();
        Variable_t* Stash_Option_Variable();
        Variable_t* Summon_Option_Variable();
        Variable_t* Goto_Option_Variable();
        Variable_t* Rating_Option_Variable();
        Variable_t* Resurrect_Option_Variable();
        Variable_t* Follow_Option_Variable();
        Variable_t* Unfollow_Option_Variable();
        Variable_t* Sneak_Option_Variable();
        Variable_t* Unsneak_Option_Variable();

        Variable_t* Health_Attribute_Option_Variable();
        Variable_t* Magicka_Attribute_Option_Variable();
        Variable_t* Stamina_Attribute_Option_Variable();

        Variable_t* One_Handed_Skill_Option_Variable();
        Variable_t* Two_Handed_Skill_Option_Variable();
        Variable_t* Block_Skill_Option_Variable();
        Variable_t* Heavy_Armor_Skill_Option_Variable();
        Variable_t* Light_Armor_Skill_Option_Variable();
        Variable_t* Smithing_Skill_Option_Variable();

        Variable_t* Destruction_Skill_Option_Variable();
        Variable_t* Restoration_Skill_Option_Variable();
        Variable_t* Conjuration_Skill_Option_Variable();
        Variable_t* Alteration_Skill_Option_Variable();
        Variable_t* Illusion_Skill_Option_Variable();
        Variable_t* Enchanting_Skill_Option_Variable();

        Variable_t* Marksman_Skill_Option_Variable();
        Variable_t* Sneak_Skill_Option_Variable();
        Variable_t* Alchemy_Skill_Option_Variable();
        Variable_t* Lockpicking_Skill_Option_Variable();
        Variable_t* Pickpocket_Skill_Option_Variable();
        Variable_t* Speechcraft_Skill_Option_Variable();

        Variable_t* Race_Option_Variable();
        Variable_t* Relationship_Rank_Option_Variable();

        Int_t Current_View();
        Party::Member_t* Party_Member();

        void View_Members_Member(Party::Member_t* member);
        void View_Filter_Members_Member(Party::Member_t* member);
        void Build_Page();
        void Build_Commands();
        void Update_Commands();
        void Build_Statistics();
        void Update_Statistics();
        void Go_Back();

        void On_Option_Select(Int_t option);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
