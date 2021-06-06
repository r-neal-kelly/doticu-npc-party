/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party.h"
#include "party_follower.h"
#include "party_member.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Follower_t::Save_t::Save_t() :
        member_id(),

        is_retreater(),
        is_saddler(),
        is_sojourner()
    {
    }

    Follower_t::Save_t::~Save_t()
    {
    }

    void Follower_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->member_id);

        NPCP.Write(file, this->is_retreater);
        NPCP.Write(file, this->is_saddler);
        NPCP.Write(file, this->is_sojourner);
    }

    void Follower_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->member_id);

        NPCP.Read(file, this->is_retreater);
        NPCP.Read(file, this->is_saddler);
        NPCP.Read(file, this->is_sojourner);
    }

    Follower_t::State_t::State_t() :
        save()
    {
    }

    Follower_t::State_t::~State_t()
    {
    }

    Party_t& Follower_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Follower_t::Members()
    {
        return Party().Members();
    }

    Followers_t& Follower_t::Followers()
    {
        return Party().Followers();
    }

    Follower_t::Follower_t() :
        state()
    {
    }

    Follower_t::Follower_t(some<Member_ID_t> member_id) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);

        Save().member_id = member_id;
    }

    Follower_t::~Follower_t()
    {
    }

    void Follower_t::On_After_New_Game()
    {
    }

    void Follower_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
    }

    void Follower_t::On_After_Save_Game()
    {
    }

    void Follower_t::On_Before_Load_Game()
    {
    }

    void Follower_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
    }

    void Follower_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);
    }

    Follower_t::State_t& Follower_t::State()
    {
        return this->state;
    }

    Follower_t::Save_t& Follower_t::Save()
    {
        return State().save;
    }

    Bool_t Follower_t::Is_Active()
    {
        return Save().member_id && Members().Member(Save().member_id()).Is_Active();
    }

    some<Member_ID_t> Follower_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    some<Follower_ID_t> Follower_t::Follower_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Follower_ID()();
    }

    Member_t& Follower_t::Member()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Member(Member_ID());
    }

    void Follower_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());
    }

}}
