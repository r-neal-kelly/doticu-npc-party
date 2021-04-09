/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "main.h"
#include "npcp.h"
#include "party_main.h"
#include "party_members.h"
#include "party_settlers.inl"

namespace doticu_npcp { namespace Party {

    const Settler_Duration_t    Settlers_t::DEFAULT_DURATION(DEFAULT_DURATION_HOURS, DEFAULT_DURATION_MINUTES);
    const Settler_Time_t        Settlers_t::DEFAULT_TIME(DEFAULT_TIME_AM_PM, DEFAULT_TIME_HOUR, DEFAULT_TIME_MINUTE);

    Settlers_t::Save_State::Save_State(const some<Quest_t*> quest) :
        quest(quest),

        sandboxer_flags(Vector_t<Settler_Flags_Sandboxer_e>(MAX_SETTLERS, 0)),
        sleeper_flags(Vector_t<Settler_Flags_Sleeper_e>(MAX_SETTLERS, 0)),
        sitter_flags(Vector_t<Settler_Flags_Sitter_e>(MAX_SETTLERS, 0)),
        eater_flags(Vector_t<Settler_Flags_Eater_e>(MAX_SETTLERS, 0)),
        guard_flags(Vector_t<Settler_Flags_Guard_e>(MAX_SETTLERS, 0)),

        sandboxer_markers(Vector_t<maybe<Reference_t*>>(MAX_SETTLERS, none<Reference_t*>())),
        sleeper_markers(Vector_t<maybe<Reference_t*>>(MAX_SETTLERS, none<Reference_t*>())),
        sitter_markers(Vector_t<maybe<Reference_t*>>(MAX_SETTLERS, none<Reference_t*>())),
        eater_markers(Vector_t<maybe<Reference_t*>>(MAX_SETTLERS, none<Reference_t*>())),
        guard_markers(Vector_t<maybe<Reference_t*>>(MAX_SETTLERS, none<Reference_t*>())),

        sandboxer_radii(Vector_t<maybe<Settler_Radius_t>>(MAX_SETTLERS, DEFAULT_RADIUS)),
        sleeper_radii(Vector_t<maybe<Settler_Radius_t>>(MAX_SETTLERS, DEFAULT_RADIUS)),
        sitter_radii(Vector_t<maybe<Settler_Radius_t>>(MAX_SETTLERS, DEFAULT_RADIUS)),
        eater_radii(Vector_t<maybe<Settler_Radius_t>>(MAX_SETTLERS, DEFAULT_RADIUS)),
        guard_radii(Vector_t<maybe<Settler_Radius_t>>(MAX_SETTLERS, DEFAULT_RADIUS)),

        sleeper_times(Vector_t<maybe<Settler_Time_t>>(MAX_SETTLERS, DEFAULT_TIME)),
        sitter_times(Vector_t<maybe<Settler_Time_t>>(MAX_SETTLERS, DEFAULT_TIME)),
        eater_times(Vector_t<maybe<Settler_Time_t>>(MAX_SETTLERS, DEFAULT_TIME)),
        guard_times(Vector_t<maybe<Settler_Time_t>>(MAX_SETTLERS, DEFAULT_TIME)),

        sleeper_durations(Vector_t<maybe<Settler_Duration_t>>(MAX_SETTLERS, DEFAULT_DURATION)),
        sitter_durations(Vector_t<maybe<Settler_Duration_t>>(MAX_SETTLERS, DEFAULT_DURATION)),
        eater_durations(Vector_t<maybe<Settler_Duration_t>>(MAX_SETTLERS, DEFAULT_DURATION)),
        guard_durations(Vector_t<maybe<Settler_Duration_t>>(MAX_SETTLERS, DEFAULT_DURATION)),

        sandboxer_attentions(Vector_t<maybe<Settler_Attention_t>>(MAX_SETTLERS, DEFAULT_ATTENTION)),
        sleeper_attentions(Vector_t<maybe<Settler_Attention_t>>(MAX_SETTLERS, DEFAULT_ATTENTION)),
        eater_attentions(Vector_t<maybe<Settler_Attention_t>>(MAX_SETTLERS, DEFAULT_ATTENTION)),

