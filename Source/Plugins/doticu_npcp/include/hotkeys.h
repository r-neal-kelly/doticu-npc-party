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

        class Save_t
        {
        public:
            u16 global_dialogue_menu[4];

            u16 actor_toggle_member[4];
            u16 actor_toggle_move[4];
            u16 actor_move_nearer[4];
            u16 actor_move_farther[4];
            u16 actor_move_rotate_left[4];
            u16 actor_move_rotate_right[4];
            u16 actor_has_base[4];
            u16 actor_count_base[4];
            u16 actor_has_head[4];
            u16 actor_count_heads[4];

            u16 member_toggle_clone[4];
            u16 member_toggle_settler[4];
            u16 member_toggle_thrall[4];
            u16 member_toggle_immobile[4];
            u16 member_toggle_paralyzed[4];
            u16 member_toggle_follower[4];

            u16 follower_toggle_sneak[4];
            u16 follower_toggle_saddler[4];

            u16 members_toggle_display[4];
            u16 members_display_previous[4];
            u16 members_display_next[4];

            u16 followers_summon_all[4];
            u16 followers_summon_mobile[4];
            u16 followers_summon_immobile[4];
            u16 followers_settle[4];
            u16 followers_unsettle[4];
            u16 followers_mobilize[4];
            u16 followers_immobilize[4];
            u16 followers_sneak[4];
            u16 followers_unsneak[4];
            u16 followers_saddle[4];
            u16 followers_unsaddle[4];
            u16 followers_resurrect[4];

        public:
            Save_t();
            Save_t(const Save_t& other) = delete;
            Save_t(Save_t&& other) noexcept = delete;
            Save_t& operator =(const Save_t& other) = delete;
            Save_t& operator =(Save_t&& other) noexcept = delete;
            ~Save_t();
        };

        class State_t
        {
        public:
            Save_t                  save;

            const some<Quest_t*>    quest;
            u16                     currently_pressed_key;

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        static String_t                 Class_Name();
        static some<Virtual::Class_t*>  Class();
        static void                     Register_Me(some<Virtual::Machine_t*> machine);

    public:
        static void Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback);

    public:
        State_t state;

    public:
        Hotkeys_t();
        Hotkeys_t(const Hotkeys_t& other) = delete;
        Hotkeys_t(Hotkeys_t&& other) noexcept = delete;
        Hotkeys_t& operator =(const Hotkeys_t& other) = delete;
        Hotkeys_t& operator =(Hotkeys_t&& other) noexcept = delete;
        ~Hotkeys_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        State_t&    State();

    public:
        some<Virtual::Object_t*>    Object();

        Bool_t                      On_Key_Down(Virtual::Stack_ID_t stack_id, Int_t key_code);
        Bool_t                      On_Key_Up(Virtual::Stack_ID_t stack_id, Int_t key_code, Float_t time_held);

    public:
        void    Log(std::string indent = "");
    };

}}
