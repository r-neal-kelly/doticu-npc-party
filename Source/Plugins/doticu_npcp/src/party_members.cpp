/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/voice_type.h"
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
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS))
    {
        SKYLIB_ASSERT_SOME(quest);

        // this maybe should go ahead and load available data?
        // we would need that if we have this object reinstantiated each game load by Main_t.
    }

    Members_t::Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        Members_t(quest)
    {
    }

    Members_t::~Members_t()
    {
        // we maybe should destroy all custom_bases here.
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

    void Members_t::Initialize()
    {
    }

    void Members_t::Before_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Validate_Member(member_id)) {
                // we can do a test to see if this even matters.
                Some_Actor(member_id)->Actor_Base(Some_Original_Base(member_id));
            }
        }

        Actors_Variable() = reinterpret_cast<Vector_t<Actor_t*>&>(this->save_state.actors);
        Original_Bases_Variable() = reinterpret_cast<Vector_t<Actor_Base_t*>&>(this->save_state.original_bases);
        Ratings_Variable() = reinterpret_cast<Vector_t<Int_t>&>(this->save_state.ratings); // this is not correct.

        // styles and vitalites should be stored as strings. maybe ratings too. we unpack them into integers of course
    }

    void Members_t::After_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            Validate_Member(member_id); // sets the custom base. we may want to just do that manually here?
        }
    }

    void Members_t::Before_Load()
    {
        for (Member_ID_t member_id = 0, end = this->custom_bases.size(); member_id < end; member_id += 1) {
            maybe<Actor_Base_t*> custom_base = this->custom_bases[member_id];
            if (custom_base) {
                Actor_Base_t::Destroy(custom_base());
                this->custom_bases[member_id] = none<Actor_Base_t*>();
            }
        }
    }

    void Members_t::After_Load()
    {
        this->save_state.~Save_State();
        new (&this->save_state) Save_State();

        // validate EVERYTHING.

        Vector_t<Actor_t*> actors = Actors_Variable();
        Vector_t<Actor_Base_t*> original_bases = Original_Bases_Variable();
        Vector_t<Int_t> ratings = Ratings_Variable();

        actors.resize(MAX_MEMBERS);
        original_bases.resize(MAX_MEMBERS);
        ratings.resize(MAX_MEMBERS);

        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            this->save_state.actors[member_id] = actors[member_id];
            this->save_state.original_bases[member_id] = original_bases[member_id];
            this->save_state.ratings[member_id] = ratings[member_id];

            Validate_Member(member_id);
            // we need to make sure the correct actor is in the correct alias. if no actor, it needs to be unfilled.
            // effectively that makes Members_t's Save_State the one and only source of truth.
            // I think we need to do it here or in another func that is not Validate_Member, because this can be rather slow.
        }
    }

    void Members_t::u_0_10_0()
    {
        // this is going to be pretty rough. It might be best to just require a new game sadly. in any case, we may just
        // want to focus on getting a new game working first, and then come back to this monster.

        // the current design calls this func, and then After_Load is called. we need to make sure this data is saved,
        // or skip the After_Load for this update, perhaps all updates? maybe we should have main call save game instead of load game?

        // we may want to unfill all aliases first, which shouldn't affect the data stored on their scripts. (use Unfill_All)

        for (size_t idx = 0, end = this->quest->aliases.Count(); idx < end; idx += 1) {
            maybe<Alias_Base_t*> alias_base = this->quest->aliases[idx];
            if (alias_base) {
                maybe<V::Object_t*> object = V::Object_t::Find(alias_base(), "doticu_npcp_member", false);
                if (object) {
                    maybe<Actor_t*> actor = object->Variable("p_ref_actor")->As<Actor_t*>();
                    if (actor) {
                        maybe<Member_ID_t> maybe_member_id = Add_Member(actor());
                        if (maybe_member_id.Has_Value()) {
                            Member_ID_t member_id = maybe_member_id.Value();

                            // we should apply data through normal method calls, to make sure the state is set up correctly.

                            Bool_t is_banished = false;
                            Bool_t is_clone = object->Variable("p_is_clone")->As<Bool_t>();
                            Bool_t is_immobile = object->Variable("p_is_immobile")->As<Bool_t>();
                            Bool_t is_mannequin = object->Variable("p_is_mannequin")->As<Bool_t>();
                            Bool_t is_paralyzed = object->Variable("p_is_paralyzed")->As<Bool_t>();
                            Bool_t is_reanimated = object->Variable("p_is_reanimated")->As<Bool_t>();
                            Bool_t is_thrall = object->Variable("p_is_thrall")->As<Bool_t>();
                            
                            String_t name = object->Variable("p_str_name")->As<String_t>();
                            maybe<Reference_t*> pack = object->Variable("p_container_pack")->As<Reference_t*>(); // move items to new ref
                            maybe<Voice_Type_t*> voice_type = none<Voice_Type_t*>();

                            maybe<Outfit_t*> default_outfit = object->Variable("p_outfit_default")->As<Outfit_t*>();
                            maybe<Outfit_t*> vanilla_outfit = object->Variable("p_outfit_vanilla")->As<Outfit_t*>();

                            // all of these need to have their items moved to a new ref and cleaned up too.
                            maybe<Reference_t*> backup_suit = object->Variable("p_outfit2_auto_backup")->As<Reference_t*>(); // this needs to be handled specially
                            maybe<Reference_t*> current_suit = object->Variable("p_outfit2_current")->As<Reference_t*>(); // ""
                            maybe<Reference_t*> default_suit = object->Variable("p_outfit2_default")->As<Reference_t*>();
                            maybe<Reference_t*> follower_suit = object->Variable("p_outfit2_follower")->As<Reference_t*>();
                            maybe<Reference_t*> immobile_suit = object->Variable("p_outfit2_immobile")->As<Reference_t*>();
                            maybe<Reference_t*> member_suit = object->Variable("p_outfit2_member")->As<Reference_t*>();
                            maybe<Reference_t*> settler_suit = object->Variable("p_outfit2_settler")->As<Reference_t*>();
                            maybe<Reference_t*> thrall_suit = object->Variable("p_outfit2_thrall")->As<Reference_t*>();
                            maybe<Reference_t*> vanilla_suit = object->Variable("p_outfit2_vanilla")->As<Reference_t*>();

                            Int_t rating = object->Variable("p_int_rating")->As<Int_t>();
                            Int_t style = object->Variable("p_code_style")->As<Int_t>();
                            Int_t vitality = object->Variable("p_code_vitality")->As<Int_t>();

                            /*
                                DEFAULT = -380,
                                WARRIOR = -381,
                                MAGE = -382,
                                ARCHER = -383,
                                COWARD = -384,
                            */

                            /*
                                MORTAL = -303,
                                PROTECTED = -304,
                                ESSENTIAL = -305,
                                INVULNERABLE = -306
                            */

                            // we maybe should completely clear all data on the script too, before deleting.

                            Validate_Member(member_id); // we may not need to call this if we use proper methods to set all this data.
                        }
                    }
                }
            }
        }

        // because we'll now be storing member relevant data on this one script
        // we'll need to pull any relevant data from each member alias and transfer it over
        // that way we only have to serialize this script, and we can even get rid of
        // the member scripts in the future.

        // when moving packs over, go ahead and create new references that aren't based on the old script type
        // probably same thing for outfits too.

        // clean up style and vitality codes as well. we could just use strings instead of ints, only double the data.

        // for the bools, maybe we could switch to flags? might not be worth it though, because it's hard to change at that point.

        // display markers should go to Expoees_t, because there can only be so many at a time, it uses less data to cache the actor
        // might want to do the same thing for Mannequins as well, however, it might make more sense to have that data here seeing
        // how we can have upto MAX_MEMBERS of mannequins

        // all settler data should go in Settlers_t, just to make things cleaner.
    }

    maybe<Member_ID_t> Members_t::Add_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return 0;
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
        // we maybe should do the aliases checks here or in load, not sure. I think it would be really slow to do it here

        maybe<Actor_t*> actor = this->save_state.actors[member_id];
        maybe<Actor_Base_t*> original_base = this->save_state.original_bases[member_id];
        if (actor && original_base) {
            if (!this->custom_bases[member_id]) {
                this->custom_bases[member_id] = Actor_Base_t::Create_Temporary_Copy(original_base())();
            }
            actor->Actor_Base(this->custom_bases[member_id]());
            // we need to apply any data to the base that we want, like voice type, relation, etc.
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
