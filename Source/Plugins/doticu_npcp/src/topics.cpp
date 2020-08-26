/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "papyrus.inl"
#include "utils.h"

#include "topics.h"
#include "commands.h"

namespace doticu_npcp { namespace Modules { namespace Control {

    String_t Topics_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_topics");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Topics_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Variable_t* Topics_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    #define TOPIC(METHOD_)                                              \
    M                                                                   \
        if (ref->formType == kFormType_Character) {                     \
            Commands_t::Self()->METHOD_(static_cast<Actor_t*>(ref));    \
        }                                                               \
    W

    // NPC
    void Topics_t::Member(Reference_t* ref) { TOPIC(Member); }
    void Topics_t::Unmember(Reference_t* ref) { TOPIC(Unmember); }
    void Topics_t::Clone(Reference_t* ref) { TOPIC(Clone); }
    void Topics_t::Unclone(Reference_t* ref) { TOPIC(Unclone); }

    // Member
    void Topics_t::Open_Pack(Reference_t* ref) { TOPIC(Open_Pack); }
    void Topics_t::Stash(Reference_t* ref) { TOPIC(Stash); }
    void Topics_t::Mobilize(Reference_t* ref) { TOPIC(Mobilize); }
    void Topics_t::Immobilize(Reference_t* ref) { TOPIC(Immobilize); }
    void Topics_t::Settle(Reference_t* ref) { TOPIC(Settle); }
    void Topics_t::Resettle(Reference_t* ref) { TOPIC(Resettle); }
    void Topics_t::Unsettle(Reference_t* ref) { TOPIC(Unsettle); }
    void Topics_t::Enthrall(Reference_t* ref) { TOPIC(Enthrall); }
    void Topics_t::Unthrall(Reference_t* ref) { TOPIC(Unthrall); }
    void Topics_t::Paralyze(Reference_t* ref) { TOPIC(Paralyze); }
    void Topics_t::Deanimate(Reference_t* ref) { TOPIC(Deanimate); }
    void Topics_t::Follow(Reference_t* ref) { TOPIC(Follow); }
    void Topics_t::Unfollow(Reference_t* ref) { TOPIC(Unfollow); }
    void Topics_t::Stylize_Default(Reference_t* ref) { TOPIC(Stylize_Default); }
    void Topics_t::Stylize_Warrior(Reference_t* ref) { TOPIC(Stylize_Warrior); }
    void Topics_t::Stylize_Mage(Reference_t* ref) { TOPIC(Stylize_Mage); }
    void Topics_t::Stylize_Archer(Reference_t* ref) { TOPIC(Stylize_Archer); }
    void Topics_t::Stylize_Coward(Reference_t* ref) { TOPIC(Stylize_Coward); }
    void Topics_t::Vitalize_Mortal(Reference_t* ref) { TOPIC(Vitalize_Mortal); }
    void Topics_t::Vitalize_Protected(Reference_t* ref) { TOPIC(Vitalize_Protected); }
    void Topics_t::Vitalize_Essential(Reference_t* ref) { TOPIC(Vitalize_Essential); }
    void Topics_t::Vitalize_Invulnerable(Reference_t* ref) { TOPIC(Vitalize_Invulnerable); }
    void Topics_t::Change_Member_Outfit2(Reference_t* ref) { TOPIC(Change_Member_Outfit2); }
    void Topics_t::Change_Immobile_Outfit2(Reference_t* ref) { TOPIC(Change_Immobile_Outfit2); }
    void Topics_t::Change_Settler_Outfit2(Reference_t* ref) { TOPIC(Change_Settler_Outfit2); }
    void Topics_t::Change_Thrall_Outfit2(Reference_t* ref) { TOPIC(Change_Thrall_Outfit2); }
    void Topics_t::Change_Follower_Outfit2(Reference_t* ref) { TOPIC(Change_Follower_Outfit2); }
    void Topics_t::Change_Vanilla_Outfit2(Reference_t* ref) { TOPIC(Change_Vanilla_Outfit2); }
    void Topics_t::Change_Default_Outfit2(Reference_t* ref) { TOPIC(Change_Default_Outfit2); }
    void Topics_t::Change_Current_Outfit2(Reference_t* ref) { TOPIC(Change_Current_Outfit2); }
    void Topics_t::Show_Style(Reference_t* ref) { TOPIC(Show_Style); }
    void Topics_t::Show_Vitality(Reference_t* ref) { TOPIC(Show_Vitality); }
    void Topics_t::Show_Outfit2(Reference_t* ref) { TOPIC(Show_Outfit2); }

