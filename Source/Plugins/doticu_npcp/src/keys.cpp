/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

//#define INITGUID

#pragma once

#include "skse64/GameInput.h"
#include "skse64/Hooks_DirectInput8Create.h"
#include "skse64/Hooks_Gameplay.h"
#include "skse64/PapyrusGame.h"

#include "consts.h"
#include "form.h"
#include "game.h"
#include "keys.h"
#include "object_ref.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "string2.h"
#include "ui.h"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "party/party_movee.h"
#include "party/party_followers.h"
#include "party/party_follower.h"

#include "commands.h"

namespace doticu_npcp { namespace Papyrus {

    void Keys_t::On_Load_Plugin()
    {
        Hooks_DirectInput_Commit();
    }

    const char* Keys_t::Code_To_String(Int_t code)
    {
        switch (code) {
            case KEY_INVALID: return "Invalid";
            case KEY_ESCAPE: return "Esc";
            case KEY_1: return "1";
            case KEY_2: return "2";
            case KEY_3: return "3";
            case KEY_4: return "4";
            case KEY_5: return "5";
            case KEY_6: return "6";
            case KEY_7: return "7";
            case KEY_8: return "8";
            case KEY_9: return "9";
            case KEY_0: return "0";
            case KEY_MINUS: return "-";
            case KEY_EQUALS: return "=";
            case KEY_BACKSPACE: return "Backspace";
            case KEY_TAB: return "Tab";
            case KEY_Q: return "Q";
            case KEY_W: return "W";
            case KEY_E: return "E";
            case KEY_R: return "R";
            case KEY_T: return "T";
            case KEY_Y: return "Y";
            case KEY_U: return "U";
            case KEY_I: return "I";
            case KEY_O: return "O";
            case KEY_P: return "P";
            case KEY_LEFT_BRACKET: return "[";
            case KEY_RIGHT_BRACKET: return "]";
            case KEY_ENTER: return "Enter";
            case KEY_LEFT_CONTROL: return "LCtrl";
            case KEY_A: return "A";
            case KEY_S: return "S";
            case KEY_D: return "D";
            case KEY_F: return "F";
            case KEY_G: return "G";
            case KEY_H: return "H";
            case KEY_J: return "J";
            case KEY_K: return "K";
            case KEY_L: return "L";
            case KEY_SEMICOLON: return ";";
            case KEY_APOSTROPHE: return "'";
            case KEY_TILDE: return "`";
            case KEY_LEFT_SHIFT: return "LShift";
            case KEY_BACK_SLASH: return "\\";
            case KEY_Z: return "Z";
            case KEY_X: return "X";
            case KEY_C: return "C";
            case KEY_V: return "V";
            case KEY_B: return "B";
            case KEY_N: return "N";
            case KEY_M: return "M";
            case KEY_COMMA: return ",";
            case KEY_PERIOD: return ".";
            case KEY_FORWARD_SLASH: return "/";
            case KEY_RIGHT_SHIFT: return "RShift";
            case KEY_NUM_ASTERISK: return "Num *";
            case KEY_LEFT_ALT: return "LAlt";
            case KEY_SPACEBAR: return "Spacebar";
            case KEY_CAPS_LOCK: return "Caps Lock";
            case KEY_F1: return "F1";
            case KEY_F2: return "F2";
            case KEY_F3: return "F3";
            case KEY_F4: return "F4";
            case KEY_F5: return "F5";
            case KEY_F6: return "F6";
            case KEY_F7: return "F7";
            case KEY_F8: return "F8";
            case KEY_F9: return "F9";
            case KEY_F10: return "F10";
            case KEY_NUM_LOCK: return "Num Lock";
            case KEY_SCROLL_LOCK: return "Scroll Lock";
            case KEY_NUM_7: return "Num 7";
            case KEY_NUM_8: return "Num 8";
            case KEY_NUM_9: return "Num 9";
            case KEY_NUM_MINUS: return "Num -";
            case KEY_NUM_4: return "Num 4";
            case KEY_NUM_5: return "Num 5";
            case KEY_NUM_6: return "Num 6";
            case KEY_NUM_PLUS: return "Num +";
            case KEY_NUM_1: return "Num 1";
            case KEY_NUM_2: return "Num 2";
            case KEY_NUM_3: return "Num 3";
            case KEY_NUM_0: return "Num 0";
            case KEY_NUM_PERIOD: return "Num .";
            case KEY_F11: return "F11";
            case KEY_F12: return "F12";
            case KEY_NUM_ENTER: return "Num Enter";
            case KEY_RIGHT_CONTROL: return "RCtrl";
            case KEY_NUM_FORWARD_SLASH: return "Num /";
            case KEY_RIGHT_ALT: return "RAlt";
            case KEY_PAUSE: return "Pause";
            case KEY_HOME: return "Home";
            case KEY_UP_ARROW: return "Up Arrow";
            case KEY_PAGE_UP: return "Page Up";
            case KEY_LEFT_ARROW: return "Left Arrow";
            case KEY_RIGHT_ARROW: return "Right Arrow";
            case KEY_END: return "End";
            case KEY_DOWN_ARROW: return "Down Arrow";
            case KEY_PAGE_DOWN: return "Page Down";
            case KEY_INSERT: return "Insert";
            case KEY_DELETE: return "Delete";
            case MOUSE_LEFT: return "Mouse Left";
            case MOUSE_RIGHT: return "Mouse Right";
            case MOUSE_MIDDLE: return "Mouse Middle";
            case MOUSE_3: return "Mouse 3";
            case MOUSE_4: return "Mouse 4";
            case MOUSE_5: return "Mouse 5";
            case MOUSE_6: return "Mouse 6";
            case MOUSE_7: return "Mouse 7";
            case MOUSE_WHEEL_UP: return "Mouse Wheel Up";
            case MOUSE_WHEEL_DOWN: return "Mouse Wheel Down";
            case PAD_DPAD_UP: return "Dpad Up";
            case PAD_DPAD_DOWN: return "Dpad Down";
            case PAD_DPAD_LEFT: return "Dpad Left";
            case PAD_DPAD_RIGHT: return "Dpad Right";
            case PAD_START: return "Start";
            case PAD_BACK: return "Back";
            case PAD_LEFT_THUMB: return "LThumb";
            case PAD_RIGHT_THUMB: return "RThumb";
            case PAD_LEFT_SHOULDER: return "LShoulder";
            case PAD_RIGHT_SHOULDER: return "RShoulder";
            case PAD_A: return "Button A";
            case PAD_B: return "Button B";
            case PAD_X: return "Button X";
            case PAD_Y: return "Button Y";
            case PAD_LEFT_TRIGGER: return "LTrigger";
            case PAD_RIGHT_TRIGGER: return "RTrigger";
            default: return "";
        }
    }

