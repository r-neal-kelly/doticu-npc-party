/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "cell.h"
#include "codes.h"
#include "form_vector.h"
#include "object_ref.h"
#include "outfit.h"
#include "party.h"
#include "party.inl"
#include "utils.h"
#include "vars.h"

namespace doticu_npcp { namespace Party {

    String_t NPCS_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_npcs");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* NPCS_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    NPCS_t* NPCS_t::Self()
    {
        static NPCS_t* self = static_cast<NPCS_t*>(Consts::Funcs_Quest());
        NPCP_ASSERT(self);
        return self;
    }

    void NPCS_t::Initialize()
    {
        Int_t reserve = 8;

        Bases_Variable()->Pack(
            Form_Vector_t::Create(reserve, nullptr, 1.5f)
        );
        Default_Outfits_Variable()->Pack(
            Form_Vector_t::Create(reserve, nullptr, 1.5f)
        );
    }

    void NPCS_t::Uninitialize()
    {
        Variable_t* default_outfits_variable = Default_Outfits_Variable();
        if (default_outfits_variable->Has_Object()) {
            Form_Vector_t::Destroy(
                static_cast<Form_Vector_t*>(default_outfits_variable->Reference())
            );
        }
        default_outfits_variable->None(Form_Vector_t::Class_Info());

        Variable_t* bases_variable = Bases_Variable();
        if (bases_variable->Has_Object()) {
            Form_Vector_t::Destroy(
                static_cast<Form_Vector_t*>(bases_variable->Reference())
            );
        }
        bases_variable->None(Form_Vector_t::Class_Info());
    }

    void NPCS_t::Reinitialize()
    {
        Uninitialize();
        Initialize();

        Vector_t<Member_t*> members = Members_t::Self()->Filled();
        for (size_t idx = 0, count = members.size(); idx < count; idx += 1) {
            Actor_t* actor = members.at(idx)->Actor();
            Add_Base_If_Needed(actor, actor);
        }
    }

    Object_t* NPCS_t::Object()
    {
        Object_t* object = Object_t::Fetch(this, Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* NPCS_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* NPCS_t::Bases_Variable()
    {
        static const String_t variable_name = String_t("p_vec_bases");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* NPCS_t::Default_Outfits_Variable()
    {
        static const String_t variable_name = String_t("p_vec_outfits_def");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Form_Vector_t* NPCS_t::Bases()
    {
        Form_Vector_t* bases = static_cast<Form_Vector_t*>
            (Bases_Variable()->Reference());
        if (!bases) {
            _MESSAGE("npcs base array was not created. reinitializing.");
            Reinitialize();
            bases = static_cast<Form_Vector_t*>
                (Bases_Variable()->Reference());
        }
        NPCP_ASSERT(bases);
        return bases;
    }

    Form_Vector_t* NPCS_t::Default_Outfits()
    {
        Form_Vector_t* default_outfits = static_cast<Form_Vector_t*>
            (Default_Outfits_Variable()->Reference());
        if (!default_outfits) {
            _MESSAGE("npcs default outfit array was not created. reinitializing.");
            Reinitialize();
            default_outfits = static_cast<Form_Vector_t*>
                (Default_Outfits_Variable()->Reference());
        }
        NPCP_ASSERT(default_outfits);
        return default_outfits;
    }

    Actor_Base_t* NPCS_t::Base(Actor_t* actor)
    {
        NPCP_ASSERT(actor);
        Actor_Base_t* real_base = Actor2::Real_Base(actor);
        NPCP_ASSERT(real_base);
        return real_base;
    }

    Int_t NPCS_t::Base_Idx(Actor_t* actor)
    {
        NPCP_ASSERT(actor);
        return Bases()->Find(Base(actor));
    }

    Outfit_t* NPCS_t::Default_Outfit(Int_t base_idx)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Default_Outfits()->Count());
        Outfit_t* default_outfit = static_cast<Outfit_t*>(Default_Outfits()->At(base_idx));
        NPCP_ASSERT(default_outfit);
        return default_outfit;
    }

    Bool_t NPCS_t::Has_Base(Actor_t* actor)
    {
        NPCP_ASSERT(actor);
        return Bases()->Has(Base(actor));
    }

    Int_t NPCS_t::Add_Base_If_Needed(Actor_t* actor_with_base, Actor_t* actor_with_outfit)
    {
        NPCP_ASSERT(actor_with_base);
        NPCP_ASSERT(actor_with_outfit);

        Int_t base_idx = Base_Idx(actor_with_base);
        if (base_idx < 0) {
            Outfit_t* default_outfit = Actor2::Base_Outfit(actor_with_outfit);
            if (!default_outfit) {
                default_outfit = Consts::Empty_Outfit();
            }

            Outfit::Add_Item(default_outfit, Consts::Blank_Armor()); // maybe redundant, outfitter checks it

            Form_Vector_t* bases = Bases();
            base_idx = bases->Count();
            bases->Push(Base(actor_with_base));
            Default_Outfits()->Push(default_outfit);

            return base_idx;
        } else {
            return base_idx;
        }
    }

    void NPCS_t::Remove_Base_If_Needed(Int_t base_idx)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Bases()->Count());

        Outfit_t* default_outfit = Default_Outfit(base_idx);
        Outfit::Remove_Item(default_outfit, Consts::Blank_Armor()); // added back by outfitter when needed.

        Bases()->Remove_Unstable(base_idx);
        Default_Outfits()->Remove_Unstable(base_idx);
    }

