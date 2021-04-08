/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_main.h"
#include "party_member_id.h"
#include "party_settler_attention.h"
#include "party_settler_duration.h"
#include "party_settler_duration_hours.h"
#include "party_settler_duration_minutes.h"
#include "party_settler_flags.h"
#include "party_settler_flags_eater.h"
#include "party_settler_flags_guard.h"
#include "party_settler_flags_sandboxer.h"
#include "party_settler_flags_sitter.h"
#include "party_settler_flags_sleeper.h"
#include "party_settler_id.h"
#include "party_settler_radius.h"
#include "party_settler_speed.h"
#include "party_settler_time.h"
#include "party_settler_time_am_pm.h"
#include "party_settler_time_hour.h"
#include "party_settler_time_minute.h"
#include "party_settler_value_index.h"
#include "party_settler_value_index_eater.h"
#include "party_settler_value_index_guard.h"
#include "party_settler_value_index_sandboxer.h"
#include "party_settler_value_index_sitter.h"
#include "party_settler_value_index_sleeper.h"
#include "party_settler_wander_distance.h"

namespace doticu_npcp { namespace Party {

    class Eater_t;
    class Guard_t;
    class Sandboxer_t;
    class Sitter_t;
    class Sleeper_t;

    class Settlers_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t                                 MAX_SETTLERS                = Main_t::MAX_SETTLERS;

        static constexpr Settler_Radius_t::value_type           DEFAULT_RADIUS              = 2048;

        static constexpr Settler_Time_AM_PM_e::value_type       DEFAULT_TIME_AM_PM          = Settler_Time_AM_PM_e::PM;
        static constexpr Settler_Time_Hour_t::value_type        DEFAULT_TIME_HOUR           = 6;
        static constexpr Settler_Time_Minute_t::value_type      DEFAULT_TIME_MINUTE         = 0;

        static constexpr Settler_Duration_Hours_t::value_type   DEFAULT_DURATION_HOURS      = 4;
        static constexpr Settler_Duration_Minutes_t::value_type DEFAULT_DURATION_MINUTES    = 0;

        static constexpr Settler_Attention_t::value_type        DEFAULT_ATTENTION           = 50;

        static constexpr Settler_Speed_e::value_type            DEFAULT_SPEED               = Settler_Speed_e::WALK;

        static constexpr Settler_Wander_Distance_t::value_type  DEFAULT_WANDER_DISTANCE     = 512;

    public:
        static const    Settler_Duration_t  DEFAULT_DURATION;
        static const    Settler_Time_t      DEFAULT_TIME;

    public:
        class Save_State
        {
        public:
            const some<Quest_t*>                        quest;

            Vector_t<Settler_Flags_Sandboxer_e>         sandboxer_flags;
            Vector_t<Settler_Flags_Sleeper_e>           sleeper_flags;
            Vector_t<Settler_Flags_Sitter_e>            sitter_flags;
            Vector_t<Settler_Flags_Eater_e>             eater_flags;
            Vector_t<Settler_Flags_Guard_e>             guard_flags;

            Vector_t<maybe<Reference_t*>>               sandboxer_markers;
            Vector_t<maybe<Reference_t*>>               sleeper_markers;
            Vector_t<maybe<Reference_t*>>               sitter_markers;
            Vector_t<maybe<Reference_t*>>               eater_markers;
            Vector_t<maybe<Reference_t*>>               guard_markers;

            Vector_t<maybe<Settler_Radius_t>>           sandboxer_radii;
            Vector_t<maybe<Settler_Radius_t>>           sleeper_radii;
            Vector_t<maybe<Settler_Radius_t>>           sitter_radii;
            Vector_t<maybe<Settler_Radius_t>>           eater_radii;
            Vector_t<maybe<Settler_Radius_t>>           guard_radii;

            Vector_t<maybe<Settler_Time_t>>             sleeper_times;
            Vector_t<maybe<Settler_Time_t>>             sitter_times;
            Vector_t<maybe<Settler_Time_t>>             eater_times;
            Vector_t<maybe<Settler_Time_t>>             guard_times;

            Vector_t<maybe<Settler_Duration_t>>         sleeper_durations;
            Vector_t<maybe<Settler_Duration_t>>         sitter_durations;
            Vector_t<maybe<Settler_Duration_t>>         eater_durations;
            Vector_t<maybe<Settler_Duration_t>>         guard_durations;

            Vector_t<maybe<Settler_Attention_t>>        sandboxer_attentions;
            Vector_t<maybe<Settler_Attention_t>>        sleeper_attentions;
            Vector_t<maybe<Settler_Attention_t>>        sitter_attentions;
            Vector_t<maybe<Settler_Attention_t>>        eater_attentions;
            Vector_t<maybe<Settler_Attention_t>>        guard_attentions;

