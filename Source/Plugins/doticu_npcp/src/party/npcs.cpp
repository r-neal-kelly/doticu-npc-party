/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "form_vector.h"
#include "object_ref.h"
#include "outfit.h"
#include "party.h"
#include "party.inl"
#include "utils.h"
#include "vars.h"

/*

    A Bases vector maps keys to several other vectors:
    Original_Vectors is a vector of vectors of original actors.
    Clone_Vectors is a vector of vectors of clone actors.
    Default_Outfits is a vector of outfits per real npc base.

    The original vectors can only contain actors that are original,
    and the clone vectors actors that are clones. They shall not have
    duplicates within or outside themselves.

    Each vector in the two vector of vectors is created on demand, and
    when emptied, is destroyed and replace with nullptr in the system.
    Each vector in the system maintains the same count as Bases vector.
    Bases and Default Outfits may never have a nullptr.

    A clone is kept in the system as a clone until they are
    destroyed. They may never be in the original vectors.

*/

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
        Original_Vectors_Variable()->Pack(
            Form_Vector_t::Create(reserve, nullptr, 1.5f)
        );
        Clone_Vectors_Variable()->Pack(
            Form_Vector_t::Create(reserve, nullptr, 1.5f)
        );
        Default_Outfits_Variable()->Pack(
            Form_Vector_t::Create(reserve, nullptr, 1.5f)
        );
    }

    void NPCS_t::Uninitialize()
    {
        Form_Vector_t::Destroy(Default_Outfits());

        Form_Vector_t* clone_vectors = Clone_Vectors();
        for (size_t idx = 0, count = clone_vectors->Count(); idx < count; idx += 1) {
            Form_Vector_t::Destroy(
                static_cast<Form_Vector_t*>(clone_vectors->At(idx))
            );
        }
        Form_Vector_t::Destroy(clone_vectors);

        Form_Vector_t* original_vectors = Original_Vectors();
        for (size_t idx = 0, count = original_vectors->Count(); idx < count; idx += 1) {
            Form_Vector_t::Destroy(
                static_cast<Form_Vector_t*>(original_vectors->At(idx))
            );
        }
        Form_Vector_t::Destroy(original_vectors);

        Form_Vector_t::Destroy(Bases());

        Default_Outfits_Variable()->None();
        Clone_Vectors_Variable()->None();
        Original_Vectors_Variable()->None();
        Bases_Variable()->None();
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

    Variable_t* NPCS_t::Original_Vectors_Variable()
    {
        static const String_t variable_name = String_t("p_vec_vec_origs");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* NPCS_t::Clone_Vectors_Variable()
    {
        static const String_t variable_name = String_t("p_vec_vec_clones");
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
        NPCP_ASSERT(bases);
        return bases;
    }

    Form_Vector_t* NPCS_t::Original_Vectors()
    {
        Form_Vector_t* original_vectors = static_cast<Form_Vector_t*>
            (Original_Vectors_Variable()->Reference());
        NPCP_ASSERT(original_vectors);
        return original_vectors;
    }

    Form_Vector_t* NPCS_t::Clone_Vectors()
    {
        Form_Vector_t* clone_vectors = static_cast<Form_Vector_t*>
            (Clone_Vectors_Variable()->Reference());
        NPCP_ASSERT(clone_vectors);
        return clone_vectors;
    }

    Form_Vector_t* NPCS_t::Default_Outfits()
    {
        Form_Vector_t* default_outfits = static_cast<Form_Vector_t*>
            (Default_Outfits_Variable()->Reference());
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

    Form_Vector_t* NPCS_t::Originals(Int_t base_idx)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Original_Vectors()->Count());
        return static_cast<Form_Vector_t*>(Original_Vectors()->At(base_idx));
    }

    Form_Vector_t* NPCS_t::Clones(Int_t base_idx)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Clone_Vectors()->Count());
        return static_cast<Form_Vector_t*>(Clone_Vectors()->At(base_idx));
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

    Bool_t NPCS_t::Has_Original(Int_t base_idx, Actor_t* actor)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Bases()->Count());
        NPCP_ASSERT(actor);

        Form_Vector_t* originals = Originals(base_idx);
        if (originals) {
            return originals->Has(actor);
        } else {
            return false;
        }
    }

    Bool_t NPCS_t::Has_Clone(Int_t base_idx, Actor_t* actor)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Bases()->Count());
        NPCP_ASSERT(actor);

        Form_Vector_t* clones = Clones(base_idx);
        if (clones) {
            return clones->Has(actor);
        } else {
            return false;
        }
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
            Original_Vectors()->Push(nullptr);
            Clone_Vectors()->Push(nullptr);
            Default_Outfits()->Push(default_outfit);

            return base_idx;
        } else {
            return base_idx;
        }
    }

    void NPCS_t::Remove_Base_If_Needed(Int_t base_idx)
    {
        NPCP_ASSERT(base_idx > -1 && base_idx < Bases()->Count());

        if (!Originals(base_idx) && !Clones(base_idx)) {
            Outfit_t* default_outfit = Default_Outfit(base_idx);
            Outfit::Remove_Item(default_outfit, Consts::Blank_Armor()); // added back by outfitter when needed.

            Bases()->Remove_Unstable(base_idx);
            Original_Vectors()->Remove_Unstable(base_idx);
            Clone_Vectors()->Remove_Unstable(base_idx);
            Default_Outfits()->Remove_Unstable(base_idx);
        }
    }

    void NPCS_t::Add_Original(Actor_t* original)
    {
        NPCP_ASSERT(original);

        Int_t base_idx = Add_Base_If_Needed(original, original);
        if (!Has_Clone(base_idx, original)) {
            Form_Vector_t* originals = Originals(base_idx);
            if (!originals) {
                originals = Form_Vector_t::Create(1, nullptr, 1.5f);
                Original_Vectors()->Set(base_idx, originals);
                originals->Push(original);
            } else if (!originals->Has(original)) {
                originals->Push(original);
            }
        }
    }

    void NPCS_t::Remove_Original(Actor_t* original)
    {
        NPCP_ASSERT(original);

        Int_t base_idx = Base_Idx(original);
        NPCP_ASSERT(base_idx > -1);

        Form_Vector_t* originals = Originals(base_idx);
        if (originals) {
            Int_t original_idx = originals->Find(original);
            if (original_idx > -1) {
                originals->Remove_Unstable(original_idx);
                if (originals->Count() < 1) {
                    Original_Vectors()->Set(base_idx, nullptr);
                    Form_Vector_t::Destroy(originals);
                    Remove_Base_If_Needed(base_idx);
                }
            }
        }
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
        Form_Vector_t* clones = Clones(base_idx);
        if (!clones) {
            clones = Form_Vector_t::Create(1, nullptr, 1.5f);
            Clone_Vectors()->Set(base_idx, clones);
            clones->Push(clone);
        } else if (!clones->Has(clone)) {
            clones->Push(clone);
        }

        Object_Ref::Remove_All_Items(clone);
        Actor2::Set_Outfit_Basic(clone, Default_Outfit(clone), false, false);

        if (Vars::Clone_Outfit() == CODES::OUTFIT::REFERENCE) {
            Reference_t* trash = Object_Ref::Create_Container();
            Actor2::Set_Outfit2(clone, nullptr, original, trash);
            Object_Ref::Delete_Safe(trash);
            Remove_All_Tokens(clone);
        }

        return clone;
    }

    void NPCS_t::Remove_Clone(Actor_t* clone)
    {
        NPCP_ASSERT(clone);

        Int_t base_idx = Base_Idx(clone);
        NPCP_ASSERT(base_idx > -1);

        Form_Vector_t* clones = Clones(base_idx);
        if (clones) {
            Int_t clone_idx = clones->Find(clone);
            if (clone_idx > -1) {
                clones->Remove_Unstable(clone_idx);
                Object_Ref::Delete_Safe(clone);
                if (clones->Count() < 1) {
                    Clone_Vectors()->Set(base_idx, nullptr);
                    Form_Vector_t::Destroy(clones);
                    Remove_Base_If_Needed(base_idx);
                }
            }
        }
    }

    Bool_t NPCS_t::Is_Original(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Int_t base_idx = Base_Idx(actor);
        if (base_idx > -1) {
            return Has_Original(base_idx, actor);
        } else {
            return false;
        }
    }

    Bool_t NPCS_t::Is_Clone(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Int_t base_idx = Base_Idx(actor);
        if (base_idx > -1) {
            return Has_Clone(base_idx, actor);
        } else {
            return false;
        }
    }

    Bool_t NPCS_t::Should_Clone(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        return
            (Actor2::Is_Unique(actor) && Vars::Do_Force_Clone_Unique()) ||
            (Actor2::Is_Generic(actor) && Vars::Do_Force_Clone_Generic());
    }

    Bool_t NPCS_t::Should_Unclone(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        if (Is_Clone(actor)) {
            return
                (Actor2::Is_Unique(actor) && Vars::Do_Force_Unclone_Unique()) ||
                (Actor2::Is_Generic(actor) && Vars::Do_Force_Unclone_Generic());
        } else {
            return false;
        }
    }

    Vector_t<Actor_t*> NPCS_t::Originals(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Int_t base_idx = Base_Idx(actor);
        if (base_idx > -1) {
            Form_Vector_t* originals = Originals(base_idx);
            if (originals) {
                return *reinterpret_cast<Vector_t<Actor_t*>*>(&originals->Vector());
            } else {
                return Vector_t<Actor_t*>();
            }
        } else {
            return Vector_t<Actor_t*>();
        }
    }

    Vector_t<Actor_t*> NPCS_t::Clones(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Int_t base_idx = Base_Idx(actor);
        if (base_idx > -1) {
            Form_Vector_t* clones = Clones(base_idx);
            if (clones) {
                return *reinterpret_cast<Vector_t<Actor_t*>*>(&clones->Vector());
            } else {
                return Vector_t<Actor_t*>();
            }
        } else {
            return Vector_t<Actor_t*>();
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

    void NPCS_t::Register_Me(Registry_t* registry)
    {
        auto Initialize = [](NPCS_t* self)->void FORWARD_VOID(NPCS_t::Initialize());
        auto Uninitialize = [](NPCS_t* self)->void FORWARD_VOID(NPCS_t::Uninitialize());
        auto Remove_Original = [](NPCS_t* self, Actor_t* original)->void FORWARD_VOID(NPCS_t::Remove_Original(original));
        auto Remove_Clone = [](NPCS_t* self, Actor_t* clone)->void FORWARD_VOID(NPCS_t::Remove_Clone(clone));

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), NPCS_t,                      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("f_Initialize", 0, void, Initialize);
        ADD_METHOD("f_Uninitialize", 0, void, Uninitialize);
        ADD_METHOD("Remove_Original", 1, void, Remove_Original, Actor_t*);
        ADD_METHOD("Remove_Clone", 1, void, Remove_Clone, Actor_t*);

        #undef ADD_METHOD
    }

}}
