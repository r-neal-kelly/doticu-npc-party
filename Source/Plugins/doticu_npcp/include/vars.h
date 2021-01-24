/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/quest.h"

#include "intrinsic.h"

namespace doticu_npcp {

    class Vars_t : public Quest_t
    {
    public:
        static some<Vars_t*>        Self();
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static some<V::Object_t*>   Object();
        static void                 Register_Me(V::Machine_t* machine);

    public:
        static V::Variable_tt<Int_t>&       Major_Version();
        static V::Variable_tt<Int_t>&       Minor_Version();
        static V::Variable_tt<Int_t>&       Patch_Version();

        static V::Variable_tt<Int_t>&       Member_Limit();
        static V::Variable_tt<Int_t>&       Member_Display_Limit();
        static V::Variable_tt<String_t>&    Default_Member_Style();
        static V::Variable_tt<String_t>&    Default_Member_Vitality();
        static V::Variable_tt<String_t>&    Member_Sort_Algorithm();

        static V::Variable_tt<Bool_t>&      Do_Auto_Resurrect_Followers();
        static V::Variable_tt<Bool_t>&      Do_Auto_Sojourn_Followers();
        static V::Variable_tt<String_t>&    Follower_Sort_Algorithm();

        static V::Variable_tt<Bool_t>&      Do_Auto_Change_Outfits();
        static V::Variable_tt<Bool_t>&      Do_Auto_Change_Immobile_Outfit();
        static V::Variable_tt<Bool_t>&      Do_Fill_Outfits();
        static V::Variable_tt<String_t>&    Clone_Outfit_Algorithm();

