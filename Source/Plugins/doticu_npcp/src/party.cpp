/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/script.h"

#include "consts.h"
#include "npcp.h"
#include "party.h"
#include "party_displays.h"
#include "party_expoees.h"
#include "party_followers.h"
#include "party_member.h"
#include "party_members.h"
#include "party_settlers.inl"

namespace doticu_skylib { namespace doticu_npcp {

    Party_t::Save_t::Save_t()
    {
    }

    Party_t::Save_t::~Save_t()
    {
    }

    Party_t::State_t::State_t() :
        save(),

        members(),
        settlers(),
        expoees(),
        displays(),
        followers(),

        scripts(),
        update_ais()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            this->scripts[idx] = none<Script_t*>();
            this->update_ais[idx] = Member_Update_AI_e::RESET_AI;
        }
    }

    Party_t::State_t::~State_t()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            maybe<Script_t*> script = this->scripts[idx];
            if (script) {
                Script_t::Destroy(script());
            }
        }
    }

    void Party_t::Register_Me(some<Virtual::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        Members_t::Register_Me(machine);
        Settlers_t::Register_Me(machine);
        Expoees_t::Register_Me(machine);
        Displays_t::Register_Me(machine);
        Followers_t::Register_Me(machine);

        NPCP.On_Log("Registered Party functions.");
    }

    Bool_t Party_t::Is_Token(some<Bound_Object_t*> bound_object)
    {
        SKYLIB_ASSERT_SOME(bound_object);

        return bound_object->Is_Misc() && bound_object->form_id.Has_Mod(Consts_t::NPCP::Mod()());
    }

    Party_t::Party_t() :
        state()
    {
    }

    Party_t::~Party_t()
    {
    }

    void Party_t::On_After_New_Game()
    {
        Members().On_After_New_Game();
        Settlers().On_After_New_Game();
        Expoees().On_After_New_Game();
        Displays().On_After_New_Game();
        Followers().On_After_New_Game();
    }

    void Party_t::On_Before_Save_Game(std::ofstream& file)
    {
        if (file.write(reinterpret_cast<char*>(&State().save), sizeof(Save_t))) {
            Members().On_Before_Save_Game(file);
            Settlers().On_Before_Save_Game(file);
            Expoees().On_Before_Save_Game(file);
            Displays().On_Before_Save_Game(file);
            Followers().On_Before_Save_Game(file);
        }
    }

    void Party_t::On_After_Save_Game()
    {
        Members().On_After_Save_Game();
        Settlers().On_After_Save_Game();
        Expoees().On_After_Save_Game();
        Displays().On_After_Save_Game();
        Followers().On_After_Save_Game();
    }

    void Party_t::On_Before_Load_Game()
    {
        Members().On_Before_Load_Game();
        Settlers().On_Before_Load_Game();
        Expoees().On_Before_Load_Game();
        Displays().On_Before_Load_Game();
        Followers().On_Before_Load_Game();
    }

    void Party_t::On_After_Load_Game(std::ifstream& file)
    {
        if (file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t))) {
            Members().On_After_Load_Game(file);
            Settlers().On_After_Load_Game(file);
            Expoees().On_After_Load_Game(file);
            Displays().On_After_Load_Game(file);
            Followers().On_After_Load_Game(file);
        }
    }

    void Party_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        if (file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t))) {
            Members().On_After_Load_Game(file, version_to_update);
            Settlers().On_After_Load_Game(file, version_to_update);
            Expoees().On_After_Load_Game(file, version_to_update);
            Displays().On_After_Load_Game(file, version_to_update);
            Followers().On_After_Load_Game(file, version_to_update);
        }
    }

    void Party_t::On_Update()
    {
        Members().On_Update();
        Settlers().On_Update();
        Expoees().On_Update();
        Displays().On_Update();
        Followers().On_Update();
    }

    Party_t::State_t& Party_t::State()
    {
        return this->state;
    }

    Members_t& Party_t::Members()
    {
        return State().members;
    }

    Settlers_t& Party_t::Settlers()
    {
        return State().settlers;
    }

    Expoees_t& Party_t::Expoees()
    {
        return State().expoees;
    }

    Displays_t& Party_t::Displays()
    {
        return State().displays;
    }

    Followers_t& Party_t::Followers()
    {
        return State().followers;
    }

    some<Script_t*> Party_t::Script(some<Member_ID_t> valid_id)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_id));

        maybe<Script_t*>& script = State().scripts[valid_id()];
        if (!script) {
            script = Script_t::Create()();
            SKYLIB_ASSERT_SOME(script);
        }

        return script();
    }

    maybe<Member_Update_AI_e> Party_t::Update_AI(some<Member_ID_t> valid_id)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_id));

        return State().update_ais[valid_id()];
    }

    void Party_t::Update_AI(some<Member_ID_t> valid_id, some<Member_Update_AI_e> value)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Members().Has_Member(valid_id));
        SKYLIB_ASSERT_SOME(value);

        maybe<Member_Update_AI_e>& update_ai = State().update_ais[valid_id()];
        if (update_ai != Member_Update_AI_e::RESET_AI) {
            update_ai = value;
        }
    }

}}
