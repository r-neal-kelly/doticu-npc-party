/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "offsets.h"
#include "types.h"
#include "papyrus.h"
#include "object_ref.h"

namespace doticu_npcp { namespace Actor2 {

    using namespace Object_Ref;
    using namespace Papyrus;

    const char *Get_Base_Name(Actor *actor);
    const char *Get_Ref_Name(Actor *actor);
    const char *Get_Name(Actor *actor);

    Outfit_t* Base_Outfit(Actor_t* actor);
    void Base_Outfit(Actor_t* actor, Outfit_t* outfit);
    void Base_Sleep_Outfit(Actor_t* actor, Outfit_t* outfit);
    void Set_Outfit_Basic(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit = false, Bool_t allow_bcontainer = true);
    void Set_Outfit(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit = false);

    class Outfit_Entry_t {
    public:
        Form_t* form = nullptr;
        Merged_XLists_t merged_xlists;
        XList_t* loose_xlist = nullptr;

        Outfit_Entry_t(Entry_t* outfit1 = nullptr, Entry_t* outfit2 = nullptr, Int_t loose_count = 0);

        XList_t* Copy(Merged_XList_t* outfit_xlist, Actor_Base_t* owner);
        Int_t Count();
        Bool_t Is_Worn();
        void Cleanup();
    };

    class Outfit_Inventory_t {
    public:
        static Bool_t Can_Evaluate_Form(Form_t* form);
    public:
        Inventory_t outfit1;
        Inventory_t outfit2;
        Vector_t<Outfit_Entry_t> entries;

        Outfit_Inventory_t(Reference_t* outfit1_ref, Reference_t* outfit2_ref);

        Outfit_Entry_t* Entry(Form_t* form);

        Bool_t Evaluate_Linchpin(Inventory_t* actor);
        Int_t Evaluate_Existing(Inventory_t* actor, Inventory_t* transfer);
        Bool_t Evaluate_Missing(Inventory_t* actor);

        void Cleanup();
        void Log(std::string indent = "");
    };

    Bool_t Set_Outfit2(Actor_t* actor, Reference_t* outfit1 = nullptr, Reference_t* outfit2 = nullptr, Reference_t* transfer = nullptr);
    void Split_Inventory(Actor_t* actor, Reference_t* worn, Reference_t* pack);
    void Cache_Worn(Actor_t* actor, Reference_t* cache_out);
    void Cache_BContainer(Actor_t* actor, Reference_t* cache_out);

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b);

    bool Is_Alive(Actor *actor);
    bool Is_Dead(Actor *actor);
    bool Is_Loaded(Actor_t *actor);
    bool Is_Unloaded(Actor_t* actor);
    bool Is_Unique(Actor_t* actor);
    bool Is_Generic(Actor_t* actor);
    bool Is_Aliased_In_Quest(Actor *actor, TESQuest *quest);
    Bool_t Is_Vampire(Actor_t* actor);

