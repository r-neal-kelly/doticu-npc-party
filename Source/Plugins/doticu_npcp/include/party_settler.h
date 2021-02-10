/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    using Settler_Speed_e = Package_t::Preferred_Speed_e;

    enum class AM_PM_e : UInt32 {
        AM = 0,
        PM = 1,
    };

    class Settler_t : public Member_t {
    public:
        static constexpr Int_t      MIN_RADIUS              = 0;
        static constexpr Int_t      MAX_RADIUS              = 32768;
        static constexpr Int_t      DEFAULT_RADIUS          = 2048;

        static constexpr Int_t      MIN_WANDER_DISTANCE     = 64;
        static constexpr Int_t      MAX_WANDER_DISTANCE     = 1024;
        static constexpr Int_t      DEFAULT_WANDER_DISTANCE = 512;

        static constexpr Int_t      MIN_TIME_HOUR           = 1;
        static constexpr Int_t      MAX_TIME_HOUR           = 12;
        static constexpr Int_t      MIN_TIME_MINUTE         = 0;
        static constexpr Int_t      MAX_TIME_MINUTE         = 59;
        static constexpr UInt32     TIME_AM_PM_MASK         = 0x00FF0000;
        static constexpr UInt32     TIME_HOUR_MASK          = 0x0000FF00;
        static constexpr UInt32     TIME_MINUTE_MASK        = 0x000000FF;
        static constexpr size_t     TIME_AM_PM_IDX          = 16;
        static constexpr size_t     TIME_HOUR_IDX           = 8;
        static constexpr size_t     TIME_MINUTE_IDX         = 0;

        static constexpr Int_t      MIN_DURATION_HOURS      = 0;
        static constexpr Int_t      MAX_DURATION_HOURS      = 24;
        static constexpr Int_t      MIN_DURATION_MINUTES    = 0;
        static constexpr Int_t      MAX_DURATION_MINUTES    = 55;
        static constexpr Int_t      MIN_DURATION            = 0;
        static constexpr Int_t      MAX_DURATION            = 1440;
        static constexpr UInt32     DURATION_HOURS_MASK     = 0xFFFF0000;
        static constexpr UInt32     DURATION_MINUTES_MASK   = 0x0000FFFF;

        static constexpr Int_t      MIN_ATTENTION           = 0;
        static constexpr Int_t      MAX_ATTENTION           = 100;
        static constexpr Int_t      DEFAULT_ATTENTION       = 50;
        static constexpr UInt32     ATTENTION_MASK          = 0xFFFF0000;
        static constexpr UInt32     SPEED_MASK              = 0x0000FFFF;

    protected:
        template <typename Type_t> Reference_t* Marker();
        template <typename Type_t> void Move_Marker();

        template <typename Type_t> Int_t Radius();
        template <typename Type_t> void Radius(Int_t radius);

        template <typename Type_t> Int_t Hour();
        template <typename Type_t> void Hour(Int_t hour);
        template <typename Type_t> String_t Hour_String();

        template <typename Type_t> Int_t Minute();
        template <typename Type_t> void Minute(Int_t minute);
        template <typename Type_t> String_t Minute_String();

        template <typename Type_t> AM_PM_e AM_PM();
        template <typename Type_t> void AM_PM(AM_PM_e am_pm);
        template <typename Type_t> String_t AM_PM_String();

        template <typename Type_t> Int_t Duration_Hours();
        template <typename Type_t> void Duration_Hours(Int_t hours);
        template <typename Type_t> String_t Duration_Hours_String();

        template <typename Type_t> Int_t Duration_Minutes();
        template <typename Type_t> void Duration_Minutes(Int_t minutes);
        template <typename Type_t> String_t Duration_Minutes_String();

        template <typename Type_t> Int_t Attention();
        template <typename Type_t> void Attention(Int_t attention);

        template <typename Type_t> Settler_Speed_e Speed();
        template <typename Type_t> void Speed(Settler_Speed_e speed);
        template <typename Type_t> String_t Speed_String();

        template <typename Type_t> Int_t Wander_Distance();
        template <typename Type_t> void Wander_Distance(Int_t distance);

        template <typename Type_t> Bool_t Is_Flagged(UInt32 flag);
        template <typename Type_t> void Flag(UInt32 flag);
        template <typename Type_t> void Unflag(UInt32 flag);

        template <typename Type_t> Bool_t Is_Created();
        template <typename Type_t> void Create();
        template <typename Type_t> void Destroy(Bool_t do_enforce = true);
        template <typename Type_t> void Default();
        template <typename Type_t> void Clear();

    public:
        Bool_t Is_Sandboxer();
        Bool_t Is_Sleeper();
        Bool_t Is_Sitter();
        Bool_t Is_Eater();
        Bool_t Is_Guard();

        void Enable_Sandboxer();
        void Enable_Sleeper();
        void Enable_Sitter();
        void Enable_Eater();
        void Enable_Guard();

        void Disable_Sandboxer();
        void Disable_Sleeper();
        void Disable_Sitter();
        void Disable_Eater();
        void Disable_Guard();

        void Enforce(Actor_t* actor, Bool_t force_reset_ai = false);
    };

    class Sandboxer_t : public Settler_t {
    public:
        enum class Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALLOW_SWIMMING,
            ALWAYS_SNEAK,
            IGNORE_COMBAT,
            KEEP_WEAPONS_DRAWN,
            HIDE_WEAPONS,
            SKIP_COMBAT_ALERT,

            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            ALLOW_IDLE_CHATTER,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            INSPECT_CORPSE_BEHAVIOR,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,

            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_HORSE_RIDING,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,

            PREFERRED_PATH_ONLY,
            UNLOCK_ON_ARRIVAL,
        };

    public:
        Variable_t* Radius_Variable(); // Int_t
        Variable_t* Movement_Variable(); // Int_t
        Variable_t* Wander_Distance_Variable(); // Int_t
        Variable_t* Flags_Variable(); // Int_t

    public:
        Misc_t* Token();

        Package_t* Package();

        Reference_t* Marker();
        void Move_Marker();

        Int_t Radius();
        void Radius(Int_t radius);

        void Flag(Flag_e flag);
        void Unflag(Flag_e flag);
        Bool_t Is_Flagged(Flag_e flag);

        Int_t Attention();
        void Attention(Int_t attention);

        Settler_Speed_e Speed();
        void Speed(Settler_Speed_e speed);
        String_t Speed_String();

        Int_t Wander_Distance();
        void Wander_Distance(Int_t distance);

        Bool_t Is_Created();
        void Create();
        void Destroy(Bool_t do_enforce = true);
        void Default();
        void Clear();
    };

    class Sleeper_t : public Settler_t {
    public:
        enum class Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALLOW_SWIMMING,
            ALWAYS_SNEAK,
            IGNORE_COMBAT,
            KEEP_WEAPONS_DRAWN,
            HIDE_WEAPONS,
            SKIP_COMBAT_ALERT,

            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            ALLOW_IDLE_CHATTER,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            INSPECT_CORPSE_BEHAVIOR,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,

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

    public:
        Variable_t* Marker_Variable(); // Reference_t*
        Variable_t* Radius_Variable(); // Int_t
        Variable_t* Time_Variable(); // Int_t
        Variable_t* Duration_Variable(); // Int_t
        Variable_t* Movement_Variable(); // Int_t
        Variable_t* Wander_Distance_Variable(); // Int_t
        Variable_t* Flags_Variable(); // Int_t
        Variable_t* Bed_Variable(); // Reference_t*

    public:
        Misc_t* Token();

        Package_t* Package();

        Reference_t* Marker();
        void Move_Marker();

        Int_t Radius();
        void Radius(Int_t radius);

        void Flag(Flag_e flag);
        void Unflag(Flag_e flag);
        Bool_t Is_Flagged(Flag_e flag);

        Int_t Hour();
        void Hour(Int_t hour);
        String_t Hour_String();

        Int_t Minute();
        void Minute(Int_t minute);
        String_t Minute_String();

        AM_PM_e AM_PM();
        void AM_PM(AM_PM_e am_pm);
        String_t AM_PM_String();

        Int_t Duration_Hours();
        void Duration_Hours(Int_t hours);
        String_t Duration_Hours_String();

        Int_t Duration_Minutes();
        void Duration_Minutes(Int_t minutes);
        String_t Duration_Minutes_String();

        Int_t Attention();
        void Attention(Int_t attention);

        Settler_Speed_e Speed();
        void Speed(Settler_Speed_e speed);
        String_t Speed_String();

        Int_t Wander_Distance();
        void Wander_Distance(Int_t distance);

        Bool_t Is_Created();
        void Create();
        void Destroy(Bool_t do_enforce = true);
        void Default();
        void Clear();

        Bool_t Has_Bed();
        void Create_Bed();
        void Destroy_Bed();
        void Add_Bed();
        void Remove_Bed();
    };

    class Sitter_t : public Settler_t {
    public:
        enum class Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALLOW_SWIMMING,
            ALWAYS_SNEAK,
            IGNORE_COMBAT,
            KEEP_WEAPONS_DRAWN,
            HIDE_WEAPONS,
            SKIP_COMBAT_ALERT,

            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            ALLOW_IDLE_CHATTER,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            INSPECT_CORPSE_BEHAVIOR,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,

            PREFERRED_PATH_ONLY,
            STOP_MOVEMENT,
        };

    public:
        Variable_t* Marker_Variable(); // Reference_t*
        Variable_t* Radius_Variable(); // Int_t
        Variable_t* Time_Variable(); // Int_t
        Variable_t* Duration_Variable(); // Int_t
        Variable_t* Movement_Variable(); // Int_t
        Variable_t* Flags_Variable(); // Int_t

    public:
        Misc_t* Token();

        Package_t* Package();

        Reference_t* Marker();
        void Move_Marker();

        Int_t Radius();
        void Radius(Int_t radius);

        void Flag(Flag_e flag);
        void Unflag(Flag_e flag);
        Bool_t Is_Flagged(Flag_e flag);

        Int_t Hour();
        void Hour(Int_t hour);
        String_t Hour_String();

        Int_t Minute();
        void Minute(Int_t minute);
        String_t Minute_String();

        AM_PM_e AM_PM();
        void AM_PM(AM_PM_e am_pm);
        String_t AM_PM_String();

        Int_t Duration_Hours();
        void Duration_Hours(Int_t hours);
        String_t Duration_Hours_String();

        Int_t Duration_Minutes();
        void Duration_Minutes(Int_t minutes);
        String_t Duration_Minutes_String();

        Settler_Speed_e Speed();
        void Speed(Settler_Speed_e speed);
        String_t Speed_String();

        Bool_t Is_Created();
        void Create();
        void Destroy(Bool_t do_enforce = true);
        void Default();
        void Clear();
    };

    class Eater_t : public Settler_t {
    public:
        enum class Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALLOW_SWIMMING,
            ALWAYS_SNEAK,
            IGNORE_COMBAT,
            KEEP_WEAPONS_DRAWN,
            HIDE_WEAPONS,
            SKIP_COMBAT_ALERT,

            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            ALLOW_IDLE_CHATTER,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            INSPECT_CORPSE_BEHAVIOR,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,

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

            PREFERRED_PATH_ONLY,
            UNLOCK_ON_ARRIVAL,
        };

    public:
        Variable_t* Marker_Variable(); // Reference_t*
        Variable_t* Radius_Variable(); // Int_t
        Variable_t* Time_Variable(); // Int_t
        Variable_t* Duration_Variable(); // Int_t
        Variable_t* Movement_Variable(); // Int_t
        Variable_t* Wander_Distance_Variable(); // Int_t
        Variable_t* Flags_Variable(); // Int_t

    public:
        Misc_t* Token();

        Package_t* Package();

        Reference_t* Marker();
        void Move_Marker();

        Int_t Radius();
        void Radius(Int_t radius);

        void Flag(Flag_e flag);
        void Unflag(Flag_e flag);
        Bool_t Is_Flagged(Flag_e flag);

        Int_t Hour();
        void Hour(Int_t hour);
        String_t Hour_String();

        Int_t Minute();
        void Minute(Int_t minute);
        String_t Minute_String();

        AM_PM_e AM_PM();
        void AM_PM(AM_PM_e am_pm);
        String_t AM_PM_String();

        Int_t Duration_Hours();
        void Duration_Hours(Int_t hours);
        String_t Duration_Hours_String();

        Int_t Duration_Minutes();
        void Duration_Minutes(Int_t minutes);
        String_t Duration_Minutes_String();

        Int_t Attention();
        void Attention(Int_t attention);

        Settler_Speed_e Speed();
        void Speed(Settler_Speed_e speed);
        String_t Speed_String();

        Int_t Wander_Distance();
        void Wander_Distance(Int_t distance);

        Bool_t Is_Created();
        void Create();
        void Destroy(Bool_t do_enforce = true);
        void Default();
        void Clear();
    };

    class Guard_t : public Settler_t {
    public:
        enum class Flag_e : UInt32 {
            IS_ENABLED = 0,

            ALLOW_SWIMMING,
            ALWAYS_SNEAK,
            IGNORE_COMBAT,
            KEEP_WEAPONS_DRAWN,
            HIDE_WEAPONS,
            SKIP_COMBAT_ALERT,

            ALLOW_HELLOS_TO_PLAYER,
            ALLOW_HELLOS_TO_NPCS,
            ALLOW_IDLE_CHATTER,
            ALLOW_AGGRO_RADIUS_BEHAVIOR,
            ALLOW_WORLD_INTERACTIONS,
            COMMENT_ON_FRIENDLY_FIRE,
            INSPECT_CORPSE_BEHAVIOR,
            OBSERVE_COMBAT_BEHAVIOR,
            REACT_TO_PLAYER_ACTIONS,
        };

    public:
        Variable_t* Marker_Variable(); // Reference_t*
        Variable_t* Radius_Variable(); // Int_t
        Variable_t* Time_Variable(); // Int_t
        Variable_t* Duration_Variable(); // Int_t
        Variable_t* Movement_Variable(); // Int_t
        Variable_t* Flags_Variable(); // Int_t

    public:
        Misc_t* Token();

        Package_t* Package();

        Reference_t* Marker();
        void Move_Marker();

        Int_t Radius();
        void Radius(Int_t radius);

        void Flag(Flag_e flag);
        void Unflag(Flag_e flag);
        Bool_t Is_Flagged(Flag_e flag);

        Int_t Hour();
        void Hour(Int_t hour);
        String_t Hour_String();

        Int_t Minute();
        void Minute(Int_t minute);
        String_t Minute_String();

        AM_PM_e AM_PM();
        void AM_PM(AM_PM_e am_pm);
        String_t AM_PM_String();

        Int_t Duration_Hours();
        void Duration_Hours(Int_t hours);
        String_t Duration_Hours_String();

        Int_t Duration_Minutes();
        void Duration_Minutes(Int_t minutes);
        String_t Duration_Minutes_String();

        Settler_Speed_e Speed();
        void Speed(Settler_Speed_e speed);
        String_t Speed_String();

        Bool_t Is_Created();
        void Create();
        void Destroy(Bool_t do_enforce = true);
        void Default();
        void Clear();
    };

}}}
