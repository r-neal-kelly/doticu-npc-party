/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <cstring>

#include "skse64/GameAPI.h"
#include "skse64/GameExtraData.h"
#include "skse64/GameForms.h"
#include "skse64/GameReferences.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"
#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PapyrusValue.h"
#include "skse64/PapyrusVM.h"

#define M \
    do {

#define W \
    } while (0)

#define Bit_Set(BITS, BIT_IDX) \
    ( (BITS) |=  ( (1llu) << (BIT_IDX) ) )

#define Bit_Unset(BITS, BIT_IDX) \
    ( (BITS) &= ~( (1llu) << (BIT_IDX) ) )

#define Bit_Is_Set(BITS, BIT_IDX) \
    ( (1llu) &   ( (BITS) >> (BIT_IDX) ) )

#define Bit_Toggle(BITS, BIT_IDX) \
    ( (BITS) ^=  ( (1llu) << (BIT_IDX) ) )

#define Bit_Clear(BITS)\
    ( (BITS) = 0 )

#define DOTICU_NPCP_PRINT_PREFIX "doticu_npcp: "

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

static IDebugLog gLog;

namespace doticu_npcp {

    class Object_Handle {
    private:
        VMClassRegistry *p_ptr_registry;
        IObjectHandlePolicy *p_ptr_policy;
        UInt32 p_type;
        UInt64 p_hnd;

    public:
        // ctors, dtors
        Object_Handle(VMClassRegistry *ptr_registry, IObjectHandlePolicy *ptr_policy, UInt32 type, void *data) {
            p_ptr_registry = ptr_registry;
            p_ptr_policy = ptr_policy;
            p_type = type;
            p_hnd = p_ptr_policy->Create(p_type, data);
        }
        Object_Handle(UInt32 type, void *data) {
            p_ptr_registry = (*g_skyrimVM)->GetClassRegistry();
            p_ptr_policy = p_ptr_registry->GetHandlePolicy();
            p_type = type;
            p_hnd = p_ptr_policy->Create(p_type, data);
        }
        Object_Handle() {
            p_ptr_registry = (*g_skyrimVM)->GetClassRegistry();
            p_ptr_policy = p_ptr_registry->GetHandlePolicy();
            p_type = 0;
            p_hnd = p_ptr_policy->GetInvalidHandle();
        }
        ~Object_Handle() {
            if (Exists()) {
                p_ptr_policy->Release(p_hnd);
            }
        }

        // getters
        UInt64 Val() {
            return p_hnd;
        }
        VMClassRegistry *Registry() {
            return p_ptr_registry;
        }
        IObjectHandlePolicy *Policy() {
            return p_ptr_policy;
        }

        // bools
        bool Exists() {
            return p_hnd != p_ptr_policy->GetInvalidHandle();
        }

        // Overloads
        operator UInt64() const {
            return p_hnd;
        }
    };

    class Object_Value {
    private:
        Object_Handle *p_hnd_object;
        BSFixedString p_str_value;
        VMValue p_vm_value;

    public:
        // ctors, dtors
        Object_Value(Object_Handle *hnd_object, const char *str_value) {
            p_hnd_object = hnd_object;
            p_str_value = BSFixedString(str_value);
            if (!p_hnd_object || !p_hnd_object->Exists()) {
                return;
            }

            class Functor : public IForEachScriptObjectFunctor {
            private:
                BSFixedString *p_str_value;
                VMScriptInstance *p_ptr_script;
                SInt32 p_idx_value = -1;
            public:
                Functor(BSFixedString *str_value) {
                    p_str_value = str_value;
                }
                virtual bool Visit(VMScriptInstance *ptr_script, void *) {
                    // this function seems to be consistent only if there is one script on the object?
                    if (ptr_script) {
                        SInt32 idx_value = CALL_MEMBER_FN(ptr_script->classInfo, GetVariable)(p_str_value);
                        if (idx_value > -1) {
                            p_ptr_script = ptr_script;
                            p_idx_value = idx_value;
                            return false; // stop iterating
                        }
                        return true; // keep iterating
                    } else {
                        return true; // keep iterating
                    }
                }
                VMScriptInstance *Script() {
                    return p_ptr_script;
                }
                SInt32 Idx() {
                    return p_idx_value;
                }
            } functor(&p_str_value);

            p_hnd_object->Registry()->VisitScripts(p_hnd_object->Val(), &functor);
            
            VMScriptInstance *ptr_script = functor.Script();
            if (!ptr_script) {
                _MESSAGE("not a script, %s:%d", __FILE__, __LINE__);
                return;
            }

            SInt32 idx_value = functor.Idx();
            if (idx_value < 0) {
                _MESSAGE("not a variable, %s:%d", __FILE__, __LINE__);
                return;
            }

            p_hnd_object->Registry()->ExtractValue(p_hnd_object->Val(), &ptr_script->classInfo->name, idx_value, &p_vm_value);
        }

        // bools
        bool Exists() {
            return p_vm_value.GetUnmangledType() != VMValue::kType_None;
        }

        // getters
        bool As_Bool() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Bool) {
                _MESSAGE("not a bool, %s:%d", __FILE__, __LINE__);
                return false;
            } else {
                return p_vm_value.data.b;
            }
        }
        SInt32 As_Int() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Int) {
                _MESSAGE("not an int, %s:%d", __FILE__, __LINE__);
                return -1;
            } else {
                return p_vm_value.data.i;
            }
        }
        Actor *As_Actor() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Identifier) {
                _MESSAGE("not an actor, %s:%d", __FILE__, __LINE__);
                return NULL;
            } else {
                return (Actor *)p_hnd_object->Policy()->Resolve(kFormType_Character, p_vm_value.data.id->GetHandle());
            }
        }
    };

    // doticu_npcp.cpp
    bool Register_Functions(VMClassRegistry *registry);

    // actor.cpp
    void Actor_Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit);

    // alias.cpp
    Actor *Alias_Get_Actor(BGSBaseAlias *ptr_alias);
    SInt32 Alias_Get_Rating(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Original(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Clone(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Follower(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Settler(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Immobile(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Thrall(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Paralyzed(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Mannequin(BGSBaseAlias *ptr_alias);
    bool Alias_Is_Reanimated(BGSBaseAlias *ptr_alias);

    // aliases.cpp
    VMResultArray<BGSBaseAlias *> Aliases_Slice(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr, UInt32 idx_from, UInt32 idx_to_ex);
    VMResultArray<BGSBaseAlias *> Aliases_Sort(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, BSFixedString str_algorithm);
    VMResultArray<BGSBaseAlias *> Aliases_Filter(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, BSFixedString str_sex, BSFixedString str_race, UInt32 int_flags);
    UInt32 Aliases_Filter_Flag(StaticFunctionTag *, UInt32 int_flags, BSFixedString str_command, BSFixedString str_flag);
    VMResultArray<BSFixedString> Aliases_Get_Race_Names(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases);
    VMResultArray<UInt32> Aliases_Update_Free(StaticFunctionTag *, VMArray<UInt32> arr_free, UInt32 size_new);

    // forms.cpp
    VMResultArray<TESForm *> Forms_Slice(StaticFunctionTag *, VMArray<TESForm *> arr, UInt32 idx_from, UInt32 idx_to_ex);

    // outfit.cpp
    void Outfit_Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);
    void Outfit_Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);

    // utils.cpp
    void Print(StaticFunctionTag *, BSFixedString str);

}
