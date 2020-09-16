/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos {

    void Execute_Topic_Info(Topic_Info_t* topic_info, Reference_t* ref);

}}}

namespace doticu_npcp { namespace Papyrus { namespace Topic_Infos { namespace Exports {

    Bool_t Register(VMClassRegistry *registry);

}}}}