    void Move_To_Orbit(Actor* actor, Reference_t* origin, float radius, float degree);

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_t* actor);
    float Get_Actor_Value(Actor *actor, const char *name);
    float Get_Base_Actor_Value(Actor *actor, const char *name);
    float Get_Max_Actor_Value(Actor *actor, const char *name);
    void Set_Actor_Value(Actor *actor, const char *name, float value);
    void Reset_Actor_Value(Actor *actor, const char *name);
    void Log_Actor_Values(Actor *actor);

    Actor_t* Get_Mount(Actor_t* mounter);
    Actor_t* Get_Mounted_Actor(Actor_t* horse);
    bool Is_On_Mount(Actor_t* actor);

    Int_t Sex(Actor_t* actor);
    String_t Sex_String(Actor_t* actor);
    String_t Race(Actor_t* actor);

    void Evaluate_Package(Actor_t* actor, bool unk_01 = false, bool unk_02 = false);
    void Update_3D_Model(Actor_t* actor);
    void Fully_Update_3D_Model(Actor_t* actor);
    void Queue_Ni_Node_Update(Actor_t* actor, bool do_update_weight = false);
    
    XFactions_t* XFactions(Actor_t* actor, bool do_create = false);
    BFaction_Ranks_t* BFaction_Ranks(Actor_t* actor);
    XFaction_Ranks_t* XFaction_Ranks(Actor_t* actor, bool do_create = false);
    
    struct Factions_And_Ranks_t {
        Vector_t<Faction_t*> factions;
        Vector_t<Int_t> ranks;
    };

    Bool_t Has_Faction(Actor_t* actor, Faction_t* faction);
    Bool_t Has_Faction_Rank(Actor_t* actor, Faction_t* faction, Int_t rank);
    void Add_Faction(Actor_t* actor, Faction_t* faction, Int_t rank = 0);
    void Remove_Faction(Actor_t* actor, Faction_t* faction);
    void Add_Crime_Faction(Actor_t* actor, Faction_t* crime_faction);
    void Remove_Crime_Faction(Actor_t* actor);
    void Log_Factions(Actor_t* actor);
    void Factions_And_Ranks(Actor_t* actor, Factions_And_Ranks_t& results, Int_t min_rank = -128, Int_t max_rank = 127);
    Faction_t* Crime_Faction(Actor_t* actor);

    void Join_Player_Team(Actor_t* actor, Bool_t allow_favors = true);
    void Leave_Player_Team(Actor_t* actor);
    Bool_t Is_Player_Teammate(Actor_t* actor);
    void Talks_To_Player(Actor_t* actor, Bool_t can_talk);
    Bool_t Can_Talk_To_Player(Actor_t* actor);
    Bool_t Cant_Talk_To_Player(Actor_t* actor);
    Bool_t Race_Can_Talk_To_Player(Actor_t* actor);
    Bool_t Race_Cant_Talk_To_Player(Actor_t* actor);

    Bool_t Is_AI_Enabled(Actor_t* actor);
    void Enable_AI(Actor_t* actor);
    void Disable_AI(Actor_t* actor);
    void Reset_AI(Actor_t* actor, Virtual_Callback_i* vcallback = nullptr);
    
    Bool_t Is_Ghost(Actor_t* actor);
    void Ghostify(Actor_t* actor);
    void Unghostify(Actor_t* actor);
    void Set_Ghost(Actor_t* actor, Bool_t is_ghost, Virtual_Callback_i* vcallback = nullptr);

    void Enable_Havok_Collision(Actor_t* actor);
    void Disable_Havok_Collision(Actor_t* actor);

    void Ignore_Friendly_Hits(Actor_t* actor);
    void Notice_Friendly_Hits(Actor_t* actor);
    void Show_On_Stealth_Eye(Actor_t* actor);
    void Hide_From_Stealth_Eye(Actor_t* actor);

    void Stop_Movement(Actor_t* actor);

    Actor_Base_t* Dynamic_Base(Actor_t* actor);
    Actor_Base_t* Real_Base(Actor_t* actor);

    void Stop_Combat(Actor_t* actor);
    void Stop_Combat_Alarm(Actor_t* actor);
    void Pacify(Actor_t* actor);
    void Kill(Actor_t* actor, Actor_t* killer = nullptr, Float_t damage = 0.0f, Bool_t do_send_event = true, Bool_t do_quick_ragdoll = false);

    Actor_t* Clone(Actor_t* actor, Reference_t* marker = nullptr);
    void Resurrect(Actor_t* actor, Bool_t do_reset_inventory = false);
    Bool_t Try_Resurrect(Actor_t* actor, Bool_t do_reset_inventory = false);

    Bool_t Is_Child(Actor_t* actor);
    Bool_t Isnt_Child(Actor_t* actor);

    void Update_Equipment(Actor_t* actor, Callback_t<Actor_t*>* user_callback = nullptr);

    void Stop_If_Playing_Music(Actor_t* actor);

    Relationship_t::Rank_e Relationship_Rank(Actor_t* actor, Actor_t* other);
    void Relationship_Rank(Actor_t* actor, Actor_t* other, Relationship_t::Rank_e rank);

    Bool_t Has_Magic_Effect(Actor_t* actor, Magic_Effect_t* magic_effect);

    Bool_t Add_Spell(Actor_t* actor, Spell_t* spell);
    void Add_Spell(Actor_t* actor, Spell_t* spell, Bool_t be_verbose, Virtual_Callback_i** callback = nullptr);
    void Remove_Spell(Actor_t* actor, Spell_t* spell, Virtual_Callback_i** callback = nullptr);

    Bool_t Is_Sneaking(Actor_t* actor);
    void Is_Talking_To_Player(Actor_t* actor, Virtual_Callback_i** callback);

    void Owner(Actor_t* actor, Actor_Base_t* owner); // maybe we could try the reference instead of base, for horses

    void Send_Animation_Event(Actor_t* actor, String_t animation, Virtual_Callback_i** callback = nullptr);

    void Set_Doing_Favor(Actor_t* actor, Bool_t is, Virtual_Callback_i* vcallback = nullptr);

    void Set_Alpha(Actor_t* actor, Float_t alpha_0_to_1, Bool_t do_fade_in = false, Virtual_Callback_i* vcallback = nullptr);

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
