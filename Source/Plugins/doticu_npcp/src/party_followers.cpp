/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

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
    }

    void Followers_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_FOLLOWERS; idx < end; idx += 1) {
            State().followers[idx].On_After_Load_Game(file, version_to_update);
        }
    }

    void Followers_t::On_Update()
    {
    }

    Followers_t::State_t& Followers_t::State()
    {
        return this->state;
    }

    Followers_t::Save_t& Followers_t::Save()
    {
        return State().save;
    }

    Follower_t& Followers_t::Follower(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        return State().followers[follower_id()];
    }

    maybe<Follower_t*> Followers_t::Active_Follower(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        Member_t& member = Members().Member(member_id);
        if (member.Is_Active()) {
            return member.Follower();
        } else {
            return none<Follower_t*>();
        }
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

    Bool_t Followers_t::Remove_Follower(some<Follower_ID_t> follower_id)
    {
        SKYLIB_ASSERT_SOME(follower_id);

        // this will cleanse anything under the id that it can, even if the data is incomplete in some manner, it cleans it up.
        // it fails gracefully and just defaults the values.

        // this should forcibly reset ai and make sure other state is reset that is needed.
        return false;
    }

    some<Alias_Reference_t*> Followers_t::Alias_Reference(some<Follower_ID_t> valid_follower_id)
    {
        SKYLIB_ASSERT_SOME(valid_follower_id);
        SKYLIB_ASSERT(Has_Follower(valid_follower_id));

        some<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(valid_follower_id())();
        SKYLIB_ASSERT_SOME(alias_reference);
        return alias_reference;
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