            Vector_t<maybe<Settler_Speed_e>>            sandboxer_speeds;
            Vector_t<maybe<Settler_Speed_e>>            sleeper_speeds;
            Vector_t<maybe<Settler_Speed_e>>            sitter_speeds;
            Vector_t<maybe<Settler_Speed_e>>            eater_speeds;
            Vector_t<maybe<Settler_Speed_e>>            guard_speeds;

            Vector_t<maybe<Settler_Wander_Distance_t>>  sandboxer_wander_distances;
            Vector_t<maybe<Settler_Wander_Distance_t>>  sleeper_wander_distances;
            Vector_t<maybe<Settler_Wander_Distance_t>>  eater_wander_distances;

            Vector_t<maybe<Reference_t*>>               sleeper_beds;

        public:
            Save_State(const some<Quest_t*> quest);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>                              Object();

            V::Variable_tt<Vector_t<Int_t>>&                Sandboxer_Flags();
            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Flags();
            V::Variable_tt<Vector_t<Int_t>>&                Sitter_Flags();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Flags();
            V::Variable_tt<Vector_t<Int_t>>&                Guard_Flags();

            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Sandboxer_Markers();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Sleeper_Markers();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Sitter_Markers();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Eater_Markers();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Guard_Markers();

            V::Variable_tt<Vector_t<Int_t>>&                Sandboxer_Radii();
            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Radii();
            V::Variable_tt<Vector_t<Int_t>>&                Sitter_Radii();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Radii();
            V::Variable_tt<Vector_t<Int_t>>&                Guard_Radii();

            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Times();
            V::Variable_tt<Vector_t<Int_t>>&                Sitter_Times();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Times();
            V::Variable_tt<Vector_t<Int_t>>&                Guard_Times();

            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Durations();
            V::Variable_tt<Vector_t<Int_t>>&                Sitter_Durations();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Durations();
            V::Variable_tt<Vector_t<Int_t>>&                Guard_Durations();

            V::Variable_tt<Vector_t<Int_t>>&                Sandboxer_Attentions();
            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Attentions();
            V::Variable_tt<Vector_t<Int_t>>&                Sitter_Attentions();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Attentions();
            V::Variable_tt<Vector_t<Int_t>>&                Guard_Attentions();

            V::Variable_tt<Vector_t<Int_t>>&                Sandboxer_Speeds();
            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Speeds();
            V::Variable_tt<Vector_t<Int_t>>&                Sitter_Speeds();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Speeds();
            V::Variable_tt<Vector_t<Int_t>>&                Guard_Speeds();

            V::Variable_tt<Vector_t<Int_t>>&                Sandboxer_Wander_Distances();
            V::Variable_tt<Vector_t<Int_t>>&                Sleeper_Wander_Distances();
            V::Variable_tt<Vector_t<Int_t>>&                Eater_Wander_Distances();

            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Sleeper_Beds();

        public:
            void    Read();
            void    Write();
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        const some<Quest_t*>    quest;
        Save_State              save_state;

    public:
        Settlers_t(some<Quest_t*> quest, Bool_t is_new_game);
        Settlers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Settlers_t(const Settlers_t& other)                                         = delete;
        Settlers_t(Settlers_t&& other) noexcept                                     = delete;
        Settlers_t& operator =(const Settlers_t& other)                             = delete;
        Settlers_t& operator =(Settlers_t&& other) noexcept                         = delete;
        ~Settlers_t();

    public:
        void    Before_Save();
        void    After_Save();

    public:
        Members_t&          Members();

        Bool_t              Has_Settler(some<Settler_ID_t> settler_id);
        Bool_t              Has_Settler(some<Member_ID_t> member_id);
        Bool_t              Has_Settler(some<Actor_t*> actor);

        maybe<Settler_ID_t> Add_Settler(some<Member_ID_t> valid_member_id);
        Bool_t              Remove_Settler(some<Settler_ID_t> settler_id);

        void                Validate();

    public:
        template <typename T>
        some<Misc_t*>                               Token();

        template <typename T>
        some<Form_List_t*>                          Packages();
        template <typename T>
        some<Package_t*>                            Package(some<Settler_ID_t> valid_settler_id);

        template <typename T>
        Vector_t<Settler_Flags_e>&                  Flags();
        template <typename T>
        Settler_Flags_e&                            Flags(some<Settler_ID_t> settler_id);
        template <typename T>
        Bool_t                                      Is_Flagged(some<Settler_ID_t> settler_id, Settler_Flags_e flag);
        template <typename T>
        void                                        Is_Flagged(some<Settler_ID_t> settler_id, Settler_Flags_e flag, Bool_t value);

