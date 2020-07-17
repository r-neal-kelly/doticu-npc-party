/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"
#include "papyrus.inl"

namespace doticu_npcp { namespace Party {

    using namespace Papyrus;

    class Aliases_t;
    class Members_t;
    class Followers_t;
    class Horses_t;

    class Alias_t;
    class Member_t;
    class Follower_t;
    class Horse_t;

    template <typename Type>
    struct Range_t {
        Type begin;
        Type end;
    };

    namespace Filter_Flags_1 {
        enum : UInt64 {
            IS_LOADED, IS_UNLOADED,
            IS_UNIQUE, IS_GENERIC,
            IS_ORIGINAL, IS_CLONE,
            IS_ALIVE, IS_DEAD,
            IS_MOBILE, IS_IMMOBILE,
            IS_SETTLER, ISNT_SETTLER,
            IS_THRALL, ISNT_THRALL,
            IS_PARALYZED, ISNT_PARALYZED,
            IS_MANNEQUIN, ISNT_MANNEQUIN,
            IS_REANIMATED, ISNT_REANIMATED,
            IS_FOLLOWER, ISNT_FOLLOWER,
            IS_SNEAK, ISNT_SNEAK,
            IS_SADDLER, ISNT_SADDLER,
            IS_RETREATER, ISNT_RETREATER,
        };
    }

    namespace Filter_Flags_2 {
        enum : UInt64 {
            // if we hit 32 indices in the first one
        };
    }

    // I want to update these before going out of beta
    namespace Style_e {
        enum : Int_t {
            DEFAULT = -380,
            WARRIOR = -381,
            MAGE = -382,
            ARCHER = -383,
            COWARD = -384
        };
    }

    // I would like to change these numbers before going out of beta.
    namespace Vitality_e {
        enum : Int_t {
            MORTAL = -303,
            PROTECTED = -304,
            ESSENTIAL = -305,
            INVULNERABLE = -306
        };
    }

    class Aliases_t : public Quest_t {
    public:
        template <typename Alias>
        static int Compare_Names(const void* item_a,
                                 const void* item_b);
        template <typename Alias>
        static int Compare_Names_Caseless(const void* item_a,
                                          const void* item_b);
        template <typename Alias>
        static int Compare_Ratings_Names(const void* item_a,
                                         const void* item_b);
        template <typename Alias>
        static int Compare_Ratings_Names_Caseless(const void* item_a,
                                                  const void* item_b);

    public:
        template <typename Alias>
        Range_t<Alias**> Aliases(UInt64 begin, UInt64 end);

        template <typename Alias>
        Alias* From_ID(Int_t unique_id);
        template <typename Alias>
        Alias* From_Actor(Actor_t* actor);
        template <typename Alias>
        Alias* From_Unfilled(Range_t<Alias**> aliases);

        template <typename Alias>
        Int_t Count_If(Range_t<Alias**> aliases,
                       Bool_t(Alias::* Is)());
        template <typename Alias>
        Int_t Count_If(Range_t<Alias**> aliases,
                       Bool_t(Alias::* Is)(),
                       Bool_t(Alias::* Is_Also)());

        template <typename Alias>
        Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases,
                                 Bool_t(Alias::* Is)(),
                                 size_t reserve);
        template <typename Alias>
        Vector_t<Alias*> Copy_If(Range_t<Alias**> aliases,
                                 Bool_t(Alias::* Is)(),
                                 Bool_t(Alias::* Is_Also)(),
                                 size_t reserve);

        template <typename Alias>
        inline Vector_t<Alias*> Sort(Vector_t<Alias*> aliases,
                                     String_t algorithm);

        template <typename Alias>
        Vector_t<Alias*> Slice(Vector_t<Alias*> aliases, Int_t begin, Int_t end);

        template <typename Alias>
        Bool_t Has_Head(Range_t<Alias**> aliases, Actor_t* actor);
        template <typename Alias>
        Int_t Count_Heads(Range_t<Alias**> aliases, Actor_t* actor);

        Vector_t<String_t> Filter_Strings(String_t sex = "", String_t race = "", String_t search = "");
        Vector_t<Int_t> Filter_Ints(Int_t style = 0, Int_t vitality = 0, Int_t outfit2 = 0, Int_t rating = -1);
        Int_t Add_Filter_Flag_1(Int_t flags_1, String_t flag_1);
        Int_t Add_Filter_Flag_2(Int_t flags_2, String_t flag_2);
        template <typename Alias>
        Vector_t<Alias*> Filter(Range_t<Alias**> aliases,
                                Vector_t<String_t>* strings = nullptr,
                                Vector_t<Int_t>* ints = nullptr,
                                Int_t flags_1 = 0,
                                Int_t flags_2 = 0);
    };

