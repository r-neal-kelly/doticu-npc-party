/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "form_vector.h"
#include "outfit2.h"
#include "papyrus.h"
#include "papyrus.inl"

namespace doticu_npcp { namespace Party {

    using namespace Papyrus;

    class NPCS_t;

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

    class NPCS_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static NPCS_t* Self();
    public:
        void Initialize();
        void Uninitialize();

        Object_t* Object();
        Variable_t* Variable(String_t variable_name);
        Variable_t* Bases_Variable();
        Variable_t* Default_Outfits_Variable();

        Form_Vector_t* Bases();
        Form_Vector_t* Default_Outfits();

        Actor_Base_t* Base(Actor_t* actor);
        Int_t Base_Idx(Actor_t* actor);
        Outfit_t* Default_Outfit(Int_t base_idx);

        Bool_t Has_Base(Actor_t* actor);

        Int_t Add_Base_If_Needed(Actor_t* actor_with_base, Actor_t* actor_with_outfit);
        void Remove_Base_If_Needed(Int_t base_idx);
        void Add_Original(Actor_t* original);
        void Remove_Original(Actor_t* original);
        Actor_t* Add_Clone(Actor_t* original);
        void Remove_Clone(Actor_t* clone, Bool_t do_delete_clone);

        Outfit_t* Default_Outfit(Actor_t* actor);
        void Change_Default_Outfit(Actor_t* actor, Outfit_t* default_outfit);

        void Remove_All_Tokens(Actor_t* actor);

        void u_0_9_3();
    public:
        static void Register_Me(Registry_t* registry);
    };

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
        Bool_t Has_Base(Range_t<Alias**> aliases, Actor_t* actor_with_base);
        template <typename Alias>
        Bool_t Has_Head(Range_t<Alias**> aliases, Actor_t* actor);
        template <typename Alias>
        Int_t Count_Base(Range_t<Alias**> aliases, Actor_t* actor_with_base);
        template <typename Alias>
        Int_t Count_Heads(Range_t<Alias**> aliases, Actor_t* actor);

        Vector_t<String_t> Filter_Strings(String_t sex = "",
                                          String_t race = "",
                                          String_t search = "");
        Vector_t<Int_t> Filter_Ints(Int_t style = 0,
                                    Int_t vitality = 0,
                                    Int_t outfit2 = 0,
                                    Int_t rating = -1);
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
        static constexpr size_t MAX = Consts::MAX_MEMBERS;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = 0;
        static constexpr size_t END = BEGIN + MAX;

