//-----------------------------------------------------------------------------
// <copyright file="IdentifyResponse.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 20:30:35</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Identify response type
//-----------------------------------------------------------------------------
#pragma once
#include "VisibleString.h"
#include "serialization.h"
namespace MMS
{
    namespace PDU
    {
        namespace Confirmed
        {
            /************************************//**
             * \brief Identify-response type
             *
             * \details Represents identify response type
             *
             * \note OIDs are not supported yet therefore listOfAbstractSyntaxes is commented out
             *
             ****************************************/
            template <class St>
            struct IdentifyResponse
            {
                MMS::DataTypes::VisibleString<St> vendorName;
                MMS::DataTypes::VisibleString<St> modelName;
                MMS::DataTypes::VisibleString<St> revision;
                // listOfAbstractSyntaxes
            };
        }
    }
    namespace serialization
    {
        using MMS::PDU::Confirmed::IdentifyResponse;

        template <class St>
        T_PDU_IMPLICIT_FIELD(IdentifyResponse<St>, 0, IdentifyResponse<St>::vendorName);
        template <class St>
        T_PDU_IMPLICIT_FIELD(IdentifyResponse<St>, 1, IdentifyResponse<St>::modelName);
        template <class St>
        T_PDU_IMPLICIT_FIELD(IdentifyResponse<St>, 2, IdentifyResponse<St>::revision);

    }

}

