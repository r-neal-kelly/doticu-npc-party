/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party.h"

namespace doticu_npcp { namespace Party { namespace Followers {

    constexpr UInt64 MAX = 16;
    constexpr UInt64 BEGIN = 0;
    constexpr UInt64 END = BEGIN + MAX;

    Range_t<UInt64> Indices(Followers_t* self);
    Range_t<Alias_t**> Aliases(Followers_t* self);
    Range_t<Follower_t**> Followers(Followers_t* self);

    Follower_t* From_Actor(Followers_t* self, Actor_t* actor);

}}}









































#include "types.h"

namespace doticu_npcp { namespace Followers {

    static const SInt32 MAX = 16;

    void Register(Followers_t *followers);
    void Summon(std::vector<Follower_t *> vec_followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Summon(Followers_t *followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Summon_Mobile(Followers_t *followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Summon_Immobile(Followers_t *followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Catch_Up(Followers_t *followers);
    void Stash(Followers_t *followers);
    void Enforce(Followers_t *followers, TESForm *tasklist = nullptr);
    void Resurrect(Followers_t *followers, TESForm *tasklist = nullptr);
    void Mobilize(Followers_t *followers, TESForm *tasklist = nullptr);
    void Immobilize(Followers_t *followers, TESForm *tasklist = nullptr);
    void Settle(Followers_t *followers, TESForm *tasklist = nullptr);
    void Unsettle(Followers_t *followers, TESForm *tasklist = nullptr);
    void Sneak(Followers_t *followers, TESForm *tasklist = nullptr);
    void Unsneak(Followers_t *followers, TESForm *tasklist = nullptr);
    void Saddle(Followers_t *followers, TESForm *tasklist = nullptr);
    void Unsaddle(Followers_t *followers, TESForm *tasklist = nullptr);
    void Retreat(Followers_t *followers, TESForm *tasklist = nullptr);
    void Unretreat(Followers_t *followers, TESForm *tasklist = nullptr);
    void Unfollow(Followers_t *followers, TESForm *tasklist = nullptr);
    void Unmember(Followers_t *followers, TESForm *tasklist = nullptr);

    SInt32 Max(Followers_t *followers);
    SInt32 Count_All(Followers_t *followers);
    SInt32 Count_Alive(Followers_t *followers);
    SInt32 Count_Dead(Followers_t *followers);
    SInt32 Count_Mobile(Followers_t *followers);
    SInt32 Count_Immobile(Followers_t *followers);
    SInt32 Count_Settlers(Followers_t *followers);
    SInt32 Count_Non_Settlers(Followers_t *followers);
    SInt32 Count_Sneaks(Followers_t *followers);
    SInt32 Count_Non_Sneaks(Followers_t *followers);
    SInt32 Count_Saddlers(Followers_t *followers);
    SInt32 Count_Non_Saddlers(Followers_t *followers);
    SInt32 Count_Retreaters(Followers_t *followers);
    SInt32 Count_Non_Retreaters(Followers_t *followers);

    VMResultArray<Follower_t *> All(Followers_t *followers);
    VMResultArray<Follower_t *> Alive(Followers_t *followers);
    VMResultArray<Follower_t *> Dead(Followers_t *followers);
    VMResultArray<Follower_t *> Mobile(Followers_t *followers);
    VMResultArray<Follower_t *> Immobile(Followers_t *followers);
    VMResultArray<Follower_t *> Settlers(Followers_t *followers);
    VMResultArray<Follower_t *> Non_Settlers(Followers_t *followers);
    VMResultArray<Follower_t *> Sneaks(Followers_t *followers);
    VMResultArray<Follower_t *> Non_Sneaks(Followers_t *followers);
    VMResultArray<Follower_t *> Saddlers(Followers_t *followers);
    VMResultArray<Follower_t *> Non_Saddlers(Followers_t *followers);
    VMResultArray<Follower_t *> Retreaters(Followers_t *followers);
    VMResultArray<Follower_t *> Non_Retreaters(Followers_t *followers);

    VMResultArray<Follower_t *> Sort_All(Followers_t *followers, SInt32 from = 0, SInt32 to_exclusive = -1, BSFixedString algorithm = "");

    Follower_t *ID_To_Follower(Followers_t *followers, SInt32 id);
    Follower_t *Actor_To_Follower(Followers_t *followers, Actor *actor);
    SInt32 Actor_To_ID(Followers_t *followers, Actor *actor);
    idx_t Actor_To_Alias_Idx(Followers_t* followers, Actor* actor);
    Horse_t* Actor_To_Horse(Followers_t* followers, Actor* horse);
    Actor_t* Horse_Actor_To_Follower_Actor(Followers_t* followers, Actor_t* horse);

    Follower_t *Unused_Follower(Followers_t *followers);
    SInt32 Unused_ID(Followers_t *followers);

    bool Has_Space(Followers_t *followers);
    bool Hasnt_Space(Followers_t *followers);
    bool Are_In_Combat(Followers_t *followers);
    bool Has_Actor(Followers_t *followers, Actor *actor);

    Followers_t *Self();

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