    // Keys_t::Mods_t

    Keys_t::Mods_t::Mods_t(Int_t mod_1, Int_t mod_2, Int_t mod_3) :
        mod_1(mod_1), mod_2(mod_2), mod_3(mod_3)
    {
    }

    Keys_t::Mods_t::Mods_t(Array_t* array)
    {
        if (array) {
            if (array->count > 0) {
                mod_1 = array->Point(0)->Int();
            }
            if (array->count > 1) {
                mod_2 = array->Point(1)->Int();
            }
            if (array->count > 2) {
                mod_3 = array->Point(2)->Int();
            }
        }
    }

    Int_t Keys_t::Mods_t::Count()
    {
        Int_t count = 0;
        if (mod_1 > KEY_INVALID) {
            count += 1;
        }
        if (mod_2 > KEY_INVALID) {
            count += 1;
        }
        if (mod_3 > KEY_INVALID) {
            count += 1;
        }
        return count;
    }

    Bool_t Keys_t::Mods_t::Has(Int_t mod)
    {
        return mod_1 == mod || mod_2 == mod || mod_3 == mod;
    }

    Bool_t Keys_t::Mods_t::Are_Pressed()
    {
        static DIHookControl& controls = DIHookControl::GetSingleton();

        if (mod_3 > KEY_INVALID) {
            return controls.IsKeyPressed(mod_1) || controls.IsKeyPressed(mod_2) || controls.IsKeyPressed(mod_3);
        } else if (mod_2 > KEY_INVALID) {
            return controls.IsKeyPressed(mod_1) || controls.IsKeyPressed(mod_2);
        } else if (mod_1 > KEY_INVALID) {
            return controls.IsKeyPressed(mod_1);
        } else {
            return true;
        }
    }

