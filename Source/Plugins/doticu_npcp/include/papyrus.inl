/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"
#include "string2.h"
#include "utils.h"

namespace doticu_npcp { namespace Papyrus {

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

    inline Handle_t::Handle_t(void* instance, Type_ID_t type_id)
    {
        if (instance) {
            handle = Policy()->Create(type_id, instance);
        } else {
            handle = Policy()->GetInvalidHandle();
        }
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

    template <>
    inline Handle_t::Handle_t(void* instance)
    {
        NPCP_ASSERT(false);
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

    inline Bool_t Handle_t::Is_Valid()
    {
        return handle != Policy()->GetInvalidHandle();
    }

    inline Bool_t Handle_t::Has_Type_ID(Type_ID_t type_id)
    {
        return reinterpret_cast<Handle_Policy_t*>(Policy())->Has_Type_ID(type_id, handle);
    }

    inline Handle_t::operator UInt64()
    {
        return handle;
    }

    // Object_Bind_Policy_t

    inline void Object_Policy_t::Bind_Object(Object_t*& object, Handle_t handle)
    {
        static auto bind_object = reinterpret_cast
            <void (*)(Object_Policy_t*, Object_t*& object, Handle_t)>
            (RelocationManager::s_baseAddr + Offsets::Object_Policy::BIND_OBJECT);
        bind_object(this, object, handle);
    }

    inline void Object_Policy_t::Unbind_Object(Object_t*& object)
    {
        virtual_binder->Unbind_Object(object);
    }

    // Virtual_Machine_t

    inline Virtual_Machine_t* Virtual_Machine_t::Self()
    {
        static Virtual_Machine_t* const virtual_machine =
            reinterpret_cast<Virtual_Machine_t*>((*g_skyrimVM)->GetClassRegistry());
        NPCP_ASSERT(virtual_machine);
        return virtual_machine;
    }

    template <typename BSObject>
    inline void Virtual_Machine_t::Send_Event(BSObject* object, String_t event_name, IFunctionArguments* arguments)
    {
        NPCP_ASSERT(object && event_name && arguments);
        Self()->Send_Event(Handle_t(object), &event_name, arguments);
    }

    template <typename BSObject>
    inline void Virtual_Machine_t::Send_Event(BSObject* object, String_t event_name)
    {
        NPCP_ASSERT(object && event_name);
        struct : public IFunctionArguments {
            bool Copy(Output* output) { return true; }
        } arguments;
        Self()->Send_Event(Handle_t(object), &event_name, &arguments);
    }

    inline Bool_t Virtual_Machine_t::Call_Method(Handle_t handle,
                                                 String_t class_name,
                                                 String_t function_name,
                                                 Virtual_Arguments_i* arguments,
                                                 Virtual_Callback_i** callback)
    {
        if (!callback) {
            Virtual_Callback_i* default_callback = new Virtual_Callback_t();
            callback = &default_callback;
        }

        if (arguments) {
            return Call_Method2(handle, &class_name, &function_name, arguments, callback);
        } else {
            Virtual_Arguments_t default_arguments;
            return Call_Method2(handle, &class_name, &function_name, &default_arguments, callback);
        }
    }

    inline Int_t Virtual_Machine_t::Count_Objects(Handle_t handle)
    {
        class Counter : public IForEachScriptObjectFunctor {
        public:
            Handle_t handle;
            Int_t count = 0;

            Counter(Handle_t handle) :
                handle(handle), count(0)
            {
            }

            virtual bool Visit(Script_t* object, void*)
            {
                count += 1;
                return true;
            }
        } counter(handle);

        For_Each_Object(handle, &counter);

        return counter.count;
    }

    inline Bool_t Virtual_Machine_t::Has_Object(Handle_t handle)
    {
        return Count_Objects(handle) < 1;
    }

    inline Type_ID_t Virtual_Machine_t::Type_ID(String_t class_name)
    {
        NPCP_ASSERT(class_name);
        Type_ID_t type_id = 0;
        Type_ID(&class_name, &type_id);
        return type_id;
    }

    // Virtual_Arguments_i

    inline Bool_t Virtual_Arguments_i::Arguments_t::Resize(UInt32 count)
    {
        static auto resize = reinterpret_cast
            <Bool_t (*)(Virtual_Arguments_i::Arguments_t*, UInt32)>
            (RelocationManager::s_baseAddr + Offsets::Virtual_Arguments::RESIZE);
        return resize(this, count);
    }

    inline Variable_t* Virtual_Arguments_i::Arguments_t::At(UInt32 idx)
    {
        if (idx < count) {
            return variables + idx;
        } else {
            return nullptr;
        }
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
        if (Is_Object()) {
            return reinterpret_cast<Class_Info_t*>(mangled);
        } else if (Is_Object_Array()) {
            return reinterpret_cast<Class_Info_t*>(mangled - 1);
        } else {
            return nullptr;
        }
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

    inline Bool_t Type_t::Is_None()
    {
        return Unmangled() == NONE;
    }

    inline Bool_t Type_t::Is_Bool()
    {
        return Unmangled() == BOOL;
    }

    inline Bool_t Type_t::Is_Int()
    {
        return Unmangled() == INT;
    }

    inline Bool_t Type_t::Is_Float()
    {
        return Unmangled() == FLOAT;
    }

    inline Bool_t Type_t::Is_String()
    {
        return Unmangled() == STRING;
    }

    inline Bool_t Type_t::Is_Object()
    {
        return Unmangled() == OBJECT;
    }

    inline Bool_t Type_t::Is_Array()
    {
        Type_e unmangled = Unmangled();
        return unmangled >= NONE_ARRAY && unmangled <= BOOL_ARRAY;
    }

    inline Bool_t Type_t::Is_None_Array()
    {
        return Unmangled() == NONE_ARRAY;
    }

    inline Bool_t Type_t::Is_Bool_Array()
    {
        return Unmangled() == BOOL_ARRAY;
    }

    inline Bool_t Type_t::Is_Int_Array()
    {
        return Unmangled() == INT_ARRAY;
    }

    inline Bool_t Type_t::Is_Float_Array()
    {
        return Unmangled() == FLOAT_ARRAY;
    }

    inline Bool_t Type_t::Is_String_Array()
    {
        return Unmangled() == STRING_ARRAY;
    }

    inline Bool_t Type_t::Is_Object_Array()
    {
        return Unmangled() == OBJECT_ARRAY;
    }

    // Array_t

    inline Array_t* Array_t::Create(Type_t* item_type, UInt32 count)
    {
        if (item_type) {
            Array_t* arr;
            if (Virtual_Machine_t::Self()->Create_Array(item_type, count, &arr)) {
                return arr;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    inline void Array_t::Destroy(Array_t* arr)
    {
        static auto destroy = reinterpret_cast
            <void (*)(Array_t*)>
            (RelocationManager::s_baseAddr + Offsets::Array::DESTROY);
        if (arr) {
            destroy(arr);
        }
    }

    inline void Array_t::Increment_Count()
    {
        InterlockedIncrement(&ref_count);
    }

    inline void Array_t::Decrement_Count()
    {
        if (InterlockedDecrement(&ref_count) < 1) {
            Array_t::Destroy(this);
        }
    }

    inline Type_t Array_t::Array_Type()
    {
        if (item_type.mangled < Type_t::NONE_ARRAY) {
            return item_type.mangled + Type_t::NONE_ARRAY;
        } else {
            return item_type.mangled + 1;
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

    inline Bool_t Variable_t::Is_None() { return type.Is_None(); }
    inline Bool_t Variable_t::Is_Bool() { return type.Is_Bool(); }
    inline Bool_t Variable_t::Is_Int() { return type.Is_Int(); }
    inline Bool_t Variable_t::Is_Float() { return type.Is_Float(); }
    inline Bool_t Variable_t::Is_String() { return type.Is_String(); }
    inline Bool_t Variable_t::Is_Object() { return type.Is_Object(); }
    inline Bool_t Variable_t::Is_Array() { return type.Is_Array(); }
    inline Bool_t Variable_t::Is_None_Array() { return type.Is_None_Array(); }
    inline Bool_t Variable_t::Is_Object_Array() { return type.Is_Object_Array(); }
    inline Bool_t Variable_t::Is_String_Array() { return type.Is_String_Array(); }
    inline Bool_t Variable_t::Is_Int_Array() { return type.Is_Int_Array(); }
    inline Bool_t Variable_t::Is_Float_Array() { return type.Is_Float_Array(); }
    inline Bool_t Variable_t::Is_Bool_Array() { return type.Is_Bool_Array(); }

    inline Bool_t Variable_t::Has_String()
    {
        return Is_String() && data.str && data.str.data && data.str.data[0] != 0;
    }

    inline Bool_t Variable_t::Has_Object()
    {
        return Is_Object() && data.obj != nullptr;
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

    inline Object_t* Variable_t::Object()
    {
        if (type.Is_Object()) {
            return data.obj;
        } else {
            return nullptr;
        }
    }

    inline Array_t* Variable_t::Array()
    {
        if (type.Is_Array()) {
            return data.arr;
        } else {
            return nullptr;
        }
    }

    inline Array_t* Variable_t::Object_Array()
    {
        if (type.Is_Object_Array()) {
            return data.arr;
        } else {
            return nullptr;
        }
    }

    inline Form_t* Variable_t::Form()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Form_t*>(Policy()->Resolve(kFormType_None, data.obj->Handle()));
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
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

    inline Outfit_t* Variable_t::Outfit()
    {
        if (type.Is_Object()) {
            if (data.obj) {
                return static_cast<Outfit_t*>(Policy()->Resolve(kFormType_Outfit, data.obj->Handle()));
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
            Copy(&temp); // this prob. does stuff we don't
        } else {
            None();
        }
    }

    inline void Variable_t::Array(Array_t* value)
    {
        if (value) {
            Destroy();
            type = value->Array_Type();
            data.arr = value;
            value->ref_count += 1; // value->Increment_Count();
        } else {
            None();
        }
    }

    template <typename Type>
    inline void Variable_t::Pack(Type* value, Class_Info_t* class_info)
    {
        NPCP_ASSERT(class_info);

        if (value) {
            Object_t* object = nullptr;
            Virtual_Machine_t::Self()->Find_Bound_Object(value, class_info->name, &object);
            if (!object) {
                Virtual_Machine_t* vm = Virtual_Machine_t::Self();

                vm->Create_Object2(&class_info->name, &object);
                NPCP_ASSERT(object);

                class_info->Hold();
                vm->Object_Policy()->Bind_Object(object, vm->Type_ID(class_info->name));
                class_info->Free();
            }
            object->Decrement_Lock();

            Object(object);
        } else {
            Destroy();
            Variable_t temp;
            temp.type = class_info;
            temp.data.obj = nullptr;
            Copy(&temp); // this prob. does stuff we don't
        }

        class_info->Free();
    }

    template <typename Type>
    inline void Variable_t::Pack(Type* value)
    {
        if (value) {
            PackHandle(reinterpret_cast<VMValue*>(this), value, Type::kTypeID, Registry());
        } else {
            None();
        }
    }

    template <>
    inline void Variable_t::Pack(Bool_t* value)
    {
        if (value) {
            Bool(*value);
        } else {
            Bool(0);
        }
    }

    template <>
    inline void Variable_t::Pack(Int_t* value)
    {
        if (value) {
            Int(*value);
        } else {
            Int(0);
        }
    }

    template <>
    inline void Variable_t::Pack(Float_t* value)
    {
        if (value) {
            Float(*value);
        } else {
            Float(0.0f);
        }
    }

    template <>
    inline void Variable_t::Pack(String_t* value)
    {
        if (value) {
            String(*value);
        } else {
            String("");
        }
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
        class_info->Free();

        Type_t type(class_info);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);
        arr->ref_count -= 1;

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(values[idx]);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Bool_t>& values)
    {
        Type_t type(Type_t::BOOL);
        Array_t* arr = Array_t::Create(&type, values.size());
        NPCP_ASSERT(arr);
        arr->ref_count -= 1;

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
        arr->ref_count -= 1;

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
        arr->ref_count -= 1;

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
        arr->ref_count -= 1;

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
        arr->ref_count -= 1;

        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            arr->Point(idx)->Pack(values[idx]);
        }

        Array(arr);
    }

    template <>
    inline void Variable_t::Pack(Vector_t<Array_t*>& values)
    {
        NPCP_ASSERT(false);
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
    inline Object_t* Object_t::Fetch(Type* instance, String_t class_name)
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

    template <typename Type>
    inline Object_t* Object_t::Create(Type* instance, String_t class_name)
    {
        Handle_t handle(instance);
        if (handle.Is_Valid()) {
            Virtual_Machine_t* virtual_machine = Virtual_Machine_t::Self();

            Class_Info_t* class_info = Class_Info_t::Fetch(class_name);
            class_info->Free();

            Object_t* object = nullptr;
            virtual_machine->Create_Object2(&class_info->name, &object);
            if (object) {
                virtual_machine->Object_Policy()->virtual_binder->Bind_Object(object, handle, false);
                if (object) {
                    NPCP_ASSERT(object->info == class_info);
                    return object;
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

    inline Variable_t* Object_t::Variables()
    {
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    inline void Object_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void (*)(Object_t*)>
            (RelocationManager::s_baseAddr + Offsets::Object::DESTROY);
        destroy(this);
    }

    inline void Object_t::Increment_Lock()
    {
        static auto increment_lock = reinterpret_cast
            <void (*)(Object_t*)>
            (RelocationManager::s_baseAddr + Offsets::Object::INCREMENT_LOCK);
        return increment_lock(this);
    }

    inline UInt32 Object_t::Decrement_Lock()
    {
        static auto decrement_lock = reinterpret_cast
            <UInt32(*)(Object_t*)>
            (RelocationManager::s_baseAddr + Offsets::Object::DECREMENT_LOCK);
        return decrement_lock(this);
    }

    inline Handle_t Object_t::Handle()
    {
        return reinterpret_cast<VMIdentifier*>(this)->GetHandle();
    }

    inline Variable_t* Object_t::Property(String_t property_name)
    {
        Class_Info_t* info = this->info;
        SInt64 idx = -1;
        SInt64 offset = 0;
        while (info) {
            if (idx < 0) {
                idx = info->Property_Index(property_name);
            } else {
                offset += info->Count_Variable_Infos();
            }
            info = info->parent != info ? info->parent : nullptr;
        }

        if (idx > -1) {
            return Variables() + offset + idx;
        } else {
            return nullptr;
        }
    }

    inline Variable_t* Object_t::Variable(String_t variable_name)
    {
        Class_Info_t* info = this->info;
        SInt64 idx = -1;
        SInt64 offset = 0;
        while (info) {
            if (idx < 0) {
                idx = info->Variable_Index(variable_name);
            } else {
                offset += info->Count_Variable_Infos();
            }
            info = info->parent != info ? info->parent : nullptr;
        }

        if (idx > -1) {
            return Variables() + offset + idx;
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
