/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"
#include "party.h"
#include "tests.h"
#include "utils.h"
#include "form_vector.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Tests {

    #define ASSERTS(IS_TRUE_)                   \
    M                                           \
        if ( !(IS_TRUE_) ) {                    \
            return "failed '" #IS_TRUE_ "'";    \
        }                                       \
    W

    const char* Test_Static_Values()
    {
        using namespace Papyrus;

        Virtual_Machine_t* virtual_machine = Virtual_Machine_t::Self();
        ASSERTS(virtual_machine != nullptr);

        return "ok";
    }

    const char* Test_Class_Info()
    {
        using namespace Papyrus;

        String_t class_name = String_t("doticu_npcp_members");
        Class_Info_t* class_info = Class_Info_t::Fetch(class_name);
        ASSERTS(class_info != nullptr);

        UInt32 ref_count = class_info->ref_count;
        for (size_t idx = 0; idx < 12; idx += 1) {
            Class_Info_t* new_class_info = Class_Info_t::Fetch(class_name);
            new_class_info->Free();
            ASSERTS(new_class_info->ref_count == ref_count);
        }

        class_info->Free();

        return "ok";
    }

    const char* Test_Object()
    {
        // we need to check whether or not we are incrementing ref when we fetch the object.

        return "ok";
    }

    const char* Test_Form_Vector()
    {
        using namespace Papyrus;

        Form_Vector_t* forms;

        forms = Form_Vector_t::Create(0, nullptr, 1.5f);
        NPCP_ASSERT(forms);
        NPCP_ASSERT(forms->Array() != nullptr);
        NPCP_ASSERT(forms->Capacity() == 0);
        NPCP_ASSERT(forms->Count() == 0);
        NPCP_ASSERT(forms->Filler() == nullptr);
        NPCP_ASSERT(forms->Grow_Rate() == 1.5f);
        NPCP_ASSERT(forms->Vector().size() == 0);
        Form_Vector_t::Destroy(forms);

        forms = Form_Vector_t::Create(1, nullptr, 2.0f);
        NPCP_ASSERT(forms);
        NPCP_ASSERT(forms->Array() != nullptr);
        NPCP_ASSERT(forms->Capacity() == 1);
        NPCP_ASSERT(forms->Count() == 0);
        NPCP_ASSERT(forms->Filler() == nullptr);
        NPCP_ASSERT(forms->Grow_Rate() == 2.0f);
        NPCP_ASSERT(forms->Vector().size() == 0);
        forms->Push(Consts::Clone_Token());
        NPCP_ASSERT(forms->Capacity() == 1);
        NPCP_ASSERT(forms->Count() == 1);
        NPCP_ASSERT(forms->Vector().size() == 1);
        forms->Push(Consts::Blank_Weapon());
        NPCP_ASSERT(forms->Capacity() == 2);
        NPCP_ASSERT(forms->Count() == 2);
        NPCP_ASSERT(forms->Vector().size() == 2);
        NPCP_ASSERT(forms->At(0) == Consts::Clone_Token());
        NPCP_ASSERT(forms->At(1) == Consts::Blank_Weapon());
        NPCP_ASSERT(forms->Has(Consts::Clone_Token()) == true);
        forms->Remove_Unstable(0);
        NPCP_ASSERT(forms->Capacity() == 2);
        NPCP_ASSERT(forms->Count() == 1);
        NPCP_ASSERT(forms->Vector().size() == 1);
        NPCP_ASSERT(forms->At(0) == Consts::Blank_Weapon());
        NPCP_ASSERT(forms->Has(Consts::Clone_Token()) == false);

        _MESSAGE("data: %p, type: %s, count: %i, capacity: %i",
                 forms->Array(),
                 forms->Array_Variable()->type.Class_Info()->name,
                 forms->Count(),
                 forms->Capacity());

        Form_Vector_t::Destroy(forms);

        return "ok";
    }

    const char* Test_Members()
    {
        using namespace Papyrus;

        /*Members_t* members = Party::Members::Self();
        ASSERTS(members != nullptr);

        String_t class_name = Party::Members::Class_Name();
        ASSERTS(class_name == String_t("doticu_npcp_members"));

        Class_Info_t* class_info = Party::Members::Class_Info();
        ASSERTS(class_info != nullptr);

        Object_t* instance = Party::Members::Object();
        ASSERTS(instance != nullptr);

        ASSERTS(class_info == instance->info);*/

        /*for (size_t idx = 0, count = members->aliases.count; idx < count; idx += 1) {
            Alias_Reference_t* alias = reinterpret_cast<Alias_Reference_t*>(members->aliases.entries[idx]);
            _MESSAGE("%zu %s:", idx, alias->name);
            _MESSAGE("    flags: %u", alias->flags);
            _MESSAGE("    type: %s", alias->Type());
            _MESSAGE("    fill_type: %u", alias->fill_type);
            _MESSAGE("    fill_data: %u, %u, %u", alias->fill.padding[0], alias->fill.padding[1], alias->fill.padding[2]);
            _MESSAGE("    conditions: %p", alias->conditions);
        }*/

        return "ok";
    }

    const char* Test_Followers()
    {
        using namespace Papyrus;

        /*Followers_t* followers = Followers::Self();
        ASSERTS(followers != nullptr);*/

        return "ok";
    }

    const char* Test_Member()
    {
        using namespace Papyrus;

        /*String_t class_name = Party::Member::Class_Name();
        ASSERTS(class_name == String_t("doticu_npcp_member"));

        Class_Info_t* class_info = Party::Member::Class_Info();
        ASSERTS(class_info != nullptr);*/

        // get a member_alias and test against class_info

        return "ok";
    }

    const char* Test_Papyrus_Handle()
    {
        using namespace Papyrus;

        Quest_t* quest = dynamic_cast<Quest_t*>(Party::Followers_t::Self());
        ASSERTS(quest != nullptr);

        Papyrus::Handle_t quest_handle(quest);
        ASSERTS(quest_handle.Is_Valid());

        Form_t* quest_form = dynamic_cast<Form_t*>(quest);
        Papyrus::Handle_t form_handle(quest_form);
        ASSERTS(form_handle.Is_Valid());
        ASSERTS(quest_handle == form_handle);

        Alias_Base_t* alias = reinterpret_cast<Alias_Base_t*>(quest->aliases.entries[0]);
        ASSERTS(alias != nullptr);

        Papyrus::Handle_t alias_handle(alias);
        ASSERTS(alias_handle.Is_Valid());
        ASSERTS(quest_handle != alias_handle);

        return "ok";
    }

    #undef ASSERTS

    void Run_Tests()
    {
        #define RUN_TEST(TEST_NAME_)                        \
        M                                                   \
            _MESSAGE("%s: %s", #TEST_NAME_, TEST_NAME_());  \
        W

        _MESSAGE("Running Tests:");

        RUN_TEST(Test_Static_Values);
        RUN_TEST(Test_Class_Info);
        RUN_TEST(Test_Object);
        RUN_TEST(Test_Form_Vector);
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
