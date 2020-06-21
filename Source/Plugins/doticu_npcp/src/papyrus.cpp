/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus {

    Object::Info::Type_Info::Type_t Object::Info::Type_Info::Type()
    {
        if (raw <= Type_t::TYPE_BOOL_ARRAY) {
            return raw;
        } else {
            return static_cast<UInt64>(raw) & 1llu ? Type_t::TYPE_OBJECT_ARRAY : Type_t::TYPE_OBJECT;
        }
    }

    Object::Info* Object::Info::Type_Info::Object_Info()
    {
        return reinterpret_cast<Object::Info*>(raw);
    }

    String_t Object::Info::Type_Info::To_String()
    {
        switch (Type()) {
            case Type_t::TYPE_NONE: return "None";
            case Type_t::TYPE_OBJECT: return Object_Info()->name;
            case Type_t::TYPE_STRING: return "String";
            case Type_t::TYPE_INT: return "Int";
            case Type_t::TYPE_FLOAT: return "Float";
            case Type_t::TYPE_BOOL: return "Bool";
            case Type_t::TYPE_NONE_ARRAY: return "None[]";
            case Type_t::TYPE_OBJECT_ARRAY: return "Object[]";
            case Type_t::TYPE_STRING_ARRAY: return "String[]";
            case Type_t::TYPE_INT_ARRAY: return "Int[]";
            case Type_t::TYPE_FLOAT_ARRAY: return "Float[]";
            case Type_t::TYPE_BOOL_ARRAY: return "Bool[]";
            default: return "Invalid";
        };
    }

    bool Object::Info::Type_Info::Is_None()
    {
        return Type() == Type_t::TYPE_NONE;
    }

    bool Object::Info::Type_Info::Is_Object()
    {
        return Type() == Type_t::TYPE_OBJECT;
    }

    bool Object::Info::Type_Info::Is_String()
    {
        return Type() == Type_t::TYPE_STRING;
    }

    bool Object::Info::Type_Info::Is_Int()
    {
        return Type() == Type_t::TYPE_INT;
    }

    bool Object::Info::Type_Info::Is_Float()
    {
        return Type() == Type_t::TYPE_FLOAT;
    }

    bool Object::Info::Type_Info::Is_Bool()
    {
        return Type() == Type_t::TYPE_BOOL;
    }

    bool Object::Info::Type_Info::Is_None_Array()
    {
        return Type() == Type_t::TYPE_NONE_ARRAY;
    }

    bool Object::Info::Type_Info::Is_Object_Array()
    {
        return Type() == Type_t::TYPE_OBJECT_ARRAY;
    }

    bool Object::Info::Type_Info::Is_String_Array()
    {
        return Type() == Type_t::TYPE_STRING_ARRAY;
    }

    bool Object::Info::Type_Info::Is_Int_Array()
    {
        return Type() == Type_t::TYPE_INT_ARRAY;
    }

    bool Object::Info::Type_Info::Is_Float_Array()
    {
        return Type() == Type_t::TYPE_FLOAT_ARRAY;
    }

    bool Object::Info::Type_Info::Is_Bool_Array()
    {
        return Type() == Type_t::TYPE_BOOL_ARRAY;
    }

    Object::Object(Form_t* form, const char* class_name)
    {
        m_handle = Handle(form);
        _Object(class_name);
    }

    Object::Object(Alias_t* alias, const char* class_name)
    {
        m_handle = Handle(alias);
        _Object(class_name);
    }

    void Object::_Object(const char* class_name)
    {
        if (m_handle.Is_Valid()) {
            m_handle.Registry()->Unk_1C(m_handle, class_name, &m_obj);
            if (m_obj) {
                m_info = reinterpret_cast<Info*>(m_obj->m_type);
                m_vars = reinterpret_cast<Variable_t*>(reinterpret_cast<u8*>(m_obj) + 0x30);
            }
        }
    }

    bool Object::Is_Valid()
    {
        return m_obj && m_info && m_vars;
    }

    bool Object::Read_Property(String_t property_name, Variable_t& in_variable)
    {
        in_variable.SetNone();
        if (Is_Valid()) {
            _MESSAGE("reading variable.");
            if (m_handle.Registry()->Unk_21(&m_obj, property_name, in_variable)) {
                _MESSAGE("read variable.");
                return true;
            } else {
                _MESSAGE("failed to read variable.");
                return false;
            }
        } else {
            _MESSAGE("object isn't valid.");
            return false;
        }

        in_variable.SetNone();
        return Is_Valid() && m_handle.Registry()->Unk_21(&m_obj, property_name, in_variable);
    }

    bool Object::Write_Property(String_t property_name, Variable_t& out_variable)
    {
        if (Is_Valid()) {
            _MESSAGE("writing variable.");
            if (m_handle.Registry()->Unk_20(&m_obj, property_name, out_variable)) {
                _MESSAGE("wrote variable.");
                return true;
            } else {
                _MESSAGE("failed to write variable.");
                return false;
            }
        } else {
            _MESSAGE("object isn't valid.");
            return false;
        }

        return Is_Valid() && m_handle.Registry()->Unk_20(&m_obj, property_name, out_variable);
    }

    Variable_t* Object::Property(String_t property_name)
    {
        SInt64 idx = m_info->Property_Index(property_name);
        if (idx > -1) {
            return &m_vars[idx];
        } else {
            return nullptr;
        }
    }

    Variable_t* Object::Variable(String_t variable_name)
    {
        SInt64 idx = m_info->Variable_Index(variable_name);
        if (idx > -1) {
            return &m_vars[idx];
        } else {
            return nullptr;
        }
    }

    void Object::Log_Variables()
    {
        _MESSAGE("Logging Object Variables: %s", m_info->name);
        Info::Variable_t* variables_infos = m_info->Variables();
        for (u64 idx = 0, size = m_info->Count_Variables(); idx < size; idx += 1) {
            Papyrus::Variable_t& variable = m_vars[idx];
            Info::Variable_t& info = variables_infos[idx];
            _MESSAGE("Variable: %s", info.name);
            if (info.type.Is_Int()) {
                _MESSAGE("    type: %s, val: %i\n", info.type.To_String(), variable.data.i);
            } else if (info.type.Is_String()) {
                _MESSAGE("    type: %s, val: %s\n", info.type.To_String(), variable.data.str);
            } else {
                _MESSAGE("    type: %s, val: %p\n", info.type.To_String(), variable.data.p);
            }
        }
    }

    Object::operator Entity_t* ()
    {
        return m_obj;
    }

    UInt64 Object::Info::Count_Settings()
    {
        UInt64 flags = static_cast<UInt64>(flags_20);
        UInt64 six_bits = static_cast<UInt64>(0x3F);
        return (flags >> 2) & six_bits;
    }

    UInt64 Object::Info::Count_Variables()
    {
        UInt64 flags = static_cast<UInt64>(flags_20);
        UInt64 ten_bits = static_cast<UInt64>(0x3FF);
        return (flags >> 8) & ten_bits;
    }

    UInt64 Object::Info::Count_Defaults()
    {
        UInt64 flags = static_cast<UInt64>(flags_24);
        UInt64 ten_bits = static_cast<UInt64>(0x3FF);
        return flags & ten_bits;
    }

    UInt64 Object::Info::Count_Properties()
    {
        UInt64 flags = static_cast<UInt64>(flags_24);
        UInt64 ten_bits = static_cast<UInt64>(0x3FF);
        return (flags >> 10) & ten_bits;
    }

    Object::Info::Setting_t* Object::Info::Settings()
    {
        return reinterpret_cast<Setting_t*>(data);
    }

    Object::Info::Variable_t* Object::Info::Variables()
    {
        return reinterpret_cast<Variable_t*>(Settings() + Count_Settings());
    }

    Object::Info::Default_t* Object::Info::Defaults()
    {
        return reinterpret_cast<Default_t*>(Variables() + Count_Variables());
    }

    Object::Info::Property_t* Object::Info::Properties()
    {
        return reinterpret_cast<Property_t*>(Defaults() + Count_Defaults());
    }

    SInt64 Object::Info::Variable_Index(String_t variable_name)
    {
        Variable_t* variables = Variables();
        for (s64 idx = 0, size = Count_Variables(); idx < size; idx += 1) {
            if (variables[idx].name == variable_name) {
                return idx;
            }
        }

        return -1;
    }

    SInt64 Object::Info::Property_Index(String_t property_name)
    {
        Property_t* properties = Properties();
        for (s64 idx = 0, size = Count_Properties(); idx < size; idx += 1) {
            if (properties[idx].name == property_name) {
                return properties[idx].auto_var_idx;
            }
        }

        return -1;
    }

    Object::Info::Property_t* Object::Info::Property(String_t property_name)
    {
        Property_t* properties = Properties();
        for (s64 idx = 0, size = Count_Properties(); idx < size; idx += 1) {
            if (properties[idx].name == property_name) {
                return &properties[idx];
            }
        }

        return nullptr;
    }

    void Object::Info::Log()
    {
        _MESSAGE("name: %s\n"
                 "parent_name: %s\n",
                 name,
                 parent ? parent->name : "");
    }

    void Object::Info::Log_Variables()
    {
        _MESSAGE("Logging Variables:");
        Variable_t* variables = Variables();
        for (u64 idx = 0, size = Count_Variables(); idx < size; idx += 1) {
            Variable_t& variable = variables[idx];
            _MESSAGE("name: %s", variable.name);
            _MESSAGE("    type: %u", variable.type);
            _MESSAGE("        name: %s\n", variable.type.To_String());
        }
    }

    void Object::Info::Log_Defaults()
    {
        _MESSAGE("Logging Defaults:");
        Default_t* defaults = Defaults();
        for (u64 idx = 0, size = Count_Defaults(); idx < size; idx += 1) {
            Default_t& def = defaults[idx];
            Type_Info& type = reinterpret_cast<Type_Info&>(def.variable.type);
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

    void Object::Info::Log_Properties()
    {
        _MESSAGE("Logging Properties:");
        Property_t* properties = Properties();
        for (u64 idx = 0, size = Count_Properties(); idx < size; idx += 1) {
            Property_t& property = properties[idx];
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

}}

namespace doticu_npcp { namespace Papyrus { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
