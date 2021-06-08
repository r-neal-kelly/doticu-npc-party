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

    Follower_t::Follower_t(some<Member_ID_t> member_id, some<Follower_ID_t> follower_id) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);
        SKYLIB_ASSERT_SOME(follower_id);
        SKYLIB_ASSERT(Members().Member(member_id).Is_Active());

        Paired_Member_ID(member_id);
        Members().Member(member_id).Paired_Follower_ID(follower_id);
        Party().Update_AI(member_id, Member_Update_AI_e::RESET_AI);
    }

    Follower_t::~Follower_t()
    {
        if (Is_Active()) {
            Party().Update_AI(Member_ID(), Member_Update_AI_e::RESET_AI);
            Member().Paired_Follower_ID(none<Follower_ID_t>());
        }
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

    maybe<Member_ID_t> Follower_t::Paired_Member_ID()
    {
        return Save().member_id;
    }

    void Follower_t::Paired_Member_ID(maybe<Member_ID_t> member_id)
    {
        Save().member_id = member_id;
    }

    maybe<Member_t*> Follower_t::Paired_Member()
    {
        maybe<Member_ID_t> paired_member_id = Paired_Member_ID();
        if (paired_member_id) {
            return &Members().Member(paired_member_id());
        } else {
            return none<Member_t*>();
        }
    }

    void Follower_t::Reset()
    {
        this->~Follower_t();
        new (this) Follower_t();
    }

    Bool_t Follower_t::Is_Active()
    {
        maybe<Member_t*> paired_member = Paired_Member();
        if (paired_member) {
            if (paired_member->Is_Active() && paired_member->Paired_Follower() == this) {
                return true;
            } else {
                Reset();
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Retreater()
    {
        return Save().is_retreater;
    }

    void Follower_t::Is_Retreater(Bool_t value)
    {
        Save().is_retreater = value;
    }

    Bool_t Follower_t::Is_Saddler()
    {
        return Save().is_saddler;
    }

    void Follower_t::Is_Saddler(Bool_t value)
    {
        Save().is_saddler = value;
    }

    Bool_t Follower_t::Is_Sojourner()
    {
        return Save().is_sojourner;
    }

    void Follower_t::Is_Sojourner(Bool_t value)
    {
        Save().is_sojourner = value;
    }

    some<Member_ID_t> Follower_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    some<Follower_ID_t> Follower_t::Follower_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Paired_Follower_ID()();
    }

    some<Alias_Reference_t*> Follower_t::Alias()
    {
        SKYLIB_ASSERT(Is_Active());

        return Followers().Alias(Follower_ID());
    }

    some<Actor_t*> Follower_t::Actor()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Actor();
    }

    Member_t& Follower_t::Member()
    {
        SKYLIB_ASSERT(Is_Active());

        return *Paired_Member();
    }

    void Follower_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());
    }

}}