    class Members_t : public Aliases_t {
    public:
        static constexpr size_t MAX = 1024;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = 0;
        static constexpr size_t END = BEGIN + MAX;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Members_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Range_t<UInt64> Indices();
        Range_t<Member_t**> Aliases();

        Member_t* From_ID(Int_t unique_id);
        Member_t* From_Actor(Actor_t* actor);
        Member_t* From_Unfilled();

        Bool_t Has_Space();
        Bool_t Hasnt_Space();
        Bool_t Has_Actor(Actor_t* actor);
        Bool_t Hasnt_Actor(Actor_t* actor);
        Bool_t Has_Head(Actor_t* actor);
        Bool_t Hasnt_Head(Actor_t* actor);

        Int_t Max();
        Int_t Count_Filled();
        Int_t Count_Unfilled();
        Int_t Count_Loaded();
        Int_t Count_Unloaded();
        Int_t Count_Unique();
        Int_t Count_Generic();
        Int_t Count_Alive();
        Int_t Count_Dead();
        Int_t Count_Originals();
        Int_t Count_Clones();
        Int_t Count_Mobile();
        Int_t Count_Immobile();
        Int_t Count_Settlers();
        Int_t Count_Non_Settlers();
        Int_t Count_Thralls();
        Int_t Count_Non_Thralls();
        Int_t Count_Paralyzed();
        Int_t Count_Non_Paralyzed();
        Int_t Count_Mannequins();
        Int_t Count_Non_Mannequins();
        Int_t Count_Reanimated();
        Int_t Count_Non_Reanimated();
        Int_t Count_Followers();
        Int_t Count_Non_Followers();
        Int_t Count_Sneaks();
        Int_t Count_Non_Sneaks();
        Int_t Count_Saddlers();
        Int_t Count_Non_Saddlers();
        Int_t Count_Retreaters();
        Int_t Count_Non_Retreaters();
        Int_t Count_Heads(Actor_t* actor);

        Vector_t<Member_t*> All();
        Vector_t<Member_t*> Filled();
        Vector_t<Member_t*> Unfilled();
        Vector_t<Member_t*> Loaded();
        Vector_t<Member_t*> Unloaded();

        Vector_t<Member_t*> Sort(Vector_t<Member_t*> members);
        Vector_t<Member_t*> Sort_Filled(Int_t begin = 0, Int_t end = -1);

        Vector_t<String_t> Race_Names();

        void Enforce_Loaded();

        Vector_t<Member_t*> Filter(Vector_t<String_t>* strings = nullptr,
                                   Vector_t<Int_t>* ints = nullptr,
                                   Int_t flags_1 = 0,
                                   Int_t flags_2 = 0);

        // now we could queue up calls to doticu_npcp_member.
        // but as much as possible, I want this behavior to be done
        // here, and as little state as possible saved in scripts.
        void Start_Display();
        void Next_Display();
        void Prev_Display();
        void Stop_Display();
    };

    class Followers_t : public Aliases_t {
    public:
        static constexpr size_t MAX = 16;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = 0;
        static constexpr size_t END = BEGIN + MAX;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Followers_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Range_t<UInt64> Indices();
        Range_t<Follower_t**> Aliases();

        Follower_t* From_ID(Int_t unique_id);
        Follower_t* From_Actor(Actor_t* actor);
        Follower_t* From_Unfilled();
        Follower_t* From_Horse_Actor(Actor_t* actor);

        Form_t* Tasklist();

        Bool_t Has_Space();
        Bool_t Hasnt_Space();
        Bool_t Has_Actor(Actor_t* actor);
        Bool_t Hasnt_Actor(Actor_t* actor);
        Bool_t Are_In_Combat();

        Int_t Max();
        Int_t Count_Filled();
        Int_t Count_Unfilled();
        Int_t Count_Loaded();
        Int_t Count_Unloaded();
        Int_t Count_Unique();
        Int_t Count_Generic();
        Int_t Count_Alive();
        Int_t Count_Dead();
        Int_t Count_Originals();
        Int_t Count_Clones();
        Int_t Count_Mobile();
        Int_t Count_Immobile();
        Int_t Count_Settlers();
        Int_t Count_Non_Settlers();
        Int_t Count_Thralls();
        Int_t Count_Non_Thralls();
        Int_t Count_Paralyzed();
        Int_t Count_Non_Paralyzed();
        Int_t Count_Mannequins();
        Int_t Count_Non_Mannequins();
        Int_t Count_Reanimated();
        Int_t Count_Non_Reanimated();
        Int_t Count_Followers();
        Int_t Count_Non_Followers();
        Int_t Count_Sneaks();
        Int_t Count_Non_Sneaks();
        Int_t Count_Saddlers();
        Int_t Count_Non_Saddlers();
        Int_t Count_Retreaters();
        Int_t Count_Non_Retreaters();

