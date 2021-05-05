/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skse_plugin.h"

#include "intrinsic.h"

namespace doticu_npcp {

    class Main_t;

    class NPCP_t :
        public SKSE_Plugin_t
    {
    public:
        maybe<Main_t*> main;

    public:
        NPCP_t(const some<const char*> plugin_name);

    public:
        virtual         ~NPCP_t();
        virtual Bool_t  On_Register(some<V::Machine_t*> machine) override;
        virtual void    On_Message(some<SKSE_Message_t*> message) override;

    public:
        Bool_t  Is_Active();

        Main_t& Main();
    };

    extern NPCP_t NPCP;

}