        static constexpr float DEFAULT_DISPLAY_RADIUS = 140.0f;
        static constexpr float DEFAULT_DISPLAY_DEGREE = 0.0f;
        static constexpr float DEFAULT_DISPLAY_INTERVAL = 24.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Members_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);
        Variable_t* Has_Display_Variable();
        Variable_t* Display_Idx_Variable();
        Variable_t* Display_Marker_Variable();

        Range_t<UInt64> Indices();
        Range_t<Member_t**> Aliases();
        Reference_t* Display_Marker();

        Member_t* From_ID(Int_t unique_id);
        Member_t* From_Actor(Actor_t* actor);
        Member_t* From_Unfilled();

        Bool_t Has_Space();
        Bool_t Hasnt_Space();
        Bool_t Has_Actor(Actor_t* actor);
        Bool_t Hasnt_Actor(Actor_t* actor);
        Bool_t Has_Base(Actor_t* actor_with_base);
        Bool_t Hasnt_Base(Actor_t* actor_with_base);
        Bool_t Has_Head(Actor_t* actor);
        Bool_t Hasnt_Head(Actor_t* actor);
        Bool_t Has_Display();
        Bool_t Hasnt_Display();

        Bool_t Should_Clone(Actor_t* actor);
        Bool_t Should_Unclone(Actor_t* actor);

        Int_t Max();
        Int_t Limit();
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
        Int_t Count_Base(Actor_t* actor_with_base);
        Int_t Count_Heads(Actor_t* actor);

        Vector_t<Member_t*> All();
        Vector_t<Member_t*> Filled();
        Vector_t<Member_t*> Unfilled();
        Vector_t<Member_t*> Loaded();
        Vector_t<Member_t*> Unloaded();
        Vector_t<Member_t*> Displayed();
        Vector_t<Member_t*> Undisplayed();

        Vector_t<Member_t*> Sort(Vector_t<Member_t*> members);
        Vector_t<Member_t*> Sort_Filled(Int_t begin = 0, Int_t end = -1);

        Vector_t<String_t> Race_Names();

        void Enforce_Loaded(Bool_t do_resurrect = false);

        Vector_t<Member_t*> Filter(Vector_t<String_t>* strings = nullptr,
                                   Vector_t<Int_t>* ints = nullptr,
                                   Int_t flags_1 = 0,
                                   Int_t flags_2 = 0);

        Vector_t<Member_t*> Current_Filter();

        Int_t Display_Start();
        Int_t Display_Stop();
        Int_t Display_Next();
        Int_t Display_Previous();
        void Display(Vector_t<Member_t*> filter,
                     Int_t begin,
                     Int_t count,
                     Reference_t* origin,
                     float radius = DEFAULT_DISPLAY_RADIUS,
                     float degree = DEFAULT_DISPLAY_DEGREE,
                     float interval = DEFAULT_DISPLAY_INTERVAL);
        void Undisplay();

        Int_t Add_Original(Actor_t* original);
        Int_t Remove_Original(Actor_t* original);
        Int_t Add_Clone(Actor_t* original);
        Int_t Remove_Clone(Actor_t* clone, Bool_t do_delete_clone);

        void Delete_Unused_Outfit2s();

        void u_0_9_3();
    };

    namespace Members { namespace Exports {

        Bool_t Register(Registry_t* registry);

    }}

    class Followers_t : public Aliases_t {
    public:
        static constexpr size_t MAX = Consts::MAX_FOLLOWERS;
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

        Int_t Add_Follower(Member_t* member);
        Int_t Remove_Follower(Member_t* member, Virtual_Callback_i** callback);

        Int_t Enforce();
        Int_t Resurrect();
        Int_t Mobilize();
        Int_t Immobilize();
        Int_t Settle();
        Int_t Resettle();
        Int_t Unsettle();
        Int_t Enthrall();
        Int_t Unthrall();
        Int_t Paralyze();
        Int_t Unparalyze();
        Int_t Sneak();
        Int_t Unsneak();
        Int_t Saddle();
        Int_t Unsaddle();
        Int_t Retreat();
        Int_t Unretreat();
        Int_t Unfollow();
        Int_t Unmember();

        void Summon(Vector_t<Follower_t*> followers, float radius = 140.0, float degree = 0.0, float interval = 19.0);
        Int_t Summon_Filled(float radius = 140.0, float degree = 0.0, float interval = 19.0);
        Int_t Summon_Mobile(float radius = 140.0, float degree = 0.0, float interval = 19.0);
        Int_t Summon_Immobile(float radius = 140.0, float degree = 0.0, float interval = 19.0);

        Int_t Catch_Up();
        Int_t Stash();

        Vector_t<Follower_t*> Filter(Vector_t<String_t>* strings = nullptr,
                                     Vector_t<Int_t>* ints = nullptr,
                                     Int_t flags_1 = 0,
                                     Int_t flags_2 = 0);
    };

    namespace Followers { namespace Exports {

        Bool_t Register(Registry_t* registry);

    }}

    class Horses_t : public Aliases_t {
    public:
        static constexpr size_t MAX = Consts::MAX_FOLLOWERS;
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

        Int_t Add_Horse(Follower_t* follower);
        Int_t Remove_Horse(Follower_t* follower);
    };

    namespace Horses { namespace Exports {

        Bool_t Register(Registry_t* registry);

    }}

    class Alias_t : public Alias_Base_t {
    public:

    public:
        Int_t ID();
        Actor_t* Actor();

        Bool_t Is_Filled();
        Bool_t Is_Unfilled();

        void Fill(Actor_t* actor, Virtual_Callback_i** callback);
        void Unfill(Virtual_Callback_i** callback);
    };

    class Member_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable();
        Variable_t* Pack_Variable();
        Variable_t* Mannequin_Marker_Variable();
        Variable_t* Display_Marker_Variable();
        Variable_t* Undisplay_Marker_Variable();
        Variable_t* Vanilla_Outfit_Variable();
        Variable_t* Default_Outfit_Variable();

        Variable_t* Member_Outfit2_Variable();
        Variable_t* Immobile_Outfit2_Variable();
        Variable_t* Settler_Outfit2_Variable();
        Variable_t* Thrall_Outfit2_Variable();
        Variable_t* Follower_Outfit2_Variable();
        Variable_t* Vanilla_Outfit2_Variable();
        Variable_t* Default_Outfit2_Variable();
        Variable_t* Current_Outfit2_Variable();
        Variable_t* Backup_Outfit2_Variable();
        
        Variable_t* Is_Clone_Variable();
        Variable_t* Is_Immobile_Variable();
        Variable_t* Is_Settler_Variable();
        Variable_t* Is_Thrall_Variable();
        Variable_t* Is_Paralyzed_Variable();
        Variable_t* Is_Mannequin_Variable();
        Variable_t* Is_Display_Variable();
        Variable_t* Is_Reanimated_Variable();

        Variable_t* Style_Variable();
        Variable_t* Vitality_Variable();
        Variable_t* Outfit2_Variable();
        Variable_t* Rating_Variable();

        Variable_t* Name_Variable();

        Variable_t* Previous_Factions_Variable();
        Variable_t* Previous_Crime_Faction_Variable();
        Variable_t* Previous_Potential_Follower_Faction_Variable();
        Variable_t* Previous_No_Body_Cleanup_Faction_Variable();
        Variable_t* Previous_Aggression_Variable();
        Variable_t* Previous_Confidence_Variable();
        Variable_t* Previous_Assistance_Variable();
        Variable_t* Previous_Morality_Variable();

        Actor_t* Actor();
        Follower_t* Follower();
        Reference_t* Pack();
        Reference_t* Settler_Marker();
        Reference_t* Mannequin_Marker();
        Reference_t* Display_Marker();
        Reference_t* Undisplay_Marker();
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
        String_t Rating_Stars();

        Outfit_t* Vanilla_Outfit();
        Outfit_t* Default_Outfit();
        Outfit2_t* Member_Outfit2();
        Outfit2_t* Immobile_Outfit2();
        Outfit2_t* Settler_Outfit2();
        Outfit2_t* Thrall_Outfit2();
        Outfit2_t* Follower_Outfit2();
        Outfit2_t* Vanilla_Outfit2();
        Outfit2_t* Default_Outfit2();
        Outfit2_t* Current_Outfit2();
        Outfit2_t* Backup_Outfit2();

        Bool_t Is_Ready();
        Bool_t Is_Unready();
        Bool_t Is_Loaded();
        Bool_t Is_Unloaded();
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
        Bool_t Is_Display();
        Bool_t Isnt_Display();
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

        Bool_t Is_Loaded_Unsafe();
        Bool_t Is_Unloaded_Unsafe();
        Bool_t Is_Unique_Unsafe();
        Bool_t Is_Generic_Unsafe();
        Bool_t Is_Original_Unsafe();
        Bool_t Is_Clone_Unsafe();
        Bool_t Is_Alive_Unsafe();
        Bool_t Is_Dead_Unsafe();
        Bool_t Is_Mobile_Unsafe();
        Bool_t Is_Immobile_Unsafe();
        Bool_t Is_Settler_Unsafe();
        Bool_t Isnt_Settler_Unsafe();
        Bool_t Is_Thrall_Unsafe();
        Bool_t Isnt_Thrall_Unsafe();
        Bool_t Is_Paralyzed_Unsafe();
        Bool_t Isnt_Paralyzed_Unsafe();
        Bool_t Is_Mannequin_Unsafe();
        Bool_t Isnt_Mannequin_Unsafe();
        Bool_t Is_Display_Unsafe();
        Bool_t Isnt_Display_Unsafe();
        Bool_t Is_Reanimated_Unsafe();
        Bool_t Isnt_Reanimated_Unsafe();
        Bool_t Is_Follower_Unsafe();
        Bool_t Isnt_Follower_Unsafe();
        Bool_t Is_Sneak_Unsafe();
        Bool_t Isnt_Sneak_Unsafe();
        Bool_t Is_Saddler_Unsafe();
        Bool_t Isnt_Saddler_Unsafe();
        Bool_t Is_Retreater_Unsafe();
        Bool_t Isnt_Retreater_Unsafe();

        Bool_t Has_Same_Base(Actor_t* other_actor);
        Bool_t Has_Same_Head(Actor_t* other_actor);

        Bool_t Has_Same_Base_Unsafe(Actor_t* other_actor);
        Bool_t Has_Same_Head_Unsafe(Actor_t* other_actor);

        Bool_t Should_Unclone();

        void On_Load();
        void On_Death(Actor_t* killer);
        void On_Activate(Reference_t* activator);
        void On_Combat_State_Changed(Actor_t* target, Int_t combat_code);
        void On_Hit(Reference_t* attacker,
                    Form_t* tool,
                    Projectile_Base_t* projectile,
                    Bool_t is_power,
                    Bool_t is_sneak,
                    Bool_t is_bash,
                    Bool_t is_blocked);

        void Fill(Actor_t* actor, Bool_t is_clone);
        void Unfill();
        void Create(Actor_t* actor, Bool_t is_clone);
        void Destroy();
        void Destroy_Containers();
        void Destroy_Outfit2s();
        void Backup_State(Actor_t* actor);
        void Restore_State(Actor_t* actor);

        void Enforce_Member(Actor_t* actor);
        void Destroy_Member(Actor_t* actor);
        void Enforce_Non_Member(Actor_t* actor);

        Int_t Mobilize();
        void Destroy_Immobile(Actor_t* actor);
        void Enforce_Mobile(Actor_t* actor);
        Int_t Immobilize();
        void Enforce_Immobile(Actor_t* actor);

        Int_t Settle();
        void Enforce_Settler(Actor_t* actor);
        Int_t Resettle();
        Int_t Unsettle();
        void Destroy_Settler(Actor_t* actor);
        void Enforce_Non_Settler(Actor_t* actor);

        Int_t Enthrall();
        void Enforce_Thrall(Actor_t* actor);
        Int_t Unthrall();
        void Destroy_Thrall(Actor_t* actor);
        void Enforce_Non_Thrall(Actor_t* actor);

        Int_t Paralyze();
        void Enforce_Paralyzed(Actor_t* actor);
        Int_t Unparalyze();
        void Destroy_Paralyzed(Actor_t* actor);
        void Enforce_Non_Paralyzed(Actor_t* actor);

        Int_t Mannequinize(Reference_t* marker = nullptr);
        void Enforce_Mannequin(Actor_t* actor, Reference_t* marker);
        Int_t Unmannequinize();
        void Destroy_Mannequin(Actor_t* actor);
        void Enforce_Non_Mannequin(Actor_t* actor);

        Int_t Display(Reference_t* origin, Float_t radius = 140.0f, Float_t degree = 0.0f);
        void Create_Display(Actor_t* actor, Reference_t* origin, Float_t radius, Float_t degree);
        void Enforce_Display(Actor_t* actor, Reference_t* display_marker);
        Int_t Undisplay();
        void Destroy_Display(Actor_t* actor);
        void Enforce_Non_Display(Actor_t* actor);

        Int_t Reanimate();
        void Enforce_Reanimated(Actor_t* actor);
        Int_t Deanimate();
        void Destroy_Reanimated(Actor_t* actor);
        void Enforce_Non_Reanimated(Actor_t* actor);

        Int_t Unmember();
        Int_t Clone();
        Int_t Unclone();

        Int_t Stylize(Int_t style);
        Int_t Stylize_Default();
        Int_t Stylize_Warrior();
        Int_t Stylize_Mage();
        Int_t Stylize_Archer();
        Int_t Stylize_Coward();
        void Enforce_Style(Actor_t* actor);
        void Enforce_Default_Style(Actor_t* actor);
        void Enforce_Warrior_Style(Actor_t* actor);
        void Enforce_Mage_Style(Actor_t* actor);
        void Enforce_Archer_Style(Actor_t* actor);
        void Enforce_Coward_Style(Actor_t* actor);
        Int_t Unstylize();

        Int_t Vitalize(Int_t vitality);
        Int_t Vitalize_Mortal();
        Int_t Vitalize_Protected();
        Int_t Vitalize_Essential();
        Int_t Vitalize_Invulnerable();
        void Enforce_Vitality(Actor_t* actor);
        void Enforce_Mortal_Vitality(Actor_t* actor);
        void Enforce_Protected_Vitality(Actor_t* actor);
        void Enforce_Essential_Vitality(Actor_t* actor);
        void Enforce_Invulnerable_Vitality(Actor_t* actor);
        Int_t Unvitalize();

        void Change_Outfit1(Outfit_t* outfit);
        Int_t Change_Outfit2(Int_t outfit2_code);
        Int_t Change_Member_Outfit2();
        Int_t Change_Immobile_Outfit2();
        Int_t Change_Settler_Outfit2();
        Int_t Change_Thrall_Outfit2();
        Int_t Change_Follower_Outfit2();
        Int_t Change_Vanilla_Outfit2();
        Int_t Change_Default_Outfit2();
        Int_t Change_Current_Outfit2();
        void Update_Outfit2(Int_t outfit2_code, Bool_t do_cache_outfit1 = false);
        void Open_Outfit2();
        void Enforce_Outfit2(Actor_t* actor);

        Int_t Rate(Int_t rating);

        Int_t Rename(String_t new_name);
        void Enforce_Name(Actor_t* actor, String_t name);

        void Enforce();

        void Summon(Reference_t* origin, Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon(Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon_Ahead(Float_t radius = 140.0f);
        Int_t Summon_Behind(Float_t radius = 140.0f);

        Int_t Open_Pack();
        Int_t Stash();
        Int_t Resurrect();
        Int_t Kill();
        void Enforce_Kill(Actor_t* actor);

        Int_t Follow();
        Int_t Unfollow();

        void Level();
    };

    namespace Member { namespace Exports {

        Bool_t Register(Registry_t* registry);

    }}

    class Follower_t : public Alias_t {
    public:
        static constexpr Float_t MAX_SNEAK_SPEED = 160.0f;
        static constexpr Float_t MAX_UNSNEAK_SPEED = 130.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable(); // Actor_t
        Variable_t* Member_Variable(); // Member_t
        Variable_t* Horse_Variable(); // Horse_t

        Variable_t* Is_Sneak_Variable(); // Bool_t
        Variable_t* Is_Saddler_Variable(); // Bool_t
        Variable_t* Is_Retreater_Variable(); // Bool_t

        Variable_t* Previous_Player_Relationship_Variable(); // Int_t
        Variable_t* Previous_Waiting_For_Player_Variable(); // Float_t
        Variable_t* Previous_Speed_Multiplier_Variable(); // Float_t
        Variable_t* Previous_No_Auto_Bard_Faction_Variable(); // Bool_t

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

        Bool_t Is_Loaded();
        Bool_t Is_Unloaded();
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
        Bool_t Is_Display();
        Bool_t Isnt_Display();
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
        Bool_t Is_In_Combat();
        Bool_t Isnt_In_Combat();

        bool Has_Token(Misc_t* token, Int_t count = 1);
        void Token(Misc_t* token, Int_t count = 1);
        void Untoken(Misc_t* token);

        void Fill(Member_t* member);
        void Unfill(Virtual_Callback_i** callback);
        void Create(Member_t* member);
        void Destroy();
        void Create_Horse();
        void Destroy_Horse();
        void Backup_State(Actor_t* actor);
        void Restore_State(Actor_t* actor);

        void Enforce_Follower(Actor_t* actor);
        void Enforce_Non_Follower(Actor_t* actor);
        void Level();
        void Unlevel();
        Int_t Sneak();
        void Enforce_Sneak(Actor_t* actor);
        Int_t Unsneak();
        void Enforce_Non_Sneak(Actor_t* actor);
        Int_t Saddle();
        void Enforce_Saddler(Actor_t* actor);
        Int_t Unsaddle();
        void Enforce_Non_Saddler(Actor_t* actor);
        Int_t Retreat();
        void Enforce_Retreater(Actor_t* actor);
        Int_t Unretreat();
        void Enforce_Non_Retreater(Actor_t* actor);

        void Enforce();

        void Summon(Reference_t* origin, Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon(Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon_Ahead(Float_t radius = 140.0f);
        Int_t Summon_Behind(Float_t radius = 140.0f);

        Int_t Mobilize();
        Int_t Immobilize();
        Int_t Settle();
        Int_t Resettle();
        Int_t Unsettle();
        Int_t Enthrall();
        Int_t Unthrall();
        Int_t Paralyze();
        Int_t Unparalyze();
        Int_t Stash();
        Int_t Resurrect();
        Int_t Kill();

        void Catch_Up();
        void Rename(String_t new_name);
    };

    namespace Follower { namespace Exports {

        Bool_t Register(Registry_t* registry);

    }}

    class Horse_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable();
        Variable_t* Follower_Variable();

        Actor_t* Actor();
        Follower_t* Follower();
        Cell_t* Cell();
        String_t Base_Name();
        String_t Reference_Name();
        String_t Name();

        Bool_t Is_Alive();
        Bool_t Is_Dead();

        void Fill(Actor_t* actor, Follower_t* follower);
        void Unfill(Virtual_Callback_i** callback);
        void Create(Actor_t* actor, Follower_t* follower);
        void Destroy();

        Int_t Groom();
        void Enforce_Groom(Actor_t* actor);
        Int_t Ungroom();
        void Enforce_Non_Groom(Actor_t* actor);

        void Enforce();

        void Rename(String_t new_name);
    };

    namespace Horse { namespace Exports {

        Bool_t Register(Registry_t* registry);

    }}

}}
