/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "string2.h"

namespace doticu_npcp { namespace Papyrus {

    class Handle
    {
    private:
        Registry_t *m_registry = nullptr;
        Policy_t *m_policy = nullptr;
        Form_Type_t m_form_type = kFormType_None;
        Handle_ID_t m_handle = 0;

    public:
        Handle(Registry_t *registry, Policy_t *policy, Form_Type_t form_type, void *data)
        {
            m_registry = registry;
            m_policy = policy;
            m_form_type = form_type;
            m_handle = m_policy->Create(m_form_type, data);
        }
        Handle(Form_Type_t form_type, void *data)
        {
            m_registry = (*g_skyrimVM)->GetClassRegistry();
            m_policy = m_registry->GetHandlePolicy();
            m_form_type = form_type;
            m_handle = m_policy->Create(m_form_type, data);
        }
        Handle(Form_t *form)
        {
            m_registry = (*g_skyrimVM)->GetClassRegistry();
            m_policy = m_registry->GetHandlePolicy();
            m_form_type = form->formType;
            m_handle = m_policy->Create(m_form_type, form);
        }
        Handle(Alias_t *alias)
        {
            m_registry = (*g_skyrimVM)->GetClassRegistry();
            m_policy = m_registry->GetHandlePolicy();
            m_form_type = kFormType_Alias;
            m_handle = m_policy->Create(m_form_type, alias);
        }
        Handle()
        {
            m_registry = (*g_skyrimVM)->GetClassRegistry();
            m_policy = m_registry->GetHandlePolicy();
            m_form_type = kFormType_None;
            m_handle = m_policy->GetInvalidHandle();
        }
        ~Handle()
        {
            if (Is_Valid()) {
                m_policy->Release(m_handle);
            }
        }

        Handle_ID_t ID() { return m_handle; }
        Registry_t *Registry() { return m_registry; }
        Policy_t *Policy() { return m_policy; }

        bool Is_Valid() { return m_handle != m_policy->GetInvalidHandle(); }

        operator Handle_ID_t() const { return m_handle; }
    };

    class Variable : public IForEachScriptObjectFunctor
    {
    private:
        Handle m_handle;
        const char *m_script_name = nullptr;
        const char *m_variable_name = nullptr;
        Variable_t m_variable;

    public:
        Variable(Form_t *form, const char *script_name, const char *variable_name)
        {
            m_handle = Handle(form);
            m_script_name = script_name && script_name[0] != 0 ? script_name : nullptr;
            m_variable_name = variable_name;
            m_handle.Registry()->VisitScripts(m_handle, this);
        }
        Variable(Alias_t *alias, const char *script_name, const char *variable_name)
        {
            m_handle = Handle(alias);
            m_script_name = script_name && script_name[0] != 0 ? script_name : nullptr;
            m_variable_name = variable_name;
            m_handle.Registry()->VisitScripts(m_handle, this);
        }
        Variable(Form_t *form, const char *variable_name)
        {
            m_handle = Handle(form);
            m_script_name = nullptr;
            m_variable_name = variable_name;
            m_handle.Registry()->VisitScripts(m_handle, this);
        }
        Variable(Alias_t *alias, const char *variable_name)
        {
            m_handle = Handle(alias);
            m_script_name = nullptr;
            m_variable_name = variable_name;
            m_handle.Registry()->VisitScripts(m_handle, this);
        }

        virtual bool Visit(Script_t *script, void *)
        {
            if (script) {
                if (!m_script_name || String2::Is_Same_Caseless(script->classInfo->name.data, m_script_name)) {
                    String_t variable_name(m_variable_name);
                    Int_t variable_idx = CALL_MEMBER_FN(script->classInfo, GetVariable)(&variable_name);
                    if (variable_idx > -1) {
                        m_handle.Registry()->ExtractValue(m_handle, &script->classInfo->name, variable_idx, &m_variable);
                        return false; // break;
                    } else {
                        return true; // continue;
                    }
                } else {
                    return true; // continue;
                }
            } else {
                return true; // continue;
            }
        }

        bool Is_None()
        {
            return m_variable.GetUnmangledType() == Variable_t::kType_None;
        }

        bool Isnt_None()
        {
            return m_variable.GetUnmangledType() != Variable_t::kType_None;
        }

        Bool_t Bool()
        {
            if (m_variable.GetUnmangledType() == Variable_t::kType_Bool) {
                return m_variable.data.b;
            } else {
                return false;
            }
        }

