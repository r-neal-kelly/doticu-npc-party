/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "form.h"
#include "game.h"
#include "object_ref.h"
#include "packages.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_player.h"

namespace doticu_npcp { namespace Papyrus { namespace Packages {

    void Execute_Package(Package_t* package, Actor_t* actor)
    {
        if (package == Consts::Menu_Exit_Package()) {
            return Execute_Menu_Exit();
        }
    }

    void Execute_Menu_Exit()
    {
        Party::Player_t::Self()->Close_Global_Dialogue_Menu();
    }

    void Log_Packages()
    {
        uintptr_t base = RelocationManager::s_baseAddr;

        DataHandler* data_handler = Game::Data_Handler();
        for (size_t idx = 0, end = data_handler->arrPACK.count; idx < end; idx += 1) {
            Package_t* package = static_cast<Package_t*>(data_handler->arrPACK.entries[idx]);
            _MESSAGE("package: %p, id: %p, data: %p, location: %p, target: %p",
                     package,
                     package->formID,
                     package->data,
                     package->location,
                     package->target);
            if (package->data) {
                Package_Data_t* package_data = package->data;

                _MESSAGE("    " "values: %p", package_data->values);
                for (size_t idx = 0, end = package_data->value_count; idx < end; idx += 1) {
                    Package_Value_t* value = package_data->values[idx];
                    Package_Value_t::Type_e value_type = value->Type();
                    if (value_type == Package_Value_t::Type_e::BOOL) {
                        Package_Bool_Value_t* bool_value =
                            static_cast<Package_Bool_Value_t*>(value);
                        _MESSAGE("        " "bool: %i", bool_value->value > 0);
                    } else if (value_type == Package_Value_t::Type_e::INT) {
                        Package_Int_Value_t* int_value =
                            static_cast<Package_Int_Value_t*>(value);
                        _MESSAGE("        " "int: %i", int_value->value);
                    } else if (value_type == Package_Value_t::Type_e::FLOAT) {
                        Package_Float_Value_t* float_value =
                            static_cast<Package_Float_Value_t*>(value);
                        _MESSAGE("        " "float: %f", float_value->value);
                    } else if (value_type == Package_Value_t::Type_e::LOCATION) {
                        Package_Location_Value_t* location_value =
                            static_cast<Package_Location_Value_t*>(value);
                        Package_Location_t* location = location_value->location;
                        if (location->type == Package_Location_t::Type_e::NEAR_REFERENCE) {
                            Reference_t* reference = Object_Ref::From_Handle(location->location.handle);
                            _MESSAGE("        " "location: %p, type: %u, reference: %p, form_id: 0x%X, form_type: %s, editor_id: %s, name: %s, radius: %u",
                                     location,
                                     location->type,
                                     reference,
                                     reference ? reference->formID : 0,
                                     reference ? Form::Get_Type_String(reference) : "",
                                     reference ? reference->Editor_ID() : "",
                                     reference ? Object_Ref::Get_Name(reference) : "",
                                     location->radius);
                        } else {
                            _MESSAGE("        " "location: %p, type: %u, form: %p, radius: %u",
                                     location,
                                     location->type,
                                     location->location.form,
                                     location->radius);
                        }
                    } else if (value_type == Package_Value_t::Type_e::SINGLE_REFERENCE) {
                        Package_Single_Reference_Value_t* reference_value =
                            static_cast<Package_Single_Reference_Value_t*>(value);
                        Package_Target_t* target = reference_value->target;
                        if (target->type == Package_Target_t::Type_e::SPECIFIC) {
                            Reference_t* specific = Object_Ref::From_Handle(target->target.specific);
                            _MESSAGE("        " "reference %p, type: %i, specific: %p, form_id: 0x%X, form_type: %s, editor_id: %s, name: %s, count_or_distance: %i",
                                     target,
                                     target->type,
                                     specific,
                                     specific ? specific->formID : 0,
                                     specific ? Form::Get_Type_String(specific) : "",
                                     specific ? specific->Editor_ID() : "",
                                     specific ? Object_Ref::Get_Name(specific) : "",
                                     target->count_or_distance);
                        } else if (target->type == Package_Target_t::Type_e::FORM_ID) {
                            _MESSAGE("        " "reference %p, type: %i, form_id: 0x%X, count_or_distance: %i",
                                     target,
                                     target->type,
                                     target->target.form_id,
                                     target->count_or_distance);
                        } else if (target->type == Package_Target_t::Type_e::FORM_TYPE) {
                            _MESSAGE("        " "reference %p, type: %i, form_type: %s, count_or_distance: %i",
                                     target,
                                     target->type,
                                     Form::Get_Type_String(target->target.form_type),
                                     target->count_or_distance);
                        } else if (target->type == Package_Target_t::Type_e::LINKED) {
                            Form_t* linked = target->target.linked;
                            _MESSAGE("        " "reference %p, type: %i, linked: %p, form_id: 0x%X, editor_id: %s, name: %s, count_or_distance: %i",
                                     target,
                                     target->type,
                                     linked,
                                     linked ? linked->formID : 0,
                                     linked ? linked->Editor_ID() : "",
                                     linked ? Form::Name(linked) : "",
                                     target->count_or_distance);
                        } else if (target->type == Package_Target_t::Type_e::ALIAS_ID) {
                            _MESSAGE("        " "reference %p, type: %i, alias_id: %u, count_or_distance: %i",
                                     target,
                                     target->type,
                                     target->target.alias_id,
                                     target->count_or_distance);
                        } else if (target->type == Package_Target_t::Type_e::SELF) {
                            _MESSAGE("        " "reference %p, type: %i, self, count_or_distance: %i",
                                     target,
                                     target->type,
                                     target->count_or_distance);
                        } else {
                            _MESSAGE("        " "reference %p, type: %i, union: %p, count_or_distance: %i",
                                     target,
                                     target->type,
                                     target->target.linked,
                                     target->count_or_distance);
                        }
                    } else {
                        _MESSAGE("        " "%p, vtbl offset: %p", value, (*(uintptr_t*)value) - base);
                    }
                }

                _MESSAGE("    " "data_10: %p", package_data->data_10);
                _MESSAGE("    " "value_count: %u", package_data->value_count);
                _MESSAGE("    " "marker: 0x%X", package_data->marker);
                _MESSAGE("    " "uint_1B: 0x%X", package_data->uint_1B);
                _MESSAGE("    " "bool_1C: %u", package_data->bool_1C);
                _MESSAGE("    " "pad_1D: 0x%X", package_data->pad_1D);
                _MESSAGE("    " "pad_1E: 0x%X", package_data->pad_1E);
                _MESSAGE("    " "shared_20: %p", package_data->shared_20);
                _MESSAGE("    " "shared_28: %p", package_data->shared_28);
                _MESSAGE("    " "package_template: %p", package_data->package_template);
                _MESSAGE("    " "version: %u", package_data->version);
                _MESSAGE("    " "uint_3A: 0x%X", package_data->uint_3A);
                _MESSAGE("    " "bool_3C: %u", package_data->bool_3C);
                _MESSAGE("    " "pad_3D: 0x%X", package_data->pad_3D);
                _MESSAGE("    " "pad_3E: 0x%X", package_data->pad_3E);
            }
        }
    }

    void Log_Template_Packages()
    {
        DataHandler* data_handler = Game::Data_Handler();
        for (size_t idx = 0, end = data_handler->arrPACK.count; idx < end; idx += 1) {
            Package_t* package = static_cast<Package_t*>(data_handler->arrPACK.entries[idx]);
            if (package && package->type == Package_t::Type_e::PACKAGE_TEMPLATE) {
                _MESSAGE("package: %p, form_id: 0x%08X, editor_id: %s, name: %s",
                         package,
                         package->formID,
                         package->Editor_ID(),
                         Form::Name(package));
            }
        }
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace Packages { namespace Exports {

    void Execute_Package(Selfless_t*, Package_t* package, Actor_t* actor)
    {
        return Packages::Execute_Package(package, actor);
    }

    Bool_t Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_main", Selfless_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("Execute_Package", 2, void, Execute_Package, Package_t*, Actor_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
