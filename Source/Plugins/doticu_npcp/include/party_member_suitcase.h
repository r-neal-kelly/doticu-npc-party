/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/reference.h"

#include "intrinsic.h"
#include "party_member_suit_type.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Suitcase_t :
        public Reference_t
    {
    public:
        class Suit_Entry_t
        {
        public:
            some<Bound_Object_t*>           bound_object;
            Vector_t<some<Extra_List_t*>>   copies;

        public:
            Suit_Entry_t(some<Bound_Object_t*> bound_object);
            Suit_Entry_t(some<Bound_Object_t*> bound_object, Vector_t<some<Extra_List_t*>> copies);
            Suit_Entry_t(const Suit_Entry_t& other)                                                 = delete;
            Suit_Entry_t(Suit_Entry_t&& other) noexcept;
            Suit_Entry_t& operator =(const Suit_Entry_t& other)                                     = delete;
            Suit_Entry_t& operator =(Suit_Entry_t&& other) noexcept                                 = delete;
            ~Suit_Entry_t();

        public:
            Bool_t  Has_Copies();
            Bool_t  Destroy_Copy_If_Equals(some<Extra_List_t*> extra_list);

            void    Add_Copy(some<Extra_List_t*> original, s16 count, maybe<Outfit_t*> outfit);

        public:
            void    Log(std::string indent = "");
        };

        class Suit_Entries_t
        {
        public:
            Vector_t<Suit_Entry_t> entries;

        public:
            Suit_Entries_t();
            Suit_Entries_t(Vector_t<Suit_Entry_t> entries);
            Suit_Entries_t(const Suit_Entries_t& other)                 = delete;
            Suit_Entries_t(Suit_Entries_t&& other) noexcept;
            Suit_Entries_t& operator =(const Suit_Entries_t& other)     = delete;
            Suit_Entries_t& operator =(Suit_Entries_t&& other) noexcept = delete;
            ~Suit_Entries_t();

        public:
            Bool_t                  Has_Copies();

            size_t                  Count();

            maybe<Suit_Entry_t*>    Maybe_Entry(some<Bound_Object_t*> bound_object);
            some<Suit_Entry_t*>     Some_Entry(some<Bound_Object_t*> bound_object);
        };

        class Filter_Out_Blank_Objects_t :
            public Filter_i<some<Bound_Object_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object) override;
        };

        class Filter_Out_Token_Objects_t :
            public Filter_i<some<Bound_Object_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object) override;
        };

        class Filter_Out_Unplayable_Objects_t :
            public Filter_i<some<Bound_Object_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object) override;
        };

        class Filter_Out_Blank_Or_Token_Objects_t :
            public Filter_i<some<Bound_Object_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object) override;
        };

        class Filter_Out_Blank_Or_Token_Or_Unplayable_Objects_t :
            public Filter_i<some<Bound_Object_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object) override;
        };

        class Filter_Out_No_Extra_Lists_t :
            public Filter_i<some<Bound_Object_t*>, some<Extra_List_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object, some<Extra_List_t*> x_list) override;
        };

        class Filter_Out_Quest_Extra_Lists_t :
            public Filter_i<some<Bound_Object_t*>, some<Extra_List_t*>>
        {
        public:
            virtual Bool_t operator ()(some<Bound_Object_t*> object, some<Extra_List_t*> x_list) override;
        };

    public:
        static Filter_Out_Blank_Objects_t                           filter_out_blank_objects;
        static Filter_Out_Token_Objects_t                           filter_out_token_objects;
        static Filter_Out_Unplayable_Objects_t                      filter_out_unplayable_objects;
        static Filter_Out_Blank_Or_Token_Objects_t                  filter_out_blank_or_token_objects;
        static Filter_Out_Blank_Or_Token_Or_Unplayable_Objects_t    filter_out_blank_or_token_or_unplayable_objects;
        static Filter_Out_No_Extra_Lists_t                          filter_out_no_extra_lists;
        static Filter_Out_Quest_Extra_Lists_t                       filter_out_quest_extra_lists;

    public:
        static some<Member_Suitcase_t*> Create();
        static void                     Destroy(some<Member_Suitcase_t*> suitcase);

    public:
        Bool_t  Has_Inactive_Outfit_Item(some<Actor_t*> actor);
        void    Destroy_Inactive_Outfit_Items(some<Actor_t*> actor);

    public:
        void    Copy_Suit_From(some<Member_Suit_Type_e> suit, some<Reference_t*> from);
        void    Move_Suit_From(some<Member_Suit_Type_e> suit, some<Reference_t*> from);
        void    Move_Suit_To(some<Member_Suit_Type_e> suit, maybe<Reference_t*> to);
        void    Move_All_Suits_To(maybe<Reference_t*> to);

    public:
        Suit_Entries_t  Active_Suit_Entries(some<Member_Suit_Type_e> suit_type,
                                            maybe<Outfit_t*> outfit,
                                            Bool_t only_playables);

        void            Apply_Suit(some<Member_Suit_Type_e> suit,
                                   some<Actor_t*> actor,
                                   Bool_t only_playables,
                                   Bool_t remove_non_suit_items,
                                   maybe<Reference_t*> non_suit_destination);
    };

}}
