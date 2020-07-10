/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Papyrus {

    // a lot of credit for deciphering these classes goes to Ryan-rsm-McKenzie of CommonLibSSE as well as the SKSE team
    class Class_Info_t;
    class Virtual_Machine_t { // Registry_t
    public:
        static Virtual_Machine_t* Self();

        virtual ~Virtual_Machine_t(); // 00
        virtual void _01(void); // 01
        virtual void _02(void); // 02
        virtual void _03(void); // 03
        virtual void _04(void); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual void Load_Class_Info(String_t* class_name, Class_Info_t** info_out); // 09, call Class_Info_t Free() after use
        virtual void _0A(void); // 0A
        virtual void Class_Info(String_t* class_name, Class_Info_t** info_out); // 0B, call Class_Info_t Free() after use
    };

    class Handle_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        UInt64 handle = 0;

        template <typename Type>
        Handle_t(Type* instance);
        Handle_t(Form_t* form);
        Handle_t(UInt64 handle);
        Handle_t();

        bool Is_Valid();

        operator UInt64();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

    class Class_Info_t;
    class Type_t {
    public:
        enum : Type_e {
            NONE = 0,
            OBJECT = 1,
            STRING = 2,
            INT = 3,
            FLOAT = 4,
            BOOL = 5,

            NONE_ARRAY = 10,
            OBJECT_ARRAY = 11,
            STRING_ARRAY = 12,
            INT_ARRAY = 13,
            FLOAT_ARRAY = 14,
            BOOL_ARRAY = 15
        };

        UInt64 mangled;

        Type_e Unmangled();
        Class_Info_t* Class_Info();
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
    STATIC_ASSERT(sizeof(Type_t) == 0x8);

    class Variable_t;
    class Array_t {
    public:
        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        Type_t type; // 08
        UInt32 count; // 10
        UInt32 pad_14; // 14
        UInt64 lock; // 18
        //Variable_t variables[0]; // 20

        Variable_t* Variables();

        // see VMArray, it's a wrapper of this object
        // so you can add similar templated funcs.
    };
    STATIC_ASSERT(sizeof(Array_t) == 0x20);

    class Object_t;
    class Alias_Base_t;
    class Variable_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        template <typename Type>
        static Variable_t* Fetch(Type* bsobject,
                                 String_t class_name,
                                 String_t variable_name);

        Type_t type;
        union Variable_u {
            void* ptr;
            Int_t i;
            Float_t f;
            Bool_t b;
            Array_t* arr;
            Object_t* obj;
            String_t str;
        } data;

        Actor_t* Actor();
        Alias_Base_t* Alias();
        Bool_t Bool();
        Float_t Float();
        Int_t Int();
        String_t String();
        Reference_t* Reference();
    };
    STATIC_ASSERT(sizeof(Variable_t) == 0x10);

    class Class_Info_t {
    public:
        static Class_Info_t* Fetch(String_t class_name);

        struct Setting_Info_t {
            UInt64 unk_00; // 00
        };
        STATIC_ASSERT(sizeof(Setting_Info_t) == 0x8);

        struct Variable_Info_t {
            String_t name; // 00
            Type_t type; // 08
        };
        STATIC_ASSERT(sizeof(Variable_Info_t) == 0x10);

        struct Default_Info_t {
            UInt32 variable_idx; // 00
            UInt32 pad_04; // 04
            Variable_t variable; // 08
        };
        STATIC_ASSERT(sizeof(Default_Info_t) == 0x18);

        struct Property_Info_t {
            String_t name; // 00
            String_t parent_name; // 08
            String_t property_name; // 10
            Type_t type; // 18
            UInt32 flags_20; // 20
            UInt32 unk_24; // 24
            IFunction* getter; // 28
            IFunction* setter; // 30
            UInt32 auto_var_idx; // 38
            UInt32 flags_3C; // 3C
            String_t unk_40; // 40
        };
        STATIC_ASSERT(sizeof(Property_Info_t) == 0x48);

        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        String_t name; // 08
        Class_Info_t* parent; // 10
        String_t unk_18; // 18
        UInt32 flags_20; // 20
        UInt32 flags_24; // 24
        UInt32 flags_28; // 28
        UInt32 pad_2C; // 2C
        UInt8* data; // 30

        UInt64 Count_Setting_Infos();
        UInt64 Count_Variable_Infos();
        UInt64 Count_Default_Infos();
        UInt64 Count_Property_Infos();

        Setting_Info_t* Setting_Infos();
        Variable_Info_t* Variable_Infos();
        Default_Info_t* Default_Infos();
        Property_Info_t* Property_Infos();

        SInt64 Variable_Index(String_t variable_name);
        SInt64 Property_Index(String_t property_name);
        Property_Info_t* Property_Info(String_t property_name);

        void Hold();
        void Free();

        void Log();
        //void Log_Setting_Infos();
        void Log_Variable_Infos();
        void Log_Default_Infos();
        void Log_Property_Infos();
    };
    STATIC_ASSERT(sizeof(Class_Info_t) == 0x38);

    class Object_t {
    public:
        template <typename Type>
        static Object_t* Fetch(Type* bsobject, String_t class_name);

        UInt64 unk_00; // 00
        Class_Info_t* info; // 08
        String_t unk_10; // 10
        void* unk_18; // 18
        volatile Handle_t handle; // 20
        volatile SInt32 lock; // 28
        UInt32 pad_2C; // 2C
        //Variable_t variables[0]; // 30

        Handle_t Handle();
        Variable_t* Property(String_t property_name);
        Variable_t* Variable(String_t variable_name);
        Variable_t* Variables();

        void Log_Variables();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x30);

    class Function_t {
    public:
    };

    class Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_Alias
        };

        enum Flags : UInt32 {
            // ...
        };

        enum Fill_Types : UInt16 {
            CONDITION_FILL = 0,
            FORCED_FILL = 1
            // ...
        };

        virtual ~Alias_Base_t(); // 00
        virtual bool Load(TESFile* file); // 01
        virtual void Item(TESForm* form); // 02
        virtual String_t Type(); // 03

        // void* _vtbl; // 00
        String_t name; // 08
        Quest_t* quest; // 10
        UInt32 id; // 18
        UInt32 flags; // 1C
        UInt16 fill_type; // 20
        UInt16 pad_22; // 22
        UInt32 pad_24; // 24
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

    class Alias_Reference_t : public Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_ReferenceAlias
        };

        struct Forced_Fill {
            Reference_Handle_t ref_handle; // this never seems to be there...
        };
        STATIC_ASSERT(sizeof(Forced_Fill) == 0x4);

        union Fill_u {
            UInt64 padding[3];
            Forced_Fill forced;
        };
        STATIC_ASSERT(sizeof(Fill_u) == 0x18);

        virtual ~Alias_Reference_t(); // 00
        virtual bool Load(TESFile* file) override; // 01
        virtual void Item(TESForm* form) override; // 02
        virtual String_t Type() override; // 03

        Fill_u fill; // 28
        void* conditions; // 40
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

    class Actor_Base_Data_t : public BaseFormComponent {
    public:
        enum Flags : UInt32 {
            FLAG_FEMALE = 1 << 0,
            FLAG_ESSENTIAL = 1 << 1,
            FLAG_FACE_PRESET = 1 << 2,
            FLAG_RESPAWNS = 1 << 3,
            FLAG_AUTO_STATS = 1 << 4,
            FLAG_UNIQUE = 1 << 5
            // ...
        };

        UInt32 flags; // 08

        Bool_t Is_Unique()
        {
            return (flags & FLAG_UNIQUE) != 0;
        }
    };

    class Scripts : public IForEachScriptObjectFunctor
    {
    public:
        Handle_t handle;
        std::vector<const char *> names;
        std::vector<Script_t *> scripts;

        Scripts(Form_t *form)
        {
            handle = Papyrus::Handle_t(form);
            handle.Registry()->VisitScripts(handle, this);
        }
        Scripts(Alias_Base_t* alias)
        {
            handle = Papyrus::Handle_t(alias);
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
    Vector_t<Type> Slice_Array(VMArray<Type> arr, SInt32 from = 0, SInt32 to_exclusive = -1)
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
    Vector_t<Type> Slice_Vector(Vector_t<Type> vec, SInt32 from = 0, SInt32 to_exclusive = -1)
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