    // Follower
    void Topics_t::Sneak(Reference_t* ref) { TOPIC(Sneak); }
    void Topics_t::Unsneak(Reference_t* ref) { TOPIC(Unsneak); }
    void Topics_t::Saddle(Reference_t* ref) { TOPIC(Saddle); }
    void Topics_t::Unsaddle(Reference_t* ref) { TOPIC(Unsaddle); }
    void Topics_t::Retreat(Reference_t* ref) { TOPIC(Retreat); }
    void Topics_t::Unretreat(Reference_t* ref) { TOPIC(Unretreat); }

    #undef TOPIC

    void Topics_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Topics_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        // NPC
        METHOD("Member", 1, void, Member, Reference_t*);
        METHOD("Unmember", 1, void, Unmember, Reference_t*);
        METHOD("Clone", 1, void, Clone, Reference_t*);
        METHOD("Unclone", 1, void, Unclone, Reference_t*);

        // Member
        METHOD("Pack", 1, void, Open_Pack, Reference_t*);
        METHOD("Stash", 1, void, Stash, Reference_t*);
        METHOD("Mobilize", 1, void, Mobilize, Reference_t*);
        METHOD("Immobilize", 1, void, Immobilize, Reference_t*);
        METHOD("Settle", 1, void, Settle, Reference_t*);
        METHOD("Resettle", 1, void, Resettle, Reference_t*);
        METHOD("Unsettle", 1, void, Unsettle, Reference_t*);
        METHOD("Enthrall", 1, void, Enthrall, Reference_t*);
        METHOD("Unthrall", 1, void, Unthrall, Reference_t*);
        METHOD("Paralyze", 1, void, Paralyze, Reference_t*);
        METHOD("Deanimate", 1, void, Deanimate, Reference_t*);
        METHOD("Follow", 1, void, Follow, Reference_t*);
        METHOD("Unfollow", 1, void, Unfollow, Reference_t*);
        METHOD("Stylize_Default", 1, void, Stylize_Default, Reference_t*);
        METHOD("Stylize_Warrior", 1, void, Stylize_Warrior, Reference_t*);
        METHOD("Stylize_Mage", 1, void, Stylize_Mage, Reference_t*);
        METHOD("Stylize_Archer", 1, void, Stylize_Archer, Reference_t*);
        METHOD("Stylize_Coward", 1, void, Stylize_Coward, Reference_t*);
        METHOD("Vitality_Mortal", 1, void, Vitalize_Mortal, Reference_t*);
        METHOD("Vitality_Protected", 1, void, Vitalize_Protected, Reference_t*);
        METHOD("Vitality_Essential", 1, void, Vitalize_Essential, Reference_t*);
        METHOD("Vitality_Invulnerable", 1, void, Vitalize_Invulnerable, Reference_t*);
        METHOD("Outfit_Member", 1, void, Change_Member_Outfit2, Reference_t*);
        METHOD("Outfit_Immobile", 1, void, Change_Immobile_Outfit2, Reference_t*);
        METHOD("Outfit_Settler", 1, void, Change_Settler_Outfit2, Reference_t*);
        METHOD("Outfit_Thrall", 1, void, Change_Thrall_Outfit2, Reference_t*);
        METHOD("Outfit_Follower", 1, void, Change_Follower_Outfit2, Reference_t*);
        METHOD("Outfit_Vanilla", 1, void, Change_Vanilla_Outfit2, Reference_t*);
        METHOD("Outfit_Default", 1, void, Change_Default_Outfit2, Reference_t*);
        METHOD("Outfit_Current", 1, void, Change_Current_Outfit2, Reference_t*);
        METHOD("Style_Show", 1, void, Show_Style, Reference_t*);
        METHOD("Vitality_Show", 1, void, Show_Vitality, Reference_t*);
        METHOD("Outfit_Show", 1, void, Show_Outfit2, Reference_t*);

        // Follower
        METHOD("Sneak", 1, void, Sneak, Reference_t*);
        METHOD("Unsneak", 1, void, Unsneak, Reference_t*);
        METHOD("Saddle", 1, void, Saddle, Reference_t*);
        METHOD("Unsaddle", 1, void, Unsaddle, Reference_t*);
        METHOD("Retreat", 1, void, Retreat, Reference_t*);
        METHOD("Unretreat", 1, void, Unretreat, Reference_t*);

        #undef METHOD
    }

}}}
