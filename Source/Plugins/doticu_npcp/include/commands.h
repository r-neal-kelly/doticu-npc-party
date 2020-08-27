/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Modules { namespace Control {

    using namespace Papyrus;

    class Commands_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Commands_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        void Log_Note(const char* note, Bool_t do_log = true);
        void Log_Note(const char* part_1, const char* part_2, Bool_t do_log = true);
        void Log_Note(const char* part_1, const char* part_2, const char* part_3, Bool_t do_log = true);
        void Log_Note(const char* part_1, const char* part_2, const char* part_3, const char* part_4, Bool_t do_log = true);
        void Log_Error(const char* error, Int_t code, Bool_t do_log = true);
        void Log_Error(const char* part_1, const char* part_2, Int_t code, Bool_t do_log = true);

        // NPC
        void Log_Member(Int_t code, const char* name);
        void Log_Follow(Int_t code, const char* name);

        void Member(Actor_t* actor);
        void Unmember(Actor_t* actor);
        void Clone(Actor_t* actor);
        void Unclone(Actor_t* actor);
        void Start_Move(Actor_t* actor);
        void Stop_Move(Actor_t* actor);
        void Toggle_Member(Actor_t* actor);
        void Toggle_Clone(Actor_t* actor);
        void Toggle_Move(Actor_t* actor);
        void Has_Base(Actor_t* actor);
        void Has_Head(Actor_t* actor);
        void Count_Base(Actor_t* actor);
        void Count_Heads(Actor_t* actor);

        // Member
        void Summon(Actor_t* actor);
        void Goto(Actor_t* actor);
        void Open_Pack(Actor_t* actor);
        void Stash(Actor_t* actor);
        void Resurrect(Actor_t* actor);
        void Kill(Actor_t* actor);
        void Mobilize(Actor_t* actor);
        void Immobilize(Actor_t* actor);
        void Settle(Actor_t* actor);
        void Resettle(Actor_t* actor);
        void Unsettle(Actor_t* actor);
        void Enthrall(Actor_t* actor);
        void Unthrall(Actor_t* actor);
        void Paralyze(Actor_t* actor);
        void Unparalyze(Actor_t* actor);
        void Mannequinize(Actor_t* actor, Reference_t* marker);
        void Unmannequinize(Actor_t* actor);
        void Expo(Int_t expoee_id, Reference_t* marker);
        void Unexpo(Int_t expoee_id);
        void Reanimate(Actor_t* actor);
        void Deanimate(Actor_t* actor);
        void Follow(Actor_t* actor);
        void Unfollow(Actor_t* actor);
        void Stylize_Default(Actor_t* actor);
        void Stylize_Warrior(Actor_t* actor);
        void Stylize_Mage(Actor_t* actor);
        void Stylize_Archer(Actor_t* actor);
        void Stylize_Coward(Actor_t* actor);
        void Vitalize_Mortal(Actor_t* actor);
        void Vitalize_Protected(Actor_t* actor);
        void Vitalize_Essential(Actor_t* actor);
        void Vitalize_Invulnerable(Actor_t* actor);
        void Change_Member_Outfit2(Actor_t* actor);
        void Change_Immobile_Outfit2(Actor_t* actor);
        void Change_Settler_Outfit2(Actor_t* actor);
        void Change_Thrall_Outfit2(Actor_t* actor);
        void Change_Follower_Outfit2(Actor_t* actor);
        void Change_Vanilla_Outfit2(Actor_t* actor);
        void Change_Default_Outfit2(Actor_t* actor);
        void Change_Current_Outfit2(Actor_t* actor);
        void Toggle_Immobile(Actor_t* actor);
        void Toggle_Settler(Actor_t* actor);
        void Toggle_Thrall(Actor_t* actor);
        void Toggle_Paralyzed(Actor_t* actor);
        void Toggle_Mannequin(Actor_t* actor, Reference_t* marker);
        void Toggle_Expoee(Int_t expoee_id, Reference_t* marker);
        void Toggle_Reanimated(Actor_t* actor);
        void Toggle_Follower(Actor_t* actor);
        void Show_Style(Actor_t* actor);
        void Show_Vitality(Actor_t* actor);
        void Show_Outfit2(Actor_t* actor);
        void Cycle_Style(Actor_t* actor);
        void Cycle_Vitality(Actor_t* actor);

        // Follower
        void Sneak(Actor_t* actor);
        void Unsneak(Actor_t* actor);
        void Saddle(Actor_t* actor);
        void Unsaddle(Actor_t* actor);
        void Retreat(Actor_t* actor);
        void Unretreat(Actor_t* actor);
        void Toggle_Sneak(Actor_t* actor);
        void Toggle_Saddler(Actor_t* actor);
        void Toggle_Retreater(Actor_t* actor);

        // Members
        void Members_Start_Display();
        void Members_Stop_Display();
        void Members_Display_Previous();
        void Members_Display_Next();
        void Members_Toggle_Display();

        // Followers
        void Followers_Summon_All();
        void Followers_Summon_Mobile();
        void Followers_Summon_Immobile();
        void Followers_Stash();
        void Followers_Resurrect();
        void Followers_Mobilize();
        void Followers_Immobilize();
        void Followers_Settle();
        void Followers_Resettle();
        void Followers_Unsettle();
        void Followers_Enthrall();
        void Followers_Unthrall();
        void Followers_Paralyze();
        void Followers_Unparalyze();
        void Followers_Sneak();
        void Followers_Unsneak();
        void Followers_Saddle();
        void Followers_Unsaddle();
        void Followers_Retreat();
        void Followers_Unretreat();
        void Followers_Unfollow();
        void Followers_Unmember();
        void Followers_Toggle_Immobile();
        void Followers_Toggle_Settler();
        void Followers_Toggle_Thrall();
        void Followers_Toggle_Paralyzed();
        void Followers_Toggle_Sneak();
        void Followers_Toggle_Saddler();
        void Followers_Toggle_Retreater();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
