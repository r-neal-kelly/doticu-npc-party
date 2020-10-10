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
        RIDE_HORSE_IF_POSSIBLE,     // Bool
        ENERGY,                     // Float
    };

    enum class Sleeper_Value_e : UInt16 {
        LOCATION = 0,               // Location
        SEARCH_CRITERIA,            // Target_Selector
        DO_LOCK_DOORS,              // Bool
        WARN_BEFORE_LOCKING,        // Bool
        RIDE_HORSE_IF_POSSIBLE,     // Bool
        UNKNOWN_OBJECT_LIST_1,      // Object_List
        ALLOW_EATING,               // Bool
        ALLOW_SLEEPING,             // Bool
        ALLOW_CONVERSATION,         // Bool
        ALLOW_IDLE_MARKERS,         // Bool
        ALLOW_SITTING,              // Bool
        ALLOW_SPECIAL_FURNITURE,    // Bool
        ALLOW_WANDERING,            // Bool
        UNKNOWN_BOOL_1,             // Bool
        MIN_WANDER_DISTANCE,        // Float
        UNKNOWN_BOOL_2,             // Bool
        ENERGY,                     // Float
    };

    enum class Eater_Value_e : UInt16 {
        LOCATION = 0,               // Location
        DO_UNLOCK_ON_ARRIVAL,       // Bool
        UNKNOWN_TARGET_SELECTOR_1,  // Target_Selector
        UNKNOWN_OBJECT_LIST_1,      // Object_List
        UNKNOWN_TARGET_SELECTOR_2,  // Target_Selector
        UNKNOWN_OBJECT_LIST_2,      // Object_List
        NUM_FOOD_ITEMS,             // Int
        ALLOW_ALREADY_HELD,         // Bool
        RIDE_HORSE_IF_POSSIBLE,     // Bool
        DO_CREATE_FAKE_FOOD,        // Bool
        ALLOW_EATING,               // Bool
        ALLOW_SLEEPING,             // Bool
        ALLOW_CONVERSATION,         // Bool
        ALLOW_IDLE_MARKERS,         // Bool
        ALLOW_SPECIAL_FURNITURE,    // Bool
        ALLOW_SITTING,              // Bool
        ALLOW_WANDERING,            // Bool
        UNKNOWN_BOOL_1,             // Bool
        MIN_WANDER_DISTANCE,        // Float
        UNKNOWN_BOOL_2,             // Bool
        ENERGY,                     // Float
    };

    enum class Guard_Value_e : UInt16 {
        PATROL_START = 0,           // Single_Reference
        PATROL_RADIUS,              // Float
        IS_REPEATABLE,              // Bool
        DO_START_AT_NEAREST,        // Bool
        LOCATION,                   // Location
    };

    Variable_t* Settler_t::Sandboxer_Flags_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_flags"); }
    Variable_t* Settler_t::Sleeper_Flags_Variable() { DEFINE_VARIABLE("p_settler_sleeper_flags"); }
    Variable_t* Settler_t::Eater_Flags_Variable() { DEFINE_VARIABLE("p_settler_eater_flags"); }
    Variable_t* Settler_t::Guard_Flags_Variable() { DEFINE_VARIABLE("p_settler_guard_flags"); }

    Variable_t* Settler_t::Sandboxer_Radius_Variable() { DEFINE_VARIABLE("p_settler_sandboxer_radius"); }
    Variable_t* Settler_t::Sleeper_Radius_Variable() { DEFINE_VARIABLE("p_settler_sleeper_radius"); }
    Variable_t* Settler_t::Eater_Radius_Variable() { DEFINE_VARIABLE("p_settler_eater_radius"); }
    Variable_t* Settler_t::Guard_Radius_Variable() { DEFINE_VARIABLE("p_settler_guard_radius"); }

    Variable_t* Settler_t::Sleeper_Time_Variable() { DEFINE_VARIABLE("p_settler_sleeper_time"); }
    Variable_t* Settler_t::Eater_Time_Variable() { DEFINE_VARIABLE("p_settler_eater_time"); }
    Variable_t* Settler_t::Guard_Time_Variable() { DEFINE_VARIABLE("p_settler_guard_time"); }

    Variable_t* Settler_t::Sleeper_Duration_Variable() { DEFINE_VARIABLE("p_settler_sleeper_duration"); }
    Variable_t* Settler_t::Eater_Duration_Variable() { DEFINE_VARIABLE("p_settler_eater_duration"); }
    Variable_t* Settler_t::Guard_Duration_Variable() { DEFINE_VARIABLE("p_settler_guard_duration"); }

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

    Reference_t* Settler_t::Sandboxer_Marker()
    {
        return static_cast<Reference_t*>
            (Consts::Settler_Markers_Formlist()->forms.entries[ID()]);
    }

    Reference_t* Settler_t::Sleeper_Marker()
    {
        return static_cast<Reference_t*>
            (Consts::Settler_Sleeper_Markers_Formlist()->forms.entries[ID()]);
    }

    Reference_t* Settler_t::Eater_Marker()
    {
        return static_cast<Reference_t*>
            (Consts::Settler_Eater_Markers_Formlist()->forms.entries[ID()]);
    }

    Reference_t* Settler_t::Guard_Marker()
    {
        return static_cast<Reference_t*>
            (Consts::Settler_Guard_Markers_Formlist()->forms.entries[ID()]);
    }

    template <Variable_t*(Settler_t::*Radius_Variable)()>
    Int_t Settler_t::Radius()
    {
        return (this->*Radius_Variable)()->Int();
    }

    Int_t Settler_t::Sandboxer_Radius()
    {
        return Radius<&Settler_t::Sandboxer_Radius_Variable>();
    }

    Int_t Settler_t::Sleeper_Radius()
    {
        return Radius<&Settler_t::Sleeper_Radius_Variable>();
    }

    Int_t Settler_t::Eater_Radius()
    {
        return Radius<&Settler_t::Eater_Radius_Variable>();
    }

    Int_t Settler_t::Guard_Radius()
    {
        return Radius<&Settler_t::Guard_Radius_Variable>();
    }

    template <Variable_t*(Settler_t::*Radius_Variable)()>
    void Settler_t::Radius(Int_t radius)
    {
        if (radius < MIN_RADIUS) {
            radius = MIN_RADIUS;
        } else if (radius > MAX_RADIUS) {
            radius = MAX_RADIUS;
        }

        (this->*Radius_Variable)()->Int(radius);
    }

    void Settler_t::Sandboxer_Radius(Int_t radius)
    {
        Radius<&Settler_t::Sandboxer_Radius_Variable>(radius);
    }

    void Settler_t::Sleeper_Radius(Int_t radius)
    {
        Radius<&Settler_t::Sleeper_Radius_Variable>(radius);
    }

    void Settler_t::Eater_Radius(Int_t radius)
    {
        Radius<&Settler_t::Eater_Radius_Variable>(radius);
    }

    void Settler_t::Guard_Radius(Int_t radius)
    {
        Radius<&Settler_t::Guard_Radius_Variable>(radius);
    }

    template <Variable_t*(Settler_t::*Time_Variable)()>
    Int_t Settler_t::Hour()
    {
        return (((this->*Time_Variable)()->Int() & HOUR_MASK) >> 16) - 1;
    }

    Int_t Settler_t::Sleeper_Hour()
    {
        return Hour<&Settler_t::Sleeper_Time_Variable>();
    }

    Int_t Settler_t::Eater_Hour()
    {
        return Hour<&Settler_t::Eater_Time_Variable>();
    }

    Int_t Settler_t::Guard_Hour()
    {
        return Hour<&Settler_t::Guard_Time_Variable>();
    }

    template <Variable_t*(Settler_t::*Time_Variable)()>
    void Settler_t::Hour(Int_t hour)
    {
        if (hour < MIN_TIME_HOUR) {
            hour = MIN_TIME_HOUR;
        } else if (hour > MAX_TIME_HOUR) {
            hour = MAX_TIME_HOUR;
        }
        hour += 1;

        (this->*Time_Variable)()->Int(
            (hour << 16) |
            ((this->*Time_Variable)()->Int() & MINUTE_MASK)
        );
    }

    void Settler_t::Sleeper_Hour(Int_t hour)
    {
        Hour<&Settler_t::Sleeper_Time_Variable>(hour);
    }

    void Settler_t::Eater_Hour(Int_t hour)
    {
        Hour<&Settler_t::Eater_Time_Variable>(hour);
    }

    void Settler_t::Guard_Hour(Int_t hour)
    {
        Hour<&Settler_t::Guard_Time_Variable>(hour);
    }

    template <Variable_t*(Settler_t::*Time_Variable)()>
    Int_t Settler_t::Minute()
    {
        return ((this->*Time_Variable)()->Int() & MINUTE_MASK) - 1;
    }

    Int_t Settler_t::Sleeper_Minute()
    {
        return Minute<&Settler_t::Sleeper_Time_Variable>();
    }

    Int_t Settler_t::Eater_Minute()
    {
        return Minute<&Settler_t::Eater_Time_Variable>();
    }

    Int_t Settler_t::Guard_Minute()
    {
        return Minute<&Settler_t::Guard_Time_Variable>();
    }

    template <Variable_t*(Settler_t::*Time_Variable)()>
    void Settler_t::Minute(Int_t minute)
    {
        if (minute < MIN_TIME_MINUTE) {
            minute = MIN_TIME_MINUTE;
        } else if (minute > MAX_TIME_MINUTE) {
            minute = MAX_TIME_MINUTE;
        }
        minute += 1;

        (this->*Time_Variable)()->Int(
            ((this->*Time_Variable)()->Int() & HOUR_MASK) |
            (minute & MINUTE_MASK)
        );
    }

    void Settler_t::Sleeper_Minute(Int_t minute)
    {
        Minute<&Settler_t::Sleeper_Time_Variable>(minute);
    }

    void Settler_t::Eater_Minute(Int_t minute)
    {
        Minute<&Settler_t::Eater_Time_Variable>(minute);
    }

    void Settler_t::Guard_Minute(Int_t minute)
    {
        Minute<&Settler_t::Guard_Time_Variable>(minute);
    }

    template <Variable_t*(Settler_t::*Duration_Variable)()>
    Int_t Settler_t::Duration()
    {
        return (this->*Duration_Variable)()->Int();
    }

    Int_t Settler_t::Sleeper_Duration()
    {
        return Duration<&Settler_t::Sleeper_Duration_Variable>();
    }

    Int_t Settler_t::Eater_Duration()
    {
        return Duration<&Settler_t::Eater_Duration_Variable>();
    }

    Int_t Settler_t::Guard_Duration()
    {
        return Duration<&Settler_t::Guard_Duration_Variable>();
    }

    template <Variable_t*(Settler_t::*Duration_Variable)()>
    void Settler_t::Duration(Int_t minutes)
    {
        if (minutes < MIN_DURATION_MINUTES) {
            minutes = MIN_DURATION_MINUTES;
        } else if (minutes > MAX_DURATION_MINUTES) {
            minutes = MAX_DURATION_MINUTES;
        }

        (this->*Duration_Variable)()->Int(minutes);
    }

    void Settler_t::Sleeper_Duration(Int_t minutes)
    {
        Duration<&Settler_t::Sleeper_Duration_Variable>(minutes);
    }

    void Settler_t::Eater_Duration(Int_t minutes)
    {
        Duration<&Settler_t::Eater_Duration_Variable>(minutes);
    }

    void Settler_t::Guard_Duration(Int_t minutes)
    {
        Duration<&Settler_t::Guard_Duration_Variable>(minutes);
    }

    template <typename Flag_e>
    Bool_t Settler_t::Is_Flagged(Flag_e flag)
    {
        return false;
    }

    template <>
    Bool_t Settler_t::Is_Flagged(Sandboxer_Flag_e flag)
    {
        return (Sandboxer_Flags_Variable()->Int() & (1 << static_cast<Int_t>(flag))) > 0;
    }

    template <>
    Bool_t Settler_t::Is_Flagged(Sleeper_Flag_e flag)
    {
        return (Sleeper_Flags_Variable()->Int() & (1 << static_cast<Int_t>(flag))) > 0;
    }

    template <>
    Bool_t Settler_t::Is_Flagged(Eater_Flag_e flag)
    {
        return (Eater_Flags_Variable()->Int() & (1 << static_cast<Int_t>(flag))) > 0;
    }

    template <>
    Bool_t Settler_t::Is_Flagged(Guard_Flag_e flag)
    {
        return (Guard_Flags_Variable()->Int() & (1 << static_cast<Int_t>(flag))) > 0;
    }

    template <typename Flag_e>
    void Settler_t::Flag(Flag_e flag)
    {
        return;
    }

    template <>
    void Settler_t::Flag(Sandboxer_Flag_e flag)
    {
        Variable_t* variable = Sandboxer_Flags_Variable();
        variable->Int(variable->Int() | (1 << static_cast<Int_t>(flag)));
    }

    template <>
    void Settler_t::Flag(Sleeper_Flag_e flag)
    {
        Variable_t* variable = Sleeper_Flags_Variable();
        variable->Int(variable->Int() | (1 << static_cast<Int_t>(flag)));
    }

    template <>
    void Settler_t::Flag(Eater_Flag_e flag)
    {
        Variable_t* variable = Eater_Flags_Variable();
        variable->Int(variable->Int() | (1 << static_cast<Int_t>(flag)));
    }

    template <>
    void Settler_t::Flag(Guard_Flag_e flag)
    {
        Variable_t* variable = Guard_Flags_Variable();
        variable->Int(variable->Int() | (1 << static_cast<Int_t>(flag)));
    }

    template <typename Flag_e>
    void Settler_t::Unflag(Flag_e flag)
    {
        return;
    }

    template <>
    void Settler_t::Unflag(Sandboxer_Flag_e flag)
    {
        Variable_t* variable = Sandboxer_Flags_Variable();
        variable->Int(variable->Int() & ~(1 << static_cast<Int_t>(flag)));
    }

    template <>
    void Settler_t::Unflag(Sleeper_Flag_e flag)
    {
        Variable_t* variable = Sleeper_Flags_Variable();
        variable->Int(variable->Int() & ~(1 << static_cast<Int_t>(flag)));
    }

    template <>
    void Settler_t::Unflag(Eater_Flag_e flag)
    {
        Variable_t* variable = Eater_Flags_Variable();
        variable->Int(variable->Int() & ~(1 << static_cast<Int_t>(flag)));
    }

    template <>
    void Settler_t::Unflag(Guard_Flag_e flag)
    {
        Variable_t* variable = Guard_Flags_Variable();
        variable->Int(variable->Int() & ~(1 << static_cast<Int_t>(flag)));
    }

    Bool_t Settler_t::Is_Sandboxer()
    {
        return Is_Flagged(Sandboxer_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Sleeper()
    {
        return Is_Flagged(Sleeper_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Eater()
    {
        return Is_Flagged(Eater_Flag_e::IS_ENABLED);
    }

    Bool_t Settler_t::Is_Guard()
    {
        return Is_Flagged(Guard_Flag_e::IS_ENABLED);
    }

    void Settler_t::Enable_Sleeper()
    {
        if (Is_Settler() && !Is_Sleeper()) {
            Actor_t* actor = Actor();
            Flag(Sleeper_Flag_e::IS_ENABLED);
            Object_Ref::Move_To_Orbit(Sleeper_Marker(), Sandboxer_Marker(), 0.0f, 180.0f);
            Default_Sleeper();
            Enforce(actor, true);
        }
    }

    void Settler_t::Enable_Eater()
    {
        if (Is_Settler() && !Is_Eater()) {
            Actor_t* actor = Actor();
            Flag(Eater_Flag_e::IS_ENABLED);
            Object_Ref::Move_To_Orbit(Eater_Marker(), Sandboxer_Marker(), 0.0f, 180.0f);
            Default_Eater();
            Enforce(actor, true);
        }
    }

    void Settler_t::Enable_Guard()
    {
        if (Is_Settler() && !Is_Guard()) {
            Actor_t* actor = Actor();
            Flag(Guard_Flag_e::IS_ENABLED);
            Object_Ref::Move_To_Orbit(Guard_Marker(), Sandboxer_Marker(), 0.0f, 180.0f);
            Default_Guard();
            Enforce(actor, true);
        }
    }

    void Settler_t::Disable_Sleeper()
    {
        if (Is_Sleeper()) {
            Unflag(Sleeper_Flag_e::IS_ENABLED);
            Enforce(Actor(), true);
        }
    }

    void Settler_t::Disable_Eater()
    {
        if (Is_Eater()) {
            Unflag(Eater_Flag_e::IS_ENABLED);
            Enforce(Actor(), true);
        }
    }

    void Settler_t::Disable_Guard()
    {
        if (Is_Guard()) {
            Unflag(Guard_Flag_e::IS_ENABLED);
            Enforce(Actor(), true);
        }
    }

    void Settler_t::Default_Sandboxer()
    {
        if (Is_Settler()) {
            Sandboxer_Radius(DEFAULT_RADIUS);
        }
    }

    void Settler_t::Default_Sleeper()
    {
        if (Is_Sleeper()) {
            Sleeper_Radius(DEFAULT_RADIUS);
            Sleeper_Hour(10 + 12);
            Sleeper_Minute(30);
            Sleeper_Duration(8 * 60);
        }
    }

    void Settler_t::Default_Eater()
    {
        if (Is_Eater()) {
            Eater_Radius(DEFAULT_RADIUS);
            Eater_Hour(12);
            Eater_Minute(0);
            Eater_Duration(2 * 60);
        }
    }

    void Settler_t::Default_Guard()
    {
        if (Is_Guard()) {
            Guard_Radius(DEFAULT_RADIUS);
            Guard_Hour(2 + 12);
            Guard_Minute(0);
            Guard_Duration(6 * 60);
        }
    }

    void Settler_t::Enforce(Actor_t* actor, Bool_t force_reset_ai)
    {
        Bool_t do_reset_ai = force_reset_ai;

        auto Enforce_Sandboxer = [&]()->void
        {
            Package_t* package = Sandboxer_Package();

            package->flags |= static_cast<UInt32>(Package_t::General_Flag_e::PREFERRED_SPEED);
            package->preferred_speed = Package_t::Preferred_Speed_e::RUN;

            Package_Location_t* location = static_cast<Package_Location_Value_t*>
                (package->data->values[static_cast<UInt16>(Sandboxer_Value_e::LOCATION)])->location;
            Int_t radius = Sandboxer_Radius();
            if (location->radius != radius) {
                do_reset_ai = true;
                location->radius = radius;
            }

            Package_Float_Value_t* energy_value = static_cast<Package_Float_Value_t*>
                (package->data->values[static_cast<UInt16>(Sandboxer_Value_e::ENERGY)]);
            Float_t energy = 100.0f;
            if (energy_value->value != energy) {
                do_reset_ai = true;
                energy_value->value = energy;
            }
        };

        auto Enforce_Sleeper = [&]()->void
        {
            if (Is_Sleeper()) {
                Object_Ref::Token(actor, Consts::Settler_Sleeper_Token());

                Package_t* package = Sleeper_Package();

                package->flags |= static_cast<UInt32>(Package_t::General_Flag_e::PREFERRED_SPEED);
                package->preferred_speed = Package_t::Preferred_Speed_e::RUN;

                Package_Schedule_t& schedule = package->schedule;
                Int_t hour = Sleeper_Hour();
                if (schedule.hour != hour) {
                    do_reset_ai = true;
                    schedule.hour = hour;
                }
                Int_t minute = Sleeper_Minute();
                if (schedule.minute != minute) {
                    do_reset_ai = true;
                    schedule.minute = minute;
                }
                Int_t duration = Sleeper_Duration();
                if (schedule.duration_in_minutes != duration) {
                    do_reset_ai = true;
                    schedule.duration_in_minutes = duration;
                }

                Package_Location_t* location = static_cast<Package_Location_Value_t*>
                    (package->data->values[static_cast<UInt16>(Sleeper_Value_e::LOCATION)])->location;
                UInt32 marker_handle = Sleeper_Marker()->CreateRefHandle();
                if (location->location.handle != marker_handle) {
                    do_reset_ai = true;
                    location->location.handle = marker_handle;
                }
                Int_t radius = Sleeper_Radius();
                if (location->radius != radius) {
                    do_reset_ai = true;
                    location->radius = radius;
                }

                Package_Float_Value_t* energy_value = static_cast<Package_Float_Value_t*>
                    (package->data->values[static_cast<UInt16>(Sleeper_Value_e::ENERGY)]);
                Float_t energy = 10.0f;
                if (energy_value->value != energy) {
                    do_reset_ai = true;
                    energy_value->value = energy;
                }
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Sleeper_Token());
            }
        };

        auto Enforce_Eater = [&]()->void
        {
            if (Is_Eater()) {
                Object_Ref::Token(actor, Consts::Settler_Eater_Token());

                Package_t* package = Eater_Package();

                package->flags |= static_cast<UInt32>(Package_t::General_Flag_e::PREFERRED_SPEED);
                package->preferred_speed = Package_t::Preferred_Speed_e::RUN;

                Package_Schedule_t& schedule = package->schedule;
                Int_t hour = Eater_Hour();
                if (schedule.hour != hour) {
                    do_reset_ai = true;
                    schedule.hour = hour;
                }
                Int_t minute = Eater_Minute();
                if (schedule.minute != minute) {
                    do_reset_ai = true;
                    schedule.minute = minute;
                }
                Int_t duration = Eater_Duration();
                if (schedule.duration_in_minutes != duration) {
                    do_reset_ai = true;
                    schedule.duration_in_minutes = duration;
                }

                Package_Location_t* location = static_cast<Package_Location_Value_t*>
                    (package->data->values[static_cast<UInt16>(Eater_Value_e::LOCATION)])->location;
                UInt32 marker_handle = Eater_Marker()->CreateRefHandle();
                if (location->location.handle != marker_handle) {
                    do_reset_ai = true;
                    location->location.handle = marker_handle;
                }
                Int_t radius = Eater_Radius();
                if (location->radius != radius) {
                    do_reset_ai = true;
                    location->radius = radius;
                }

                Package_Float_Value_t* energy_value = static_cast<Package_Float_Value_t*>
                    (package->data->values[static_cast<UInt16>(Eater_Value_e::ENERGY)]);
                Float_t energy = 10.0f;
                if (energy_value->value != energy) {
                    do_reset_ai = true;
                    energy_value->value = energy;
                }
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Eater_Token());
            }
        };

        auto Enforce_Guard = [&]()->void
        {
            if (Is_Guard()) {
                Object_Ref::Token(actor, Consts::Settler_Guard_Token());

                Package_t* package = Guard_Package();

                package->flags |= static_cast<UInt32>(Package_t::General_Flag_e::PREFERRED_SPEED);
                package->preferred_speed = Package_t::Preferred_Speed_e::RUN;
                
                Package_Schedule_t& schedule = package->schedule;
                Int_t hour = Guard_Hour();
                if (schedule.hour != hour) {
                    do_reset_ai = true;
                    schedule.hour = hour;
                }
                Int_t minute = Guard_Minute();
                if (schedule.minute != minute) {
                    do_reset_ai = true;
                    schedule.minute = minute;
                }
                Int_t duration = Guard_Duration();
                if (schedule.duration_in_minutes != duration) {
                    do_reset_ai = true;
                    schedule.duration_in_minutes = duration;
                }

                Package_Target_t* target = static_cast<Package_Single_Reference_Value_t*>
                    (package->data->values[static_cast<UInt16>(Guard_Value_e::PATROL_START)])->target;
                Package_Location_t* location = static_cast<Package_Location_Value_t*>
                    (package->data->values[static_cast<UInt16>(Guard_Value_e::LOCATION)])->location;
                UInt32 marker_handle = Guard_Marker()->CreateRefHandle();
                if (target->target.specific != marker_handle) {
                    do_reset_ai = true;
                    target->target.specific = marker_handle;
                }
                if (location->location.handle != marker_handle) {
                    do_reset_ai = true;
                    location->location.handle = marker_handle;
                }
                Int_t radius = Guard_Radius();
                if (location->radius != radius) {
                    do_reset_ai = true;
                    location->radius = radius;
                }

                Package_Float_Value_t* patrol_radius_value = static_cast<Package_Float_Value_t*>
                    (package->data->values[static_cast<UInt16>(Guard_Value_e::PATROL_RADIUS)]);
                if (patrol_radius_value->value != radius) { // may want this to be a separate value.
                    do_reset_ai = true;
                    patrol_radius_value->value = static_cast<Float_t>(radius);
                }
            } else {
                Object_Ref::Untoken(actor, Consts::Settler_Guard_Token());
            }
        };

        Enforce_Sandboxer();
        Enforce_Sleeper();
        Enforce_Eater();
        Enforce_Guard();

        if (do_reset_ai) {
            Actor2::Reset_AI(Actor());
        }
    }

}}}