        struct Key
        {
            struct Base
            {
                struct Global
                {
                    static V::Variable_tt<Int_t>& Dialogue_Menu();
                };
                struct NPC
                {
                    static V::Variable_tt<Int_t>& Toggle_Member();
                    static V::Variable_tt<Int_t>& Toggle_Move();
                    static V::Variable_tt<Int_t>& Move_Nearer();
                    static V::Variable_tt<Int_t>& Move_Farther();
                    static V::Variable_tt<Int_t>& Move_Rotate_Left();
                    static V::Variable_tt<Int_t>& Move_Rotate_Right();
                    static V::Variable_tt<Int_t>& Has_Base();
                    static V::Variable_tt<Int_t>& Count_Base();
                    static V::Variable_tt<Int_t>& Has_Head();
                    static V::Variable_tt<Int_t>& Count_Heads();
                };
                struct Member
                {
                    static V::Variable_tt<Int_t>& Toggle_Clone();
                    static V::Variable_tt<Int_t>& Toggle_Settler();
                    static V::Variable_tt<Int_t>& Toggle_Thrall();
                    static V::Variable_tt<Int_t>& Toggle_Immobile();
                    static V::Variable_tt<Int_t>& Toggle_Paralyzed();
                    static V::Variable_tt<Int_t>& Toggle_Follower();
                };
                struct Follower
                {
                    static V::Variable_tt<Int_t>& Toggle_Sneak();
                    static V::Variable_tt<Int_t>& Toggle_Saddler();
                };
                struct Members
                {
                    static V::Variable_tt<Int_t>& Toggle_Display();
                    static V::Variable_tt<Int_t>& Display_Previous();
                    static V::Variable_tt<Int_t>& Display_Next();
                };
                struct Followers
                {
                    static V::Variable_tt<Int_t>& Summon_All();
                    static V::Variable_tt<Int_t>& Summon_Mobile();
                    static V::Variable_tt<Int_t>& Summon_Immobile();
                    static V::Variable_tt<Int_t>& Settle();
                    static V::Variable_tt<Int_t>& Unsettle();
                    static V::Variable_tt<Int_t>& Mobilize();
                    static V::Variable_tt<Int_t>& Immobilize();
                    static V::Variable_tt<Int_t>& Sneak();
                    static V::Variable_tt<Int_t>& Unsneak();
                    static V::Variable_tt<Int_t>& Saddle();
                    static V::Variable_tt<Int_t>& Unsaddle();
                    static V::Variable_tt<Int_t>& Resurrect();
                };
            };
            struct Mods
            {
                struct Global
                {
                    static V::Variable_tt<Vector_t<Int_t>>& Dialogue_Menu();
                };
                struct NPC
                {
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Member();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Move();
                    static V::Variable_tt<Vector_t<Int_t>>& Move_Nearer();
                    static V::Variable_tt<Vector_t<Int_t>>& Move_Farther();
                    static V::Variable_tt<Vector_t<Int_t>>& Move_Rotate_Left();
                    static V::Variable_tt<Vector_t<Int_t>>& Move_Rotate_Right();
                    static V::Variable_tt<Vector_t<Int_t>>& Has_Base();
                    static V::Variable_tt<Vector_t<Int_t>>& Count_Base();
                    static V::Variable_tt<Vector_t<Int_t>>& Has_Head();
                    static V::Variable_tt<Vector_t<Int_t>>& Count_Heads();
                };
                struct Member
                {
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Clone();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Settler();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Thrall();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Immobile();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Paralyzed();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Follower();
                };
                struct Follower
                {
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Sneak();
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Saddler();
                };
                struct Members
                {
                    static V::Variable_tt<Vector_t<Int_t>>& Toggle_Display();
                    static V::Variable_tt<Vector_t<Int_t>>& Display_Previous();
                    static V::Variable_tt<Vector_t<Int_t>>& Display_Next();
                };
                struct Followers
                {
                    static V::Variable_tt<Vector_t<Int_t>>& Summon_All();
                    static V::Variable_tt<Vector_t<Int_t>>& Summon_Mobile();
                    static V::Variable_tt<Vector_t<Int_t>>& Summon_Immobile();
                    static V::Variable_tt<Vector_t<Int_t>>& Settle();
                    static V::Variable_tt<Vector_t<Int_t>>& Unsettle();
                    static V::Variable_tt<Vector_t<Int_t>>& Mobilize();
                    static V::Variable_tt<Vector_t<Int_t>>& Immobilize();
                    static V::Variable_tt<Vector_t<Int_t>>& Sneak();
                    static V::Variable_tt<Vector_t<Int_t>>& Unsneak();
                    static V::Variable_tt<Vector_t<Int_t>>& Saddle();
                    static V::Variable_tt<Vector_t<Int_t>>& Unsaddle();
                    static V::Variable_tt<Vector_t<Int_t>>& Resurrect();
                };
            };
        };

    public:
        static Bool_t               Do_Allow_Dialogue_For_All();
        static void                 Do_Allow_Dialogue_For_All(Bool_t value);
        static Bool_t               Do_Allow_Chatter();
        static void                 Do_Allow_Chatter(Bool_t value);
        static Bool_t               Do_Force_Clone_Uniques();
        static void                 Do_Force_Clone_Uniques(Bool_t value);
        static Bool_t               Do_Force_Clone_Generics();
        static void                 Do_Force_Clone_Generics(Bool_t value);
        static Bool_t               Do_Force_Unclone_Uniques();
        static void                 Do_Force_Unclone_Uniques(Bool_t value);
        static Bool_t               Do_Force_Unclone_Generics();
        static void                 Do_Force_Unclone_Generics(Bool_t value);
        static Bool_t               Do_Level_Followers();
        static void                 Do_Level_Followers(Bool_t value);

        static Int_t                Fill_Outfit_Body_Percent();
        static void                 Fill_Outfit_Body_Percent(Int_t value);
        static Int_t                Fill_Outfit_Feet_Percent();
        static void                 Fill_Outfit_Feet_Percent(Int_t value);
        static Int_t                Fill_Outfit_Hands_Percent();
        static void                 Fill_Outfit_Hands_Percent(Int_t value);
        static Int_t                Fill_Outfit_Head_Percent();
        static void                 Fill_Outfit_Head_Percent(Int_t value);

        static const Version_t<u16> Version();
        static void                 Version(const Version_t<u16> value);

    public:
        static void Initialize();
    };

}