        template <typename T>
        Bool_t                                      Is_Enabled(some<Settler_ID_t> settler_id);
        template <typename T>
        void                                        Is_Enabled(some<Settler_ID_t> settler_id, Bool_t value);

        template <typename T>
        Vector_t<maybe<Reference_t*>>&              Markers();
        template <typename T>
        some<Reference_t*>                          Marker(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Move_Marker(some<Settler_ID_t> valid_settler_id, some<Reference_t*> to);

        template <typename T>
        Vector_t<maybe<Settler_Radius_t>>&          Radii();
        template <typename T>
        some<Settler_Radius_t>                      Radius(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Radius(some<Settler_ID_t> valid_settler_id, some<Settler_Radius_t> radius);

        template <typename T>
        Vector_t<maybe<Settler_Time_t>>&            Times();
        template <typename T>
        some<Settler_Time_t>                        Time(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Time(some<Settler_ID_t> valid_settler_id, some<Settler_Time_t> time);
        template <typename T>
        some<Settler_Time_AM_PM_e>                  Time_AM_PM(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Time_AM_PM(some<Settler_ID_t> valid_settler_id,
                                                               some<Settler_Time_AM_PM_e> am_pm);
        template <typename T>
        some<Settler_Time_Hour_t>                   Time_Hour(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Time_Hour(some<Settler_ID_t> valid_settler_id,
                                                              some<Settler_Time_Hour_t> hour);
        template <typename T>
        some<Settler_Time_Minute_t>                 Time_Minute(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Time_Minute(some<Settler_ID_t> valid_settler_id,
                                                                some<Settler_Time_Minute_t> minute);

        template <typename T>
        Vector_t<maybe<Settler_Duration_t>>&        Durations();
        template <typename T>
        some<Settler_Duration_t>                    Duration(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Duration(some<Settler_ID_t> valid_settler_id,
                                                             some<Settler_Duration_t> duration);
        template <typename T>
        some<Settler_Duration_Hours_t>              Duration_Hours(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Duration_Hours(some<Settler_ID_t> valid_settler_id,
                                                                   some<Settler_Duration_Hours_t> hours);
        template <typename T>
        some<Settler_Duration_Minutes_t>            Duration_Minutes(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Duration_Minutes(some<Settler_ID_t> valid_settler_id,
                                                                     some<Settler_Duration_Minutes_t> minutes);

        template <typename T>
        Vector_t<maybe<Settler_Attention_t>>&       Attentions();
        template <typename T>
        some<Settler_Attention_t>                   Attention(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Attention(some<Settler_ID_t> valid_settler_id, some<Settler_Attention_t> attention);

        template <typename T>
        Vector_t<maybe<Settler_Speed_e>>&           Speeds();
        template <typename T>
        some<Settler_Speed_e>                       Speed(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Speed(some<Settler_ID_t> valid_settler_id, some<Settler_Speed_e> speed);

        template <typename T>
        Vector_t<maybe<Settler_Wander_Distance_t>>& Wander_Distances();
        template <typename T>
        some<Settler_Wander_Distance_t>             Wander_Distance(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Wander_Distance(some<Settler_ID_t> valid_settler_id,
                                                                    some<Settler_Wander_Distance_t> wander_distance);

        template <typename T>
        Vector_t<maybe<Reference_t*>>&              Beds();
        template <typename T>
        maybe<Reference_t*>                         Bed(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Bed(some<Settler_ID_t> valid_settler_id, maybe<Reference_t*> bed);

    public:
        void    Bool(some<Package_t*> package,
                     Settler_Value_Index_e index,
                     Bool_t value,
                     Bool_t& do_reset_ai);
        void    Flag_General(some<Package_t*> package,
                             Package_Flags_e general_flag,
                             Bool_t value,
                             Bool_t& do_reset_ai);
        void    Flag_Interrupt(some<Package_t*> package,
                               Package_Interrupt_Flags_e interrupt_flag,
                               Bool_t value,
                               Bool_t& do_reset_ai);
        void    Float(some<Package_t*> package,
                      Settler_Value_Index_e index,
                      Float_t value,
                      Bool_t& do_reset_ai);
        void    Location(some<Package_t*> package,
                         Settler_Value_Index_e index,
                         some<Reference_t*> marker,
                         some<Settler_Radius_t> radius,
                         Bool_t& do_reset_ai);
        void    Speed(some<Package_t*> package,
                      some<Settler_Speed_e> speed,
                      Bool_t& do_reset_ai);
        void    Schedule(some<Package_t*> package,
                         maybe<Settler_Time_t> time,
                         maybe<Settler_Duration_t> duration,
                         Bool_t& do_reset_ai);

        void    Enforce(some<Settler_ID_t> settler_id);

    public:
        void    Log(std::string indent = "");
    };

}}
