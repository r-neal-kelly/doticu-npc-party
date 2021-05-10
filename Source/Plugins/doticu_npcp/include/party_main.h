/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/unique.h"

#include "intrinsic.h"
#include "party_member_id.h"
#include "party_member_update_ai.h"

namespace doticu_npcp { namespace Party {

    class Displays_t;
    class Expoees_t;
    class Followers_t;
    class Members_t;
    class Settlers_t;

    class Main_t
    {
    public:
        static void Register_Me(some<V::Machine_t*> machine);

    public:
        const some<unique<Members_t>>       members;
        const some<unique<Settlers_t>>      settlers;
        const some<unique<Expoees_t>>       expoees;
        const some<unique<Displays_t>>      displays;
        const some<unique<Followers_t>>     followers;
        Vector_t<maybe<Script_t*>>          scripts;
        Vector_t<maybe<Member_Update_AI_e>> update_ais;

    public:
        Main_t(Bool_t is_new_game);
        Main_t(const Version_t<u16> version_to_update);
        Main_t(const Main_t& other)                     = delete;
        Main_t(Main_t&& other) noexcept                 = delete;
        Main_t& operator =(const Main_t& other)         = delete;
        Main_t& operator =(Main_t&& other) noexcept     = delete;
        ~Main_t();

    public:
        void    Before_Save();
        void    After_Save();
        void    Validate();

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

        Bool_t  Is_Currently_Sandboxer(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Currently_Sleeper(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Currently_Sitter(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Currently_Eater(some<Member_ID_t> valid_member_id);
        Bool_t  Is_Currently_Guard(some<Member_ID_t> valid_member_id);

        Bool_t  Is_Follower(some<Member_ID_t> valid_member_id);

    public:
        some<Script_t*> Script(some<Member_ID_t> valid_member_id);
        void            Update_AI(some<Member_ID_t> valid_member_id, some<Member_Update_AI_e> update_ai);

        Bool_t          Is_Token(some<Bound_Object_t*> bound_object);

        void            Tokenize(some<Member_ID_t> valid_member_id,
                                 some<Bound_Object_t*> object,
                                 Container_Entry_Count_t count = 1);
        void            Untokenize(some<Member_ID_t> valid_member_id,
                                   some<Bound_Object_t*> object);

        void            Enforce(some<Member_ID_t> valid_member_id);
        void            Enforce();

    public:
        void    Log(std::string indent = "");
    };

}}
