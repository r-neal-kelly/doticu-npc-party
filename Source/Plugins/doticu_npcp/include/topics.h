/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Modules { namespace Control {

    using namespace Papyrus;

    class Topics_t : public Topic_Info_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        // NPC
        void Member(Reference_t* ref);
        void Unmember(Reference_t* ref);
        void Clone(Reference_t* ref);
        void Unclone(Reference_t* ref);

        // Member
        void Open_Pack(Reference_t* ref);
        void Stash(Reference_t* ref);
        void Mobilize(Reference_t* ref);
        void Immobilize(Reference_t* ref);
        void Settle(Reference_t* ref);
        void Resettle(Reference_t* ref);
        void Unsettle(Reference_t* ref);
        void Enthrall(Reference_t* ref);
        void Unthrall(Reference_t* ref);
        void Paralyze(Reference_t* ref);
        void Deanimate(Reference_t* ref);
        void Follow(Reference_t* ref);
        void Unfollow(Reference_t* ref);
        void Stylize_Default(Reference_t* ref);
        void Stylize_Warrior(Reference_t* ref);
        void Stylize_Mage(Reference_t* ref);
        void Stylize_Archer(Reference_t* ref);
        void Stylize_Coward(Reference_t* ref);
        void Vitalize_Mortal(Reference_t* ref);
        void Vitalize_Protected(Reference_t* ref);
        void Vitalize_Essential(Reference_t* ref);
        void Vitalize_Invulnerable(Reference_t* ref);
        void Change_Member_Outfit2(Reference_t* ref);
        void Change_Immobile_Outfit2(Reference_t* ref);
        void Change_Settler_Outfit2(Reference_t* ref);
        void Change_Thrall_Outfit2(Reference_t* ref);
        void Change_Follower_Outfit2(Reference_t* ref);
        void Change_Vanilla_Outfit2(Reference_t* ref);
        void Change_Default_Outfit2(Reference_t* ref);
        void Change_Current_Outfit2(Reference_t* ref);
        void Show_Style(Reference_t* ref);
        void Show_Vitality(Reference_t* ref);
        void Show_Outfit2(Reference_t* ref);

        // Follower
        void Sneak(Reference_t* ref);
        void Unsneak(Reference_t* ref);
        void Saddle(Reference_t* ref);
        void Unsaddle(Reference_t* ref);
        void Retreat(Reference_t* ref);
        void Unretreat(Reference_t* ref);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
