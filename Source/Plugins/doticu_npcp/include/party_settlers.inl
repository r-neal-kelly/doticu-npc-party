/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/static.h"

#include "intrinsic.h"
#include "party_settlers.h"

namespace doticu_npcp { namespace Party {

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

}}
