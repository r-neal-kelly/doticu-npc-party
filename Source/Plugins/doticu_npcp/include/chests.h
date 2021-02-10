/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcp {

    class Form_t;
    class Reference_t;

    class Chests_t
    {
    public:
        static constexpr size_t MAX_CUSTOM_CHESTS = 16;

    public:
        static some<Reference_t*>   Chest(some<Form_t*> form);
        static some<Reference_t*>   Custom_Chest(some<Form_t*> form);
        static void                 Open_Chest(some<Reference_t*> chest);
        static void                 Update_Chests();

    public:
        static void Categorize_All_Items(some<Reference_t*> ref);
        static void Categorize_Custom_Items(some<Reference_t*> ref);
    };

}
