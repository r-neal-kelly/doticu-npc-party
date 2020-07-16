/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameInput.h"
#include "skse64/Hooks_DirectInput8Create.h"

#include "consts.h"
#include "game.h"
#include "keys.h"
#include "papyrus.h"
#include "string2.h"
#include "utils.h"
#include "vars.h"
#include "vector.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Keys {

    class Key_System_t
    {
    public:
        class Mods
        {
        public:
            Int_t mod_1 = -1;
            Int_t mod_2 = -1;
            Int_t mod_3 = -1;

            Mods(Int_t mod_1 = -1, Int_t mod_2 = -1, Int_t mod_3 = -1) :
                mod_1(mod_1), mod_2(mod_2), mod_3(mod_3)
            {
            }

            Mods(VMArray<Int_t> mods)
            {
                u64 mods_size = mods.Length();
                if (mods_size > 0) {
                    mods.Get(&mod_1, 0);
                }
                if (mods_size > 1) {
                    mods.Get(&mod_2, 1);
                }
                if (mods_size > 2) {
                    mods.Get(&mod_3, 2);
                }
            }

            Mods(String_t mods_variable_name)
            {
                Variable_t* variable = Vars::Property(mods_variable_name);
                if (variable && variable->type.Is_Int_Array() && variable->data.arr) {
                    Array_t* arr = variable->data.arr;
                    Variable_t* variables = variable->data.arr->Variables();
                    if (arr->count > 0) {
                        mod_1 = variables[0].Int();
                    }
                    if (arr->count > 1) {
                        mod_2 = variables[1].Int();
                    }
                    if (arr->count > 2) {
                        mod_3 = variables[2].Int();
                    }
                }
            }

            Vector_t<Int_t> Vector()
            {
                Vector_t<Int_t> mods;

                mods.reserve(3);
                mods.push_back(mod_1);
                mods.push_back(mod_2);
                mods.push_back(mod_3);

                return mods;
            }

            String_t String()
            {
                std::string mods("");

                if (mod_1 > 0) {
                    mods.append(Key_To_String(mod_1));
                    if (mod_2 > 0) {
                        mods.append(" + ");
                        mods.append(Key_To_String(mod_2));
                        if (mod_3 > 0) {
                            mods.append(" + ");
                            mods.append(Key_To_String(mod_3));
                        }
                    }
                } else {
                    mods.append("???");
                }
                
                return String_t(mods.c_str());
            }

            bool operator ==(Mods& rhs)
            {
                return
                    mod_1 == rhs.mod_1 &&
                    mod_2 == rhs.mod_2 &&
                    mod_3 == rhs.mod_3;
            }

            bool Has(Int_t mod)
            {
                return mod == mod_1 || mod == mod_2 || mod == mod_3;
            }

            size_t Size()
            {
                size_t count = 0;
                if (mod_1 > 0) {
                    count += 1;
                }
                if (mod_2 > 0) {
                    count += 1;
                }
                if (mod_3 > 0) {
                    count += 1;
                }
                return count;
            }
        };

        std::vector<String_t> keys;
        std::vector<String_t> var_names;
        std::vector<String_t> var_mods;
        std::vector<Int_t> defaults;
        std::vector<Mods> default_mods;

        Key_System_t()
        {
            keys.reserve(64);
            var_names.reserve(64);
            var_mods.reserve(64);
            defaults.reserve(64);
            default_mods.reserve(64);

            #define KEY(NAME_, VAR_NAME_, DEFAULT_, ...)    \
            M                                               \
                keys.push_back(NAME_);                      \
                var_names.push_back(VAR_NAME_);             \
                var_mods.push_back(VAR_NAME_ "_mods");      \
                defaults.push_back(DEFAULT_);               \
                default_mods.push_back(Mods(__VA_ARGS__));  \
            W

            KEY("Global: Open Dialogue Menu",   "key_g_dialogue_menu",      KEY_G,                  KEY_LEFT_CONTROL);

            KEY("NPC: Toggle Member",           "key_n_toggle_member",      KEY_NUM_PLUS,           KEY_LEFT_CONTROL);
            KEY("NPC: Toggle Move",             "key_n_toggle_move",        KEY_LEFT_ALT,           KEY_LEFT_CONTROL);
            KEY("NPC: Move Farther",            "key_n_move_farther",       KEY_UP_ARROW);
            KEY("NPC: Move Nearer",             "key_n_move_nearer",        KEY_DOWN_ARROW);
            KEY("NPC: Rotate Left",             "key_n_move_rotate_left",   KEY_LEFT_ARROW);
            KEY("NPC: Rotate Right",            "key_n_move_rotate_right",  KEY_RIGHT_ARROW);
            KEY("NPC: Has Base",                "key_n_has_base",           KEY_RIGHT_SHIFT,        KEY_LEFT_CONTROL);
            KEY("NPC: Count Base",              "key_n_count_base",         KEY_RIGHT_SHIFT,        KEY_LEFT_ALT);
            KEY("NPC: Has Head",                "key_n_has_head",           KEY_ENTER,              KEY_LEFT_CONTROL);
            KEY("NPC: Count Heads",             "key_n_count_heads",        KEY_ENTER,              KEY_LEFT_ALT);

            KEY("Member: Toggle Clone",         "key_m_toggle_clone",       KEY_NUM_ENTER,          KEY_LEFT_CONTROL);
            KEY("Member: Toggle Settler",       "key_m_toggle_settler",     KEY_NUM_0,              KEY_LEFT_CONTROL);
            KEY("Member: Toggle Thrall",        "key_m_toggle_thrall",      KEY_NUM_9,              KEY_LEFT_CONTROL);
            KEY("Member: Toggle Immobile",      "key_m_toggle_immobile",    KEY_NUM_PERIOD,         KEY_LEFT_CONTROL);
            KEY("Member: Toggle Paralyzed",     "key_m_toggle_paralyzed",   KEY_NUM_FORWARD_SLASH,  KEY_LEFT_CONTROL);
            KEY("Member: Toggle Follower",      "key_m_toggle_follower",    KEY_NUM_ASTERISK,       KEY_LEFT_CONTROL);

            KEY("Follower: Toggle Sneak",       "key_f_toggle_sneak",       KEY_NUM_ASTERISK,       KEY_LEFT_ALT);
            KEY("Follower: Toggle Saddler",     "key_f_toggle_saddler",     KEY_NUM_FORWARD_SLASH,  KEY_LEFT_ALT);

            KEY("Members: Toggle Display",      "key_ms_toggle_display",    KEY_BACK_SLASH,         KEY_LEFT_CONTROL);
            KEY("Members: Display Previous",    "key_ms_display_previous",  KEY_LEFT_BRACKET,       KEY_LEFT_CONTROL);
            KEY("Members: Display Next",        "key_ms_display_next",      KEY_RIGHT_BRACKET,      KEY_LEFT_CONTROL);

            KEY("Followers: Summon All",        "key_fs_summon_all",        KEY_FORWARD_SLASH,      KEY_LEFT_CONTROL);
            KEY("Followers: Summon Mobile",     "key_fs_summon_mobile",     KEY_FORWARD_SLASH);
            KEY("Followers: Summon Immobile",   "key_fs_summon_immobile",   KEY_FORWARD_SLASH,      KEY_LEFT_ALT);
            KEY("Followers: Settle",            "key_fs_settle",            KEY_0,                  KEY_LEFT_CONTROL);
            KEY("Followers: Unsettle",          "key_fs_unsettle",          KEY_0,                  KEY_LEFT_ALT);
            KEY("Followers: Mobilize",          "key_fs_mobilize",          KEY_EQUALS,             KEY_LEFT_CONTROL);
            KEY("Followers: Immobilize",        "key_fs_immobilize",        KEY_EQUALS,             KEY_LEFT_ALT);
            KEY("Followers: Sneak",             "key_fs_sneak",             KEY_MINUS,              KEY_LEFT_CONTROL);
            KEY("Followers: Unsneak",           "key_fs_unsneak",           KEY_MINUS,              KEY_LEFT_ALT);
            KEY("Followers: Saddle",            "key_fs_saddle",            KEY_H,                  KEY_LEFT_CONTROL);
            KEY("Followers: Unsaddle",          "key_fs_unsaddle",          KEY_H,                  KEY_LEFT_ALT);
            KEY("Followers: Resurrect",         "key_fs_resurrect",         KEY_BACKSPACE,          KEY_LEFT_CONTROL);

            #undef KEY
        }

        s64 Index_Of(String_t key)
        {
            for (u64 idx = 0, size = keys.size(); idx < size; idx += 1) {
                if (String2::Is_Same_Caseless(keys[idx], key)) {
                    return idx;
                }
            }

            return -1;
        }

        String_t Hotkey(idx_t idx)
        {
            if (idx > -1 && idx < Size()) {
                return keys[idx];
            } else {
                return "";
            }
        }

        Int_t Default_Value(String_t key)
        {
            s64 idx = Index_Of(key);
            if (idx > -1) {
                return defaults[idx];
            } else {
                return KEY_INVALID;
            }
        }

        Int_t Current_Value(String_t key)
        {
            s64 idx = Index_Of(key);
            if (idx > -1) {
                Variable_t* variable = Vars::Property(var_names[idx]);
                if (variable && variable->type.Unmangled() == Type_t::INT) {
                    return variable->data.i;
                } else {
                    return KEY_INVALID;
                }
            } else {
                return KEY_INVALID;
            }
        }

        Int_t Current_Value(idx_t idx)
        {
            if (idx > -1 && idx < Size()) {
                Variable_t* variable = Vars::Property(var_names[idx]);
                if (variable && variable->type.Unmangled() == Type_t::INT) {
                    return variable->data.i;
                } else {
                    return -1;
                }
            } else {
                return KEY_INVALID;
            }
        }

        Mods Default_Mods(String_t key)
        {
            s64 idx = Index_Of(key);
            if (idx > -1) {
                return default_mods[idx];
            } else {
                return Mods();
            }
        }

        Mods Current_Mods(String_t key)
        {
            s64 idx = Index_Of(key);
            if (idx > -1) {
                return Mods(var_mods[idx]);
            } else {
                return Mods();
            }
        }

        Mods Current_Mods(idx_t idx)
        {
            if (idx > -1 && idx < Size()) {
                return Mods(var_mods[idx]);
            } else {
                return Mods();
            }
        }

        u64 Size()
        {
            return keys.size();
        }
    };

    static Key_System_t& Key_System()
    {
        static Key_System_t key_system;
        return key_system;
    }

    const char* Key_To_String(Int_t key)
    {
        switch (key) {
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

    Keys_t* Self()
    {
        static Keys_t* keys;
        return keys ? keys : keys = (Keys_t*)Game::NPCP_Form(Consts::QUEST_CONTROL);
    }

    Int_t Default_Value(Keys_t* keys, String_t key)
    {
        return Key_System().Default_Value(key);
    }

    Int_t Current_Value(Keys_t* keys, String_t key)
    {
        return Key_System().Current_Value(key);
    }

    Vector_t<Int_t> Default_Mods(Keys_t* keys, String_t key)
    {
        return Key_System().Default_Mods(key).Vector();
    }

    Vector_t<Int_t> Current_Mods(Keys_t* keys, String_t key)
    {
        return Key_System().Current_Mods(key).Vector();
    }

    String_t Default_Mods_To_String(Keys_t* keys, String_t key)
    {
        return Key_System().Default_Mods(key).String();
    }

    String_t Current_Mods_To_String(Keys_t* keys, String_t key)
    {
        return Key_System().Current_Mods(key).String();
    }

    String_t Conflicting_Hotkey(Keys_t* keys, String_t key, Int_t value, Int_t mod_1, Int_t mod_2, Int_t mod_3)
    {
        Key_System_t& key_system = Key_System();
        Key_System_t::Mods mods = Key_System_t::Mods(mod_1, mod_2, mod_3);

        for (idx_t idx = 0, size = key_system.Size(); idx < size; idx += 1) {
            String_t current_key = key_system.Hotkey(idx);
            if (!String2::Is_Same_Caseless(current_key, key)) {
                Int_t current_value = key_system.Current_Value(idx);
                if (current_value > 0 && current_value == value) {
                    Key_System_t::Mods current_mods = key_system.Current_Mods(idx);
                    if (current_mods == mods) {
                        return current_key;
                    }
                }
            }
        }

        return "";
    }

    String_t Pressed_Hotkey(Keys_t* self, Int_t value,
                            Int_t pressed_1, Int_t pressed_2, Int_t pressed_3, Int_t pressed_4,
                            Int_t pressed_5, Int_t pressed_6, Int_t pressed_7, Int_t pressed_8)
    {
        Key_System_t& key_system = Key_System();

        std::vector<Int_t> pressed_keys;
        pressed_keys.reserve(8);
        if (pressed_1 != value) {
            pressed_keys.push_back(pressed_1);
        }
        if (pressed_2 != value) {
            pressed_keys.push_back(pressed_2);
        }
        if (pressed_3 != value) {
            pressed_keys.push_back(pressed_3);
        }
        if (pressed_4 != value) {
            pressed_keys.push_back(pressed_4);
        }
        if (pressed_5 != value) {
            pressed_keys.push_back(pressed_5);
        }
        if (pressed_6 != value) {
            pressed_keys.push_back(pressed_6);
        }
        if (pressed_7 != value) {
            pressed_keys.push_back(pressed_7);
        }
        if (pressed_8 != value) {
            pressed_keys.push_back(pressed_8);
        }
        while (pressed_keys.size() < 7) {
            pressed_keys.push_back(KEY_INVALID);
        }

        String_t chosen_hotkey = "";
        Int_t chosen_mods_size = -1;
        for (idx_t idx = 0, size = key_system.Size(); idx < size; idx += 1) {
            String_t current_hotkey = key_system.Hotkey(idx);
            Int_t current_value = key_system.Current_Value(idx);
            if (current_value == value) {
                Key_System_t::Mods current_mods = key_system.Current_Mods(idx);
                if (Vector::Has(pressed_keys, current_mods.mod_1) &&
                    Vector::Has(pressed_keys, current_mods.mod_2) &&
                    Vector::Has(pressed_keys, current_mods.mod_3)) {
                    Int_t current_mods_size = current_mods.Size();
                    if (current_mods_size > chosen_mods_size) {
                        chosen_hotkey = current_hotkey;
                        chosen_mods_size = current_mods_size;
                    }
                }
            }
        }
        
        return chosen_hotkey;
    }

}}

namespace doticu_npcp { namespace Keys { namespace Exports {

    bool Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_keys", Keys_t,                \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Keys::METHOD_, __VA_ARGS__);      \
        W

        ADD_METHOD("Default_Value", 1, Int_t, Default_Value, String_t);
        ADD_METHOD("Current_Value", 1, Int_t, Current_Value, String_t);
        ADD_METHOD("Default_Mods", 1, Vector_t<Int_t>, Default_Mods, String_t);
        ADD_METHOD("Current_Mods", 1, Vector_t<Int_t>, Current_Mods, String_t);
        ADD_METHOD("Default_Mods_To_String", 1, String_t, Default_Mods_To_String, String_t);
        ADD_METHOD("Current_Mods_To_String", 1, String_t, Current_Mods_To_String, String_t);
        ADD_METHOD("Conflicting_Hotkey", 5, String_t, Conflicting_Hotkey, String_t, Int_t, Int_t, Int_t, Int_t);
        ADD_METHOD("Pressed_Hotkey", 9, String_t, Pressed_Hotkey, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t);

        #undef ADD_METHOD

        return true;
    }

}}}
