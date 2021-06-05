/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include <thread>

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
        /*settlers(),
        expoees(),
        displays(),
        followers(),*/

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
        /*Settlers_t::Register_Me(machine);
        Expoees_t::Register_Me(machine);
        Displays_t::Register_Me(machine);
        Followers_t::Register_Me(machine);*/
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
        /*Settlers().On_After_New_Game();
        Expoees().On_After_New_Game();
        Displays().On_After_New_Game();
        Followers().On_After_New_Game();*/
    }

    void Party_t::On_Before_Save_Game(std::ofstream& file)
    {
        (file.write(reinterpret_cast<char*>(&State().save), sizeof(Save_t)).good()) &&
            (Members().On_Before_Save_Game(file), file.good())/* &&
            (Settlers().On_Before_Save_Game(file), file.good()) &&
            (Expoees().On_Before_Save_Game(file), file.good()) &&
            (Displays().On_Before_Save_Game(file), file.good()) &&
            (Followers().On_Before_Save_Game(file), file.good())*/;
    }

    void Party_t::On_After_Save_Game()
    {
        Members().On_After_Save_Game();
        /*Settlers().On_After_Save_Game();
        Expoees().On_After_Save_Game();
        Displays().On_After_Save_Game();
        Followers().On_After_Save_Game();*/
    }

    void Party_t::On_Before_Load_Game()
    {
        Members().On_Before_Load_Game();
        /*Settlers().On_Before_Load_Game();
        Expoees().On_Before_Load_Game();
        Displays().On_Before_Load_Game();
        Followers().On_Before_Load_Game();*/
    }

    void Party_t::On_After_Load_Game(std::ifstream& file)
    {
        (file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t)).good()) &&
            (Members().On_After_Load_Game(file), file.good())/* &&
            (Settlers().On_After_Load_Game(file), file.good()) &&
            (Expoees().On_After_Load_Game(file), file.good()) &&
            (Displays().On_After_Load_Game(file), file.good()) &&
            (Followers().On_After_Load_Game(file), file.good())*/;
    }

    void Party_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        (file.read(reinterpret_cast<char*>(&State().save), sizeof(Save_t)).good()) &&
            (Members().On_After_Load_Game(file, version_to_update), file.good())/* &&
            (Settlers().On_After_Load_Game(file, version_to_update), file.good()) &&
            (Expoees().On_After_Load_Game(file, version_to_update), file.good()) &&
            (Displays().On_After_Load_Game(file, version_to_update), file.good()) &&
            (Followers().On_After_Load_Game(file, version_to_update), file.good())*/;
    }

    void Party_t::On_Update()
    {
        Members().On_Update();
        /*Settlers().On_Update();
        Expoees().On_Update();
        Displays().On_Update();
        Followers().On_Update();*/

        Evaluate();
    }

    Party_t::State_t& Party_t::State()
    {
        return this->state;
    }

    Members_t& Party_t::Members()
    {
        return State().members;
    }

    /*Settlers_t& Party_t::Settlers()
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
    }*/

    some<Script_t*> Party_t::Script(some<Member_ID_t> valid_id)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Members().Has(valid_id));

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
        SKYLIB_ASSERT(Members().Has(valid_id));

        return State().update_ais[valid_id()];
    }

    void Party_t::Update_AI(some<Member_ID_t> valid_id, some<Member_Update_AI_e> value)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Members().Has(valid_id));
        SKYLIB_ASSERT_SOME(value);

        maybe<Member_Update_AI_e>& update_ai = State().update_ais[valid_id()];
        if (update_ai != Member_Update_AI_e::RESET_AI) {
            update_ai = value;
        }
    }

    void Party_t::Evaluate()
    {
        static std::mutex parallel_lock; // only used in rare circumstances, e.g. Member_t needs to access Members_t state

        std::thread(
            []()->void
            {
                const size_t THREAD_COUNT = 8;
                SKYLIB_ASSERT(MAX_MEMBERS % THREAD_COUNT == 0);
                SKYLIB_ASSERT(MAX_FOLLOWERS % THREAD_COUNT == 0);

                Vector_t<std::thread> threads;
                threads.reserve(THREAD_COUNT);

                // once we get Follower_t setup, we can eval those first and mark their ids as evaluated

                for (size_t m = 0; m < MAX_MEMBERS; m += THREAD_COUNT) {
                    threads.clear();
                    {
                        NPCP_t::Locker_t locker = NPCP.Locker();
                        if (NPCP.Is_Valid()) {
                            for (size_t t = 0; t < THREAD_COUNT; t += 1) {
                                some<Member_ID_t> id = m + t;
                                threads.push_back(std::thread(
                                    [id]()->void
                                    {
                                        SKYLIB_ASSERT_SOME(id);
                                        NPCP.Party().Evaluate_In_Parallel(id(), parallel_lock);
                                    }
                                ));
                            }
                            for (size_t t = 0; t < THREAD_COUNT; t += 1) {
                                if (threads[t].joinable()) {
                                    threads[t].join();
                                }
                            }
                        } else {
                            return;
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::nanoseconds(0)); // increase only if necessary
                }
            }
        ).detach();
    }

    void Party_t::Evaluate_In_Parallel(some<Member_ID_t> id, std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT_SOME(id);

        Member_t& member = Members().Member(id);
        // we'll grab all the types here, so that we can execute with precedence.

        if (member.Is_Active()) {
            member.Evaluate_In_Parallel(parallel_lock);
        }
    }

}}
