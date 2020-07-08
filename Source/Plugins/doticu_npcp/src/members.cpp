/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "game.h"
#include "consts.h"
#include "vars.h"
#include "vector.h"

#include "papyrus.inl"

#include "aliases.h"
#include "members.h"
#include "member.h"

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

    Member_t* From_ID(Members_t* self, Int_t unique_id)
    {
        if (self) {
            if (unique_id >= BEGIN && unique_id < END) {
                return Aliases::From_ID(self, unique_id);
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
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

    Bool_t Has_Actor(Members_t* self, Actor_t* actor)
    {
        if (self && actor) {
            return From_Actor(self, actor) != nullptr;
        } else {
            return false;
        }
    }

    Bool_t Hasnt_Actor(Members_t* self, Actor_t* actor)
    {
        if (self && actor) {
            return From_Actor(self, actor) == nullptr;
        } else {
            return false;
        }
    }

    Bool_t Has_Head(Members_t* self, Actor_t* actor)
    {
        return self && actor && Aliases::Has_Head(Members(self), actor, Member::Has_Same_Head);
    }

    Bool_t Hasnt_Head(Members_t* self, Actor_t* actor)
    {
        return self && actor && !Aliases::Has_Head(Members(self), actor, Member::Has_Same_Head);
    }

    Int_t Max(Members_t* self)
    {
        return Members::MAX;
    }

    Int_t Count_Filled(Members_t* self)
    {
        return Aliases::Count_If(Members(self), Member::Is_Filled);
    }

    Int_t Count_Unfilled(Members_t* self)
    {
        return Aliases::Count_If(Members(self), Member::Is_Unfilled);
    }

    Int_t Count_Loaded(Members_t* self)
    {
        return Aliases::Count_If(Members(self), Member::Is_Filled, Member::Is_Loaded);
    }

    Int_t Count_Unloaded(Members_t* self)
    {
        return Aliases::Count_If(Members(self), Member::Is_Filled, Member::Is_Unloaded);
    }

    Int_t Count_Heads(Members_t* self, Actor_t* actor)
    {
        return Aliases::Count_Heads(Members(self), actor, Member::Has_Same_Head);
    }

    Vector_t<Member_t*> Filled(Members_t* self)
    {
        return Aliases::Copy_If(Members(self), Member::Is_Filled, MAX);
    }

    Vector_t<Member_t*> Loaded(Members_t* self)
    {
        return Aliases::Copy_If(Members(self), Member::Is_Filled, Member::Is_Loaded, HALF);
    }

    Vector_t<Member_t*> Unloaded(Members_t* self)
    {
        return Aliases::Copy_If(Members(self), Member::Is_Filled, Member::Is_Unloaded, HALF);
    }

    Vector_t<Member_t*> Sort(Vector_t<Member_t*> members)
    {
        static const String_t sort_algorithm_name = String_t("p_str_sort_members");

        return Aliases::Sort<Member_t, Member::Actor, Member::Rating>
            (members, Vars::String_Variable(sort_algorithm_name));
    }

    Vector_t<Member_t*> Sort_Filled(Members_t* self, Int_t begin, Int_t end)
    {
        return Slice_Vector(Sort(Filled(self)), begin, end);
    }

    Vector_t<String_t> Race_Names(Members_t* self)
    {
        Vector_t<String_t> race_names;
        race_names.reserve(16);

        Range_t<Member_t**> members = Members(self);
        for (; members.begin < members.end; members.begin += 1) {
            String_t race_name = Member::Race_Name(*members.begin);
            if (!Vector::Has(race_names, race_name)) {
                race_names.push_back(race_name);
            }
        }

        return race_names;
    }

    void Enforce_Loaded(Members_t* self)
    {
        static const String_t event_name("Enforce");

        if (self) {
            struct Args : public IFunctionArguments {
                bool Copy(Output* output) { return true; }
            } args;

            Vector_t<Member_t*> vec_members = Loaded(self);
            for (u64 idx = 0, size = vec_members.size(); idx < size; idx += 1) {
                Member_t* member = vec_members[idx];
                Handle_t handle(member);
                handle.Registry()->QueueEvent(handle, &event_name, &args);
            }
        }
    }

}}}

#include "utils.h"

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    //template <typename Type>
    //inline Type_e

    class Function_t : public NativeFunction {
    public:
        Member_t* (*callback)(Members_t*, Actor_t*);

        Function_t(const char* function_name, const char* class_name, Member_t* (*callback)(Members_t*, Actor_t*), Registry_t* virtual_machine) :
            NativeFunction(function_name, class_name, IsStaticType<Members_t*>::value, 1), callback(callback)
        {
            m_retnType = reinterpret_cast<UInt64>(Member::Class_Info());
            m_params.data[0].type = reinterpret_cast<UInt64>(Class_Info_t::Fetch("Actor"));
            m_isLatent = false;
        }

        virtual ~Function_t()
        {
        }

        virtual bool Run(VMValue* base_variable,
                         Registry_t* virtual_machine,
                         UInt32 stack_id,
                         VMValue* return_variable,
                         VMState* stack_frame)
        {
            UInt32 args_offset = CALL_MEMBER_FN(stack_frame->argList, GetOffset)(stack_frame);

            // static/global function has to be handled slightly differently.

            Members_t* base = nullptr;
            UnpackValue(&base, base_variable);
            if (base) {
                Actor_t* arg_0;
                UnpackValue(&arg_0, CALL_MEMBER_FN(stack_frame->argList, Get)(stack_frame, 0, args_offset));

                Member_t* result = callback(base, arg_0);

                PackValue(return_variable, &result, virtual_machine);

                return true;
            } else {
                return false;
            }
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

        ADD_METHOD("p_From_ID", 1, Member_t*, From_ID, Int_t);
        ADD_METHOD("p_From_Actor", 1, Member_t*, From_Actor, Actor_t*);

        ADD_METHOD("Has_Actor", 1, Bool_t, Has_Actor, Actor_t*);
        ADD_METHOD("Hasnt_Actor", 1, Bool_t, Hasnt_Actor, Actor_t*);
        ADD_METHOD("Has_Head", 1, Bool_t, Has_Head, Actor_t*);
        ADD_METHOD("Hasnt_Head", 1, Bool_t, Hasnt_Head, Actor_t*);

        ADD_METHOD("Max", 0, Int_t, Max);
        ADD_METHOD("Count_Filled", 0, Int_t, Count_Filled);
        ADD_METHOD("Count_Unfilled", 0, Int_t, Count_Unfilled);
        ADD_METHOD("Count_Loaded", 0, Int_t, Count_Loaded);
        ADD_METHOD("Count_Unloaded", 0, Int_t, Count_Unloaded);
        ADD_METHOD("Count_Heads", 1, Int_t, Count_Heads, Actor_t*);

        ADD_METHOD("Filled", 0, Vector_t<Member_t*>, Filled);

        ADD_METHOD("Sort_Filled", 2, Vector_t<Member_t*>, Sort_Filled, Int_t, Int_t);

        ADD_METHOD("Race_Names", 0, Vector_t<String_t>, Race_Names);

        ADD_METHOD("Enforce_Loaded", 0, void, Enforce_Loaded);

        #undef ADD_METHOD

        return true;
    }

}}}}
