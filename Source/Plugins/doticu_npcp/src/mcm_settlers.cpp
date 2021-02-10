/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_alias.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_settler.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_settlers.h"

#include "commands.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    enum class Sandboxer_Option_e {
        UNSETTLE = 0,

        _MOVEMENT,
        MOVE_MARKER,
        MARKER_RADIUS,
        MOVEMENT_SPEED,
        ALLOW_SWIMMING,
        ALWAYS_SNEAK,

        _ACTIVITY,
        ALLOW_CONVERSATION,
        ALLOW_EATING,
        ALLOW_IDLE_MARKERS,
        ALLOW_SITTING,
        ALLOW_SLEEPING,
        ALLOW_SPECIAL_FURNITURE,
        ALLOW_WANDERING,
        PREFERRED_PATH_ONLY,
        MIN_WANDER_DISTANCE,
        ATTENTION,
        
        _COMBAT,
        IGNORE_COMBAT,
        SKIP_COMBAT_ALERT,
        ALLOW_AGGRO_RADIUS_BEHAVIOR,
        OBSERVE_COMBAT_BEHAVIOR,
        INSPECT_CORPSE_BEHAVIOR,
        KEEP_WEAPONS_DRAWN,
        HIDE_WEAPONS,
        
        _TALKING,
        ALLOW_HELLOS_TO_PLAYER,
        ALLOW_HELLOS_TO_NPCS,
        ALLOW_IDLE_CHATTER,
        ALLOW_WORLD_INTERACTIONS,
        REACT_TO_PLAYER_ACTIONS,
    };

    enum class Sleeper_Option_e {
        ENABLE = 0,

        _MOVEMENT,
        MOVE_MARKER,
        MARKER_RADIUS,
        MOVEMENT_SPEED,
        ALLOW_SWIMMING,
        ALWAYS_SNEAK,

        _TIME,
        TIME_HOUR,
        TIME_MINUTE,
        TIME_AM_PM,
        DURATION_HOURS,
        DURATION_MINUTES,

        SPACE_,
        SPACE__,
        SPACE___,

        _ACTIVITY,
        CREATE_BED_AT_MARKER,

        _COMBAT,
        IGNORE_COMBAT,
        SKIP_COMBAT_ALERT,
        ALLOW_AGGRO_RADIUS_BEHAVIOR,
        OBSERVE_COMBAT_BEHAVIOR,
        INSPECT_CORPSE_BEHAVIOR,
        KEEP_WEAPONS_DRAWN,
        HIDE_WEAPONS,
    };

    enum class Sitter_Option_e {
        ENABLE = 0,

        _MOVEMENT,
        MOVE_MARKER,
        MARKER_RADIUS,
        MOVEMENT_SPEED,
        ALLOW_SWIMMING,
        ALWAYS_SNEAK,

        _TIME,
        TIME_HOUR,
        TIME_MINUTE,
        TIME_AM_PM,
        DURATION_HOURS,
        DURATION_MINUTES,

        _COMBAT,
        IGNORE_COMBAT,
        SKIP_COMBAT_ALERT,
        ALLOW_AGGRO_RADIUS_BEHAVIOR,
        OBSERVE_COMBAT_BEHAVIOR,
        INSPECT_CORPSE_BEHAVIOR,
        KEEP_WEAPONS_DRAWN,
        HIDE_WEAPONS,

        _TALKING,
        ALLOW_HELLOS_TO_PLAYER,
        ALLOW_HELLOS_TO_NPCS,
        ALLOW_IDLE_CHATTER,
        ALLOW_WORLD_INTERACTIONS,
        REACT_TO_PLAYER_ACTIONS,
    };

    enum class Eater_Option_e {
        ENABLE = 0,

        _MOVEMENT,
        MOVE_MARKER,
        MARKER_RADIUS,
        MOVEMENT_SPEED,
        ALLOW_SWIMMING,
        ALWAYS_SNEAK,

        _TIME,
        TIME_HOUR,
        TIME_MINUTE,
        TIME_AM_PM,
        DURATION_HOURS,
        DURATION_MINUTES,

        _COMBAT,
        IGNORE_COMBAT,
        SKIP_COMBAT_ALERT,
        ALLOW_AGGRO_RADIUS_BEHAVIOR,
        OBSERVE_COMBAT_BEHAVIOR,
        INSPECT_CORPSE_BEHAVIOR,
        KEEP_WEAPONS_DRAWN,
        HIDE_WEAPONS,

        _TALKING,
        ALLOW_HELLOS_TO_PLAYER,
        ALLOW_HELLOS_TO_NPCS,
        ALLOW_IDLE_CHATTER,
        ALLOW_WORLD_INTERACTIONS,
        REACT_TO_PLAYER_ACTIONS,
    };

    enum class Guard_Option_e {
        ENABLE = 0,

        _MOVEMENT,
        MOVE_MARKER,
        MARKER_RADIUS,
        MOVEMENT_SPEED,
        ALLOW_SWIMMING,
        ALWAYS_SNEAK,

        _TIME,
        TIME_HOUR,
        TIME_MINUTE,
        TIME_AM_PM,
        DURATION_HOURS,
        DURATION_MINUTES,

        _COMBAT,
        IGNORE_COMBAT,
        SKIP_COMBAT_ALERT,
        ALLOW_AGGRO_RADIUS_BEHAVIOR,
        OBSERVE_COMBAT_BEHAVIOR,
        INSPECT_CORPSE_BEHAVIOR,
        KEEP_WEAPONS_DRAWN,
        HIDE_WEAPONS,

        _TALKING,
        ALLOW_HELLOS_TO_PLAYER,
        ALLOW_HELLOS_TO_NPCS,
        ALLOW_IDLE_CHATTER,
        ALLOW_WORLD_INTERACTIONS,
        REACT_TO_PLAYER_ACTIONS,
    };

    String_t Settlers_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_settlers");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Settlers_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Settlers_t* Settlers_t::Self()
    {
        return static_cast<Settlers_t*>(Consts::Control_Quest());
    }

    Object_t* Settlers_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Settlers_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Settlers_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Settlers_t::Current_View_Variable() { DEFINE_VARIABLE("p_current_view"); }

    Variable_t* Settlers_t::Settlers_Variable() { DEFINE_VARIABLE("p_settlers"); }
    Variable_t* Settlers_t::Page_Count_Variable() { DEFINE_VARIABLE("p_page_count"); }
    Variable_t* Settlers_t::Page_Index_Variable() { DEFINE_VARIABLE("p_page_index"); }

    Variable_t* Settlers_t::Settler_Variable() { DEFINE_VARIABLE("p_settler"); }
    Variable_t* Settlers_t::Settler_Page_Index_Variable() { DEFINE_VARIABLE("p_settler_page_index"); }
    Variable_t* Settlers_t::Do_Previous_Settler_Variable() { DEFINE_VARIABLE("p_do_previous_settler"); }
    Variable_t* Settlers_t::Do_Next_Settler_Variable() { DEFINE_VARIABLE("p_do_next_settler"); }

    Variable_t* Settlers_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Settlers_t::Update_Option_Variable() { DEFINE_VARIABLE("p_option_update"); }
    Variable_t* Settlers_t::Back_Option_Variable() { DEFINE_VARIABLE("p_option_back"); }
    Variable_t* Settlers_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_previous"); }
    Variable_t* Settlers_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }
    Variable_t* Settlers_t::Previous_2_Option_Variable() { DEFINE_VARIABLE("p_option_previous_2"); }
    Variable_t* Settlers_t::Next_2_Option_Variable() { DEFINE_VARIABLE("p_option_next_2"); }

    Int_t Settlers_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Settlers_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    Array_t* Settlers_t::Settlers()
    {
        return Settlers_Variable()->Array();
    }

    void Settlers_t::Settlers(Vector_t<Party::Member_t*> settlers)
    {
        Settlers_Variable()->Pack(settlers);
    }

    Int_t Settlers_t::Page_Count()
    {
        return Page_Count_Variable()->Int();
    }

    void Settlers_t::Page_Count(Int_t page_count)
    {
        Page_Count_Variable()->Int(page_count);
    }

    Int_t Settlers_t::Page_Index()
    {
        return Page_Index_Variable()->Int();
    }

    void Settlers_t::Page_Index(Int_t page_index)
    {
        Page_Index_Variable()->Int(page_index);
    }

    Party::Settler_t* Settlers_t::Settler()
    {
        return static_cast<Party::Settler_t*>(Settler_Variable()->Alias());
    }

    void Settlers_t::Settler(Party::Settler_t* settler)
    {
        Settler_Variable()->Pack(settler, Class_Info_t::Fetch(Party::Settler_t::kTypeID, true));
    }

    Int_t Settlers_t::Settler_Page_Index()
    {
        return Settler_Page_Index_Variable()->Int();
    }

    void Settlers_t::Settler_Page_Index(Int_t page_index)
    {
        Settler_Page_Index_Variable()->Int(page_index);
    }

    Int_t Settlers_t::Settler_Option_Index(Int_t option)
    {
        return (option - SETTLER_HEADERS - Options_Offset_Variable()->Int()) / 2;
    }

    Party::Settler_t* Settlers_t::Previous_Settler()
    {
        Array_t* settlers = Settlers();
        if (settlers && settlers->count > 0) {
            Party::Settler_t* settler = Settler();
            Int_t idx = settlers->Find(Party::Settler_t::kTypeID, settler);
            if (idx > -1) {
                if (idx == 0) {
                    return static_cast<Party::Settler_t*>(settlers->Point(settlers->count - 1)->Alias());
                } else {
                    return static_cast<Party::Settler_t*>(settlers->Point(idx - 1)->Alias());
                }
            } else {
                return static_cast<Party::Settler_t*>(settlers->Point(0)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Party::Settler_t* Settlers_t::Next_Settler()
    {
        Array_t* settlers = Settlers();
        if (settlers && settlers->count > 0) {
            Party::Settler_t* settler = Settler();
            Int_t idx = settlers->Find(Party::Settler_t::kTypeID, settler);
            if (idx > -1) {
                if (idx == settlers->count - 1) {
                    return static_cast<Party::Settler_t*>(settlers->Point(0)->Alias());
                } else {
                    return static_cast<Party::Settler_t*>(settlers->Point(idx + 1)->Alias());
                }
            } else {
                return static_cast<Party::Settler_t*>(settlers->Point(settlers->count - 1)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Bool_t Settlers_t::Do_Previous_Settler()
    {
        return Do_Previous_Settler_Variable()->Bool();
    }

    void Settlers_t::Do_Previous_Settler(Bool_t value)
    {
        Do_Previous_Settler_Variable()->Bool(value);
    }

    Bool_t Settlers_t::Do_Next_Settler()
    {
        return Do_Next_Settler_Variable()->Bool();
    }

    void Settlers_t::Do_Next_Settler(Bool_t value)
    {
        Do_Next_Settler_Variable()->Bool(value);
    }

    Bool_t Settlers_t::Is_Valid_Settler(Party::Settler_t* settler)
    {
        Array_t* settlers = Settlers();
        if (settlers) {
            return settler && settler->Is_Filled() && settler->Is_Settler() && settlers->Has(Party::Settler_t::kTypeID, settler);
        } else {
            return false;
        }
    }

    Int_t Settlers_t::Headers_Per_Page()
    {
        if (Current_View() == CODES::VIEW::SETTLERS) {
            return 4;
        } else if (Current_View() == CODES::VIEW::SETTLERS_SETTLER) {
            return 6;
        } else {
            NPCP_ASSERT(false);
            return 0;
        }
    }

    Int_t Settlers_t::Settlers_Per_Page()
    {
        if (Current_View() == CODES::VIEW::SETTLERS) {
            return 20;
        } else if (Current_View() == CODES::VIEW::SETTLERS_SETTLER) {
            return 1;
        } else {
            NPCP_ASSERT(false);
            return 0;
        }
    }

    Party::Settler_t* Settlers_t::Option_To_Settler(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            Int_t settlers_per_page = Settlers_Per_Page();
            Int_t relative_idx = option - Options_Offset_Variable()->Int() - Headers_Per_Page();
            if (relative_idx > -1 && relative_idx < settlers_per_page) {
                Array_t* settlers = Settlers();
                Int_t absolute_idx = Page_Index() * settlers_per_page + relative_idx;
                if (absolute_idx > -1 && absolute_idx < settlers->count) {
                    return static_cast<Party::Settler_t*>(settlers->Point(absolute_idx)->Alias());
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            return Settler();
        } else {
            NPCP_ASSERT(false);
            return nullptr;
        }
    }

    String_t Settlers_t::Settler_Info_String(Party::Settler_t* settler)
    {
        // we could add location cell, etc.

        if (settler) {
            std::string info =
                std::string("Sex: ") + settler->Sex().data + ", " +
                std::string("Race: ") + settler->Race().data + "\n";
            if (settler->Rating() > 0) {
                info += std::string("Rating: ") + settler->Rating_Stars().data;
            }
            return info.c_str();
        } else {
            return "";
        }
    }

    void Settlers_t::Review_Settlers()
    {
        Current_View(CODES::VIEW::SETTLERS);
        Settler(static_cast<Party::Settler_t*>(nullptr));
        Do_Previous_Settler(false);
        Do_Next_Settler(false);
    }

    void Settlers_t::View_Settler(Party::Settler_t* settler)
    {
        Current_View(CODES::VIEW::SETTLERS_SETTLER);
        Settler(settler);
        Do_Previous_Settler(false);
        Do_Next_Settler(false);
    }

    void Settlers_t::Reset_Page()
    {
        Main_t::Self()->Reset_Page(Main_t::SETTLERS_PAGE);
    }

    String_t Settlers_t::Format_Title(Int_t settler_count, Int_t page_index, Int_t page_count)
    {
        std::string settlers =
            std::string("Settlers: ") +
            std::to_string(settler_count) + "/" +
            std::to_string(Party::Members_t::Self()->Limit());

        std::string pages =
            std::string("Page: ") +
            std::to_string(page_index + 1) + "/" +
            std::to_string(page_count);

        return (settlers + "               " + pages).c_str();
    }

    template <typename Type_t>
    void Settlers_t::Build_Movement_Block(Main_t* mcm, Type_t* settler, Int_t flag)
    {
        mcm->Add_Text_Option(" Move Marker to Player ", "", flag);
        mcm->Add_Slider_Option(" Marker Radius: ", settler->Radius(), " {0} ", flag);
        mcm->Add_Menu_Option(" Movement Speed: ", settler->Speed_String(), flag);
        mcm->Add_Toggle_Option(" Allow Swimming ", settler->Is_Flagged(Type_t::Flag_e::ALLOW_SWIMMING), flag);
        mcm->Add_Toggle_Option(" Always Sneak ", settler->Is_Flagged(Type_t::Flag_e::ALWAYS_SNEAK), flag);
    }

    template <typename Type_t>
    void Settlers_t::Build_Time_Block(Main_t* mcm, Type_t* settler, Int_t flag)
    {
        mcm->Add_Menu_Option(" Time: ", settler->Hour_String(), flag);
        mcm->Add_Menu_Option("", settler->Minute_String(), flag);
        mcm->Add_Menu_Option("", settler->AM_PM_String(), flag);
        mcm->Add_Menu_Option(" Duration: ", settler->Duration_Hours_String(), flag);
        if (settler->Duration_Hours() == Party::Settler_t::MAX_DURATION_HOURS) {
            mcm->Add_Menu_Option("", settler->Duration_Minutes_String(), MCM::DISABLE);
        } else {
            mcm->Add_Menu_Option("", settler->Duration_Minutes_String(), flag);
        }
    }

    template <typename Type_t>
    void Settlers_t::Build_Combat_Block(Main_t* mcm, Type_t* settler, Int_t flag)
    {
        mcm->Add_Toggle_Option(" Ignore Combat ",               settler->Is_Flagged(Type_t::Flag_e::IGNORE_COMBAT),                 flag);
        mcm->Add_Toggle_Option(" Skip Combat Alert ",           settler->Is_Flagged(Type_t::Flag_e::SKIP_COMBAT_ALERT),             flag);
        mcm->Add_Toggle_Option(" Allow Aggro Radius Behavior ", settler->Is_Flagged(Type_t::Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR),   flag);
        mcm->Add_Toggle_Option(" Observe Combat Behavior ",     settler->Is_Flagged(Type_t::Flag_e::OBSERVE_COMBAT_BEHAVIOR),       flag);
        mcm->Add_Toggle_Option(" Inspect Corpse Behavior ",     settler->Is_Flagged(Type_t::Flag_e::INSPECT_CORPSE_BEHAVIOR),       flag);
        mcm->Add_Toggle_Option(" Keep Weapons Drawn ",          settler->Is_Flagged(Type_t::Flag_e::KEEP_WEAPONS_DRAWN),            flag);
        mcm->Add_Toggle_Option(" Hide Weapons ",                settler->Is_Flagged(Type_t::Flag_e::HIDE_WEAPONS),                  flag);
    }

    template <typename Type_t>
    void Settlers_t::Build_Talking_Block(Main_t* mcm, Type_t* settler, Int_t flag)
    {
        mcm->Add_Toggle_Option(" Allow Hellos to Player ",      settler->Is_Flagged(Type_t::Flag_e::ALLOW_HELLOS_TO_PLAYER),    flag);
        mcm->Add_Toggle_Option(" Allow Hellos to NPCs ",        settler->Is_Flagged(Type_t::Flag_e::ALLOW_HELLOS_TO_NPCS),      flag);
        mcm->Add_Toggle_Option(" Allow Idle Chatter ",          settler->Is_Flagged(Type_t::Flag_e::ALLOW_IDLE_CHATTER),        flag);
        mcm->Add_Toggle_Option(" Allow World Interactions ",    settler->Is_Flagged(Type_t::Flag_e::ALLOW_WORLD_INTERACTIONS),  flag);
        mcm->Add_Toggle_Option(" React to Player Actions ",     settler->Is_Flagged(Type_t::Flag_e::REACT_TO_PLAYER_ACTIONS),   flag);
    }

    template <typename Type_t>
    void Settlers_t::Build_Sandboxing_Block(Main_t* mcm, Type_t* settler, Int_t flag)
    {
        mcm->Add_Toggle_Option(" Allow Conversation ",          settler->Is_Flagged(Type_t::Flag_e::ALLOW_CONVERSATION),        flag);
        mcm->Add_Toggle_Option(" Allow Eating ",                settler->Is_Flagged(Type_t::Flag_e::ALLOW_EATING),              flag);
        mcm->Add_Toggle_Option(" Allow Idle Markers ",          settler->Is_Flagged(Type_t::Flag_e::ALLOW_IDLE_MARKERS),        flag);
        mcm->Add_Toggle_Option(" Allow Sitting ",               settler->Is_Flagged(Type_t::Flag_e::ALLOW_SITTING),             flag);
        mcm->Add_Toggle_Option(" Allow Sleeping ",              settler->Is_Flagged(Type_t::Flag_e::ALLOW_SLEEPING),            flag);
        mcm->Add_Toggle_Option(" Allow Special Furniture ",     settler->Is_Flagged(Type_t::Flag_e::ALLOW_SPECIAL_FURNITURE),   flag);
        mcm->Add_Toggle_Option(" Allow Wandering ",             settler->Is_Flagged(Type_t::Flag_e::ALLOW_WANDERING),           flag);
        mcm->Add_Toggle_Option(" Wander Preferred Path ",       settler->Is_Flagged(Type_t::Flag_e::PREFERRED_PATH_ONLY),       flag);
        mcm->Add_Slider_Option(" Minimum Wander Distance: ",    settler->Wander_Distance(), " {0} ", flag);
        mcm->Add_Slider_Option(" Attention: ",                  settler->Attention(),       " {0} ", flag);
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Select_Movement_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum)
    {
        if (option_enum == Option_e::MOVE_MARKER) {
            mcm->Flicker(option);
            settler->Move_Marker();
        } else if (option_enum == Option_e::ALLOW_SWIMMING) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_SWIMMING);
        } else if (option_enum == Option_e::ALWAYS_SNEAK) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALWAYS_SNEAK);
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Select_Combat_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum)
    {
        if (option_enum == Option_e::IGNORE_COMBAT) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::IGNORE_COMBAT);
        } else if (option_enum == Option_e::SKIP_COMBAT_ALERT) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::SKIP_COMBAT_ALERT);
        } else if (option_enum == Option_e::ALLOW_AGGRO_RADIUS_BEHAVIOR) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_AGGRO_RADIUS_BEHAVIOR);
        } else if (option_enum == Option_e::OBSERVE_COMBAT_BEHAVIOR) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::OBSERVE_COMBAT_BEHAVIOR);
        } else if (option_enum == Option_e::INSPECT_CORPSE_BEHAVIOR) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::INSPECT_CORPSE_BEHAVIOR);
        } else if (option_enum == Option_e::KEEP_WEAPONS_DRAWN) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::KEEP_WEAPONS_DRAWN);
        } else if (option_enum == Option_e::HIDE_WEAPONS) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::HIDE_WEAPONS);
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Select_Talking_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum)
    {
        if (option_enum == Option_e::ALLOW_HELLOS_TO_PLAYER) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_HELLOS_TO_PLAYER);
        } else if (option_enum == Option_e::ALLOW_HELLOS_TO_NPCS) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_HELLOS_TO_NPCS);
        } else if (option_enum == Option_e::ALLOW_IDLE_CHATTER) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_IDLE_CHATTER);
        } else if (option_enum == Option_e::ALLOW_WORLD_INTERACTIONS) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_WORLD_INTERACTIONS);
        } else if (option_enum == Option_e::REACT_TO_PLAYER_ACTIONS) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::REACT_TO_PLAYER_ACTIONS);
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Select_Sandboxing_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum)
    {
        if (option_enum == Option_e::ALLOW_CONVERSATION) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_CONVERSATION);
        } else if (option_enum == Option_e::ALLOW_EATING) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_EATING);
        } else if (option_enum == Option_e::ALLOW_IDLE_MARKERS) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_IDLE_MARKERS);
        } else if (option_enum == Option_e::ALLOW_SITTING) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_SITTING);
        } else if (option_enum == Option_e::ALLOW_SLEEPING) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_SLEEPING);
        } else if (option_enum == Option_e::ALLOW_SPECIAL_FURNITURE) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_SPECIAL_FURNITURE);
        } else if (option_enum == Option_e::ALLOW_WANDERING) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::ALLOW_WANDERING);
        } else if (option_enum == Option_e::PREFERRED_PATH_ONLY) {
            Toggle_Flag(mcm, option, settler, Type_t::Flag_e::PREFERRED_PATH_ONLY);
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Highlight_Movement_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum, std::string& name)
    {
        if (option_enum == Option_e::MOVE_MARKER) {
            mcm->Info_Text(name + " will stay around this invisible marker.");
        } else if (option_enum == Option_e::MARKER_RADIUS) {
            mcm->Info_Text("Change the range in which " + name + " will stay around the invisible marker.");
        } else if (option_enum == Option_e::MOVEMENT_SPEED) {
            mcm->Info_Text("Change how fast " + name + " will move around.");
        } else if (option_enum == Option_e::ALLOW_SWIMMING) {
            mcm->Info_Text(name + " will be allowed to swim to get to the next destination.");
        } else if (option_enum == Option_e::ALWAYS_SNEAK) {
            mcm->Info_Text(name + " will sneak around while moving.");
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Highlight_Time_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum, std::string& name)
    {
        if (option_enum == Option_e::TIME_HOUR) {
            mcm->Info_Text("The hour at which " + name + " will begin this package.");
        } else if (option_enum == Option_e::TIME_MINUTE) {
            mcm->Info_Text("The minute at which " + name + " will begin this package.");
        } else if (option_enum == Option_e::TIME_AM_PM) {
            mcm->Info_Text("The period at which " + name + " will begin this package.");
        } else if (option_enum == Option_e::DURATION_HOURS) {
            mcm->Info_Text("The duration in hours that " + name + " will continue this package.");
        } else if (option_enum == Option_e::DURATION_MINUTES) {
            mcm->Info_Text("The duration in minutes that " + name + " will continue this package.");
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Highlight_Combat_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum, std::string& name)
    {
        if (option_enum == Option_e::IGNORE_COMBAT) {
            mcm->Info_Text(name + " will not fight or flee from combat.");
        } else if (option_enum == Option_e::SKIP_COMBAT_ALERT) {
            mcm->Info_Text(name + " will immediately jump into battle, skipping the alert phase.");
        } else if (option_enum == Option_e::ALLOW_AGGRO_RADIUS_BEHAVIOR) {
            mcm->Info_Text(name + " may warn a potential enemy before engaging in battle.");
        } else if (option_enum == Option_e::OBSERVE_COMBAT_BEHAVIOR) {
            mcm->Info_Text(name + " may comment and observe a battle they are excluded from.");
        } else if (option_enum == Option_e::INSPECT_CORPSE_BEHAVIOR) {
            mcm->Info_Text(name + " may comment and inspect a nearby corpse.");
        } else if (option_enum == Option_e::KEEP_WEAPONS_DRAWN) {
            mcm->Info_Text(name + " will keep their weapons drawn.");
        } else if (option_enum == Option_e::HIDE_WEAPONS) {
            mcm->Info_Text(name + " will hide their weapons away.");
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Highlight_Talking_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum, std::string& name)
    {
        if (option_enum == Option_e::ALLOW_HELLOS_TO_PLAYER) {
            mcm->Info_Text(name + " may speak to you when you draw near.");
        } else if (option_enum == Option_e::ALLOW_HELLOS_TO_NPCS) {
            mcm->Info_Text(name + " may participate in a conversation with a sandboxing NPC.");
        } else if (option_enum == Option_e::ALLOW_IDLE_CHATTER) {
            mcm->Info_Text(name + " may randomly speak out loud from time to time.");
        } else if (option_enum == Option_e::ALLOW_WORLD_INTERACTIONS) {
            mcm->Info_Text(name + " may participate in world interaction events.");
        } else if (option_enum == Option_e::REACT_TO_PLAYER_ACTIONS) {
            mcm->Info_Text(name + " may react to the player doing something.");
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Option_e>
    Bool_t Settlers_t::Try_Highlight_Sandboxing_Block(Main_t* mcm, Int_t option, Type_t* settler, Option_e option_enum, std::string& name)
    {
        if (option_enum == Option_e::ALLOW_CONVERSATION) {
            mcm->Info_Text(name + " may initiate a conversation with another NPC.");
        } else if (option_enum == Option_e::ALLOW_EATING) {
            mcm->Info_Text(name + " may eat while sandboxing.");
        } else if (option_enum == Option_e::ALLOW_IDLE_MARKERS) {
            mcm->Info_Text(name + " may stand at pre-determined locations within their environment.");
        } else if (option_enum == Option_e::ALLOW_SITTING) {
            mcm->Info_Text(name + " may sit while sandboxing. They may still sit if they are allowed to eat.");
        } else if (option_enum == Option_e::ALLOW_SLEEPING) {
            mcm->Info_Text(name + " may sleep while sandboxing. They will need to find a bed unowned by another NPC.");
        } else if (option_enum == Option_e::ALLOW_SPECIAL_FURNITURE) {
            mcm->Info_Text(name + " may use enchanting and alchemical tables, armory stations, etc.");
        } else if (option_enum == Option_e::ALLOW_WANDERING) {
            mcm->Info_Text(name + " may wander a little ways from their marker.");
        } else if (option_enum == Option_e::PREFERRED_PATH_ONLY) {
            mcm->Info_Text(name + " may wander only on preferred navmesh triangles.");
        } else if (option_enum == Option_e::MIN_WANDER_DISTANCE) {
            mcm->Info_Text("The minimum distance " + name + " should wander away from where they are standing.");
        } else if (option_enum == Option_e::ATTENTION) {
            mcm->Info_Text("Affects how long " + name + " will continue in their current sandboxing activity.");
        } else {
            return false;
        }
        return true;
    }

    template <typename Type_t, typename Flag_e>
    void Settlers_t::Toggle_Flag(Main_t* mcm, Int_t option, Type_t* settler, Flag_e flag)
    {
        if (settler->Is_Flagged(flag)) {
            settler->Unflag(flag);
            mcm->Toggle_Option_Value(option, false, true);
        } else {
            settler->Flag(flag);
            mcm->Toggle_Option_Value(option, true, true);
        }
        settler->Enforce(settler->Actor(), true);
    }

    void Settlers_t::Open_Time_Hour_Menu()
    {
        Main_t* mcm = Main_t::Self();

        Vector_t<String_t> values;
        values.reserve(12);

        values.push_back(" 1 ");
        values.push_back(" 2 ");
        values.push_back(" 3 ");
        values.push_back(" 4 ");
        values.push_back(" 5 ");
        values.push_back(" 6 ");
        values.push_back(" 7 ");
        values.push_back(" 8 ");
        values.push_back(" 9 ");
        values.push_back(" 10 ");
        values.push_back(" 11 ");
        values.push_back(" 12 ");

        mcm->Menu_Dialog_Values(values);
        mcm->Menu_Dialog_Default(5);
    }

    void Settlers_t::Open_Time_Minute_Menu()
    {
        Main_t* mcm = Main_t::Self();

        Vector_t<String_t> values;
        values.reserve(12);

        values.push_back(" 00 ");
        values.push_back(" 05 ");
        values.push_back(" 10 ");
        values.push_back(" 15 ");
        values.push_back(" 20 ");
        values.push_back(" 25 ");
        values.push_back(" 30 ");
        values.push_back(" 35 ");
        values.push_back(" 40 ");
        values.push_back(" 45 ");
        values.push_back(" 50 ");
        values.push_back(" 55 ");

        mcm->Menu_Dialog_Values(values);
        mcm->Menu_Dialog_Default(0);
    }

    void Settlers_t::Open_Time_AM_PM_Menu()
    {
        Main_t* mcm = Main_t::Self();

        Vector_t<String_t> values;
        values.reserve(2);

        values.push_back(" AM ");
        values.push_back(" PM ");

        mcm->Menu_Dialog_Values(values);
        mcm->Menu_Dialog_Default(0);
    }

    void Settlers_t::Open_Duration_Hours_Menu()
    {
        Main_t* mcm = Main_t::Self();

        Vector_t<String_t> values;
        values.reserve(25);

        values.push_back(" 0 hours ");
        values.push_back(" 1 hour ");
        values.push_back(" 2 hours ");
        values.push_back(" 3 hours ");
        values.push_back(" 4 hours ");
        values.push_back(" 5 hours ");
        values.push_back(" 6 hours ");
        values.push_back(" 7 hours ");
        values.push_back(" 8 hours ");
        values.push_back(" 9 hours ");
        values.push_back(" 10 hours ");
        values.push_back(" 11 hours ");
        values.push_back(" 12 hours ");
        values.push_back(" 13 hours ");
        values.push_back(" 14 hours ");
        values.push_back(" 15 hours ");
        values.push_back(" 16 hours ");
        values.push_back(" 17 hours ");
        values.push_back(" 18 hours ");
        values.push_back(" 19 hours ");
        values.push_back(" 20 hours ");
        values.push_back(" 21 hours ");
        values.push_back(" 22 hours ");
        values.push_back(" 23 hours ");
        values.push_back(" 24 hours ");

        mcm->Menu_Dialog_Values(values);
        mcm->Menu_Dialog_Default(1);
    }

    void Settlers_t::Open_Duration_Minutes_Menu()
    {
        Main_t* mcm = Main_t::Self();

        Vector_t<String_t> values;
        values.reserve(12);

        values.push_back(" 0 minutes ");
        values.push_back(" 5 minutes ");
        values.push_back(" 10 minutes ");
        values.push_back(" 15 minutes ");
        values.push_back(" 20 minutes ");
        values.push_back(" 25 minutes ");
        values.push_back(" 30 minutes ");
        values.push_back(" 35 minutes ");
        values.push_back(" 40 minutes ");
        values.push_back(" 45 minutes ");
        values.push_back(" 50 minutes ");
        values.push_back(" 55 minutes ");

        mcm->Menu_Dialog_Values(values);
        mcm->Menu_Dialog_Default(0);
    }

    void Settlers_t::Open_Movement_Speed_Menu()
    {
        Main_t* mcm = Main_t::Self();

        Vector_t<String_t> values;
        values.reserve(4);

        values.push_back(" Walk ");
        values.push_back(" Fast Walk ");
        values.push_back(" Jog ");
        values.push_back(" Run ");

        mcm->Menu_Dialog_Values(values);
        mcm->Menu_Dialog_Default(0);
    }

    template <typename Type_t>
    void Settlers_t::Accept_Time_Hour_Menu(Int_t option, Int_t idx, Type_t* settler)
    {
        if (idx > -1) {
            Main_t* mcm = Main_t::Self();

            settler->Hour(idx + 1);
            settler->Enforce(settler->Actor(), true);
            mcm->Menu_Option_Value(option, settler->Hour_String(), true);
        }
    }

    template <typename Type_t>
    void Settlers_t::Accept_Time_Minute_Menu(Int_t option, Int_t idx, Type_t* settler)
    {
        if (idx > -1) {
            Main_t* mcm = Main_t::Self();

            settler->Minute(idx * 5);
            settler->Enforce(settler->Actor(), true);
            mcm->Menu_Option_Value(option, settler->Minute_String(), true);
        }
    }

    template <typename Type_t>
    void Settlers_t::Accept_Time_AM_PM_Menu(Int_t option, Int_t idx, Type_t* settler)
    {
        if (idx > -1) {
            Main_t* mcm = Main_t::Self();

            settler->AM_PM(static_cast<Party::AM_PM_e>(idx));
            settler->Enforce(settler->Actor(), true);
            mcm->Menu_Option_Value(option, settler->AM_PM_String(), true);
        }
    }

    template <typename Type_t>
    void Settlers_t::Accept_Duration_Hours_Menu(Int_t option, Int_t idx, Type_t* settler)
    {
        if (idx > -1) {
            Main_t* mcm = Main_t::Self();

            settler->Duration_Hours(idx);
            settler->Enforce(settler->Actor(), true);
            mcm->Menu_Option_Value(option, settler->Duration_Hours_String(), false);
            mcm->Menu_Option_Value(option + 2, settler->Duration_Minutes_String(), true);
            if (settler->Duration_Hours() == Party::Settler_t::MAX_DURATION_HOURS) {
                mcm->Option_Flags(option + 2, MCM::DISABLE, true);
            } else {
                mcm->Option_Flags(option + 2, MCM::NONE, true);
            }
        }
    }

    template <typename Type_t>
    void Settlers_t::Accept_Duration_Minutes_Menu(Int_t option, Int_t idx, Type_t* settler)
    {
        if (idx > -1) {
            Main_t* mcm = Main_t::Self();

            settler->Duration_Minutes(idx * 5);
            settler->Enforce(settler->Actor(), true);
            mcm->Menu_Option_Value(option - 2, settler->Duration_Hours_String(), false);
            mcm->Menu_Option_Value(option, settler->Duration_Minutes_String(), true);
            if (settler->Duration_Hours() == Party::Settler_t::MAX_DURATION_HOURS) {
                mcm->Option_Flags(option, MCM::DISABLE, true);
            } else {
                mcm->Option_Flags(option, MCM::NONE, true);
            }
        }
    }

    template <typename Type_t>
    void Settlers_t::Accept_Movement_Speed_Menu(Int_t option, Int_t idx, Type_t* settler)
    {
        if (idx > -1) {
            Main_t* mcm = Main_t::Self();

            if (idx == 0) {
                settler->Speed(Party::Settler_Speed_e::WALK);
            } else if (idx == 1) {
                settler->Speed(Party::Settler_Speed_e::FAST_WALK);
            } else if (idx == 2) {
                settler->Speed(Party::Settler_Speed_e::JOG);
            } else if (idx == 3) {
                settler->Speed(Party::Settler_Speed_e::RUN);
            }
            settler->Enforce(settler->Actor(), true);
            mcm->Menu_Option_Value(option, settler->Speed_String(), true);
        }
    }

    template <typename Type_t>
    void Settlers_t::Open_Marker_Radius_Slider(Type_t* settler)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Slider_Dialog_Current_Value(settler->Radius());
        mcm->Slider_Dialog_Default_Value(Party::Settler_t::DEFAULT_RADIUS);
        mcm->Slider_Dialog_Range_Values(Party::Settler_t::MIN_RADIUS, Party::Settler_t::MAX_RADIUS);
        mcm->Slider_Dialog_Interval_Value(64.0f);
    }

    template <typename Type_t>
    void Settlers_t::Open_Wander_Distance_Slider(Type_t* settler)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Slider_Dialog_Current_Value(settler->Wander_Distance());
        mcm->Slider_Dialog_Default_Value(Party::Settler_t::DEFAULT_WANDER_DISTANCE);
        mcm->Slider_Dialog_Range_Values(Party::Settler_t::MIN_WANDER_DISTANCE, Party::Settler_t::MAX_WANDER_DISTANCE);
        mcm->Slider_Dialog_Interval_Value(16.0f);
    }

    template <typename Type_t>
    void Settlers_t::Open_Attention_Slider(Type_t* settler)
    {
        Main_t* mcm = Main_t::Self();

        mcm->Slider_Dialog_Current_Value(settler->Attention());
        mcm->Slider_Dialog_Default_Value(Party::Settler_t::DEFAULT_ATTENTION);
        mcm->Slider_Dialog_Range_Values(Party::Settler_t::MIN_ATTENTION, Party::Settler_t::MAX_ATTENTION);
        mcm->Slider_Dialog_Interval_Value(1.0f);
    }

    template <typename Type_t>
    void Settlers_t::Accept_Marker_Radius_Slider(Int_t option, Float_t value, Type_t* settler)
    {
        Main_t* mcm = Main_t::Self();

        settler->Radius(value);
        settler->Enforce(settler->Actor(), true);
        mcm->Slider_Option_Value(option, value, " {0} ", true);
    }

    template <typename Type_t>
    void Settlers_t::Accept_Wander_Distance_Slider(Int_t option, Float_t value, Type_t* settler)
    {
        Main_t* mcm = Main_t::Self();

        settler->Wander_Distance(value);
        settler->Enforce(settler->Actor(), true);
        mcm->Slider_Option_Value(option, value, " {0} ", true);
    }

    template <typename Type_t>
    void Settlers_t::Accept_Attention_Slider(Int_t option, Float_t value, Type_t* settler)
    {
        Main_t* mcm = Main_t::Self();

        settler->Attention(value);
        settler->Enforce(settler->Actor(), true);
        mcm->Slider_Option_Value(option, value, " {0} ", true);
    }

    void Settlers_t::On_Build_Page()
    {
        auto Update_Settlers_Data = [&]()
        {
            Vector_t<Party::Member_t*> settlers = Party::Members_t::Self()->Sort_Settlers();
            Int_t settler_count = settlers.size();
            Int_t settlers_per_page = Settlers_Per_Page();
            Settlers(settlers);

            Int_t page_count;
            if (settler_count > 0) {
                page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(settler_count) / static_cast<Float_t>(settlers_per_page)
                ));
            } else {
                page_count = 0;
            }
            Page_Count(page_count);

            Int_t page_index = Page_Index();
            if (page_count > 0) {
                if (page_index < 0) {
                    page_index = 0;
                } else if (page_index >= page_count) {
                    page_index = page_count - 1;
                }
            } else {
                page_index = -1;
            }
            Page_Index(page_index);
        };

        auto Update_Settler_Data = [&]()
        {
            Int_t page_count = SETTLER_MAX_PAGES;
            Int_t page_index = Settler_Page_Index();
            if (page_index < 0) {
                page_index = 0;
            } else if (page_index >= page_count) {
                page_index = page_count - 1;
            }
            Settler_Page_Index(page_index);

            if (Do_Previous_Settler()) {
                Do_Previous_Settler(false);
                Settler(Previous_Settler());
            } else if (Do_Next_Settler()) {
                Do_Next_Settler(false);
                Settler(Next_Settler());
            }
        };

        auto Build_Settlers = [&]()
        {
            Update_Settlers_Data();

            Main_t* mcm = Main_t::Self();
            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

            Array_t* settlers = Settlers();
            if (settlers && settlers->count > 0) {
                Int_t settlers_per_page = Settlers_Per_Page();

                mcm->Title_Text(Format_Title(settlers->count, Page_Index(), Page_Count()));

                if (settlers->count > settlers_per_page) {
                    Previous_Option_Variable()->Int(
                        mcm->Add_Text_Option("                     Go to Previous Page", "")
                    );
                    Next_Option_Variable()->Int(
                        mcm->Add_Text_Option("                       Go to Next Page", "")
                    );
                } else {
                    Previous_Option_Variable()->Int(
                        mcm->Add_Text_Option("                     Go to Previous Page", "", MCM::DISABLE)
                    );
                    Next_Option_Variable()->Int(
                        mcm->Add_Text_Option("                       Go to Next Page", "", MCM::DISABLE)
                    );
                }
                Options_Offset_Variable()->Int(Previous_Option_Variable()->Int());

                mcm->Add_Header_Option("");
                mcm->Add_Header_Option("");

                Int_t begin = settlers_per_page * Page_Index();
                Int_t end = begin + settlers_per_page;
                if (end > settlers->count) {
                    end = settlers->count;
                }
                for (; begin < end; begin += 1) {
                    Party::Settler_t* settler = static_cast<Party::Settler_t*>
                        (settlers->Point(begin)->Alias());
                    mcm->Add_Text_Option(settler->Name(), "...");
                }
            } else {
                mcm->Title_Text(Format_Title(0, 0, 1));
                mcm->Add_Header_Option(" No Settlers ");
            }
        };

        auto Build_Settler = [&]()
        {
            Update_Settlers_Data();
            Update_Settler_Data();

            Party::Settler_t* settler = Settler();
            if (settler && Is_Valid_Settler(settler)) {
                Main_t* mcm = Main_t::Self();
                String_t settler_name = settler->Name();
                Int_t page_index = Settler_Page_Index();

                mcm->Title_Text((std::string("Settler: ") + settler_name.data).c_str());

                mcm->Cursor_Position(0);
                mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

                Update_Option_Variable()->Int(
                    mcm->Add_Text_Option("                   Manually Update AI", "")
                );
                Back_Option_Variable()->Int(
                    mcm->Add_Text_Option("                             Back", "")
                );
                Previous_Option_Variable()->Int(
                    mcm->Add_Text_Option("                      Previous Settler", "")
                );
                Next_Option_Variable()->Int(
                    mcm->Add_Text_Option("                        Next Settler", "")
                );
                Previous_2_Option_Variable()->Int(
                    mcm->Add_Text_Option("                    Previous Packages", "")
                );
                Next_2_Option_Variable()->Int(
                    mcm->Add_Text_Option("                      Next Packages", "")
                );
                Options_Offset_Variable()->Int(Update_Option_Variable()->Int());

                if (page_index == 0) {
                    mcm->Cursor_Position(6);
                    mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
                    mcm->Add_Header_Option(" Sandboxer ");
                    {
                        using Flag_e = Party::Sandboxer_t::Flag_e;

                        Party::Sandboxer_t* sandboxer = static_cast<Party::Sandboxer_t*>(settler);

                        mcm->Add_Text_Option(" Unsettle ", "");

                        mcm->Add_Empty_Option();
                        Build_Movement_Block(mcm, sandboxer, MCM::NONE);

                        mcm->Add_Empty_Option();
                        Build_Sandboxing_Block(mcm, sandboxer, MCM::NONE);

                        mcm->Add_Empty_Option();
                        Build_Combat_Block(mcm, sandboxer, MCM::NONE);

                        mcm->Add_Empty_Option();
                        Build_Talking_Block(mcm, sandboxer, MCM::NONE);
                    }

                    mcm->Cursor_Position(7);
                    mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
                    mcm->Add_Header_Option(" Sleeper ");
                    {
                        using Flag_e = Party::Sleeper_t::Flag_e;

                        Party::Sleeper_t* sleeper = static_cast<Party::Sleeper_t*>(settler);
                        Bool_t is_sleeper = sleeper->Is_Created();
                        Int_t flag = is_sleeper ? MCM::NONE : MCM::DISABLE;

                        mcm->Add_Toggle_Option(" Enabled: ", is_sleeper);

                        mcm->Add_Empty_Option();
                        Build_Movement_Block(mcm, sleeper, flag);

                        mcm->Add_Empty_Option();
                        Build_Time_Block(mcm, sleeper, flag);

                        mcm->Add_Empty_Option();
                        mcm->Add_Empty_Option();
                        mcm->Add_Empty_Option();

                        mcm->Add_Empty_Option();
                        mcm->Add_Toggle_Option(" Create Bed At Marker: ", sleeper->Has_Bed(), flag);

                        mcm->Add_Empty_Option();
                        Build_Combat_Block(mcm, sleeper, flag);
                    }
                } else if (page_index == 1) {
                    mcm->Cursor_Position(6);
                    mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
                    mcm->Add_Header_Option(" Sitter ");
                    {
                        using Flag_e = Party::Sitter_t::Flag_e;

                        Party::Sitter_t* sitter = static_cast<Party::Sitter_t*>(settler);
                        Bool_t is_sitter = sitter->Is_Created();
                        Int_t flag = is_sitter ? MCM::NONE : MCM::DISABLE;

                        mcm->Add_Toggle_Option(" Enabled: ", is_sitter);

                        mcm->Add_Empty_Option();
                        Build_Movement_Block(mcm, sitter, flag);

                        mcm->Add_Empty_Option();
                        Build_Time_Block(mcm, sitter, flag);

                        mcm->Add_Empty_Option();
                        Build_Combat_Block(mcm, sitter, flag);

                        mcm->Add_Empty_Option();
                        Build_Talking_Block(mcm, sitter, flag);
                    }

                    mcm->Cursor_Position(7);
                    mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
                    mcm->Add_Header_Option(" Eater ");
                    {
                        using Flag_e = Party::Eater_t::Flag_e;

                        Party::Eater_t* eater = static_cast<Party::Eater_t*>(settler);
                        Bool_t is_eater = eater->Is_Created();
                        Int_t flag = is_eater ? MCM::NONE : MCM::DISABLE;

                        mcm->Add_Toggle_Option(" Enabled: ", is_eater);

                        mcm->Add_Empty_Option();
                        Build_Movement_Block(mcm, eater, flag);

                        mcm->Add_Empty_Option();
                        Build_Time_Block(mcm, eater, flag);

                        mcm->Add_Empty_Option();
                        Build_Combat_Block(mcm, eater, flag);

                        mcm->Add_Empty_Option();
                        Build_Talking_Block(mcm, eater, flag);
                    }
                } else if (page_index == 2) {
                    mcm->Cursor_Position(6);
                    mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
                    mcm->Add_Header_Option(" Guard ");
                    {
                        using Flag_e = Party::Guard_t::Flag_e;

                        Party::Guard_t* guard = static_cast<Party::Guard_t*>(settler);
                        Bool_t is_guard = guard->Is_Created();
                        Int_t flag = is_guard ? MCM::NONE : MCM::DISABLE;

                        mcm->Add_Toggle_Option(" Enabled: ", is_guard);

                        mcm->Add_Empty_Option();
                        Build_Movement_Block(mcm, guard, flag);

                        mcm->Add_Empty_Option();
                        Build_Time_Block(mcm, guard, flag);

                        mcm->Add_Empty_Option();
                        Build_Combat_Block(mcm, guard, flag);

                        mcm->Add_Empty_Option();
                        Build_Talking_Block(mcm, guard, flag);
                    }
                }
            } else {
                Review_Settlers();
                Build_Settlers();
            }
        };

        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            Build_Settlers();
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Build_Settler();
        } else {
            Review_Settlers();
            Build_Settlers();
        }
    }

    void Settlers_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>*;
        NPCP_ASSERT(user_callback);

        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            if (option == Previous_Option_Variable()->Int()) {
                mcm->Disable(option);

                Int_t page_idx = Page_Index();
                if (page_idx == 0) {
                    page_idx = Page_Count() - 1;
                } else {
                    page_idx -= 1;
                }
                Page_Index(page_idx);

                mcm->Reset_Page();
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Disable(option);

                Int_t page_idx = Page_Index();
                if (page_idx == Page_Count() - 1) {
                    page_idx = 0;
                } else {
                    page_idx += 1;
                }
                Page_Index(page_idx);

                mcm->Reset_Page();
            } else {
                Party::Settler_t* settler = Option_To_Settler(option);
                if (settler) {
                    mcm->Disable(option);
                    View_Settler(settler);
                    mcm->Reset_Page();
                }
            }
            mcm->Return_Latent(user_callback);
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Party::Settler_t* settler = Settler();
            if (Is_Valid_Settler(settler)) {
                if (option == Update_Option_Variable()->Int()) {
                    Actor_t* settler_actor = settler->Actor();
                    mcm->Flicker(option);
                    settler->Enforce(settler_actor, true);
                    Actor2::Send_Animation_Event(settler_actor, "IdleForceDefaultState");
                } else if (option == Back_Option_Variable()->Int()) {
                    mcm->Disable(option);
                    Review_Settlers();
                    mcm->Reset_Page();
                } else if (option == Previous_Option_Variable()->Int()) {
                    mcm->Disable(option);
                    Do_Previous_Settler(true);
                    Reset_Page();
                } else if (option == Next_Option_Variable()->Int()) {
                    mcm->Disable(option);
                    Do_Next_Settler(true);
                    Reset_Page();
                } else if (option == Previous_2_Option_Variable()->Int()) {
                    mcm->Disable(option);

                    Int_t page_idx = Settler_Page_Index();
                    if (page_idx == 0) {
                        page_idx = SETTLER_MAX_PAGES - 1;
                    } else {
                        page_idx -= 1;
                    }
                    Settler_Page_Index(page_idx);

                    Reset_Page();
                } else if (option == Next_2_Option_Variable()->Int()) {
                    mcm->Disable(option);

                    Int_t page_idx = Settler_Page_Index();
                    if (page_idx == SETTLER_MAX_PAGES - 1) {
                        page_idx = 0;
                    } else {
                        page_idx += 1;
                    }
                    Settler_Page_Index(page_idx);

                    Reset_Page();
                } else {
                    Int_t page_index = Settler_Page_Index();
                    Int_t option_index = Settler_Option_Index(option);
                    if (page_index == 0) {
                        if (Utils::Is_Even(option)) {
                            using Option_e = Sandboxer_Option_e;
                            using Flag_e = Party::Sandboxer_t::Flag_e;

                            Party::Sandboxer_t* sandboxer = static_cast<Party::Sandboxer_t*>(settler);
                            Option_e option_enum = static_cast<Option_e>(option_index);
                            if (option_enum == Option_e::UNSETTLE) {
                                mcm->Disable(option);
                                Modules::Control::Commands_t::Self()->Unsettle(sandboxer->Actor(), true);
                                Review_Settlers();
                                mcm->Reset_Page();
                            } else if (Try_Select_Movement_Block(mcm, option, sandboxer, option_enum)) {
                            } else if (Try_Select_Sandboxing_Block(mcm, option, sandboxer, option_enum)) {
                            } else if (Try_Select_Combat_Block(mcm, option, sandboxer, option_enum)) {
                            } else if (Try_Select_Talking_Block(mcm, option, sandboxer, option_enum)) {
                            }
                        } else {
                            using Option_e = Sleeper_Option_e;
                            using Flag_e = Party::Sleeper_t::Flag_e;

                            Party::Sleeper_t* sleeper = static_cast<Party::Sleeper_t*>(settler);
                            Option_e option_enum = static_cast<Option_e>(option_index);
                            if (option_enum == Option_e::ENABLE) {
                                if (sleeper->Is_Sleeper()) {
                                    sleeper->Disable_Sleeper();
                                } else {
                                    sleeper->Enable_Sleeper();
                                }
                                Reset_Page();
                            } else if (Try_Select_Movement_Block(mcm, option, sleeper, option_enum)) {
                            } else if (option_enum == Option_e::CREATE_BED_AT_MARKER) {
                                if (sleeper->Has_Bed()) {
                                    sleeper->Remove_Bed();
                                    mcm->Toggle_Option_Value(option, false, true);
                                } else {
                                    sleeper->Add_Bed();
                                    mcm->Toggle_Option_Value(option, true, true);
                                }
                            } else if (Try_Select_Combat_Block(mcm, option, sleeper, option_enum)) {
                            }
                        }
                    } else if (page_index == 1) {
                        if (Utils::Is_Even(option)) {
                            using Option_e = Sitter_Option_e;
                            using Flag_e = Party::Sitter_t::Flag_e;

                            Party::Sitter_t* sitter = static_cast<Party::Sitter_t*>(settler);
                            Option_e option_enum = static_cast<Option_e>(option_index);
                            if (option_enum == Option_e::ENABLE) {
                                if (sitter->Is_Sitter()) {
                                    sitter->Disable_Sitter();
                                } else {
                                    sitter->Enable_Sitter();
                                }
                                Reset_Page();
                            } else if (Try_Select_Movement_Block(mcm, option, sitter, option_enum)) {
                            } else if (Try_Select_Combat_Block(mcm, option, sitter, option_enum)) {
                            } else if (Try_Select_Talking_Block(mcm, option, sitter, option_enum)) {
                            }
                        } else {
                            using Option_e = Eater_Option_e;
                            using Flag_e = Party::Eater_t::Flag_e;

                            Party::Eater_t* eater = static_cast<Party::Eater_t*>(settler);
                            Option_e option_enum = static_cast<Option_e>(option_index);
                            if (option_enum == Option_e::ENABLE) {
                                if (eater->Is_Eater()) {
                                    eater->Disable_Eater();
                                } else {
                                    eater->Enable_Eater();
                                }
                                Reset_Page();
                            } else if (Try_Select_Movement_Block(mcm, option, eater, option_enum)) {
                            } else if (Try_Select_Combat_Block(mcm, option, eater, option_enum)) {
                            } else if (Try_Select_Talking_Block(mcm, option, eater, option_enum)) {
                            }
                        }
                    } else if (page_index == 2) {
                        if (Utils::Is_Even(option)) {
                            using Option_e = Guard_Option_e;
                            using Flag_e = Party::Guard_t::Flag_e;

                            Party::Guard_t* guard = static_cast<Party::Guard_t*>(settler);
                            Option_e option_enum = static_cast<Option_e>(option_index);
                            if (option_enum == Option_e::ENABLE) {
                                if (guard->Is_Guard()) {
                                    guard->Disable_Guard();
                                } else {
                                    guard->Enable_Guard();
                                }
                                Reset_Page();
                            } else if (Try_Select_Movement_Block(mcm, option, guard, option_enum)) {
                            } else if (Try_Select_Combat_Block(mcm, option, guard, option_enum)) {
                            } else if (Try_Select_Talking_Block(mcm, option, guard, option_enum)) {
                            }
                        }
                    }
                }
            }
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settlers_t::On_Option_Menu_Open(Int_t option)
    {
        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Party::Settler_t* settler = Settler();
            if (Is_Valid_Settler(settler)) {
                Int_t page_index = Settler_Page_Index();
                Int_t option_index = Settler_Option_Index(option);
                if (page_index == 0) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sandboxer_Option_e;

                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Open_Movement_Speed_Menu();
                        }
                    } else {
                        using Option_e = Sleeper_Option_e;

                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Open_Movement_Speed_Menu();
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Open_Time_Hour_Menu();
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Open_Time_Minute_Menu();
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Open_Time_AM_PM_Menu();
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Open_Duration_Hours_Menu();
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Open_Duration_Minutes_Menu();

                        }
                    }
                } else if (page_index == 1) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sitter_Option_e;

                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Open_Movement_Speed_Menu();
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Open_Time_Hour_Menu();
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Open_Time_Minute_Menu();
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Open_Time_AM_PM_Menu();
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Open_Duration_Hours_Menu();
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Open_Duration_Minutes_Menu();

                        }
                    } else {
                        using Option_e = Eater_Option_e;

                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Open_Movement_Speed_Menu();
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Open_Time_Hour_Menu();
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Open_Time_Minute_Menu();
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Open_Time_AM_PM_Menu();
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Open_Duration_Hours_Menu();
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Open_Duration_Minutes_Menu();

                        }
                    }
                } else if (page_index == 2) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Guard_Option_e;

                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Open_Movement_Speed_Menu();
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Open_Time_Hour_Menu();
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Open_Time_Minute_Menu();
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Open_Time_AM_PM_Menu();
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Open_Duration_Hours_Menu();
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Open_Duration_Minutes_Menu();

                        }
                    }
                }
            }
        } else {

        }
    }

    void Settlers_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Party::Settler_t* settler = Settler();
            if (Is_Valid_Settler(settler)) {
                Int_t page_index = Settler_Page_Index();
                Int_t option_index = Settler_Option_Index(option);
                if (page_index == 0) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sandboxer_Option_e;

                        Party::Sandboxer_t* sandboxer = static_cast<Party::Sandboxer_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Accept_Movement_Speed_Menu(option, idx, sandboxer);
                        }
                    } else {
                        using Option_e = Sleeper_Option_e;

                        Party::Sleeper_t* sleeper = static_cast<Party::Sleeper_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Accept_Movement_Speed_Menu(option, idx, sleeper);
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Accept_Time_Hour_Menu(option, idx, sleeper);
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Accept_Time_Minute_Menu(option, idx, sleeper);
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Accept_Time_AM_PM_Menu(option, idx, sleeper);
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Accept_Duration_Hours_Menu(option, idx, sleeper);
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Accept_Duration_Minutes_Menu(option, idx, sleeper);

                        }
                    }
                } else if (page_index == 1) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sitter_Option_e;

                        Party::Sitter_t* sitter = static_cast<Party::Sitter_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Accept_Movement_Speed_Menu(option, idx, sitter);
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Accept_Time_Hour_Menu(option, idx, sitter);
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Accept_Time_Minute_Menu(option, idx, sitter);
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Accept_Time_AM_PM_Menu(option, idx, sitter);
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Accept_Duration_Hours_Menu(option, idx, sitter);
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Accept_Duration_Minutes_Menu(option, idx, sitter);

                        }
                    } else {
                        using Option_e = Eater_Option_e;

                        Party::Eater_t* eater = static_cast<Party::Eater_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Accept_Movement_Speed_Menu(option, idx, eater);
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Accept_Time_Hour_Menu(option, idx, eater);
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Accept_Time_Minute_Menu(option, idx, eater);
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Accept_Time_AM_PM_Menu(option, idx, eater);
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Accept_Duration_Hours_Menu(option, idx, eater);
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Accept_Duration_Minutes_Menu(option, idx, eater);

                        }
                    }
                } else if (page_index == 2) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Guard_Option_e;

                        Party::Guard_t* guard = static_cast<Party::Guard_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MOVEMENT_SPEED) {
                            Accept_Movement_Speed_Menu(option, idx, guard);
                        } else if (option_enum == Option_e::TIME_HOUR) {
                            Accept_Time_Hour_Menu(option, idx, guard);
                        } else if (option_enum == Option_e::TIME_MINUTE) {
                            Accept_Time_Minute_Menu(option, idx, guard);
                        } else if (option_enum == Option_e::TIME_AM_PM) {
                            Accept_Time_AM_PM_Menu(option, idx, guard);
                        } else if (option_enum == Option_e::DURATION_HOURS) {
                            Accept_Duration_Hours_Menu(option, idx, guard);
                        } else if (option_enum == Option_e::DURATION_MINUTES) {
                            Accept_Duration_Minutes_Menu(option, idx, guard);

                        }
                    }
                }
            }
        } else {

        }
    }

    void Settlers_t::On_Option_Slider_Open(Int_t option)
    {
        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Party::Settler_t* settler = Settler();
            if (Is_Valid_Settler(settler)) {
                Int_t page_index = Settler_Page_Index();
                Int_t option_index = Settler_Option_Index(option);
                if (page_index == 0) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sandboxer_Option_e;

                        Party::Sandboxer_t* sandboxer = static_cast<Party::Sandboxer_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Open_Marker_Radius_Slider(sandboxer);
                        } else if (option_enum == Option_e::MIN_WANDER_DISTANCE) {
                            Open_Wander_Distance_Slider(sandboxer);
                        } else if (option_enum == Option_e::ATTENTION) {
                            Open_Attention_Slider(sandboxer);
                        }
                    } else {
                        using Option_e = Sleeper_Option_e;

                        Party::Sleeper_t* sleeper = static_cast<Party::Sleeper_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Open_Marker_Radius_Slider(sleeper);
                        }
                    }
                } else if (page_index == 1) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sitter_Option_e;

                        Party::Sitter_t* sitter = static_cast<Party::Sitter_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Open_Marker_Radius_Slider(sitter);
                        }
                    } else {
                        using Option_e = Eater_Option_e;

                        Party::Eater_t* eater = static_cast<Party::Eater_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Open_Marker_Radius_Slider(eater);
                        }
                    }
                } else if (page_index == 2) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Guard_Option_e;

                        Party::Guard_t* guard = static_cast<Party::Guard_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Open_Marker_Radius_Slider(guard);
                        }
                    }
                }
            }
        } else {

        }
    }

    void Settlers_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Party::Settler_t* settler = Settler();
            if (Is_Valid_Settler(settler)) {
                Int_t page_index = Settler_Page_Index();
                Int_t option_index = Settler_Option_Index(option);
                if (page_index == 0) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sandboxer_Option_e;

                        Party::Sandboxer_t* sandboxer = static_cast<Party::Sandboxer_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Accept_Marker_Radius_Slider(option, value, sandboxer);
                        } else if (option_enum == Option_e::MIN_WANDER_DISTANCE) {
                            Accept_Wander_Distance_Slider(option, value, sandboxer);
                        } else if (option_enum == Option_e::ATTENTION) {
                            Accept_Attention_Slider(option, value, sandboxer);
                        }
                    } else {
                        using Option_e = Sleeper_Option_e;

                        Party::Sleeper_t* sleeper = static_cast<Party::Sleeper_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Accept_Marker_Radius_Slider(option, value, sleeper);
                        }
                    }
                } else if (page_index == 1) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sitter_Option_e;

                        Party::Sitter_t* sitter = static_cast<Party::Sitter_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Accept_Marker_Radius_Slider(option, value, sitter);
                        }
                    } else {
                        using Option_e = Eater_Option_e;

                        Party::Eater_t* eater = static_cast<Party::Eater_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Accept_Marker_Radius_Slider(option, value, eater);
                        }
                    }
                } else if (page_index == 2) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Guard_Option_e;

                        Party::Guard_t* guard = static_cast<Party::Guard_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::MARKER_RADIUS) {
                            Accept_Marker_Radius_Slider(option, value, guard);
                        }
                    }
                }
            }
        } else {

        }
    }

    void Settlers_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::On_Option_Keymap_Change(Int_t option,
                                             Int_t key_code,
                                             String_t conflict,
                                             String_t conflicting_mod,
                                             Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            mcm->Return_Latent(user_callback);
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settlers_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            mcm->Return_Latent(user_callback);
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settlers_t::On_Option_Highlight(Int_t option)
    {
        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            if (option == Previous_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Previous Page");
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Next Page");
            } else {
                Party::Settler_t* settler = Option_To_Settler(option);
                if (settler) {
                    mcm->Info_Text(
                        (std::string("Opens the settler menu for ") +
                         settler->Name().data + ".\n" +
                         Settler_Info_String(settler).data).c_str()
                    );
                }
            }
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Party::Settler_t* settler = Settler();
            if (Is_Valid_Settler(settler)) {
                std::string name = settler->Name().data;
                Int_t page_index = Settler_Page_Index();
                Int_t option_index = Settler_Option_Index(option);
                if (page_index == 0) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sandboxer_Option_e;

                        Party::Sandboxer_t* sandboxer = static_cast<Party::Sandboxer_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::UNSETTLE) {
                            mcm->Info_Text(name + " will no longer be a settler. All other settler packages will also be disabled.");
                        } else if (Try_Highlight_Movement_Block(mcm, option, sandboxer, option_enum, name)) {
                        } else if (Try_Highlight_Sandboxing_Block(mcm, option, sandboxer, option_enum, name)) {
                        } else if (Try_Highlight_Combat_Block(mcm, option, sandboxer, option_enum, name)) {
                        } else if (Try_Highlight_Talking_Block(mcm, option, sandboxer, option_enum, name)) {
                        }
                    } else {
                        using Option_e = Sleeper_Option_e;

                        Party::Sleeper_t* sleeper = static_cast<Party::Sleeper_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::ENABLE) {
                            mcm->Info_Text("Toggle the Sleeper package for " + name + ".");
                        } else if (option_enum == Option_e::CREATE_BED_AT_MARKER) {
                            mcm->Info_Text("Create a bed for " + name + " to sleep in, located where the marker is placed.");
                        } else if (Try_Highlight_Movement_Block(mcm, option, sleeper, option_enum, name)) {
                        } else if (Try_Highlight_Time_Block(mcm, option, sleeper, option_enum, name)) {
                        } else if (Try_Highlight_Combat_Block(mcm, option, sleeper, option_enum, name)) {
                        }
                    }
                } else if (page_index == 1) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Sitter_Option_e;

                        Party::Sitter_t* sitter = static_cast<Party::Sitter_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::ENABLE) {
                            mcm->Info_Text("Toggle the Sitter package for " + name + ".");
                        } else if (Try_Highlight_Movement_Block(mcm, option, sitter, option_enum, name)) {
                        } else if (Try_Highlight_Time_Block(mcm, option, sitter, option_enum, name)) {
                        } else if (Try_Highlight_Combat_Block(mcm, option, sitter, option_enum, name)) {
                        } else if (Try_Highlight_Talking_Block(mcm, option, sitter, option_enum, name)) {
                        }
                    } else {
                        using Option_e = Eater_Option_e;

                        Party::Eater_t* eater = static_cast<Party::Eater_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::ENABLE) {
                            mcm->Info_Text("Toggle the Eater package for " + name + ".");
                        } else if (Try_Highlight_Movement_Block(mcm, option, eater, option_enum, name)) {
                        } else if (Try_Highlight_Time_Block(mcm, option, eater, option_enum, name)) {
                        } else if (Try_Highlight_Combat_Block(mcm, option, eater, option_enum, name)) {
                        } else if (Try_Highlight_Talking_Block(mcm, option, eater, option_enum, name)) {
                        }
                    }
                } else if (page_index == 2) {
                    if (Utils::Is_Even(option)) {
                        using Option_e = Guard_Option_e;

                        Party::Guard_t* guard = static_cast<Party::Guard_t*>(settler);
                        Option_e option_enum = static_cast<Option_e>(option_index);
                        if (option_enum == Option_e::ENABLE) {
                            mcm->Info_Text("Toggle the Guard package for " + name + ".");
                        } else if (Try_Highlight_Movement_Block(mcm, option, guard, option_enum, name)) {
                        } else if (Try_Highlight_Time_Block(mcm, option, guard, option_enum, name)) {
                        } else if (Try_Highlight_Combat_Block(mcm, option, guard, option_enum, name)) {
                        } else if (Try_Highlight_Talking_Block(mcm, option, guard, option_enum, name)) {
                        }
                    }
                }
            }
        } else {

        }
    }

    void Settlers_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Members_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
