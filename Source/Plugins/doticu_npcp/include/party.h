/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <fstream>

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/unique.h"

#include "intrinsic.h"
#include "party_member_id.h"
#include "party_member_update_ai.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Displays_t;
    class Expoees_t;
    class Followers_t;
    class Members_t;
    class Settlers_t;

    class Party_t
    {
    public:
        static void Register_Me(some<Virtual::Machine_t*> machine);

    public:
        const some<unique<Members_t>>       members;
        const some<unique<Settlers_t>>      settlers;
        const some<unique<Expoees_t>>       expoees;
        const some<unique<Displays_t>>      displays;
        const some<unique<Followers_t>>     followers;
        Vector_t<maybe<Script_t*>>          scripts;
        Vector_t<maybe<Member_Update_AI_e>> update_ais;

    public:
        Party_t();
        Party_t(const Party_t& other) = delete;
        Party_t(Party_t&& other) noexcept = delete;
        Party_t& operator =(const Party_t& other) = delete;
        Party_t& operator =(Party_t&& other) noexcept = delete;
        ~Party_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        Members_t&      Members();
        Settlers_t&     Settlers();
        Expoees_t&      Expoees();
        Displays_t&     Displays();
        Followers_t&    Followers();

    public:
        Bool_t  Is_Sandboxer(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Sleeper(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Sitter(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Eater(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Guard(some<Member_ID_t> valid_member_id);

        Bool_t  Is_Active_Sandboxer(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Sleeper(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Sitter(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Eater(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Active_Guard(some<Member_ID_t> valid_member_id);

        Bool_t  Is_Follower(some<Member_ID_t> valid_member_id);

    public:
        some<Script_t*> Script(some<Member_ID_t> valid_member_id);
        void            Update_AI(some<Member_ID_t> valid_member_id, some<Member_Update_AI_e> update_ai);

        Bool_t          Is_Token(some<Bound_Object_t*> bound_object);

        void            Enforce(some<Member_ID_t> valid_member_id);
        void            Enforce();

    public:
        void    Log(std::string indent = "");
    };

}}
