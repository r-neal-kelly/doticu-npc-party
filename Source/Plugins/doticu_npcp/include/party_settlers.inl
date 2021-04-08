/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/package.h"
#include "doticu_skylib/package_data.h"
#include "doticu_skylib/package_location.h"
#include "doticu_skylib/package_value.h"
#include "doticu_skylib/package_value_bool.h"
#include "doticu_skylib/package_value_float.h"
#include "doticu_skylib/package_value_int.h"
#include "doticu_skylib/package_value_list.h"
#include "doticu_skylib/package_value_location.h"
#include "doticu_skylib/package_value_reference.h"
#include "doticu_skylib/package_value_target.h"
#include "doticu_skylib/package_value_topic.h"
#include "doticu_skylib/static.h"

#include "consts.h"
#include "intrinsic.h"
#include "party_settlers.h"

namespace doticu_npcp { namespace Party {

    template <typename T>
    inline some<Misc_t*> Settlers_t::Token()
    {
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Sandboxer_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sandboxer();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Sleeper_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sleeper();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Sitter_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sitter();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Eater_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Eater();
    }

    template <>
    inline some<Misc_t*> Settlers_t::Token<Guard_t>()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Guard();
    }

    template <typename T>
    inline some<Form_List_t*> Settlers_t::Packages()
    {
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Sandboxer_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Sandboxer_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Sleeper_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Sleeper_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Sitter_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Sitter_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Eater_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Eater_Packages();
    }

    template <>
    inline some<Form_List_t*> Settlers_t::Packages<Guard_t>()
    {
        return Consts_t::NPCP::Form_List::Settler_Guard_Packages();
    }

    template <typename T>
    inline some<Package_t*> Settlers_t::Package(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Packages<T>()->At(valid_settler_id())->As_Package()();
    }

