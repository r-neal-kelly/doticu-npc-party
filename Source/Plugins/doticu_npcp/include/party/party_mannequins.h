/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_aliases.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    /*
    
        Formlist Structure:
        ------------    ------------
        |  23  31  |    |  55  63  |
        |  22  30  |    |  54  62  |
        |  21  29  |    |  53  61  |
        |  20  28  |    |  52  60  |
        |          |    |          |
        |  19  27  |    |  51  59  |
        |  18  26  |    |  50  58  |
        |  17  25  |    |  49  57  |
        |  16  24  |    |  48  56  |
        |c1        |    |c2        |
        |  r2      |    |  r2      |
        ------------    ------------
        ------------    ------------
        |   7  15  |    |  39  47  |
        |   6  14  |    |  38  46  |
        |   5  13  |    |  37  45  |
        |   4  12  |    |  36  44  |
        |          |    |          |
        |   3  11  |    |  35  43  |
        |   2  10  |    |  34  42  |
        |   1   9  |    |  33  41  |
        |   0   8  |    |  32  40  |
        |c1        |    |c2        |
        |  r1      |    |  r1      |
        ------------    ------------

        * Pattern extends to a total of 8 rows.
        * Columns can be added in the future, but not rows.
    
    */

    class Member_t;

    class Mannequins_t : public Aliases_t {
    public:
        static constexpr size_t COLUMNS             = 8;
        static constexpr size_t ROWS                = 8;
        static constexpr size_t SLOTS_PER_CELL      = 16;
        static constexpr size_t CELLS               = COLUMNS * ROWS;
        static constexpr size_t SLOTS               = SLOTS_PER_CELL * ROWS * COLUMNS;
        static constexpr size_t SLOTS_PER_COLUMN    = SLOTS_PER_CELL * ROWS;

    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Mannequins_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Slots_Array_Variable();
        Variable_t* Cell_Names_Array_Variable();
        Variable_t* Go_Back_Marker_Variable();

        Array_t* Slots_Array();
        Array_t* Cell_Names_Array();
        Reference_t* Go_Back_Marker();
        void Go_Back_Marker(Reference_t* marker);

        void Initialize();
        void Uninitialize();
        void Reinitialize();

        Bool_t Has_Expoee(Int_t expoee_id);
        Bool_t Hasnt_Expoee(Int_t expoee_id);
        Bool_t Is_Member_In_Expo(Member_t* member);
        Bool_t Is_Player_In_Expo();

        Int_t Max_Expoees();
        Int_t Count_Expoees();

        void Expo(Int_t expoee_id, Reference_t* marker, void (*callback)(Int_t code, const char* name));
        void Unexpo(Int_t expoee_id, void (*callback)(Int_t code, const char* name));

        void Enforce_Expoee(Int_t expoee_id, Reference_t* marker);

        void Normalize_Coords(Int_t& column, Int_t& row);

        Vector_t<Member_t*> Expoees(Int_t column, Int_t row);
        String_t Cell_Name(Int_t column, Int_t row);
        void Cell_Name(Int_t column, Int_t row, String_t name);

        void Move_Player_To_Cell(Int_t column, Int_t row);
        void Move_Player_To_Antechamber();
        void Remove_Player();

        void Update_Go_Back_Marker(Member_t* member);
        void Try_To_Set_Go_Back_Marker();
        void Try_To_Unset_Go_Back_Marker();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
