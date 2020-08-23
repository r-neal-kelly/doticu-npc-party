/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "form.h"
#include "form_vector.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

namespace doticu_npcp { namespace Papyrus {

    String_t Form_Vector_t::Class_Name()
    {
        static String_t class_name = String_t("doticu_npcp_vector_form");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Form_Vector_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Variable_t* Form_Vector_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Form_Vector_t::Array_Variable()
    {
        static const String_t variable_name = String_t("p_arr_forms");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* Form_Vector_t::Count_Variable()
    {
        static const String_t variable_name = String_t("p_num_forms");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* Form_Vector_t::Filler_Variable()
    {
        static const String_t variable_name = String_t("p_item_fill");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Variable_t* Form_Vector_t::Grow_Rate_Variable()
    {
        static const String_t variable_name = String_t("p_grow_rate");
        NPCP_ASSERT(variable_name);
        Variable_t* variable = Variable(variable_name);
        NPCP_ASSERT(variable);
        return variable;
    }

    Form_Vector_t* Form_Vector_t::Create(Int_t reserve, Form_t* filler, Float_t grow_rate)
    {
        Form_Vector_t* form_vector = static_cast<Form_Vector_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Form_Vector(), 1));
        NPCP_ASSERT(form_vector);
        NPCP_ASSERT(reserve > -1);
        NPCP_ASSERT(grow_rate >= 1.0f);

        Vector_t<Form_t*> forms;
        forms.reserve(reserve);
        for (size_t idx = 0, count = reserve; idx < count; idx += 1) {
            forms.push_back(filler);
        }

        form_vector->Array_Variable()->Pack(forms);
        form_vector->Count_Variable()->Int(0);
        form_vector->Filler_Variable()->Pack(filler);
        form_vector->Grow_Rate_Variable()->Float(grow_rate);

        return form_vector;
    }

    void Form_Vector_t::Destroy(Form_Vector_t* form_vector)
    {
        NPCP_ASSERT(form_vector);

        form_vector->Array_Variable()->None(Type_t::OBJECT_ARRAY); // not sure if this will work correctly, maybe pass empty vector
        form_vector->Count_Variable()->Int(0);
        form_vector->Filler_Variable()->None(Class_Info_t::Fetch(Form_t::kTypeID, true));
        form_vector->Grow_Rate_Variable()->Float(0.0f);

        Object_Ref::Delete_Safe(form_vector);
    }

    Array_t* Form_Vector_t::Array()
    {
        Array_t* arr = Array_Variable()->Object_Array();
        NPCP_ASSERT(arr);
        return arr;
    }

    Int_t Form_Vector_t::Count()
    {
        Int_t count = Count_Variable()->Int();
        NPCP_ASSERT(count > -1);
        return count;
    }

    Int_t Form_Vector_t::Capacity()
    {
        Int_t capacity = static_cast<Int_t>(Array()->count);
        NPCP_ASSERT(capacity > -1);
        return capacity;
    }

    Form_t* Form_Vector_t::Filler()
    {
        return Filler_Variable()->Form();
    }

    Float_t Form_Vector_t::Grow_Rate()
    {
        Float_t grow_rate = Grow_Rate_Variable()->Float();
        NPCP_ASSERT(grow_rate >= 1.0f);
        return grow_rate;
    }

    void Form_Vector_t::Grow()
    {
        Array_t* arr = Array();

        Int_t old_capacity = arr->count;
        Int_t new_capacity = static_cast<Int_t>(ceilf(old_capacity * Grow_Rate()));
        if (new_capacity <= old_capacity) {
            new_capacity += 1;
        }
        NPCP_ASSERT(new_capacity > 0);

        Vector_t<Form_t*> vector;
        vector.reserve(new_capacity);
        for (Variable_t* data = Point(0), *end = data + Count(); data != end; data += 1) {
            vector.push_back(data->Form());
        }

        Form_t* filler = Filler();
        for (size_t idx = old_capacity; idx < new_capacity; idx += 1) {
            vector.push_back(filler);
        }

        Array_Variable()->Pack(vector);
    }

    Vector_t<Form_t*> Form_Vector_t::Vector()
    {
        Int_t count = Count();
        Vector_t<Form_t*> vector;
        vector.reserve(count);
        for (Variable_t* data = Point(0), *end = data + count; data != end; data += 1) {
            vector.push_back(data->Form());
        }
        return vector;
    }

    void Form_Vector_t::Push(Form_t* form)
    {
        Variable_t* count_variable = Count_Variable();
        Int_t count = count_variable->Int();
        if (count >= Capacity()) {
            Grow();
        }

        Point(count)->Pack(form);

        count += 1;
        NPCP_ASSERT(count > 0);
        count_variable->Int(count);
    }

    Form_t* Form_Vector_t::Pop()
    {
        Variable_t* count_variable = Count_Variable();
        Int_t count = count_variable->Int();
        NPCP_ASSERT(count > 0);
        count -= 1;
        count_variable->Int(count);

        Variable_t* form_variable = Point(count);
        Form_t* form = form_variable->Form();
        form_variable->Pack(Filler());
        
        return form;
    }

    Form_t* Form_Vector_t::At(Int_t idx)
    {
        NPCP_ASSERT(idx > -1 && idx < Count());
        return Point(idx)->Form();
    }

    Variable_t* Form_Vector_t::Point(Int_t idx)
    {
        NPCP_ASSERT(idx > -1 && idx <= Count());
        return Array()->Point(idx);
    }

    void Form_Vector_t::Set(Int_t idx, Form_t* form)
    {
        NPCP_ASSERT(idx > -1 && idx < Count());
        Point(idx)->Pack(form);
    }

    void Form_Vector_t::Remove_Unstable(Int_t idx)
    {
        Variable_t* count_variable = Count_Variable();
        Int_t count = count_variable->Int();
        NPCP_ASSERT(idx > -1 && idx < count);
        NPCP_ASSERT(count > 0);
        count -= 1;
        count_variable->Int(count);

        Variable_t* data = Point(0);
        Variable_t* last = data + count;
        if (idx != count) {
            (data + idx)->Pack(last->Form());
        }
        last->Pack(Filler());
    }

    Int_t Form_Vector_t::Find(Form_t* form)
    {
        Int_t idx = 0;
        for (Variable_t* data = Point(0), *end = data + Count(); data != end; data += 1, idx += 1) {
            if (data->Form() == form) {
                return idx;
            }
        }
        return -1;
    }

    Bool_t Form_Vector_t::Has(Form_t* form)
    {
        return Find(form) > -1;
    }

    void Form_Vector_t::Empty()
    {
        Vector_t<Form_t*> vector;
        Array_Variable()->Pack(vector);
        Count_Variable()->Int(0);
    }

}}

namespace doticu_npcp { namespace Form_Vector { namespace Exports {

    bool Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        #undef ADD_GLOBAL

        return true;
    }

}}}
