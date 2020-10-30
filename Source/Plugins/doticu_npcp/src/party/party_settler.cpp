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

    /* Sandboxer_t */

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
        MIN_WANDER_DISTANCE,        // Float
    };

    Variable_t* Sandboxer_t::Radius_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_radius"); }
    Variable_t* Sandboxer_t::Movement_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_movement"); }
    Variable_t* Sandboxer_t::Wander_Distance_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_wander_distance"); }
    Variable_t* Sandboxer_t::Flags_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_flags"); }

    /* Sleeper_t */

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

    Variable_t* Sleeper_t::Marker_Variable() { DEFINE_VARIABLE("p_settler_sleeper_marker"); }
    Variable_t* Sleeper_t::Radius_Variable() { DEFINE_VARIABLE("p_settler_sleeper_radius"); }
    Variable_t* Sleeper_t::Time_Variable() { DEFINE_VARIABLE("p_settler_sleeper_time"); }
    Variable_t* Sleeper_t::Duration_Variable() { DEFINE_VARIABLE("p_settler_sleeper_duration"); }
    Variable_t* Sleeper_t::Movement_Variable() { DEFINE_VARIABLE("p_settler_sleeper_movement"); }
    Variable_t* Sleeper_t::Wander_Distance_Variable() { DEFINE_VARIABLE("p_settler_sleeper_wander_distance"); }
    Variable_t* Sleeper_t::Flags_Variable() { DEFINE_VARIABLE("p_settler_sleeper_flags"); }
    Variable_t* Sleeper_t::Bed_Variable() { DEFINE_VARIABLE("p_settler_sleeper_bed"); }

    /* Sitter_t */

    enum class Sitter_Value_e : UInt16 {
        LOCATION = 0,               // Location
        SEARCH_CRITERIA,            // Target_Selector
        CHAIR_LIST,                 // Object_List
        WAIT_TIME,                  // Float
        DO_STOP_MOVEMENT,           // Bool
        DO_PREFERRED_PATH_ONLY,     // Bool
        FALSE_BOOL,                 // Bool
    };

    Variable_t* Sitter_t::Marker_Variable() { DEFINE_VARIABLE("p_settler_sitter_marker"); }
    Variable_t* Sitter_t::Radius_Variable() { DEFINE_VARIABLE("p_settler_sitter_radius"); }
    Variable_t* Sitter_t::Time_Variable() { DEFINE_VARIABLE("p_settler_sitter_time"); }
    Variable_t* Sitter_t::Duration_Variable() { DEFINE_VARIABLE("p_settler_sitter_duration"); }
    Variable_t* Sitter_t::Movement_Variable() { DEFINE_VARIABLE("p_settler_sitter_movement"); }
    Variable_t* Sitter_t::Flags_Variable() { DEFINE_VARIABLE("p_settler_sitter_flags"); }

    /* Eater_t */

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

    Variable_t* Eater_t::Marker_Variable() { DEFINE_VARIABLE("p_settler_eater_marker"); }
    Variable_t* Eater_t::Radius_Variable() { DEFINE_VARIABLE("p_settler_eater_radius"); }
    Variable_t* Eater_t::Time_Variable() { DEFINE_VARIABLE("p_settler_eater_time"); }
    Variable_t* Eater_t::Duration_Variable() { DEFINE_VARIABLE("p_settler_eater_duration"); }
    Variable_t* Eater_t::Movement_Variable() { DEFINE_VARIABLE("p_settler_eater_movement"); }
    Variable_t* Eater_t::Wander_Distance_Variable() { DEFINE_VARIABLE("p_settler_eater_wander_distance"); }
    Variable_t* Eater_t::Flags_Variable() { DEFINE_VARIABLE("p_settler_eater_flags"); }

    /* Guard_t */

    enum class Guard_Value_e : UInt16 {
        WAIT_LOCATION,              // Location
        RESTRICTED_LOCATION,        // Location
    };

    Variable_t* Guard_t::Marker_Variable() { DEFINE_VARIABLE("p_settler_guard_marker"); }
    Variable_t* Guard_t::Radius_Variable() { DEFINE_VARIABLE("p_settler_guard_radius"); }
    Variable_t* Guard_t::Time_Variable() { DEFINE_VARIABLE("p_settler_guard_time"); }
    Variable_t* Guard_t::Duration_Variable() { DEFINE_VARIABLE("p_settler_guard_duration"); }
    Variable_t* Guard_t::Movement_Variable() { DEFINE_VARIABLE("p_settler_guard_movement"); }
    Variable_t* Guard_t::Flags_Variable() { DEFINE_VARIABLE("p_settler_guard_flags"); }

    /* Token */

    Misc_t* Sandboxer_t::Token()
    {
        return Consts::Settler_Token();
    }

    Misc_t* Sleeper_t::Token()
    {
        return Consts::Settler_Sleeper_Token();
    }

    Misc_t* Sitter_t::Token()
    {
        return Consts::Settler_Sitter_Token();
    }

    Misc_t* Eater_t::Token()
    {
        return Consts::Settler_Eater_Token();
    }

    Misc_t* Guard_t::Token()
    {
        return Consts::Settler_Guard_Token();
    }

    /* Package */

    Package_t* Sandboxer_t::Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Sleeper_t::Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Sleeper_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Sitter_t::Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Sitter_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Eater_t::Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Eater_Packages_Formlist()->forms.entries[ID()]);
    }

    Package_t* Guard_t::Package()
    {
        return static_cast<Package_t*>
            (Consts::Settler_Guard_Packages_Formlist()->forms.entries[ID()]);
    }

    /* Marker */

    template <typename Type_t>
    Reference_t* Settler_t::Marker()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Marker_Variable();
        return variable->Reference();
    }

    template <>
    Reference_t* Settler_t::Marker<Sandboxer_t>()
    {
        return static_cast<Reference_t*>
            (Consts::Settler_Markers_Formlist()->forms.entries[ID()]);
    }

    Reference_t* Sandboxer_t::Marker() { return Settler_t::Marker<Sandboxer_t>(); }
    Reference_t* Sleeper_t::Marker() { return Settler_t::Marker<Sleeper_t>(); }
    Reference_t* Sitter_t::Marker() { return Settler_t::Marker<Sitter_t>(); }
    Reference_t* Eater_t::Marker() { return Settler_t::Marker<Eater_t>(); }
    Reference_t* Guard_t::Marker() { return Settler_t::Marker<Guard_t>(); }

    /* Move Marker */

    template <typename Type_t>
    void Settler_t::Move_Marker()
    {
        if (static_cast<Type_t*>(this)->Is_Created()) {
            Reference_t* marker = static_cast<Type_t*>(this)->Marker();
            if (marker) {
                Actor_t* actor = Actor();
                Object_Ref::Move_To_Orbit(marker, Consts::Player_Actor(), 0.0f, 180.0f);
                Enforce(actor, true);
            }
        }
    }

    template <>
    void Settler_t::Move_Marker<Sleeper_t>()
    {
        if (static_cast<Sleeper_t*>(this)->Is_Created()) {
            Reference_t* marker = static_cast<Sleeper_t*>(this)->Marker();
            Reference_t* bed = static_cast<Sleeper_t*>(this)->Bed_Variable()->Reference();
            if (marker) {
                Actor_t* actor = Actor();
                Object_Ref::Move_To_Orbit(marker, Consts::Player_Actor(), 0.0f, 180.0f);
                if (bed) {
                    Object_Ref::Move_To_Orbit(bed, marker, 0.0f, 180.0f);
                }
                Enforce(actor, true);
            }
        }
    }

    void Sandboxer_t::Move_Marker() { Settler_t::Move_Marker<Sandboxer_t>(); }
    void Sleeper_t::Move_Marker() { Settler_t::Move_Marker<Sleeper_t>(); }
    void Sitter_t::Move_Marker() { Settler_t::Move_Marker<Sitter_t>(); }
    void Eater_t::Move_Marker() { Settler_t::Move_Marker<Eater_t>(); }
    void Guard_t::Move_Marker() { Settler_t::Move_Marker<Guard_t>(); }

    /* Radius */

    template <typename Type_t>
    Int_t Settler_t::Radius()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Radius_Variable();
        return variable->Int();
    }

    Int_t Sandboxer_t::Radius() { return Settler_t::Radius<Sandboxer_t>(); }
    Int_t Sleeper_t::Radius() { return Settler_t::Radius<Sleeper_t>(); }
    Int_t Sitter_t::Radius() { return Settler_t::Radius<Sitter_t>(); }
    Int_t Eater_t::Radius() { return Settler_t::Radius<Eater_t>(); }
    Int_t Guard_t::Radius() { return Settler_t::Radius<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Radius(Int_t radius)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Radius_Variable();

        if (radius < Settler_t::MIN_RADIUS) {
            radius = Settler_t::MIN_RADIUS;
        } else if (radius > Settler_t::MAX_RADIUS) {
            radius = Settler_t::MAX_RADIUS;
        }

        variable->Int(radius);
    }

    void Sandboxer_t::Radius(Int_t radius) { Settler_t::Radius<Sandboxer_t>(radius); }
    void Sleeper_t::Radius(Int_t radius) { Settler_t::Radius<Sleeper_t>(radius); }
    void Sitter_t::Radius(Int_t radius) { Settler_t::Radius<Sitter_t>(radius); }
    void Eater_t::Radius(Int_t radius) { Settler_t::Radius<Eater_t>(radius); }
    void Guard_t::Radius(Int_t radius) { Settler_t::Radius<Guard_t>(radius); }

    /* Hour */

    template <typename Type_t>
    Int_t Settler_t::Hour()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Time_Variable();

        return static_cast<Int_t>(
            (static_cast<UInt32>(variable->Int()) & Settler_t::TIME_HOUR_MASK) >>
            Settler_t::TIME_HOUR_IDX
        );
    }

    template <> Int_t Settler_t::Hour<Sandboxer_t>() = delete;
    Int_t Sleeper_t::Hour() { return Settler_t::Hour<Sleeper_t>(); }
    Int_t Sitter_t::Hour() { return Settler_t::Hour<Sitter_t>(); }
    Int_t Eater_t::Hour() { return Settler_t::Hour<Eater_t>(); }
    Int_t Guard_t::Hour() { return Settler_t::Hour<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Hour(Int_t hour)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Time_Variable();

        if (hour < Settler_t::MIN_TIME_HOUR) {
            hour = Settler_t::MIN_TIME_HOUR;
        } else if (hour > Settler_t::MAX_TIME_HOUR) {
            hour = Settler_t::MAX_TIME_HOUR;
        }

        Int_t mask = variable->Int();
        variable->Int(
            (static_cast<UInt32>(mask) & Settler_t::TIME_AM_PM_MASK) |
            ((static_cast<UInt32>(hour) << Settler_t::TIME_HOUR_IDX) & Settler_t::TIME_HOUR_MASK) |
            (static_cast<UInt32>(mask) & Settler_t::TIME_MINUTE_MASK)
        );
    }

    template <> void Settler_t::Hour<Sandboxer_t>(Int_t hour) = delete;
    void Sleeper_t::Hour(Int_t hour) { Settler_t::Hour<Sleeper_t>(hour); }
    void Sitter_t::Hour(Int_t hour) { Settler_t::Hour<Sitter_t>(hour); }
    void Eater_t::Hour(Int_t hour) { Settler_t::Hour<Eater_t>(hour); }
    void Guard_t::Hour(Int_t hour) { Settler_t::Hour<Guard_t>(hour); }

    template <typename Type_t>
    String_t Settler_t::Hour_String()
    {
        Int_t hour = static_cast<Type_t*>(this)->Hour();

        if (hour < Settler_t::MIN_TIME_HOUR) {
            hour = Settler_t::MIN_TIME_HOUR;
        } else if (hour > Settler_t::MAX_TIME_HOUR) {
            hour = Settler_t::MAX_TIME_HOUR;
        }

        return (" " + std::to_string(hour) + " ").c_str();
    }

    template <> String_t Settler_t::Hour_String<Sandboxer_t>() = delete;
    String_t Sleeper_t::Hour_String() { return Settler_t::Hour_String<Sleeper_t>(); }
    String_t Sitter_t::Hour_String() { return Settler_t::Hour_String<Sitter_t>(); }
    String_t Eater_t::Hour_String() { return Settler_t::Hour_String<Eater_t>(); }
    String_t Guard_t::Hour_String() { return Settler_t::Hour_String<Guard_t>(); }

    /* Minute */

    template <typename Type_t>
    Int_t Settler_t::Minute()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Time_Variable();

        return static_cast<Int_t>(
            (static_cast<UInt32>(variable->Int()) & Settler_t::TIME_MINUTE_MASK) >>
            Settler_t::TIME_MINUTE_IDX
        );
    }

    template <> Int_t Settler_t::Minute<Sandboxer_t>() = delete;
    Int_t Sleeper_t::Minute() { return Settler_t::Minute<Sleeper_t>(); }
    Int_t Sitter_t::Minute() { return Settler_t::Minute<Sitter_t>(); }
    Int_t Eater_t::Minute() { return Settler_t::Minute<Eater_t>(); }
    Int_t Guard_t::Minute() { return Settler_t::Minute<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Minute(Int_t minute)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Time_Variable();

        if (minute < Settler_t::MIN_TIME_MINUTE) {
            minute = Settler_t::MIN_TIME_MINUTE;
        } else if (minute > Settler_t::MAX_TIME_MINUTE) {
            minute = Settler_t::MAX_TIME_MINUTE;
        }

        Int_t mask = variable->Int();
        variable->Int(
            (static_cast<UInt32>(mask) & Settler_t::TIME_AM_PM_MASK) |
            (static_cast<UInt32>(mask) & Settler_t::TIME_HOUR_MASK) |
            ((static_cast<UInt32>(minute) << Settler_t::TIME_MINUTE_IDX) & Settler_t::TIME_MINUTE_MASK)
        );
    }

    template <> void Settler_t::Minute<Sandboxer_t>(Int_t minute) = delete;
    void Sleeper_t::Minute(Int_t minute) { Settler_t::Minute<Sleeper_t>(minute); }
    void Sitter_t::Minute(Int_t minute) { Settler_t::Minute<Sitter_t>(minute); }
    void Eater_t::Minute(Int_t minute) { Settler_t::Minute<Eater_t>(minute); }
    void Guard_t::Minute(Int_t minute) { Settler_t::Minute<Guard_t>(minute); }

    template <typename Type_t>
    String_t Settler_t::Minute_String()
    {
        Int_t minute = static_cast<Type_t*>(this)->Minute();

        if (minute < Settler_t::MIN_TIME_MINUTE) {
            minute = Settler_t::MIN_TIME_MINUTE;
        } else if (minute > Settler_t::MAX_TIME_MINUTE) {
            minute = Settler_t::MAX_TIME_MINUTE;
        }

        if (minute < 10) {
            return (" 0" + std::to_string(minute) + " ").c_str();
        } else {
            return (" " + std::to_string(minute) + " ").c_str();
        }
    }

    template <> String_t Settler_t::Minute_String<Sandboxer_t>() = delete;
    String_t Sleeper_t::Minute_String() { return Settler_t::Minute_String<Sleeper_t>(); }
    String_t Sitter_t::Minute_String() { return Settler_t::Minute_String<Sitter_t>(); }
    String_t Eater_t::Minute_String() { return Settler_t::Minute_String<Eater_t>(); }
    String_t Guard_t::Minute_String() { return Settler_t::Minute_String<Guard_t>(); }

    /* AM PM */

    template <typename Type_t>
    AM_PM_e Settler_t::AM_PM()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Time_Variable();

        return static_cast<AM_PM_e>(
            (static_cast<UInt32>(variable->Int()) & Settler_t::TIME_AM_PM_MASK) >>
            Settler_t::TIME_AM_PM_IDX
        );
    }

    template <> AM_PM_e Settler_t::AM_PM<Sandboxer_t>() = delete;
    AM_PM_e Sleeper_t::AM_PM() { return Settler_t::AM_PM<Sleeper_t>(); }
    AM_PM_e Sitter_t::AM_PM() { return Settler_t::AM_PM<Sitter_t>(); }
    AM_PM_e Eater_t::AM_PM() { return Settler_t::AM_PM<Eater_t>(); }
    AM_PM_e Guard_t::AM_PM() { return Settler_t::AM_PM<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::AM_PM(AM_PM_e am_pm)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Time_Variable();

        if (am_pm != AM_PM_e::AM && am_pm != AM_PM_e::PM) {
            am_pm = AM_PM_e::AM;
        }

        Int_t mask = variable->Int();
        variable->Int(
            ((static_cast<UInt32>(am_pm) << Settler_t::TIME_AM_PM_IDX) & Settler_t::TIME_AM_PM_MASK) |
            (static_cast<UInt32>(mask) & Settler_t::TIME_HOUR_MASK) |
            (static_cast<UInt32>(mask) & Settler_t::TIME_MINUTE_MASK)
        );
    }

    template <> void Settler_t::AM_PM<Sandboxer_t>(AM_PM_e am_pm) = delete;
    void Sleeper_t::AM_PM(AM_PM_e am_pm) { Settler_t::AM_PM<Sleeper_t>(am_pm); }
    void Sitter_t::AM_PM(AM_PM_e am_pm) { Settler_t::AM_PM<Sitter_t>(am_pm); }
    void Eater_t::AM_PM(AM_PM_e am_pm) { Settler_t::AM_PM<Eater_t>(am_pm); }
    void Guard_t::AM_PM(AM_PM_e am_pm) { Settler_t::AM_PM<Guard_t>(am_pm); }

    template <typename Type_t>
    String_t Settler_t::AM_PM_String()
    {
        AM_PM_e am_pm = static_cast<Type_t*>(this)->AM_PM();

        if (am_pm != AM_PM_e::AM && am_pm != AM_PM_e::PM) {
            am_pm = AM_PM_e::AM;
        }

        if (am_pm == AM_PM_e::AM) {
            return " AM ";
        } else {
            return " PM ";
        }
    }

    template <> String_t Settler_t::AM_PM_String<Sandboxer_t>() = delete;
    String_t Sleeper_t::AM_PM_String() { return Settler_t::AM_PM_String<Sleeper_t>(); }
    String_t Sitter_t::AM_PM_String() { return Settler_t::AM_PM_String<Sitter_t>(); }
    String_t Eater_t::AM_PM_String() { return Settler_t::AM_PM_String<Eater_t>(); }
    String_t Guard_t::AM_PM_String() { return Settler_t::AM_PM_String<Guard_t>(); }

    /* Hour Duration */

    template <typename Type_t>
    Int_t Settler_t::Duration_Hours()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Duration_Variable();

        return static_cast<Int_t>(
            (static_cast<UInt32>(variable->Int()) & Settler_t::DURATION_HOURS_MASK) >> 16
        );
    }

    template <> Int_t Settler_t::Duration_Hours<Sandboxer_t>() = delete;
    Int_t Sleeper_t::Duration_Hours() { return Settler_t::Duration_Hours<Sleeper_t>(); }
    Int_t Sitter_t::Duration_Hours() { return Settler_t::Duration_Hours<Sitter_t>(); }
    Int_t Eater_t::Duration_Hours() { return Settler_t::Duration_Hours<Eater_t>(); }
    Int_t Guard_t::Duration_Hours() { return Settler_t::Duration_Hours<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Duration_Hours(Int_t hours)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Duration_Variable();

        if (hours < Settler_t::MIN_DURATION_HOURS) {
            hours = Settler_t::MIN_DURATION_HOURS;
        } else if (hours > Settler_t::MAX_DURATION_HOURS) {
            hours = Settler_t::MAX_DURATION_HOURS;
        }

        variable->Int(
            (static_cast<UInt32>(hours) << 16) |
            (static_cast<UInt32>(hours == Settler_t::MAX_DURATION_HOURS ? 0 : variable->Int()) & Settler_t::DURATION_MINUTES_MASK)
        );
    }

    template <> void Settler_t::Duration_Hours<Sandboxer_t>(Int_t hours) = delete;
    void Sleeper_t::Duration_Hours(Int_t hours) { Settler_t::Duration_Hours<Sleeper_t>(hours); }
    void Sitter_t::Duration_Hours(Int_t hours) { Settler_t::Duration_Hours<Sitter_t>(hours); }
    void Eater_t::Duration_Hours(Int_t hours) { Settler_t::Duration_Hours<Eater_t>(hours); }
    void Guard_t::Duration_Hours(Int_t hours) { Settler_t::Duration_Hours<Guard_t>(hours); }

    template <typename Type_t>
    String_t Settler_t::Duration_Hours_String()
    {
        Int_t hours = static_cast<Type_t*>(this)->Duration_Hours();
        Int_t minutes = static_cast<Type_t*>(this)->Duration_Minutes();

        if (hours < Settler_t::MIN_DURATION_HOURS) {
            hours = Settler_t::MIN_DURATION_HOURS;
        } else if (hours > Settler_t::MAX_DURATION_HOURS) {
            hours = Settler_t::MAX_DURATION_HOURS;
        }

        if (minutes < Settler_t::MIN_DURATION_MINUTES) {
            minutes = Settler_t::MIN_DURATION_MINUTES;
        } else if (minutes > Settler_t::MAX_DURATION_MINUTES) {
            minutes = Settler_t::MAX_DURATION_MINUTES;
        }

        if ((hours * 60) + minutes == 0) {
            return " Never ";
        } else {
            if (hours == 1) {
                return " 1 hour ";
            } else {
                return (" " + std::to_string(hours) + " hours ").c_str();
            }
        }
    }

    template <> String_t Settler_t::Duration_Hours_String<Sandboxer_t>() = delete;
    String_t Sleeper_t::Duration_Hours_String() { return Settler_t::Duration_Hours_String<Sleeper_t>(); }
    String_t Sitter_t::Duration_Hours_String() { return Settler_t::Duration_Hours_String<Sitter_t>(); }
    String_t Eater_t::Duration_Hours_String() { return Settler_t::Duration_Hours_String<Eater_t>(); }
    String_t Guard_t::Duration_Hours_String() { return Settler_t::Duration_Hours_String<Guard_t>(); }

    /* Minute Duration */

    template <typename Type_t>
    Int_t Settler_t::Duration_Minutes()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Duration_Variable();

        return static_cast<Int_t>(
            static_cast<UInt32>(variable->Int()) & Settler_t::DURATION_MINUTES_MASK
        );
    }

    template <> Int_t Settler_t::Duration_Minutes<Sandboxer_t>() = delete;
    Int_t Sleeper_t::Duration_Minutes() { return Settler_t::Duration_Minutes<Sleeper_t>(); }
    Int_t Sitter_t::Duration_Minutes() { return Settler_t::Duration_Minutes<Sitter_t>(); }
    Int_t Eater_t::Duration_Minutes() { return Settler_t::Duration_Minutes<Eater_t>(); }
    Int_t Guard_t::Duration_Minutes() { return Settler_t::Duration_Minutes<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Duration_Minutes(Int_t minutes)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Duration_Variable();
        Int_t hours = static_cast<Type_t*>(this)->Duration_Hours();

        if (minutes < Settler_t::MIN_DURATION_MINUTES) {
            minutes = Settler_t::MIN_DURATION_MINUTES;
        } else if (minutes > Settler_t::MAX_DURATION_MINUTES) {
            minutes = Settler_t::MAX_DURATION_MINUTES;
        }

        variable->Int(
            (static_cast<UInt32>(variable->Int()) & Settler_t::DURATION_HOURS_MASK) |
            (static_cast<UInt32>(hours == Settler_t::MAX_DURATION_HOURS ? 0 : minutes) & Settler_t::DURATION_MINUTES_MASK)
        );
    }

    template <> void Settler_t::Duration_Minutes<Sandboxer_t>(Int_t minutes) = delete;
    void Sleeper_t::Duration_Minutes(Int_t minutes) { Settler_t::Duration_Minutes<Sleeper_t>(minutes); }
    void Sitter_t::Duration_Minutes(Int_t minutes) { Settler_t::Duration_Minutes<Sitter_t>(minutes); }
    void Eater_t::Duration_Minutes(Int_t minutes) { Settler_t::Duration_Minutes<Eater_t>(minutes); }
    void Guard_t::Duration_Minutes(Int_t minutes) { Settler_t::Duration_Minutes<Guard_t>(minutes); }

    template <typename Type_t>
    String_t Settler_t::Duration_Minutes_String()
    {
        Int_t hours = static_cast<Type_t*>(this)->Duration_Hours();
        Int_t minutes = static_cast<Type_t*>(this)->Duration_Minutes();

        if (hours < Settler_t::MIN_DURATION_HOURS) {
            hours = Settler_t::MIN_DURATION_HOURS;
        } else if (hours > Settler_t::MAX_DURATION_HOURS) {
            hours = Settler_t::MAX_DURATION_HOURS;
        }

        if (minutes < Settler_t::MIN_DURATION_MINUTES) {
            minutes = Settler_t::MIN_DURATION_MINUTES;
        } else if (minutes > Settler_t::MAX_DURATION_MINUTES) {
            minutes = Settler_t::MAX_DURATION_MINUTES;
        }

        if ((hours * 60) + minutes == 0) {
            return " Never ";
        } else {
            if (minutes == 1) {
                return " 1 minute ";
            } else {
                return (" " + std::to_string(minutes) + " minutes ").c_str();
            }
        }
    }

    template <> String_t Settler_t::Duration_Minutes_String<Sandboxer_t>() = delete;
    String_t Sleeper_t::Duration_Minutes_String() { return Settler_t::Duration_Minutes_String<Sleeper_t>(); }
    String_t Sitter_t::Duration_Minutes_String() { return Settler_t::Duration_Minutes_String<Sitter_t>(); }
    String_t Eater_t::Duration_Minutes_String() { return Settler_t::Duration_Minutes_String<Eater_t>(); }
    String_t Guard_t::Duration_Minutes_String() { return Settler_t::Duration_Minutes_String<Guard_t>(); }

    /* Attention */

    template <typename Type_t>
    Int_t Settler_t::Attention()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Movement_Variable();

        return static_cast<Int_t>(
            (static_cast<UInt32>(variable->Int()) & Settler_t::ATTENTION_MASK) >> 16
        );
    }

    Int_t Sandboxer_t::Attention() { return Settler_t::Attention<Sandboxer_t>(); }
    Int_t Sleeper_t::Attention() { return Settler_t::Attention<Sleeper_t>(); }
    template <> Int_t Settler_t::Attention<Sitter_t>() = delete;
    Int_t Eater_t::Attention() { return Settler_t::Attention<Eater_t>(); }
    template <> Int_t Settler_t::Attention<Guard_t>() = delete;

    template <typename Type_t>
    void Settler_t::Attention(Int_t attention)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Movement_Variable();

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

    void Sandboxer_t::Attention(Int_t attention) { Settler_t::Attention<Sandboxer_t>(attention); }
    void Sleeper_t::Attention(Int_t attention) { Settler_t::Attention<Sleeper_t>(attention); }
    template <> void Settler_t::Attention<Sitter_t>(Int_t attention) = delete;
    void Eater_t::Attention(Int_t attention) { Settler_t::Attention<Eater_t>(attention); }
    template <> void Settler_t::Attention<Guard_t>(Int_t attention) = delete;

    /* Speed */

    template <typename Type_t>
    Settler_Speed_e Settler_t::Speed()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Movement_Variable();

        return static_cast<Settler_Speed_e>(
            static_cast<UInt32>(variable->Int()) & Settler_t::SPEED_MASK
        );
    }

    Settler_Speed_e Sandboxer_t::Speed() { return Settler_t::Speed<Sandboxer_t>(); }
    Settler_Speed_e Sleeper_t::Speed() { return Settler_t::Speed<Sleeper_t>(); }
    Settler_Speed_e Sitter_t::Speed() { return Settler_t::Speed<Sitter_t>(); }
    Settler_Speed_e Eater_t::Speed() { return Settler_t::Speed<Eater_t>(); }
    Settler_Speed_e Guard_t::Speed() { return Settler_t::Speed<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Speed(Settler_Speed_e speed)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Movement_Variable();

        variable->Int(
            (static_cast<UInt32>(variable->Int()) & Settler_t::ATTENTION_MASK) |
            (static_cast<UInt32>(speed) & Settler_t::SPEED_MASK)
        );
    }

    void Sandboxer_t::Speed(Settler_Speed_e speed) { Settler_t::Speed<Sandboxer_t>(speed); }
    void Sleeper_t::Speed(Settler_Speed_e speed) { Settler_t::Speed<Sleeper_t>(speed); }
    void Sitter_t::Speed(Settler_Speed_e speed) { Settler_t::Speed<Sitter_t>(speed); }
    void Eater_t::Speed(Settler_Speed_e speed) { Settler_t::Speed<Eater_t>(speed); }
    void Guard_t::Speed(Settler_Speed_e speed) { Settler_t::Speed<Guard_t>(speed); }

    template <typename Type_t>
    String_t Settler_t::Speed_String()
    {
        Settler_Speed_e speed = static_cast<Type_t*>(this)->Speed();

        if (speed == Settler_Speed_e::WALK) {
            return " Walk ";
        } else if (speed == Settler_Speed_e::FAST_WALK) {
            return " Fast Walk ";
        } else if (speed == Settler_Speed_e::JOG) {
            return " Jog ";
        } else if (speed == Settler_Speed_e::RUN) {
            return " Run ";
        } else {
            return "";
        }
    }

    String_t Sandboxer_t::Speed_String() { return Settler_t::Speed_String<Sandboxer_t>(); }
    String_t Sleeper_t::Speed_String() { return Settler_t::Speed_String<Sleeper_t>(); }
    String_t Sitter_t::Speed_String() { return Settler_t::Speed_String<Sitter_t>(); }
    String_t Eater_t::Speed_String() { return Settler_t::Speed_String<Eater_t>(); }
    String_t Guard_t::Speed_String() { return Settler_t::Speed_String<Guard_t>(); }

    /* Wander Distance */

    template <typename Type_t>
    Int_t Settler_t::Wander_Distance()
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Wander_Distance_Variable();

        return variable->Int();
    }

    Int_t Sandboxer_t::Wander_Distance() { return Settler_t::Wander_Distance<Sandboxer_t>(); }
    Int_t Sleeper_t::Wander_Distance() { return Settler_t::Wander_Distance<Sleeper_t>(); }
    template <> Int_t Settler_t::Wander_Distance<Sitter_t>() = delete;
    Int_t Eater_t::Wander_Distance() { return Settler_t::Wander_Distance<Eater_t>(); }
    template <> Int_t Settler_t::Wander_Distance<Guard_t>() = delete;

    template <typename Type_t>
    void Settler_t::Wander_Distance(Int_t distance)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Wander_Distance_Variable();

        if (distance < Settler_t::MIN_RADIUS) {
            distance = Settler_t::MIN_RADIUS;
        } else if (distance > Settler_t::MAX_RADIUS) {
            distance = Settler_t::MAX_RADIUS;
        }

        variable->Int(distance);
    }

    void Sandboxer_t::Wander_Distance(Int_t distance) { Settler_t::Wander_Distance<Sandboxer_t>(distance); }
    void Sleeper_t::Wander_Distance(Int_t distance) { Settler_t::Wander_Distance<Sleeper_t>(distance); }
    template <> void Settler_t::Wander_Distance<Sitter_t>(Int_t distance) = delete;
    void Eater_t::Wander_Distance(Int_t distance) { Settler_t::Wander_Distance<Eater_t>(distance); }
    template <> void Settler_t::Wander_Distance<Guard_t>(Int_t distance) = delete;

    /* Flag */

    template <typename Type_t>
    Bool_t Settler_t::Is_Flagged(UInt32 flag)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Flags_Variable();

        return (static_cast<UInt32>(variable->Int()) & (static_cast<UInt32>(1) << flag)) > 0;
    }

    Bool_t Sandboxer_t::Is_Flagged(Sandboxer_t::Flag_e flag) { return Settler_t::Is_Flagged<Sandboxer_t>(static_cast<UInt32>(flag)); }
    Bool_t Sleeper_t::Is_Flagged(Sleeper_t::Flag_e flag) { return Settler_t::Is_Flagged<Sleeper_t>(static_cast<UInt32>(flag)); }
    Bool_t Sitter_t::Is_Flagged(Sitter_t::Flag_e flag) { return Settler_t::Is_Flagged<Sitter_t>(static_cast<UInt32>(flag)); }
    Bool_t Eater_t::Is_Flagged(Eater_t::Flag_e flag) { return Settler_t::Is_Flagged<Eater_t>(static_cast<UInt32>(flag)); }
    Bool_t Guard_t::Is_Flagged(Guard_t::Flag_e flag) { return Settler_t::Is_Flagged<Guard_t>(static_cast<UInt32>(flag)); }

    template <typename Type_t>
    void Settler_t::Flag(UInt32 flag)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Flags_Variable();

        variable->Int(
            static_cast<UInt32>(variable->Int()) |
            (static_cast<UInt32>(1) << flag)
        );
    }

    void Sandboxer_t::Flag(Sandboxer_t::Flag_e flag) { Settler_t::Flag<Sandboxer_t>(static_cast<UInt32>(flag)); }
    void Sleeper_t::Flag(Sleeper_t::Flag_e flag) { Settler_t::Flag<Sleeper_t>(static_cast<UInt32>(flag)); }
    void Sitter_t::Flag(Sitter_t::Flag_e flag) { Settler_t::Flag<Sitter_t>(static_cast<UInt32>(flag)); }
    void Eater_t::Flag(Eater_t::Flag_e flag) { Settler_t::Flag<Eater_t>(static_cast<UInt32>(flag)); }
    void Guard_t::Flag(Guard_t::Flag_e flag) { Settler_t::Flag<Guard_t>(static_cast<UInt32>(flag)); }

    template <typename Type_t>
    void Settler_t::Unflag(UInt32 flag)
    {
        Variable_t* variable = static_cast<Type_t*>(this)->Flags_Variable();

        variable->Int(
            static_cast<UInt32>(variable->Int()) &
            ~(static_cast<UInt32>(1) << flag)
        );
    }

    void Sandboxer_t::Unflag(Sandboxer_t::Flag_e flag) { Settler_t::Unflag<Sandboxer_t>(static_cast<UInt32>(flag)); }
    void Sleeper_t::Unflag(Sleeper_t::Flag_e flag) { Settler_t::Unflag<Sleeper_t>(static_cast<UInt32>(flag)); }
    void Sitter_t::Unflag(Sitter_t::Flag_e flag) { Settler_t::Unflag<Sitter_t>(static_cast<UInt32>(flag)); }
    void Eater_t::Unflag(Eater_t::Flag_e flag) { Settler_t::Unflag<Eater_t>(static_cast<UInt32>(flag)); }
    void Guard_t::Unflag(Guard_t::Flag_e flag) { Settler_t::Unflag<Guard_t>(static_cast<UInt32>(flag)); }

    /* Create/Destroy */

    template <typename Type_t>
    Bool_t Settler_t::Is_Created()
    {
        return static_cast<Type_t*>(this)->Is_Flagged(Type_t::Flag_e::IS_ENABLED);
    }

    Bool_t Sandboxer_t::Is_Created() { return Settler_t::Is_Created<Sandboxer_t>(); }
    Bool_t Sleeper_t::Is_Created() { return Settler_t::Is_Created<Sleeper_t>(); }
    Bool_t Sitter_t::Is_Created() { return Settler_t::Is_Created<Sitter_t>(); }
    Bool_t Eater_t::Is_Created() { return Settler_t::Is_Created<Eater_t>(); }
    Bool_t Guard_t::Is_Created() { return Settler_t::Is_Created<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Create()
    {
        if (Is_Sandboxer() && !static_cast<Type_t*>(this)->Is_Created()) {
            Actor_t* actor = Actor();

            static_cast<Type_t*>(this)->Clear();

            Reference_t* marker = Object_Ref::Create_Marker_At(static_cast<Sandboxer_t*>(this)->Marker());
            static_cast<Type_t*>(this)->Marker_Variable()->Pack(marker);

            static_cast<Type_t*>(this)->Flag(Type_t::Flag_e::IS_ENABLED);
            static_cast<Type_t*>(this)->Default();

            Object_Ref::Token(actor, static_cast<Type_t*>(this)->Token());

            Enforce(actor, true);
        }
    }

    template <>
    void Settler_t::Create<Sandboxer_t>()
    {
        if (!Is_Sandboxer()) {
            Actor_t* actor = Actor();

            static_cast<Sandboxer_t*>(this)->Clear();

            Object_Ref::Move_To_Orbit(static_cast<Sandboxer_t*>(this)->Marker(), Consts::Player_Actor(), 0.0f, 180.0f);

            static_cast<Sandboxer_t*>(this)->Flag(Sandboxer_t::Flag_e::IS_ENABLED);
            static_cast<Sandboxer_t*>(this)->Default();

            Object_Ref::Token(actor, static_cast<Sandboxer_t*>(this)->Token());

            Enforce(actor, true);
        }
    }

    void Sandboxer_t::Create() { Settler_t::Create<Sandboxer_t>(); }
    void Sleeper_t::Create() { Settler_t::Create<Sleeper_t>(); }
    void Sitter_t::Create() { Settler_t::Create<Sitter_t>(); }
    void Eater_t::Create() { Settler_t::Create<Eater_t>(); }
    void Guard_t::Create() { Settler_t::Create<Guard_t>(); }

    template <typename Type_t>
    void Settler_t::Destroy(Bool_t do_enforce)
    {
        if (static_cast<Type_t*>(this)->Is_Created()) {
            Actor_t* actor = Actor();

            Object_Ref::Untoken(actor, static_cast<Type_t*>(this)->Token());

            Reference_t* marker = static_cast<Type_t*>(this)->Marker();
            static_cast<Type_t*>(this)->Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(marker);

            static_cast<Type_t*>(this)->Unflag(Type_t::Flag_e::IS_ENABLED);

            static_cast<Type_t*>(this)->Clear();

            if (do_enforce) {
                Enforce(actor, true);
            }
        }
    }

    template <>
    void Settler_t::Destroy<Sandboxer_t>(Bool_t do_enforce)
    {
        if (Is_Sandboxer()) {
            Actor_t* actor = Actor();

            static_cast<Guard_t*>(this)->Destroy(false);
            static_cast<Eater_t*>(this)->Destroy(false);
            static_cast<Sitter_t*>(this)->Destroy(false);
            static_cast<Sleeper_t*>(this)->Destroy(false);

            Object_Ref::Untoken(actor, static_cast<Sandboxer_t*>(this)->Token());

            Object_Ref::Move_To_Orbit(static_cast<Sandboxer_t*>(this)->Marker(), Consts::Storage_Marker(), 0.0f, 0.0f);

            static_cast<Sandboxer_t*>(this)->Unflag(Sandboxer_t::Flag_e::IS_ENABLED);

            static_cast<Sandboxer_t*>(this)->Clear();

            if (do_enforce) {
                Enforce(actor, true);
            }
        }
    }

    template <>
    void Settler_t::Destroy<Sleeper_t>(Bool_t do_enforce)
    {
        using Type_t = Sleeper_t;

        if (Is_Sleeper()) {
            Actor_t* actor = Actor();

            static_cast<Type_t*>(this)->Destroy_Bed();

            Object_Ref::Untoken(actor, static_cast<Type_t*>(this)->Token());

            Reference_t* marker = static_cast<Type_t*>(this)->Marker();
            static_cast<Type_t*>(this)->Marker_Variable()->None(Object_Ref::Class_Info());
            Object_Ref::Delete_Safe(marker);

            static_cast<Type_t*>(this)->Unflag(Type_t::Flag_e::IS_ENABLED);

            static_cast<Type_t*>(this)->Clear();

            if (do_enforce) {
                Enforce(actor, true);
            }
        }
    }

    void Sandboxer_t::Destroy(Bool_t do_enforce) { Settler_t::Destroy<Sandboxer_t>(do_enforce); }
    void Sleeper_t::Destroy(Bool_t do_enforce) { Settler_t::Destroy<Sleeper_t>(do_enforce); }
    void Sitter_t::Destroy(Bool_t do_enforce) { Settler_t::Destroy<Sitter_t>(do_enforce); }
    void Eater_t::Destroy(Bool_t do_enforce) { Settler_t::Destroy<Eater_t>(do_enforce); }
    void Guard_t::Destroy(Bool_t do_enforce) { Settler_t::Destroy<Guard_t>(do_enforce); }

    /* Default */

    template <>
    void Settler_t::Default<Sandboxer_t>()
    {
        using Type_t = Sandboxer_t;
        using Flag_e = Type_t::Flag_e;

        static_cast<Type_t*>(this)->Radius(DEFAULT_RADIUS);
        static_cast<Type_t*>(this)->Attention(40);
        static_cast<Type_t*>(this)->Speed(Settler_Speed_e::WALK);
        static_cast<Type_t*>(this)->Wander_Distance(DEFAULT_WANDER_DISTANCE);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SWIMMING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALWAYS_SNEAK);
        static_cast<Type_t*>(this)->Unflag(Flag_e::IGNORE_COMBAT);
        static_cast<Type_t*>(this)->Unflag(Flag_e::KEEP_WEAPONS_DRAWN);
        static_cast<Type_t*>(this)->Unflag(Flag_e::HIDE_WEAPONS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::SKIP_COMBAT_ALERT);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_HELLOS_TO_PLAYER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_HELLOS_TO_NPCS);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_IDLE_CHATTER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_WORLD_INTERACTIONS);
        static_cast<Type_t*>(this)->Flag(Flag_e::COMMENT_ON_FRIENDLY_FIRE);
        static_cast<Type_t*>(this)->Flag(Flag_e::INSPECT_CORPSE_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::OBSERVE_COMBAT_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::REACT_TO_PLAYER_ACTIONS);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_CONVERSATION);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_EATING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HORSE_RIDING);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_IDLE_MARKERS);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SITTING);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SLEEPING);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SPECIAL_FURNITURE);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_WANDERING);

        static_cast<Type_t*>(this)->Unflag(Flag_e::PREFERRED_PATH_ONLY);
        static_cast<Type_t*>(this)->Flag(Flag_e::UNLOCK_ON_ARRIVAL);
    }

    template <>
    void Settler_t::Default<Sleeper_t>()
    {
        using Type_t = Sleeper_t;
        using Flag_e = Type_t::Flag_e;

        static_cast<Type_t*>(this)->Radius(DEFAULT_RADIUS);
        static_cast<Type_t*>(this)->Hour(10);
        static_cast<Type_t*>(this)->Minute(30);
        static_cast<Type_t*>(this)->AM_PM(AM_PM_e::PM);
        static_cast<Type_t*>(this)->Duration_Hours(8);
        static_cast<Type_t*>(this)->Duration_Minutes(0);
        static_cast<Type_t*>(this)->Attention(100);
        static_cast<Type_t*>(this)->Speed(Settler_Speed_e::JOG);
        static_cast<Type_t*>(this)->Wander_Distance(DEFAULT_WANDER_DISTANCE);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SWIMMING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALWAYS_SNEAK);
        static_cast<Type_t*>(this)->Unflag(Flag_e::IGNORE_COMBAT);
        static_cast<Type_t*>(this)->Unflag(Flag_e::KEEP_WEAPONS_DRAWN);
        static_cast<Type_t*>(this)->Flag(Flag_e::HIDE_WEAPONS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::SKIP_COMBAT_ALERT);

        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HELLOS_TO_PLAYER);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HELLOS_TO_NPCS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_IDLE_CHATTER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_WORLD_INTERACTIONS);
        static_cast<Type_t*>(this)->Flag(Flag_e::COMMENT_ON_FRIENDLY_FIRE);
        static_cast<Type_t*>(this)->Flag(Flag_e::INSPECT_CORPSE_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::OBSERVE_COMBAT_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::REACT_TO_PLAYER_ACTIONS);

        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_CONVERSATION);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_EATING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HORSE_RIDING);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_IDLE_MARKERS);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SITTING);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SLEEPING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_SPECIAL_FURNITURE);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_WANDERING);

        static_cast<Type_t*>(this)->Unflag(Flag_e::LOCK_DOORS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::PREFERRED_PATH_ONLY);
        static_cast<Type_t*>(this)->Flag(Flag_e::WARN_BEFORE_LOCKING);
    }

    template <>
    void Settler_t::Default<Sitter_t>()
    {
        using Type_t = Sitter_t;
        using Flag_e = Type_t::Flag_e;

        static_cast<Type_t*>(this)->Radius(DEFAULT_RADIUS);
        static_cast<Type_t*>(this)->Hour(8);
        static_cast<Type_t*>(this)->Minute(0);
        static_cast<Type_t*>(this)->AM_PM(AM_PM_e::AM);
        static_cast<Type_t*>(this)->Duration_Hours(0);
        static_cast<Type_t*>(this)->Duration_Minutes(30);
        static_cast<Type_t*>(this)->Speed(Settler_Speed_e::WALK);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SWIMMING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALWAYS_SNEAK);
        static_cast<Type_t*>(this)->Unflag(Flag_e::IGNORE_COMBAT);
        static_cast<Type_t*>(this)->Unflag(Flag_e::KEEP_WEAPONS_DRAWN);
        static_cast<Type_t*>(this)->Unflag(Flag_e::HIDE_WEAPONS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::SKIP_COMBAT_ALERT);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_HELLOS_TO_PLAYER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_HELLOS_TO_NPCS);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_IDLE_CHATTER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_WORLD_INTERACTIONS);
        static_cast<Type_t*>(this)->Flag(Flag_e::COMMENT_ON_FRIENDLY_FIRE);
        static_cast<Type_t*>(this)->Flag(Flag_e::INSPECT_CORPSE_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::OBSERVE_COMBAT_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::REACT_TO_PLAYER_ACTIONS);

        static_cast<Type_t*>(this)->Unflag(Flag_e::PREFERRED_PATH_ONLY);
        static_cast<Type_t*>(this)->Unflag(Flag_e::STOP_MOVEMENT);
    }

    template <>
    void Settler_t::Default<Eater_t>()
    {
        using Type_t = Eater_t;
        using Flag_e = Type_t::Flag_e;

        static_cast<Type_t*>(this)->Radius(DEFAULT_RADIUS);
        static_cast<Type_t*>(this)->Hour(12);
        static_cast<Type_t*>(this)->Minute(0);
        static_cast<Type_t*>(this)->AM_PM(AM_PM_e::PM);
        static_cast<Type_t*>(this)->Duration_Hours(2);
        static_cast<Type_t*>(this)->Duration_Minutes(0);
        static_cast<Type_t*>(this)->Attention(0);
        static_cast<Type_t*>(this)->Speed(Settler_Speed_e::FAST_WALK);
        static_cast<Type_t*>(this)->Wander_Distance(DEFAULT_WANDER_DISTANCE);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_SWIMMING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALWAYS_SNEAK);
        static_cast<Type_t*>(this)->Unflag(Flag_e::IGNORE_COMBAT);
        static_cast<Type_t*>(this)->Unflag(Flag_e::KEEP_WEAPONS_DRAWN);
        static_cast<Type_t*>(this)->Unflag(Flag_e::HIDE_WEAPONS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::SKIP_COMBAT_ALERT);

        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HELLOS_TO_PLAYER);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HELLOS_TO_NPCS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_IDLE_CHATTER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_WORLD_INTERACTIONS);
        static_cast<Type_t*>(this)->Flag(Flag_e::COMMENT_ON_FRIENDLY_FIRE);
        static_cast<Type_t*>(this)->Flag(Flag_e::INSPECT_CORPSE_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::OBSERVE_COMBAT_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::REACT_TO_PLAYER_ACTIONS);

        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_ALREADY_HELD);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_CONVERSATION);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_EATING);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_FAKE_FOOD);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HORSE_RIDING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_IDLE_MARKERS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_SITTING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_SLEEPING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_SPECIAL_FURNITURE);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_WANDERING);

        static_cast<Type_t*>(this)->Unflag(Flag_e::PREFERRED_PATH_ONLY);
        static_cast<Type_t*>(this)->Flag(Flag_e::UNLOCK_ON_ARRIVAL);
    }

    template <>
    void Settler_t::Default<Guard_t>()
    {
        using Type_t = Guard_t;
        using Flag_e = Type_t::Flag_e;

        static_cast<Type_t*>(this)->Radius(0);
        static_cast<Type_t*>(this)->Hour(2);
        static_cast<Type_t*>(this)->Minute(0);
        static_cast<Type_t*>(this)->AM_PM(AM_PM_e::PM);
        static_cast<Type_t*>(this)->Duration_Hours(5);
        static_cast<Type_t*>(this)->Duration_Minutes(45);
        static_cast<Type_t*>(this)->Speed(Settler_Speed_e::RUN);

        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_SWIMMING);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALWAYS_SNEAK);
        static_cast<Type_t*>(this)->Unflag(Flag_e::IGNORE_COMBAT);
        static_cast<Type_t*>(this)->Flag(Flag_e::KEEP_WEAPONS_DRAWN);
        static_cast<Type_t*>(this)->Unflag(Flag_e::HIDE_WEAPONS);
        static_cast<Type_t*>(this)->Flag(Flag_e::SKIP_COMBAT_ALERT);

        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HELLOS_TO_PLAYER);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_HELLOS_TO_NPCS);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_IDLE_CHATTER);
        static_cast<Type_t*>(this)->Flag(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR);
        static_cast<Type_t*>(this)->Unflag(Flag_e::ALLOW_WORLD_INTERACTIONS);
        static_cast<Type_t*>(this)->Flag(Flag_e::COMMENT_ON_FRIENDLY_FIRE);
        static_cast<Type_t*>(this)->Flag(Flag_e::INSPECT_CORPSE_BEHAVIOR);
        static_cast<Type_t*>(this)->Flag(Flag_e::OBSERVE_COMBAT_BEHAVIOR);
        static_cast<Type_t*>(this)->Unflag(Flag_e::REACT_TO_PLAYER_ACTIONS);
    }

    void Sandboxer_t::Default() { Settler_t::Default<Sandboxer_t>(); }
    void Sleeper_t::Default() { Settler_t::Default<Sleeper_t>(); }
    void Sitter_t::Default() { Settler_t::Default<Sitter_t>(); }
    void Eater_t::Default() { Settler_t::Default<Eater_t>(); }
    void Guard_t::Default() { Settler_t::Default<Guard_t>(); }

    /* Clear */

    template <>
    void Settler_t::Clear<Sandboxer_t>()
    {
        using Type_t = Sandboxer_t;

        static_cast<Guard_t*>(this)->Clear();
        static_cast<Eater_t*>(this)->Clear();
        static_cast<Sitter_t*>(this)->Clear();
        static_cast<Sleeper_t*>(this)->Clear();

        static_cast<Type_t*>(this)->Radius_Variable()->Int(0);
        static_cast<Type_t*>(this)->Movement_Variable()->Int(0);
        static_cast<Type_t*>(this)->Wander_Distance_Variable()->Int(0);
        static_cast<Type_t*>(this)->Flags_Variable()->Int(0);
    }

    template <>
    void Settler_t::Clear<Sleeper_t>()
    {
        using Type_t = Sleeper_t;

        Class_Info_t* reference_class_info = Object_Ref::Class_Info();

        static_cast<Type_t*>(this)->Marker_Variable()->None(reference_class_info);
        static_cast<Type_t*>(this)->Radius_Variable()->Int(0);
        static_cast<Type_t*>(this)->Time_Variable()->Int(0);
        static_cast<Type_t*>(this)->Duration_Variable()->Int(0);
        static_cast<Type_t*>(this)->Movement_Variable()->Int(0);
        static_cast<Type_t*>(this)->Wander_Distance_Variable()->Int(0);
        static_cast<Type_t*>(this)->Flags_Variable()->Int(0);
        static_cast<Type_t*>(this)->Bed_Variable()->None(reference_class_info);
    }

    template <>
    void Settler_t::Clear<Sitter_t>()
    {
        using Type_t = Sitter_t;

        static_cast<Type_t*>(this)->Marker_Variable()->None(Object_Ref::Class_Info());
        static_cast<Type_t*>(this)->Radius_Variable()->Int(0);
        static_cast<Type_t*>(this)->Time_Variable()->Int(0);
        static_cast<Type_t*>(this)->Duration_Variable()->Int(0);
        static_cast<Type_t*>(this)->Movement_Variable()->Int(0);
        static_cast<Type_t*>(this)->Flags_Variable()->Int(0);
    }

    template <>
    void Settler_t::Clear<Eater_t>()
    {
        using Type_t = Eater_t;

        static_cast<Type_t*>(this)->Marker_Variable()->None(Object_Ref::Class_Info());
        static_cast<Type_t*>(this)->Radius_Variable()->Int(0);
        static_cast<Type_t*>(this)->Time_Variable()->Int(0);
        static_cast<Type_t*>(this)->Duration_Variable()->Int(0);
        static_cast<Type_t*>(this)->Movement_Variable()->Int(0);
        static_cast<Type_t*>(this)->Wander_Distance_Variable()->Int(0);
        static_cast<Type_t*>(this)->Flags_Variable()->Int(0);
    }

    template <>
    void Settler_t::Clear<Guard_t>()
    {
        using Type_t = Guard_t;

        static_cast<Type_t*>(this)->Marker_Variable()->None(Object_Ref::Class_Info());
        static_cast<Type_t*>(this)->Radius_Variable()->Int(0);
        static_cast<Type_t*>(this)->Time_Variable()->Int(0);
        static_cast<Type_t*>(this)->Duration_Variable()->Int(0);
        static_cast<Type_t*>(this)->Movement_Variable()->Int(0);
        static_cast<Type_t*>(this)->Flags_Variable()->Int(0);
    }

    void Sandboxer_t::Clear() { Settler_t::Clear<Sandboxer_t>(); }
    void Sleeper_t::Clear() { Settler_t::Clear<Sleeper_t>(); }
    void Sitter_t::Clear() { Settler_t::Clear<Sitter_t>(); }
    void Eater_t::Clear() { Settler_t::Clear<Eater_t>(); }
    void Guard_t::Clear() { Settler_t::Clear<Guard_t>(); }

    /* Settler_t */

    Bool_t Settler_t::Is_Sandboxer() { return static_cast<Sandboxer_t*>(this)->Is_Created(); }
    Bool_t Settler_t::Is_Sleeper() { return static_cast<Sleeper_t*>(this)->Is_Created(); }
    Bool_t Settler_t::Is_Sitter() { return static_cast<Sitter_t*>(this)->Is_Created(); }
    Bool_t Settler_t::Is_Eater() { return static_cast<Eater_t*>(this)->Is_Created(); }
    Bool_t Settler_t::Is_Guard() { return static_cast<Guard_t*>(this)->Is_Created(); }

    void Settler_t::Enable_Sandboxer() { static_cast<Sandboxer_t*>(this)->Create(); }
    void Settler_t::Enable_Sleeper() { static_cast<Sleeper_t*>(this)->Create(); }
    void Settler_t::Enable_Sitter() { static_cast<Sitter_t*>(this)->Create(); }
    void Settler_t::Enable_Eater() { static_cast<Eater_t*>(this)->Create(); }
    void Settler_t::Enable_Guard() { static_cast<Guard_t*>(this)->Create(); }

    void Settler_t::Disable_Sandboxer() { static_cast<Sandboxer_t*>(this)->Destroy(true); }
    void Settler_t::Disable_Sleeper() { static_cast<Sleeper_t*>(this)->Destroy(true); }
    void Settler_t::Disable_Sitter() { static_cast<Sitter_t*>(this)->Destroy(true); }
    void Settler_t::Disable_Eater() { static_cast<Eater_t*>(this)->Destroy(true); }
    void Settler_t::Disable_Guard() { static_cast<Guard_t*>(this)->Destroy(true); }

    void Settler_t::Enforce(Actor_t* actor, Bool_t force_reset_ai)
    {
        Bool_t do_reset_ai = force_reset_ai;

        auto Enforce_General_Flag = [&](Package_t* package, Package_t::General_Flag_e flag, Bool_t value)->void
        {
            if (package->Flag(flag, value)) {
                do_reset_ai = true;
            }
        };

        auto Enforce_Interrupt_Flag = [&](Package_t* package, Package_t::Interrupt_Flag_e flag, Bool_t value)->void
        {
            if (package->Flag(flag, value)) {
                do_reset_ai = true;
            }
        };

        auto Enforce_Bool = [&](Package_t* package, Bool_t is_enabled, UInt16 value_index)->void
        {
            enum {
                IS_FALSE = 0,
                IS_TRUE = 2,
            };

            Package_Bool_Value_t* value = static_cast<Package_Bool_Value_t*>
                (package->data->values[value_index]);
            if (is_enabled) {
                if (value->value == IS_FALSE) {
                    do_reset_ai = true;
                    value->value = IS_TRUE;
                }
            } else {
                if (value->value == IS_TRUE) {
                    do_reset_ai = true;
                    value->value = IS_FALSE;
                }
            }
        };

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

        auto Enforce_Time = [&](Package_t* package, Int_t hour, Int_t minute, AM_PM_e am_pm, Int_t duration_hours, Int_t duration_minutes)->void
        {
            Package_Schedule_t& schedule = package->schedule;

            if (hour == 12) {
                hour = 0;
            }
            if (am_pm == AM_PM_e::PM) {
                hour += 12;
            }
            if (schedule.hour != hour) {
                do_reset_ai = true;
                schedule.hour = hour;
            }

            if (schedule.minute != minute) {
                do_reset_ai = true;
                schedule.minute = minute;
            }

            Int_t duration = (duration_hours * 60) + duration_minutes;
            if (duration < Settler_t::MIN_DURATION) {
                duration = Settler_t::MIN_DURATION;
            } else if (duration > Settler_t::MAX_DURATION) {
                duration = Settler_t::MAX_DURATION;
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
            Enforce_General_Flag(package, Package_t::General_Flag_e::ALLOW_PREFERRED_SPEED, true);
            if (package->preferred_speed != speed) {
                do_reset_ai = true;
                package->preferred_speed = speed;
            }
        };

        auto Enforce_Wander_Distance = [&](Package_t* package, Float_t wander_distance, UInt16 value_index)->void
        {
            Package_Float_Value_t* value = static_cast<Package_Float_Value_t*>
                (package->data->values[value_index]);
            if (value->value != wander_distance) {
                do_reset_ai = true;
                value->value = wander_distance;
            }
        };

        auto Enforce_Sandboxer = [&]()->void
        {
            using General_e = Package_t::General_Flag_e;
            using Interrupt_e = Package_t::Interrupt_Flag_e;
            using Flag_e = Sandboxer_t::Flag_e;
            using Value_e = Sandboxer_Value_e;

            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Value_e::LOCATION),
                ATTENTION = static_cast<UInt16>(Value_e::ATTENTION),
                MIN_WANDER_DISTANCE = static_cast<UInt16>(Value_e::MIN_WANDER_DISTANCE),

                ALLOW_CONVERSATION = static_cast<UInt16>(Value_e::ALLOW_CONVERSATION),
                ALLOW_EATING = static_cast<UInt16>(Value_e::ALLOW_EATING),
                ALLOW_HORSE_RIDING = static_cast<UInt16>(Value_e::ALLOW_HORSE_RIDING),
                ALLOW_IDLE_MARKERS = static_cast<UInt16>(Value_e::ALLOW_IDLE_MARKERS),
                ALLOW_SITTING = static_cast<UInt16>(Value_e::ALLOW_SITTING),
                ALLOW_SLEEPING = static_cast<UInt16>(Value_e::ALLOW_SLEEPING),
                ALLOW_SPECIAL_FURNITURE = static_cast<UInt16>(Value_e::ALLOW_SPECIAL_FURNITURE),
                ALLOW_WANDERING = static_cast<UInt16>(Value_e::ALLOW_WANDERING),
                
                DO_PREFERRED_PATH_ONLY = static_cast<UInt16>(Value_e::DO_PREFERRED_PATH_ONLY),
                DO_UNLOCK_ON_ARRIVAL = static_cast<UInt16>(Value_e::DO_UNLOCK_ON_ARRIVAL),
            };

            Sandboxer_t* self = static_cast<Sandboxer_t*>(this);

            if (self->Is_Created()) {
                Package_t* package = self->Package();
                Enforce_Location(package, self->Marker(), self->Radius(), LOCATION);
                Enforce_Attention(package, self->Attention(), ATTENTION);
                Enforce_Speed(package, self->Speed());
                Enforce_Wander_Distance(package, self->Wander_Distance(), MIN_WANDER_DISTANCE);

                Enforce_General_Flag(package, General_e::ALLOW_SWIMMING, self->Is_Flagged(Flag_e::ALLOW_SWIMMING));
                Enforce_General_Flag(package, General_e::ALWAYS_SNEAK, self->Is_Flagged(Flag_e::ALWAYS_SNEAK));
                Enforce_General_Flag(package, General_e::IGNORE_COMBAT, self->Is_Flagged(Flag_e::IGNORE_COMBAT));
                Enforce_General_Flag(package, General_e::KEEP_WEAPONS_DRAWN, self->Is_Flagged(Flag_e::KEEP_WEAPONS_DRAWN));
                Enforce_General_Flag(package, General_e::HIDE_WEAPONS, self->Is_Flagged(Flag_e::HIDE_WEAPONS));
                Enforce_General_Flag(package, General_e::SKIP_COMBAT_ALERT, self->Is_Flagged(Flag_e::SKIP_COMBAT_ALERT));
                
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_PLAYER, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_PLAYER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_NPCS, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_NPCS));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_IDLE_CHATTER, self->Is_Flagged(Flag_e::ALLOW_IDLE_CHATTER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_AGGRO_RADIUS_BEHAVIOR, self->Is_Flagged(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_WORLD_INTERACTIONS, self->Is_Flagged(Flag_e::ALLOW_WORLD_INTERACTIONS));
                Enforce_Interrupt_Flag(package, Interrupt_e::COMMENT_ON_FRIENDLY_FIRE, self->Is_Flagged(Flag_e::COMMENT_ON_FRIENDLY_FIRE));
                Enforce_Interrupt_Flag(package, Interrupt_e::INSPECT_CORPSE_BEHAVIOR, self->Is_Flagged(Flag_e::INSPECT_CORPSE_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::OBSERVE_COMBAT_BEHAVIOR, self->Is_Flagged(Flag_e::OBSERVE_COMBAT_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::REACT_TO_PLAYER_ACTIONS, self->Is_Flagged(Flag_e::REACT_TO_PLAYER_ACTIONS));

                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_CONVERSATION), ALLOW_CONVERSATION);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_EATING), ALLOW_EATING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_HORSE_RIDING), ALLOW_HORSE_RIDING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_IDLE_MARKERS), ALLOW_IDLE_MARKERS);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SITTING), ALLOW_SITTING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SLEEPING), ALLOW_SLEEPING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SPECIAL_FURNITURE), ALLOW_SPECIAL_FURNITURE);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_WANDERING), ALLOW_WANDERING);

                Enforce_Bool(package, self->Is_Flagged(Flag_e::PREFERRED_PATH_ONLY), DO_PREFERRED_PATH_ONLY);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::UNLOCK_ON_ARRIVAL), DO_UNLOCK_ON_ARRIVAL);

                Object_Ref::Token(actor, self->Token());
            } else {
                Object_Ref::Untoken(actor, self->Token());
            }
        };

        auto Enforce_Sleeper = [&]()->void
        {
            using General_e = Package_t::General_Flag_e;
            using Interrupt_e = Package_t::Interrupt_Flag_e;
            using Flag_e = Sleeper_t::Flag_e;
            using Value_e = Sleeper_Value_e;

            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Value_e::LOCATION),
                ATTENTION = static_cast<UInt16>(Value_e::ATTENTION),
                MIN_WANDER_DISTANCE = static_cast<UInt16>(Value_e::MIN_WANDER_DISTANCE),

                ALLOW_CONVERSATION = static_cast<UInt16>(Value_e::ALLOW_CONVERSATION),
                ALLOW_EATING = static_cast<UInt16>(Value_e::ALLOW_EATING),
                ALLOW_HORSE_RIDING = static_cast<UInt16>(Value_e::ALLOW_HORSE_RIDING),
                ALLOW_IDLE_MARKERS = static_cast<UInt16>(Value_e::ALLOW_IDLE_MARKERS),
                ALLOW_SITTING = static_cast<UInt16>(Value_e::ALLOW_SITTING),
                ALLOW_SLEEPING = static_cast<UInt16>(Value_e::ALLOW_SLEEPING),
                ALLOW_SPECIAL_FURNITURE = static_cast<UInt16>(Value_e::ALLOW_SPECIAL_FURNITURE),
                ALLOW_WANDERING = static_cast<UInt16>(Value_e::ALLOW_WANDERING),

                DO_LOCK_DOORS = static_cast<UInt16>(Value_e::DO_LOCK_DOORS),
                DO_PREFERRED_PATH_ONLY = static_cast<UInt16>(Value_e::DO_PREFERRED_PATH_ONLY),
                DO_WARN_BEFORE_LOCKING = static_cast<UInt16>(Value_e::DO_WARN_BEFORE_LOCKING),
            };

            Sleeper_t* self = static_cast<Sleeper_t*>(this);

            if (self->Is_Created()) {
                Package_t* package = self->Package();
                Enforce_Location(package, self->Marker(), self->Radius(), LOCATION);
                Enforce_Time(package, self->Hour(), self->Minute(), self->AM_PM(), self->Duration_Hours(), self->Duration_Minutes());
                Enforce_Attention(package, self->Attention(), ATTENTION);
                Enforce_Speed(package, self->Speed());
                Enforce_Wander_Distance(package, self->Wander_Distance(), MIN_WANDER_DISTANCE);

                Enforce_General_Flag(package, General_e::ALLOW_SWIMMING, self->Is_Flagged(Flag_e::ALLOW_SWIMMING));
                Enforce_General_Flag(package, General_e::ALWAYS_SNEAK, self->Is_Flagged(Flag_e::ALWAYS_SNEAK));
                Enforce_General_Flag(package, General_e::IGNORE_COMBAT, self->Is_Flagged(Flag_e::IGNORE_COMBAT));
                Enforce_General_Flag(package, General_e::KEEP_WEAPONS_DRAWN, self->Is_Flagged(Flag_e::KEEP_WEAPONS_DRAWN));
                Enforce_General_Flag(package, General_e::HIDE_WEAPONS, self->Is_Flagged(Flag_e::HIDE_WEAPONS));
                Enforce_General_Flag(package, General_e::SKIP_COMBAT_ALERT, self->Is_Flagged(Flag_e::SKIP_COMBAT_ALERT));

                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_PLAYER, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_PLAYER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_NPCS, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_NPCS));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_IDLE_CHATTER, self->Is_Flagged(Flag_e::ALLOW_IDLE_CHATTER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_AGGRO_RADIUS_BEHAVIOR, self->Is_Flagged(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_WORLD_INTERACTIONS, self->Is_Flagged(Flag_e::ALLOW_WORLD_INTERACTIONS));
                Enforce_Interrupt_Flag(package, Interrupt_e::COMMENT_ON_FRIENDLY_FIRE, self->Is_Flagged(Flag_e::COMMENT_ON_FRIENDLY_FIRE));
                Enforce_Interrupt_Flag(package, Interrupt_e::INSPECT_CORPSE_BEHAVIOR, self->Is_Flagged(Flag_e::INSPECT_CORPSE_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::OBSERVE_COMBAT_BEHAVIOR, self->Is_Flagged(Flag_e::OBSERVE_COMBAT_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::REACT_TO_PLAYER_ACTIONS, self->Is_Flagged(Flag_e::REACT_TO_PLAYER_ACTIONS));

                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_CONVERSATION), ALLOW_CONVERSATION);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_EATING), ALLOW_EATING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_HORSE_RIDING), ALLOW_HORSE_RIDING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_IDLE_MARKERS), ALLOW_IDLE_MARKERS);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SITTING), ALLOW_SITTING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SLEEPING), ALLOW_SLEEPING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SPECIAL_FURNITURE), ALLOW_SPECIAL_FURNITURE);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_WANDERING), ALLOW_WANDERING);

                Enforce_Bool(package, self->Is_Flagged(Flag_e::LOCK_DOORS), DO_LOCK_DOORS);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::PREFERRED_PATH_ONLY), DO_PREFERRED_PATH_ONLY);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::WARN_BEFORE_LOCKING), DO_WARN_BEFORE_LOCKING);

                Reference_t* bed = self->Bed_Variable()->Reference();
                if (bed) {
                    Object_Ref::Owner(bed, Base_Actor());
                }

                Object_Ref::Token(actor, self->Token());
            } else {
                Object_Ref::Untoken(actor, self->Token());
            }
        };

        auto Enforce_Sitter = [&]()
        {
            using General_e = Package_t::General_Flag_e;
            using Interrupt_e = Package_t::Interrupt_Flag_e;
            using Flag_e = Sitter_t::Flag_e;
            using Value_e = Sitter_Value_e;

            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Value_e::LOCATION),

                DO_PREFERRED_PATH_ONLY = static_cast<UInt16>(Value_e::DO_PREFERRED_PATH_ONLY),
                DO_STOP_MOVEMENT = static_cast<UInt16>(Value_e::DO_STOP_MOVEMENT),
            };

            Sitter_t* self = static_cast<Sitter_t*>(this);

            if (self->Is_Created()) {
                Package_t* package = self->Package();
                Enforce_Location(package, self->Marker(), self->Radius(), LOCATION);
                Enforce_Time(package, self->Hour(), self->Minute(), self->AM_PM(), self->Duration_Hours(), self->Duration_Minutes());
                Enforce_Speed(package, self->Speed());

                Enforce_General_Flag(package, General_e::ALLOW_SWIMMING, self->Is_Flagged(Flag_e::ALLOW_SWIMMING));
                Enforce_General_Flag(package, General_e::ALWAYS_SNEAK, self->Is_Flagged(Flag_e::ALWAYS_SNEAK));
                Enforce_General_Flag(package, General_e::IGNORE_COMBAT, self->Is_Flagged(Flag_e::IGNORE_COMBAT));
                Enforce_General_Flag(package, General_e::KEEP_WEAPONS_DRAWN, self->Is_Flagged(Flag_e::KEEP_WEAPONS_DRAWN));
                Enforce_General_Flag(package, General_e::HIDE_WEAPONS, self->Is_Flagged(Flag_e::HIDE_WEAPONS));
                Enforce_General_Flag(package, General_e::SKIP_COMBAT_ALERT, self->Is_Flagged(Flag_e::SKIP_COMBAT_ALERT));

                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_PLAYER, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_PLAYER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_NPCS, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_NPCS));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_IDLE_CHATTER, self->Is_Flagged(Flag_e::ALLOW_IDLE_CHATTER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_AGGRO_RADIUS_BEHAVIOR, self->Is_Flagged(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_WORLD_INTERACTIONS, self->Is_Flagged(Flag_e::ALLOW_WORLD_INTERACTIONS));
                Enforce_Interrupt_Flag(package, Interrupt_e::COMMENT_ON_FRIENDLY_FIRE, self->Is_Flagged(Flag_e::COMMENT_ON_FRIENDLY_FIRE));
                Enforce_Interrupt_Flag(package, Interrupt_e::INSPECT_CORPSE_BEHAVIOR, self->Is_Flagged(Flag_e::INSPECT_CORPSE_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::OBSERVE_COMBAT_BEHAVIOR, self->Is_Flagged(Flag_e::OBSERVE_COMBAT_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::REACT_TO_PLAYER_ACTIONS, self->Is_Flagged(Flag_e::REACT_TO_PLAYER_ACTIONS));

                Enforce_Bool(package, self->Is_Flagged(Flag_e::PREFERRED_PATH_ONLY), DO_PREFERRED_PATH_ONLY);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::STOP_MOVEMENT), DO_STOP_MOVEMENT);

                Object_Ref::Token(actor, self->Token());
            } else {
                Object_Ref::Untoken(actor, self->Token());
            }
        };

        auto Enforce_Eater = [&]()->void
        {
            using General_e = Package_t::General_Flag_e;
            using Interrupt_e = Package_t::Interrupt_Flag_e;
            using Flag_e = Eater_t::Flag_e;
            using Value_e = Eater_Value_e;

            enum : UInt16 {
                LOCATION = static_cast<UInt16>(Value_e::LOCATION),
                ATTENTION = static_cast<UInt16>(Value_e::ATTENTION),
                MIN_WANDER_DISTANCE = static_cast<UInt16>(Value_e::MIN_WANDER_DISTANCE),

                ALLOW_ALREADY_HELD = static_cast<UInt16>(Value_e::ALLOW_ALREADY_HELD),
                ALLOW_CONVERSATION = static_cast<UInt16>(Value_e::ALLOW_CONVERSATION),
                ALLOW_EATING = static_cast<UInt16>(Value_e::ALLOW_EATING),
                ALLOW_FAKE_FOOD = static_cast<UInt16>(Value_e::ALLOW_FAKE_FOOD),
                ALLOW_HORSE_RIDING = static_cast<UInt16>(Value_e::ALLOW_HORSE_RIDING),
                ALLOW_IDLE_MARKERS = static_cast<UInt16>(Value_e::ALLOW_IDLE_MARKERS),
                ALLOW_SITTING = static_cast<UInt16>(Value_e::ALLOW_SITTING),
                ALLOW_SLEEPING = static_cast<UInt16>(Value_e::ALLOW_SLEEPING),
                ALLOW_SPECIAL_FURNITURE = static_cast<UInt16>(Value_e::ALLOW_SPECIAL_FURNITURE),
                ALLOW_WANDERING = static_cast<UInt16>(Value_e::ALLOW_WANDERING),

                DO_PREFERRED_PATH_ONLY = static_cast<UInt16>(Value_e::DO_PREFERRED_PATH_ONLY),
                DO_UNLOCK_ON_ARRIVAL = static_cast<UInt16>(Value_e::DO_UNLOCK_ON_ARRIVAL),
            };

            Eater_t* self = static_cast<Eater_t*>(this);

            if (self->Is_Created()) {
                Package_t* package = self->Package();
                Enforce_Location(package, self->Marker(), self->Radius(), LOCATION);
                Enforce_Time(package, self->Hour(), self->Minute(), self->AM_PM(), self->Duration_Hours(), self->Duration_Minutes());
                Enforce_Attention(package, self->Attention(), ATTENTION);
                Enforce_Speed(package, self->Speed());
                Enforce_Wander_Distance(package, self->Wander_Distance(), MIN_WANDER_DISTANCE);

                Enforce_General_Flag(package, General_e::ALLOW_SWIMMING, self->Is_Flagged(Flag_e::ALLOW_SWIMMING));
                Enforce_General_Flag(package, General_e::ALWAYS_SNEAK, self->Is_Flagged(Flag_e::ALWAYS_SNEAK));
                Enforce_General_Flag(package, General_e::IGNORE_COMBAT, self->Is_Flagged(Flag_e::IGNORE_COMBAT));
                Enforce_General_Flag(package, General_e::KEEP_WEAPONS_DRAWN, self->Is_Flagged(Flag_e::KEEP_WEAPONS_DRAWN));
                Enforce_General_Flag(package, General_e::HIDE_WEAPONS, self->Is_Flagged(Flag_e::HIDE_WEAPONS));
                Enforce_General_Flag(package, General_e::SKIP_COMBAT_ALERT, self->Is_Flagged(Flag_e::SKIP_COMBAT_ALERT));

                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_PLAYER, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_PLAYER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_NPCS, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_NPCS));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_IDLE_CHATTER, self->Is_Flagged(Flag_e::ALLOW_IDLE_CHATTER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_AGGRO_RADIUS_BEHAVIOR, self->Is_Flagged(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_WORLD_INTERACTIONS, self->Is_Flagged(Flag_e::ALLOW_WORLD_INTERACTIONS));
                Enforce_Interrupt_Flag(package, Interrupt_e::COMMENT_ON_FRIENDLY_FIRE, self->Is_Flagged(Flag_e::COMMENT_ON_FRIENDLY_FIRE));
                Enforce_Interrupt_Flag(package, Interrupt_e::INSPECT_CORPSE_BEHAVIOR, self->Is_Flagged(Flag_e::INSPECT_CORPSE_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::OBSERVE_COMBAT_BEHAVIOR, self->Is_Flagged(Flag_e::OBSERVE_COMBAT_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::REACT_TO_PLAYER_ACTIONS, self->Is_Flagged(Flag_e::REACT_TO_PLAYER_ACTIONS));

                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_ALREADY_HELD), ALLOW_ALREADY_HELD);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_CONVERSATION), ALLOW_CONVERSATION);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_EATING), ALLOW_EATING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_FAKE_FOOD), ALLOW_FAKE_FOOD);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_HORSE_RIDING), ALLOW_HORSE_RIDING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_IDLE_MARKERS), ALLOW_IDLE_MARKERS);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SITTING), ALLOW_SITTING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SLEEPING), ALLOW_SLEEPING);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_SPECIAL_FURNITURE), ALLOW_SPECIAL_FURNITURE);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::ALLOW_WANDERING), ALLOW_WANDERING);

                Enforce_Bool(package, self->Is_Flagged(Flag_e::PREFERRED_PATH_ONLY), DO_PREFERRED_PATH_ONLY);
                Enforce_Bool(package, self->Is_Flagged(Flag_e::UNLOCK_ON_ARRIVAL), DO_UNLOCK_ON_ARRIVAL);

                Object_Ref::Token(actor, self->Token());
            } else {
                Object_Ref::Untoken(actor, self->Token());
            }
        };

        auto Enforce_Guard = [&]()->void
        {
            using General_e = Package_t::General_Flag_e;
            using Interrupt_e = Package_t::Interrupt_Flag_e;
            using Flag_e = Guard_t::Flag_e;
            using Value_e = Guard_Value_e;

            enum : UInt16 {
                WAIT_LOCATION = static_cast<UInt16>(Value_e::WAIT_LOCATION),
                RESTRICTED_LOCATION = static_cast<UInt16>(Value_e::RESTRICTED_LOCATION),
            };

            Guard_t* self = static_cast<Guard_t*>(this);

            if (self->Is_Created()) {
                Package_t* package = self->Package();
                Enforce_Location(package, self->Marker(), 0, WAIT_LOCATION);
                Enforce_Location(package, self->Marker(), self->Radius(), RESTRICTED_LOCATION);
                Enforce_Time(package, self->Hour(), self->Minute(), self->AM_PM(), self->Duration_Hours(), self->Duration_Minutes());
                Enforce_Speed(package, self->Speed());

                Enforce_General_Flag(package, General_e::ALLOW_SWIMMING, self->Is_Flagged(Flag_e::ALLOW_SWIMMING));
                Enforce_General_Flag(package, General_e::ALWAYS_SNEAK, self->Is_Flagged(Flag_e::ALWAYS_SNEAK));
                Enforce_General_Flag(package, General_e::IGNORE_COMBAT, self->Is_Flagged(Flag_e::IGNORE_COMBAT));
                Enforce_General_Flag(package, General_e::KEEP_WEAPONS_DRAWN, self->Is_Flagged(Flag_e::KEEP_WEAPONS_DRAWN));
                Enforce_General_Flag(package, General_e::HIDE_WEAPONS, self->Is_Flagged(Flag_e::HIDE_WEAPONS));
                Enforce_General_Flag(package, General_e::SKIP_COMBAT_ALERT, self->Is_Flagged(Flag_e::SKIP_COMBAT_ALERT));

                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_PLAYER, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_PLAYER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_HELLOS_TO_NPCS, self->Is_Flagged(Flag_e::ALLOW_HELLOS_TO_NPCS));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_IDLE_CHATTER, self->Is_Flagged(Flag_e::ALLOW_IDLE_CHATTER));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_AGGRO_RADIUS_BEHAVIOR, self->Is_Flagged(Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::ALLOW_WORLD_INTERACTIONS, self->Is_Flagged(Flag_e::ALLOW_WORLD_INTERACTIONS));
                Enforce_Interrupt_Flag(package, Interrupt_e::COMMENT_ON_FRIENDLY_FIRE, self->Is_Flagged(Flag_e::COMMENT_ON_FRIENDLY_FIRE));
                Enforce_Interrupt_Flag(package, Interrupt_e::INSPECT_CORPSE_BEHAVIOR, self->Is_Flagged(Flag_e::INSPECT_CORPSE_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::OBSERVE_COMBAT_BEHAVIOR, self->Is_Flagged(Flag_e::OBSERVE_COMBAT_BEHAVIOR));
                Enforce_Interrupt_Flag(package, Interrupt_e::REACT_TO_PLAYER_ACTIONS, self->Is_Flagged(Flag_e::REACT_TO_PLAYER_ACTIONS));

                Object_Ref::Token(actor, self->Token());
            } else {
                Object_Ref::Untoken(actor, self->Token());
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

    /* Sleeper_t */

    Bool_t Sleeper_t::Has_Bed()
    {
        return Is_Sleeper() && Bed_Variable()->Has_Object();
    }

    void Sleeper_t::Create_Bed()
    {
        if (Is_Sleeper()) {
            Reference_t* marker = Marker();
            Reference_t* bed = Bed_Variable()->Reference();
            if (!bed) {
                bed = Object_Ref::Place_At_Me(marker, Consts::Bedroll_Furniture(), 1, true, false);
                Bed_Variable()->Pack(bed);
            }
            Object_Ref::Move_To_Orbit(bed, marker, 0.0f, 180.0f);
            Object_Ref::Owner(bed, Base_Actor());
        }
    }

    void Sleeper_t::Destroy_Bed()
    {
        if (Has_Bed()) {
            Actor_t* actor = Actor();
            Reference_t* bed = Bed_Variable()->Reference();
            Bed_Variable()->None(Object_Ref::Class_Info());
            if (Object_Ref::Get_Distance(actor, bed) < 16.0f) {
                Actor2::Move_To_Orbit(actor, bed, 0.0f, 180.0f);
            }
            Object_Ref::Delete_Safe(bed);
        }
    }

    void Sleeper_t::Add_Bed()
    {
        if (Is_Sleeper()) {
            Actor_t* actor = Actor();
            Create_Bed();
            Enforce(actor, true);
        }
    }

    void Sleeper_t::Remove_Bed()
    {
        if (Is_Sleeper()) {
            Actor_t* actor = Actor();
            Destroy_Bed();
            Enforce(actor, true);
        }
    }

}}}
