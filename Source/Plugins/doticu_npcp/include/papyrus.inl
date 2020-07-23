/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"
#include "string2.h"
#include "utils.h"

namespace doticu_npcp { namespace Papyrus {

    // Virtual_Machine_t

    inline Virtual_Machine_t* Virtual_Machine_t::Self()
    {
        static Virtual_Machine_t* const virtual_machine =
            reinterpret_cast<Virtual_Machine_t*>((*g_skyrimVM)->GetClassRegistry());
        NPCP_ASSERT(virtual_machine);
        return virtual_machine;
    }

    // Handle_t

    inline Registry_t* Handle_t::Registry()
    {
        static Registry_t* registry = (*g_skyrimVM)->GetClassRegistry();
        NPCP_ASSERT(registry);
        return registry;
    }

    inline Policy_t* Handle_t::Policy()
    {
        static Policy_t* policy = Registry()->GetHandlePolicy();
        NPCP_ASSERT(policy);
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

    inline Type_t::Type_t() :
        mangled(NONE)
    {
    }

    inline Type_t::Type_t(Type_e type) :
        mangled(type)
    {
    }

    inline Type_t::Type_t(Class_Info_t* class_info) :
        mangled(reinterpret_cast<UInt64>(class_info))
    {
    }

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

    inline Array_t* Array_t::Create(Type_t* type, UInt32 count)
    {
        if (type) {
            Array_t* arr;
            if (Virtual_Machine_t::Self()->Create_Array(type, count, &arr)) {
                return arr;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Variable_t* Array_t::Variables()
    {
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    inline Variable_t* Array_t::Point(size_t idx)
    {
        if (idx < count) {
            return Variables() + idx;
        } else {
            return nullptr;
        }
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

    inline Variable_t::Variable_t() :
        type(Type_t()), data(Variable_u())
    {
    }

    inline Variable_t::Variable_u::Variable_u() :
        ptr(nullptr)
    {
    }

    inline void Variable_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void (*)(Variable_t*)>
            (RelocationManager::s_baseAddr + Offsets::Variable::DESTROY);
        destroy(this);
        data.ptr = nullptr;
    }

    inline void Variable_t::Copy(Variable_t* other)
    {
        static auto copy = reinterpret_cast
            <void (*)(Variable_t*, Variable_t*)>
            (RelocationManager::s_baseAddr + Offsets::Variable::COPY);
        Destroy();
        copy(this, other);
    }

    inline Bool_t Variable_t::Bool()
    {
        if (type.Is_Bool()) {
            return data.b;
        } else {
            return false;
        }
    }

    inline Int_t Variable_t::Int()
    {
        if (type.Is_Int()) {
            return data.i;
        } else {
            return 0;
        }
    }

    inline Float_t Variable_t::Float()
    {
        if (type.Is_Float()) {
            return data.f;
        } else {
            return 0.0;
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

    inline Actor_t* Variable_t::Actor()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Actor_t*>(Policy()->Resolve(kFormType_Character, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Alias_Base_t* Variable_t::Alias()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Alias_Base_t*>(Policy()->Resolve(kFormType_Alias, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Faction_t* Variable_t::Faction()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Faction_t*>(Policy()->Resolve(kFormType_Faction, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Misc_t* Variable_t::Misc()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Misc_t*>(Policy()->Resolve(kFormType_Misc, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline Reference_t* Variable_t::Reference()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Reference_t*>(Policy()->Resolve(kFormType_Reference, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline void Variable_t::None()
    {
        Destroy();
        type = Type_t::NONE;
        data.ptr = nullptr;
    }

    inline void Variable_t::Bool(Bool_t value)
    {
        Destroy();
        type = Type_t::BOOL;
        data.b = value;
    }

    inline void Variable_t::Int(Int_t value)
    {
        Destroy();
        type = Type_t::INT;
        data.i = value;
    }

    inline void Variable_t::Float(Float_t value)
    {
        Destroy();
        type = Type_t::FLOAT;
        data.f = value;
    }

    inline void Variable_t::String(String_t value)
    {
        static auto set = reinterpret_cast
            <String_t* (*)(String_t*, const char*)>
            (RelocationManager::s_baseAddr + Offsets::String::SET);
        Destroy();
        type = Type_t::STRING;
        set(&data.str, value ? value : "");
    }

    inline void Variable_t::Object(Object_t* value)
    {
        if (value) {
            Destroy();
            Variable_t temp;
            temp.type = value->info;
            temp.data.obj = value;
            Copy(&temp); // this may do stuff we don't
        } else {
            None();
        }
    }

    inline void Variable_t::Array(Array_t* value)
    {
        if (value) {
            Destroy();
            Variable_t temp;
            temp.type = value->type;
            temp.data.arr = value;
            Copy(&temp); // this may do stuff we don't
        } else {
            None();
        }
    }

    template <typename Type>
    inline void Variable_t::Pack(Type* value)
    {
        /////////////////////////////////////////////////////
        PackHandle(reinterpret_cast<VMValue*>(this), value, Type::kTypeID, Registry());
        return;
        /////////////////////////////////////////////////////

        NPCP_ASSERT(value);

        Class_Info_t* class_info = Class_Info_t::Fetch(Type::kTypeID);
        NPCP_ASSERT(class_info);

        Object_t* object = Object_t::Fetch(value, class_info->name);
        NPCP_ASSERT(object);

        Object(object);

        class_info->Free();
    }

    template <>
    inline void Variable_t::Pack(Bool_t* value)
    {
        NPCP_ASSERT(value);
        Bool(*value);
    }

    template <>
    inline void Variable_t::Pack(Int_t* value)
    {
        NPCP_ASSERT(value);
        Int(*value);
    }

    template <>
    inline void Variable_t::Pack(Float_t* value)
    {
        NPCP_ASSERT(value);
        Float(*value);
    }

    template <>
    inline void Variable_t::Pack(String_t* value)
    {
        NPCP_ASSERT(value);
        String(*value);
    }

    template <>
    inline void Variable_t::Pack(Object_t* value)
    {
        NPCP_ASSERT(value);
        Object(value);
    }

    template <>
    inline void Variable_t::Pack(Array_t* value)
    {
        NPCP_ASSERT(value);
        Array(value);
    }

    template <typename Type>
    inline void Variable_t::Pack(Vector_t<Type>& values)
    {
        Class_Info_t* class_info = Class_Info_t::Fetch(std::remove_pointer<Type>::type::kTypeID);
        NPCP_ASSERT(class_info);

        Type_t type(class_info);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(values[idx]);
        }

        Array(arr);

        class_info->Free();
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Bool_t>& values)
    {
        Type_t type(Type_t::BOOL);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            // can't point to std::vector<bool>[i]. f'ing stupid. if I wanted a bitfield I would use a different type!!!
            Bool_t value = values[idx];
            arr->Point(idx)->Pack(&value);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Int_t>& values)
    {
        Type_t type(Type_t::INT);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(&values[idx]);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Float_t>& values)
    {
        Type_t type(Type_t::FLOAT);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(&values[idx]);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<String_t>& values)
    {
        Type_t type(Type_t::STRING);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(&values[idx]);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Object_t*>& values)
    {
        NPCP_ASSERT(values.size() > 0);
        Type_t type(values[0]->info);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(values[idx]);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Array_t*>& values)
    {
        // not tested, may not work with Virtual_Machine_t::Create_Array
        NPCP_ASSERT(values.size() > 0);
        Type_t type(values[0]->type);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(values[idx]);
        }

        Array(arr);
    }

    // Class_Info_t

    inline Class_Info_t* Class_Info_t::Fetch(String_t class_name)
    {
        Virtual_Machine_t* const virtual_machine = Virtual_Machine_t::Self();
        if (virtual_machine) {
            Class_Info_t* info_out = nullptr;
            virtual_machine->Load_Class_Info(&class_name, &info_out);
            return info_out;
        } else {
            return nullptr;
        }
    }

    inline Class_Info_t* Class_Info_t::Fetch(Type_ID_t type_id)
    {
        Virtual_Machine_t* const virtual_machine = Virtual_Machine_t::Self();
        if (virtual_machine) {
            Class_Info_t* info_out = nullptr;
            virtual_machine->Load_Class_Info2(type_id, &info_out);
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
            if (String2::Is_Same_Caseless(variables[idx].name, variable_name)) {
                return idx;
            }
        }

        return -1;
    }

    inline SInt64 Class_Info_t::Property_Index(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (s64 idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (String2::Is_Same_Caseless(properties[idx].name, property_name)) {
                return properties[idx].auto_var_idx;
            }
        }

        return -1;
    }

    inline Class_Info_t::Property_Info_t* Class_Info_t::Property_Info(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (s64 idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (String2::Is_Same_Caseless(properties[idx].name, property_name)) {
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
            Object_t* object = nullptr;
            if (Virtual_Machine_t::Self()->Find_Bound_Object(handle, class_name, &object)) {
                return object;
            } else {
                return nullptr;
            }
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
