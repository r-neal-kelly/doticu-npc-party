/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcp { namespace Actor2 {

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

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_t* actor);
    float Get_Actor_Value(Actor *actor, const char *name);
    float Get_Base_Actor_Value(Actor *actor, const char *name);
    float Get_Max_Actor_Value(Actor *actor, const char *name);
    void Set_Actor_Value(Actor *actor, const char *name, float value);
    void Reset_Actor_Value(Actor *actor, const char *name);
    void Log_Actor_Values(Actor *actor);

    void Update_3D_Model(Actor_t* actor);
    void Fully_Update_3D_Model(Actor_t* actor);

    void Enable_Havok_Collision(Actor_t* actor);
    void Disable_Havok_Collision(Actor_t* actor);

    Bool_t Is_Moving(Actor_t* actor);
    Bool_t Has_Weapon_Sheathed(Actor_t* actor);
    Bool_t Has_Weapon_Drawn(Actor_t* actor);

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

    Voice_Type_t* Voice_Type(Actor_t* actor);

}}
