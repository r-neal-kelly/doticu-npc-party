/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Settler_t : public Member_t {
    public:
        static constexpr Int_t  MIN_RADIUS              = 0;
        static constexpr Int_t  MAX_RADIUS              = 16384;
        static constexpr Int_t  DEFAULT_RADIUS          = 4096;
        static constexpr Int_t  MIN_TIME_HOUR           = -1;
        static constexpr Int_t  MAX_TIME_HOUR           = 23;
        static constexpr Int_t  MIN_TIME_MINUTE         = -1;
        static constexpr Int_t  MAX_TIME_MINUTE         = 59;
        static constexpr Int_t  MIN_DURATION_MINUTES    = 1;
        static constexpr Int_t  MAX_DURATION_MINUTES    = 1440;
        static constexpr Int_t  MIN_ENERGY              = 0;
        static constexpr Int_t  MAX_ENERGY              = 100;
        static constexpr UInt32 HOUR_MASK               = 0xFFFF0000;
        static constexpr UInt32 MINUTE_MASK             = 0x0000FFFF;

        // the following enums are incomplete and don't take into account all the possible flags that are of interest.
        enum class Sandboxer_Flag_e : UInt32 {
            IS_ENABLED = 0,
            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_FRIENDLY_FIRE_COMMENTS,
            ALLOW_IDLE_CHATTER,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,
        };

        enum class Sleeper_Flag_e : UInt32 {
            IS_ENABLED = 0,
            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_FRIENDLY_FIRE_COMMENTS,
            ALLOW_IDLE_CHATTER,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,
        };

        enum class Eater_Flag_e : UInt32 {
            IS_ENABLED = 0,
            ALLOW_CONVERSATION,
            ALLOW_EATING,
            ALLOW_FRIENDLY_FIRE_COMMENTS,
            ALLOW_IDLE_CHATTER,
            ALLOW_IDLE_MARKERS,
            ALLOW_SITTING,
            ALLOW_SLEEPING,
            ALLOW_SPECIAL_FURNITURE,
            ALLOW_WANDERING,
        };

        enum class Guard_Flag_e : UInt32 {
            IS_ENABLED = 0,
            ALLOW_FRIENDLY_FIRE_COMMENTS,
            ALLOW_IDLE_CHATTER,
        };

    public:
        Variable_t* Sandboxer_Flags_Variable(); // Int_t
        Variable_t* Sleeper_Flags_Variable(); // Int_t
        Variable_t* Eater_Flags_Variable(); // Int_t
        Variable_t* Guard_Flags_Variable(); // Int_t

        Variable_t* Sandboxer_Radius_Variable(); // Int_t
        Variable_t* Sleeper_Radius_Variable(); // Int_t
        Variable_t* Eater_Radius_Variable(); // Int_t
        Variable_t* Guard_Radius_Variable(); // Int_t

        Variable_t* Sleeper_Time_Variable(); // Int_t
        Variable_t* Eater_Time_Variable(); // Int_t
        Variable_t* Guard_Time_Variable(); // Int_t

        Variable_t* Sleeper_Duration_Variable(); // Int_t
        Variable_t* Eater_Duration_Variable(); // Int_t
        Variable_t* Guard_Duration_Variable(); // Int_t

        Package_t* Sandboxer_Package();
        Package_t* Sleeper_Package();
        Package_t* Eater_Package();
        Package_t* Guard_Package();

        Reference_t* Sandboxer_Marker();
        Reference_t* Sleeper_Marker();
        Reference_t* Eater_Marker();
        Reference_t* Guard_Marker();

        template <Variable_t*(Settler_t::*Radius_Variable)()>
        Int_t Radius();
        Int_t Sandboxer_Radius();
        Int_t Sleeper_Radius();
        Int_t Eater_Radius();
        Int_t Guard_Radius();

        template <Variable_t*(Settler_t::*Radius_Variable)()>
        void Radius(Int_t radius);
        void Sandboxer_Radius(Int_t radius);
        void Sleeper_Radius(Int_t radius);
        void Eater_Radius(Int_t radius);
        void Guard_Radius(Int_t radius);
        
        template <Variable_t*(Settler_t::*Time_Variable)()>
        Int_t Hour();
        Int_t Sleeper_Hour();
        Int_t Eater_Hour();
        Int_t Guard_Hour();

        template <Variable_t*(Settler_t::*Time_Variable)()>
        void Hour(Int_t hour);
        void Sleeper_Hour(Int_t hour);
        void Eater_Hour(Int_t hour);
        void Guard_Hour(Int_t hour);

        template <Variable_t*(Settler_t::*Time_Variable)()>
        Int_t Minute();
        Int_t Sleeper_Minute();
        Int_t Eater_Minute();
        Int_t Guard_Minute();

        template <Variable_t*(Settler_t::*Time_Variable)()>
        void Minute(Int_t minute);
        void Sleeper_Minute(Int_t minute);
        void Eater_Minute(Int_t minute);
        void Guard_Minute(Int_t minute);

        template <Variable_t*(Settler_t::*Duration_Variable)()>
        Int_t Duration();
        Int_t Sleeper_Duration();
        Int_t Eater_Duration();
        Int_t Guard_Duration();

        template <Variable_t*(Settler_t::*Duration_Variable)()>
        void Duration(Int_t minutes);
        void Sleeper_Duration(Int_t minutes);
        void Eater_Duration(Int_t minutes);
        void Guard_Duration(Int_t minutes);

        template <typename Flag_e>
        Bool_t Is_Flagged(Flag_e flag);
        template <typename Flag_e>
        void Flag(Flag_e flag);
        template <typename Flag_e>
        void Unflag(Flag_e flag);

        Bool_t Is_Sandboxer();
        Bool_t Is_Sleeper();
        Bool_t Is_Eater();
        Bool_t Is_Guard();

        void Enable_Sleeper();
        void Enable_Eater();
        void Enable_Guard();

        void Disable_Sleeper();
        void Disable_Eater();
        void Disable_Guard();

        void Default_Sandboxer();
        void Default_Sleeper();
        void Default_Eater();
        void Default_Guard();

        void Create();
        void Destroy(); // this needs to cleanup all the packages, especially the sandbox package, and delete dynamic markers
        void Enforce(Actor_t* actor, Bool_t force_reset_ai = false); // Reset_AI should not be called here, but only on changes to the packages.
    };

}}}
