/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Hotkeys_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static void Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback);

    public:
        const some<Quest_t*>    quest;
        Int_t                   currently_pressed_key;

    public:
        Hotkeys_t(some<Quest_t*> quest, Bool_t is_new_game);
        Hotkeys_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Hotkeys_t(const Hotkeys_t& other)                                           = delete;
        Hotkeys_t(Hotkeys_t&& other) noexcept                                       = delete;
        Hotkeys_t& operator =(const Hotkeys_t& other)                               = delete;
        Hotkeys_t& operator =(Hotkeys_t&& other) noexcept                           = delete;
        ~Hotkeys_t();

    public:
        some<V::Object_t*>                  Object();

        V::Variable_tt<Int_t>&              Global_Dialogue_Menu();

        V::Variable_tt<Int_t>&              Actor_Toggle_Member();
        V::Variable_tt<Int_t>&              Actor_Toggle_Move();
        V::Variable_tt<Int_t>&              Actor_Move_Nearer();
        V::Variable_tt<Int_t>&              Actor_Move_Farther();
        V::Variable_tt<Int_t>&              Actor_Move_Rotate_Left();
        V::Variable_tt<Int_t>&              Actor_Move_Rotate_Right();
        V::Variable_tt<Int_t>&              Actor_Has_Base();
        V::Variable_tt<Int_t>&              Actor_Count_Base();
        V::Variable_tt<Int_t>&              Actor_Has_Head();
        V::Variable_tt<Int_t>&              Actor_Count_Heads();

        V::Variable_tt<Int_t>&              Member_Toggle_Clone();
        V::Variable_tt<Int_t>&              Member_Toggle_Settler();
        V::Variable_tt<Int_t>&              Member_Toggle_Thrall();
        V::Variable_tt<Int_t>&              Member_Toggle_Immobile();
        V::Variable_tt<Int_t>&              Member_Toggle_Paralyzed();
        V::Variable_tt<Int_t>&              Member_Toggle_Follower();

        V::Variable_tt<Int_t>&              Follower_Toggle_Sneak();
        V::Variable_tt<Int_t>&              Follower_Toggle_Saddler();

        V::Variable_tt<Int_t>&              Members_Toggle_Display();
        V::Variable_tt<Int_t>&              Members_Display_Previous();
        V::Variable_tt<Int_t>&              Members_Display_Next();

        V::Variable_tt<Int_t>&              Followers_Summon_All();
        V::Variable_tt<Int_t>&              Followers_Summon_Mobile();
        V::Variable_tt<Int_t>&              Followers_Summon_Immobile();
        V::Variable_tt<Int_t>&              Followers_Settle();
        V::Variable_tt<Int_t>&              Followers_Unsettle();
        V::Variable_tt<Int_t>&              Followers_Mobilize();
        V::Variable_tt<Int_t>&              Followers_Immobilize();
        V::Variable_tt<Int_t>&              Followers_Sneak();
        V::Variable_tt<Int_t>&              Followers_Unsneak();
        V::Variable_tt<Int_t>&              Followers_Saddle();
        V::Variable_tt<Int_t>&              Followers_Unsaddle();
        V::Variable_tt<Int_t>&              Followers_Resurrect();

        V::Variable_tt<Vector_t<Int_t>>&    Global_Dialogue_Menu_Mods();

        V::Variable_tt<Vector_t<Int_t>>&    Actor_Toggle_Member_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Toggle_Move_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Move_Nearer_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Move_Farther_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Move_Rotate_Left_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Move_Rotate_Right_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Has_Base_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Count_Base_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Has_Head_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Actor_Count_Heads_Mods();

        V::Variable_tt<Vector_t<Int_t>>&    Member_Toggle_Clone_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Member_Toggle_Settler_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Member_Toggle_Thrall_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Member_Toggle_Immobile_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Member_Toggle_Paralyzed_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Member_Toggle_Follower_Mods();

        V::Variable_tt<Vector_t<Int_t>>&    Follower_Toggle_Sneak_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Follower_Toggle_Saddler_Mods();

        V::Variable_tt<Vector_t<Int_t>>&    Members_Toggle_Display_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Members_Display_Previous_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Members_Display_Next_Mods();

        V::Variable_tt<Vector_t<Int_t>>&    Followers_Summon_All_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Summon_Mobile_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Summon_Immobile_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Settle_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Unsettle_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Mobilize_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Immobilize_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Sneak_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Unsneak_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Saddle_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Unsaddle_Mods();
        V::Variable_tt<Vector_t<Int_t>>&    Followers_Resurrect_Mods();

        Bool_t                              On_Key_Down(V::Stack_ID_t stack_id, Int_t key_code);
        Bool_t                              On_Key_Up(V::Stack_ID_t stack_id, Int_t key_code, Float_t time_held);

    public:
        void    Before_Save();
        void    After_Save();
        void    Validate();

    public:
        void Log(std::string indent = "");
    };

}}