    Vector_t<Int_t> Keys_t::Mods_t::Vector()
    {
        Vector_t<Int_t> mods;

        mods.reserve(3);
        mods.push_back(mod_1);
        mods.push_back(mod_2);
        mods.push_back(mod_3);

        return mods;
    }

    String_t Keys_t::Mods_t::String()
    {
        std::string mods("");

        if (mod_1 > KEY_INVALID) {
            mods.append(Code_To_String(mod_1));
            if (mod_2 > KEY_INVALID) {
                mods.append(" + ");
                mods.append(Code_To_String(mod_2));
                if (mod_3 > KEY_INVALID) {
                    mods.append(" + ");
                    mods.append(Code_To_String(mod_3));
                }
            }
        } else {
            mods.append("???");
        }

        return mods.c_str();
    }

    Bool_t Keys_t::Mods_t::operator ==(Mods_t& rhs)
    {
        return
            mod_1 == rhs.mod_1 &&
            mod_2 == rhs.mod_2 &&
            mod_3 == rhs.mod_3;
    }

    // Keys_t::Hotkeys_t

    Keys_t::Hotkeys_t* Keys_t::Hotkeys_t::Self()
    {
        static Hotkeys_t hotkeys;
        return &hotkeys;
    }

    Keys_t::Hotkeys_t::Hotkeys_t()
    {
        names.reserve(64);
        current_values.reserve(64);
        current_mods.reserve(64);
        default_values.reserve(64);
        default_mods.reserve(64);

        #define ADD_HOTKEY(HOTKEY_, DEFAULT_VALUE_, ...)                        \
        M                                                                       \
            names.push_back(HOTKEY_());                                         \
            current_values.push_back(                                           \
                []()->Variable_t* { return Vars::HOTKEY_##_Value_Property(); }  \
            );                                                                  \
            current_mods.push_back(                                             \
                []()->Variable_t* { return Vars::HOTKEY_##_Mods_Property(); }   \
            );                                                                  \
            default_values.push_back(DEFAULT_VALUE_);                           \
            default_mods.push_back(Mods_t(__VA_ARGS__));                        \
        W

        ADD_HOTKEY(G_Dialogue_Menu, KEY_G, KEY_LEFT_CONTROL);

        ADD_HOTKEY(N_Toggle_Member, KEY_NUM_PLUS, KEY_LEFT_CONTROL);
        ADD_HOTKEY(N_Toggle_Move, KEY_LEFT_ALT, KEY_LEFT_CONTROL);
        ADD_HOTKEY(N_Move_Farther, KEY_UP_ARROW);
        ADD_HOTKEY(N_Move_Nearer, KEY_DOWN_ARROW);
        ADD_HOTKEY(N_Move_Rotate_Left, KEY_LEFT_ARROW);
        ADD_HOTKEY(N_Move_Rotate_Right, KEY_RIGHT_ARROW);
        ADD_HOTKEY(N_Has_Base, KEY_RIGHT_SHIFT, KEY_LEFT_CONTROL);
        ADD_HOTKEY(N_Count_Base, KEY_RIGHT_SHIFT, KEY_LEFT_ALT);
        ADD_HOTKEY(N_Has_Head, KEY_ENTER, KEY_LEFT_CONTROL);
        ADD_HOTKEY(N_Count_Heads, KEY_ENTER, KEY_LEFT_ALT);

        ADD_HOTKEY(M_Toggle_Clone, KEY_NUM_ENTER, KEY_LEFT_CONTROL);
        ADD_HOTKEY(M_Toggle_Settler, KEY_NUM_0, KEY_LEFT_CONTROL);
        ADD_HOTKEY(M_Toggle_Thrall, KEY_NUM_9, KEY_LEFT_CONTROL);
        ADD_HOTKEY(M_Toggle_Immobile, KEY_NUM_PERIOD, KEY_LEFT_CONTROL);
        ADD_HOTKEY(M_Toggle_Paralyzed, KEY_NUM_FORWARD_SLASH, KEY_LEFT_CONTROL);
        ADD_HOTKEY(M_Toggle_Follower, KEY_NUM_ASTERISK, KEY_LEFT_CONTROL);

        ADD_HOTKEY(F_Toggle_Sneak, KEY_NUM_ASTERISK, KEY_LEFT_ALT);
        ADD_HOTKEY(F_Toggle_Saddler, KEY_NUM_FORWARD_SLASH, KEY_LEFT_ALT);

        ADD_HOTKEY(MS_Toggle_Display, KEY_BACK_SLASH, KEY_LEFT_CONTROL);
        ADD_HOTKEY(MS_Display_Previous, KEY_LEFT_BRACKET, KEY_LEFT_CONTROL);
        ADD_HOTKEY(MS_Display_Next, KEY_RIGHT_BRACKET, KEY_LEFT_CONTROL);

        ADD_HOTKEY(FS_Summon_All, KEY_FORWARD_SLASH, KEY_LEFT_CONTROL);
        ADD_HOTKEY(FS_Summon_Mobile, KEY_FORWARD_SLASH);
        ADD_HOTKEY(FS_Summon_Immobile, KEY_FORWARD_SLASH, KEY_LEFT_ALT);
        ADD_HOTKEY(FS_Settle, KEY_0, KEY_LEFT_CONTROL);
        ADD_HOTKEY(FS_Unsettle, KEY_0, KEY_LEFT_ALT);
        ADD_HOTKEY(FS_Mobilize, KEY_EQUALS, KEY_LEFT_CONTROL);
        ADD_HOTKEY(FS_Immobilize, KEY_EQUALS, KEY_LEFT_ALT);
        ADD_HOTKEY(FS_Sneak, KEY_MINUS, KEY_LEFT_CONTROL);
        ADD_HOTKEY(FS_Unsneak, KEY_MINUS, KEY_LEFT_ALT);
        ADD_HOTKEY(FS_Saddle, KEY_H, KEY_LEFT_CONTROL);
        ADD_HOTKEY(FS_Unsaddle, KEY_H, KEY_LEFT_ALT);
        ADD_HOTKEY(FS_Resurrect, KEY_BACKSPACE, KEY_LEFT_CONTROL);

        #undef ADD_HOTKEY
    }

    Int_t Keys_t::Hotkeys_t::Count()
    {
        Int_t count = static_cast<Int_t>(names.size());
        NPCP_ASSERT(count > -1);
        return count;
    }

    Int_t Keys_t::Hotkeys_t::Index_Of(String_t hotkey)
    {
        for (Int_t idx = 0, count = Count(); idx < count; idx += 1) {
            if (String2::Is_Same_Caseless(names[idx], hotkey)) {
                return idx;
            }
        }
        return -1;
    }

    Bool_t Keys_t::Hotkeys_t::Has(String_t hotkey)
    {
        return Index_Of(hotkey) > -1;
    }

    String_t Keys_t::Hotkeys_t::Hotkey(Int_t idx)
    {
        NPCP_ASSERT(idx > -1 && idx < Count());
        return names[idx];
    }

    Int_t Keys_t::Hotkeys_t::Default_Value(String_t key)
    {
        Int_t idx = Index_Of(key);
        NPCP_ASSERT(idx > -1);
        return default_values[idx];
    }

    Int_t Keys_t::Hotkeys_t::Current_Value(String_t key)
    {
        Int_t idx = Index_Of(key);
        NPCP_ASSERT(idx > -1);
        return current_values[idx]()->Int();
    }

    Int_t Keys_t::Hotkeys_t::Current_Value(Int_t idx)
    {
        NPCP_ASSERT(idx > -1 && idx < Count());
        return current_values[idx]()->Int();
    }

    Keys_t::Mods_t Keys_t::Hotkeys_t::Default_Mods(String_t key)
    {
        Int_t idx = Index_Of(key);
        NPCP_ASSERT(idx > -1);
        return default_mods[idx];
    }

    Keys_t::Mods_t Keys_t::Hotkeys_t::Current_Mods(String_t key)
    {
        Int_t idx = Index_Of(key);
        NPCP_ASSERT(idx > -1);
        return Mods_t(current_mods[idx]()->Array());
    }

    Keys_t::Mods_t Keys_t::Hotkeys_t::Current_Mods(Int_t idx)
    {
        NPCP_ASSERT(idx > -1 && idx < Count());
        return Mods_t(current_mods[idx]()->Array());
    }

    // Keys_t

    String_t Keys_t::Class_Name() { DEFINE_STRING("doticu_npcp_keys"); }

    Class_Info_t* Keys_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Keys_t* Keys_t::Self()
    {
        return static_cast<Keys_t*>(Consts::Control_Quest());
    }

    Object_t* Keys_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    // Global
    String_t Keys_t::G_Dialogue_Menu() { DEFINE_STRING("Global: Open Dialogue Menu"); }

    // NPC
    String_t Keys_t::N_Toggle_Member() { DEFINE_STRING("NPC: Toggle Member"); }
    String_t Keys_t::N_Toggle_Move() { DEFINE_STRING("NPC: Toggle Move"); }
    String_t Keys_t::N_Move_Farther() { DEFINE_STRING("NPC: Move Farther"); }
    String_t Keys_t::N_Move_Nearer() { DEFINE_STRING("NPC: Move Nearer"); }
    String_t Keys_t::N_Move_Rotate_Left() { DEFINE_STRING("NPC: Rotate Left"); }
    String_t Keys_t::N_Move_Rotate_Right() { DEFINE_STRING("NPC: Rotate Right"); }
    String_t Keys_t::N_Has_Base() { DEFINE_STRING("NPC: Has Base"); }
    String_t Keys_t::N_Count_Base() { DEFINE_STRING("NPC: Count Base"); }
    String_t Keys_t::N_Has_Head() { DEFINE_STRING("NPC: Has Head"); }
    String_t Keys_t::N_Count_Heads() { DEFINE_STRING("NPC: Count Heads"); }

    // Member
    String_t Keys_t::M_Toggle_Clone() { DEFINE_STRING("Member: Toggle Clone"); }
    String_t Keys_t::M_Toggle_Settler() { DEFINE_STRING("Member: Toggle Settler"); }
    String_t Keys_t::M_Toggle_Thrall() { DEFINE_STRING("Member: Toggle Thrall"); }
    String_t Keys_t::M_Toggle_Immobile() { DEFINE_STRING("Member: Toggle Immobile"); }
    String_t Keys_t::M_Toggle_Paralyzed() { DEFINE_STRING("Member: Toggle Paralyzed"); }
    String_t Keys_t::M_Toggle_Follower() { DEFINE_STRING("Member: Toggle Follower"); }

    // Follower
    String_t Keys_t::F_Toggle_Sneak() { DEFINE_STRING("Follower: Toggle Sneak"); }
    String_t Keys_t::F_Toggle_Saddler() { DEFINE_STRING("Follower: Toggle Saddler"); }

    // Members
    String_t Keys_t::MS_Toggle_Display() { DEFINE_STRING("Members: Toggle Display"); }
    String_t Keys_t::MS_Display_Previous() { DEFINE_STRING("Members: Display Previous"); }
    String_t Keys_t::MS_Display_Next() { DEFINE_STRING("Members: Display Next"); }

    // Followers
    String_t Keys_t::FS_Summon_All() { DEFINE_STRING("Followers: Summon All"); }
    String_t Keys_t::FS_Summon_Mobile() { DEFINE_STRING("Followers: Summon Mobile"); }
    String_t Keys_t::FS_Summon_Immobile() { DEFINE_STRING("Followers: Summon Immobile"); }
    String_t Keys_t::FS_Settle() { DEFINE_STRING("Followers: Settle"); }
    String_t Keys_t::FS_Unsettle() { DEFINE_STRING("Followers: Unsettle"); }
    String_t Keys_t::FS_Mobilize() { DEFINE_STRING("Followers: Mobilize"); }
    String_t Keys_t::FS_Immobilize() { DEFINE_STRING("Followers: Immobilize"); }
    String_t Keys_t::FS_Sneak() { DEFINE_STRING("Followers: Sneak"); }
    String_t Keys_t::FS_Unsneak() { DEFINE_STRING("Followers: Unsneak"); }
    String_t Keys_t::FS_Saddle() { DEFINE_STRING("Followers: Saddle"); }
    String_t Keys_t::FS_Unsaddle() { DEFINE_STRING("Followers: Unsaddle"); }
    String_t Keys_t::FS_Resurrect() { DEFINE_STRING("Followers: Resurrect"); }

    Variable_t* Keys_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Keys_t::Pressed_Hotkey_Variable() { DEFINE_VARIABLE("p_pressed_hotkey"); }

    Int_t Keys_t::Default_Value(String_t hotkey)
    {
        return Hotkeys_t::Self()->Default_Value(hotkey);
    }

    Int_t Keys_t::Current_Value(String_t hotkey)
    {
        return Hotkeys_t::Self()->Current_Value(hotkey);
    }

    Vector_t<Int_t> Keys_t::Default_Mods(String_t hotkey)
    {
        return Hotkeys_t::Self()->Default_Mods(hotkey).Vector();
    }

    Vector_t<Int_t> Keys_t::Current_Mods(String_t hotkey)
    {
        return Hotkeys_t::Self()->Current_Mods(hotkey).Vector();
    }

    String_t Keys_t::Default_Mods_String(String_t hotkey)
    {
        return Hotkeys_t::Self()->Default_Mods(hotkey).String();
    }

    String_t Keys_t::Current_Mods_String(String_t hotkey)
    {
        return Hotkeys_t::Self()->Current_Mods(hotkey).String();
    }

    String_t Keys_t::Conflicting_Hotkey(String_t hotkey, Int_t value, Int_t mod_1, Int_t mod_2, Int_t mod_3)
    {
        Hotkeys_t* hotkeys = Hotkeys_t::Self();
        Mods_t mods = Mods_t(mod_1, mod_2, mod_3);
        for (Int_t idx = 0, count = hotkeys->Count(); idx < count; idx += 1) {
            String_t current_key = hotkeys->Hotkey(idx);
            if (!String2::Is_Same_Caseless(current_key, hotkey)) {
                Int_t current_value = hotkeys->Current_Value(idx);
                if (current_value > KEY_INVALID && current_value == value) {
                    Mods_t current_mods = hotkeys->Current_Mods(idx);
                    if (current_mods == mods) {
                        return current_key;
                    }
                }
            }
        }
        return "";
    }

    String_t Keys_t::Pressed_Hotkey(Int_t value)
    {
        Hotkeys_t* hotkeys = Hotkeys_t::Self();

        String_t chosen_hotkey = "";
        Int_t chosen_mods_count = -1;
        for (Int_t idx = 0, count = hotkeys->Count(); idx < count; idx += 1) {
            String_t current_hotkey = hotkeys->Hotkey(idx);
            Int_t current_value = hotkeys->Current_Value(idx);
            if (current_value == value) {
                Mods_t current_mods = hotkeys->Current_Mods(idx);
                Int_t current_mods_count = current_mods.Count();
                if (current_mods_count > chosen_mods_count && current_mods.Are_Pressed()) {
                    chosen_hotkey = current_hotkey;
                    chosen_mods_count = current_mods_count;
                }
            }
        }

        return chosen_hotkey;
    }

    void Keys_t::Register()
    {
        Unregister();

        auto Try_To_Register = [&](Int_t hotkey_value)->void
        {
            if (hotkey_value > Keys_t::KEY_INVALID) {
                Form::Register_Key(this, hotkey_value);
            }
        };

        // General
        Try_To_Register(Vars::G_Dialogue_Menu_Value());

        // NPC
        Try_To_Register(Vars::N_Toggle_Member_Value());
        Try_To_Register(Vars::N_Toggle_Move_Value());
        Try_To_Register(Vars::N_Has_Base_Value());
        Try_To_Register(Vars::N_Count_Base_Value());
        Try_To_Register(Vars::N_Has_Head_Value());
        Try_To_Register(Vars::N_Count_Heads_Value());

        // Member
        Try_To_Register(Vars::M_Toggle_Clone_Value());
        Try_To_Register(Vars::M_Toggle_Immobile_Value());
        Try_To_Register(Vars::M_Toggle_Settler_Value());
        Try_To_Register(Vars::M_Toggle_Thrall_Value());
        Try_To_Register(Vars::M_Toggle_Paralyzed_Value());
        Try_To_Register(Vars::M_Toggle_Follower_Value());

        // Follower
        Try_To_Register(Vars::F_Toggle_Sneak_Value());
        Try_To_Register(Vars::F_Toggle_Saddler_Value());

        // Members
        Try_To_Register(Vars::MS_Toggle_Display_Value());
        Try_To_Register(Vars::MS_Display_Previous_Value());
        Try_To_Register(Vars::MS_Display_Next_Value());

        // Followers
        Try_To_Register(Vars::FS_Summon_All_Value());
        Try_To_Register(Vars::FS_Summon_Mobile_Value());
        Try_To_Register(Vars::FS_Summon_Immobile_Value());
        Try_To_Register(Vars::FS_Mobilize_Value());
        Try_To_Register(Vars::FS_Immobilize_Value());
        Try_To_Register(Vars::FS_Settle_Value());
        Try_To_Register(Vars::FS_Unsettle_Value());
        Try_To_Register(Vars::FS_Sneak_Value());
        Try_To_Register(Vars::FS_Unsneak_Value());
        Try_To_Register(Vars::FS_Saddle_Value());
        Try_To_Register(Vars::FS_Unsaddle_Value());
        Try_To_Register(Vars::FS_Resurrect_Value());

        Party::Movee_t::Self()->Register();
    }

    void Keys_t::Unregister()
    {
        Form::Unregister_Keys(this);
    }

    void Keys_t::Actor_In_Crosshair(Bool_t allow_follower_horse, void(*callback)(Actor_t*))
    {
        using namespace Papyrus::Party;

        struct VCallback : Virtual_Callback_t {
            Bool_t allow_follower_horse;
            void(*callback)(Actor_t*);
            VCallback(Bool_t allow_follower_horse, void(*callback)(Actor_t*)) :
                allow_follower_horse(allow_follower_horse), callback(callback)
            {
            }
            void operator()(Variable_t* result)
            {
                if (result && result->Has_Object()) {
                    Reference_t* ref = result->Reference();
                    if (ref && ref->formType == kFormType_Character) {
                        Actor_t* actor = static_cast<Actor_t*>(ref);
                        if (allow_follower_horse) {
                            callback(actor);
                        } else {
                            Follower_t* follower = Followers_t::Self()->From_Horse_Actor(actor);
                            if (follower) {
                                callback(follower->Actor());
                            } else {
                                callback(actor);
                            }
                        }
                    } else {
                        callback(nullptr);
                    }
                } else {
                    callback(nullptr);
                }
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(allow_follower_horse, callback);
        Object_Ref::Current_Crosshair_Reference(&vcallback);
    }

    void Keys_t::On_Key_Down(Int_t value)
    {
        struct Callback : public Virtual_Callback_t {
            Keys_t* self;
            Int_t value;
            Callback(Keys_t* self, Int_t value) :
                self(self), value(value)
            {
            }
            void operator()(Variable_t* result)
            {
                self->Pressed_Hotkey_Variable()->String(self->Pressed_Hotkey(value));
            }
        };
        Virtual_Callback_i* callback = new Callback(this, value);
        Object_Ref::Can_Use_Keys(&callback);
    }

    void Keys_t::On_Key_Up(Int_t key_code, Float_t time_held)
    {
        using namespace Modules::Control;

        struct Callback : public Virtual_Callback_t {
            Keys_t* self;
            Int_t key_code;
            Float_t time_held;
            Callback(Keys_t* self, Int_t key_code, Float_t time_held) :
                self(self), key_code(key_code), time_held(time_held)
            {
            }
            void operator()(Variable_t* result)
            {
                if (result && result->Bool()) {
                    self->Process_On_Key_Up(key_code, time_held);
                }
            }
        };
        Virtual_Callback_i* callback = new Callback(this, key_code, time_held);
        Object_Ref::Can_Use_Keys(&callback);
    }

    void Keys_t::Process_On_Key_Up(Int_t key_code, Float_t time_held)
    {
        using namespace Modules::Control;

        String_t pressed_hotkey = Pressed_Hotkey_Variable()->String();
        if (pressed_hotkey && pressed_hotkey.data && pressed_hotkey.data[0]) {
            Pressed_Hotkey_Variable()->String("");

            #define IS(HOTKEY_) String2::Is_Same_Caseless(pressed_hotkey, HOTKEY_())

            if (IS(G_Dialogue_Menu)) { // General
                Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(), "doticu_npcp_actors", "Create_Menu");

            } else if (IS(N_Toggle_Member)) { // NPC
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Member(actor);
                                   });
            } else if (IS(N_Toggle_Move)) {
                Actor_In_Crosshair(true, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Move(actor);
                                   });
            } else if (IS(N_Has_Base)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Has_Base(actor);
                                   });
            } else if (IS(N_Count_Base)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Count_Base(actor);
                                   });
            } else if (IS(N_Has_Head)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Has_Head(actor);
                                   });
            } else if (IS(N_Count_Heads)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Count_Heads(actor);
                                   });

            } else if (IS(M_Toggle_Clone)) { // Member
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Clone(actor);
                                   });
            } else if (IS(M_Toggle_Settler)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Settler(actor);
                                   });
            } else if (IS(M_Toggle_Thrall)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Thrall(actor);
                                   });
            } else if (IS(M_Toggle_Immobile)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Immobile(actor);
                                   });
            } else if (IS(M_Toggle_Paralyzed)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Paralyzed(actor);
                                   });
            } else if (IS(M_Toggle_Follower)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Follower(actor);
                                   });

            } else if (IS(F_Toggle_Sneak)) { // Follower
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Sneak(actor);
                                   });
            } else if (IS(F_Toggle_Saddler)) {
                Actor_In_Crosshair(false, [](Actor_t* actor)->void
                                   {
                                       Commands_t::Self()->Toggle_Saddler(actor);
                                   });

            } else if (IS(MS_Toggle_Display)) { // Members
                Commands_t::Self()->Members_Toggle_Display();
            } else if (IS(MS_Display_Previous)) {
                Commands_t::Self()->Members_Display_Previous();
            } else if (IS(MS_Display_Next)) {
                Commands_t::Self()->Members_Display_Next();

            } else if (IS(FS_Summon_All)) { // Followers
                Commands_t::Self()->Followers_Summon_All();
            } else if (IS(FS_Summon_Mobile)) {
                Commands_t::Self()->Followers_Summon_Mobile();
            } else if (IS(FS_Summon_Immobile)) {
                Commands_t::Self()->Followers_Summon_Immobile();
            } else if (IS(FS_Settle)) {
                Commands_t::Self()->Followers_Settle();
            } else if (IS(FS_Unsettle)) {
                Commands_t::Self()->Followers_Unsettle();
            } else if (IS(FS_Mobilize)) {
                Commands_t::Self()->Followers_Mobilize();
            } else if (IS(FS_Immobilize)) {
                Commands_t::Self()->Followers_Immobilize();
            } else if (IS(FS_Sneak)) {
                Commands_t::Self()->Followers_Sneak();
            } else if (IS(FS_Unsneak)) {
                Commands_t::Self()->Followers_Unsneak();
            } else if (IS(FS_Saddle)) {
                Commands_t::Self()->Followers_Saddle();
            } else if (IS(FS_Unsaddle)) {
                Commands_t::Self()->Followers_Unsaddle();
            } else if (IS(FS_Resurrect)) {
                Commands_t::Self()->Followers_Resurrect();
            }

            #undef IS
        }
    }

    void Keys_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Keys_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("Register", 0, void, Register);
        METHOD("Unregister", 0, void, Unregister);

        METHOD("Default_Value", 1, Int_t, Default_Value, String_t);
        METHOD("Current_Value", 1, Int_t, Current_Value, String_t);
        METHOD("Default_Mods", 1, Vector_t<Int_t>, Default_Mods, String_t);
        METHOD("Current_Mods", 1, Vector_t<Int_t>, Current_Mods, String_t);

        METHOD("Default_Mods_To_String", 1, String_t, Default_Mods_String, String_t);
        METHOD("Current_Mods_To_String", 1, String_t, Current_Mods_String, String_t);

        METHOD("Conflicting_Hotkey", 5, String_t, Conflicting_Hotkey, String_t, Int_t, Int_t, Int_t, Int_t);
        METHOD("Pressed_Hotkey", 1, String_t, Pressed_Hotkey, Int_t);

        METHOD("OnKeyDown", 1, void, On_Key_Down, Int_t);
        METHOD("OnKeyUp", 2, void, On_Key_Up, Int_t, Float_t);

        #undef METHOD
    }

}}
