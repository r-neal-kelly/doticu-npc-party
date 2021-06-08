/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party.h"
#include "party_display.h"
#include "party_member.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Display_t::Save_t::Save_t() :
        member_id()
    {
    }

    Display_t::Save_t::~Save_t()
    {
    }

    void Display_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->member_id);
    }

    void Display_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->member_id);
    }

    Display_t::State_t::State_t() :
        save()
    {
    }

    Display_t::State_t::~State_t()
    {
    }

    Party_t& Display_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Display_t::Members()
    {
        return Party().Members();
    }

    Displays_t& Display_t::Displays()
    {
        return Party().Displays();
    }

    Display_t::Display_t() :
        state()
    {
    }

    Display_t::Display_t(some<Member_ID_t> member_id, some<Display_ID_t> display_id) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);
        SKYLIB_ASSERT_SOME(display_id);
        SKYLIB_ASSERT(Members().Member(member_id).Is_Active());

        Paired_Member_ID(member_id);
        Members().Member(member_id).Paired_Display_ID(display_id);
        Party().Update_AI(member_id, Member_Update_AI_e::RESET_AI);
    }

    Display_t::~Display_t()
    {
        if (Is_Active()) {
            Party().Update_AI(Member_ID(), Member_Update_AI_e::RESET_AI);
            Member().Paired_Display_ID(none<Display_ID_t>());
        }
    }

    void Display_t::On_After_New_Game()
    {
    }

    void Display_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
    }

    void Display_t::On_After_Save_Game()
    {
    }

    void Display_t::On_Before_Load_Game()
    {
    }

    void Display_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
    }

    void Display_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);
    }

    Display_t::State_t& Display_t::State()
    {
        return this->state;
    }

    Display_t::Save_t& Display_t::Save()
    {
        return State().save;
    }

    maybe<Member_ID_t> Display_t::Paired_Member_ID()
    {
        return Save().member_id;
    }

    void Display_t::Paired_Member_ID(maybe<Member_ID_t> member_id)
    {
        Save().member_id = member_id;
    }

    maybe<Member_t*> Display_t::Paired_Member()
    {
        maybe<Member_ID_t> paired_member_id = Paired_Member_ID();
        if (paired_member_id) {
            return &Members().Member(paired_member_id());
        } else {
            return none<Member_t*>();
        }
    }

    void Display_t::Reset()
    {
        this->~Display_t();
        new (this) Display_t();
    }

    Bool_t Display_t::Is_Active()
    {
        maybe<Member_t*> paired_member = Paired_Member();
        if (paired_member) {
            if (paired_member->Is_Active() && paired_member->Paired_Display() == this) {
                return true;
            } else {
                Reset();
                return false;
            }
        } else {
            return false;
        }
    }

    some<Member_ID_t> Display_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    some<Display_ID_t> Display_t::Display_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Paired_Display_ID()();
    }

    some<Actor_t*> Display_t::Actor()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member().Actor();
    }

    Member_t& Display_t::Member()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Member(Member_ID());
    }

    void Display_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());
    }

}}
