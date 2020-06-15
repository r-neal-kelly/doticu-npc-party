/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <mutex>
#include <chrono>

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"

#include "actor2.h"
#include "aliases.h"
#include "follower.h"
#include "followers.h"
#include "game.h"
#include "member.h"
#include "object_ref.h"
#include "papyrus.h"
#include "utils.h"

namespace doticu_npcp { namespace Followers {

    static std::recursive_timed_mutex lock;

    // ForceRefTo is found and callable on TESQuest
    // Clear might be unlabeled on the virtual table of BGSBaseAlias

    #define SEND(NAME_, ARGS_)                                                      \
    M                                                                               \
        BSFixedString name(NAME_);                                                  \
        for (u64 idx = 0, size = vec_followers.size(); idx < size; idx += 1) {      \
            Follower_t *follower = vec_followers[idx];                              \
            Papyrus::Handle follower_handle(kFormType_Alias, follower);             \
            follower_handle.Registry()->QueueEvent(follower_handle, &name, &ARGS_); \
        }                                                                           \
    W

    static void Send(std::vector<Follower_t *> vec_followers, const char *event_name) {
        if (vec_followers.size() < 1 || !event_name || !event_name[0]) {
            return;
        }
        
        struct Args : public IFunctionArguments {
            bool Copy(Output *output) { return true; }
        } args;

        SEND(event_name, args);
    }

    static void Send(std::vector<Follower_t *> vec_followers, const char *event_name, TESForm *tasklist) {
        if (vec_followers.size() < 1 || !event_name || !event_name[0]) {
            return;
        }

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

        SEND(event_name, args);
    }

    #undef SEND

    void Register(Followers_t *followers) {
        if (followers) {
            Send(All(followers), "f_Register");
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

        std::vector<Follower_t *> vec_followers = All(followers);
        if (vec_followers.size() < 1) {
            return;
        }

        Summon(vec_followers, distance, angle_degree, interval_degree);
    }

    void Summon_Mobile(Followers_t *followers, float distance, float angle_degree, float interval_degree) {
        if (!followers) {
            return;
        }

        std::vector<Follower_t *> vec_followers = Mobile(followers);
        if (vec_followers.size() < 1) {
            return;
        }

        Summon(vec_followers, distance, angle_degree, interval_degree);
    }

    void Summon_Immobile(Followers_t *followers, float distance, float angle_degree, float interval_degree) {
        if (!followers) {
            return;
        }

        std::vector<Follower_t *> vec_followers = Immobile(followers);
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
        for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1) {
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
        for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1) {
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
            Send(All(followers), "On_Followers_Enforce", tasklist);
        }
    }

