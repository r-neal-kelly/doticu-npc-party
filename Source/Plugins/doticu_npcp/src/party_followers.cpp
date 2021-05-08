/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/virtual_macros.h"

#include "main.h"
#include "npcp.h"
#include "party_followers.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    Followers_t::Save_State::Save_State(const some<Quest_t*> quest) :
        quest(quest),

        limit(DEFAULT_LIMIT),

        do_auto_resurrect(DEFAULT_DO_AUTO_RESURRECT),
        do_auto_sojourn(DEFAULT_DO_AUTO_SOJOURN),
        do_level(DEFAULT_DO_LEVEL),

        sort_type(DEFAULT_SORT_TYPE),

        member_ids(Vector_t<maybe<Member_ID_t>>(MAX_FOLLOWERS, none<Member_ID_t>())),

        flags(Vector_t<Follower_Flags_e>(MAX_FOLLOWERS, 0))
    {
    }

    Followers_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Followers_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    V::Variable_tt<Int_t>& Followers_t::Save_State::Limit()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "limit");
    }

    V::Variable_tt<Bool_t>& Followers_t::Save_State::Do_Auto_Resurrect()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_resurrect");
    }

    V::Variable_tt<Bool_t>& Followers_t::Save_State::Do_Auto_Sojourn()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_sojourn");
    }

    V::Variable_tt<Bool_t>& Followers_t::Save_State::Do_Level()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_level");
    }

    V::Variable_tt<String_t>& Followers_t::Save_State::Sort_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "sort_type");
    }

    V::Variable_tt<Vector_t<Int_t>>& Followers_t::Save_State::Member_IDs()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "member_ids");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Followers_t::Save_State::Flags_Is_Retreater()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_retreater");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Followers_t::Save_State::Flags_Is_Saddler()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_saddler");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Followers_t::Save_State::Flags_Is_Sneak()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_sneak");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Followers_t::Save_State::Flags_Is_Sojourner()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_sojourner");
    }

    void Followers_t::Save_State::Read()
    {
        this->limit = static_cast<Follower_Limit_t::value_type>(Limit());

        this->do_auto_resurrect = Do_Auto_Resurrect();
        this->do_auto_sojourn = Do_Auto_Sojourn();
        this->do_level = Do_Level();

        this->sort_type = Sort_Type().As<String_t>();

        Vector_t<Int_t> member_ids = Member_IDs();

        Vector_t<Bool_t> flags_is_retreater = Flags_Is_Retreater();
        Vector_t<Bool_t> flags_is_saddler = Flags_Is_Saddler();
        Vector_t<Bool_t> flags_is_sneak = Flags_Is_Sneak();
        Vector_t<Bool_t> flags_is_sojourner = Flags_Is_Sojourner();

        member_ids.resize(MAX_FOLLOWERS);

        flags_is_retreater.resize(MAX_FOLLOWERS);
        flags_is_saddler.resize(MAX_FOLLOWERS);
        flags_is_sneak.resize(MAX_FOLLOWERS);
        flags_is_sojourner.resize(MAX_FOLLOWERS);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            this->member_ids[idx] = member_ids[idx];

            Follower_Flags_e& flags = this->flags[idx];
            flags.Is_Flagged(Follower_Flags_e::IS_RETREATER, flags_is_retreater[idx]);
            flags.Is_Flagged(Follower_Flags_e::IS_SADDLER, flags_is_saddler[idx]);
            flags.Is_Flagged(Follower_Flags_e::IS_SNEAK, flags_is_sneak[idx]);
            flags.Is_Flagged(Follower_Flags_e::IS_SOJOURNER, flags_is_sojourner[idx]);
        }
    }

    void Followers_t::Save_State::Write()
    {
        Vector_t<Int_t> member_ids(MAX_FOLLOWERS, Member_ID_t::_NONE_);

        Vector_t<Bool_t> flags_is_retreater(MAX_FOLLOWERS, false);
        Vector_t<Bool_t> flags_is_saddler(MAX_FOLLOWERS, false);
        Vector_t<Bool_t> flags_is_sneak(MAX_FOLLOWERS, false);
        Vector_t<Bool_t> flags_is_sojourner(MAX_FOLLOWERS, false);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            member_ids[idx] = this->member_ids[idx]();

            Follower_Flags_e flags = this->flags[idx];
            flags_is_retreater[idx] = flags.Is_Flagged(Follower_Flags_e::IS_RETREATER);
            flags_is_saddler[idx] = flags.Is_Flagged(Follower_Flags_e::IS_SADDLER);
            flags_is_sneak[idx] = flags.Is_Flagged(Follower_Flags_e::IS_SNEAK);
            flags_is_sojourner[idx] = flags.Is_Flagged(Follower_Flags_e::IS_SOJOURNER);
        }

        Limit() = static_cast<Follower_Limit_t::value_type>(this->limit());

        Do_Auto_Resurrect() = this->do_auto_resurrect;
        Do_Auto_Sojourn() = this->do_auto_sojourn;
        Do_Level() = this->do_level;

        Sort_Type() = this->sort_type().As_String();

        Member_IDs() = member_ids;

        Flags_Is_Retreater() = flags_is_retreater;
        Flags_Is_Saddler() = flags_is_saddler;
        Flags_Is_Sneak() = flags_is_sneak;
        Flags_Is_Sojourner() = flags_is_sojourner;
    }

    String_t Followers_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_party_followers");
    }

    some<V::Class_t*> Followers_t::Class()
    {
        DEFINE_CLASS();
    }

    void Followers_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)          \
        SKYLIB_M                                                                            \
            BIND_METHOD(machine, class_name, Followers_t, METHOD_NAME_, WAITS_FOR_FRAME_,   \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                                \
        SKYLIB_W

        #undef METHOD
    }

    Followers_t::Followers_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        save_state(quest)
    {
        if (is_new_game) {

        } else {
            this->save_state.Read();
        }
    }

    Followers_t::Followers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest)
    {
        // update code goes here

        this->save_state.Read();
    }

    Followers_t::~Followers_t()
    {
    }

    void Followers_t::Before_Save()
    {
        this->save_state.Write();
    }

    void Followers_t::After_Save()
    {
    }

    void Followers_t::Validate()
    {
        if (!this->save_state.limit) {
            this->save_state.limit = Follower_Limit_t::_MAX_;
        } else {
            size_t follower_count = Follower_Count();
            if (this->save_state.limit() < follower_count) {
                this->save_state.limit = follower_count;
            }
        }

        class Unfill_Aliases_Callback :
            public Callback_i<>
        {
        public:
            Followers_t& self;

        public:
            Unfill_Aliases_Callback(Followers_t& self) :
                self(self)
            {
            }

        public:
            virtual void operator ()() override
            {
                for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
                    if (this->self.Has_Follower(Follower_ID_t(idx))) {
                        this->self.Alias_Reference(idx)->Fill(this->self.Actor(idx), none<V::Callback_i*>());
                    } else {
                        this->self.Remove_Follower(idx);
                    }
                }
            }
        };
        this->quest->Unfill_Aliases(new Unfill_Aliases_Callback(*this));
    }

    Main_t& Followers_t::Main()
    {
        return NPCP.Main().Party();
    }

    Members_t& Followers_t::Members()
    {
        return NPCP.Main().Party().Members();
    }

    some<Follower_Limit_t> Followers_t::Limit()
    {
        return this->save_state.limit;
    }

    void Followers_t::Limit(some<Follower_Limit_t> value)
    {
        SKYLIB_ASSERT_SOME(value);
        SKYLIB_ASSERT(value() >= Follower_Count());

        this->save_state.limit = value;
    }

    Bool_t Followers_t::Do_Auto_Resurrect()
    {
        return this->save_state.do_auto_resurrect;
    }

    void Followers_t::Do_Auto_Resurrect(Bool_t value)
    {
        this->save_state.do_auto_resurrect = value;
    }

    Bool_t Followers_t::Do_Auto_Sojourn()
    {
        return this->save_state.do_auto_sojourn;
    }

    void Followers_t::Do_Auto_Sojourn(Bool_t value)
    {
        this->save_state.do_auto_sojourn = value;
    }

    Bool_t Followers_t::Do_Level()
    {
        return this->save_state.do_level;
    }

    void Followers_t::Do_Level(Bool_t value)
    {
        this->save_state.do_level = value;
    }

    some<Member_Sort_Type_e> Followers_t::Sort_Type()
    {
        if (!this->save_state.sort_type) {
            this->save_state.sort_type = DEFAULT_SORT_TYPE;
        }

        return this->save_state.sort_type;
    }

    void Followers_t::Sort_Type(some<Member_Sort_Type_e> value)
    {
        SKYLIB_ASSERT_SOME(value);

        this->save_state.sort_type = value;
    }

    Bool_t Followers_t::Has_Alias(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        return this->quest->Has_Alias_Index(follower_id());
    }

    Bool_t Followers_t::Has_Alias(Alias_ID_t alias_id)
    {
        return this->quest->Has_Alias_ID(alias_id);
    }

    Bool_t Followers_t::Has_Follower(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        maybe<Member_ID_t> member_id = this->save_state.member_ids[follower_id()];
        return member_id && Members().Has_Member(member_id());
    }

    Bool_t Followers_t::Has_Follower(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        return Used_Follower_ID(member_id) != none<Follower_ID_t>();
    }

    Bool_t Followers_t::Has_Follower(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Used_Follower_ID(actor) != none<Follower_ID_t>();
    }

    maybe<Follower_ID_t> Followers_t::Used_Follower_ID(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            if (this->save_state.member_ids[idx] == member_id && Members().Has_Member(member_id())) {
                return idx;
            }
        }
        return none<Follower_ID_t>();
    }

    maybe<Follower_ID_t> Followers_t::Used_Follower_ID(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            maybe<Member_ID_t> member_id = this->save_state.member_ids[idx];
            if (member_id && Members().Has_Member(member_id()) && Members().Actor(member_id()) == actor) {
                return idx;
            }
        }
        return none<Follower_ID_t>();
    }

    maybe<Follower_ID_t> Followers_t::Unused_Follower_ID()
    {
        // this needs to be locked.
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            if (!Has_Follower(Follower_ID_t(idx))) {
                return idx;
            }
        }
        return none<Follower_ID_t>();
    }

    static void Add_Follower(Followers_t& self, some<Follower_ID_t> follower_id, some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);
        SKYLIB_ASSERT_SOME(member_id);

        self.save_state.member_ids[follower_id()] = member_id;

        // may want to create static defaults for these
        Follower_Flags_e& flags = self.save_state.flags[follower_id()];
        flags.Is_Flagged(Follower_Flags_e::IS_RETREATER, false);
        flags.Is_Flagged(Follower_Flags_e::IS_SADDLER, false);
        flags.Is_Flagged(Follower_Flags_e::IS_SNEAK, false);
        flags.Is_Flagged(Follower_Flags_e::IS_SOJOURNER, false);

        self.Alias_Reference(follower_id)->Fill(self.Actor(follower_id), none<V::Callback_i*>());
    }

    maybe<Follower_ID_t> Followers_t::Add_Follower(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        maybe<Follower_ID_t> used_follower_id = Used_Follower_ID(member_id);
        if (used_follower_id) {
            return used_follower_id;
        } else {
            if (Follower_Count() < Limit()()) {
                if (Members().Has_Member(member_id)) {
                    maybe<Follower_ID_t> follower_id = Unused_Follower_ID();
                    if (follower_id) {
                        Party::Add_Follower(*this, follower_id(), member_id);
                        Enforce(follower_id());
                        return follower_id;
                    } else {
                        return none<Follower_ID_t>();
                    }
                } else {
                    return none<Follower_ID_t>();
                }
            } else {
                return none<Follower_ID_t>();
            }
        }
    }

    Bool_t Followers_t::Remove_Follower(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        // this will cleanse anything under the id that it can, even if the data is incomplete in some manner, it cleans it up.
        // it fails gracefully and just defaults the values.

        // this should forcibly reset ai and make sure other state is reset that is needed.
        return false;
    }

    size_t Followers_t::Follower_Count()
    {
        size_t result = 0;
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            if (Has_Follower(Follower_ID_t(idx))) {
                result += 1;
            }
        }
        return result;
    }

    some<Alias_Reference_t*> Followers_t::Alias_Reference(some<Follower_ID_t> valid_follower_id)
    {
        SKYLIB_ASSERT_SOME(valid_follower_id);
        SKYLIB_ASSERT(Has_Follower(valid_follower_id));

        some<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(valid_follower_id())();
        SKYLIB_ASSERT_SOME(alias_reference);
        return alias_reference;
    }

    some<Actor_t*> Followers_t::Actor(some<Follower_ID_t> valid_follower_id)
    {
        SKYLIB_ASSERT_SOME(valid_follower_id);
        SKYLIB_ASSERT(Has_Follower(valid_follower_id));

        return Members().Actor(Member_ID(valid_follower_id));
    }

    some<Member_ID_t> Followers_t::Member_ID(some<Follower_ID_t> valid_follower_id)
    {
        SKYLIB_ASSERT_SOME(valid_follower_id);
        SKYLIB_ASSERT(Has_Follower(valid_follower_id));

        some<Member_ID_t> member_id = this->save_state.member_ids[valid_follower_id()]();
        SKYLIB_ASSERT_SOME(member_id);
        return member_id;
    }

    void Followers_t::Enforce(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        // may want to have a separate flow for in combat actors

        if (Has_Follower(follower_id)) {
            Main_t& main = Main();
            Members_t& members = Members();

            some<Actor_t*> actor = Actor(follower_id);
            some<Member_ID_t> member_id = Member_ID(follower_id);

            main.Tokenize(member_id, Consts_t::NPCP::Misc::Token::Follower(), follower_id() + 1);

            actor->Is_Player_Teammate(true);
        } else {
            Remove_Follower(follower_id);
        }
    }

}}