        sandboxer_speeds(Vector_t<maybe<Settler_Speed_e>>(MAX_SETTLERS, DEFAULT_SPEED)),
        sleeper_speeds(Vector_t<maybe<Settler_Speed_e>>(MAX_SETTLERS, DEFAULT_SPEED)),
        sitter_speeds(Vector_t<maybe<Settler_Speed_e>>(MAX_SETTLERS, DEFAULT_SPEED)),
        eater_speeds(Vector_t<maybe<Settler_Speed_e>>(MAX_SETTLERS, DEFAULT_SPEED)),
        guard_speeds(Vector_t<maybe<Settler_Speed_e>>(MAX_SETTLERS, DEFAULT_SPEED)),

        sandboxer_wander_distances(Vector_t<maybe<Settler_Wander_Distance_t>>(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE)),
        sleeper_wander_distances(Vector_t<maybe<Settler_Wander_Distance_t>>(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE)),
        eater_wander_distances(Vector_t<maybe<Settler_Wander_Distance_t>>(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE)),

        sleeper_beds(Vector_t<maybe<Reference_t*>>(MAX_SETTLERS, none<Reference_t*>()))
    {
    }

    Settlers_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Settlers_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sandboxer_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sandboxer_flags");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_flags");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sitter_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sitter_flags");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_flags");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Guard_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "guard_flags");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Settlers_t::Save_State::Sandboxer_Markers()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "sandboxer_markers");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Settlers_t::Save_State::Sleeper_Markers()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "sleeper_markers");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Settlers_t::Save_State::Sitter_Markers()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "sitter_markers");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Settlers_t::Save_State::Eater_Markers()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "eater_markers");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Settlers_t::Save_State::Guard_Markers()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "guard_markers");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sandboxer_Radii()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sandboxer_radii");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Radii()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_radii");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sitter_Radii()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sitter_radii");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Radii()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_radii");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Guard_Radii()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "guard_radii");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Times()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_times");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sitter_Times()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sitter_times");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Times()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_times");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Guard_Times()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "guard_times");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Durations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_durations");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sitter_Durations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sitter_durations");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Durations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_durations");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Guard_Durations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "guard_durations");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sandboxer_Attentions()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sandboxer_attentions");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Attentions()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_attentions");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Attentions()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_attentions");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sandboxer_Speeds()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sandboxer_speeds");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Speeds()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_speeds");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sitter_Speeds()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sitter_speeds");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Speeds()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_speeds");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Guard_Speeds()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "guard_speeds");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sandboxer_Wander_Distances()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sandboxer_wander_distances");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Sleeper_Wander_Distances()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "sleeper_wander_distances");
    }

    V::Variable_tt<Vector_t<Int_t>>& Settlers_t::Save_State::Eater_Wander_Distances()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "eater_wander_distances");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Settlers_t::Save_State::Sleeper_Beds()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "sleeper_beds");
    }

    void Settlers_t::Save_State::Read()
    {
        // read
        Vector_t<Int_t> sandboxer_flags = Sandboxer_Flags();
        Vector_t<Int_t> sleeper_flags = Sleeper_Flags();
        Vector_t<Int_t> sitter_flags = Sitter_Flags();
        Vector_t<Int_t> eater_flags = Eater_Flags();
        Vector_t<Int_t> guard_flags = Guard_Flags();

        this->sandboxer_markers = Sandboxer_Markers();
        this->sleeper_markers = Sleeper_Markers();
        this->sitter_markers = Sitter_Markers();
        this->eater_markers = Eater_Markers();
        this->guard_markers = Guard_Markers();

        Vector_t<Int_t> sandboxer_radii = Sandboxer_Radii();
        Vector_t<Int_t> sleeper_radii = Sleeper_Radii();
        Vector_t<Int_t> sitter_radii = Sitter_Radii();
        Vector_t<Int_t> eater_radii = Eater_Radii();
        Vector_t<Int_t> guard_radii = Guard_Radii();

        Vector_t<Int_t> sleeper_times = Sleeper_Times();
        Vector_t<Int_t> sitter_times = Sitter_Times();
        Vector_t<Int_t> eater_times = Eater_Times();
        Vector_t<Int_t> guard_times = Guard_Times();

        Vector_t<Int_t> sleeper_durations = Sleeper_Durations();
        Vector_t<Int_t> sitter_durations = Sitter_Durations();
        Vector_t<Int_t> eater_durations = Eater_Durations();
        Vector_t<Int_t> guard_durations = Guard_Durations();

        Vector_t<Int_t> sandboxer_attentions = Sandboxer_Attentions();
        Vector_t<Int_t> sleeper_attentions = Sleeper_Attentions();
        Vector_t<Int_t> eater_attentions = Eater_Attentions();

        Vector_t<Int_t> sandboxer_speeds = Sandboxer_Speeds();
        Vector_t<Int_t> sleeper_speeds = Sleeper_Speeds();
        Vector_t<Int_t> sitter_speeds = Sitter_Speeds();
        Vector_t<Int_t> eater_speeds = Eater_Speeds();
        Vector_t<Int_t> guard_speeds = Guard_Speeds();

        Vector_t<Int_t> sandboxer_wander_distances = Sandboxer_Wander_Distances();
        Vector_t<Int_t> sleeper_wander_distances = Sleeper_Wander_Distances();
        Vector_t<Int_t> eater_wander_distances = Eater_Wander_Distances();

        this->sleeper_beds = Sleeper_Beds();

        // resize
        sandboxer_flags.resize(MAX_SETTLERS, 0);
        sleeper_flags.resize(MAX_SETTLERS, 0);
        sitter_flags.resize(MAX_SETTLERS, 0);
        eater_flags.resize(MAX_SETTLERS, 0);
        guard_flags.resize(MAX_SETTLERS, 0);

        this->sandboxer_markers.resize(MAX_SETTLERS, none<Reference_t*>());
        this->sleeper_markers.resize(MAX_SETTLERS, none<Reference_t*>());
        this->sitter_markers.resize(MAX_SETTLERS, none<Reference_t*>());
        this->eater_markers.resize(MAX_SETTLERS, none<Reference_t*>());
        this->guard_markers.resize(MAX_SETTLERS, none<Reference_t*>());

        sandboxer_radii.resize(MAX_SETTLERS, DEFAULT_RADIUS);
        sleeper_radii.resize(MAX_SETTLERS, DEFAULT_RADIUS);
        sitter_radii.resize(MAX_SETTLERS, DEFAULT_RADIUS);
        eater_radii.resize(MAX_SETTLERS, DEFAULT_RADIUS);
        guard_radii.resize(MAX_SETTLERS, DEFAULT_RADIUS);

        sleeper_times.resize(MAX_SETTLERS, DEFAULT_TIME);
        sitter_times.resize(MAX_SETTLERS, DEFAULT_TIME);
        eater_times.resize(MAX_SETTLERS, DEFAULT_TIME);
        guard_times.resize(MAX_SETTLERS, DEFAULT_TIME);

        sleeper_durations.resize(MAX_SETTLERS, DEFAULT_DURATION);
        sitter_durations.resize(MAX_SETTLERS, DEFAULT_DURATION);
        eater_durations.resize(MAX_SETTLERS, DEFAULT_DURATION);
        guard_durations.resize(MAX_SETTLERS, DEFAULT_DURATION);

        sandboxer_attentions.resize(MAX_SETTLERS, DEFAULT_ATTENTION);
        sleeper_attentions.resize(MAX_SETTLERS, DEFAULT_ATTENTION);
        eater_attentions.resize(MAX_SETTLERS, DEFAULT_ATTENTION);

        sandboxer_speeds.resize(MAX_SETTLERS, DEFAULT_SPEED);
        sleeper_speeds.resize(MAX_SETTLERS, DEFAULT_SPEED);
        sitter_speeds.resize(MAX_SETTLERS, DEFAULT_SPEED);
        eater_speeds.resize(MAX_SETTLERS, DEFAULT_SPEED);
        guard_speeds.resize(MAX_SETTLERS, DEFAULT_SPEED);

        sandboxer_wander_distances.resize(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE);
        sleeper_wander_distances.resize(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE);
        eater_wander_distances.resize(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE);

        this->sleeper_beds.resize(MAX_SETTLERS, none<Reference_t*>());

        // assign
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            this->sandboxer_flags[idx] = sandboxer_flags[idx];
            this->sleeper_flags[idx] = sleeper_flags[idx];
            this->sitter_flags[idx] = sitter_flags[idx];
            this->eater_flags[idx] = eater_flags[idx];
            this->guard_flags[idx] = guard_flags[idx];

            this->sandboxer_radii[idx] = sandboxer_radii[idx];
            this->sleeper_radii[idx] = sleeper_radii[idx];
            this->sitter_radii[idx] = sitter_radii[idx];
            this->eater_radii[idx] = eater_radii[idx];
            this->guard_radii[idx] = guard_radii[idx];

            this->sleeper_times[idx] = sleeper_times[idx];
            this->sitter_times[idx] = sitter_times[idx];
            this->eater_times[idx] = eater_times[idx];
            this->guard_times[idx] = guard_times[idx];

            this->sleeper_durations[idx] = sleeper_durations[idx];
            this->sitter_durations[idx] = sitter_durations[idx];
            this->eater_durations[idx] = eater_durations[idx];
            this->guard_durations[idx] = guard_durations[idx];

            this->sandboxer_attentions[idx] = sandboxer_attentions[idx];
            this->sleeper_attentions[idx] = sleeper_attentions[idx];
            this->eater_attentions[idx] = eater_attentions[idx];

            this->sandboxer_speeds[idx] = sandboxer_speeds[idx];
            this->sleeper_speeds[idx] = sleeper_speeds[idx];
            this->sitter_speeds[idx] = sitter_speeds[idx];
            this->eater_speeds[idx] = eater_speeds[idx];
            this->guard_speeds[idx] = guard_speeds[idx];

            this->sandboxer_wander_distances[idx] = sandboxer_wander_distances[idx];
            this->sleeper_wander_distances[idx] = sleeper_wander_distances[idx];
            this->eater_wander_distances[idx] = eater_wander_distances[idx];
        }
    }

    void Settlers_t::Save_State::Write()
    {
        // buffer
        Vector_t<Int_t> sandboxer_flags(MAX_SETTLERS, 0);
        Vector_t<Int_t> sleeper_flags(MAX_SETTLERS, 0);
        Vector_t<Int_t> sitter_flags(MAX_SETTLERS, 0);
        Vector_t<Int_t> eater_flags(MAX_SETTLERS, 0);
        Vector_t<Int_t> guard_flags(MAX_SETTLERS, 0);

        Vector_t<Int_t> sandboxer_radii(MAX_SETTLERS, DEFAULT_RADIUS);
        Vector_t<Int_t> sleeper_radii(MAX_SETTLERS, DEFAULT_RADIUS);
        Vector_t<Int_t> sitter_radii(MAX_SETTLERS, DEFAULT_RADIUS);
        Vector_t<Int_t> eater_radii(MAX_SETTLERS, DEFAULT_RADIUS);
        Vector_t<Int_t> guard_radii(MAX_SETTLERS, DEFAULT_RADIUS);

        Vector_t<Int_t> sleeper_times(MAX_SETTLERS, DEFAULT_TIME);
        Vector_t<Int_t> sitter_times(MAX_SETTLERS, DEFAULT_TIME);
        Vector_t<Int_t> eater_times(MAX_SETTLERS, DEFAULT_TIME);
        Vector_t<Int_t> guard_times(MAX_SETTLERS, DEFAULT_TIME);

        Vector_t<Int_t> sleeper_durations(MAX_SETTLERS, DEFAULT_DURATION);
        Vector_t<Int_t> sitter_durations(MAX_SETTLERS, DEFAULT_DURATION);
        Vector_t<Int_t> eater_durations(MAX_SETTLERS, DEFAULT_DURATION);
        Vector_t<Int_t> guard_durations(MAX_SETTLERS, DEFAULT_DURATION);

        Vector_t<Int_t> sandboxer_attentions(MAX_SETTLERS, DEFAULT_ATTENTION);
        Vector_t<Int_t> sleeper_attentions(MAX_SETTLERS, DEFAULT_ATTENTION);
        Vector_t<Int_t> eater_attentions(MAX_SETTLERS, DEFAULT_ATTENTION);

        Vector_t<Int_t> sandboxer_speeds(MAX_SETTLERS, DEFAULT_SPEED);
        Vector_t<Int_t> sleeper_speeds(MAX_SETTLERS, DEFAULT_SPEED);
        Vector_t<Int_t> sitter_speeds(MAX_SETTLERS, DEFAULT_SPEED);
        Vector_t<Int_t> eater_speeds(MAX_SETTLERS, DEFAULT_SPEED);
        Vector_t<Int_t> guard_speeds(MAX_SETTLERS, DEFAULT_SPEED);

        Vector_t<Int_t> sandboxer_wander_distances(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE);
        Vector_t<Int_t> sleeper_wander_distances(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE);
        Vector_t<Int_t> eater_wander_distances(MAX_SETTLERS, DEFAULT_WANDER_DISTANCE);

        // read
        for (size_t idx = 0, end = MAX_SETTLERS; idx < end; idx += 1) {
            sandboxer_flags[idx] = this->sandboxer_flags[idx];
            sleeper_flags[idx] = this->sleeper_flags[idx];
            sitter_flags[idx] = this->sitter_flags[idx];
            eater_flags[idx] = this->eater_flags[idx];
            guard_flags[idx] = this->guard_flags[idx];

            sandboxer_radii[idx] = this->sandboxer_radii[idx]();
            sleeper_radii[idx] = this->sleeper_radii[idx]();
            sitter_radii[idx] = this->sitter_radii[idx]();
            eater_radii[idx] = this->eater_radii[idx]();
            guard_radii[idx] = this->guard_radii[idx]();

            sleeper_times[idx] = this->sleeper_times[idx]();
            sitter_times[idx] = this->sitter_times[idx]();
            eater_times[idx] = this->eater_times[idx]();
            guard_times[idx] = this->guard_times[idx]();

            sleeper_durations[idx] = this->sleeper_durations[idx]();
            sitter_durations[idx] = this->sitter_durations[idx]();
            eater_durations[idx] = this->eater_durations[idx]();
            guard_durations[idx] = this->guard_durations[idx]();

            sandboxer_attentions[idx] = this->sandboxer_attentions[idx]();
            sleeper_attentions[idx] = this->sleeper_attentions[idx]();
            eater_attentions[idx] = this->eater_attentions[idx]();

            sandboxer_speeds[idx] = this->sandboxer_speeds[idx]();
            sleeper_speeds[idx] = this->sleeper_speeds[idx]();
            sitter_speeds[idx] = this->sitter_speeds[idx]();
            eater_speeds[idx] = this->eater_speeds[idx]();
            guard_speeds[idx] = this->guard_speeds[idx]();

            sandboxer_wander_distances[idx] = this->sandboxer_wander_distances[idx]();
            sleeper_wander_distances[idx] = this->sleeper_wander_distances[idx]();
            eater_wander_distances[idx] = this->eater_wander_distances[idx]();
        }

        // assign
        Sandboxer_Flags() = sandboxer_flags;
        Sleeper_Flags() = sleeper_flags;
        Sitter_Flags() = sitter_flags;
        Eater_Flags() = eater_flags;
        Guard_Flags() = guard_flags;

        Sandboxer_Markers() = this->sandboxer_markers;
        Sleeper_Markers() = this->sleeper_markers;
        Sitter_Markers() = this->sitter_markers;
        Eater_Markers() = this->eater_markers;
        Guard_Markers() = this->guard_markers;

        Sandboxer_Radii() = sandboxer_radii;
        Sleeper_Radii() = sleeper_radii;
        Sitter_Radii() = sitter_radii;
        Eater_Radii() = eater_radii;
        Guard_Radii() = guard_radii;

        Sleeper_Times() = sleeper_times;
        Sitter_Times() = sitter_times;
        Eater_Times() = eater_times;
        Guard_Times() = guard_times;

        Sleeper_Durations() = sleeper_durations;
        Sitter_Durations() = sitter_durations;
        Eater_Durations() = eater_durations;
        Guard_Durations() = guard_durations;

        Sandboxer_Attentions() = sandboxer_attentions;
        Sleeper_Attentions() = sleeper_attentions;
        Eater_Attentions() = eater_attentions;

        Sandboxer_Speeds() = sandboxer_speeds;
        Sleeper_Speeds() = sleeper_speeds;
        Sitter_Speeds() = sitter_speeds;
        Eater_Speeds() = eater_speeds;
        Guard_Speeds() = guard_speeds;

        Sandboxer_Wander_Distances() = sandboxer_wander_distances;
        Sleeper_Wander_Distances() = sleeper_wander_distances;
        Eater_Wander_Distances() = eater_wander_distances;

        Sleeper_Beds() = this->sleeper_beds;
    }

    String_t Settlers_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_party_settlers");
    }

    some<V::Class_t*> Settlers_t::Class()
    {
        DEFINE_CLASS();
    }

    void Settlers_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)          \
        SKYLIB_M                                                                            \
            BIND_METHOD(machine, class_name, Settlers_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                                \
        SKYLIB_W

        #undef METHOD
    }

    Settlers_t::Settlers_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        save_state(quest)
    {
        if (is_new_game) {

        } else {
            this->save_state.Read();
            Validate();
        }
    }

    Settlers_t::Settlers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest)
    {
        // update code goes here

        this->save_state.Read();
        Validate();
    }

    Settlers_t::~Settlers_t()
    {
    }

    void Settlers_t::Before_Save()
    {
        Validate();
        this->save_state.Write();
    }

    void Settlers_t::After_Save()
    {
    }

    Main_t& Settlers_t::Main()
    {
        return NPCP.Main().Party();
    }

    Members_t& Settlers_t::Members()
    {
        return NPCP.Main().Party().Members();
    }

    Bool_t Settlers_t::Has_Settler(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        return
            Is_Enabled<Sandboxer_t>(settler_id) ||
            Is_Enabled<Sleeper_t>(settler_id) ||
            Is_Enabled<Sitter_t>(settler_id) ||
            Is_Enabled<Eater_t>(settler_id) ||
            Is_Enabled<Guard_t>(settler_id);
    }

    Bool_t Settlers_t::Has_Settler(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        if (Members().Has_Member(member_id)) {
            return Has_Settler(some<Settler_ID_t>(member_id));
        } else {
            return false;
        }
    }

    Bool_t Settlers_t::Has_Settler(some<Actor_t*> actor)
    {
        maybe<Member_ID_t> valid_member_id = Members().Used_Member_ID(actor);
        if (valid_member_id) {
            return Has_Settler(some<Settler_ID_t>(valid_member_id()));
        } else {
            return false;
        }
    }

    maybe<Settler_ID_t> Settlers_t::Add_Settler(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_member_id));

        some<Settler_ID_t> settler_id = valid_member_id;
        if (!Has_Settler(settler_id)) {
            Is_Enabled<Sandboxer_t>(settler_id, true);
            Default<Sandboxer_t>(settler_id);
            Marker<Sandboxer_t>(settler_id)->Move_To_Orbit(Members().Actor(settler_id), 0.0f, 180.0f);
            Main().Update_AI(settler_id, Member_Update_AI_e::EVALUATE_PACKAGE);
            //Main().Enforce(settler_id);
            return settler_id;
        } else {
            return none<Settler_ID_t>();
        }
    }

    void Settlers_t::Validate()
    {

    }

    void Settlers_t::Bool(some<Package_t*> package,
                          Settler_Value_Index_e index,
                          Bool_t value,
                          Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(package->data);

        if (package->data->Bool(index) != value) {
            package->data->Bool(index, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::Float(some<Package_t*> package,
                           Settler_Value_Index_e index,
                           Float_t value,
                           Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(package->data);

        if (package->data->Float(index) != value) {
            package->data->Float(index, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::General_Flag(some<Package_t*> package,
                                  Package_Flags_e general_flag,
                                  Bool_t value,
                                  Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);

        if (package->package_flags.Is_Flagged(general_flag) != value) {
            package->package_flags.Is_Flagged(general_flag, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::Interrupt_Flag(some<Package_t*> package,
                                    Package_Interrupt_Flags_e interrupt_flag,
                                    Bool_t value,
                                    Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);

        if (package->interrupt_flags.Is_Flagged(interrupt_flag) != value) {
            package->interrupt_flags.Is_Flagged(interrupt_flag, value);
            do_reset_ai = true;
        }
    }

    void Settlers_t::Location(some<Package_t*> package,
                              Settler_Value_Index_e index,
                              some<Reference_t*> marker,
                              some<Settler_Radius_t> radius,
                              Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(package->data);

        maybe<Package_Location_t*> location = package->data->Location(index);
        SKYLIB_ASSERT_SOME(location);

        if (location->Reference() != marker()) {
            location->Reference(marker());
            do_reset_ai = true;
        }

        if (location->Radius() != radius) {
            location->Radius(radius());
            do_reset_ai = true;
        }
    }

    void Settlers_t::Schedule(some<Package_t*> package,
                              maybe<Settler_Time_t> time,
                              maybe<Settler_Duration_t> duration,
                              Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);

        if (time) {
            s32 hour = time().Military_Hour();
            if (package->schedule.hour != hour) {
                package->schedule.hour = hour;
                do_reset_ai = true;
            }
            s32 minute = time().Minute()();
            if (package->schedule.minute != minute) {
                package->schedule.minute = minute;
                do_reset_ai = true;
            }
        } else {
            if (package->schedule.hour != -1) {
                package->schedule.hour = -1;
                do_reset_ai = true;
            }
            if (package->schedule.minute != -1) {
                package->schedule.minute = -1;
                do_reset_ai = true;
            }
        }

        if (duration) {
            s32 duration_in_minutes = duration().Total_Minutes();
            if (package->schedule.duration_in_minutes != duration_in_minutes) {
                package->schedule.duration_in_minutes = duration_in_minutes;
                do_reset_ai = true;
            }
        } else {
            if (package->schedule.duration_in_minutes != 0) {
                package->schedule.duration_in_minutes = 0;
                do_reset_ai = true;
            }
        }
    }

    void Settlers_t::Speed(some<Package_t*> package,
                           some<Settler_Speed_e> speed,
                           Bool_t& do_reset_ai)
    {
        SKYLIB_ASSERT_SOME(package);
        SKYLIB_ASSERT_SOME(speed);

        General_Flag(package, Package_Flags_e::ALLOW_PREFERRED_SPEED, true, do_reset_ai);

        if (package->preferred_speed != speed) {
            package->preferred_speed = speed();
            do_reset_ai = true;
        }
    }

    void Settlers_t::Enforce(some<Settler_ID_t> settler_id)
    {
        SKYLIB_ASSERT_SOME(settler_id);

        Members_t& members = Members();
        if (members.Has_Member(settler_id())) {
            Bool_t do_reset_ai = false;

            if (Is_Enabled<Sandboxer_t>(settler_id)) {
                Enforce_Package<Sandboxer_t>(settler_id, do_reset_ai);
                members.Tokenize(settler_id, Token<Sandboxer_t>());
            } else {
                members.Untokenize(settler_id, Token<Sandboxer_t>());
            }

            if (Is_Enabled<Sleeper_t>(settler_id)) {
                Enforce_Package<Sleeper_t>(settler_id, do_reset_ai);

                maybe<Reference_t*> bed = Bed<Sleeper_t>(settler_id);
                if (bed) {
                    bed->This_Actor_Base_Owner(members.Custom_Base(settler_id)); // this may need to be cleared in dtor?
                }

                members.Tokenize(settler_id, Token<Sleeper_t>());
            } else {
                members.Untokenize(settler_id, Token<Sleeper_t>());
            }

            if (Is_Enabled<Sitter_t>(settler_id)) {
                Enforce_Package<Sitter_t>(settler_id, do_reset_ai);
                members.Tokenize(settler_id, Token<Sitter_t>());
            } else {
                members.Untokenize(settler_id, Token<Sitter_t>());
            }

            if (Is_Enabled<Eater_t>(settler_id)) {
                Enforce_Package<Eater_t>(settler_id, do_reset_ai);
                members.Tokenize(settler_id, Token<Eater_t>());
            } else {
                members.Untokenize(settler_id, Token<Eater_t>());
            }

            if (Is_Enabled<Guard_t>(settler_id)) {
                Enforce_Package<Guard_t>(settler_id, do_reset_ai);
                members.Tokenize(settler_id, Token<Guard_t>());
            } else {
                members.Untokenize(settler_id, Token<Guard_t>());
            }

            if (do_reset_ai) {
                Main().Update_AI(settler_id, Member_Update_AI_e::RESET_AI);
            }
        }
    }

}}
