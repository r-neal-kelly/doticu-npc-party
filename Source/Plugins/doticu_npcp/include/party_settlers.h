/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"
#include "party_settler.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Members_t;
    class Party;

    class Settlers_t
    {
    public:
        static constexpr size_t MAX_SETTLERS    = Consts_t::NPCP::Int::MAX_SETTLERS;

    public:
        class Save_t
        {
        public:
            Save_t();
            Save_t(const Save_t& other) = delete;
            Save_t(Save_t&& other) noexcept = delete;
            Save_t& operator =(const Save_t& other) = delete;
            Save_t& operator =(Save_t&& other) noexcept = delete;
            ~Save_t();

        public:
            void    Write(std::ofstream& file);
            void    Read(std::ifstream& file);
        };

        class State_t
        {
        public:
            Save_t      save;

            Settler_t   settlers[MAX_SETTLERS];

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        static Party_t&     Party();
        static Members_t&   Members();

    public:
        State_t state;

    public:
        Settlers_t();
        Settlers_t(const Settlers_t& other) = delete;
        Settlers_t(Settlers_t&& other) noexcept = delete;
        Settlers_t& operator =(const Settlers_t& other) = delete;
        Settlers_t& operator =(Settlers_t&& other) noexcept = delete;
        ~Settlers_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        State_t&    State();
        Save_t&     Save();

    public:
        Settler_t&          Settler(some<Settler_ID_t> settler_id);

        maybe<Settler_t*>   Active_Settler(some<Member_ID_t> member_id);
    };

}}

    /*
    public:
        static constexpr size_t                                 MAX_SETTLERS                = Consts_t::NPCP::Int::MAX_SETTLERS;

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
        Main_t&             Main();
        Members_t&          Members();

        Bool_t              Has_Settler(some<Settler_ID_t> settler_id);
        Bool_t              Has_Settler(some<Member_ID_t> member_id);
        Bool_t              Has_Settler(some<Actor_t*> actor);

    public:
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
        Bool_t                                      Is_Currently_Enabled(some<Settler_ID_t> settler_id); // Is_Active, Is_Current

        template <typename T>
        Bool_t                                      Allow_Swimming(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Swimming(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Always_Sneak(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Always_Sneak(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Ignore_Combat(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Ignore_Combat(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Keep_Weapons_Drawn(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Keep_Weapons_Drawn(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Hide_Weapons(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Hide_Weapons(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Skip_Combat_Alert(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Skip_Combat_Alert(some<Settler_ID_t> valid_settler_id, Bool_t value);

        template <typename T>
        Bool_t                                      Allow_Hellos_To_Player(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Hellos_To_Player(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Hellos_To_NPCs(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Hellos_To_NPCs(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Idle_Chatter(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Idle_Chatter(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Aggro_Radius(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Aggro_Radius(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_World_Interactions(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_World_Interactions(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Comment_On_Friendly_Fire(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Comment_On_Friendly_Fire(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Inspect_Corpses(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Inspect_Corpses(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Observe_Combat(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Observe_Combat(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      React_To_Player_Actions(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        React_To_Player_Actions(some<Settler_ID_t> valid_settler_id, Bool_t value);

        template <typename T>
        Bool_t                                      Allow_Already_Held_Food(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Already_Held_Food(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Conversation(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Conversation(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Eating(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Eating(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Fake_Food(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Fake_Food(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Horse_Riding(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Horse_Riding(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Idle_Markers(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Idle_Markers(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Sitting(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Sitting(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Sleeping(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Sleeping(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Special_Furniture(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Special_Furniture(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Allow_Wandering(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Allow_Wandering(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Lock_Doors(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Lock_Doors(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Only_Preferred_Path(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Only_Preferred_Path(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Stop_Movement(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Stop_Movement(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Unlock_On_Arrival(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Unlock_On_Arrival(some<Settler_ID_t> valid_settler_id, Bool_t value);
        template <typename T>
        Bool_t                                      Warn_Before_Locking(some<Settler_ID_t> valid_settler_id);
        template <typename T>
        void                                        Warn_Before_Locking(some<Settler_ID_t> valid_settler_id, Bool_t value);

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
        void                                        Attention(some<Settler_ID_t> valid_settler_id,
                                                              some<Settler_Attention_t> attention);

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
        template <typename T>
        void                                        Bed(some<Settler_ID_t> valid_settler_id, some<Furniture_t*> bed);

        template <typename T>
        void                                        Default(some<Settler_ID_t> valid_settler_id);

        template <typename T>
        some<Settler_ID_t>                          Add(some<Member_ID_t> valid_member_id);
        template <typename T>
        Bool_t                                      Remove(some<Settler_ID_t> settler_id);

        Bool_t  Is_Sandboxer(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Sleeper(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Sitter(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Eater(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Guard(some<Member_ID_t> valid_member_id);

        Bool_t  Is_Active_Sandboxer(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Sleeper(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Sitter(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Eater(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Guard(some<Member_ID_t> valid_member_id);

    public:
        void    Bool(some<Package_t*> package,
                     Settler_Value_Index_e index,
                     Bool_t value,
                     Bool_t& do_reset_ai);
        void    Float(some<Package_t*> package,
                      Settler_Value_Index_e index,
                      Float_t value,
                      Bool_t& do_reset_ai);
        void    General_Flag(some<Package_t*> package,
                             Package_Flags_e general_flag,
                             Bool_t value,
                             Bool_t& do_reset_ai);
        void    Interrupt_Flag(some<Package_t*> package,
                               Package_Interrupt_Flags_e interrupt_flag,
                               Bool_t value,
                               Bool_t& do_reset_ai);
        void    Location(some<Package_t*> package,
                         Settler_Value_Index_e index,
                         some<Reference_t*> marker,
                         some<Settler_Radius_t> radius,
                         Bool_t& do_reset_ai);
        void    Schedule(some<Package_t*> package,
                         maybe<Settler_Time_t> time,
                         maybe<Settler_Duration_t> duration,
                         Bool_t& do_reset_ai);
        void    Speed(some<Package_t*> package,
                      some<Settler_Speed_e> speed,
                      Bool_t& do_reset_ai);

        template <typename F>
        void    Enforce_Package_General_Flags(some<Package_t*> package,
                                              Settler_Flags_e flags,
                                              Bool_t& do_reset_ai);
        template <typename F>
        void    Enforce_Package_Interrupt_Flags(some<Package_t*> package,
                                                Settler_Flags_e flags,
                                                Bool_t& do_reset_ai);
        template <typename T>
        void    Enforce_Package(some<Settler_ID_t> valid_settler_id,
                                Bool_t& do_reset_ai);
        void    Enforce(some<Settler_ID_t> settler_id);

    public:
        void    Log(std::string indent = "");
    */
