/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    Members_t::Save_State::Save_State() :
        actors(Vector_t<maybe<Actor_t*>>(MAX_MEMBERS)),
        original_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),

        flags(Vector_t<Member_Flags_e>(MAX_MEMBERS)),

        names(Vector_t<String_t>(MAX_MEMBERS)),
        packs(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS)),
        voice_types(Vector_t<maybe<Voice_Type_t*>>(MAX_MEMBERS)),

        default_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS)),
        vanilla_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS)),

        backup_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        current_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        default_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        follower_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        immobile_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        member_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        settler_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        thrall_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        vanilla_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),

        ratings(Vector_t<Member_Rating_t>(MAX_MEMBERS)),
        relations(Vector_t<Relation_e>(MAX_MEMBERS)),
        styles(Vector_t<Member_Style_e>(MAX_MEMBERS)),
        vitalities(Vector_t<Vitality_e>(MAX_MEMBERS))
    {
    }

    Members_t::Save_State::~Save_State()
    {
    }

    String_t Members_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_members");
    }

    some<V::Class_t*> Members_t::Class()
    {
        DEFINE_CLASS();
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

    Members_t::Members_t(some<Quest_t*> quest) :
        quest(quest),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        save_state(Save_State())
    {
        SKYLIB_ASSERT_SOME(quest);
    }

    Members_t::~Members_t()
    {
    }

    some<V::Object_t*> Members_t::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    V::Variable_tt<Vector_t<Actor_t*>>& Members_t::Actors_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Actor_t*>, "actors");
    }

    V::Variable_tt<Vector_t<Actor_Base_t*>>& Members_t::Original_Bases_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Actor_Base_t*>, "original_bases");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Banished_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_banished_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Clone_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_clone_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Immobile_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_immobile_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Mannequin_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_mannequin_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Paralyzed_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_paralyzed_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Reanimated_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_reanimated_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Is_Thrall_Flags_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_thrall_flags");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Names_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "names");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Packs_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "packs");
    }

    V::Variable_tt<Vector_t<Voice_Type_t*>>& Members_t::Voice_Types_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Voice_Type_t*>, "voice_types");
    }

    V::Variable_tt<Vector_t<Outfit_t*>>& Members_t::Default_Outfits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Outfit_t*>, "default_outfits");
    }

    V::Variable_tt<Vector_t<Outfit_t*>>& Members_t::Vanilla_Outfits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Outfit_t*>, "vanilla_outfits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Backup_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "backup_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Current_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "current_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Default_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "default_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Follower_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "follower_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Immobile_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "immobile_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Member_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "member_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Settler_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "settler_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Thrall_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "thrall_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Vanilla_Suits_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "vanilla_suits");
    }

    V::Variable_tt<Vector_t<Int_t>>& Members_t::Ratings_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "ratings");
    }

    V::Variable_tt<Vector_t<Int_t>>& Members_t::Relations_Variable()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "relations");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Styles_Variables()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "styles");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Vitalities_Variables()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "vitalities");
    }

    void Members_t::Before_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Validate_Member(member_id)) {
                Some_Actor(member_id)->Actor_Base(Some_Original_Base(member_id));
            }
        }

        Actors_Variable() = reinterpret_cast<Vector_t<Actor_t*>&>(this->save_state.actors);
        Original_Bases_Variable() = reinterpret_cast<Vector_t<Actor_Base_t*>&>(this->save_state.original_bases);
        Ratings_Variable() = reinterpret_cast<Vector_t<Int_t>&>(this->save_state.ratings);

        // styles and vitalites should be stored as strings. maybe ratings too. we unpack them into integers of course
    }

    void Members_t::After_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            Validate_Member(member_id); // sets the custom base
        }
    }

    void Members_t::After_Load()
    {
        this->save_state.~Save_State();
        new (&this->save_state) Save_State();

        // we need to actually validate everything.

        Vector_t<Actor_t*> actors = Actors_Variable();
        Vector_t<Actor_Base_t*> original_bases = Original_Bases_Variable();
        Vector_t<Int_t> ratings = Ratings_Variable();

        // we need to make sure each vector is the correct size. if they are not, we need to essentially either
        // try to match up each available actor to one that is actually aliased
        // or just leave leave the save_state empty and unfill all aliases.

        // we need to make sure that filled aliases are filled, and empty ones unfilled either here, or in validate

        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            this->save_state.actors[member_id] = actors[member_id];
            this->save_state.original_bases[member_id] = original_bases[member_id];
            this->save_state.ratings[member_id] = ratings[member_id];

            Validate_Member(member_id);
        }
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

    maybe<Member_ID_t> Members_t::Add_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);
    }

    maybe<Member_ID_t> Members_t::Add_Member_Clone(some<Actor_t*> actor)
    {
        // don't forget, when cloning an actor, we need to use their static base.
        // check that there is space, clone it, and pass to Add_Member.
    }

    void Members_t::Remove_Member(Member_ID_t member_id)
    {
        // this will cleanse anything under the id that it can, even if the data is incomplete in some manner, it cleans it up.
        // it fails gracefully and just defaults the values.
    }

    Bool_t Members_t::Validate_Member(Member_ID_t member_id)
    {
        // we should weed out actors that are invalid or deleted too probably. same with bases.
        // we maybe should do the aliases checks here or in load, not sure. prob. here.

        maybe<Actor_t*> actor = this->save_state.actors[member_id];
        maybe<Actor_Base_t*> original_base = this->save_state.original_bases[member_id];
        if (actor && original_base) {
            if (!this->custom_bases[member_id]) {
                this->custom_bases[member_id] = Actor_Base_t::Create_Temporary_Copy(original_base())();
            }
            actor->Actor_Base(this->custom_bases[member_id]());
            return true;
        } else {
            Remove_Member(member_id);
            return false;
        }
    }

    some<Actor_t*> Members_t::Some_Actor(Member_ID_t valid_member_id)
    {
        return this->save_state.actors[valid_member_id]();
    }

    some<Actor_Base_t*> Members_t::Some_Original_Base(Member_ID_t valid_member_id)
    {
        return this->save_state.original_bases[valid_member_id]();
    }

    some<Actor_Base_t*> Members_t::Some_Custom_Base(Member_ID_t valid_member_id)
    {
        return this->custom_bases[valid_member_id]();
    }

}}
