/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "types.h"

namespace doticu_npcp { namespace Followers {

    void Register(Followers_t *followers);
    void Summon(std::vector<Follower_t *> vec_followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Summon(Followers_t *followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Summon_Mobile(Followers_t *followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Summon_Immobile(Followers_t *followers, float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0);
    void Stash(Followers_t *followers);
    void Resurrect(Followers_t *followers, TESForm *tasklist = NULL);
    void Mobilize(Followers_t *followers, TESForm *tasklist = NULL);
    void Immobilize(Followers_t *followers, TESForm *tasklist = NULL);
    void Settle(Followers_t *followers, TESForm *tasklist = NULL);
    void Unsettle(Followers_t *followers, TESForm *tasklist = NULL);
    void Sneak(Followers_t *followers, TESForm *tasklist = NULL);
    void Unsneak(Followers_t *followers, TESForm *tasklist = NULL);
    void Saddle(Followers_t *followers, TESForm *tasklist = NULL);
    void Unsaddle(Followers_t *followers, TESForm *tasklist = NULL);
    void Retreat(Followers_t *followers, TESForm *tasklist = NULL);
    void Unretreat(Followers_t *followers, TESForm *tasklist = NULL);
    void Unfollow(Followers_t *followers, TESForm *tasklist = NULL);
    void Unmember(Followers_t *followers, TESForm *tasklist = NULL);

    SInt32 Get_Count(Followers_t *followers);
    SInt32 Get_Alive_Count(Followers_t *followers);
    SInt32 Get_Dead_Count(Followers_t *followers);
    SInt32 Get_Mobile_Count(Followers_t *followers);
    SInt32 Get_Immobile_Count(Followers_t *followers);
    SInt32 Get_Settler_Count(Followers_t *followers);
    SInt32 Get_Non_Settler_Count(Followers_t *followers);
    SInt32 Get_Sneak_Count(Followers_t *followers);
    SInt32 Get_Non_Sneak_Count(Followers_t *followers);
    SInt32 Get_Saddler_Count(Followers_t *followers);
    SInt32 Get_Non_Saddler_Count(Followers_t *followers);
    SInt32 Get_Retreater_Count(Followers_t *followers);
    SInt32 Get_Non_Retreater_Count(Followers_t *followers);

    VMResultArray<Follower_t *> Get(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Alive(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Dead(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Mobile(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Immobile(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Settlers(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Non_Settlers(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Sneaks(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Non_Sneaks(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Saddlers(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Non_Saddlers(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Retreaters(Followers_t *followers);
    VMResultArray<Follower_t *> Get_Non_Retreaters(Followers_t *followers);

    bool Are_In_Combat(Followers_t *followers);

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