    void Resurrect(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Dead(followers), "On_Followers_Resurrect", tasklist);
        }
    }

    void Mobilize(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Immobile(followers), "On_Followers_Mobilize", tasklist);
        }
    }

    void Immobilize(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Mobile(followers), "On_Followers_Immobilize", tasklist);
        }
    }

    void Settle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(All(followers), "On_Followers_Settle", tasklist);
        }
    }

    void Unsettle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Settlers(followers), "On_Followers_Unsettle", tasklist);
        }
    }

    void Sneak(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Non_Sneaks(followers), "On_Followers_Sneak", tasklist);
        }
    }

    void Unsneak(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Sneaks(followers), "On_Followers_Unsneak", tasklist);
        }
    }

    void Saddle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Non_Saddlers(followers), "On_Followers_Saddle", tasklist);
        }
    }

    void Unsaddle(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Saddlers(followers), "On_Followers_Unsaddle", tasklist);
        }
    }

    void Retreat(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Non_Retreaters(followers), "On_Followers_Retreat", tasklist);
        }
    }

    void Unretreat(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(Retreaters(followers), "On_Followers_Unretreat", tasklist);
        }
    }

    void Unfollow(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(All(followers), "On_Followers_Unfollow", tasklist);
        }
    }

    void Unmember(Followers_t *followers, TESForm *tasklist) {
        if (followers) {
            Send(All(followers), "On_Followers_Unmember", tasklist);
        }
    }

    SInt32 Max(Followers_t *followers)
    {
        return Followers::MAX;
    }

    #define COUNT(TEST_FOR_FOLLOWER)                                        \
    M                                                                       \
        if (!followers) {                                                   \
            return -1;                                                      \
        }                                                                   \
                                                                            \
        SInt32 count = 0;                                                   \
        Follower_t *follower;                                               \
        for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1) {    \
            followers->aliases.GetNthItem(idx, follower);                   \
            if (!follower) {                                                \
                continue;                                                   \
            }                                                               \
                                                                            \
            if (Follower::Is_Created(follower) &&                           \
                Follower::Get_Actor(follower) &&                            \
                TEST_FOR_FOLLOWER(follower)) {                              \
                count += 1;                                                 \
            }                                                               \
        }                                                                   \
                                                                            \
        return count;                                                       \
    W

    SInt32 Count_All(Followers_t *followers)
    {
        PRAGMA_PUSH_WARNING_DISABLE(4003);
        COUNT();
        PRAGMA_POP_WARNING();
    }

    SInt32 Count_Alive(Followers_t *followers) {
        COUNT(Follower::Is_Alive);
    }

    SInt32 Count_Dead(Followers_t *followers) {
        COUNT(Follower::Is_Dead);
    }

    SInt32 Count_Mobile(Followers_t *followers) {
        COUNT(Follower::Is_Mobile);
    }

    SInt32 Count_Immobile(Followers_t *followers) {
        COUNT(Follower::Is_Immobile);
    }

    SInt32 Count_Settlers(Followers_t *followers) {
        COUNT(Follower::Is_Settler);
    }

    SInt32 Count_Non_Settlers(Followers_t *followers) {
        COUNT(Follower::Isnt_Settler);
    }

    SInt32 Count_Sneaks(Followers_t *followers) {
        COUNT(Follower::Is_Sneak);
    }

    SInt32 Count_Non_Sneaks(Followers_t *followers) {
        COUNT(Follower::Isnt_Sneak);
    }

    SInt32 Count_Saddlers(Followers_t *followers) {
        COUNT(Follower::Is_Saddler);
    }

    SInt32 Count_Non_Saddlers(Followers_t *followers) {
        COUNT(Follower::Isnt_Saddler);
    }

    SInt32 Count_Retreaters(Followers_t *followers) {
        COUNT(Follower::Is_Retreater);
    }

    SInt32 Count_Non_Retreaters(Followers_t *followers) {
        COUNT(Follower::Isnt_Retreater);
    }

    #undef COUNT

    #define COPY(TEST_FOR_FOLLOWER)                                         \
    M                                                                       \
        VMResultArray<Follower_t *> vec_followers;                          \
                                                                            \
        if (!followers) {                                                   \
            return vec_followers;                                           \
        }                                                                   \
                                                                            \
        Follower_t *follower;                                               \
        for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1) {    \
            followers->aliases.GetNthItem(idx, follower);                   \
            if (!follower) {                                                \
                continue;                                                   \
            }                                                               \
                                                                            \
            if (Follower::Is_Created(follower) &&                           \
                Follower::Get_Actor(follower) &&                            \
                TEST_FOR_FOLLOWER(follower)) {                              \
                vec_followers.push_back(follower);                          \
            }                                                               \
        }                                                                   \
                                                                            \
        return vec_followers;                                               \
    W

    VMResultArray<Follower_t *> All(Followers_t *followers) {
        PRAGMA_PUSH_WARNING_DISABLE(4003);
        COPY();
        PRAGMA_POP_WARNING();
    }

    VMResultArray<Follower_t *> Alive(Followers_t *followers) {
        COPY(Follower::Is_Alive);
    }

    VMResultArray<Follower_t *> Dead(Followers_t *followers) {
        COPY(Follower::Is_Dead);
    }

    VMResultArray<Follower_t *> Mobile(Followers_t *followers) {
        COPY(Follower::Is_Mobile);
    }

    VMResultArray<Follower_t *> Immobile(Followers_t *followers) {
        COPY(Follower::Is_Immobile);
    }

    VMResultArray<Follower_t *> Settlers(Followers_t *followers) {
        COPY(Follower::Is_Settler);
    }

    VMResultArray<Follower_t *> Non_Settlers(Followers_t *followers) {
        COPY(Follower::Isnt_Settler);
    }

    VMResultArray<Follower_t *> Sneaks(Followers_t *followers) {
        COPY(Follower::Is_Sneak);
    }

    VMResultArray<Follower_t *> Non_Sneaks(Followers_t *followers) {
        COPY(Follower::Isnt_Sneak);
    }

    VMResultArray<Follower_t *> Saddlers(Followers_t *followers) {
        COPY(Follower::Is_Saddler);
    }

    VMResultArray<Follower_t *> Non_Saddlers(Followers_t *followers) {
        COPY(Follower::Isnt_Saddler);
    }

    VMResultArray<Follower_t *> Retreaters(Followers_t *followers) {
        COPY(Follower::Is_Retreater);
    }

    VMResultArray<Follower_t *> Non_Retreaters(Followers_t *followers) {
        COPY(Follower::Isnt_Retreater);
    }

    #undef COPY

    VMResultArray<Follower_t *> Sort_All(Followers_t *followers, SInt32 from, SInt32 to_exclusive, BSFixedString algorithm)
    {
        return Papyrus::Slice_Vector(Aliases::Sort(All(followers), algorithm), from, to_exclusive);
    }

    Follower_t *ID_To_Follower(Followers_t *followers, SInt32 id)
    {
        if (followers && id > -1 && id < Followers::MAX) {
            Follower_t *follower;
            followers->aliases.GetNthItem(id, follower);
            return follower;
        } else {
            return nullptr;
        }
    }

    Follower_t *Actor_To_Follower(Followers_t *followers, Actor *actor)
    {
        if (followers && actor) {
            XAliases_t *xaliases = (XAliases_t *)actor->extraData.GetByType(kExtraData_AliasInstanceArray);
            if (xaliases) {
                for (u64 idx = 0, size = xaliases->aliases.count; idx < size; idx += 1) {
                    XAliases_t::AliasInfo *info = xaliases->aliases[idx];
                    if (info && info->quest == followers) {
                        return info->alias;
                    }
                }
            }
        }

        return nullptr;
    }

    SInt32 Actor_To_ID(Followers_t *followers, Actor *actor)
    {
        if (followers && actor) {
            Follower_t *follower = Actor_To_Follower(followers, actor);
            if (follower) {
                s64 follower_idx = followers->aliases.GetItemIndex(follower);
                if (follower_idx > -1 && follower_idx < Followers::MAX) {
                    return follower_idx;
                }
            }
        }

        return -1;
    }

    Follower_t *Unused_Follower(Followers_t *followers)
    {
        if (followers) {
            for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1) {
                Follower_t *follower;
                followers->aliases.GetNthItem(idx, follower);
                if (follower && !Follower::Exists(follower)) {
                    return follower;
                }
            }
        }

        return nullptr;
    }

    SInt32 Unused_ID(Followers_t *followers)
    {
        if (followers)
        {
            Follower_t *follower;
            for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1)
            {
                followers->aliases.GetNthItem(idx, follower);
                if (follower && !Follower::Exists(follower))
                {
                    return idx;
                }
            }
        }

        return -1;
    }

    bool Has_Space(Followers_t *followers)
    {
        return Count_All(followers) < Followers::MAX;
    }

    bool Hasnt_Space(Followers_t *followers)
    {
        return Count_All(followers) >= Followers::MAX;
    }

    bool Are_In_Combat(Followers_t *followers) {
        if (!followers) {
            return false;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = Followers::MAX; idx < size; idx += 1) {
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

    bool Has_Actor(Followers_t *followers, Actor *actor)
    {
        return followers && actor && Actor2::Is_Aliased_In_Quest(actor, followers);
    }

    Followers_t *Self() {
        static Followers_t *followers;
        return followers ? followers : followers = (Followers_t *)Game::Get_NPCP_Form(0x000D83);
    }

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    bool Register(VMClassRegistry *registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_followers", Followers_t,      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Followers::METHOD_, __VA_ARGS__); \
        W

        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("p_Register", 0, void, Register);
        ADD_METHOD("p_Summon", 3, void, Summon, float, float, float);
        ADD_METHOD("p_Summon_Mobile", 3, void, Summon_Mobile, float, float, float);
        ADD_METHOD("p_Summon_Immobile", 3, void, Summon_Immobile, float, float, float);
        ADD_METHOD("p_Catch_Up", 0, void, Catch_Up);
        ADD_METHOD("p_Stash", 0, void, Stash);
        ADD_METHOD("p_Enforce", 1, void, Enforce, TESForm *);
        ADD_METHOD("p_Resurrect", 1, void, Resurrect, TESForm *);
        ADD_METHOD("p_Mobilize", 1, void, Mobilize, TESForm *);
        ADD_METHOD("p_Immobilize", 1, void, Immobilize, TESForm *);
        ADD_METHOD("p_Settle", 1, void, Settle, TESForm *);
        ADD_METHOD("p_Unsettle", 1, void, Unsettle, TESForm *);
        ADD_METHOD("p_Sneak", 1, void, Sneak, TESForm *);
        ADD_METHOD("p_Unsneak", 1, void, Unsneak, TESForm *);
        ADD_METHOD("p_Saddle", 1, void, Saddle, TESForm *);
        ADD_METHOD("p_Unsaddle", 1, void, Unsaddle, TESForm *);
        ADD_METHOD("p_Retreat", 1, void, Retreat, TESForm *);
        ADD_METHOD("p_Unretreat", 1, void, Unretreat, TESForm *);
        ADD_METHOD("p_Unfollow", 1, void, Unfollow, TESForm *);
        ADD_METHOD("p_Unmember", 1, void, Unmember, TESForm *);

        ADD_METHOD("Max", 0, SInt32, Max);
        ADD_METHOD("Count_All", 0, SInt32, Count_All);
        ADD_METHOD("Count_Alive", 0, SInt32, Count_Alive);
        ADD_METHOD("Count_Dead", 0, SInt32, Count_Dead);
        ADD_METHOD("Count_Mobile", 0, SInt32, Count_Mobile);
        ADD_METHOD("Count_Immobile", 0, SInt32, Count_Immobile);
        ADD_METHOD("Count_Settlers", 0, SInt32, Count_Settlers);
        ADD_METHOD("Count_Non_Settlers", 0, SInt32, Count_Non_Settlers);
        ADD_METHOD("Count_Sneaks", 0, SInt32, Count_Sneaks);
        ADD_METHOD("Count_Non_Sneaks", 0, SInt32, Count_Non_Sneaks);
        ADD_METHOD("Count_Saddlers", 0, SInt32, Count_Saddlers);
        ADD_METHOD("Count_Non_Saddlers", 0, SInt32, Count_Non_Saddlers);
        ADD_METHOD("Count_Retreaters", 0, SInt32, Count_Retreaters);
        ADD_METHOD("Count_Non_Retreaters", 0, SInt32, Count_Non_Retreaters);

        ADD_METHOD("p_Sort_All", 3, VMResultArray<Follower_t *>, Sort_All, SInt32, SInt32, BSFixedString);

        ADD_METHOD("p_ID_To_Follower", 1, Follower_t *, ID_To_Follower, SInt32);
        ADD_METHOD("p_Actor_To_Follower", 1, Follower_t *, Actor_To_Follower, Actor *);
        ADD_METHOD("p_Actor_To_ID", 1, SInt32, Actor_To_ID, Actor *);

        ADD_METHOD("p_Unused_Follower", 0, Follower_t *, Unused_Follower);
        ADD_METHOD("p_Unused_ID", 0, SInt32, Unused_ID);

        ADD_METHOD("Has_Space", 0, bool, Has_Space);
        ADD_METHOD("Hasnt_Space", 0, bool, Hasnt_Space);
        ADD_METHOD("Are_In_Combat", 0, bool, Are_In_Combat);
        ADD_METHOD("Has_Actor", 1, bool, Has_Actor, Actor *);

        #undef ADD_METHOD
        #undef ADD_GLOBAL

        return true;
    }

}}}
