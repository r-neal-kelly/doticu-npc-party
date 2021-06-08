/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/quest.h"

#include "npcp.inl"
#include "party.h"
#include "party_followers.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Followers_t::Save_t::Save_t() :
        do_level(DEFAULT_DO_LEVEL),
        do_resurrect_automatically(DEFAULT_DO_RESURRECT_AUTOMATICALLY),
        do_sojourn_automatically(DEFAULT_DO_SOJOURN_AUTOMATICALLY),

        limit(DEFAULT_LIMIT),

        sort_type(DEFAULT_SORT_TYPE)
    {
    }

    Followers_t::Save_t::~Save_t()
    {
    }

    void Followers_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->do_level);
        NPCP.Write(file, this->do_resurrect_automatically);
        NPCP.Write(file, this->do_sojourn_automatically);

        NPCP.Write(file, this->limit);

        NPCP.Write(file, this->sort_type);
    }

    void Followers_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->do_level);
        NPCP.Read(file, this->do_resurrect_automatically);
        NPCP.Read(file, this->do_sojourn_automatically);

        NPCP.Read(file, this->limit);

        NPCP.Read(file, this->sort_type);
    }

    Followers_t::State_t::State_t() :
        save(),

        followers()
    {
    }

    Followers_t::State_t::~State_t()
    {
    }

    Party_t& Followers_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Followers_t::Members()
    {
        return Party().Members();
    }

    Followers_t::Followers_t() :
        state()
    {
    }

    Followers_t::~Followers_t()
    {
    }

    void Followers_t::On_After_New_Game()
    {
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_After_New_Game();
        }
    }

    void Followers_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_Before_Save_Game(file);
        }
    }

    void Followers_t::On_After_Save_Game()
    {
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_After_Save_Game();
        }
    }

    void Followers_t::On_Before_Load_Game()
    {
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_Before_Load_Game();
        }
    }

    void Followers_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_After_Load_Game(file);
        }

        Refill_Aliases();
    }

    void Followers_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_After_Load_Game(file, version_to_update);
        }

        Refill_Aliases();
    }

    void Followers_t::On_Update()
    {
        some<Quest_t*> quest = Quest();
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            Follower_t& follower = Follower(idx);
            if (follower.Is_Active()) {
                if (!quest->Has_Filled_Alias(idx)) {
                    Alias(idx)->Fill(follower.Actor(), none<Virtual::Callback_i*>());
                }
            } else {
                if (quest->Has_Filled_Alias(idx)) {
                    Alias(idx)->Unfill(none<Virtual::Callback_i*>());
                }
            }
        }
    }

    Followers_t::State_t& Followers_t::State()
    {
        return this->state;
    }

    Followers_t::Save_t& Followers_t::Save()
    {
        return State().save;
    }

    Bool_t Followers_t::Do_Level()
    {
        return Save().do_level;
    }

    void Followers_t::Do_Level(Bool_t value)
    {
        Save().do_level = value;
    }

    Bool_t Followers_t::Do_Resurrect_Automatically()
    {
        return Save().do_resurrect_automatically;
    }

    void Followers_t::Do_Resurrect_Automatically(Bool_t value)
    {
        Save().do_resurrect_automatically = value;
    }

    Bool_t Followers_t::Do_Sojourn_Automatically()
    {
        return Save().do_sojourn_automatically;
    }

    void Followers_t::Do_Sojourn_Automatically(Bool_t value)
    {
        Save().do_sojourn_automatically = value;
    }

    some<Follower_Limit_t> Followers_t::Limit()
    {
        maybe<Follower_Limit_t>& value = Save().limit;
        if (!value) {
            value = DEFAULT_LIMIT;
        }

        size_t active_follower_count = Active_Count();
        if (value() < active_follower_count) {
            value = active_follower_count;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Followers_t::Limit(maybe<Follower_Limit_t> value)
    {
        Save().limit = value;
    }

    some<Member_Sort_Type_e> Followers_t::Sort_Type()
    {
        maybe<Member_Sort_Type_e>& value = Save().sort_type;
        if (!value) {
            value = DEFAULT_SORT_TYPE;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Followers_t::Sort_Type(maybe<Member_Sort_Type_e> value)
    {
        Save().sort_type = value;
    }

    some<Quest_t*> Followers_t::Quest()
    {
        return Consts_t::NPCP::Quest::Followers();
    }

    some<Alias_Reference_t*> Followers_t::Alias(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        maybe<Alias_Reference_t*> alias = Quest()->Index_To_Alias_Reference(follower_id());
        SKYLIB_ASSERT_SOME(alias);

        return alias();
    }

    Follower_t& Followers_t::Follower(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        return State().followers[follower_id()];
    }

    maybe<Follower_t*> Followers_t::Follower(Member_t& member)
    {
        return member.Follower();
    }

    maybe<Follower_t*> Followers_t::Follower(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            Follower_t& follower = Follower(idx);
            if (follower.Is_Active() && follower.Actor() == actor) {
                return &follower;
            }
        }
        return none<Follower_t*>();
    }

    maybe<Follower_ID_t> Followers_t::Inactive_ID()
    {
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            Follower_t& follower = Follower(idx);
            if (!follower.Is_Active()) {
                return idx;
            }
        }
        return none<Follower_ID_t>();
    }

    size_t Followers_t::Active_Count()
    {
        size_t count = 0;
        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            if (Follower(idx).Is_Active()) {
                count += 1;
            }
        }
        return count;
    }

    size_t Followers_t::Inactive_Count()
    {
        return MAX_FOLLOWERS - Active_Count();
    }

    Bool_t Followers_t::Has(Member_t& member)
    {
        return member.Is_Follower();
    }

    Bool_t Followers_t::Has(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Follower(actor) != none<Follower_t*>();
    }

    maybe<Follower_t*> Followers_t::Add(Member_t& member)
    {
        if (member.Is_Active() && !Has(member)) {
            maybe<Follower_ID_t> follower_id = Inactive_ID();
            if (follower_id) {
                Follower_t& follower = Follower(follower_id());
                follower.~Follower_t();
                new (&follower) Follower_t(member.Member_ID(), follower_id());
                if (follower.Is_Active()) {
                    Alias(follower_id())->Fill(follower.Actor(), none<Virtual::Callback_i*>());
                    return &follower;
                } else {
                    Alias(follower_id())->Unfill(none<Virtual::Callback_i*>());
                    return none<Follower_t*>();
                }
            } else {
                return none<Follower_t*>();
            }
        } else {
            return none<Follower_t*>();
        }
    }

    maybe<Follower_t*> Followers_t::Add(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Member_t*> member = Members().Member(actor);
        if (member) {
            return Add(*member);
        } else {
            member = Members().Add(actor, false);
            if (member) {
                return Add(*member);
            } else {
                return none<Follower_t*>();
            }
        }
    }

    Bool_t Followers_t::Remove(Follower_t& follower)
    {
        if (follower.Is_Active()) {
            follower.Alias()->Unfill(none<Virtual::Callback_i*>());
            follower.Reset();

            return true;
        } else {
            return false;
        }
    }

    Bool_t Followers_t::Remove(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Follower_t*> follower = Follower(actor);
        if (follower) {
            return Remove(*follower);
        } else {
            return false;
        }
    }

    void Followers_t::Refill_Aliases()
    {
        class Unfill_Aliases_Callback :
            public Callback_i<>
        {
        public:
            virtual void operator ()() override
            {
                std::thread(
                    []()->void
                    {
                        NPCP_t::Locker_t locker = NPCP.Locker();
                        if (NPCP.Is_Valid()) {
                            Followers_t& followers = NPCP.Party().Followers();
                            for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
                                Follower_t& follower = followers.Follower(idx);
                                if (follower.Is_Active()) {
                                    follower.Alias()->Fill(follower.Actor(), none<Virtual::Callback_i*>());
                                }
                            }
                        }
                    }
                ).detach();
            }
        };
        Quest()->Unfill_Aliases(new Unfill_Aliases_Callback());
    }

    void Followers_t::Reset_Options()
    {
        State().save.~Save_t();
        new (&State().save) Save_t();
    }

}}





/*
namespace doticu_npcp { namespace Party {

    static void Add_Follower(Followers_t& self, some<Follower_ID_t> follower_id, some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);
        SKYLIB_ASSERT_SOME(member_id);

        self.save_state.member_ids[follower_id()] = member_id;

        // may want to create static defaults for these
        Follower_Flags_e& flags = self.save_state.flags[follower_id()];
        flags.Is_Flagged(Follower_Flags_e::IS_RETREATER, false);
        flags.Is_Flagged(Follower_Flags_e::IS_SADDLER, false);
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

    void Followers_t::Enforce(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        // may want to have a separate flow for in combat actors

        if (Has_Follower(follower_id)) {
            Main_t& main = Main();
            Members_t& members = Members();

            some<Actor_t*> actor = Actor(follower_id);
            some<Member_ID_t> member_id = Member_ID(follower_id);

            Member_t(member_id).Tokenize(Consts_t::NPCP::Misc::Token::Follower(), follower_id() + 1);

            actor->Is_Player_Teammate(true);
        } else {
            Remove_Follower(follower_id);
        }
    }

}}
*/
