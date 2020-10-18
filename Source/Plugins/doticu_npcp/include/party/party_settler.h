/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    using Settler_Speed_e = Package_t::Preferred_Speed_e;

    class Settler_t : public Member_t {
    public:
        static constexpr Int_t      MIN_RADIUS              = 0;
        static constexpr Int_t      MAX_RADIUS              = 16384;
        static constexpr Int_t      DEFAULT_RADIUS          = 2048;
        static constexpr Int_t      MIN_TIME_HOUR           = -1;
        static constexpr Int_t      MAX_TIME_HOUR           = 23;
        static constexpr Int_t      MIN_TIME_MINUTE         = -1;
        static constexpr Int_t      MAX_TIME_MINUTE         = 59;
        static constexpr Int_t      MIN_DURATION_MINUTES    = 1;
        static constexpr Int_t      MAX_DURATION_MINUTES    = 1440;
        static constexpr Int_t      MIN_ATTENTION           = 0;
        static constexpr Int_t      MAX_ATTENTION           = 100;
        static constexpr UInt32     HOUR_MASK               = 0xFFFF0000;
        static constexpr UInt32     MINUTE_MASK             = 0x0000FFFF;
        static constexpr UInt32     ATTENTION_MASK          = 0xFFFF0000;
        static constexpr UInt32     SPEED_MASK              = 0x0000FFFF;

        enum class Sandboxer_Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALWAYS_SNEAK,
            ALLOW_SWIMMING,
            ALLOW_IDLE_CHATTER,
            IGNORE_COMBAT,
            SKIP_COMBAT_ALERT,
            KEEP_WEAPON_DRAWN,
            HIDE_WEAPONS,
            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,

            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_HORSE_RIDING,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,

            UNLOCK_ON_ARRIVAL,
            PREFERRED_PATH_ONLY,
        };

        enum class Sleeper_Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALWAYS_SNEAK,
            ALLOW_SWIMMING,
            ALLOW_IDLE_CHATTER,
            IGNORE_COMBAT,
            SKIP_COMBAT_ALERT,
            KEEP_WEAPON_DRAWN,
            HIDE_WEAPONS,
            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,

            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_HORSE_RIDING,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,

            LOCK_DOORS,
            PREFERRED_PATH_ONLY,
            WARN_BEFORE_LOCKING,
        };

        enum class Sitter_Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALWAYS_SNEAK,
            ALLOW_SWIMMING,
            ALLOW_IDLE_CHATTER,
            IGNORE_COMBAT,
            SKIP_COMBAT_ALERT,
            KEEP_WEAPON_DRAWN,
            HIDE_WEAPONS,
            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,

            STOP_MOVEMENT,
            PREFERRED_PATH_ONLY,
        };

        enum class Eater_Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALWAYS_SNEAK,
            ALLOW_SWIMMING,
            ALLOW_IDLE_CHATTER,
            IGNORE_COMBAT,
            SKIP_COMBAT_ALERT,
            KEEP_WEAPON_DRAWN,
            HIDE_WEAPONS,
            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,

            ALLOW_ALREADY_HELD,
            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_FAKE_FOOD,
            ALLOW_HORSE_RIDING,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,

            UNLOCK_ON_ARRIVAL,
            PREFERRED_PATH_ONLY,
        };

        enum class Guard_Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALWAYS_SNEAK,
            ALLOW_SWIMMING,
            ALLOW_IDLE_CHATTER,
            IGNORE_COMBAT,
            SKIP_COMBAT_ALERT,
            KEEP_WEAPON_DRAWN,
            HIDE_WEAPONS,
            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,
        };

    public:
        Variable_t* Sleeper_Marker_Variable(); // Reference_t*
        Variable_t* Sitter_Marker_Variable(); // Reference_t*
        Variable_t* Eater_Marker_Variable(); // Reference_t*
        Variable_t* Guard_Marker_Variable(); // Reference_t*

        Variable_t* Sandboxer_Radius_Variable(); // Int_t
        Variable_t* Sleeper_Radius_Variable(); // Int_t
        Variable_t* Sitter_Radius_Variable(); // Int_t
        Variable_t* Eater_Radius_Variable(); // Int_t
        Variable_t* Guard_Radius_Variable(); // Int_t

        Variable_t* Sleeper_Time_Variable(); // Int_t (Hour, Minute)
        Variable_t* Sitter_Time_Variable(); // Int_t (Hour, Minute)
        Variable_t* Eater_Time_Variable(); // Int_t (Hour, Minute)
        Variable_t* Guard_Time_Variable(); // Int_t (Hour, Minute)

        Variable_t* Sleeper_Duration_Variable(); // Int_t
        Variable_t* Sitter_Duration_Variable(); // Int_t
        Variable_t* Eater_Duration_Variable(); // Int_t
        Variable_t* Guard_Duration_Variable(); // Int_t

        Variable_t* Sandboxer_Movement_Variable(); // Int_t (Attention, Speed)
        Variable_t* Sleeper_Movement_Variable(); // Int_t (Attention, Speed)
        Variable_t* Sitter_Movement_Variable(); // Int_t (Attention, Speed)
        Variable_t* Eater_Movement_Variable(); // Int_t (Attention, Speed)
        Variable_t* Guard_Movement_Variable(); // Int_t (Attention, Speed)

        Variable_t* Sandboxer_Flags_Variable(); // Int_t
        Variable_t* Sleeper_Flags_Variable(); // Int_t
        Variable_t* Sitter_Flags_Variable(); // Int_t
        Variable_t* Eater_Flags_Variable(); // Int_t
        Variable_t* Guard_Flags_Variable(); // Int_t

        Package_t* Sandboxer_Package();
        Package_t* Sleeper_Package();
        Package_t* Sitter_Package();
        Package_t* Eater_Package();
        Package_t* Guard_Package();

        Reference_t* Sandboxer_Marker();
        Reference_t* Sleeper_Marker();
        Reference_t* Sitter_Marker();
        Reference_t* Eater_Marker();
        Reference_t* Guard_Marker();

        Int_t Sandboxer_Radius();
        Int_t Sleeper_Radius();
        Int_t Sitter_Radius();
        Int_t Eater_Radius();
        Int_t Guard_Radius();
        void Sandboxer_Radius(Int_t radius);
        void Sleeper_Radius(Int_t radius);
        void Sitter_Radius(Int_t radius);
        void Eater_Radius(Int_t radius);
        void Guard_Radius(Int_t radius);
        
        Int_t Sleeper_Hour();
        Int_t Sitter_Hour();
        Int_t Eater_Hour();
        Int_t Guard_Hour();
        void Sleeper_Hour(Int_t hour);
        void Sitter_Hour(Int_t hour);
        void Eater_Hour(Int_t hour);
        void Guard_Hour(Int_t hour);

        Int_t Sleeper_Minute();
        Int_t Sitter_Minute();
        Int_t Eater_Minute();
        Int_t Guard_Minute();
        void Sleeper_Minute(Int_t minute);
        void Sitter_Minute(Int_t minute);
        void Eater_Minute(Int_t minute);
        void Guard_Minute(Int_t minute);

        Int_t Sleeper_Duration();
        Int_t Sitter_Duration();
        Int_t Eater_Duration();
        Int_t Guard_Duration();
        void Sleeper_Duration(Int_t minutes);
        void Sitter_Duration(Int_t minutes);
        void Eater_Duration(Int_t minutes);
        void Guard_Duration(Int_t minutes);

        Int_t Sandboxer_Attention();
        Int_t Sleeper_Attention();
        Int_t Eater_Attention();
        void Sandboxer_Attention(Int_t attention);
        void Sleeper_Attention(Int_t attention);
        void Eater_Attention(Int_t attention);

        Settler_Speed_e Sandboxer_Speed();
        Settler_Speed_e Sleeper_Speed();
        Settler_Speed_e Sitter_Speed();
        Settler_Speed_e Eater_Speed();
        Settler_Speed_e Guard_Speed();
        void Sandboxer_Speed(Settler_Speed_e speed);
        void Sleeper_Speed(Settler_Speed_e speed);
        void Sitter_Speed(Settler_Speed_e speed);
        void Eater_Speed(Settler_Speed_e speed);
        void Guard_Speed(Settler_Speed_e speed);

        Bool_t Is_Flagged(Sandboxer_Flag_e flag);
        Bool_t Is_Flagged(Sleeper_Flag_e flag);
        Bool_t Is_Flagged(Sitter_Flag_e flag);
        Bool_t Is_Flagged(Eater_Flag_e flag);
        Bool_t Is_Flagged(Guard_Flag_e flag);
        void Flag(Sandboxer_Flag_e flag);
        void Flag(Sleeper_Flag_e flag);
        void Flag(Sitter_Flag_e flag);
        void Flag(Eater_Flag_e flag);
        void Flag(Guard_Flag_e flag);
        void Unflag(Sandboxer_Flag_e flag);
        void Unflag(Sleeper_Flag_e flag);
        void Unflag(Sitter_Flag_e flag);
        void Unflag(Eater_Flag_e flag);
        void Unflag(Guard_Flag_e flag);

        Bool_t Is_Sandboxer();
        Bool_t Is_Sleeper();
        Bool_t Is_Sitter();
        Bool_t Is_Eater();
        Bool_t Is_Guard();

        void Create(Actor_t* actor);
        void Create_Sandboxer(Actor_t* actor);
        void Create_Sleeper(Actor_t* actor);
        void Create_Sitter(Actor_t* actor);
        void Create_Eater(Actor_t* actor);
        void Create_Guard(Actor_t* actor);
        void Destroy(Actor_t* actor);
        void Destroy_Sandboxer(Actor_t* actor);
        void Destroy_Sleeper(Actor_t* actor);
        void Destroy_Sitter(Actor_t* actor);
        void Destroy_Eater(Actor_t* actor);
        void Destroy_Guard(Actor_t* actor);
        void Clear_Variables();

        void Default_Sandboxer();
        void Default_Sleeper();
        void Default_Sitter();
        void Default_Eater();
        void Default_Guard();

        void Enable_Sleeper();
        void Enable_Sitter();
        void Enable_Eater();
        void Enable_Guard();
        void Disable_Sleeper();
        void Disable_Sitter();
        void Disable_Eater();
        void Disable_Guard();

        void Move_Sandboxer_Marker();
        void Move_Sleeper_Marker();
        void Move_Sitter_Marker();
        void Move_Eater_Marker();
        void Move_Guard_Marker();

        void Enforce(Actor_t* actor, Bool_t force_reset_ai = false);
    };

}}}