        Int_t Int()
        {
            if (m_variable.GetUnmangledType() == Variable_t::kType_Int) {
                return m_variable.data.i;
            } else {
                return -1;
            }
        }

        Actor_t *Actor()
        {
            if (m_variable.GetUnmangledType() == Variable_t::kType_Identifier) {
                if (m_variable.data.id) {
                    return static_cast<Actor_t *>(m_handle.Policy()->Resolve(
                        kFormType_Character, m_variable.data.id->GetHandle()
                    ));
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        Alias_t *Alias()
        {
            if (m_variable.GetUnmangledType() == Variable_t::kType_Identifier) {
                if (m_variable.data.id) {
                    return static_cast<Alias_t *>(m_handle.Policy()->Resolve(
                        kFormType_Alias, m_variable.data.id->GetHandle()
                    ));
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        Object_t *Object()
        {
            if (m_variable.GetUnmangledType() == Variable_t::kType_Identifier) {
                if (m_variable.data.id) {
                    return static_cast<Object_t *>(m_handle.Policy()->Resolve(
                        kFormType_Reference, m_variable.data.id->GetHandle()
                    ));
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }
    };

    class Scripts : public IForEachScriptObjectFunctor
    {
    public:
        Handle handle;
        std::vector<const char *> names;
        std::vector<Script_t *> scripts;

        Scripts(Form_t *form)
        {
            handle = Papyrus::Handle(form);
            handle.Registry()->VisitScripts(handle, this);
        }
        Scripts(Alias_t *alias)
        {
            handle = Papyrus::Handle(alias);
            handle.Registry()->VisitScripts(handle, this);
        }

        virtual bool Visit(Script_t *script, void *)
        {
            //_MESSAGE("%s", script->classInfo->name.data);
            names.push_back(script->classInfo->name.data);
            scripts.push_back(script);
            return true;
        }

        Script_t *Script(const char *script_name)
        {
            for (u64 idx = 0, size = names.size(); idx < size; idx += 1) {
                if (_stricmp(script_name, names[idx]) == 0) {
                    return scripts[idx];
                }
            }

            return nullptr;
        }
    };

    class Script : public IForEachScriptObjectFunctor
    {
    public:
        Handle m_handle;
        const char* m_name = nullptr;
        Script_t* m_script = nullptr;

        Script(Form_t* form, const char* name)
        {
            m_handle = Papyrus::Handle(form);
            m_name = name;
            m_handle.Registry()->VisitScripts(m_handle, this);
        }
        Script(Alias_t* alias, const char* name)
        {
            m_handle = Papyrus::Handle(alias);
            m_name = name;
            m_handle.Registry()->VisitScripts(m_handle, this);
        }

        virtual bool Visit(Script_t* script, void*)
        {
            if (String2::Is_Same_Caseless(m_name, script->classInfo->name.data)) {
                m_script = script;
                return false; // break
            } else {
                return true; // continue
            }
        }

        operator Script_t* ()
        {
            return m_script;
        }

        operator void* ()
        {
            return static_cast<void*>(m_script);
        }
    };

    // a lot of the credit for deciphering these types goes to Ryan-rsm-McKenzie of CommonLibSSE
    class Object
    {
    public:
        class Info
        {
        public:
            class Type_Info
            {
            public:
                enum class Type_t : UInt64
                {
                    TYPE_NONE = 0,
                    TYPE_OBJECT = 1,
                    TYPE_STRING = 2,
                    TYPE_INT = 3,
                    TYPE_FLOAT = 4,
                    TYPE_BOOL = 5,

                    TYPE_NONE_ARRAY = 10,
                    TYPE_OBJECT_ARRAY = 11,
                    TYPE_STRING_ARRAY = 12,
                    TYPE_INT_ARRAY = 13,
                    TYPE_FLOAT_ARRAY = 14,
                    TYPE_BOOL_ARRAY = 15
                };

                Type_t raw;

                Type_t Type();
                Object::Info* Object_Info();
                String_t To_String();
                bool Is_None();
                bool Is_Object();
                bool Is_String();
                bool Is_Int();
                bool Is_Float();
                bool Is_Bool();
                bool Is_None_Array();
                bool Is_Object_Array();
                bool Is_String_Array();
                bool Is_Int_Array();
                bool Is_Float_Array();
                bool Is_Bool_Array();
            };

            struct Setting_t
            {
                UInt64 unk_00; // 00
            };
            STATIC_ASSERT(sizeof(Setting_t) == 0x8);

            struct Variable_t
            {
                String_t name; // 00
                Type_Info type; // 08
            };
            STATIC_ASSERT(sizeof(Variable_t) == 0x10);

            struct Default_t
            {
                UInt32 variable_idx; // 00
                UInt32 pad_04; // 04
                Papyrus::Variable_t variable; // 08
            };
            STATIC_ASSERT(sizeof(Default_t) == 0x18);

            struct Property_t
            {
                String_t name; // 00
                String_t parent_name; // 08
                String_t property_name; // 10
                Type_Info type; // 18
                UInt32 flags_20; // 20
                UInt32 unk_24; // 24
                IFunction* getter; // 28
                IFunction* setter; // 30
                UInt32 auto_var_idx; // 38
                UInt32 flags_3C; // 3C
                String_t unk_40; // 40
            };
            STATIC_ASSERT(sizeof(Property_t) == 0x48);

            UInt32 ref_count; // 00
            UInt32 pad_04; // 04
            String_t name; // 08
            Info* parent; // 10
            String_t unk_18; // 18
            UInt32 flags_20; // 20
            UInt32 flags_24; // 24
            UInt32 flags_28; // 28
            UInt32 pad_2C; // 2C
            UInt8* data; // 30

            UInt64 Count_Settings();
            UInt64 Count_Variables();
            UInt64 Count_Defaults();
            UInt64 Count_Properties();

            Setting_t* Settings();
            Variable_t* Variables();
            Default_t* Defaults();
            Property_t* Properties();

            SInt64 Variable_Index(String_t variable_name);
            SInt64 Property_Index(String_t property_name);
            Property_t* Property(String_t property_name);

            void Log();
            void Log_Settings();
            void Log_Variables();
            void Log_Defaults();
            void Log_Properties();
        };
        STATIC_ASSERT(sizeof(Info) == 0x38);

        Handle m_handle;
        Entity_t* m_obj = nullptr;
        Info* m_info = nullptr;
        Variable_t* m_vars = nullptr;

    private:
        void _Object(const char* class_name);

    public:
        Object(Form_t* form, const char* class_name);
        Object(Alias_t* alias, const char* class_name);
    
        bool Is_Valid();

        bool Read_Property(String_t property_name, Variable_t& in_variable);
        bool Write_Property(String_t property_name, Variable_t& out_variable);

        Variable_t* Property(String_t property_name);
        Variable_t* Variable(String_t variable_name);

        void Log_Variables();

        operator Entity_t*();
    };

    class IFunction_Callback_Functor
    {
    public:
        virtual ~IFunction_Callback_Functor() = default; // 00
        virtual void operator()(Variable_t result) = 0; // 01
        virtual bool Can_Save() { return false; } // 02
        virtual void Entity(Papyrus::Entity_t** entity) = 0; // 03

        UInt32 ref_count = 0; // 00
        UInt32 pad_04 = 0; // 04
    };

    typedef IFunctionArguments IFunction_Arguments_Functor;

    template <typename Type>
    Vector_t<Type> Slice_Array(Array_t<Type> arr, SInt32 from, SInt32 to_exclusive)
    {
        Vector_t<Type> slice;
        u64 arr_size = arr.Length();

        if (from < 0) {
            from = 0;
        } else if (from > arr_size) {
            from = arr_size;
        }

        if (to_exclusive > arr_size || to_exclusive < 0) {
            to_exclusive = arr_size;
        }

        s64 slice_size = to_exclusive - from;
        if (slice_size > 0) {
            slice.reserve(slice_size);
            for (u64 idx = from, end = to_exclusive; idx < end; idx += 1) {
                Type elem;
                arr.Get(&elem, idx);
                slice.push_back(elem);
            }
        }

        return slice;
    }

    template <typename Type>
    Vector_t<Type> Slice_Vector(Vector_t<Type> vec, SInt32 from, SInt32 to_exclusive)
    {
        Vector_t<Type> slice;
        u64 vec_size = vec.size();

        if (from < 0) {
            from = 0;
        } else if (from > vec_size) {
            from = vec_size;
        }

        if (to_exclusive > vec_size || to_exclusive < 0) {
            to_exclusive = vec_size;
        }

        s64 slice_size = to_exclusive - from;
        if (slice_size > 0) {
            slice.reserve(slice_size);
            for (u64 idx = from, end = to_exclusive; idx < end; idx += 1) {
                slice.push_back(vec[idx]);
            }
        }

        return slice;
    }

}}

namespace doticu_npcp { namespace Papyrus { namespace Exports {

    bool Register(Registry_t *registry);

}}}
