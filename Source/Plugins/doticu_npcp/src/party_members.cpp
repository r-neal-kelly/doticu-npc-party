/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    Members_t::State::State() :
        actors(Vector_t<maybe<Actor_t*>>(MAX_MEMBERS)),
        original_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),

        flags(Vector_t<Member_Flags_e>(MAX_MEMBERS)),

        names(Vector_t<String_t>(MAX_MEMBERS)),
        packs(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS)),
        voice_types(Vector_t<maybe<Voice_Type_t*>>(MAX_MEMBERS)),

        default_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS)),
        vanilla_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS)),
        member_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        immobile_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        settler_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        thrall_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        follower_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        vanilla_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        default_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        current_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        backup_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),

        ratings(Vector_t<Member_Rating_t>(MAX_MEMBERS)),
        relations(Vector_t<Relation_e>(MAX_MEMBERS)),
        styles(Vector_t<Member_Style_e>(MAX_MEMBERS)),
        vitalities(Vector_t<Vitality_e>(MAX_MEMBERS))
    {
    }

    Members_t::State::~State()
    {
    }

    void Members_t::State::Save()
    {
        // just save actor form_ids, but make sure to switch back to the original actor_base.
        // we can send an event to update them again after Save, or just do it on the clock.
        
        // just save strings directly
        
        // ratings -> Int_t

        // styles and vitalites should be stored as strings. maybe ratings too. put we unpack them into integers of course
    }

    void Members_t::State::Load()
    {
        // resolve actor form_ids and weed out void, invalid, and deleted ones.
        // when an invalid form_id is found, we need to clean up any allocated data, like Reference_t (e.g. packs)
        // if we do the base switch trick, then we need to clone the base and do everything that we need to to update it.
        // it's decided, I'm greenlighting actor base switches at this point, until we see a reason not to do it. we'll
        // do it dynamically. we should keep our outfitting system similar though, because it offers much more versatility.
        // however we need to add the option per member to enable/disable it. with custom bases, we can even change voice types.
        // so many traditionaly problems will just go away. don't forget, when cloning a member, we need to use their static base.
        // one potential problem is that if the user changes the base dynamically, there is no way for them to save the changes.
        // however, that's quite normal, it's come to be expected. however, we can save changes for them using our persistence model

        // load strings directly
        
        // ratings -> Member_Rating_t
    }

    Members_t::State Members_t::state = State();

    some<Members_t*> Members_t::Self()
    {
        return Consts_t::NPCP::Quest::Members();
    }

    String_t Members_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_members");
    }

    some<V::Class_t*> Members_t::Class()
    {
        DEFINE_CLASS();
    }

    some<V::Object_t*> Members_t::Object()
    {
        DEFINE_OBJECT_STATIC();
    }

    void Members_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)      \
        SKYLIB_M                                                                        \
            BIND_METHOD(machine, class_name, Members_t, METHOD_NAME_, WAITS_FOR_FRAME_, \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        #undef METHOD
    }

    void Members_t::Initialize()
    {
    }

    void Members_t::Before_Save()
    {
        state.Save();
    }

    void Members_t::After_Load()
    {
        state.~State();
        new (&state) State();
        state.Load();
    }

    void Members_t::u_0_10_0()
    {
        // because we'll now be storing member relevant data on this one script
        // we'll need to pull any relevant data from each member alias and transfer it over
        // that way we only have to serialize this script, and maybe we can even get rid of
        // the member scripts in the future.

        // when moving packs over, go ahead and create new references that aren't base on the old script type
        // probably same thing for outfits too.

        // clean up style and vitality codes as well. we could just use strings instead of ints, only double the data.

        // for the bools, maybe we could switch to flags? might not be worth it though, because it's hard to change at that point.

        // display markers should go to Expoees_t, because there can only be so many at a time, it uses less data to cache the actor
        // might want to do the same thing for Mannequins as well, however, it might make more sense to have that data here seeing
        // how we can have upto MAX_MEMBERS of mannequins

        // I'm seriously considering switching actor bases for each member, so that we can don't pollute the global bases. we could
        // have 1024 static blank bases in the .esp that we just copy the info to, or we could do it dynamically. I think we need to
        // do more testing, but it would save so much trouble! the trouble is, what happens when the mod is uninstalled? It will
        // probably be safe, as long as we create clones from their original base. they'll just automatically switch back.

        // all settler data should go in Settlers_t, just to make things cleaner.

    }

}}
