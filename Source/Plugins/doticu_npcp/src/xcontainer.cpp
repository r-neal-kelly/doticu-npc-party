/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64_common/Relocation.h"

#include "utils.h"
#include "xcontainer.h"

namespace doticu_npcp { namespace XContainer {

    XContainer_t *Create(TESObjectREFR *owner) {
        const RelocPtr<uintptr_t> xcontainer_vtbl(0x0152F260);
        XContainer_t *xcontainer = (XContainer_t *)XData_t::Create(sizeof(XContainer_t), xcontainer_vtbl.GetUIntPtr());
        Assert(xcontainer);

        xcontainer->data = Create_Data(owner);

        return xcontainer;
    }

    XContainer_t::Data *Create_Data(TESObjectREFR *owner) {

        XContainer_t::Data *data = (XContainer_t::Data *)Heap_Allocate(sizeof(XContainer_t::Data));
        Assert(data);

        data->objList = Create_Data_Entries();

        data->owner = owner;

        // might want to double check, but I think everything but player is set to -1.0
        data->totalWeight = 0.0;
        data->armorWeight = 0.0;

        return data;
    }

    XEntries_t *Create_Data_Entries() {
        XEntries_t *xentries = XEntries_t::Create();
        Assert(xentries);

        return xentries;
    }

}}
