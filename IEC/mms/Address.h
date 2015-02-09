//-----------------------------------------------------------------------------
// <copyright file="Address.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 20:45:10</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Address protocol element
//-----------------------------------------------------------------------------
#pragma once
#include "serialization.h"
#include "VisibleString.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Address structure
             ****************************************/
            struct Address
            {
                /************************************//**
                 * \brief Choice
                 ****************************************/
                enum: char{
                    id_numeric_address,
                    id_symbolic_address,
                    id_unconstrained_address
                } choice;
                int numericAddress;
                MMS::DataTypes::VisibleStringBuffer     symbolicAddress;
                MMS::DataTypes::OctetStringBuffer       unconstrainedAddress;
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Elements::Address;

        PDU_IMPLICIT_FIELD(Address, 0, Address::numericAddress);
        PDU_IMPLICIT_FIELD(Address, 1, Address::symbolicAddress);
        PDU_IMPLICIT_FIELD(Address, 2, Address::unconstrainedAddress);

    }
}

