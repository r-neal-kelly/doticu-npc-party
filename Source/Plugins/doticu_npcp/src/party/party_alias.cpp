/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusEvents.h"

#include "papyrus.inl"
#include "quest.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    Int_t Alias_t::ID()
    {
        return id;
    }

    Actor_t* Alias_t::Actor()
    {
        return Quest::Alias_Actor(quest, id);
    }

    Bool_t Alias_t::Is_Filled()
    {
        return Quest::Is_Alias_Filled(quest, id);
    }

    Bool_t Alias_t::Is_Unfilled()
    {
        return !Quest::Is_Alias_Filled(quest, id);
    }

    void Alias_t::Fill(Actor_t* actor, Virtual_Callback_i** callback)
    {
        struct Arguments : public Virtual_Arguments_t {
        public:
            Reference_t* ref;
            Arguments(Reference_t* ref) :
                ref(ref)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(ref);

                return true;
            }
        } arguments(actor);

        Virtual_Machine_t::Self()->Call_Method(this, "ReferenceAlias", "ForceRefTo", &arguments, callback);
    }

    void Alias_t::Unfill(Virtual_Callback_i** callback)
    {
        Virtual_Machine_t::Self()->Call_Method(this, "ReferenceAlias", "Clear", nullptr, callback);
    }

    void Alias_t::Queue(Callback_t<>* user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<>;

        struct VCallback : public Virtual_Callback_t {
            UCallback_t* user_callback;
            VCallback(UCallback_t* user_callback) :
                user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                user_callback->operator()();
                delete user_callback;
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(user_callback);
        Virtual_Machine_t::Self()->Call_Method(this, "Alias", "GetOwningQuest", nullptr, &vcallback);
    }

    void Alias_t::Register_Key(Int_t key_code)
    {
        UInt32 u_key_code = key_code;
        g_inputKeyEventRegs.Register(u_key_code, Alias_t::kTypeID, this);
    }

    void Alias_t::Unregister_Key(Int_t key_code)
    {
        UInt32 u_key_code = key_code;
        g_inputKeyEventRegs.Unregister(u_key_code, Alias_t::kTypeID, this);
    }

    void Alias_t::Unregister_Keys()
    {
        g_inputKeyEventRegs.UnregisterAll(Alias_t::kTypeID, this);
    }

    void Alias_t::Register_Control(String_t control)
    {
        g_inputControlEventRegs.Register(control, Alias_t::kTypeID, this);
    }

    void Alias_t::Unregister_Control(String_t control)
    {
        g_inputControlEventRegs.Unregister(control, Alias_t::kTypeID, this);
    }

    void Alias_t::Unregister_Controls()
    {
        g_inputControlEventRegs.UnregisterAll(Alias_t::kTypeID, this);
    }

    void Alias_t::Register_Action(Int_t action_code)
    {
        UInt32 u_action_code = action_code;
        g_actionEventRegs.Register(u_action_code, Alias_t::kTypeID, this);
    }

    void Alias_t::Unregister_Action(Int_t action_code)
    {
        UInt32 u_action_code = action_code;
        g_actionEventRegs.Unregister(u_action_code, Alias_t::kTypeID, this);
    }

    void Alias_t::Unregister_Actions()
    {
        g_actionEventRegs.UnregisterAll(Alias_t::kTypeID, this);
    }

    void Alias_t::Register_For_Crosshair_Change(Virtual_Callback_i* vcallback)
    {
        Virtual_Machine_t::Self()->Call_Method(
            this,
            "Alias",
            "RegisterForCrosshairRef",
            nullptr,
            vcallback ? &vcallback : nullptr
        );
    }

    void Alias_t::Unregister_For_Crosshair_Change(Virtual_Callback_i* vcallback)
    {
        Virtual_Machine_t::Self()->Call_Method(
            this,
            "Alias",
            "UnregisterForCrosshairRef",
            nullptr,
            vcallback ? &vcallback : nullptr
        );
    }

    void Alias_t::Register_Menu(String_t menu_name, Virtual_Callback_i* vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            String_t menu_name;
            Arguments(String_t menu_name) :
                menu_name(menu_name)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->String(menu_name);
                return true;
            }
        } arguments(menu_name);
        Virtual_Machine_t::Self()->Call_Method(
            this,
            "Alias",
            "RegisterForMenu",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    void Alias_t::Unregister_Menus(Virtual_Callback_i* vcallback)
    {
        Virtual_Machine_t::Self()->Call_Method(
            this,
            "Alias",
            "UnregisterForAllMenus",
            nullptr,
            vcallback ? &vcallback : nullptr
        );
    }

}}}