        Vector_t<Follower_t*> All();
        Vector_t<Follower_t*> Filled();
        Vector_t<Follower_t*> Unfilled();
        Vector_t<Follower_t*> Loaded();
        Vector_t<Follower_t*> Unloaded();
        Vector_t<Follower_t*> Unique();
        Vector_t<Follower_t*> Generic();
        Vector_t<Follower_t*> Alive();
        Vector_t<Follower_t*> Dead();
        Vector_t<Follower_t*> Originals();
        Vector_t<Follower_t*> Clones();
        Vector_t<Follower_t*> Mobile();
        Vector_t<Follower_t*> Immobile();
        Vector_t<Follower_t*> Settlers();
        Vector_t<Follower_t*> Non_Settlers();
        Vector_t<Follower_t*> Thralls();
        Vector_t<Follower_t*> Non_Thralls();
        Vector_t<Follower_t*> Paralyzed();
        Vector_t<Follower_t*> Non_Paralyzed();
        Vector_t<Follower_t*> Mannequins();
        Vector_t<Follower_t*> Non_Mannequins();
        Vector_t<Follower_t*> Reanimated();
        Vector_t<Follower_t*> Non_Reanimated();
        Vector_t<Follower_t*> Followers();
        Vector_t<Follower_t*> Non_Followers();
        Vector_t<Follower_t*> Sneaks();
        Vector_t<Follower_t*> Non_Sneaks();
        Vector_t<Follower_t*> Saddlers();
        Vector_t<Follower_t*> Non_Saddlers();
        Vector_t<Follower_t*> Retreaters();
        Vector_t<Follower_t*> Non_Retreaters();

        Vector_t<Follower_t*> Sort(Vector_t<Follower_t*> members);
        Vector_t<Follower_t*> Sort_Filled(Int_t begin = 0, Int_t end = -1);

        void Send(Vector_t<Follower_t*> followers, String_t event_name);
        void Send(Vector_t<Follower_t*> followers, String_t event_name, Form_t* form_arg);
        void Register();
        void Enforce();
        void Resurrect();
        void Mobilize();
        void Immobilize();
        void Settle();
        void Unsettle();
        void Enthrall();
        void Unthrall();
        void Paralyze();
        void Unparalyze();
        void Sneak();
        void Unsneak();
        void Saddle();
        void Unsaddle();
        void Retreat();
        void Unretreat();
        void Unfollow();
        void Unmember();

        void Summon(Vector_t<Follower_t*> followers, float radius = 140.0, float degree = 0.0, float interval = 19.0);
        void Summon_Filled(float radius = 140.0, float degree = 0.0, float interval = 19.0);
        void Summon_Mobile(float radius = 140.0, float degree = 0.0, float interval = 19.0);
        void Summon_Immobile(float radius = 140.0, float degree = 0.0, float interval = 19.0);

        void Catch_Up();
        void Stash();

        Vector_t<Follower_t*> Filter(Vector_t<String_t>* strings = nullptr,
                                     Vector_t<Int_t>* ints = nullptr,
                                     Int_t flags_1 = 0,
                                     Int_t flags_2 = 0);
    };

    class Horses_t : public Aliases_t {
    public:
        static constexpr size_t MAX = 16;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = Followers_t::END;
        static constexpr size_t END = BEGIN + MAX;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Horses_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Range_t<UInt64> Indices();
        Range_t<Horse_t**> Aliases();

        Horse_t* From_ID(Int_t unique_id);
        Horse_t* From_Actor(Actor_t* actor);
    };

    class Alias_t : public Alias_Base_t {
    public:

    public:
        Int_t ID();
    };

