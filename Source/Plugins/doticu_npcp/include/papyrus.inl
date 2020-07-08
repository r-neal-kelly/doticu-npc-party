/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus {

    // Virtual_Machine_t

    inline Virtual_Machine_t* Virtual_Machine_t::Self()
    {
        static Virtual_Machine_t* const virtual_machine =
            reinterpret_cast<Virtual_Machine_t*>((*g_skyrimVM)->GetClassRegistry());
        return virtual_machine;
    }

    // Handle_t

    inline Registry_t* Handle_t::Registry()
    {
        static Registry_t* registry = (*g_skyrimVM)->GetClassRegistry();
        return registry;
    }

    inline Policy_t* Handle_t::Policy()
    {
        static Policy_t* policy = Registry()->GetHandlePolicy();
        return policy;
    }

    template <typename Type>
    inline Handle_t::Handle_t(Type* instance)
    {
        if (instance) {
            handle = Policy()->Create(Type::kTypeID, instance);
        } else {
            handle = Policy()->GetInvalidHandle();
        }
    }

    inline Handle_t::Handle_t(Form_t* form)
    {
        if (form) {
            handle = Policy()->Create(form->formType, form);
        } else {
            handle = Policy()->GetInvalidHandle();
        }
    }

    inline Handle_t::Handle_t(UInt64 handle) :
        handle(handle)
    {
    }

    inline Handle_t::Handle_t() :
        handle(Policy()->GetInvalidHandle())
    {
    }

    // doing this causes a lot of warnings to pop up in the log.
    // it does not seem to be necessary for our purposes.
    /*inline Handle_t::~Handle_t()
    {
        if (Is_Valid()) {
            
            Policy()->Release(handle);
        }
    }*/

    inline bool Handle_t::Is_Valid()
    {
        return handle != Policy()->GetInvalidHandle();
    }

    inline Handle_t::operator UInt64()
    {
        return handle;
    }

    // Type_t

    inline Type_e Type_t::Unmangled()
    {
        if (mangled <= BOOL_ARRAY) {
            return mangled;
        } else {
            return (mangled & 1llu) ? OBJECT_ARRAY : OBJECT;
        }
    }

    inline Class_Info_t* Type_t::Class_Info()
    {
        return reinterpret_cast<Class_Info_t*>(mangled);
    }

    inline String_t Type_t::To_String()
    {
        switch (Unmangled()) {
            case NONE: return "None";
            case OBJECT: return Class_Info()->name;
            case STRING: return "String";
            case INT: return "Int";
            case FLOAT: return "Float";
            case BOOL: return "Bool";
            case NONE_ARRAY: return "None[]";
            case OBJECT_ARRAY: return "Object[]";
            case STRING_ARRAY: return "String[]";
            case INT_ARRAY: return "Int[]";
            case FLOAT_ARRAY: return "Float[]";
            case BOOL_ARRAY: return "Bool[]";
            default: return "Invalid";
        };
    }

    inline bool Type_t::Is_None()
    {
        return Unmangled() == NONE;
    }

    inline bool Type_t::Is_Object()
    {
        return Unmangled() == OBJECT;
    }

    inline bool Type_t::Is_String()
    {
        return Unmangled() == STRING;
    }

    inline bool Type_t::Is_Int()
    {
        return Unmangled() == INT;
    }

    inline bool Type_t::Is_Float()
    {
        return Unmangled() == FLOAT;
    }

    inline bool Type_t::Is_Bool()
    {
        return Unmangled() == BOOL;
    }

    inline bool Type_t::Is_None_Array()
    {
        return Unmangled() == NONE_ARRAY;
    }

    inline bool Type_t::Is_Object_Array()
    {
        return Unmangled() == OBJECT_ARRAY;
    }

    inline bool Type_t::Is_String_Array()
    {
        return Unmangled() == STRING_ARRAY;
    }

    inline bool Type_t::Is_Int_Array()
    {
        return Unmangled() == INT_ARRAY;
    }

    inline bool Type_t::Is_Float_Array()
    {
        return Unmangled() == FLOAT_ARRAY;
    }

    inline bool Type_t::Is_Bool_Array()
    {
        return Unmangled() == BOOL_ARRAY;
    }

    // Array_t

    inline Variable_t* Array_t::Variables()
    {
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    // Variable_t

    inline Registry_t* Variable_t::Registry()
    {
        static Registry_t* registry = (*g_skyrimVM)->GetClassRegistry();
        return registry;
    }

    inline Policy_t* Variable_t::Policy()
    {
        static Policy_t* policy = Registry()->GetHandlePolicy();
        return policy;
    }

    template <typename Type>
    inline Variable_t* Variable_t::Fetch(Type* instance,
                                         String_t class_name,
                                         String_t variable_name)
    {
        Object_t* object = Object_t::Fetch(instance, class_name);
        if (object) {
            return object->Variable(variable_name);
        } else {
            return nullptr;
        }
    }

    inline Actor_t* Variable_t::Actor()
    {
        if (type.Unmangled() == Type_t::OBJECT) {
            if (data.obj) {
                return static_cast<Actor_t*>(Policy()->Resolve(kFormType_Character, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Alias_t* Variable_t::Alias()
    {
        if (type.Unmangled() == Type_t::OBJECT) {
            if (data.obj) {
                return static_cast<Alias_t*>(Policy()->Resolve(kFormType_Alias, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Bool_t Variable_t::Bool()
    {
        if (type.Unmangled() == Type_t::BOOL) {
            return data.b;
        } else {
            return false;
        }
    }

    inline Float_t Variable_t::Float()
    {
        if (type.Unmangled() == Type_t::FLOAT) {
            return data.f;
        } else {
            return 0.0;
        }
    }

    inline Int_t Variable_t::Int()
    {
        if (type.Unmangled() == Type_t::INT) {
            return data.i;
        } else {
            return 0;
        }
    }

    inline String_t Variable_t::String()
    {
        if (type.Is_String()) {
            return data.str;
        } else {
            return "";
        }
    }

    inline Reference_t* Variable_t::Reference()
    {
        if (type.Unmangled() == Type_t::OBJECT) {
            if (data.obj) {
                return static_cast<Reference_t*>(Policy()->Resolve(kFormType_Reference, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    // Class_Info_t

    inline Class_Info_t* Class_Info_t::Fetch(String_t class_name)
    {
        Virtual_Machine_t* const virtual_machine = Virtual_Machine_t::Self();
        if (virtual_machine) {
            Class_Info_t* info_out = nullptr;
            virtual_machine->Load_Class_Info(&class_name, &info_out);
            //virtual_machine->Class_Info(&class_name, &info_out);
            return info_out;
        } else {
            return nullptr;
        }
    }

    inline UInt64 Class_Info_t::Count_Setting_Infos()
    {
        UInt64 flags = static_cast<UInt64>(flags_20);
        UInt64 six_bits = static_cast<UInt64>(0x3F);
        return (flags >> 2) & six_bits;
    }

    inline UInt64 Class_Info_t::Count_Variable_Infos()
    {
        UInt64 flags = static_cast<UInt64>(flags_20);
        UInt64 ten_bits = static_cast<UInt64>(0x3FF);
        return (flags >> 8) & ten_bits;
    }

    inline UInt64 Class_Info_t::Count_Default_Infos()
    {
        UInt64 flags = static_cast<UInt64>(flags_24);
        UInt64 ten_bits = static_cast<UInt64>(0x3FF);
        return flags & ten_bits;
    }

    inline UInt64 Class_Info_t::Count_Property_Infos()
    {
        UInt64 flags = static_cast<UInt64>(flags_24);
        UInt64 ten_bits = static_cast<UInt64>(0x3FF);
        return (flags >> 10) & ten_bits;
    }

    inline Class_Info_t::Setting_Info_t* Class_Info_t::Setting_Infos()
    {
        return reinterpret_cast<Setting_Info_t*>(data);
    }

    inline Class_Info_t::Variable_Info_t* Class_Info_t::Variable_Infos()
    {
        return reinterpret_cast<Variable_Info_t*>(Setting_Infos() + Count_Setting_Infos());
    }

    inline Class_Info_t::Default_Info_t* Class_Info_t::Default_Infos()
    {
        return reinterpret_cast<Default_Info_t*>(Variable_Infos() + Count_Variable_Infos());
    }

    inline Class_Info_t::Property_Info_t* Class_Info_t::Property_Infos()
    {
        return reinterpret_cast<Property_Info_t*>(Default_Infos() + Count_Default_Infos());
    }

    inline SInt64 Class_Info_t::Variable_Index(String_t variable_name)
    {
        Variable_Info_t* variables = Variable_Infos();
        for (s64 idx = 0, size = Count_Variable_Infos(); idx < size; idx += 1) {
            if (variables[idx].name == variable_name) {
                return idx;
            }
        }

        return -1;
    }

    inline SInt64 Class_Info_t::Property_Index(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (s64 idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (properties[idx].name == property_name) {
                return properties[idx].auto_var_idx;
            }
        }

        return -1;
    }

    inline Class_Info_t::Property_Info_t* Class_Info_t::Property_Info(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (s64 idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (properties[idx].name == property_name) {
                return &properties[idx];
            }
        }

        return nullptr;
    }

    inline void Class_Info_t::Hold()
    {
        reinterpret_cast<VMClassInfo*>(this)->AddRef();
    }

    inline void Class_Info_t::Free()
    {
        reinterpret_cast<VMClassInfo*>(this)->Release();
    }

    inline void Class_Info_t::Log()
    {
        _MESSAGE("name: %s\n"
                 "parent_name: %s\n",
                 name,
                 parent ? parent->name : "");
    }

    inline void Class_Info_t::Log_Variable_Infos()
    {
        _MESSAGE("Logging Variables: %s", name);
        Variable_Info_t* variables = Variable_Infos();
        for (u64 idx = 0, size = Count_Variable_Infos(); idx < size; idx += 1) {
            Variable_Info_t& variable = variables[idx];
            _MESSAGE("name: %s", variable.name);
            _MESSAGE("    type: %u", variable.type);
            _MESSAGE("        name: %s\n", variable.type.To_String());
        }
    }

    inline void Class_Info_t::Log_Default_Infos()
    {
        _MESSAGE("Logging Defaults: %s", name);
        Default_Info_t* defaults = Default_Infos();
        for (u64 idx = 0, size = Count_Default_Infos(); idx < size; idx += 1) {
            Default_Info_t& def = defaults[idx];
            Type_t& type = reinterpret_cast<Type_t&>(def.variable.type);
            _MESSAGE("Default:");
            _MESSAGE("    variable_idx: %u", def.variable_idx);
            _MESSAGE("    pad_04: %p", def.pad_04);
            _MESSAGE("    variable_type: %s", type.To_String());
            if (type.Is_String()) {
                _MESSAGE("        String: %s\n", def.variable.data.str);
            } else {
                _MESSAGE("        (unhandled variable type.)\n");
            }
        }
    }

    inline void Class_Info_t::Log_Property_Infos()
    {
        _MESSAGE("Logging Properties: %s", name);
        Property_Info_t* properties = Property_Infos();
        for (u64 idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            Property_Info_t& property = properties[idx];
            _MESSAGE("name: %s", property.name);
            _MESSAGE("    parent_name: %s", property.parent_name);
            _MESSAGE("    property_name: %s", property.property_name);
            _MESSAGE("    type: %s", property.type.To_String());
            _MESSAGE("    flags_20: %u", property.flags_20);
            _MESSAGE("    pad_24: %p", property.unk_24);
            _MESSAGE("    getter: %p", property.getter);
            _MESSAGE("    setter: %p", property.setter);
            _MESSAGE("    auto_var_idx: %p", property.auto_var_idx);
            _MESSAGE("    flags_3C: %u", property.flags_3C);
            _MESSAGE("    unk_40: %p\n", property.unk_40);
        }
    }

    // Object_t

    template <typename Type>
    inline Object_t* Object_t::Fetch(Type* instance,
                                     String_t class_name)
    {
        Handle_t handle(instance);
        if (handle.Is_Valid()) {
            VMIdentifier* identifier = nullptr;
            handle.Registry()->Unk_1C(handle, class_name, &identifier);
            return reinterpret_cast<Object_t*>(identifier);
        } else {
            return nullptr;
        }
    }

    inline Variable_t* Object_t::Variables()
    {
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    inline Handle_t Object_t::Handle()
    {
        return reinterpret_cast<VMIdentifier*>(this)->GetHandle();
    }

    inline Variable_t* Object_t::Property(String_t property_name)
    {
        SInt64 idx = info->Property_Index(property_name);
        if (idx > -1) {
            return &Variables()[idx];
        } else {
            return nullptr;
        }
    }

    inline Variable_t* Object_t::Variable(String_t variable_name)
    {
        SInt64 idx = info->Variable_Index(variable_name);
        if (idx > -1) {
            return &Variables()[idx];
        } else {
            return nullptr;
        }
    }

    inline void Object_t::Log_Variables()
    {
        _MESSAGE("Logging Object Variables: %s", info->name);
        Class_Info_t::Variable_Info_t* variables_infos = info->Variable_Infos();
        for (u64 idx = 0, size = info->Count_Variable_Infos(); idx < size; idx += 1) {
            Variable_t& variable = Variables()[idx];
            Class_Info_t::Variable_Info_t& info = variables_infos[idx];
            _MESSAGE("Variable: %s", info.name);
            if (info.type.Is_Int()) {
                _MESSAGE("    type: %s, val: %i\n", info.type.To_String(), variable.data.i);
            } else if (info.type.Is_String()) {
                _MESSAGE("    type: %s, val: %s\n", info.type.To_String(), variable.data.str);
            } else {
                _MESSAGE("    type: %s, val: %p\n", info.type.To_String(), variable.data.ptr);
            }
        }
    }

}}