    template <typename T>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags()
    {
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Sandboxer_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.sandboxer_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Sleeper_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.sleeper_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Sitter_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.sitter_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Eater_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.eater_flags);
    }

    template <>
    inline Vector_t<Settler_Flags_e>& Settlers_t::Flags<Guard_t>()
    {
        return reinterpret_cast<Vector_t<Settler_Flags_e>&>(this->save_state.guard_flags);
    }

    template <typename T>
    inline Settler_Flags_e& Settlers_t::Flags(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Flags<T>()[settler_id()];
    }

    template <typename T>
    inline Bool_t Settlers_t::Is_Flagged(some<Settler_ID_t> settler_id, Settler_Flags_e flag)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Flags<T>(settler_id).Is_Flagged(flag);
    }

    template <typename T>
    inline void Settlers_t::Is_Flagged(some<Settler_ID_t> settler_id, Settler_Flags_e flag, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Flags<T>(settler_id).Is_Flagged(flag, value);
    }

    template <typename T>
    inline Bool_t Settlers_t::Is_Enabled(some<Settler_ID_t> settler_id)
    {
    }

    template <>
    inline Bool_t Settlers_t::Is_Enabled<Sandboxer_t>(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Is_Flagged<Sandboxer_t>(settler_id, Settler_Flags_Sandboxer_e::IS_ENABLED);
    }

    template <>
    inline Bool_t Settlers_t::Is_Enabled<Sleeper_t>(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Is_Flagged<Sleeper_t>(settler_id, Settler_Flags_Sleeper_e::IS_ENABLED);
    }

    template <>
    inline Bool_t Settlers_t::Is_Enabled<Sitter_t>(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Is_Flagged<Sitter_t>(settler_id, Settler_Flags_Sitter_e::IS_ENABLED);
    }

    template <>
    inline Bool_t Settlers_t::Is_Enabled<Eater_t>(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Is_Flagged<Eater_t>(settler_id, Settler_Flags_Eater_e::IS_ENABLED);
    }

    template <>
    inline Bool_t Settlers_t::Is_Enabled<Guard_t>(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return Is_Flagged<Guard_t>(settler_id, Settler_Flags_Guard_e::IS_ENABLED);
    }

    template <typename T>
    inline void Settlers_t::Is_Enabled(some<Settler_ID_t> settler_id, Bool_t value)
    {
    }

    template <>
    inline void Settlers_t::Is_Enabled<Sandboxer_t>(some<Settler_ID_t> settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Is_Flagged<Sandboxer_t>(settler_id, Settler_Flags_Sandboxer_e::IS_ENABLED, value);
    }

    template <>
    inline void Settlers_t::Is_Enabled<Sleeper_t>(some<Settler_ID_t> settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Is_Flagged<Sleeper_t>(settler_id, Settler_Flags_Sleeper_e::IS_ENABLED, value);
    }

    template <>
    inline void Settlers_t::Is_Enabled<Sitter_t>(some<Settler_ID_t> settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Is_Flagged<Sitter_t>(settler_id, Settler_Flags_Sitter_e::IS_ENABLED, value);
    }

    template <>
    inline void Settlers_t::Is_Enabled<Eater_t>(some<Settler_ID_t> settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Is_Flagged<Eater_t>(settler_id, Settler_Flags_Eater_e::IS_ENABLED, value);
    }

    template <>
    inline void Settlers_t::Is_Enabled<Guard_t>(some<Settler_ID_t> settler_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Is_Flagged<Guard_t>(settler_id, Settler_Flags_Guard_e::IS_ENABLED, value);
    }

    template <typename T>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers()
    {
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Sandboxer_t>()
    {
        return this->save_state.sandboxer_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Sleeper_t>()
    {
        return this->save_state.sleeper_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Sitter_t>()
    {
        return this->save_state.sitter_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Eater_t>()
    {
        return this->save_state.eater_markers;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Markers<Guard_t>()
    {
        return this->save_state.guard_markers;
    }

    template <typename T>
    inline some<Reference_t*> Settlers_t::Marker(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Reference_t*>& marker = Markers<T>()[valid_settler_id()];
        if (!marker || !marker->Is_Valid() || marker->Is_Deleted()) {
            marker = Static_t::Create_X_Marker(Members().Actor(valid_settler_id)())();
            SKYLIB_ASSERT_SOME(marker);
        }

        return marker();
    }

    template <typename T>
    inline void Settlers_t::Move_Marker(some<Settler_ID_t> valid_settler_id, some<Reference_t*> to)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(to);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Marker<T>(valid_settler_id)->Move_To_Orbit(skylib::Const::Actor::Player(), 0.0f, 180.0f);
    }

    template <>
    inline void Settlers_t::Move_Marker<Sleeper_t>(some<Settler_ID_t> valid_settler_id, some<Reference_t*> to)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(to);
        SKYLIB_ASSERT(Is_Enabled<Sleeper_t>(valid_settler_id));

        Marker<Sleeper_t>(valid_settler_id)->Move_To_Orbit(skylib::Const::Actor::Player(), 0.0f, 180.0f);

        maybe<Reference_t*> bed = Bed<Sleeper_t>(valid_settler_id);
        if (bed) {
            bed->Move_To_Orbit(skylib::Const::Actor::Player(), 0.0f, 180.0f);
        }
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Sandboxer_t>()
    {
        return this->save_state.sandboxer_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Sleeper_t>()
    {
        return this->save_state.sleeper_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Sitter_t>()
    {
        return this->save_state.sitter_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Eater_t>()
    {
        return this->save_state.eater_radii;
    }

    template <>
    inline Vector_t<maybe<Settler_Radius_t>>& Settlers_t::Radii<Guard_t>()
    {
        return this->save_state.guard_radii;
    }

    template <typename T>
    inline some<Settler_Radius_t> Settlers_t::Radius(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Radius_t>& radius = Radii<T>()[valid_settler_id()];
        if (!radius) {
            radius = DEFAULT_RADIUS;
            SKYLIB_ASSERT_SOME(radius);
        }

        return radius();
    }

    template <typename T>
    inline void Settlers_t::Radius(some<Settler_ID_t> valid_settler_id, some<Settler_Radius_t> radius)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(radius);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Radii<T>()[valid_settler_id()] = radius;
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Sandboxer_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Sleeper_t>()
    {
        return this->save_state.sleeper_times;
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Sitter_t>()
    {
        return this->save_state.sitter_times;
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Eater_t>()
    {
        return this->save_state.eater_times;
    }

    template <>
    inline Vector_t<maybe<Settler_Time_t>>& Settlers_t::Times<Guard_t>()
    {
        return this->save_state.guard_times;
    }

    template <typename T>
    inline some<Settler_Time_t> Settlers_t::Time(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Time_t>& time = Times<T>()[valid_settler_id()];
        if (!time) {
            time = DEFAULT_TIME;
            SKYLIB_ASSERT_SOME(time);
        }

        return time();
    }

    template <>
    inline some<Settler_Time_t> Settlers_t::Time<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time(some<Settler_ID_t> valid_settler_id, some<Settler_Time_t> time)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(time);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Times<T>()[valid_settler_id()] = time;
    }

    template <>
    inline void Settlers_t::Time<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_t> time) = delete;

    template <typename T>
    inline some<Settler_Time_AM_PM_e> Settlers_t::Time_AM_PM(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Time_AM_PM_e> am_pm = Time<T>(valid_settler_id).AM_PM();
        SKYLIB_ASSERT_SOME(am_pm);

        return am_pm();
    }

    template <>
    inline some<Settler_Time_AM_PM_e> Settlers_t::Time_AM_PM<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time_AM_PM(some<Settler_ID_t> valid_settler_id, some<Settler_Time_AM_PM_e> am_pm)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(am_pm);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Time_t> time = Time<T>(valid_settler_id);
        time.AM_PM(am_pm);
        Time<T>(valid_settler_id, time);
    }

    template <>
    inline void Settlers_t::Time_AM_PM<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_AM_PM_e> am_pm) = delete;

    template <typename T>
    inline some<Settler_Time_Hour_t> Settlers_t::Time_Hour(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Time_Hour_t> hour = Time<T>(valid_settler_id).Hour();
        SKYLIB_ASSERT_SOME(hour);

        return hour();
    }

    template <>
    inline some<Settler_Time_Hour_t> Settlers_t::Time_Hour<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time_Hour(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Hour_t> hour)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(hour);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Time_t> time = Time<T>(valid_settler_id);
        time.Hour(hour);
        Time<T>(valid_settler_id, time);
    }

    template <>
    inline void Settlers_t::Time_Hour<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Hour_t> hour) = delete;

    template <typename T>
    inline some<Settler_Time_Minute_t> Settlers_t::Time_Minute(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Time_Minute_t> minute = Time<T>(valid_settler_id).Minute();
        SKYLIB_ASSERT_SOME(minute);

        return minute();
    }

    template <>
    inline some<Settler_Time_Minute_t> Settlers_t::Time_Minute<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Time_Minute(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Minute_t> minute)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(minute);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Time_t> time = Time<T>(valid_settler_id);
        time.Minute(minute);
        Time<T>(valid_settler_id, time);
    }

    template <>
    inline void Settlers_t::Time_Minute<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Time_Minute_t> minute) = delete;

    template <typename T>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Sandboxer_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Sleeper_t>()
    {
        return this->save_state.sleeper_durations;
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Sitter_t>()
    {
        return this->save_state.sitter_durations;
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Eater_t>()
    {
        return this->save_state.eater_durations;
    }

    template <>
    inline Vector_t<maybe<Settler_Duration_t>>& Settlers_t::Durations<Guard_t>()
    {
        return this->save_state.guard_durations;
    }

    template <typename T>
    inline some<Settler_Duration_t> Settlers_t::Duration(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Duration_t>& duration = Durations<T>()[valid_settler_id()];
        if (!duration) {
            duration = DEFAULT_DURATION;
            SKYLIB_ASSERT_SOME(duration);
        }

        return duration();
    }

    template <>
    inline some<Settler_Duration_t> Settlers_t::Duration<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Duration(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_t> duration)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(duration);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Durations<T>()[valid_settler_id()] = duration;
    }

    template <>
    inline void Settlers_t::Duration<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_t> duration) = delete;

    template <typename T>
    inline some<Settler_Duration_Hours_t> Settlers_t::Duration_Hours(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Duration_Hours_t> hours = Duration<T>(valid_settler_id).Hours();
        SKYLIB_ASSERT_SOME(hours);

        return hours();
    }

    template <>
    inline some<Settler_Duration_Hours_t> Settlers_t::Duration_Hours<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Duration_Hours(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_Hours_t> hours)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(hours);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Duration_t> duration = Duration<T>(valid_settler_id);
        duration.Hours(hours);
        Duration<T>(valid_settler_id, duration);
    }

    template <>
    inline void Settlers_t::Duration_Hours<Sandboxer_t>(some<Settler_ID_t> valid_settler_id,
                                                        some<Settler_Duration_Hours_t> hours) = delete;

    template <typename T>
    inline some<Settler_Duration_Minutes_t> Settlers_t::Duration_Minutes(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Duration_Minutes_t> minutes = Duration<T>(valid_settler_id).Minutes();
        SKYLIB_ASSERT_SOME(minutes);

        return minutes();
    }

    template <>
    inline some<Settler_Duration_Minutes_t> Settlers_t::Duration_Minutes<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Duration_Minutes(some<Settler_ID_t> valid_settler_id, some<Settler_Duration_Minutes_t> minutes)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(minutes);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        some<Settler_Duration_t> duration = Duration<T>(valid_settler_id);
        duration.Minutes(minutes);
        Duration<T>(valid_settler_id, duration);
    }

    template <>
    inline void Settlers_t::Duration_Minutes<Sandboxer_t>(some<Settler_ID_t> valid_settler_id,
                                                          some<Settler_Duration_Minutes_t> minutes) = delete;

    template <typename T>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Sandboxer_t>()
    {
        return this->save_state.sandboxer_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Sleeper_t>()
    {
        return this->save_state.sleeper_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Sitter_t>()
    {
        return this->save_state.sitter_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Eater_t>()
    {
        return this->save_state.eater_attentions;
    }

    template <>
    inline Vector_t<maybe<Settler_Attention_t>>& Settlers_t::Attentions<Guard_t>()
    {
        return this->save_state.guard_attentions;
    }

    template <typename T>
    inline some<Settler_Attention_t> Settlers_t::Attention(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Attention_t>& attention = Attentions<T>()[valid_settler_id()];
        if (!attention) {
            attention = DEFAULT_ATTENTION;
            SKYLIB_ASSERT_SOME(attention);
        }

        return attention();
    }

    template <typename T>
    inline void Settlers_t::Attention(some<Settler_ID_t> valid_settler_id, some<Settler_Attention_t> attention)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(attention);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Attentions<T>()[valid_settler_id()] = attention;
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Sandboxer_t>()
    {
        return this->save_state.sandboxer_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Sleeper_t>()
    {
        return this->save_state.sleeper_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Sitter_t>()
    {
        return this->save_state.sitter_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Eater_t>()
    {
        return this->save_state.eater_speeds;
    }

    template <>
    inline Vector_t<maybe<Settler_Speed_e>>& Settlers_t::Speeds<Guard_t>()
    {
        return this->save_state.guard_speeds;
    }

    template <typename T>
    inline some<Settler_Speed_e> Settlers_t::Speed(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Speed_e>& speed = Speeds<T>()[valid_settler_id()];
        if (!speed) {
            speed = DEFAULT_SPEED;
            SKYLIB_ASSERT_SOME(speed);
        }

        return speed();
    }

    template <typename T>
    inline void Settlers_t::Speed(some<Settler_ID_t> valid_settler_id, some<Settler_Speed_e> speed)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(speed);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Speeds<T>()[valid_settler_id()] = speed;
    }

    template <typename T>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances()
    {
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Sandboxer_t>()
    {
        return this->save_state.sandboxer_wander_distances;
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Sleeper_t>()
    {
        return this->save_state.sleeper_wander_distances;
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Sitter_t>() = delete;

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Eater_t>()
    {
        return this->save_state.eater_wander_distances;
    }

    template <>
    inline Vector_t<maybe<Settler_Wander_Distance_t>>& Settlers_t::Wander_Distances<Guard_t>() = delete;

    template <typename T>
    inline some<Settler_Wander_Distance_t> Settlers_t::Wander_Distance(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        maybe<Settler_Wander_Distance_t>& wander_distance = Wander_Distances<T>()[valid_settler_id()];
        if (!wander_distance) {
            wander_distance = DEFAULT_WANDER_DISTANCE;
            SKYLIB_ASSERT_SOME(wander_distance);
        }

        return wander_distance();
    }

    template <>
    inline some<Settler_Wander_Distance_t> Settlers_t::Wander_Distance<Sitter_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline some<Settler_Wander_Distance_t> Settlers_t::Wander_Distance<Guard_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Wander_Distance(some<Settler_ID_t> valid_settler_id,
                                            some<Settler_Wander_Distance_t> wander_distance)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT_SOME(wander_distance);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Wander_Distances<T>()[valid_settler_id()] = wander_distance;
    }

    template <>
    inline void Settlers_t::Wander_Distance<Sitter_t>(some<Settler_ID_t> valid_settler_id,
                                                      some<Settler_Wander_Distance_t> wander_distance) = delete;

    template <>
    inline void Settlers_t::Wander_Distance<Guard_t>(some<Settler_ID_t> valid_settler_id,
                                                     some<Settler_Wander_Distance_t> wander_distance) = delete;

    template <typename T>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds()
    {
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Sandboxer_t>() = delete;

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Sleeper_t>()
    {
        return this->save_state.sleeper_beds;
    }

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Sitter_t>() = delete;

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Eater_t>() = delete;

    template <>
    inline Vector_t<maybe<Reference_t*>>& Settlers_t::Beds<Guard_t>() = delete;

    template <typename T>
    inline maybe<Reference_t*> Settlers_t::Bed(some<Settler_ID_t> valid_settler_id)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        return Beds<T>()[valid_settler_id()];
    }

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Sandboxer_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Sitter_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Eater_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <>
    inline maybe<Reference_t*> Settlers_t::Bed<Guard_t>(some<Settler_ID_t> valid_settler_id) = delete;

    template <typename T>
    inline void Settlers_t::Bed(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed)
    {
        SKYLIB_ASSERT_SOME(valid_settler_id);
        SKYLIB_ASSERT(Is_Enabled<T>(valid_settler_id));

        Beds<T>()[valid_settler_id()] = bed;
    }

    template <>
    inline void Settlers_t::Bed<Sandboxer_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Sitter_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Eater_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

    template <>
    inline void Settlers_t::Bed<Guard_t>(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed) = delete;

}}
