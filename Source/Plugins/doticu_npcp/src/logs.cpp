/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "logs.h"
#include "papyrus.inl"
#include "ui.h"
#include "utils.h"

namespace doticu_npcp { namespace Modules {

    String_t Logs_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_logs");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Logs_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Logs_t* Logs_t::Self()
    {
        return static_cast<Logs_t*>(Consts::Funcs_Quest());
    }

    Object_t* Logs_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Logs_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Logs_t::Notes_Variable() { DEFINE_VARIABLE("p_notes"); }
    Variable_t* Logs_t::Notes_Count_Variable() { DEFINE_VARIABLE("p_notes_used"); }
    Variable_t* Logs_t::Notes_Pivot_Variable() { DEFINE_VARIABLE("p_notes_pivot"); }

    Variable_t* Logs_t::Errors_Variable() { DEFINE_VARIABLE("p_errors"); }
    Variable_t* Logs_t::Errors_Count_Variable() { DEFINE_VARIABLE("p_errors_used"); }
    Variable_t* Logs_t::Errors_Pivot_Variable() { DEFINE_VARIABLE("p_errors_pivot"); }

    Array_t* Logs_t::Notes_Array()
    {
        return Notes_Variable()->Array();
    }

    void Logs_t::Notes_Array(Vector_t<String_t> notes)
    {
        Notes_Variable()->Pack(notes);
    }

    Int_t Logs_t::Notes_Count()
    {
        return Notes_Count_Variable()->Int();
    }

    void Logs_t::Notes_Count(Int_t count)
    {
        Notes_Count_Variable()->Int(count);
    }

    Int_t Logs_t::Notes_Pivot()
    {
        return Notes_Pivot_Variable()->Int();
    }

    void Logs_t::Notes_Pivot(Int_t pivot)
    {
        Notes_Pivot_Variable()->Int(pivot);
    }

    Array_t* Logs_t::Errors_Array()
    {
        return Errors_Variable()->Array();
    }

    void Logs_t::Errors_Array(Vector_t<String_t> errors)
    {
        Errors_Variable()->Pack(errors);
    }

    Int_t Logs_t::Errors_Count()
    {
        return Errors_Count_Variable()->Int();
    }

    void Logs_t::Errors_Count(Int_t count)
    {
        Errors_Count_Variable()->Int(count);
    }

    Int_t Logs_t::Errors_Pivot()
    {
        return Errors_Pivot_Variable()->Int();
    }

    void Logs_t::Errors_Pivot(Int_t pivot)
    {
        Errors_Pivot_Variable()->Int(pivot);
    }

    void Logs_t::Initialize()
    {
        Vector_t<String_t> notes;
        Vector_t<String_t> errors;
        notes.reserve(MAX);
        errors.reserve(MAX);

        for (size_t idx = 0; idx < MAX; idx += 1) {
            notes.push_back("");
            errors.push_back("");
        }

        Notes_Array(notes);
        Errors_Array(errors);

        Notes_Count(0);
        Errors_Count(0);

        Notes_Pivot(MAX - 1);
        Errors_Pivot(MAX - 1);
    }

    void Logs_t::Uninitialize()
    {
        Vector_t<String_t> notes;
        Vector_t<String_t> errors;

        Notes_Array(notes);
        Errors_Array(errors);

        Notes_Count(0);
        Errors_Count(0);

        Notes_Pivot(0);
        Errors_Pivot(0);
    }

    void Logs_t::Reinitialize()
    {
        Uninitialize();
        Initialize();
    }

    template <
        Array_t*(Logs_t::* Get_Array)(),
        Int_t(Logs_t::* Get_Count)(), void(Logs_t::* Set_Count)(Int_t),
        Int_t(Logs_t::* Get_Pivot)(), void(Logs_t::* Set_Pivot)(Int_t)
    > static inline void Log(Logs_t* logs, String_t str, Bool_t do_log)
    {
        static Bool_t do_add_space = false;

        if (str && str.data && str.data[0]) {
            if (UI::Is_Menu_Open("Journal Menu")) { // may need to use callback
                UI::Message_Box((std::string("NPC Party: ") + str.data).c_str());
            } else {
                if (do_add_space) {
                    UI::Notification((std::string("NPC Party: ") + str.data + " ").c_str());
                } else {
                    UI::Notification((std::string("NPC Party: ") + str.data).c_str());
                }
                do_add_space = !do_add_space;
            }

            if (do_log) {
                Array_t* array = (logs->*Get_Array)();

                Int_t pivot = (logs->*Get_Pivot)() + 1;
                if (pivot < 0 || pivot >= array->count) {
                    pivot = 0;
                }
                (logs->*Set_Pivot)(pivot);

                array->Point(pivot)->String(str);

                Int_t count = (logs->*Get_Count)();
                if (count < array->count) {
                    (logs->*Set_Count)(count + 1);
                }
            }
        }
    }

    void Logs_t::Log_Note(String_t note, Bool_t do_log)
    {
        Log<
            &Logs_t::Notes_Array,
            &Logs_t::Notes_Count, &Logs_t::Notes_Count,
            &Logs_t::Notes_Pivot, &Logs_t::Notes_Pivot
        >(this, note, do_log);
    }

    void Logs_t::Log_Error(String_t error, Bool_t do_log)
    {
        Log<
            &Logs_t::Errors_Array,
            &Logs_t::Errors_Count, &Logs_t::Errors_Count,
            &Logs_t::Errors_Pivot, &Logs_t::Errors_Pivot
        >(this, error, do_log);
    }

    void Logs_t::Clear_Notes()
    {
        Array_t* notes = Notes_Array();
        for (size_t idx = 0; idx < notes->count; idx += 1) {
            notes->Point(idx)->String("");
        }
        Notes_Count(0);
        Notes_Pivot(notes->count - 1);
    }

    void Logs_t::Clear_Errors()
    {
        Array_t* errors = Errors_Array();
        for (size_t idx = 0; idx < errors->count; idx += 1) {
            errors->Point(idx)->String("");
        }
        Errors_Count(0);
        Errors_Pivot(errors->count - 1);
    }

    static inline Vector_t<String_t> Slice(Array_t* array, Int_t count, Int_t pivot, Int_t begin = 0, Int_t end = -1)
    {
        NPCP_ASSERT(array);

        if (count < 0) {
            count = 0;
        } else if (count > array->count) {
            count = array->count;
        }

        if (pivot < 0) {
            pivot = 0;
        } else if (pivot >= array->count) {
            pivot = array->count - 1;
        }

        if (begin < 0) {
            begin = 0;
        }

        if (end > count || end < 0) {
            end = count;
        }

        Int_t slice_count = end - begin;
        if (slice_count < 1) {
            return Vector_t<String_t>();
        }

        Int_t slice_begin = pivot - begin;
        if (slice_begin < 0) {
            slice_begin += array->count;
        }

        Vector_t<String_t> slice;
        slice.reserve(slice_count);
        for (Int_t idx = slice_begin, count = 0; count < slice_count; idx -= 1, count += 1) {
            if (idx < 0) {
                idx = array->count - 1;
            }
            slice.push_back(array->Point(idx)->String());
        }

        return slice;
    }

    Vector_t<String_t> Logs_t::Notes(Int_t begin, Int_t end)
    {
        return Slice(Notes_Array(), Notes_Count(), Notes_Pivot(), begin, end);
    }

    Vector_t<String_t> Logs_t::Errors(Int_t begin, Int_t end)
    {
        return Slice(Errors_Array(), Errors_Count(), Errors_Pivot(), begin, end);
    }

    void Logs_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Logs_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}
