/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Papyrus {

    // a lot of credit for deciphering these classes goes to Ryan-rsm-McKenzie of CommonLibSSE as well as the SKSE team
    class Handle_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        UInt64 handle = 0;

        Handle_t(void* instance, Type_ID_t type_id);
        template <typename Type>
        Handle_t(Type* instance);
        Handle_t(Form_t* form);
        Handle_t(UInt64 handle);
        Handle_t();

        Bool_t Is_Valid();
        Bool_t Has_Type_ID(Type_ID_t type_id);

        operator UInt64();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

    class Class_Info_t;
    class Object_t;
    class Array_t;
    class Type_t;
    class Handle_Policy_t;
    class Object_Policy_t;
    class Virtual_Arguments_i;
    class Virtual_Callback_i;
    class Variable_t;

    class Virtual_Machine_i {
    public:
        virtual ~Virtual_Machine_i(); // 00

        virtual void _01(void) = 0; // 01
        virtual void _02(void) = 0; // 02
        virtual void _03(void) = 0; // 03
        virtual void _04(void) = 0; // 04
        virtual void _05(void) = 0; // 05
        virtual void _06(void) = 0; // 06
        virtual void _07(void) = 0; // 07
        virtual void _08(void) = 0; // 08
        virtual Bool_t Load_Class_Info(String_t* class_name, Class_Info_t** info_out) = 0; // 09, call Class_Info_t Free() after use
        virtual Bool_t Load_Class_Info2(Type_ID_t type_id, Class_Info_t** info_out) = 0; // 0A, call Class_Info_t Free() after use
        virtual Bool_t Class_Info(String_t* class_name, Class_Info_t** info_out) = 0; // 0B, call Class_Info_t Free() after use
        virtual Bool_t Class_Info2(Type_ID_t type_id, Class_Info_t** info_out) = 0; // 0C, call Class_Info_t Free() after use
        virtual Bool_t Type_ID(String_t* class_name, Type_ID_t* type_id_out) = 0; // 0D
        virtual void _0E(void) = 0; // 0E
        virtual void _0F(void) = 0; // 0F
        virtual void _10(void) = 0; // 10
        virtual void _11(void) = 0; // 11
        virtual void _12(void) = 0; // 12
        virtual void _13(void) = 0; // 13
        virtual void _14(void) = 0; // 14
        virtual Bool_t Create_Object2(String_t* class_name, Object_t** object_out) = 0; // 15
        virtual Bool_t Create_Array(Type_t* type, UInt32 count, Array_t** array_out) = 0; // 16, SKSE has Variable_t* for first arg?
        virtual void _17(void) = 0; // 17
        virtual Bool_t Bind_Function(IFunction* function) = 0; // 18
        virtual void _19(void) = 0; // 19
        virtual void _1A(void) = 0; // 1A
        virtual void For_Each_Object(Handle_t handle, IForEachScriptObjectFunctor* functor) = 0; // 1B
        virtual Bool_t Find_Bound_Object(Handle_t handle, String_t class_name, Object_t** object_out) = 0; // 1C
        virtual void _1D(void) = 0; // 1D
        virtual void _1E(void) = 0; // 1E
        virtual Bool_t Cast_Object(Object_t** object_in, Class_Info_t** cast_to, Object_t** object_out) = 0; // 1F
        virtual void _20(void) = 0; // 20
        virtual void _21(void) = 0; // 21
        virtual void _22(void) = 0; // 22
        virtual void _23(void) = 0; // 23
        virtual void Send_Event(Handle_t handle, String_t* event_name, IFunctionArguments* arguments) = 0; // 24
        virtual void _25(void) = 0; // 25
        virtual Bool_t Call_Global(String_t* class_name, String_t* function_name, Virtual_Arguments_i* arguments, Virtual_Callback_i** callback) = 0; // 26
        virtual void _27(void) = 0; // 27
        virtual Bool_t Call_Method2(Handle_t handle, String_t* class_name, String_t* function_name, Virtual_Arguments_i* arguments, Virtual_Callback_i** callback) = 0; // 28
        virtual void _29(void) = 0; // 29
        virtual void _2A(void) = 0; // 2A
        virtual void Return_Latent_Function(Stack_ID_t stack_id, Variable_t* return_variable) = 0; // 2B
        virtual void _2C(void) = 0; // 2C
        virtual Handle_Policy_t* Handle_Policy() = 0; // 2D
        virtual void _2E(void) = 0; // 2E
        virtual Object_Policy_t* Object_Policy() = 0; // 2F
    };

    class Virtual_Binder_i {
    public:
        virtual ~Virtual_Binder_i(); // 00

        virtual Handle_t Bound_Handle(Object_t*& object) = 0; // 01
        virtual Bool_t Can_Bind_Class_To_Handle(String_t& class_name, Handle_t handle) = 0; // 02
        virtual void Bind_Object(Object_t*& object, Handle_t handle, Bool_t unk_bool) = 0; // 03
        virtual void Bind_Object2(Object_t*& object, Handle_t handle, Bool_t unk_bool) = 0; // 04 (not sure what this does differently)
        virtual void Unbind_All_Objects(Handle_t handle) = 0; // 05
        virtual void Unbind_All_Objects2(Handle_t handle) = 0; // 06 (not sure what this does differently)
        virtual void Unbind_All_Objects3(Handle_t handle) = 0; // 07 (this one may also delete stuff for us?)
        virtual void Unbind_Object(Object_t*& object) = 0; // 08
        virtual void Create_Object(String_t& class_name, UInt32 property_count, Object_t** object_out) = 0; // 09
        virtual void Initialize_Object_Properties(Object_t*& object, void* unk_property, Bool_t unk_bool) = 0; // 0A
    };

    class Handle_Policy_t {
    public:
        virtual ~Handle_Policy_t();

        virtual Bool_t Has_Type_ID(Type_ID_t type_id, Handle_t handle); // 01
        virtual Bool_t Is_Valid(Handle_t handle); // 02
        virtual Handle_t Invalid_Handle(); // 03
        virtual Handle_t Handle(Type_ID_t type_id, const void* data); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual void _09(void); // 09
        virtual void Release(Handle_t handle); // 0A
        virtual void _0B(void); // 0B
    };

    class Object_Policy_t {
    public:
        virtual ~Object_Policy_t();

        void Bind_Object(Object_t*& object, Handle_t handle);
        void Unbind_Object(Object_t*& object);

        Virtual_Machine_i* virtual_machine; // 08
        Virtual_Binder_i* virtual_binder; // 10
    };

    class Virtual_Machine_t :
        public Virtual_Machine_i
    {
    public:
        static Virtual_Machine_t* Self();
    public:
        virtual ~Virtual_Machine_t(); // 00

        // Virtual_Machine_Base_t
        virtual void _01(void) override; // 01
        virtual void _02(void) override; // 02
        virtual void _03(void) override; // 03
        virtual void _04(void) override; // 04
        virtual void _05(void) override; // 05
        virtual void _06(void) override; // 06
        virtual void _07(void) override; // 07
        virtual void _08(void) override; // 08
        virtual Bool_t Load_Class_Info(String_t* class_name, Class_Info_t** info_out) override; // 09, call Class_Info_t Free() after use
        virtual Bool_t Load_Class_Info2(Type_ID_t type_id, Class_Info_t** info_out) override; // 0A, call Class_Info_t Free() after use
        virtual Bool_t Class_Info(String_t* class_name, Class_Info_t** info_out) override; // 0B, call Class_Info_t Free() after use
        virtual Bool_t Class_Info2(Type_ID_t type_id, Class_Info_t** info_out) override; // 0C, call Class_Info_t Free() after use
        virtual Bool_t Type_ID(String_t* class_name, Type_ID_t* type_id_out) override; // 0D
        virtual void _0E(void) override; // 0E
        virtual void _0F(void) override; // 0F
        virtual void _10(void) override; // 10
        virtual void _11(void) override; // 11
        virtual void _12(void) override; // 12
        virtual void _13(void) override; // 13
        virtual void _14(void) override; // 14
        virtual Bool_t Create_Object2(String_t* class_name, Object_t** object_out) override; // 15
        virtual Bool_t Create_Array(Type_t* type, UInt32 count, Array_t** array_out) override; // 16, SKSE has Variable_t* for first arg?
        virtual void _17(void) override; // 17
        virtual Bool_t Bind_Function(IFunction* function) override; // 18
        virtual void _19(void) override; // 19
        virtual void _1A(void) override; // 1A
        virtual void For_Each_Object(Handle_t handle, IForEachScriptObjectFunctor* functor) override; // 1B
        virtual Bool_t Find_Bound_Object(Handle_t handle, String_t class_name, Object_t** object_out) override; // 1C
        virtual void _1D(void) override; // 1D
        virtual void _1E(void) override; // 1E
        virtual Bool_t Cast_Object(Object_t** object_in, Class_Info_t** cast_to, Object_t** object_out) override; // 1F
        virtual void _20(void) override; // 20
        virtual void _21(void) override; // 21
        virtual void _22(void) override; // 22
        virtual void _23(void) override; // 23
        virtual void Send_Event(Handle_t handle, String_t* event_name, IFunctionArguments* arguments) override; // 24
        virtual void _25(void) override; // 25
        virtual Bool_t Call_Global(String_t* class_name, String_t* function_name, Virtual_Arguments_i* arguments, Virtual_Callback_i** callback) override; // 26
        virtual void _27(void) override; // 27
        virtual Bool_t Call_Method2(Handle_t handle, String_t* class_name, String_t* function_name, Virtual_Arguments_i* arguments, Virtual_Callback_i** callback) override; // 28
        virtual void _29(void) override; // 29
        virtual void _2A(void) override; // 2A
        virtual void Return_Latent_Function(Stack_ID_t stack_id, Variable_t* return_variable) override; // 2B
        virtual void _2C(void) override; // 2C
        virtual Handle_Policy_t* Handle_Policy() override; // 2D
        virtual void _2E(void) override; // 2E
        virtual Object_Policy_t* Object_Policy() override; // 2F

        template <typename BSObject>
        void Send_Event(BSObject* object, String_t event_name, IFunctionArguments* arguments);
        template <typename BSObject>
        void Send_Event(BSObject* object, String_t event_name);

        Bool_t Call_Global(String_t class_name,
                           String_t function_name,
                           Virtual_Arguments_i* arguments = nullptr,
                           Virtual_Callback_i** callback = nullptr);
        Bool_t Call_Method(Handle_t handle,
                           String_t class_name,
                           String_t function_name,
                           Virtual_Arguments_i* arguments = nullptr,
                           Virtual_Callback_i** callback = nullptr);

        Int_t Count_Objects(Handle_t handle);
        Bool_t Has_Object(Handle_t handle);

        Type_ID_t Type_ID(String_t class_name);
    };

    class Variable_t;
    class Virtual_Arguments_i {
    public:
        struct Arguments_t {
            UInt32 unk00; // 00
            UInt32 unk04; // 04
            Variable_t* variables; // 08
            UInt64 unk08; // 10
            UInt32 count; // 18

            Bool_t Resize(UInt32 count);
            Variable_t* At(UInt32 idx);
        };
        STATIC_ASSERT(sizeof(Arguments_t) == 0x20);

        virtual ~Virtual_Arguments_i() = default; // 00

        virtual Bool_t operator()(Arguments_t* arguments) = 0; // 01
    };
    STATIC_ASSERT(sizeof(Virtual_Arguments_i) == 0x8);

    class Virtual_Arguments_t : public Virtual_Arguments_i {
    public:
        virtual Bool_t operator()(Arguments_t* arguments) override { return true; } // 01
    };
    STATIC_ASSERT(sizeof(Virtual_Arguments_i) == 0x8);

    class Object_t;
    class Variable_t;
    class Virtual_Callback_i {
    public:
        UInt32 ref_count = 0; // 00
        // void* _vtbl; // 04 (I think)
        UInt32 pad_04; // 0C

        virtual ~Virtual_Callback_i() = default; // 00

        virtual void operator()(Variable_t* result) = 0; // 01
        virtual Bool_t Can_Save() = 0; // 02
        virtual void Set_Object(Object_t** object) = 0; // 03
    };
    STATIC_ASSERT(sizeof(Virtual_Callback_i) == 0x10);

    class Virtual_Callback_t : public Virtual_Callback_i {
    public:
        virtual void operator()(Variable_t* result) override {}; // 01
        virtual Bool_t Can_Save() override { return false; } // 02
        virtual void Set_Object(Object_t** object) override {} // 03
    };
    STATIC_ASSERT(sizeof(Virtual_Callback_i) == 0x10);

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
    public:
        Type_t();
        Type_t(Type_e type);
        Type_t(Class_Info_t* class_info);

        UInt64 mangled;

        Type_e Unmangled();
        Class_Info_t* Class_Info();
        String_t To_String();

        Bool_t Is_None();
        Bool_t Is_Bool();
        Bool_t Is_Int();
        Bool_t Is_Float();
        Bool_t Is_String();
        Bool_t Is_Object();
        Bool_t Is_Array();
        Bool_t Is_None_Array();
        Bool_t Is_Object_Array();
        Bool_t Is_String_Array();
        Bool_t Is_Int_Array();
        Bool_t Is_Float_Array();
        Bool_t Is_Bool_Array();
    };
    STATIC_ASSERT(sizeof(Type_t) == 0x8);

    class Variable_t;
    class Array_t {
    public:
        static Array_t* Create(Type_t* item_type, UInt32 count);
        static void Destroy(Array_t* arr);
    public:
        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        Type_t item_type; // 08
        UInt32 count; // 10
        UInt32 pad_14; // 14
        UInt64 lock; // 18
        //Variable_t variables[0]; // 20

        void Increment_Count();
        void Decrement_Count();
        Type_t Array_Type();
        Variable_t* Variables();
        Variable_t* Point(size_t idx);
        template <typename Type>
        Vector_t<Type> Vector();
        template <typename Type>
        Vector_t<Type*> Vector(Type_ID_t type_id);
        template <typename Type>
        Int_t Find(Type element);
        template <typename Type>
        Int_t Find(Type_ID_t type_id, Type* element);
        template <typename Type>
        Bool_t Has(Type element);
        template <typename Type>
        Bool_t Has(Type_ID_t type_id, Type* element);

        // see VMArray, it's a wrapper of this object
        // so you can add similar templated funcs.
    };
    STATIC_ASSERT(sizeof(Array_t) == 0x20);

    class Object_t;
    class Variable_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        template <typename Type>
        static Variable_t* Fetch(Type* bsobject,
                                 String_t class_name,
                                 String_t variable_name);
    public:
        Variable_t();

        Type_t type;
        union Variable_u {
            Variable_u();

            void* ptr;
            Bool_t b;
            Int_t i;
            Float_t f;
            String_t str;
            Object_t* obj;
            Array_t* arr;
        } data;

        void Destroy();
        void Copy(Variable_t* other);

        Bool_t Is_None();
        Bool_t Is_Bool();
        Bool_t Is_Int();
        Bool_t Is_Float();
        Bool_t Is_String();
        Bool_t Is_Object();
        Bool_t Is_Array();
        Bool_t Is_None_Array();
        Bool_t Is_Object_Array();
        Bool_t Is_String_Array();
        Bool_t Is_Int_Array();
        Bool_t Is_Float_Array();
        Bool_t Is_Bool_Array();

        Bool_t Has_String();
        Bool_t Has_Object();

        Bool_t Bool();
        Int_t Int();
        Float_t Float();
        String_t String();
        Object_t* Object();
        Array_t* Array();
        Array_t* Object_Array();
        template <typename Type>
        Type* Resolve(Type_ID_t type_id);
        Form_t* Form();
        Actor_t* Actor();
        Alias_Base_t* Alias();
        Faction_t* Faction();
        Misc_t* Misc();
        Outfit_t* Outfit();
        Reference_t* Reference();
        template <typename Type>
        Vector_t<Type> Vector();

        void None(Type_t type);
        void Bool(Bool_t value);
        void Int(Int_t value);
        void Float(Float_t value);
        void String(String_t value);
        void Object(Object_t* value);
        void Array(Array_t* value);

        template <typename Type>
        void Pack(Type* value, Class_Info_t* class_info);
        template <typename Type>
        void Pack(Type* value);
        template <typename Type>
        void Pack(Vector_t<Type>& values);
    };
    STATIC_ASSERT(sizeof(Variable_t) == 0x10);

    class Class_Info_t {
    public:
        static Class_Info_t* Fetch(String_t class_name, Bool_t do_auto_decrement = false);
        static Class_Info_t* Fetch(Type_ID_t type_id, Bool_t do_auto_decrement = false);

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
        static Object_t* Fetch(Type* instance, String_t class_name);
        template <typename Type>
        static Object_t* Create(Type* instance, String_t class_name);
        template <typename Type>
        static Object_t* Create(Type* instance, Class_Info_t* class_info);

        UInt64 unk_00; // 00
        Class_Info_t* info; // 08
        String_t unk_10; // 10
        void* unk_18; // 18
        volatile Handle_t handle; // 20
        volatile SInt32 lock; // 28
        UInt32 pad_2C; // 2C
        //Variable_t variables[0]; // 30

        void Destroy();
        void Increment_Lock();
        UInt32 Decrement_Lock();

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
