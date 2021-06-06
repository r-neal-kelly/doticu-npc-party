/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party.h"
#include "party_expoee.h"
#include "party_member.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Expoee_t::Save_t::Save_t() :
        member_id()
    {
    }

    Expoee_t::Save_t::~Save_t()
    {
    }

    void Expoee_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->member_id);
    }

    void Expoee_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->member_id);
    }

    Expoee_t::State_t::State_t() :
        save()
    {
    }

    Expoee_t::State_t::~State_t()
    {
    }

    Party_t& Expoee_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Expoee_t::Members()
    {
        return Party().Members();
    }

    Expoees_t& Expoee_t::Expoees()
    {
        return Party().Expoees();
    }

    Expoee_t::Expoee_t() :
        state()
    {
    }

    Expoee_t::Expoee_t(some<Member_ID_t> member_id) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);

        Save().member_id = member_id;
    }

    Expoee_t::~Expoee_t()
    {
    }

    void Expoee_t::On_After_New_Game()
    {
    }

    void Expoee_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
    }

    void Expoee_t::On_After_Save_Game()
    {
    }

    void Expoee_t::On_Before_Load_Game()
    {
    }

    void Expoee_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
    }

    void Expoee_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);
    }

    Expoee_t::State_t& Expoee_t::State()
    {
        return this->state;
    }

    Expoee_t::Save_t& Expoee_t::Save()
    {
        return State().save;
    }

    Bool_t Expoee_t::Is_Active()
    {
        return Save().member_id && Members().Member(Save().member_id()).Is_Active();
    }

    some<Member_ID_t> Expoee_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    some<Expoee_ID_t> Expoee_t::Expoee_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Expoee_ID()();
    }

    Member_t& Expoee_t::Member()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Member(Member_ID());
    }

    void Expoee_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());
    }

}}
