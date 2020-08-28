/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_member.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_followers.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Followers_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_followers");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Followers_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Followers_t* Followers_t::Self()
    {
        return static_cast<Followers_t*>(Consts::Control_Quest());
    }

    Object_t* Followers_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Followers_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Followers_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Followers_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }
    Variable_t* Followers_t::Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }
    Variable_t* Followers_t::Do_Previous_Follower_Variable() { DEFINE_VARIABLE("p_do_prev_follower"); }
    Variable_t* Followers_t::Do_Next_Follower_Variable() { DEFINE_VARIABLE("p_do_next_follower"); }

    Int_t Followers_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Followers_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    Party::Member_t* Followers_t::Member()
    {
        return static_cast<Party::Member_t*>(Member_Variable()->Alias());
    }

    void Followers_t::Member(Party::Member_t* member)
    {
        Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    void Followers_t::Review_Followers()
    {
        Current_View(CODES::VIEW::FOLLOWERS);
        Member(nullptr);
    }

    void Followers_t::Request_Previous_Follower()
    {
        Do_Previous_Follower_Variable()->Bool(true);
    }

    void Followers_t::Request_Next_Follower()
    {
        Do_Next_Follower_Variable()->Bool(true);
    }

    void Followers_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Followers_t,           \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
