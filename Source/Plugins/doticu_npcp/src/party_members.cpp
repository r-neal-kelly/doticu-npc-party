/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/global.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/voice_type.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    Members_t::Save_State::Save_State(Members_t& members) :
        members(members),

        limit(MAX_MEMBERS),

        do_auto_suits(false),
        do_auto_immobile_suit(false),
        do_fill_suits(true),

        default_style(Member_Style_e::DEFAULT),
        default_suit_type(Member_Suit_Type_e::MEMBER),
        default_vitality(Member_Vitality_e::PROTECTED),

        member_suit_fill_type(Member_Suit_Fill_Type_e::REFERENCE),
        sort_type(Member_Sort_Type_e::NAME),

        actors(Vector_t<maybe<Actor_t*>>(MAX_MEMBERS)),
        original_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),

        flags(Vector_t<Member_Flags_e>(MAX_MEMBERS)),

        names(Vector_t<String_t>(MAX_MEMBERS)),
        packs(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS)),
        voice_types(Vector_t<maybe<Voice_Type_t*>>(MAX_MEMBERS)),

        default_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS)),
        vanilla_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS)),

        backup_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        default_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        follower_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        immobile_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        member_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        settler_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        thrall_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),
        vanilla_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS)),

        ratings(Vector_t<Member_Rating_t>(MAX_MEMBERS)),
        relations(Vector_t<Member_Relation_e>(MAX_MEMBERS)),
        styles(Vector_t<Member_Style_e>(MAX_MEMBERS)),
        suit_types(Vector_t<Member_Suit_Type_e>(MAX_MEMBERS)),
        vitalities(Vector_t<Member_Vitality_e>(MAX_MEMBERS))
    {
    }

    Members_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Members_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->members.quest());
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Limit()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "limit");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Auto_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_suits");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Auto_Immobile_Suit()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_immobile_suit");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Fill_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_fill_suits");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Style()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_style");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Suit_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_suit_type");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Vitality()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_vitality");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Member_Suit_Fill_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "member_suit_fill_type");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Sort_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "sort_type");
    }

    V::Variable_tt<Vector_t<Actor_t*>>& Members_t::Save_State::Actors()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Actor_t*>, "actors");
    }

    V::Variable_tt<Vector_t<Actor_Base_t*>>& Members_t::Save_State::Original_Bases()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Actor_Base_t*>, "original_bases");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Banished_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_banished_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Clone_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_clone_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Immobile_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_immobile_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Mannequin_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_mannequin_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Paralyzed_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_paralyzed_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Reanimated_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_reanimated_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Thrall_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_thrall_flags");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Names()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "names");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Packs()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "packs");
    }

    V::Variable_tt<Vector_t<Voice_Type_t*>>& Members_t::Save_State::Voice_Types()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Voice_Type_t*>, "voice_types");
    }

    V::Variable_tt<Vector_t<Outfit_t*>>& Members_t::Save_State::Default_Outfits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Outfit_t*>, "default_outfits");
    }

    V::Variable_tt<Vector_t<Outfit_t*>>& Members_t::Save_State::Vanilla_Outfits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Outfit_t*>, "vanilla_outfits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Backup_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "backup_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Default_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "default_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Follower_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "follower_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Immobile_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "immobile_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Member_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "member_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Settler_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "settler_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Thrall_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "thrall_suits");
    }

    V::Variable_tt<Vector_t<Reference_t*>>& Members_t::Save_State::Vanilla_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Reference_t*>, "vanilla_suits");
    }

    V::Variable_tt<Vector_t<Int_t>>& Members_t::Save_State::Ratings()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "ratings");
    }

    V::Variable_tt<Vector_t<Int_t>>& Members_t::Save_State::Relations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "relations");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Styles()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "styles");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Suit_Types()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "suit_types");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Vitalities()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "vitalities");
    }

    void Members_t::Save_State::Read()
    {
        // this should validate all inputs.

        Vector_t<Actor_t*> actors = Actors();
        Vector_t<Actor_Base_t*> original_bases = Original_Bases();
        Vector_t<Int_t> ratings = Ratings();

        actors.resize(MAX_MEMBERS);
        original_bases.resize(MAX_MEMBERS);
        ratings.resize(MAX_MEMBERS);

        for (Member_ID_t member_id = 0, end = this->actors.size(); member_id < end; member_id += 1) {
            this->actors[member_id] = actors[member_id];
            this->original_bases[member_id] = original_bases[member_id];
            this->ratings[member_id] = ratings[member_id];

            members.Validate_Member(member_id);
        }
    }

    void Members_t::Save_State::Write()
    {
        Actors() = reinterpret_cast<Vector_t<Actor_t*>&>(this->actors);
        Original_Bases() = reinterpret_cast<Vector_t<Actor_Base_t*>&>(this->original_bases);
        Ratings() = reinterpret_cast<Vector_t<Int_t>&>(this->ratings); // this is not correct.

        // styles and vitalites should be stored as strings. maybe ratings too. we unpack them into integers of course
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

    Bool_t Members_t::Do_Allow_Menu_For_All_Actors()
    {
        return Consts_t::NPCP::Global::Do_Allow_Menu_For_All_Actors()->Bool();
    }

    void Members_t::Do_Allow_Menu_For_All_Actors(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Allow_Menu_For_All_Actors()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Clone_Uniques()
    {
        return Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool();
    }

    void Members_t::Do_Force_Clone_Uniques(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Clone_Generics()
    {
        return Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool();
    }

    void Members_t::Do_Force_Clone_Generics(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Unclone_Uniques()
    {
        return Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool();
    }

    void Members_t::Do_Force_Unclone_Uniques(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Unclone_Generics()
    {
        return Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool();
    }

    void Members_t::Do_Force_Unclone_Generics(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool(value);
    }

    Int_t Members_t::Fill_Outfit_Body_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Body_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()->Percent(100 - value);
    }

    Int_t Members_t::Fill_Outfit_Feet_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Feet_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()->Percent(100 - value);
    }

    Int_t Members_t::Fill_Outfit_Hands_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Hands_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()->Percent(100 - value);
    }

    Int_t Members_t::Fill_Outfit_Head_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Head_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()->Percent(100 - value);
    }

    Members_t::Members_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        save_state(*this)
    {
        SKYLIB_ASSERT_SOME(quest);

        if (is_new_game) {
            Do_Allow_Menu_For_All_Actors(true);

            Do_Force_Clone_Uniques(false);
            Do_Force_Clone_Generics(false);
            Do_Force_Unclone_Uniques(false);
            Do_Force_Unclone_Generics(false);

            Fill_Outfit_Body_Percent(DEFAULT_FILL_OUTFIT_BODY_PERCENT);
            Fill_Outfit_Feet_Percent(DEFAULT_FILL_OUTFIT_FEET_PERCENT);
            Fill_Outfit_Hands_Percent(DEFAULT_FILL_OUTFIT_HANDS_PERCENT);
            Fill_Outfit_Head_Percent(DEFAULT_FILL_OUTFIT_HEAD_PERCENT);
        } else {
            this->save_state.Read();
            Validate_Aliases_And_Members();
        }
    }

    Members_t::Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        save_state(*this)
    {
        this->save_state.Read();
        Validate_Aliases_And_Members();
    }

    Members_t::~Members_t()
    {
        for (Member_ID_t member_id = 0, end = this->custom_bases.size(); member_id < end; member_id += 1) {
            maybe<Actor_Base_t*> custom_base = this->custom_bases[member_id];
            if (custom_base) {
                Actor_Base_t::Destroy(custom_base());
                this->custom_bases[member_id] = none<Actor_Base_t*>();
            }
        }
    }

    Bool_t Members_t::Has_Member(Member_ID_t member_id)
    {
        maybe<Actor_t*> actor = this->save_state.actors[member_id];
        maybe<Actor_Base_t*> base = this->save_state.original_bases[member_id];
        return
            actor && actor->Is_Valid() && actor->Isnt_Deleted() &&
            base && base->Is_Valid() && base->Isnt_Deleted();
    }

    Bool_t Members_t::Has_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = this->save_state.actors.size(); idx < end; idx += 1) {
            if (this->save_state.actors[idx] == actor) {
                return Has_Member(idx);
            }
        }
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

    Bool_t Members_t::Remove_Member(Member_ID_t member_id)
    {
        // this will cleanse anything under the id that it can, even if the data is incomplete in some manner, it cleans it up.
        // it fails gracefully and just defaults the values.
        return false;
    }

    Bool_t Members_t::Validate_Member(Member_ID_t member_id)
    {
        if (Has_Member(member_id)) {
            some<Actor_t*> actor = Some_Actor(member_id);
            some<Actor_Base_t*> original_base = Some_Original_Base(member_id);
            if (!this->custom_bases[member_id]) {
                this->custom_bases[member_id] = Actor_Base_t::Create_Temporary_Copy(original_base)();
            }
            actor->Actor_Base(this->custom_bases[member_id](), false);
            // we need to apply any other data that we want, like voice type, relation, etc.
            return true;
        } else {
            Remove_Member(member_id);
            return false;
        }
    }

    void Members_t::Validate_Aliases_And_Members()
    {
        // we unfill first because the quest doesn't allow dupe aliases.
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            Some_Alias_Reference(member_id)->Unfill(none<V::Callback_i*>());
        }
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Has_Member(member_id)) {
                class Fill_Callback :
                    public V::Callback_t
                {
                public:
                    some<Members_t*>    self;
                    Member_ID_t         member_id;

                public:
                    Fill_Callback(some<Members_t*> self, Member_ID_t member_id) :
                        self(self), member_id(member_id)
                    {
                    }

                public:
                    virtual void operator ()(V::Variable_t*) override
                    {
                        this->self->Validate_Member(this->member_id);
                    }
                };
                Some_Alias_Reference(member_id)->Fill(Some_Actor(member_id), new Fill_Callback(this, member_id));
            }
        }
    }

    some<Alias_Reference_t*> Members_t::Some_Alias_Reference(Member_ID_t valid_member_id)
    {
        some<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(valid_member_id)();
        SKYLIB_ASSERT_SOME(alias_reference);
        return alias_reference;
    }

    some<Actor_t*> Members_t::Some_Actor(Member_ID_t valid_member_id)
    {
        some<Actor_t*> actor = this->save_state.actors[valid_member_id]();
        SKYLIB_ASSERT_SOME(actor);
        return actor;
    }

    some<Actor_Base_t*> Members_t::Some_Original_Base(Member_ID_t valid_member_id)
    {
        some<Actor_Base_t*> original_base = this->save_state.original_bases[valid_member_id]();
        SKYLIB_ASSERT_SOME(original_base);
        return original_base;
    }

    some<Actor_Base_t*> Members_t::Some_Custom_Base(Member_ID_t valid_member_id)
    {
        some<Actor_Base_t*> custom_base = this->custom_bases[valid_member_id]();
        SKYLIB_ASSERT_SOME(custom_base);
        return custom_base;
    }

    Member_Suit_Type_e Members_t::Current_Suit_Type(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.suit_types[valid_member_id];
    }

    maybe<Member_Suit_t*> Members_t::Maybe_Current_Suit(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Member_Suit_Type_e current_suit_type = Current_Suit_Type(valid_member_id);
        if (current_suit_type == Member_Suit_Type_e::MEMBER) {
            return this->save_state.member_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::IMMOBILE) {
            return this->save_state.immobile_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::SETTLER) {
            return this->save_state.settler_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::THRALL) {
            return this->save_state.thrall_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::FOLLOWER) {
            return this->save_state.follower_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::VANILLA) {
            return this->save_state.vanilla_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::DEFAULT) {
            return this->save_state.default_suits[valid_member_id];
        } else {
            none<Member_Suit_t*>();
        }
    }

    void Members_t::Before_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Validate_Member(member_id)) {
                Some_Actor(member_id)->Actor_Base(Some_Original_Base(member_id), false);
            }
        }
        this->save_state.Write();
    }

    void Members_t::After_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Has_Member(member_id)) {
                Some_Actor(member_id)->Actor_Base(Some_Custom_Base(member_id), false);
            }
        }
    }

}}
