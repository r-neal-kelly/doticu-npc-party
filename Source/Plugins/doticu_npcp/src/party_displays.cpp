/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"

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

    maybe<Display_t*> Displays_t::Display(Member_t& member)
    {
        return member.Display();
    }

    maybe<Display_t*> Displays_t::Display(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            Display_t& display = Display(idx);
            if (display.Is_Active() && display.Actor() == actor) {
                return &display;
            }
        }
        return none<Display_t*>();
    }

    maybe<Display_ID_t> Displays_t::Inactive_ID()
    {
        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            Display_t& display = Display(idx);
            if (!display.Is_Active()) {
                return idx;
            }
        }
        return none<Display_ID_t>();
    }

    size_t Displays_t::Active_Count()
    {
        size_t count = 0;
        for (size_t idx = 0, end = MAX_DISPLAYS; idx < end; idx += 1) {
            if (Display(idx).Is_Active()) {
                count += 1;
            }
        }
        return count;
    }

    size_t Displays_t::Inactive_Count()
    {
        return MAX_DISPLAYS - Active_Count();
    }

    Bool_t Displays_t::Has(Member_t& member)
    {
        return member.Is_Display();
    }

    Bool_t Displays_t::Has(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return Display(actor) != none<Display_t*>();
    }

    maybe<Display_t*> Displays_t::Add(Member_t& member)
    {
        if (member.Is_Active() && !Has(member)) {
            maybe<Display_ID_t> display_id = Inactive_ID();
            if (display_id) {
                Display_t& display = Display(display_id());
                display.~Display_t();
                new (&display) Display_t(member.Member_ID(), display_id());
                if (display.Is_Active()) {
                    return &display;
                } else {
                    return none<Display_t*>();
                }
            } else {
                return none<Display_t*>();
            }
        } else {
            return none<Display_t*>();
        }
    }

    maybe<Display_t*> Displays_t::Add(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Member_t*> member = Members().Member(actor);
        if (member) {
            return Add(*member);
        } else {
            member = Members().Add(actor);
            if (member) {
                return Add(*member);
            } else {
                return none<Display_t*>();
            }
        }
    }

    Bool_t Displays_t::Remove(Display_t& display)
    {
        if (display.Is_Active()) {
            display.Reset();

            return true;
        } else {
            return false;
        }
    }

    Bool_t Displays_t::Remove(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Display_t*> display = Display(actor);
        if (display) {
            return Remove(*display);
        } else {
            return false;
        }
    }

    void Displays_t::Reset_Options()
    {
        State().save.~Save_t();
        new (&State().save) Save_t();
    }

}}
