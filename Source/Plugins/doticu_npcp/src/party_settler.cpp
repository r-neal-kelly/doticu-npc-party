/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party.h"
#include "party_member.h"
#include "party_members.h"
#include "party_settler.h"

namespace doticu_skylib { namespace doticu_npcp {

    Settler_t::Save_t::Save_t() :
        member_id()
    {
    }

    Settler_t::Save_t::~Save_t()
    {
    }

    void Settler_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->member_id);
    }

    void Settler_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->member_id);
    }

    Settler_t::State_t::State_t() :
        save(),

        slots()
    {
    }

    Settler_t::State_t::~State_t()
    {
    }

    Party_t& Settler_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Settler_t::Members()
    {
        return Party().Members();
    }

    Settlers_t& Settler_t::Settlers()
    {
        return Party().Settlers();
    }

    Settler_t::Settler_t() :
        state()
    {
    }

    Settler_t::Settler_t(some<Member_ID_t> member_id) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);

        Save().member_id = member_id;
    }

    Settler_t::~Settler_t()
    {
    }

    void Settler_t::On_After_New_Game()
    {
        for (size_t idx = 0, end = MAX_SETTLER_SLOTS; idx < end; idx += 1) {
            State().slots[idx].On_After_New_Game();
        }
    }

    void Settler_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        for (size_t idx = 0, end = MAX_SETTLER_SLOTS; idx < end; idx += 1) {
            State().slots[idx].On_Before_Save_Game(file);
        }
    }

    void Settler_t::On_After_Save_Game()
    {
        for (size_t idx = 0, end = MAX_SETTLER_SLOTS; idx < end; idx += 1) {
            State().slots[idx].On_After_Save_Game();
        }
    }

    void Settler_t::On_Before_Load_Game()
    {
        for (size_t idx = 0, end = MAX_SETTLER_SLOTS; idx < end; idx += 1) {
            State().slots[idx].On_Before_Load_Game();
        }
    }

    void Settler_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_SETTLER_SLOTS; idx < end; idx += 1) {
            State().slots[idx].On_After_Load_Game(file);
        }
    }

    void Settler_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_SETTLER_SLOTS; idx < end; idx += 1) {
            State().slots[idx].On_After_Load_Game(file, version_to_update);
        }
    }

    Settler_t::State_t& Settler_t::State()
    {
        return this->state;
    }

    Settler_t::Save_t& Settler_t::Save()
    {
        return State().save;
    }

    Bool_t Settler_t::Is_Active()
    {
        return Save().member_id && Members().Member(Save().member_id()).Is_Active();
    }

    some<Member_ID_t> Settler_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    some<Settler_ID_t> Settler_t::Settler_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Settler_ID()();
    }

    Member_t& Settler_t::Member()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Member(Member_ID());
    }

    Settler_Slot_t& Settler_t::Slot(some<Settler_Slot_ID_t> slot_id)
    {
        SKYLIB_ASSERT(Is_Active());

        return State().slots[slot_id()];
    }

    void Settler_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());
    }

}}
