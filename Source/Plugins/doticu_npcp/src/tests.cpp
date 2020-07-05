/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "followers.h"
#include "member.h"
#include "members.h"
#include "papyrus.h"
#include "tests.h"
#include "utils.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Tests {

    #define ASSHURT(IS_TRUE_)                   \
    M                                           \
        if ( !(IS_TRUE_) ) {                    \
            return "failed '" #IS_TRUE_ "'";    \
        }                                       \
    W

    const char* Test_Static_Values()
    {
        using namespace Papyrus;

        Virtual_Machine_t* virtual_machine = Virtual_Machine_t::Self();
        ASSHURT(virtual_machine != nullptr);

        return "ok";
    }

    const char* Test_Members()
    {
        using namespace Papyrus;

        Members_t* members = Party::Members::Self();
        ASSHURT(members != nullptr);

        String_t class_name = Party::Members::Class_Name();
        ASSHURT(class_name == String_t("doticu_npcp_members"));

        Class_Info_t* class_info = Party::Members::Class_Info();
        ASSHURT(class_info != nullptr);

        Object_t* instance = Party::Members::Object();
        ASSHURT(instance != nullptr);

        ASSHURT(class_info == instance->info);

        return "ok";
    }

    const char* Test_Followers()
    {
        using namespace Papyrus;

        Followers_t* followers = Followers::Self();
        ASSHURT(followers != nullptr);

        return "ok";
    }

    const char* Test_Member()
    {
        using namespace Papyrus;

        String_t class_name = Party::Member::Class_Name();
        ASSHURT(class_name == String_t("doticu_npcp_member"));

        Class_Info_t* class_info = Party::Member::Class_Info();
        ASSHURT(class_info != nullptr);

        // get a member_alias and test against class_info

        return "ok";
    }

    const char* Test_Papyrus_Handle()
    {
        Quest_t* quest = dynamic_cast<Quest_t*>(Followers::Self());
        ASSHURT(quest != nullptr);

        Papyrus::Handle_t quest_handle(quest);
        ASSHURT(quest_handle.Is_Valid());

        Form_t* quest_form = dynamic_cast<Form_t*>(quest);
        Papyrus::Handle_t form_handle(quest_form);
        ASSHURT(form_handle.Is_Valid());
        ASSHURT(quest_handle == form_handle);

        Alias_t* alias = quest->aliases.entries[0];
        ASSHURT(alias != nullptr);

        Papyrus::Handle_t alias_handle(alias);
        ASSHURT(alias_handle.Is_Valid());
        ASSHURT(quest_handle != alias_handle);

        return "ok";
    }

    #undef ASSHURT

    void Run_Tests()
    {
        #define RUN_TEST(TEST_NAME_)                        \
        M                                                   \
            _MESSAGE("%s: %s", #TEST_NAME_, TEST_NAME_());  \
        W

        _MESSAGE("Running Tests:");

        RUN_TEST(Test_Static_Values);
        RUN_TEST(Test_Members);
        RUN_TEST(Test_Followers);
        RUN_TEST(Test_Member);
        RUN_TEST(Test_Papyrus_Handle);

        _MESSAGE("Done running tests.");

        #undef RUN_TEST
    }

}}

namespace doticu_npcp { namespace Tests { namespace Exports {

    void Run_Tests(Selfless_t*)
    {
        return Tests::Run_Tests();
    }

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("Run_Tests", 0, void, Run_Tests);

        #undef ADD_GLOBAL

        return true;
    }

}}}
