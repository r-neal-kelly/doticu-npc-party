/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_list.h"
#include "doticu_skylib/reference.h"

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

    Settler_t::Settler_t(some<Member_ID_t> member_id, some<Settler_ID_t> settler_id) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);
        SKYLIB_ASSERT_SOME(settler_id);
        SKYLIB_ASSERT(Members().Member(member_id).Is_Active());

        Paired_Member_ID(member_id);
        Members().Member(member_id).Paired_Settler_ID(settler_id);
        Party().Update_AI(member_id, Member_Update_AI_e::RESET_AI);
    }

    Settler_t::~Settler_t()
    {
        if (Is_Active()) {
            Party().Update_AI(Member_ID(), Member_Update_AI_e::RESET_AI);
            Member().Paired_Settler_ID(none<Settler_ID_t>());
        }
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

    maybe<Member_ID_t> Settler_t::Paired_Member_ID()
    {
        return Save().member_id;
    }

    void Settler_t::Paired_Member_ID(maybe<Member_ID_t> member_id)
    {
        Save().member_id = member_id;
    }

    maybe<Member_t*> Settler_t::Paired_Member()
    {
        maybe<Member_ID_t> paired_member_id = Paired_Member_ID();
        if (paired_member_id) {
            return &Members().Member(paired_member_id());
        } else {
            return none<Member_t*>();
        }
    }

    void Settler_t::Reset()
    {
        this->~Settler_t();
        new (this) Settler_t();
    }

    Bool_t Settler_t::Is_Active()
    {
        maybe<Member_t*> paired_member = Paired_Member();
        if (paired_member) {
            if (paired_member->Is_Active() && paired_member->Paired_Settler() == this) {
                return true;
            } else {
                Reset();
                return false;
            }
        } else {
            return false;
        }
    }

    some<Member_ID_t> Settler_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    some<Settler_ID_t> Settler_t::Settler_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Paired_Settler_ID()();
    }

    some<Actor_t*> Settler_t::Actor()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Actor();
    }

    Member_t& Settler_t::Member()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Member(Member_ID());
    }

    some<Reference_t*> Settler_t::Marker()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Reference_t*> marker = Consts_t::NPCP::Form_List::Settler_Markers()->Static_At(Settler_ID()())->As_Reference()();
        SKYLIB_ASSERT(marker);

        return marker();
    }

    Settler_Slot_t& Settler_t::Slot(some<Settler_Slot_ID_t> slot_id)
    {
        SKYLIB_ASSERT(Is_Active());

        return State().slots[slot_id()];
    }

    Vector_t<some<Settler_Slot_t*>> Settler_t::Active_Slots()
    {
        Vector_t<some<Settler_Slot_t*>> active_slots;
        active_slots.reserve(8);

        for (size_t idx = 0; idx < MAX_SETTLER_SLOTS; idx += 1) {
            if (State().slots[idx].Is_Active()) {
                active_slots.push_back(&State().slots[idx]);
            }
        }

        /*active_slots.Sort(
            [](some<Settler_Slot_t*>& a, some<Settler_Slot_t*>& b)->Int_t
            {
                return a.start.In_Minutes() - b.start.In_Minutes();
            }
        );*/

        /*const size_t time_count = times.size();
        if (time_count > 1) {
            const size_t last_idx = time_count - 1;
            for (size_t idx = 0, end = last_idx; idx < end; idx += 1) {
                some<Settler_Time_t>& a = times[idx];
                some<Settler_Time_t>& b = times[idx + 1];
                if (a.stop.In_Minutes() > b.start.In_Minutes()) {
                    a.stop = b.start;
                }
            }
            some<Settler_Time_t>& a = times[last_idx];
            some<Settler_Time_t>& b = times[0];
            if (a.stop.In_Minutes() > b.start.In_Minutes()) {
                a.stop = b.start;
            }
        }*/

        return std::move(active_slots);
    }

    Vector_t<some<Settler_Time_t>> Settler_t::Interpolate_Slot_Times(const Vector_t<some<Settler_Slot_t*>>& active_slots)
    {

    }

    void Settler_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());
    }

}}
