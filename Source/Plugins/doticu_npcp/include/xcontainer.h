/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "xentry.h"

namespace doticu_npcp { namespace Papyrus {

    class Container_Changes_t {
    public:
        XEntries_t* xentries; // 00
        Reference_t* owner; // 08
        Float_t total_weight; // 10
        Float_t armor_weight; // 14
        Bool_t has_changed; // 18
        UInt8 pad_19; // 19
        UInt16 pad_1A; // 1A
        UInt32 pad_1C; // 1C

        void Add_XEntry(XEntry_t* to_add, Reference_t* owner);
        void Remove_XEntry(XEntry_t* xentry);
        XEntry_t* XEntry(Form_t* form, Bool_t allow_creation);

        void Validate();
    };
    STATIC_ASSERT(sizeof(Container_Changes_t) == 0x20);

    class XContainer_t : public BSExtraData {
	public:
		virtual ~XContainer_t();

		Container_Changes_t* changes;

        void Add_XEntry(XEntry_t* xentry, Reference_t* owner);
        void Remove_XEntry(XEntry_t* xentry);
        XEntry_t* XEntry(Form_t* form, Bool_t allow_creation);

        void Validate();
    };

}}