    class Member_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);
        Variable_t* Is_Immobile_Variable();
        Variable_t* Is_Settler_Variable();
        Variable_t* Is_Thrall_Variable();
        Variable_t* Is_Paralyzed_Variable();

        Actor_t* Actor();
        Follower_t* Follower();

        Reference_t* Pack();
        Reference_t* Settler_Marker();
        Cell_t* Cell();
        Int_t Style();
        Int_t Vitality();
        Int_t Outfit2();
        Int_t Rating();
        String_t Sex();
        String_t Race();
        String_t Base_Name();
        String_t Reference_Name();
        String_t Name();

        Bool_t Is_Filled();
        Bool_t Is_Unfilled();
        Bool_t Is_Loaded();
        Bool_t Is_Unloaded();
        Bool_t Is_Created();
        Bool_t Is_Destroyed();
        Bool_t Is_Unique();
        Bool_t Is_Generic();
        Bool_t Is_Original();
        Bool_t Is_Clone();
        Bool_t Is_Alive();
        Bool_t Is_Dead();
        Bool_t Is_Mobile();
        Bool_t Is_Immobile();
        Bool_t Is_Settler();
        Bool_t Isnt_Settler();
        Bool_t Is_Thrall();
        Bool_t Isnt_Thrall();
        Bool_t Is_Paralyzed();
        Bool_t Isnt_Paralyzed();
        Bool_t Is_Mannequin();
        Bool_t Isnt_Mannequin();
        Bool_t Is_Reanimated();
        Bool_t Isnt_Reanimated();
        Bool_t Is_Follower();
        Bool_t Isnt_Follower();
        Bool_t Is_Sneak();
        Bool_t Isnt_Sneak();
        Bool_t Is_Saddler();
        Bool_t Isnt_Saddler();
        Bool_t Is_Retreater();
        Bool_t Isnt_Retreater();

        Bool_t Has_Same_Head(Actor_t* actor);

        void On_Hit(Reference_t* attacker,
                    Form_t* tool,
                    Projectile_Base_t* projectile,
                    Bool_t is_power,
                    Bool_t is_sneak,
                    Bool_t is_bash,
                    Bool_t is_blocked);

        bool Has_Token(Misc_t* token, Int_t count = 1);
        void Token(Misc_t* token, Int_t count = 1);
        void Untoken(Misc_t* token);

        void Member();
        void Unmember();
        void Mobilize();
        void Immobilize();
        void Settle();
        void Unsettle();
        void Enthrall();
        void Unthrall();
        void Paralyze();
        void Unparalyze();
        void Mannequinize();
        void Unmannequinize();
        void Stylize();
        void Unstylize();
        void Vitalize();
        void Unvitalize();

        void Log_Variable_Infos();
    };

    class Follower_t : public Alias_t {
    public:
        static constexpr Float_t MAX_SNEAK_SPEED = 160.0f;
        static constexpr Float_t MAX_UNSNEAK_SPEED = 130.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Actor_t* Actor();
        Member_t* Member();
        Horse_t* Horse();
        
        Reference_t* Pack();
        Cell_t* Cell();
        Int_t Style();
        Int_t Vitality();
        Int_t Outfit2();
        Int_t Rating();
        String_t Sex();
        String_t Race();
        String_t Base_Name();
        String_t Reference_Name();
        String_t Name();

        Bool_t Is_Filled();
        Bool_t Is_Unfilled();
        Bool_t Is_Loaded();
        Bool_t Is_Unloaded();
        Bool_t Is_Created();
        Bool_t Is_Destroyed();
        Bool_t Is_Unique();
        Bool_t Is_Generic();
        Bool_t Is_Original();
        Bool_t Is_Clone();
        Bool_t Is_Alive();
        Bool_t Is_Dead();
        Bool_t Is_Mobile();
        Bool_t Is_Immobile();
        Bool_t Is_Settler();
        Bool_t Isnt_Settler();
        Bool_t Is_Thrall();
        Bool_t Isnt_Thrall();
        Bool_t Is_Paralyzed();
        Bool_t Isnt_Paralyzed();
        Bool_t Is_Mannequin();
        Bool_t Isnt_Mannequin();
        Bool_t Is_Reanimated();
        Bool_t Isnt_Reanimated();
        Bool_t Is_Follower();
        Bool_t Isnt_Follower();
        Bool_t Is_Sneak();
        Bool_t Isnt_Sneak();
        Bool_t Is_Saddler();
        Bool_t Isnt_Saddler();
        Bool_t Is_Retreater();
        Bool_t Isnt_Retreater();
        Bool_t Is_Near_Player(float radius = 4096.0f);
        Bool_t Isnt_Near_Player(float radius = 4096.0f);
        Bool_t Is_In_Interior_Cell();
        Bool_t Is_In_Exterior_Cell();

        bool Has_Token(Misc_t* token, Int_t count = 1);
        void Token(Misc_t* token, Int_t count = 1);
        void Untoken(Misc_t* token);

        void Summon(float radius = 140.0f, float degree = 0.0);
        void Summon_Ahead(float radius = 140.0f);
        void Summon_Behind(float radius = 140.0f);

        void Mobilize();
        void Immobilize();
        void Settle();
        void Unsettle();
        void Enthrall();
        void Unthrall();
        void Paralyze();
        void Unparalyze();

        void Catch_Up();
        void Saddle();
        void Level();
        void Unlevel();
        void Sneak();
        void Unsneak();
    };

    class Horse_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Actor_t* Actor();
        Follower_t* Follower();
    };

}}

namespace doticu_npcp { namespace Party { namespace Aliases { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Followers { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Horses { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Alias { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Member { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Follower { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

namespace doticu_npcp { namespace Party { namespace Horse { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}

#include "party.inl"
