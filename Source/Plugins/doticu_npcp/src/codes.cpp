/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "utils.h"

namespace doticu_npcp { namespace CODES {



}}

namespace doticu_npcp { namespace CODES { namespace Exports {

    Int_t SUCCESS(Selfless_t*)          { return CODES::SUCCESS; }
    Int_t FAILURE(Selfless_t*)          { return CODES::FAILURE; }
    Int_t OUT_OF_BOUNDS(Selfless_t*)    { return CODES::OUT_OF_BOUNDS; }

    Int_t IS_DISPLAY(Selfless_t*)       { return CODES::IS_DISPLAY; }
    Int_t ISNT_DISPLAY(Selfless_t*)     { return CODES::ISNT_DISPLAY; }
    Int_t IS_MEMBER(Selfless_t*)        { return CODES::IS_MEMBER; }
    Int_t ISNT_MEMBER(Selfless_t*)      { return CODES::ISNT_MEMBER; }

    Int_t HAS_DISPLAY(Selfless_t*)      { return CODES::HAS_DISPLAY; }
    Int_t HASNT_DISPLAY(Selfless_t*)    { return CODES::HASNT_DISPLAY; }
    Int_t HAS_MEMBER(Selfless_t*)       { return CODES::HAS_MEMBER; }
    Int_t HASNT_MEMBER(Selfless_t*)     { return CODES::HASNT_MEMBER; }

    bool Register(Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_codes", Selfless_t,           \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("SUCCESS", 0, Int_t, SUCCESS);
        ADD_GLOBAL("FAILURE", 0, Int_t, FAILURE);
        ADD_GLOBAL("OUT_OF_BOUNDS", 0, Int_t, OUT_OF_BOUNDS);

        ADD_GLOBAL("IS_DISPLAY", 0, Int_t, IS_DISPLAY);
        ADD_GLOBAL("ISNT_DISPLAY", 0, Int_t, ISNT_DISPLAY);
        ADD_GLOBAL("IS_MEMBER", 0, Int_t, IS_MEMBER);
        ADD_GLOBAL("ISNT_MEMBER", 0, Int_t, ISNT_MEMBER);

        ADD_GLOBAL("HAS_DISPLAY", 0, Int_t, HAS_DISPLAY);
        ADD_GLOBAL("HASNT_DISPLAY", 0, Int_t, HASNT_DISPLAY);
        ADD_GLOBAL("HAS_MEMBER", 0, Int_t, HAS_MEMBER);
        ADD_GLOBAL("HASNT_MEMBER", 0, Int_t, HASNT_MEMBER);

        #undef ADD_GLOBAL

        return true;
    }

}}}
