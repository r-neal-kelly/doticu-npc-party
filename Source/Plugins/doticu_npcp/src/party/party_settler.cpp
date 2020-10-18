/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "form.h"
#include "funcs.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_alias.inl"
#include "party/party_settler.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    enum class Sandboxer_Value_e : UInt16 {
        LOCATION = 0,               // Location
        DO_UNLOCK_ON_ARRIVAL,       // Bool
        ALLOW_EATING,               // Bool
        ALLOW_SLEEPING,             // Bool
        ALLOW_CONVERSATION,         // Bool
        ALLOW_IDLE_MARKERS,         // Bool
        ALLOW_SITTING,              // Bool
        ALLOW_SPECIAL_FURNITURE,    // Bool
        ALLOW_WANDERING,            // Bool
        DO_PREFERRED_PATH_ONLY,     // Bool
        ALLOW_HORSE_RIDING,         // Bool
        ATTENTION,                  // Float
    };

    enum class Sleeper_Value_e : UInt16 {
        LOCATION = 0,               // Location
        SEARCH_CRITERIA,            // Target_Selector
        DO_LOCK_DOORS,              // Bool
        DO_WARN_BEFORE_LOCKING,     // Bool
        ALLOW_HORSE_RIDING,         // Bool
        BED_LIST,                   // Object_List
        FALSE_BOOL,                 // Bool
        ALLOW_EATING,               // Bool
        ALLOW_SLEEPING,             // Bool
        ALLOW_CONVERSATION,         // Bool
        ALLOW_IDLE_MARKERS,         // Bool
        ALLOW_SITTING,              // Bool
        ALLOW_SPECIAL_FURNITURE,    // Bool
        ALLOW_WANDERING,            // Bool
        MIN_WANDER_DISTANCE,        // Float
        DO_PREFERRED_PATH_ONLY,     // Bool
        ATTENTION,                  // Float
    };

    enum class Sitter_Value_e : UInt16 {
        LOCATION = 0,               // Location
        SEARCH_CRITERIA,            // Target_Selector
        CHAIR_LIST,                 // Object_List
        WAIT_TIME,                  // Float
        DO_STOP_MOVEMENT,           // Bool
        DO_PREFERRED_PATH_ONLY,     // Bool
        FALSE_BOOL,                 // Bool
    };

    enum class Eater_Value_e : UInt16 {
        LOCATION = 0,               // Location
        DO_UNLOCK_ON_ARRIVAL,       // Bool
        FOOD_CRITERIA,              // Target_Selector
        FOOD_LIST,                  // Object_List
        CHAIR_CRITERIA,             // Target_Selector
        CHAIR_LIST,                 // Object_List
        NUM_FOOD_ITEMS,             // Int
        ALLOW_ALREADY_HELD,         // Bool
        ALLOW_HORSE_RIDING,         // Bool
        FALSE_BOOL,                 // Bool
        ALLOW_FAKE_FOOD,            // Bool
        ALLOW_EATING,               // Bool
        ALLOW_SLEEPING,             // Bool
        ALLOW_CONVERSATION,         // Bool
        ALLOW_IDLE_MARKERS,         // Bool
        ALLOW_SPECIAL_FURNITURE,    // Bool
        ALLOW_SITTING,              // Bool
        ALLOW_WANDERING,            // Bool
        MIN_WANDER_DISTANCE,        // Float
        DO_PREFERRED_PATH_ONLY,     // Bool
        ATTENTION,                  // Float
    };

    enum class Guard_Value_e : UInt16 {
        WAIT_LOCATION,              // Location
        RESTRICTED_LOCATION,        // Location
    };

    Variable_t* Settler_t::Sleeper_Marker_Variable() { DEFINE_VARIABLE("p_settler_sleeper_marker"); }
    Variable_t* Settler_t::Sitter_Marker_Variable() { DEFINE_VARIABLE("p_settler_sitter_marker"); }
    Variable_t* Settler_t::Eater_Marker_Variable() { DEFINE_VARIABLE("p_settler_eater_marker"); }
    Variable_t* Settler_t::Guard_Marker_Variable() { DEFINE_VARIABLE("p_settler_guard_marker"); }

    Variable_t* Settler_t::Sandboxer_Radius_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_radius"); }
    Variable_t* Settler_t::Sleeper_Radius_Variable() { DEFINE_VARIABLE("p_settler_sleeper_radius"); }
    Variable_t* Settler_t::Sitter_Radius_Variable() { DEFINE_VARIABLE("p_settler_sitter_radius"); }
    Variable_t* Settler_t::Eater_Radius_Variable() { DEFINE_VARIABLE("p_settler_eater_radius"); }
    Variable_t* Settler_t::Guard_Radius_Variable() { DEFINE_VARIABLE("p_settler_guard_radius"); }

    Variable_t* Settler_t::Sleeper_Time_Variable() { DEFINE_VARIABLE("p_settler_sleeper_time"); }
    Variable_t* Settler_t::Sitter_Time_Variable() { DEFINE_VARIABLE("p_settler_sitter_time"); }
    Variable_t* Settler_t::Eater_Time_Variable() { DEFINE_VARIABLE("p_settler_eater_time"); }
    Variable_t* Settler_t::Guard_Time_Variable() { DEFINE_VARIABLE("p_settler_guard_time"); }

    Variable_t* Settler_t::Sleeper_Duration_Variable() { DEFINE_VARIABLE("p_settler_sleeper_duration"); }
    Variable_t* Settler_t::Sitter_Duration_Variable() { DEFINE_VARIABLE("p_settler_sitter_duration"); }
    Variable_t* Settler_t::Eater_Duration_Variable() { DEFINE_VARIABLE("p_settler_eater_duration"); }
    Variable_t* Settler_t::Guard_Duration_Variable() { DEFINE_VARIABLE("p_settler_guard_duration"); }

    Variable_t* Settler_t::Sandboxer_Movement_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_movement"); }
    Variable_t* Settler_t::Sleeper_Movement_Variable() { DEFINE_VARIABLE("p_settler_sleeper_movement"); }
    Variable_t* Settler_t::Sitter_Movement_Variable() { DEFINE_VARIABLE("p_settler_sitter_movement"); }
    Variable_t* Settler_t::Eater_Movement_Variable() { DEFINE_VARIABLE("p_settler_eater_movement"); }
    Variable_t* Settler_t::Guard_Movement_Variable() { DEFINE_VARIABLE("p_settler_guard_movement"); }

    Variable_t* Settler_t::Sandboxer_Flags_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_flags"); }
    Variable_t* Settler_t::Sleeper_Flags_Variable() { DEFINE_VARIABLE("p_settler_sleeper_flags"); }
    Variable_t* Settler_t::Sitter_Flags_Variable() { DEFINE_VARIABLE("p_settler_sitter_flags"); }
    Variable_t* Settler_t::Eater_Flags_Variable() { DEFINE_VARIABLE("p_settler_eater_flags"); }
    Variable_t* Settler_t::Guard_Flags_Variable() { DEFINE_VARIABLE("p_settler_guard_flags"); }

    /* Package */

    Package_t* Settler_t::Sandboxer_Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Settler_t::Sleeper_Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Sleeper_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Settler_t::Sitter_Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Sitter_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Settler_t::Eater_Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Eater_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Settler_t::Guard_Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Guard_Packages_Formlist()->forms.entries[ID()]);
    }

    /* Marker */

    inline Reference_t* Marker(Variable_t* variable)
    {
        return variable->Reference();
    }

    Reference_t* Settler_t::Sandboxer_Marker()
    {
        return static_cast<Reference_t*>
            (Consts::Settler_Markers_Formlist()->forms.entries[ID()]);
    }

    Reference_t* Settler_t::Sleeper_Marker()
    {
        return Marker(Sleeper_Marker_Variable());
    }

    Reference_t* Settler_t::Sitter_Marker()
    {
        return Marker(Sitter_Marker_Variable());
    }

    Reference_t* Settler_t::Eater_Marker()
    {
        return Marker(Eater_Marker_Variable());
    }

    Reference_t* Settler_t::Guard_Marker()
    {
        return Marker(Guard_Marker_Variable());
    }

    /* Radius */

    inline Int_t Radius(Variable_t* variable)
    {
        return variable->Int();
    }

    Int_t Settler_t::Sandboxer_Radius()
    {
        return Radius(Sandboxer_Radius_Variable());
    }

    Int_t Settler_t::Sleeper_Radius()
    {
        return Radius(Sleeper_Radius_Variable());
    }

    Int_t Settler_t::Sitter_Radius()
    {
        return Radius(Sitter_Radius_Variable());
    }

    Int_t Settler_t::Eater_Radius()
    {
        return Radius(Eater_Radius_Variable());
    }

    Int_t Settler_t::Guard_Radius()
    {
        return Radius(Guard_Radius_Variable());
    }

    inline void Radius(Variable_t* variable, Int_t radius)
    {
        if (radius < Settler_t::MIN_RADIUS) {
            radius = Settler_t::MIN_RADIUS;
        } else if (radius > Settler_t::MAX_RADIUS) {
            radius = Settler_t::MAX_RADIUS;
        }

        variable->Int(radius);
    }

    void Settler_t::Sandboxer_Radius(Int_t radius)
    {
        Radius(Sandboxer_Radius_Variable(), radius);
    }

    void Settler_t::Sleeper_Radius(Int_t radius)
    {
        Radius(Sleeper_Radius_Variable(), radius);
    }

    void Settler_t::Sitter_Radius(Int_t radius)
    {
        Radius(Sitter_Radius_Variable(), radius);
    }

    void Settler_t::Eater_Radius(Int_t radius)
    {
        Radius(Eater_Radius_Variable(), radius);
    }

    void Settler_t::Guard_Radius(Int_t radius)
    {
        Radius(Guard_Radius_Variable(), radius);
    }

    /* Hour */

    inline Int_t Hour(Variable_t* variable)
    {
        return static_cast<Int_t>((static_cast<UInt32>(variable->Int()) & Settler_t::HOUR_MASK) >> 16) - 1;
    }

    Int_t Settler_t::Sleeper_Hour()
    {
        return Hour(Sleeper_Time_Variable());
    }

    Int_t Settler_t::Sitter_Hour()
    {
        return Hour(Sitter_Time_Variable());
    }

    Int_t Settler_t::Eater_Hour()
    {
        return Hour(Eater_Time_Variable());
    }

    Int_t Settler_t::Guard_Hour()
    {
        return Hour(Guard_Time_Variable());
    }

    inline void Hour(Variable_t* variable, Int_t hour)
    {
        if (hour < Settler_t::MIN_TIME_HOUR) {
            hour = Settler_t::MIN_TIME_HOUR;
        } else if (hour > Settler_t::MAX_TIME_HOUR) {
            hour = Settler_t::MAX_TIME_HOUR;
        }
        hour += 1;

        variable->Int(
            (static_cast<UInt32>(hour) << 16) |
            (static_cast<UInt32>(variable->Int()) & Settler_t::MINUTE_MASK)
        );
    }

    void Settler_t::Sleeper_Hour(Int_t hour)
    {
        Hour(Sleeper_Time_Variable(), hour);
    }

    void Settler_t::Sitter_Hour(Int_t hour)
    {
        Hour(Sitter_Time_Variable(), hour);
    }

    void Settler_t::Eater_Hour(Int_t hour)
    {
        Hour(Eater_Time_Variable(), hour);
    }

    void Settler_t::Guard_Hour(Int_t hour)
    {
        Hour(Guard_Time_Variable(), hour);
    }

    /* Minute */

    inline Int_t Minute(Variable_t* variable)
    {
        return static_cast<Int_t>(static_cast<UInt32>(variable->Int()) & Settler_t::MINUTE_MASK) - 1;
    }

    Int_t Settler_t::Sleeper_Minute()
    {
        return Minute(Sleeper_Time_Variable());
    }

    Int_t Settler_t::Sitter_Minute()
    {
        return Minute(Sitter_Time_Variable());
    }

    Int_t Settler_t::Eater_Minute()
    {
        return Minute(Eater_Time_Variable());
    }

    Int_t Settler_t::Guard_Minute()
    {
        return Minute(Guard_Time_Variable());
    }

    inline void Minute(Variable_t* variable, Int_t minute)
    {
        if (minute < Settler_t::MIN_TIME_MINUTE) {
            minute = Settler_t::MIN_TIME_MINUTE;
        } else if (minute > Settler_t::MAX_TIME_MINUTE) {
            minute = Settler_t::MAX_TIME_MINUTE;
        }
        minute += 1;

        variable->Int(
            (static_cast<UInt32>(variable->Int()) & Settler_t::HOUR_MASK) |
            (static_cast<UInt32>(minute) & Settler_t::MINUTE_MASK)
        );
    }

    void Settler_t::Sleeper_Minute(Int_t minute)
    {
        Minute(Sleeper_Time_Variable(), minute);
    }

    void Settler_t::Sitter_Minute(Int_t minute)
    {
        Minute(Sitter_Time_Variable(), minute);
    }

    void Settler_t::Eater_Minute(Int_t minute)
    {
        Minute(Eater_Time_Variable(), minute);
    }

    void Settler_t::Guard_Minute(Int_t minute)
    {
        Minute(Guard_Time_Variable(), minute);
    }

    /* Duration */

    inline Int_t Duration(Variable_t* variable)
    {
        return variable->Int();
    }

    Int_t Settler_t::Sleeper_Duration()
    {
        return Duration(Sleeper_Duration_Variable());
    }

    Int_t Settler_t::Sitter_Duration()
    {
        return Duration(Sitter_Duration_Variable());
    }

    Int_t Settler_t::Eater_Duration()
    {
        return Duration(Eater_Duration_Variable());
    }

    Int_t Settler_t::Guard_Duration()
    {
        return Duration(Guard_Duration_Variable());
    }

    inline void Duration(Variable_t* variable, Int_t minutes)
    {
        if (minutes < Settler_t::MIN_DURATION_MINUTES) {
            minutes = Settler_t::MIN_DURATION_MINUTES;
        } else if (minutes > Settler_t::MAX_DURATION_MINUTES) {
            minutes = Settler_t::MAX_DURATION_MINUTES;
        }

        variable->Int(minutes);
    }

    void Settler_t::Sleeper_Duration(Int_t minutes)
    {
        Duration(Sleeper_Duration_Variable(), minutes);
    }

    void Settler_t::Sitter_Duration(Int_t minutes)
    {
        Duration(Sitter_Duration_Variable(), minutes);
    }

    void Settler_t::Eater_Duration(Int_t minutes)
    {
        Duration(Eater_Duration_Variable(), minutes);
    }

    void Settler_t::Guard_Duration(Int_t minutes)
    {
        Duration(Guard_Duration_Variable(), minutes);
    }

    /* Attention */

    inline Int_t Attention(Variable_t* variable)
    {
        return static_cast<Int_t>((static_cast<UInt32>(variable->Int()) & Settler_t::ATTENTION_MASK) >> 16);
    }

    Int_t Settler_t::Sandboxer_Attention()
    {
        return Attention(Sandboxer_Movement_Variable());
    }

    Int_t Settler_t::Sleeper_Attention()
    {
        return Attention(Sleeper_Movement_Variable());
    }

    Int_t Settler_t::Eater_Attention()
    {
        return Attention(Eater_Movement_Variable());
    }

    inline void Attention(Variable_t* variable, Int_t attention)
    {
        if (attention < Settler_t::MIN_ATTENTION) {
            attention = Settler_t::MIN_ATTENTION;
        } else if (attention > Settler_t::MAX_ATTENTION) {
            attention = Settler_t::MAX_ATTENTION;
        }

        variable->Int(
            (static_cast<UInt32>(attention) << 16) |
            (static_cast<UInt32>(variable->Int()) & Settler_t::SPEED_MASK)
        );
    }

    void Settler_t::Sandboxer_Attention(Int_t attention)
    {
        Attention(Sandboxer_Movement_Variable(), attention);
    }

    void Settler_t::Sleeper_Attention(Int_t attention)
    {
        Attention(Sleeper_Movement_Variable(), attention);
    }

    void Settler_t::Eater_Attention(Int_t attention)
    {
        Attention(Eater_Movement_Variable(), attention);
    }

    /* Speed */

    inline Settler_Speed_e Speed(Variable_t* variable)
    {
        return static_cast<Settler_Speed_e>(static_cast<UInt32>(variable->Int()) & Settler_t::SPEED_MASK);
    }

    Settler_Speed_e Settler_t::Sandboxer_Speed()
    {
        return Speed(Sandboxer_Movement_Variable());
    }

    Settler_Speed_e Settler_t::Sleeper_Speed()
    {
        return Speed(Sleeper_Movement_Variable());
    }

    Settler_Speed_e Settler_t::Sitter_Speed()
    {
        return Speed(Sitter_Movement_Variable());
    }

    Settler_Speed_e Settler_t::Eater_Speed()
    {
        return Speed(Eater_Movement_Variable());
    }

    Settler_Speed_e Settler_t::Guard_Speed()
    {
        return Speed(Guard_Movement_Variable());
    }

    inline void Speed(Variable_t* variable, Settler_Speed_e speed)
    {
        variable->Int(
            (static_cast<UInt32>(variable->Int()) & Settler_t::ATTENTION_MASK) |
            (static_cast<UInt32>(speed) & Settler_t::SPEED_MASK)
        );
    }

    void Settler_t::Sandboxer_Speed(Settler_Speed_e speed)
    {
        Speed(Sandboxer_Movement_Variable(), speed);
    }

    void Settler_t::Sleeper_Speed(Settler_Speed_e speed)
    {
        Speed(Sleeper_Movement_Variable(), speed);
    }

    void Settler_t::Sitter_Speed(Settler_Speed_e speed)
    {
        Speed(Sitter_Movement_Variable(), speed);
    }

    void Settler_t::Eater_Speed(Settler_Speed_e speed)
    {
        Speed(Eater_Movement_Variable(), speed);
    }

    void Settler_t::Guard_Speed(Settler_Speed_e speed)
    {
        Speed(Guard_Movement_Variable(), speed);
    }

    /* Flag */

    inline Bool_t Is_Flagged_Impl(Variable_t* variable, UInt32 flag)
    {
        return (static_cast<UInt32>(variable->Int()) & (static_cast<UInt32>(1) << flag)) > 0;
    }

    Bool_t Settler_t::Is_Flagged(Sandboxer_Flag_e flag)
    {
        return Is_Flagged_Impl(Sandboxer_Flags_Variable(), static_cast<UInt32>(flag));
    }

    Bool_t Settler_t::Is_Flagged(Sleeper_Flag_e flag)
    {
        return Is_Flagged_Impl(Sleeper_Flags_Variable(), static_cast<UInt32>(flag));
    }

    Bool_t Settler_t::Is_Flagged(Sitter_Flag_e flag)
    {
        return Is_Flagged_Impl(Sitter_Flags_Variable(), static_cast<UInt32>(flag));
    }

    Bool_t Settler_t::Is_Flagged(Eater_Flag_e flag)
    {
        return Is_Flagged_Impl(Eater_Flags_Variable(), static_cast<UInt32>(flag));
    }

    Bool_t Settler_t::Is_Flagged(Guard_Flag_e flag)
    {
        return Is_Flagged_Impl(Guard_Flags_Variable(), static_cast<UInt32>(flag));
    }

    inline void Flag_Impl(Variable_t* variable, UInt32 flag)
    {
        variable->Int(
            static_cast<UInt32>(variable->Int()) |
            (static_cast<UInt32>(1) << flag)
        );
    }

    void Settler_t::Flag(Sandboxer_Flag_e flag)
    {
        Flag_Impl(Sandboxer_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Flag(Sleeper_Flag_e flag)
    {
        Flag_Impl(Sleeper_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Flag(Sitter_Flag_e flag)
    {
        Flag_Impl(Sitter_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Flag(Eater_Flag_e flag)
    {
        Flag_Impl(Eater_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Flag(Guard_Flag_e flag)
    {
        Flag_Impl(Guard_Flags_Variable(), static_cast<UInt32>(flag));
    }

    inline void Unflag_Impl(Variable_t* variable, UInt32 flag)
    {
        variable->Int(
            static_cast<UInt32>(variable->Int()) &
            ~(static_cast<UInt32>(1) << flag)
        );
    }

    void Settler_t::Unflag(Sandboxer_Flag_e flag)
    {
        Unflag_Impl(Sandboxer_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Unflag(Sleeper_Flag_e flag)
    {
        Unflag_Impl(Sleeper_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Unflag(Sitter_Flag_e flag)
    {
        Unflag_Impl(Sitter_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Unflag(Eater_Flag_e flag)
    {
        Unflag_Impl(Eater_Flags_Variable(), static_cast<UInt32>(flag));
    }

    void Settler_t::Unflag(Guard_Flag_e flag)
    {
        Unflag_Impl(Guard_Flags_Variable(), static_cast<UInt32>(flag));
    }

    /* Bool */

    Bool_t Settler_t::Is_Sandboxer()
    {
        return Is_Flagged(Sandboxer_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Sleeper()
    {
        return Is_Flagged(Sleeper_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Sitter()
    {
        return Is_Flagged(Sitter_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Eater()
    {
        return Is_Flagged(Eater_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Guard()
    {
        return Is_Flagged(Guard_Flag_e::IS_ENABLED);
    }

    /* Create/Destroy */

    void Settler_t::Create(Actor_t* actor)
    {
        Clear_Variables();
        Create_Sandboxer(actor);
        Enforce(actor, true);
    }

    void Settler_t::Create_Sandboxer(Actor_t* actor)
    {
        if (!Is_Sandboxer()) {
            Object_Ref::Move_To_Orbit(Sandboxer_Marker(), actor, 0.0f, 180.0f); // move to player?

            Flag(Sandboxer_Flag_e::IS_ENABLED);
            Default_Sandboxer();

            Object_Ref::Token(actor, Consts::Settler_Token());
        }
    }

    void Settler_t::Create_Sleeper(Actor_t* actor)
    {
        if (Is_Sandboxer() && !Is_Sleeper()) {
            Reference_t* marker = Object_Ref::Create_Marker_At(Sandboxer_Marker());
            Sleeper_Marker_Variable()->Pack(marker);

            Flag(Sleeper_Flag_e::IS_ENABLED);
            Default_Sleeper();

            Object_Ref::Token(actor, Consts::Settler_Sleeper_Token());
        }
    }

    void Settler_t::Create_Sitter(Actor_t* actor)
    {
        if (Is_Sandboxer() && !Is_Sitter()) {
            Reference_t* marker = Object_Ref::Create_Marker_At(Sandboxer_Marker());
            Sitter_Marker_Variable()->Pack(marker);

            Flag(Sitter_Flag_e::IS_ENABLED);
            Default_Sitter();

            Object_Ref::Token(actor, Consts::Settler_Sitter_Token());
        }
    }

    void Settler_t::Create_Eater(Actor_t* actor)
    {
        if (Is_Sandboxer() && !Is_Eater()) {
            Reference_t* marker = Object_Ref::Create_Marker_At(Sandboxer_Marker());
            Eater_Marker_Variable()->Pack(marker);

            Flag(Eater_Flag_e::IS_ENABLED);
            Default_Eater();

            Object_Ref::Token(actor, Consts::Settler_Eater_Token());
        }
    }

    void Settler_t::Create_Guard(Actor_t* actor)
    {
        if (Is_Sandboxer() && !Is_Guard()) {
            Reference_t* marker = Object_Ref::Create_Directed_Marker_At(Sandboxer_Marker());
            Guard_Marker_Variable()->Pack(marker);

            Flag(Guard_Flag_e::IS_ENABLED);
            Default_Guard();

            Object_Ref::Token(actor, Consts::Settler_Guard_Token());
        }
    }

    void Settler_t::Destroy(Actor_t* actor)
    {
        Destroy_Guard(actor);
        Destroy_Eater(actor);
        Destroy_Sitter(actor);
        Destroy_Sleeper(actor);
        Destroy_Sandboxer(actor);
        Clear_Variables();
    }

    void Settler_t::Destroy_Sandboxer(Actor_t* actor)
    {
        if (Is_Sandboxer()) {
            Object_Ref::Untoken(actor, Consts::Settler_Token());

            Object_Ref::Move_To_Orbit(Sandboxer_Marker(), Consts::Storage_Marker(), 0.0f, 0.0f);

            Unflag(Sandboxer_Flag_e::IS_ENABLED);
        }
    }

    void Settler_t::Destroy_Sleeper(Actor_t* actor)
    {
        if (Is_Sleeper()) {
            Object_Ref::Untoken(actor, Consts::Settler_Sleeper_Token());

            Reference_t* marker = Sleeper_Marker_Variable()->Reference();
            Sleeper_Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(marker);

            Unflag(Sleeper_Flag_e::IS_ENABLED);
        }
    }

    void Settler_t::Destroy_Sitter(Actor_t* actor)
    {
        if (Is_Sitter()) {
            Object_Ref::Untoken(actor, Consts::Settler_Sitter_Token());

            Reference_t* marker = Sitter_Marker_Variable()->Reference();
            Sitter_Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(marker);

            Unflag(Sitter_Flag_e::IS_ENABLED);
        }
    }

    void Settler_t::Destroy_Eater(Actor_t* actor)
    {
        if (Is_Eater()) {
            Object_Ref::Untoken(actor, Consts::Settler_Eater_Token());

            Reference_t* marker = Eater_Marker_Variable()->Reference();
            Eater_Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(marker);

            Unflag(Eater_Flag_e::IS_ENABLED);
        }
    }

    void Settler_t::Destroy_Guard(Actor_t* actor)
    {
        if (Is_Guard()) {
            Object_Ref::Untoken(actor, Consts::Settler_Guard_Token());

            Reference_t* marker = Guard_Marker_Variable()->Reference();
            Guard_Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(marker);

            Unflag(Guard_Flag_e::IS_ENABLED);
        }
    }

    void Settler_t::Clear_Variables()
    {
        Class_Info_t* reference_class_info = Object_Ref::Class_Info();
        Sleeper_Marker_Variable()->None(reference_class_info);
        Sitter_Marker_Variable()->None(reference_class_info);
        Eater_Marker_Variable()->None(reference_class_info);
        Guard_Marker_Variable()->None(reference_class_info);

        Sandboxer_Radius_Variable()->Int(0);
        Sleeper_Radius_Variable()->Int(0);
        Sitter_Radius_Variable()->Int(0);
        Eater_Radius_Variable()->Int(0);
        Guard_Radius_Variable()->Int(0);

        Sleeper_Time_Variable()->Int(0);
        Sitter_Time_Variable()->Int(0);
        Eater_Time_Variable()->Int(0);
        Guard_Time_Variable()->Int(0);

        Sleeper_Duration_Variable()->Int(0);
        Sitter_Duration_Variable()->Int(0);
        Eater_Duration_Variable()->Int(0);
        Guard_Duration_Variable()->Int(0);

        Sandboxer_Movement_Variable()->Int(0);
        Sleeper_Movement_Variable()->Int(0);
        Sitter_Movement_Variable()->Int(0);
        Eater_Movement_Variable()->Int(0);
        Guard_Movement_Variable()->Int(0);

        Sandboxer_Flags_Variable()->Int(0);
        Sleeper_Flags_Variable()->Int(0);
        Sitter_Flags_Variable()->Int(0);
        Eater_Flags_Variable()->Int(0);
        Guard_Flags_Variable()->Int(0);
    }

    /* Default */

    void Settler_t::Default_Sandboxer()
    {
        Sandboxer_Radius(DEFAULT_RADIUS);
        Sandboxer_Attention(40);
        Sandboxer_Speed(Settler_Speed_e::WALK);
    }

    void Settler_t::Default_Sleeper()
    {
        Sleeper_Radius(DEFAULT_RADIUS);
        Sleeper_Hour(10 + 12);
        Sleeper_Minute(30);
        Sleeper_Duration(8 * 60);
        Sleeper_Attention(100);
        Sleeper_Speed(Settler_Speed_e::JOG);
    }

    void Settler_t::Default_Sitter()
    {
        Sitter_Radius(DEFAULT_RADIUS);
        Sitter_Hour(8);
        Sitter_Minute(0);
        Sitter_Duration(30);
        Sitter_Speed(Settler_Speed_e::WALK);
    }

    void Settler_t::Default_Eater()
    {
        Eater_Radius(DEFAULT_RADIUS);
        Eater_Hour(12);
        Eater_Minute(0);
        Eater_Duration(2 * 60);
        Eater_Attention(0);
        Eater_Speed(Settler_Speed_e::FAST_WALK);
    }

    void Settler_t::Default_Guard()
    {
        Guard_Radius(DEFAULT_RADIUS);
        Guard_Hour(2 + 12);
        Guard_Minute(0);
        Guard_Duration(6 * 60);
        Guard_Speed(Settler_Speed_e::RUN);
    }

    /* Enable/Disable */

    void Settler_t::Enable_Sleeper()
    {
        if (Is_Sandboxer() && !Is_Sleeper()) {
            Actor_t* actor = Actor();
            Create_Sleeper(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Enable_Sitter()
    {
        if (Is_Sandboxer() && !Is_Sitter()) {
            Actor_t* actor = Actor();
            Create_Sitter(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Enable_Eater()
    {
        if (Is_Sandboxer() && !Is_Eater()) {
            Actor_t* actor = Actor();
            Create_Eater(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Enable_Guard()
    {
        if (Is_Sandboxer() && !Is_Guard()) {
            Actor_t* actor = Actor();
            Create_Guard(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Disable_Sleeper()
    {
        if (Is_Sleeper()) {
            Actor_t* actor = Actor();
            Destroy_Sleeper(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Disable_Sitter()
    {
        if (Is_Sitter()) {
            Actor_t* actor = Actor();
            Destroy_Sitter(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Disable_Eater()
    {
        if (Is_Eater()) {
            Actor_t* actor = Actor();
            Destroy_Eater(actor);
            Enforce(actor, true);
        }
    }

    void Settler_t::Disable_Guard()
    {
        if (Is_Guard()) {
            Actor_t* actor = Actor();
            Destroy_Guard(actor);
            Enforce(actor, true);
        }
    }

    /* Move Marker */

    inline void Move_Marker(Settler_t* self, Reference_t* marker)
    {
        if (marker) {
            Actor_t* actor = self->Actor();
            Object_Ref::Move_To_Orbit(marker, Consts::Player_Actor(), 0.0f, 180.0f);
            self->Enforce(actor);
            Actor2::Evaluate_Package(actor);
        }
    }

    void Settler_t::Move_Sandboxer_Marker()
    {
        if (Is_Sandboxer()) {
            Move_Marker(this, Sandboxer_Marker());
        }
    }

    void Settler_t::Move_Sleeper_Marker()
    {
        if (Is_Sleeper()) {
            Move_Marker(this, Sleeper_Marker());
        }
    }

    void Settler_t::Move_Sitter_Marker()
    {
        if (Is_Sitter()) {
            Move_Marker(this, Sitter_Marker());
        }
    }

    void Settler_t::Move_Eater_Marker()
    {
        if (Is_Eater()) {
            Move_Marker(this, Eater_Marker());
        }
    }

    void Settler_t::Move_Guard_Marker()
    {
        if (Is_Guard()) {
            Move_Marker(this, Guard_Marker());
        }
    }

    /* Enforce */

    void Settler_t::Enforce(Actor_t* actor, Bool_t force_reset_ai)
    {
        Bool_t do_reset_ai = force_reset_ai;

        auto Enforce_Location = [&](Package_t* package, Reference_t* marker, Int_t radius, UInt16 value_index)->void
        {
            Package_Location_t* location = static_cast<Package_Location_Value_t*>
                (package->data->values[value_index])->location;
            UInt32 marker_handle = marker->CreateRefHandle();
            if (location->location.handle != marker_handle) {
                do_reset_ai = true;
                location->location.handle = marker_handle;
            }
            if (location->radius != radius) {
                do_reset_ai = true;
                location->radius = radius;
            }
        };

        auto Enforce_Time = [&](Package_t* package, Int_t hour, Int_t minute, Int_t duration)->void
        {
            Package_Schedule_t& schedule = package->schedule;
            if (schedule.hour != hour) {
                do_reset_ai = true;
                schedule.hour = hour;
            }
            if (schedule.minute != minute) {
                do_reset_ai = true;
                schedule.minute = minute;
            }
            if (schedule.duration_in_minutes != duration) {
                do_reset_ai = true;
                schedule.duration_in_minutes = duration;
            }
        };

        auto Enforce_Attention = [&](Package_t* package, Float_t attention, UInt16 value_index)->void
        {
            Package_Float_Value_t* value = static_cast<Package_Float_Value_t*>
                (package->data->values[value_index]);
            if (value->value != attention) {
                do_reset_ai = true;
                value->value = attention;
            }
        };

        auto Enforce_Speed = [&](Package_t* package, Settler_Speed_e speed)->void
        {
            package->flags |= static_cast<UInt32>(Package_t::General_Flag_e::PREFERRED_SPEED);
            package->preferred_speed = speed;
        };

        auto Enforce_Sandboxer = [&]()->void
        {
            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Sandboxer_Value_e::LOCATION),
                ATTENTION = static_cast<UInt16>(Sandboxer_Value_e::ATTENTION),
            };

            if (Is_Sandboxer()) {
                Package_t* package = Sandboxer_Package();
                Enforce_Location(package, Sandboxer_Marker(), Sandboxer_Radius(), LOCATION);
                Enforce_Attention(package, Sandboxer_Attention(), ATTENTION);
                Enforce_Speed(package, Sandboxer_Speed());

                Object_Ref::Token(actor, Consts::Settler_Token());
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Token());
            }
        };

        auto Enforce_Sleeper = [&]()->void
        {
            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Sleeper_Value_e::LOCATION),
                ATTENTION = static_cast<UInt16>(Sleeper_Value_e::ATTENTION),
            };

            if (Is_Sleeper()) {
                Package_t* package = Sleeper_Package();
                Enforce_Location(package, Sleeper_Marker(), Sleeper_Radius(), LOCATION);
                Enforce_Time(package, Sleeper_Hour(), Sleeper_Minute(), Sleeper_Duration());
                Enforce_Attention(package, Sleeper_Attention(), ATTENTION);
                Enforce_Speed(package, Sleeper_Speed());

                Object_Ref::Token(actor, Consts::Settler_Sleeper_Token());
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Sleeper_Token());
            }
        };

        auto Enforce_Sitter = [&]()
        {
            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Sitter_Value_e::LOCATION),
            };

            if (Is_Sitter()) {
                Package_t* package = Sitter_Package();
                Enforce_Location(package, Sitter_Marker(), Sitter_Radius(), LOCATION);
                Enforce_Time(package, Sitter_Hour(), Sitter_Minute(), Sitter_Duration());
                Enforce_Speed(package, Sitter_Speed());

                Object_Ref::Token(actor, Consts::Settler_Sitter_Token());
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Sitter_Token());
            }
        };

        auto Enforce_Eater = [&]()->void
        {
            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Eater_Value_e::LOCATION),
                ATTENTION = static_cast<UInt16>(Eater_Value_e::ATTENTION),
            };

            if (Is_Eater()) {
                Package_t* package = Eater_Package();
                Enforce_Location(package, Eater_Marker(), Eater_Radius(), LOCATION);
                Enforce_Time(package, Eater_Hour(), Eater_Minute(), Eater_Duration());
                Enforce_Attention(package, Eater_Attention(), ATTENTION);
                Enforce_Speed(package, Eater_Speed());

                Object_Ref::Token(actor, Consts::Settler_Eater_Token());
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Eater_Token());
            }
        };

        auto Enforce_Guard = [&]()->void
        {
            enum : UInt16 {
                WAIT_LOCATION = static_cast<UInt16>(Guard_Value_e::WAIT_LOCATION),
                RESTRICTED_LOCATION = static_cast<UInt16>(Guard_Value_e::RESTRICTED_LOCATION),
            };

            if (Is_Guard()) {
                Package_t* package = Guard_Package();
                Enforce_Location(package, Guard_Marker(), 0, WAIT_LOCATION);
                Enforce_Location(package, Guard_Marker(), Guard_Radius(), RESTRICTED_LOCATION);
                Enforce_Time(package, Guard_Hour(), Guard_Minute(), Guard_Duration());
                Enforce_Speed(package, Guard_Speed());

                Object_Ref::Token(actor, Consts::Settler_Guard_Token());
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Guard_Token());
            }
        };

        Enforce_Sandboxer();
        Enforce_Sleeper();
        Enforce_Sitter();
        Enforce_Eater();
        Enforce_Guard();

        if (do_reset_ai) {
            Actor2::Reset_AI(actor);
        }
    }

}}}
