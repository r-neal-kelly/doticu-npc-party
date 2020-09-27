/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "commands.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_member.h"
#include "party/party_followers.h"
#include "party/party_follower.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_followers.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Followers_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_followers");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Followers_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Followers_t* Followers_t::Self()
    {
        return static_cast<Followers_t*>(Consts::Control_Quest());
    }

    Object_t* Followers_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Followers_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Followers_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Followers_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }

    Variable_t* Followers_t::Followers_Variable() { DEFINE_VARIABLE("p_arr_aliases"); }
    Variable_t* Followers_t::Follower_Variable() { DEFINE_VARIABLE("p_ref_follower"); }

    Variable_t* Followers_t::Do_Previous_Follower_Variable() { DEFINE_VARIABLE("p_do_prev_follower"); }
    Variable_t* Followers_t::Do_Next_Follower_Variable() { DEFINE_VARIABLE("p_do_next_follower"); }

    Variable_t* Followers_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Followers_t::Menu_Option_Variable() { DEFINE_VARIABLE("p_option_menu"); }

    Int_t Followers_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Followers_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    Array_t* Followers_t::Followers()
    {
        return Followers_Variable()->Array();
    }

    void Followers_t::Followers(Vector_t<Party::Follower_t*> followers)
    {
        Followers_Variable()->Pack(followers);
    }

    Party::Follower_t* Followers_t::Follower()
    {
        return static_cast<Party::Follower_t*>(Follower_Variable()->Alias());
    }

    void Followers_t::Follower(Party::Follower_t* follower)
    {
        Follower_Variable()->Pack(follower, Party::Follower_t::Class_Info());
    }

    Party::Follower_t* Followers_t::Previous_Follower()
    {
        Array_t* followers = Followers();
        if (followers && followers->count > 0) {
            Party::Follower_t* follower = Follower();
            Int_t idx = followers->Find(Party::Follower_t::kTypeID, follower);
            if (idx > -1) {
                if (idx == 0) {
                    return static_cast<Party::Follower_t*>(followers->Point(followers->count - 1)->Alias());
                } else {
                    return static_cast<Party::Follower_t*>(followers->Point(idx - 1)->Alias());
                }
            } else {
                return static_cast<Party::Follower_t*>(followers->Point(0)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Party::Follower_t* Followers_t::Next_Follower()
    {
        Array_t* followers = Followers();
        if (followers && followers->count > 0) {
            Party::Follower_t* follower = Follower();
            Int_t idx = followers->Find(Party::Follower_t::kTypeID, follower);
            if (idx > -1) {
                if (idx == followers->count - 1) {
                    return static_cast<Party::Follower_t*>(followers->Point(0)->Alias());
                } else {
                    return static_cast<Party::Follower_t*>(followers->Point(idx + 1)->Alias());
                }
            } else {
                return static_cast<Party::Follower_t*>(followers->Point(followers->count - 1)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Followers_t::Follower_Indices_t Followers_t::Follower_Indices(Int_t option)
    {
        Int_t normal = option - Options_Offset_Variable()->Int() - HEADERS;

        Int_t follower_idx = 2 * floorf(static_cast<Float_t>(normal) / (OPTIONS_PER_FOLLOWER * 2));
        if (normal % 2 == 1) {
            follower_idx += 1;
        }

        Int_t option_idx =
            floorf(static_cast<Float_t>(normal) / 2) -
            (floorf(static_cast<Float_t>(follower_idx) / 2) * OPTIONS_PER_FOLLOWER);

        return { follower_idx, option_idx };
    }

    Bool_t Followers_t::Do_Previous_Follower()
    {
        return Do_Previous_Follower_Variable()->Bool();
    }

    void Followers_t::Do_Previous_Follower(Bool_t do_previous_follower)
    {
        Do_Previous_Follower_Variable()->Bool(do_previous_follower);
    }

    Bool_t Followers_t::Do_Next_Follower()
    {
        return Do_Next_Follower_Variable()->Bool();
    }

    void Followers_t::Do_Next_Follower(Bool_t do_next_follower)
    {
        Do_Next_Follower_Variable()->Bool(do_next_follower);
    }

    void Followers_t::View_Followers()
    {
        Vector_t<Party::Follower_t*> followers =
            Party::Followers_t::Self()->Sort_Filled();
        Followers(followers);

        if (Follower()) {
            Current_View(CODES::VIEW::FOLLOWERS_MEMBER);
        } else {
            Current_View(CODES::VIEW::FOLLOWERS);
        }
    }

    void Followers_t::Review_Followers()
    {
        Current_View(CODES::VIEW::FOLLOWERS);
        Follower(nullptr);
    }

    void Followers_t::Request_Previous_Follower()
    {
        Do_Previous_Follower_Variable()->Bool(true);
    }

    void Followers_t::Request_Next_Follower()
    {
        Do_Next_Follower_Variable()->Bool(true);
    }

    void Followers_t::On_Build_Page()
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            Array_t* followers = Followers();
            if (followers && followers->count > 0) {
                Party::Follower_t* follower = Follower();
                if (follower && follower->Is_Filled()) {
                    if (Do_Previous_Follower()) {
                        Do_Previous_Follower(false);
                        follower = Previous_Follower();
                        Follower(follower);
                    } else if (Do_Next_Follower()) {
                        Do_Next_Follower(false);
                        follower = Next_Follower();
                        Follower(follower);
                    }
                    if (follower && follower->Is_Filled()) {
                        Current_View(CODES::VIEW::FOLLOWERS_MEMBER);
                        MCM::Member_t* mcm_member = MCM::Member_t::Self();
                        mcm_member->View_Followers_Member(follower->Member());
                        mcm_member->On_Build_Page();
                    } else {
                        Review_Followers();
                        On_Build_Page();
                    }
                } else {
                    Review_Followers();
                    On_Build_Page();
                }
            } else {
                Review_Followers();
                On_Build_Page();
            }
        } else {
            MCM::Main_t* mcm = Main();

            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

            Array_t* followers = Followers();
            Int_t followers_count = followers ? followers->count : 0;
            Int_t max_followers = Party::Followers_t::Self()->Max();
            if (followers_count < 1) {
                mcm->Title_Text(("Followers: 0/" + std::to_string(max_followers)).c_str());
                mcm->Add_Header_Option(" No Followers ");
            } else {
                mcm->Title_Text(("Followers: " + std::to_string(followers_count) + "/" + std::to_string(max_followers)).c_str());

                int menu_option = mcm->Add_Menu_Option("Command All ", "...");
                Menu_Option_Variable()->Int(menu_option);
                Options_Offset_Variable()->Int(menu_option);
                mcm->Add_Empty_Option();

                mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

                for (size_t idx = 0, count = followers_count, cursor = HEADERS; idx < count; idx += 1) {
                    Party::Follower_t* follower = static_cast<Party::Follower_t*>
                        (followers->Point(idx)->Alias());

                    mcm->Cursor_Position(cursor);

                    mcm->Add_Header_Option(follower->Name());
                    mcm->Add_Text_Option("   Summon", "");
                    mcm->Add_Text_Option("   Pack", "");
                    if (follower->Is_Immobile()) {
                        mcm->Add_Text_Option("   Mobilize", "");
                    } else {
                        mcm->Add_Text_Option("   Immobilize", "");
                    }
                    mcm->Add_Text_Option("   More", "...");

                    if (cursor % 2 == 0) {
                        cursor += 1;
                    } else {
                        cursor = cursor - 1 + (OPTIONS_PER_FOLLOWER * 2);
                    }
                }
            }
        }
    }

    void Followers_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        using namespace Modules::Control;

        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Select(option, user_callback);
        } else {
            MCM::Main_t* mcm = Main();

            Array_t* followers = Followers();
            if (followers && followers->count > 0) {
                Follower_Indices_t indices = Follower_Indices(option);
                if (indices.follower > -1 && indices.follower < followers->count) {
                    Party::Follower_t* follower = static_cast<Party::Follower_t*>
                        (followers->Point(indices.follower)->Alias());
                    if (follower && follower->Is_Filled()) {
                        if (indices.option == 1) {
                            Commands_t::Self()->Summon(follower->Actor(), false);
                            mcm->Flicker(option, user_callback);
                        } else if (indices.option == 2) {
                            mcm->Disable(option);
                            struct VCallback : public Virtual_Callback_t {
                                Party::Follower_t* follower;
                                UCallback_t* user_callback;
                                VCallback(Party::Follower_t* follower, UCallback_t* user_callback) :
                                    follower(follower), user_callback(user_callback)
                                {
                                }
                                void operator()(Variable_t* result)
                                {
                                    Commands_t::Self()->Open_Pack(follower->Actor());
                                    MCM::Main_t::Self()->Return_Latent(user_callback);
                                }
                            };
                            Virtual_Callback_i* vcallback = new VCallback(follower, user_callback);
                            mcm->Close_Menus(&vcallback);
                        } else if (indices.option == 3) {
                            mcm->Disable(option);
                            if (follower->Is_Immobile()) {
                                Commands_t::Self()->Mobilize(follower->Actor());
                            } else {
                                Commands_t::Self()->Immobilize(follower->Actor());
                            }
                            mcm->Reset_Page();
                            mcm->Return_Latent(user_callback);
                        } else if (indices.option == 4) {
                            mcm->Disable(option);
                            Follower(follower);
                            Current_View(CODES::VIEW::FOLLOWERS_MEMBER);
                            MCM::Member_t::Self()->View_Followers_Member(follower->Member());
                            mcm->Reset_Page();
                            mcm->Return_Latent(user_callback);
                        } else {
                            mcm->Return_Latent(user_callback);
                        }
                    } else {
                        mcm->Return_Latent(user_callback);
                    }
                } else {
                    mcm->Return_Latent(user_callback);
                }
            } else {
                mcm->Return_Latent(user_callback);
            }
        }
    }

    void Followers_t::On_Option_Menu_Open(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Menu_Open(option);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Menu_Option_Variable()->Int()) {
                Vector_t<String_t> options;
                options.reserve(22);

                options.push_back(" Summon All ");
                options.push_back(" Summon Mobile ");
                options.push_back(" Summon Immobile ");
                options.push_back(" Stash ");
                options.push_back(" Resurrect ");
                options.push_back(" Mobilize ");
                options.push_back(" Immobilize ");
                options.push_back(" Settle ");
                options.push_back(" Resettle ");
                options.push_back(" Unsettle ");
                options.push_back(" Enthrall ");
                options.push_back(" Unthrall ");
                options.push_back(" Paralyze ");
                options.push_back(" Unparalyze ");
                options.push_back(" Sneak ");
                options.push_back(" Unsneak ");
                options.push_back(" Saddle ");
                options.push_back(" Unsaddle ");
                options.push_back(" Retreat ");
                options.push_back(" Unretreat ");
                options.push_back(" Unfollow ");
                options.push_back(" Unmember ");

                mcm->Menu_Dialog_Values(options);
            }
        }
    }

    void Followers_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Menu_Accept(option, idx);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Menu_Option_Variable()->Int()) {
                if (idx == 0) {
                    Modules::Control::Commands_t::Self()->Followers_Summon_All();
                } else if (idx == 1) {
                    Modules::Control::Commands_t::Self()->Followers_Summon_Mobile();
                } else if (idx == 2) {
                    Modules::Control::Commands_t::Self()->Followers_Summon_Immobile();
                } else if (idx == 3) {
                    Modules::Control::Commands_t::Self()->Followers_Stash();
                } else if (idx == 4) {
                    Modules::Control::Commands_t::Self()->Followers_Resurrect();
                } else if (idx == 5) {
                    Modules::Control::Commands_t::Self()->Followers_Mobilize();
                } else if (idx == 6) {
                    Modules::Control::Commands_t::Self()->Followers_Immobilize();
                } else if (idx == 7) {
                    Modules::Control::Commands_t::Self()->Followers_Settle();
                } else if (idx == 8) {
                    Modules::Control::Commands_t::Self()->Followers_Resettle();
                } else if (idx == 9) {
                    Modules::Control::Commands_t::Self()->Followers_Unsettle();
                } else if (idx == 10) {
                    Modules::Control::Commands_t::Self()->Followers_Enthrall();
                } else if (idx == 11) {
                    Modules::Control::Commands_t::Self()->Followers_Unthrall();
                } else if (idx == 12) {
                    Modules::Control::Commands_t::Self()->Followers_Paralyze();
                } else if (idx == 13) {
                    Modules::Control::Commands_t::Self()->Followers_Unparalyze();
                } else if (idx == 14) {
                    Modules::Control::Commands_t::Self()->Followers_Sneak();
                } else if (idx == 15) {
                    Modules::Control::Commands_t::Self()->Followers_Unsneak();
                } else if (idx == 16) {
                    Modules::Control::Commands_t::Self()->Followers_Saddle();
                } else if (idx == 17) {
                    Modules::Control::Commands_t::Self()->Followers_Unsaddle();
                } else if (idx == 18) {
                    Modules::Control::Commands_t::Self()->Followers_Retreat();
                } else if (idx == 19) {
                    Modules::Control::Commands_t::Self()->Followers_Unretreat();
                } else if (idx == 20) {
                    Modules::Control::Commands_t::Self()->Followers_Unfollow();
                } else if (idx == 21) {
                    Modules::Control::Commands_t::Self()->Followers_Unmember();
                }
                mcm->Reset_Page();
            }
        }
    }

    void Followers_t::On_Option_Slider_Open(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Slider_Open(option);
        }
    }

    void Followers_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Slider_Accept(option, value);
        }
    }

    void Followers_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Input_Accept(option, value);
        }
    }

    void Followers_t::On_Option_Keymap_Change(Int_t option,
                                              Int_t key_code,
                                              String_t conflict,
                                              String_t conflicting_mod,
                                              Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod, user_callback);
        } else {
            MCM::Main_t::Self()->Return_Latent(user_callback);
        }
    }

    void Followers_t::On_Option_Default(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Default(option);
        }
    }

    void Followers_t::On_Option_Highlight(Int_t option)
    {
        if (Current_View() == CODES::VIEW::FOLLOWERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Highlight(option);
        } else {
            MCM::Main_t* mcm = Main();

            if (option == Menu_Option_Variable()->Int()) {
                mcm->Info_Text("Open the menu to command all followers.");
            } else {
                Array_t* followers = Followers();
                if (followers && followers->count > 0) {
                    Follower_Indices_t indices = Follower_Indices(option);
                    if (indices.follower > -1 && indices.follower < followers->count) {
                        Party::Follower_t* follower = static_cast<Party::Follower_t*>
                            (followers->Point(indices.follower)->Alias());
                        if (follower && follower->Is_Filled()) {
                            if (indices.option == 1) {
                                mcm->Info_Text(mcm->Concat("Summon ", follower->Name(), " to you."));
                            } else if (indices.option == 2) {
                                mcm->Info_Text(mcm->Concat("Open the pack of ", follower->Name(), "."));
                            } else if (indices.option == 3) {
                                if (follower->Is_Immobile()) {
                                    mcm->Info_Text(mcm->Concat("Mobilize ", follower->Name(), "."));
                                } else {
                                    mcm->Info_Text(mcm->Concat("Immobilize ", follower->Name(), "."));
                                }
                            } else if (indices.option == 4) {
                                mcm->Info_Text(mcm->Concat("Open the follower menu of ", follower->Name(), "."));
                            }
                        }
                    }
                }
            }
        }
    }

    void Followers_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Followers_t,           \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
