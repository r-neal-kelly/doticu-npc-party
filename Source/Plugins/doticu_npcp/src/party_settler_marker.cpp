/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_point.h"

#include "npcp.inl"
#include "party_settler_marker.h"

namespace doticu_skylib { namespace doticu_npcp {

    Settler_Marker_t::Settler_Marker_t() :
        interior_cell_or_worldspace(none<Form_t*>()),
        position(),
        rotation()
    {
    }

    Settler_Marker_t::Settler_Marker_t(const Settler_Marker_t& other) :
        interior_cell_or_worldspace(other.interior_cell_or_worldspace),
        position(other.position),
        rotation(other.rotation)
    {
    }

    Settler_Marker_t::Settler_Marker_t(Settler_Marker_t&& other) noexcept :
        interior_cell_or_worldspace(std::move(other.interior_cell_or_worldspace)),
        position(std::move(other.position)),
        rotation(std::move(other.rotation))
    {
    }

    Settler_Marker_t& Settler_Marker_t::operator =(const Settler_Marker_t& other)
    {
        if (this != std::addressof(other)) {
            this->interior_cell_or_worldspace = other.interior_cell_or_worldspace;
            this->position = other.position;
            this->rotation = other.rotation;
        }
        return *this;
    }

    Settler_Marker_t& Settler_Marker_t::operator =(Settler_Marker_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->interior_cell_or_worldspace = std::move(other.interior_cell_or_worldspace);
            this->position = std::move(other.position);
            this->rotation = std::move(other.rotation);
        }
        return *this;
    }

    Settler_Marker_t::~Settler_Marker_t()
    {
    }

    void Settler_Marker_t::Write(std::ofstream& file)
    {
        NPCP.Write_Form(file, this->interior_cell_or_worldspace);
        NPCP.Write(file, this->position);
        NPCP.Write(file, this->rotation);
    }

    void Settler_Marker_t::Read(std::ifstream& file)
    {
        NPCP.Read_Form(file, this->interior_cell_or_worldspace);
        NPCP.Read(file, this->position);
        NPCP.Read(file, this->rotation);
    }

    Bool_t Settler_Marker_t::Is_Valid() const
    {
        return this->interior_cell_or_worldspace != none<Form_t*>();
    }

    Settler_Marker_t::operator Bool_t() const
    {
        return Is_Valid();
    }

}}
