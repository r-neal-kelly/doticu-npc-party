/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Modules {

    using namespace Papyrus;

    class Logs_t : public Quest_t {
    public:
        static constexpr size_t MAX = 64;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Logs_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Notes_Variable(); // Array_t* of String_t
        Variable_t* Notes_Count_Variable(); // Int_t
        Variable_t* Notes_Pivot_Variable(); // Int_t, points to latest note

        Variable_t* Errors_Variable(); // Array_t* of String_t
        Variable_t* Errors_Count_Variable(); // Int_t
        Variable_t* Errors_Pivot_Variable(); // Int_t, points to latest error

        Array_t* Notes_Array();
        void Notes_Array(Vector_t<String_t> notes);
        Int_t Notes_Count();
        void Notes_Count(Int_t count);
        Int_t Notes_Pivot();
        void Notes_Pivot(Int_t pivot);

        Array_t* Errors_Array();
        void Errors_Array(Vector_t<String_t> errors);
        Int_t Errors_Count();
        void Errors_Count(Int_t count);
        Int_t Errors_Pivot();
        void Errors_Pivot(Int_t pivot);

        void Initialize();
        void Uninitialize();
        void Reinitialize();

        void Log_Note(String_t note, Bool_t do_log = true);
        void Log_Error(String_t error, Bool_t do_log = true);

        void Clear_Notes();
        void Clear_Errors();

        Vector_t<String_t> Notes(Int_t begin = 0, Int_t end = -1);
        Vector_t<String_t> Errors(Int_t begin = 0, Int_t end = -1);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}
