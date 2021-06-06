/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_point.h"

#include "intrinsic.h"
#include "party_settler_radius.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Marker_t
    {
    public:
        maybe<Form_t*>  interior_cell_or_worldspace;
        NI_Point_3_t    position;
        NI_Point_3_t    rotation;

    public:
        Settler_Marker_t();
        Settler_Marker_t(const Settler_Marker_t& other);
        Settler_Marker_t(Settler_Marker_t&& other) noexcept;
        Settler_Marker_t& operator =(const Settler_Marker_t& other);
        Settler_Marker_t& operator =(Settler_Marker_t&& other) noexcept;
        ~Settler_Marker_t();

    public:
        void    Write(std::ofstream& file);
        void    Read(std::ifstream& file);

    public:
        Bool_t  Is_Valid();

    public:
        explicit operator   Bool_t();
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Settler_Marker_t> :
        public doticu_npcp::Settler_Marker_t
    {
    public:
        using Settler_Marker_t::Settler_Marker_t;
    };

    template <>
    class maybe<doticu_npcp::Settler_Marker_t> :
        public doticu_npcp::Settler_Marker_t
    {
    public:
        using Settler_Marker_t::Settler_Marker_t;
    };

    template <>
    class some<doticu_npcp::Settler_Marker_t> :
        public doticu_npcp::Settler_Marker_t
    {
    public:
        using Settler_Marker_t::Settler_Marker_t;
    };

}
