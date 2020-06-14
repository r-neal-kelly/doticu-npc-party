/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "form.h"
#include "game.h"
#include "object_ref.h"
#include "package.h"

namespace doticu_npcp { namespace Package {

    void Decompile(TESPackage *package, TESObjectREFR *target)
    {
        if (package && target)
        {
            _MESSAGE("Decompiling Package: p %p, f %X, n %s", package, package->formID, Form::Get_Name(package));
            _MESSAGE("            Target:  p %p, f %X, n %s", target, target->formID, Object_Ref::Get_Name(target));
            _MESSAGE("    0x000, void *_vtbl: %p", (void *)*(u8 **)((u8 *)package + 0x000));
            _MESSAGE("    0x024, u8 type: %u", *((u8 *)package + 0x024));
            _MESSAGE("    0x030, void *unk30: %p", (void *)*(u8 **)((u8 *)package + 0x030));

            for (u64 idx = sizeof(TESForm), size = sizeof(TESPackage) + 100; idx < size; idx += 1)
            {
                u8 *ptr = (u8 *)package + idx;

                if (size - idx > sizeof(void *))
                {
                    TESObjectREFR *ref = *(TESObjectREFR **)ptr;
                    if (ref == target)
                    {
                        _MESSAGE("    Found target point at offset: %X", idx);
                    }

                    uintptr_t intptr = (uintptr_t)(*(u8 **)ptr);
                    if (intptr > 0x180000000 && intptr < 0x200000000)
                    {
                        _MESSAGE("    Found possible ptr at offset: %X, ptr: %p", idx, intptr);
                    }
                    if (intptr > 0x140000000 && intptr < 0x150000000)
                    {
                        _MESSAGE("    Found possible _vtbl at offset: %X, ptr: %p", idx, intptr);
                        if (intptr == *(uintptr_t *)package)
                        {
                            return Decompile((TESPackage *)ptr, target);
                        }
                    }
                }

                if (size - idx > sizeof(UInt32))
                {
                    UInt32 form_id = *(UInt32 *)ptr;
                    if (form_id == target->formID)
                    {
                        _MESSAGE("    Found target form_id at offset: %X", idx);
                    }
                    if (form_id == (target->formID & 0x00FFFFFF))
                    {
                        _MESSAGE("    Found target lower_form_id at offset: &X", idx);
                    }
                }
            }

            _MESSAGE("End Package Decompilation.\n");
        }
    }

}}

namespace doticu_npcp { namespace Package { namespace Exports {

    bool Register(VMClassRegistry *registry)
    {
        return true;
    }

}}}
