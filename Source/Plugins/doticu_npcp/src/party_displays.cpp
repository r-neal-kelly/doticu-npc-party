/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party.h"
#include "party_displays.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Displays_t::Save_t::Save_t() :
        limit(DEFAULT_LIMIT)
    {
    }

    Displays_t::Save_t::~Save_t()
    {
    }

    void Displays_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->limit);
    }

    void Displays_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->limit);
    }

    Displays_t::State_t::State_t() :
        save(),

        displays()
    {
    }

    Displays_t::State_t::~State_t()
    {
    }

    Party_t& Displays_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Displays_t::Members()
    {
        return Party().Members();
    }

    Displays_t::Displays_t() :
        state()
    {
    }

    Displays_t::~Displays_t()
    {
    }

    void Displays_t::On_After_New_Game()
    {
        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            State().displays[idx].On_After_New_Game();
        }
    }

    void Displays_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);

        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            State().displays[idx].On_Before_Save_Game(file);
        }
    }

    void Displays_t::On_After_Save_Game()
    {
        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            State().displays[idx].On_After_Save_Game();
        }
    }

    void Displays_t::On_Before_Load_Game()
    {
        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            State().displays[idx].On_Before_Load_Game();
        }
    }

    void Displays_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            State().displays[idx].On_After_Load_Game(file);
        }
    }

    void Displays_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            State().displays[idx].On_After_Load_Game(file, version_to_update);
        }
    }

    void Displays_t::On_Update()
    {
    }

    Displays_t::State_t& Displays_t::State()
    {
        return this->state;
    }

    Displays_t::Save_t& Displays_t::Save()
    {
        return State().save;
    }

    Display_t& Displays_t::Display(some<Display_ID_t> display_id)
    {
        SKYLIB_ASSERT_SOME(display_id);

        return State().displays[display_id()];
    }

    maybe<Display_t*> Displays_t::Active_Display(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        Member_t& member = Members().Member(member_id);
        if (member.Is_Active()) {
            return member.Display();
        } else {
            return none<Display_t*>();
        }
    }

}}
