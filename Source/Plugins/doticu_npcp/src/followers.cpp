/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "follower.h"
#include "followers.h"
#include "member.h"
#include "object_ref.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Followers {

    #define SEND_FOLLOWERS()                                                        \
    M                                                                               \
        for (u64 idx = 0, size = vec_followers.size(); idx < size; idx += 1) {      \
            Follower_t *follower = vec_followers[idx];                              \
            Papyrus::Handle follower_handle(kFormType_Alias, follower);             \
            follower_handle.Registry()->QueueEvent(follower_handle, &name, &args);  \
        }                                                                           \
    W

    static void Send_Followers(std::vector<Follower_t *> vec_followers, const char *event_name) {
        if (vec_followers.size() < 1 || !event_name || !event_name[0]) {
            return;
        }

        BSFixedString name(event_name);
        struct Args : public IFunctionArguments {
            bool Copy(Output *output) { return true; }
        } args;

        SEND_FOLLOWERS();
    }

    static void Send_Followers(std::vector<Follower_t *> vec_followers, const char *event_name, TESForm *tasklist) {
        if (vec_followers.size() < 1 || !event_name || !event_name[0]) {
            return;
        }

        BSFixedString name(event_name);
        struct Args : public IFunctionArguments {
            TESForm *m_tasklist;
            Args(TESForm *tasklist) {
                m_tasklist = tasklist;
            }
            bool Copy(Output *output) {
                output->Resize(1);
                if (m_tasklist) {
                    PackValue<TESForm>(output->Get(0), &m_tasklist, (*g_skyrimVM)->GetClassRegistry());
                } else {
                    output->Get(0)->SetNone();
                }

                return true;
            }
        } args(tasklist);

        SEND_FOLLOWERS();
    }

    void Register(Followers_t *followers) {
        if (followers) {
            Send_Followers(Get(followers), "f_Register");
        }
    }

    void Summon(std::vector<Follower_t *> vec_followers, float distance, float angle_degree, float interval_degree) {
        if (vec_followers.size() < 1) {
            return;
        }

        u64 idx_followers;
        float angle_odd;
        float angle_even;
        if (vec_followers.size() % 2 != 0) {
            Follower_t *follower = vec_followers[0];
            if (follower) {
                Follower::Summon(vec_followers[0], distance, angle_degree);
            }
            idx_followers = 1;
            angle_odd = angle_degree - interval_degree;
            angle_even = angle_degree + interval_degree;
        } else {
            float interval_half = interval_degree / 2;
            idx_followers = 0;
            angle_odd = angle_degree - interval_half;
            angle_even = angle_degree + interval_half;
        }

        for (u64 idx = idx_followers, size = vec_followers.size(); idx < size; idx += 1) {
            Follower_t *follower = vec_followers[idx];
            if (!follower) {
                continue;
            }

            if (idx % 2 == 0) {
                Follower::Summon(follower, distance, angle_even);
                angle_even += interval_degree;
            } else {
                Follower::Summon(follower, distance, angle_odd);
                angle_odd -= interval_degree;
            }
        }
    }

    void Summon(Followers_t *followers, float distance, float angle_degree, float interval_degree) {
        if (!followers) {
            return;
        }

        std::vector<Follower_t *> vec_followers = Get(followers);
        if (vec_followers.size() < 1) {
            return;
        }

        Summon(vec_followers, distance, angle_degree, interval_degree);
    }

    void Summon_Mobile(Followers_t *followers, float distance, float angle_degree, float interval_degree) {
        if (!followers) {
            return;
        }

        std::vector<Follower_t *> vec_followers = Get_Mobile(followers);
        if (vec_followers.size() < 1) {
            return;
        }

        Summon(vec_followers, distance, angle_degree, interval_degree);
    }

    void Summon_Immobile(Followers_t *followers, float distance, float angle_degree, float interval_degree) {
        if (!followers) {
            return;
        }

        std::vector<Follower_t *> vec_followers = Get_Immobile(followers);
        if (vec_followers.size() < 1) {
            return;
        }

        Summon(vec_followers, distance, angle_degree, interval_degree);
    }

    void Catch_Up(Followers_t *followers) {
        if (!followers) {
            return;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (!Follower::Exists(follower)) {
                continue;
            }

            Follower::Catch_Up(follower);
        }
    }

    void Stash(Followers_t *followers) {
        if (!followers) {
            return;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            Member_t *member = Follower::Get_Member(follower);
            if (!member) {
                continue;
            }

            TESObjectREFR *pack = Member::Get_Pack(member);
            if (!pack) {
                continue;
            }

            Object_Ref::Categorize(pack);
        }
    }

    void Enforce(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get(followers), "On_Followers_Enforce", tasklist);
        }
    }

    void Resurrect(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Dead(followers), "On_Followers_Resurrect", tasklist);
        }
    }

    void Mobilize(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Immobile(followers), "On_Followers_Mobilize", tasklist);
        }
    }

    void Immobilize(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Mobile(followers), "On_Followers_Immobilize", tasklist);
        }
    }

    void Settle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get(followers), "On_Followers_Settle", tasklist);
        }
    }

    void Unsettle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Settlers(followers), "On_Followers_Unsettle", tasklist);
        }
    }

    void Sneak(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Non_Sneaks(followers), "On_Followers_Sneak", tasklist);
        }
    }

    void Unsneak(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Sneaks(followers), "On_Followers_Unsneak", tasklist);
        }
    }

    void Saddle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Non_Saddlers(followers), "On_Followers_Saddle", tasklist);
        }
    }

    void Unsaddle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Saddlers(followers), "On_Followers_Unsaddle", tasklist);
        }
    }

    void Retreat(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Non_Retreaters(followers), "On_Followers_Retreat", tasklist);
        }
    }

    void Unretreat(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get_Retreaters(followers), "On_Followers_Unretreat", tasklist);
        }
    }

    void Unfollow(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get(followers), "On_Followers_Unfollow", tasklist);
        }
    }

    void Unmember(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send_Followers(Get(followers), "On_Followers_Unmember", tasklist);
        }
    }

    #define GET_COUNT(TEST_FOR_FOLLOWER)                                            \
    M                                                                               \
        if (!followers) {                                                           \
            return -1;                                                              \
        }                                                                           \
                                                                                    \
        SInt32 count = 0;                                                           \
        Follower_t *follower;                                                       \
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {  \
            followers->aliases.GetNthItem(idx, follower);                           \
            if (!follower) {                                                        \
                continue;                                                           \
            }                                                                       \
                                                                                    \
            if (Follower::Is_Created(follower) &&                                   \
                Follower::Get_Actor(follower) &&                                    \
                TEST_FOR_FOLLOWER) {                                                \
                count += 1;                                                         \
            }                                                                       \
        }                                                                           \
                                                                                    \
        return count;                                                               \
    W

    SInt32 Get_Count(Followers_t *followers) {
        GET_COUNT(true);
    }

    SInt32 Get_Alive_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Alive(follower));
    }

    SInt32 Get_Dead_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Dead(follower));
    }

    SInt32 Get_Mobile_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Mobile(follower));
    }

    SInt32 Get_Immobile_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Immobile(follower));
    }

    SInt32 Get_Settler_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Settler(follower));
    }

    SInt32 Get_Non_Settler_Count(Followers_t *followers) {
        GET_COUNT(Follower::Isnt_Settler(follower));
    }

    SInt32 Get_Sneak_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Sneak(follower));
    }

    SInt32 Get_Non_Sneak_Count(Followers_t *followers) {
        GET_COUNT(Follower::Isnt_Sneak(follower));
    }

    SInt32 Get_Saddler_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Saddler(follower));
    }

    SInt32 Get_Non_Saddler_Count(Followers_t *followers) {
        GET_COUNT(Follower::Isnt_Saddler(follower));
    }

    SInt32 Get_Retreater_Count(Followers_t *followers) {
        GET_COUNT(Follower::Is_Retreater(follower));
    }

    SInt32 Get_Non_Retreater_Count(Followers_t *followers) {
        GET_COUNT(Follower::Isnt_Retreater(follower));
    }

    #define GET(TEST_FOR_FOLLOWER)                                                  \
    M                                                                               \
        VMResultArray<Follower_t *> vec_followers;                                  \
                                                                                    \
        if (!followers) {                                                           \
            return vec_followers;                                                   \
        }                                                                           \
                                                                                    \
        Follower_t *follower;                                                       \
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {  \
            followers->aliases.GetNthItem(idx, follower);                           \
            if (!follower) {                                                        \
                continue;                                                           \
            }                                                                       \
                                                                                    \
            if (Follower::Is_Created(follower) &&                                   \
                Follower::Get_Actor(follower) &&                                    \
                TEST_FOR_FOLLOWER) {                                                \
                vec_followers.push_back(follower);                                  \
            }                                                                       \
        }                                                                           \
                                                                                    \
        return vec_followers;                                                       \
    W

    VMResultArray<Follower_t *> Get(Followers_t *followers) {
        GET(true);
    }

    VMResultArray<Follower_t *> Get_Alive(Followers_t *followers) {
        GET(Follower::Is_Alive(follower));
    }

    VMResultArray<Follower_t *> Get_Dead(Followers_t *followers) {
        GET(Follower::Is_Dead(follower));
    }

    VMResultArray<Follower_t *> Get_Mobile(Followers_t *followers) {
        GET(Follower::Is_Mobile(follower));
    }

    VMResultArray<Follower_t *> Get_Immobile(Followers_t *followers) {
        GET(Follower::Is_Immobile(follower));
    }

    VMResultArray<Follower_t *> Get_Settlers(Followers_t *followers) {
        GET(Follower::Is_Settler(follower));
    }

    VMResultArray<Follower_t *> Get_Non_Settlers(Followers_t *followers) {
        GET(Follower::Isnt_Settler(follower));
    }

    VMResultArray<Follower_t *> Get_Sneaks(Followers_t *followers) {
        GET(Follower::Is_Sneak(follower));
    }

    VMResultArray<Follower_t *> Get_Non_Sneaks(Followers_t *followers) {
        GET(Follower::Isnt_Sneak(follower));
    }

    VMResultArray<Follower_t *> Get_Saddlers(Followers_t *followers) {
        GET(Follower::Is_Saddler(follower));
    }

    VMResultArray<Follower_t *> Get_Non_Saddlers(Followers_t *followers) {
        GET(Follower::Isnt_Saddler(follower));
    }

    VMResultArray<Follower_t *> Get_Retreaters(Followers_t *followers) {
        GET(Follower::Is_Retreater(follower));
    }

    VMResultArray<Follower_t *> Get_Non_Retreaters(Followers_t *followers) {
        GET(Follower::Isnt_Retreater(follower));
    }

    bool Are_In_Combat(Followers_t *followers) {
        if (!followers) {
            return false;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            Actor *actor = Follower::Get_Actor(follower);
            if (actor && actor->IsInCombat()) {
                return true;
            }
        }

        return false;
    }

    Followers_t *Get_Self() {
        static Followers_t *followers = nullptr;

        if (!followers) {
            DataHandler *data_handler = DataHandler::GetSingleton();
            if (!data_handler) {
                _MESSAGE("Followers::Get_Self: Unable to get data_handler.");
                return nullptr;
            }

            const ModInfo *mod_info = data_handler->LookupModByName("doticu_npc_party.esp");
            if (!mod_info) {
                _MESSAGE("Followers::Get_Self: Unable to get mod_info.");
                return nullptr;
            }

            TESForm *form = LookupFormByID(mod_info->GetFormID(0x000D83));
            if (!form) {
                _MESSAGE("Followers::Get_Self: Unable to get quest form.");
                return nullptr;
            }

            TESQuest *quest = DYNAMIC_CAST(form, TESForm, TESQuest);
            if (!quest) {
                _MESSAGE("Followers::Get_Self: Unable to get quest.");
                return nullptr;
            }

            followers = quest;
        }

        return followers;
    }

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, void>(
                "p_Register",
                "doticu_npcp_followers",
                Followers::Register,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <Followers_t, void, float, float, float>(
                "p_Summon",
                "doticu_npcp_followers",
                Followers::Summon,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <Followers_t, void, float, float, float>(
                "p_Summon_Mobile",
                "doticu_npcp_followers",
                Followers::Summon_Mobile,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <Followers_t, void, float, float, float>(
                "p_Summon_Immobile",
                "doticu_npcp_followers",
                Followers::Summon_Immobile,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, void>(
                "p_Catch_Up",
                "doticu_npcp_followers",
                Followers::Catch_Up,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, void>(
                "p_Stash",
                "doticu_npcp_followers",
                Followers::Stash,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Enforce",
                "doticu_npcp_followers",
                Followers::Enforce,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Resurrect",
                "doticu_npcp_followers",
                Followers::Resurrect,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Mobilize",
                "doticu_npcp_followers",
                Followers::Mobilize,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Immobilize",
                "doticu_npcp_followers",
                Followers::Immobilize,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Settle",
                "doticu_npcp_followers",
                Followers::Settle,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Unsettle",
                "doticu_npcp_followers",
                Followers::Unsettle,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Sneak",
                "doticu_npcp_followers",
                Followers::Sneak,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Unsneak",
                "doticu_npcp_followers",
                Followers::Unsneak,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Saddle",
                "doticu_npcp_followers",
                Followers::Saddle,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Unsaddle",
                "doticu_npcp_followers",
                Followers::Unsaddle,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Retreat",
                "doticu_npcp_followers",
                Followers::Retreat,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Unretreat",
                "doticu_npcp_followers",
                Followers::Unretreat,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Unfollow",
                "doticu_npcp_followers",
                Followers::Unfollow,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Followers_t, void, TESForm *>(
                "p_Unmember",
                "doticu_npcp_followers",
                Followers::Unmember,
                registry)
        );

        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Count",
                "doticu_npcp_followers",
                Followers::Get_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Alive_Count",
                "doticu_npcp_followers",
                Followers::Get_Alive_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Dead_Count",
                "doticu_npcp_followers",
                Followers::Get_Dead_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Mobile_Count",
                "doticu_npcp_followers",
                Followers::Get_Mobile_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Immobile_Count",
                "doticu_npcp_followers",
                Followers::Get_Immobile_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Settler_Count",
                "doticu_npcp_followers",
                Followers::Get_Settler_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Non_Settler_Count",
                "doticu_npcp_followers",
                Followers::Get_Non_Settler_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Sneak_Count",
                "doticu_npcp_followers",
                Followers::Get_Sneak_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Non_Sneak_Count",
                "doticu_npcp_followers",
                Followers::Get_Non_Sneak_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Saddler_Count",
                "doticu_npcp_followers",
                Followers::Get_Saddler_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Non_Saddler_Count",
                "doticu_npcp_followers",
                Followers::Get_Non_Saddler_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Retreater_Count",
                "doticu_npcp_followers",
                Followers::Get_Retreater_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, SInt32>(
                "Get_Non_Retreater_Count",
                "doticu_npcp_followers",
                Followers::Get_Non_Retreater_Count,
                registry)
        );

        registry->RegisterFunction(
            new NativeFunction0 <Followers_t, bool>(
                "Are_In_Combat",
                "doticu_npcp_followers",
                Followers::Are_In_Combat,
                registry)
        );

        _MESSAGE("Added Followers functions.");

        return true;
    }

}}}
