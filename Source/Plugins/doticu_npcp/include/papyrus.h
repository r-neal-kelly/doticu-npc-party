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
