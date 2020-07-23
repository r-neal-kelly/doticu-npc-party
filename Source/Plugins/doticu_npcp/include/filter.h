/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"
#include "papyrus.inl"

namespace doticu_npcp { namespace Papyrus {

    class Filter_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Filter_t* Self();
        static Object_t* Object();

        static Variable_t* Variable(String_t variable_name);
        static Variable_t* Sex_Variable();
        static Variable_t* Race_Variable();
        static Variable_t* Search_Variable();
        static Variable_t* Style_Variable();
        static Variable_t* Vitality_Variable();
        static Variable_t* Outfit2_Variable();
        static Variable_t* Rating_Variable();
        static Variable_t* Flags_1_Variable();

        static Vector_t<String_t> Strings();
        static Vector_t<Int_t> Ints();
        static Int_t Flags_1();
        static Int_t Flags_2();
    };

}}

namespace doticu_npcp { namespace Filter { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
