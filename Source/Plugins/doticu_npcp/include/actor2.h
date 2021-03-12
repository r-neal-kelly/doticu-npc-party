/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcp { namespace Actor2 {

    void Set_Outfit_Basic(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit = false, Bool_t allow_bcontainer = true);
    void Set_Outfit(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit = false);

    void Split_Inventory(Actor_t* actor, Reference_t* worn, Reference_t* pack);
    void Cache_Worn(Actor_t* actor, Reference_t* cache_out);

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b);

    Actor_t* Clone(Actor_t* actor, Reference_t* marker = nullptr);

}}
