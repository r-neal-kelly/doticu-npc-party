/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_member.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_mannequins.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Mannequins_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_mannequins");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Mannequins_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Mannequins_t* Mannequins_t::Self()
    {
        return static_cast<Mannequins_t*>(Consts::Control_Quest());
    }

    Object_t* Mannequins_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Mannequins_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Mannequins_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Mannequins_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }

    Variable_t* Mannequins_t::Page_Index_Variable() { DEFINE_VARIABLE("p_idx_page"); }
    Variable_t* Mannequins_t::Page_Count_Variable() { DEFINE_VARIABLE("p_num_pages"); }

    Variable_t* Mannequins_t::Current_Column_Variable() { DEFINE_VARIABLE("p_curr_column"); }
    Variable_t* Mannequins_t::Current_Row_Variable() { DEFINE_VARIABLE("p_curr_row"); }

    Variable_t* Mannequins_t::Members_Variable() { DEFINE_VARIABLE("p_curr_members"); }
    Variable_t* Mannequins_t::Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }

    Variable_t* Mannequins_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Mannequins_t::Enter_Option_Variable() { DEFINE_VARIABLE("p_option_enter"); }
    Variable_t* Mannequins_t::Exit_Option_Variable() { DEFINE_VARIABLE("p_option_exit"); }
    Variable_t* Mannequins_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_prev"); }
    Variable_t* Mannequins_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }
    Variable_t* Mannequins_t::Name_Option_Variable() { DEFINE_VARIABLE("p_option_name"); }
    Variable_t* Mannequins_t::Back_Option_Variable() { DEFINE_VARIABLE("p_option_back"); }
    Variable_t* Mannequins_t::North_1_Option_Variable() { DEFINE_VARIABLE("p_option_north_1"); }
    Variable_t* Mannequins_t::North_2_Option_Variable() { DEFINE_VARIABLE("p_option_north_2"); }
    Variable_t* Mannequins_t::West_Option_Variable() { DEFINE_VARIABLE("p_option_west"); }
    Variable_t* Mannequins_t::East_Option_Variable() { DEFINE_VARIABLE("p_option_east"); }
    Variable_t* Mannequins_t::South_1_Option_Variable() { DEFINE_VARIABLE("p_option_south_1"); }
    Variable_t* Mannequins_t::South_2_Option_Variable() { DEFINE_VARIABLE("p_option_south_2"); }

    Int_t Mannequins_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Mannequins_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    Int_t Mannequins_t::Page_Index()
    {
        return Page_Index_Variable()->Int();
    }

    void Mannequins_t::Page_Index(Int_t page_idx)
    {
        Page_Index_Variable()->Int(page_idx);
    }

    Int_t Mannequins_t::Page_Count()
    {
        return Page_Count_Variable()->Int();
    }

    void Mannequins_t::Page_Count(Int_t page_count)
    {
        Page_Count_Variable()->Int(page_count);
    }

    Int_t Mannequins_t::Current_Column()
    {
        return Current_Column_Variable()->Int();
    }

    void Mannequins_t::Current_Column(Int_t column)
    {
        Current_Column_Variable()->Int(column);
    }

    Int_t Mannequins_t::Current_Row()
    {
        return Current_Row_Variable()->Int();
    }

    void Mannequins_t::Current_Row(Int_t row)
    {
        Current_Row_Variable()->Int(row);
    }

    Array_t* Mannequins_t::Members()
    {
        return Members_Variable()->Array();
    }

    void Mannequins_t::Members(Vector_t<Party::Member_t*> members)
    {
        Members_Variable()->Pack(members);
    }

    Party::Member_t* Mannequins_t::Member()
    {
        return static_cast<Party::Member_t*>(Member_Variable()->Alias());
    }

    void Mannequins_t::Member(Party::Member_t* member)
    {
        Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    void Mannequins_t::View_Mannequins()
    {
        Int_t current_view = Current_View();
        if (current_view != CODES::VIEW::MANNEQUINS_CELL &&
            current_view != CODES::VIEW::MANNEQUINS_MEMBER) {
            Current_View(CODES::VIEW::MANNEQUINS);
        }
    }

    void Mannequins_t::Review_Mannequins()
    {
        Current_View(CODES::VIEW::MANNEQUINS_CELL);
        Member(nullptr);
    }

    Int_t Mannequins_t::Option_To_Column(Int_t option)
    {
        NPCP_ASSERT(Current_View() == CODES::VIEW::MANNEQUINS);

        /*
            Page 0
            0 == 1, 1 == 2
            2 == 1, 3 == 2
            4 == 1, 5 == 2
            ...
            Page 1
            0 == 3, 1 == 4
            2 == 3, 3 == 4
            4 == 3, 5 == 4
            ...
        */

        Int_t normal = option - Options_Offset_Variable()->Int() - MANNEQUINS_HEADERS;
        if (normal % 2 == 0) {
            return (Page_Index() * COLUMNS_PER_PAGE) + 1;
        } else {
            return (Page_Index() * COLUMNS_PER_PAGE) + 2;
        }
    }

    Int_t Mannequins_t::Option_To_Row(Int_t option)
    {
        NPCP_ASSERT(Current_View() == CODES::VIEW::MANNEQUINS);

        /*
            0 == 8, 1 == 8
            2 == 7, 3 == 7
            4 == 6, 5 == 6
            ...
        */

        Int_t normal = option - Options_Offset_Variable()->Int() - MANNEQUINS_HEADERS;
        return 8 - floorf(static_cast<Float_t>(normal) / 2);
    }

    Party::Member_t* Mannequins_t::Option_To_Member(Int_t option)
    {
        NPCP_ASSERT(Current_View() == CODES::VIEW::MANNEQUINS_CELL);

        /*
            0 == 7, 1 == 15
            2 == 6, 3 == 14
            4 == 5, 5 == 13
            ...
        */

        Int_t normal = option - Options_Offset_Variable()->Int() - MANNEQUINS_CELL_HEADERS;
        Int_t member_idx = 8 - (floorf(static_cast<Float_t>(normal) / 2) + 1);
        if (normal % 2 == 1) {
            member_idx += 8;
        }

        Array_t* members = Members();
        NPCP_ASSERT(members);
        if (member_idx > 0 && member_idx < members->count) {
            return static_cast<Party::Member_t*>
                (members->Point(member_idx)->Alias());
        } else {
            return nullptr;
        }
    }

    void Mannequins_t::On_Build_Page()
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {
            Party::Mannequins_t* mannequins = Party::Mannequins_t::Self();
            MCM::Main_t* mcm = Main();

            Int_t page_count = ceil(static_cast<Float_t>(Party::Mannequins_t::COLUMNS) / COLUMNS_PER_PAGE);
            Page_Count(page_count);

            Int_t page_index = Page_Index();
            if (page_index < 0) {
                page_index = page_count - 1;
                Page_Index(page_index);
            } else if (page_index >= page_count) {
                page_index = 0;
                Page_Index(page_index);
            }

            // Title
            mcm->Title_Text(
                (std::string("Mannequins: ") +
                 std::to_string(mannequins->Count_Expoees()) + "/" +
                 std::to_string(Party::Mannequins_t::SLOTS) +
                 "               " +
                 std::string("Page: ") +
                 std::to_string(page_index + 1) + "/" +
                 std::to_string(page_count)).c_str()
            );

            // Header
            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);
            if (mannequins->Is_Player_In_Expo()) {
                Enter_Option_Variable()->Int(
                    mcm->Add_Text_Option("                      Enter Antechamber", "", MCM::DISABLE)
                );
                Exit_Option_Variable()->Int(
                    mcm->Add_Text_Option("                            Exit Expo", "", MCM::NONE)
                );
            } else {
                Enter_Option_Variable()->Int(
                    mcm->Add_Text_Option("                      Enter Antechamber", "", MCM::NONE)
                );
                Exit_Option_Variable()->Int(
                    mcm->Add_Text_Option("                            Exit Expo", "", MCM::DISABLE)
                );
            }
            if (Party::Mannequins_t::COLUMNS > COLUMNS_PER_PAGE) {
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
            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");
            Options_Offset_Variable()->Int(Enter_Option_Variable()->Int());

            // Body
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
            Int_t column = (page_index * COLUMNS_PER_PAGE) + 1;
            Int_t column_end = column + COLUMNS_PER_PAGE;
            if (column_end > Party::Mannequins_t::COLUMNS + 1) {
                column_end = Party::Mannequins_t::COLUMNS + 1;
            }
            for (; column < column_end; column += 1) {
                if (column % 2 == 0) {
                    mcm->Cursor_Position(MANNEQUINS_HEADERS + 1);
                } else {
                    mcm->Cursor_Position(MANNEQUINS_HEADERS);
                }
                for (Int_t row = Party::Mannequins_t::ROWS; row > 0; row -= 1) {
                    String_t cell_name = mannequins->Cell_Name(column, row);
                    if (cell_name && cell_name.data && cell_name.data[0]) {
                        std::string label =
                            std::string("C ") + std::to_string(column) +
                            ", R " + std::to_string(row) +
                            ": " + cell_name.data;
                        mcm->Add_Text_Option(label.c_str(), "...");
                    } else {
                        std::string label =
                            std::string("Column ") + std::to_string(column) +
                            ", Row " + std::to_string(row);
                        mcm->Add_Text_Option(label.c_str(), "...");
                    }
                }
                mcm->Add_Header_Option("");
            }
        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {
            Party::Mannequins_t* mannequins = Party::Mannequins_t::Self();
            MCM::Main_t* mcm = Main();
            Int_t current_column = Current_Column();
            Int_t current_row = Current_Row();
            Members(Party::Mannequins_t::Self()->Expoees(current_column, current_row));

            // Title
            mcm->Title_Text(
                (std::string("Mannequins: C ") + std::to_string(current_column) +
                 ", R " + std::to_string(current_row)).c_str()
            );

            // Header
            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);
            Name_Option_Variable()->Int(
                mcm->Add_Input_Option(mannequins->Cell_Name(current_column, current_row), " Detail ")
            );
            Back_Option_Variable()->Int(
                mcm->Add_Text_Option("                              Go Back", "")
            );
            Enter_Option_Variable()->Int(
                mcm->Add_Text_Option("                              Enter Cell", "")
            );
            if (mannequins->Is_Player_In_Expo()) {
                Exit_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              Exit Expo", "", MCM::NONE)
                );
            } else {
                Exit_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              Exit Expo", "", MCM::DISABLE)
                );
            }
            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");
            Options_Offset_Variable()->Int(Name_Option_Variable()->Int());

            // Body
            Array_t* members = Members();
            NPCP_ASSERT(members);
            mcm->Cursor_Position(MANNEQUINS_CELL_HEADERS + 1);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
            for (size_t idx = 16; idx > 8;) {
                idx -= 1;
                Party::Member_t* member = static_cast<Party::Member_t*>
                    (members->Point(idx)->Alias());
                if (member) {
                    mcm->Add_Text_Option(member->Name(), "");
                } else {
                    mcm->Add_Text_Option("EMPTY ", "", MCM::DISABLE);
                }
            }
            mcm->Cursor_Position(MANNEQUINS_CELL_HEADERS);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
            for (size_t idx = 8; idx > 0;) {
                idx -= 1;
                Party::Member_t* member = static_cast<Party::Member_t*>
                    (members->Point(idx)->Alias());
                if (member) {
                    mcm->Add_Text_Option(member->Name(), "");
                } else {
                    mcm->Add_Text_Option("EMPTY ", "", MCM::DISABLE);
                }
            }

            // Footer
            mcm->Cursor_Position(MANNEQUINS_CELL_HEADERS + (Party::Mannequins_t::ROWS * 2));
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);
            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");
            if (current_row < Party::Mannequins_t::ROWS) {
                North_1_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              North", "")
                );
                North_2_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              North", "")
                );
            } else {
                North_1_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              North", "", MCM::DISABLE)
                );
                North_2_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              North", "", MCM::DISABLE)
                );
            }
            if (current_column > 1) {
                West_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              West", "")
                );
            } else {
                West_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              West", "", MCM::DISABLE)
                );
            }
            if (current_column < Party::Mannequins_t::COLUMNS) {
                East_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              East", "")
                );
            } else {
                East_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              East", "", MCM::DISABLE)
                );
            }
            if (current_row > 1) {
                South_1_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              South", "")
                );
                South_2_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              South", "")
                );
            } else {
                South_1_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              South", "", MCM::DISABLE)
                );
                South_2_Option_Variable()->Int(
                    mcm->Add_Text_Option("                              South", "", MCM::DISABLE)
                );
            }
        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            Party::Member_t* member = Member();
            if (member && member->Is_Filled() && member->Is_Mannequin() && Members()->Find(Party::Member_t::kTypeID, member) > -1) {
                MCM::Member_t* mcm_member = MCM::Member_t::Self();
                mcm_member->View_Mannequins_Member(member);
                mcm_member->On_Build_Page();
            } else {
                Review_Mannequins();
                On_Build_Page();
            }
        }
    }

    void Mannequins_t::On_Option_Select(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {
            MCM::Main_t* mcm = Main();
            if (option == Enter_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct VCallback : public Virtual_Callback_t {
                    void operator()(Variable_t* result)
                    {
                        Party::Mannequins_t::Self()->Move_Player_To_Antechamber();
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback();
                mcm->Close_Menus(&vcallback);
            } else if (option == Exit_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct VCallback : public Virtual_Callback_t {
                    void operator()(Variable_t* result)
                    {
                        Party::Mannequins_t::Self()->Remove_Player();
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback();
                mcm->Close_Menus(&vcallback);

            } else if (option == Previous_Option_Variable()->Int()) {
                mcm->Disable(option);
                Int_t page_index = Page_Index();
                if (page_index == 0) {
                    Page_Index(Page_Count() - 1);
                } else {
                    Page_Index(page_index - 1);
                }
                mcm->Reset_Page();
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Disable(option);
                Int_t page_index = Page_Index();
                if (page_index == Page_Count() - 1) {
                    Page_Index(0);
                } else {
                    Page_Index(page_index + 1);
                }
                mcm->Reset_Page();

            } else {
                Int_t column = Option_To_Column(option);
                Int_t row = Option_To_Row(option);
                Current_View(CODES::VIEW::MANNEQUINS_CELL);
                Current_Column(column);
                Current_Row(row);
                mcm->Disable(option);
                mcm->Reset_Page();
            }
        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {
            MCM::Main_t* mcm = Main();
            if (option == Back_Option_Variable()->Int()) {
                Current_View(CODES::VIEW::MANNEQUINS);
                mcm->Disable(option);
                mcm->Reset_Page();
            } else if (option == Enter_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct VCallback : public Virtual_Callback_t {
                    MCM::Mannequins_t* self;
                    VCallback(MCM::Mannequins_t* self) :
                        self(self)
                    {
                    }
                    void operator()(Variable_t* result)
                    {
                        Party::Mannequins_t::Self()->Move_Player_To_Cell(self->Current_Column(), self->Current_Row());
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback(this);
                mcm->Close_Menus(&vcallback);
            } else if (option == Exit_Option_Variable()->Int()) {
                mcm->Disable(option);
                struct VCallback : public Virtual_Callback_t {
                    void operator()(Variable_t* result)
                    {
                        Party::Mannequins_t::Self()->Remove_Player();
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback();
                mcm->Close_Menus(&vcallback);
            } else if (option == North_1_Option_Variable()->Int() || option == North_2_Option_Variable()->Int()) {
                Current_Row(Current_Row() + 1);
                mcm->Disable(option);
                mcm->Reset_Page();
            } else if (option == West_Option_Variable()->Int()) {
                Current_Column(Current_Column() - 1);
                mcm->Disable(option);
                mcm->Reset_Page();
            } else if (option == East_Option_Variable()->Int()) {
                Current_Column(Current_Column() + 1);
                mcm->Disable(option);
                mcm->Reset_Page();
            } else if (option == South_1_Option_Variable()->Int() || option == South_2_Option_Variable()->Int()) {
                Current_Row(Current_Row() - 1);
                mcm->Disable(option);
                mcm->Reset_Page();
            } else {
                Member(Option_To_Member(option));
                Current_View(CODES::VIEW::MANNEQUINS_MEMBER);
                mcm->Disable(option);
                mcm->Reset_Page();
            }
        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Select(option);
        }
    }

    void Mannequins_t::On_Option_Menu_Open(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Menu_Open(option);
        }
    }

    void Mannequins_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Menu_Accept(option, idx);
        }
    }

    void Mannequins_t::On_Option_Slider_Open(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Slider_Open(option);
        }
    }

    void Mannequins_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Slider_Accept(option, value);
        }
    }

    void Mannequins_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {
            MCM::Main_t* mcm = Main();
            if (option == Name_Option_Variable()->Int()) {
                Party::Mannequins_t::Self()->Cell_Name(Current_Column(), Current_Row(), value);
                mcm->Reset_Page();
            }
        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Input_Accept(option, value);
        }
    }

    void Mannequins_t::On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        }
    }

    void Mannequins_t::On_Option_Default(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {

        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Default(option);
        }
    }

    void Mannequins_t::On_Option_Highlight(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MANNEQUINS) {
            MCM::Main_t* mcm = Main();

            if (option == Enter_Option_Variable()->Int()) {
                mcm->Info_Text("Teleport to the Expo Antechamber.");
            } else if (option == Exit_Option_Variable()->Int()) {
                mcm->Info_Text("Teleport back to Tamriel.");
            } else if (option == Previous_Option_Variable()->Int()) {
                mcm->Info_Text("Open the previous page of Expo columns.");
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Info_Text("Open the next page of Expo columns.");
            } else {
                mcm->Info_Text(
                    (std::string("Open the menu for Column ") + std::to_string(Option_To_Column(option)) +
                     ", Row " + std::to_string(Option_To_Row(option)) + "."
                     ).c_str()
                );
            }
        } else if (current_view == CODES::VIEW::MANNEQUINS_CELL) {
            /*
function f_On_Option_Highlight(int id_option)
    if false

    elseIf id_option == p_option_back
        MCM.SetInfoText("Go back to main Mannequins menu.")
    elseIf id_option == p_option_enter
        MCM.SetInfoText("Teleport to Expo C " + p_curr_column + ", R" + p_curr_row + ".")
    elseIf id_option == p_option_exit
        MCM.SetInfoText("Teleport back to Tamriel.")
    elseIf id_option == p_option_north_1 || id_option == p_option_north_2
        MCM.SetInfoText("Move the menu NORTH one cell, in relation to the position of this cell.")
    elseIf id_option == p_option_south_1 || id_option == p_option_south_2
        MCM.SetInfoText("Move the menu SOUTH one cell, in relation to the position of this cell.")
    elseIf id_option == p_option_west
        MCM.SetInfoText("Move the menu WEST one cell, in relation to the position of this cell.")
    elseIf id_option == p_option_east
        MCM.SetInfoText("Move the menu EAST one cell, in relation to the position of this cell.")
    else
        doticu_npcp_member ref_member = p_curr_members[p_Get_Idx_Entity(id_option)] as doticu_npcp_member
        if ref_member
            MCM.SetInfoText("Open the mannequin menu for " + ref_member.Name() + ".\n" + MCM.MCM_MEMBERS.Member_Info_String(ref_member as Alias))
        endIf

    endIf
endFunction
            */
        } else if (current_view == CODES::VIEW::MANNEQUINS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Highlight(option);
        }
    }

    void Mannequins_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Mannequins_t,          \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("View_Mannequins", 0, void, View_Mannequins);

        METHOD("On_Build_Page", 0, void, On_Build_Page);
        METHOD("On_Option_Select", 1, void, On_Option_Select, Int_t);
        METHOD("On_Option_Menu_Open", 1, void, On_Option_Menu_Open, Int_t);
        METHOD("On_Option_Menu_Accept", 2, void, On_Option_Menu_Accept, Int_t, Int_t);
        METHOD("On_Option_Slider_Open", 1, void, On_Option_Slider_Open, Int_t);
        METHOD("On_Option_Slider_Accept", 2, void, On_Option_Slider_Accept, Int_t, Float_t);
        METHOD("On_Option_Input_Accept", 2, void, On_Option_Input_Accept, Int_t, String_t);
        METHOD("On_Option_Keymap_Change", 4, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        METHOD("On_Option_Default", 1, void, On_Option_Default, Int_t);
        METHOD("On_Option_Highlight", 1, void, On_Option_Highlight, Int_t);

        #undef METHOD
    }

}}}