    void NPCS_t::Add_Original(Actor_t* original)
    {
        NPCP_ASSERT(original);
        Add_Base_If_Needed(original, original);
    }

    void NPCS_t::Remove_Original(Actor_t* original)
    {
        NPCP_ASSERT(original);
        Remove_Base_If_Needed(Base_Idx(original));
    }

    Actor_t* NPCS_t::Add_Clone(Actor_t* original)
    {
        NPCP_ASSERT(original);

        Actor_t* clone = Actor2::Clone(original);

        String_t original_name;
        Member_t* original_member = Members_t::Self()->From_Actor(original);
        if (original_member) {
            original_name = original_member->Name();
        } else {
            original_name = Actor2::Get_Name(original);
        }
        Object_Ref::Rename(clone, (std::string("Clone of ") + original_name.data).c_str());

        Int_t base_idx = Add_Base_If_Needed(clone, original);

        Object_Ref::Remove_All_Items(clone);
        Actor2::Set_Outfit_Basic(clone, Default_Outfit(clone), false, false);

        Int_t clone_outfit = Vars::Clone_Outfit();
        if (clone_outfit == CODES::OUTFIT::BASE) {
            Actor2::Flag_Outfit1_As_Outfit2(clone);
        } else if (clone_outfit == CODES::OUTFIT::REFERENCE) {
            Reference_t* trash = Object_Ref::Create_Container();
            Actor2::Set_Outfit2(clone, nullptr, original, trash);
            Object_Ref::Delete_Safe(trash);
            Remove_All_Tokens(clone);
        }

        return clone;
    }

    void NPCS_t::Remove_Clone(Actor_t* clone, Bool_t do_delete_clone)
    {
        NPCP_ASSERT(clone);
        Remove_Base_If_Needed(Base_Idx(clone));

        if (do_delete_clone) {
            Object_Ref::Delete_Safe(clone);
        }
    }

    Outfit_t* NPCS_t::Default_Outfit(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Int_t base_idx = Base_Idx(actor);
        if (base_idx > -1) {
            return Default_Outfit(base_idx);
        } else {
            return nullptr;
        }
    }

    void NPCS_t::Change_Default_Outfit(Actor_t* actor, Outfit_t* default_outfit)
    {
        NPCP_ASSERT(actor);
        
        if (!default_outfit) {
            default_outfit = Consts::Empty_Outfit();
        }

        Int_t base_idx = Base_Idx(actor);
        if (base_idx > -1) {
            Outfit::Remove_Item(Default_Outfit(base_idx), Consts::Blank_Armor());
            Outfit::Add_Item(default_outfit, Consts::Blank_Armor());
            Default_Outfits()->Set(base_idx, default_outfit);
        }
    }

    void NPCS_t::Remove_All_Tokens(Actor_t* actor)
    {
        if (actor) {
            Object_Ref::Untoken(actor, Consts::Member_Token());
            Object_Ref::Untoken(actor, Consts::Generic_Token());
            Object_Ref::Untoken(actor, Consts::Clone_Token());
            Object_Ref::Untoken(actor, Consts::Greeter_Token());
            Object_Ref::Untoken(actor, Consts::Movee_Token());
            Object_Ref::Untoken(actor, Consts::Immobile_Token());
            Object_Ref::Untoken(actor, Consts::Settler_Token());
            Object_Ref::Untoken(actor, Consts::Thrall_Token());
            Object_Ref::Untoken(actor, Consts::Paralyzed_Token());
            Object_Ref::Untoken(actor, Consts::Mannequin_Token());
            Object_Ref::Untoken(actor, Consts::Display_Token());
            Object_Ref::Untoken(actor, Consts::Reanimated_Token());
            Object_Ref::Untoken(actor, Consts::Banished_Token());
            Object_Ref::Untoken(actor, Consts::Default_Style_Token());
            Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
            Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
            Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
            Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
            Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Follower_Token());
            Object_Ref::Untoken(actor, Consts::Sneak_Follower_Token());
            Object_Ref::Untoken(actor, Consts::Saddler_Token());
            Object_Ref::Untoken(actor, Consts::Retreater_Token());
        }
    }

    void NPCS_t::u_0_9_3()
    {
        Form_Vector_t* bases = Bases();
        Form_Vector_t* default_outfits = Default_Outfits();

        Vector_t<Reference_t*> form_vectors = Cell::References(Consts::Storage_Cell(), Consts::Form_Vector());
        for (size_t idx = 0, count = form_vectors.size(); idx < count; idx += 1) {
            Form_Vector_t* form_vector = static_cast<Form_Vector_t*>(form_vectors.at(idx));
            if (form_vector != bases && form_vector != default_outfits) {
                Form_Vector_t::Destroy(form_vector);
            }
        }
    }

    void NPCS_t::Register_Me(Registry_t* registry)
    {
        auto Initialize = [](NPCS_t* self)->void FORWARD_VOID(NPCS_t::Initialize());
        auto Uninitialize = [](NPCS_t* self)->void FORWARD_VOID(NPCS_t::Uninitialize());

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), NPCS_t,                      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("f_Initialize", 0, void, Initialize);
        ADD_METHOD("f_Uninitialize", 0, void, Uninitialize);

        #undef ADD_METHOD
    }

}}
