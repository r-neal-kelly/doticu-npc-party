/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "game.h"
#include "consts.h"

#include "aliases.h"
#include "members.h"

namespace doticu_npcp { namespace Party { namespace Members {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_members");
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Members_t* Self()
    {
        static Members_t* members = static_cast<Members_t*>(Game::Get_NPCP_Form(Consts::QUEST_MEMBERS));
        return members;
    }

    Object_t* Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), Class_Name());
        return object;
    }

    Range_t<UInt64> Indices(Members_t* self)
    {
        return { BEGIN, END };
    }

    Range_t<Alias_t**> Aliases(Members_t* self)
    {
        return Aliases::Aliases(self, BEGIN, END);
    }

    Range_t<Member_t**> Members(Members_t* self)
    {
        return Aliases(self);
    }

    Member_t* From_Actor(Members_t* self, Actor_t* actor)
    {
        if (self && actor) {
            Alias_t* alias = Aliases::From_Actor(self, actor);
            if (alias) {
                if (alias->id >= BEGIN && alias->id < END) {
                    return alias;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

}}}

#include "utils.h"

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    typedef Member_t* (*function_type)(Members_t*, Actor_t*);

    class Function_t : public NativeFunction {
        Function_t(const char* function_name, const char* class_name, function_type, Registry_t* registry) :
            NativeFunction(function_name, class_name, false, 1)
        {

        }

        bool Run(Variable_t* base, Registry_t* registry, UInt32 stack_id, VMValue* resultValue, VMState* stack_frame)
        {
            
        }
    };

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_members", Members_t,          \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Members::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("p_From_Actor", 1, Member_t*, From_Actor, Actor_t*);

        #undef ADD_METHOD



        return true;
    }

}}}}






















































#include "actor2.h"
#include "aliases.h"
#include "member.h"
#include "members.h"
#include "papyrus.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Members {

    void Enforce_Loaded(Members_t *members) {
        if (!members) {
            return;
        }

        BSFixedString func_name("Enforce");
        struct Args : public IFunctionArguments {
            bool Copy(Output *output) { return true; }
        } func_args;

        std::vector<Member_t *> vec_members = Get_Loaded(members);
        for (u64 idx = 0, size = vec_members.size(); idx < size; idx += 1) {
            Member_t *member = vec_members[idx];
            Papyrus::Handle_t member_handle(member);
            member_handle.Registry()->QueueEvent(member_handle, &func_name, &func_args);
        }
    }

    VMResultArray<Member_t *> Get_Loaded(Members_t *members) {
        VMResultArray<Member_t *> vec_members;

        if (!members) {
            return vec_members;
        }

        Member_t *member;
        for (u64 idx = 0, size = members->aliases.count; idx < size; idx += 1) {
            members->aliases.GetNthItem(idx, member);
            if (!member) {
                continue;
            }

            if (!Member::Is_Created(member)) {
                continue;
            }

            Actor *actor = Member::Get_Actor(member);
            if (!actor || !Actor2::Is_Loaded(actor)) {
                continue;
            }

            vec_members.push_back(member);
        }

        return vec_members;
    }
    
}}

namespace doticu_npcp { namespace Members { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <Members_t, void>(
                "p_Enforce_Loaded",
                "doticu_npcp_members",
                Members::Enforce_Loaded,
                registry)
        );

        return true;
    }

}}}
