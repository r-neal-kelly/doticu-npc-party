/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/script.h"

#include "consts.h"
#include "npcp.h"
#include "party.h"
#include "party_display.h"
#include "party_expoee.h"
#include "party_follower.h"
#include "party_member.h"
#include "party_settler.h"

namespace doticu_skylib { namespace doticu_npcp {

    Party_t::Save_t::Save_t()
    {
    }

    Party_t::Save_t::~Save_t()
    {
    }

    void Party_t::Save_t::Write(std::ofstream& file)
    {
    }

    void Party_t::Save_t::Read(std::ifstream& file)
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
        Save().Write(file);

        Members().On_Before_Save_Game(file);
        Settlers().On_Before_Save_Game(file);
        Expoees().On_Before_Save_Game(file);
        Displays().On_Before_Save_Game(file);
        Followers().On_Before_Save_Game(file);
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
        Save().Read(file);

        Members().On_After_Load_Game(file);
        Settlers().On_After_Load_Game(file);
        Expoees().On_After_Load_Game(file);
        Displays().On_After_Load_Game(file);
        Followers().On_After_Load_Game(file);

        // we should validate that member ids match up across types. the source of truth is member itself.
    }

    void Party_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);

        Members().On_After_Load_Game(file, version_to_update);
        Settlers().On_After_Load_Game(file, version_to_update);
        Expoees().On_After_Load_Game(file, version_to_update);
        Displays().On_After_Load_Game(file, version_to_update);
        Followers().On_After_Load_Game(file, version_to_update);

        // we should validate that member ids match up across types. the source of truth is member itself.
    }

    void Party_t::On_Update()
    {
        Members().On_Update();
        Settlers().On_Update();
        Expoees().On_Update();
        Displays().On_Update();
        Followers().On_Update();

        Evaluate();
    }

    Party_t::State_t& Party_t::State()
    {
        return this->state;
    }

    Party_t::Save_t& Party_t::Save()
    {
        return State().save;
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

    some<Script_t*> Party_t::Script(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        maybe<Script_t*>& script = State().scripts[member_id()];
        if (!script) {
            script = Script_t::Create()();
            SKYLIB_ASSERT_SOME(script);
        }

        return script();
    }

    void Party_t::Update_AI(some<Member_ID_t> member_id, some<Member_Update_AI_e> value)
    {
        SKYLIB_ASSERT_SOME(member_id);
        SKYLIB_ASSERT_SOME(value);

        maybe<Member_Update_AI_e>& update_ai = State().update_ais[member_id()];
        if (update_ai != Member_Update_AI_e::RESET_AI) {
            update_ai = value;
        }
    }

    void Party_t::Evaluate()
    {
        static std::mutex parallel_lock;

        static auto Try_Spawn_Thread = [](Vector_t<std::thread>& threads,
                                          Bool_t* evaluated_member_ids,
                                          some<Member_ID_t> member_id)->Bool_t
        {
            if (!evaluated_member_ids[member_id()]) {
                evaluated_member_ids[member_id()] = true;
                threads.push_back(std::thread(
                    [member_id]()->void
                    {
                        NPCP.Party().Evaluate_In_Parallel(member_id, parallel_lock);
                    }
                ));
                return true;
            } else {
                return false;
            }
        };

        static auto Await_Threads = [](Vector_t<std::thread>& threads)->void
        {
            for (size_t idx = 0, end = threads.size(); idx < end; idx += 1) {
                if (threads[idx].joinable()) {
                    threads[idx].join();
                }
            }
        };

        std::thread(
            []()->void
            {
                const size_t THREAD_COUNT = 8;
                Vector_t<std::thread> threads;
                threads.reserve(THREAD_COUNT);

                Bool_t evaluated_member_ids[MAX_MEMBERS] = { false };

                for (size_t id = 0; id < MAX_DISPLAYS;) {
                    {
                        NPCP_t::Locker_t locker = NPCP.Locker();
                        if (NPCP.Is_Valid()) {
                            for (size_t t = 0; t < THREAD_COUNT && id < MAX_DISPLAYS; id += 1) {
                                Display_t& display = NPCP.Party().Displays().Display(id);
                                if (display.Is_Active()) {
                                    if (Try_Spawn_Thread(threads, evaluated_member_ids, display.Member_ID())) {
                                        t += 1;
                                    }
                                }
                            }
                            Await_Threads(threads);
                        }
                    }
                    threads.clear();
                }

                for (size_t id = 0; id < MAX_FOLLOWERS;) {
                    {
                        NPCP_t::Locker_t locker = NPCP.Locker();
                        if (NPCP.Is_Valid()) {
                            for (size_t t = 0; t < THREAD_COUNT && id < MAX_FOLLOWERS; id += 1) {
                                Follower_t& follower = NPCP.Party().Followers().Follower(id);
                                if (follower.Is_Active()) {
                                    if (Try_Spawn_Thread(threads, evaluated_member_ids, follower.Member_ID())) {
                                        t += 1;
                                    }
                                }
                            }
                            Await_Threads(threads);
                        }
                    }
                    threads.clear();
                }

                for (size_t id = 0; id < MAX_MEMBERS;) {
                    {
                        NPCP_t::Locker_t locker = NPCP.Locker();
                        if (NPCP.Is_Valid()) {
                            for (size_t t = 0; t < THREAD_COUNT && id < MAX_MEMBERS; id += 1) {
                                Member_t& member = NPCP.Party().Members().Member(id);
                                if (member.Is_Active()) {
                                    if (Try_Spawn_Thread(threads, evaluated_member_ids, member.Member_ID())) {
                                        t += 1;
                                    }
                                }
                            }
                            Await_Threads(threads);
                        }
                    }
                    threads.clear();
                }
            }
        ).detach();
    }

    void Party_t::Evaluate_In_Parallel(some<Member_ID_t> id, std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT_SOME(id);

        Member_t& member = Members().Member(id);
        if (member.Is_Active()) {
            some<Actor_t*> actor = member.Actor();
            Write_Locker_t locker(actor->x_list.lock);

            member.Evaluate_In_Parallel(parallel_lock);
            maybe<Display_t*> display = member.Display();
            if (display) {
                display->Evaluate_In_Parallel(parallel_lock);
            } else {
                maybe<Follower_t*> follower = member.Follower();
                if (follower) {
                    follower->Evaluate_In_Parallel(parallel_lock);
                } else {
                    maybe<Expoee_t*> expoee = member.Expoee();
                    if (expoee) {
                        expoee->Evaluate_In_Parallel(parallel_lock);
                    } else {
                        maybe<Settler_t*> settler = member.Settler();
                        if (settler) {
                            settler->Evaluate_In_Parallel(parallel_lock);
                        }
                    }
                }
            }

            maybe<Member_Update_AI_e>& update_ai = State().update_ais[member.Member_ID()()];
            if (update_ai == Member_Update_AI_e::RESET_AI) {
                actor->Evaluate_Package(false, true);
            } else if (update_ai == Member_Update_AI_e::EVALUATE_PACKAGE) {
                actor->Evaluate_Package(false, false);
            }
            update_ai = Member_Update_AI_e::_NONE_;
        }
    }

}}
