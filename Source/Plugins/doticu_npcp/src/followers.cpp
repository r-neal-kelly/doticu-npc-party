/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "follower.h"
#include "followers.h"
#include "member.h"
#include "object_ref.h"

namespace doticu_npcp { namespace Followers {

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

    SInt32 Get_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Alive_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Alive(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Dead_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Dead(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Mobile_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Mobile(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Immobile_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Immobile(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Settler_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Settler(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Non_Settler_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Isnt_Settler(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Sneak_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Sneak(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Non_Sneak_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Isnt_Sneak(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Saddler_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Saddler(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Non_Saddler_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Isnt_Saddler(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Retreater_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Retreater(follower)) {
                count += 1;
            }
        }

        return count;
    }

    SInt32 Get_Non_Retreater_Count(Followers_t *followers) {
        if (!followers) {
            return -1;
        }

        SInt32 count = 0;
        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Isnt_Retreater(follower)) {
                count += 1;
            }
        }

        return count;
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

    VMResultArray<Follower_t *> Get(Followers_t *followers) {
        VMResultArray<Follower_t *> vec_followers;

        if (!followers) {
            return vec_followers;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower)) {
                vec_followers.push_back(follower);
            }
        }

        return vec_followers;
    }

    VMResultArray<Follower_t *> Get_Mobile(Followers_t *followers) {
        VMResultArray<Follower_t *> vec_followers;

        if (!followers) {
            return vec_followers;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Mobile(follower)) {
                vec_followers.push_back(follower);
            }
        }

        return vec_followers;
    }

    VMResultArray<Follower_t *> Get_Immobile(Followers_t *followers) {
        VMResultArray<Follower_t *> vec_followers;

        if (!followers) {
            return vec_followers;
        }

        Follower_t *follower;
        for (u64 idx = 0, size = followers->aliases.count; idx < size; idx += 1) {
            followers->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            if (Follower::Is_Created(follower) &&
                Follower::Get_Actor(follower) &&
                Follower::Is_Immobile(follower)) {
                vec_followers.push_back(follower);
            }
        }

        return vec_followers;
    }

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    void Stash(StaticFunctionTag *, Followers_t *followers) {
        return Followers::Stash(followers);
    }

    bool Register(VMClassRegistry *registry) {
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
            new NativeFunction1 <StaticFunctionTag, void, Followers_t *>(
                "Followers_Stash",
                "doticu_npcp",
                Exports::Stash,
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

        return true;
    }

}}}
