/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus {

    class Form_Vector_t : public Reference_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Form_Vector_t* Create(Int_t reserve = 0, Form_t* filler = nullptr, Float_t grow_rate = 1.5f);
        static void Destroy(Form_Vector_t* form_vector);
    public:
        Variable_t* Variable(String_t variable_name);
        Variable_t* Array_Variable();
        Variable_t* Count_Variable();
        Variable_t* Filler_Variable();
        Variable_t* Grow_Rate_Variable();

        Array_t* Array();
        Int_t Count();
        Int_t Capacity();
        Form_t* Filler();
        Float_t Grow_Rate();

        void Grow();
        Vector_t<Form_t*> Vector();
        void Push(Form_t* form);
        Form_t* Pop();
        Form_t* At(Int_t idx);
        Variable_t* Point(Int_t idx);
        void Set(Int_t idx, Form_t* form);
        void Remove_Unstable(Int_t idx);
        Int_t Find(Form_t* form);
        Bool_t Has(Form_t* form);
        void Empty();
    };

}}
