//-----------------------------------------------------------------------------
// <copyright file="Status.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 08:45:06</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Status request and status response declarations
//-----------------------------------------------------------------------------
#pragma once
#include "VarSizeBitString.h"
#include "serialization.h"
namespace MMS
{
	namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Status request is simply a boolean
             ****************************************/
            typedef bool Status_Request;
            /************************************//**
             * \brief Status response sequence declaration
             ****************************************/
            struct Status_Response
            {
                /************************************//**
                 * \brief VMD Logical Status
                 *
                 * \details Mandatory field
                 *
                 ****************************************/
                enum : int
                {	
                    state_changes_allowed=0,
                    no_state_changes_allowed=1,
                    limited_services_allowed=2,
                    support_services_allowed=3
                } vmdLogicalStatus;
                /************************************//**
                 * \brief VMD Physical status
                 *
                 * \details Mandatory field
                 *
                 ****************************************/
                enum : int
                {
                    operational,
                    partially_operational,
                    inoperable,
                    needs_comissioning
                } vmdPhysicalStatus;

                /************************************//**
                 * \brief Local details bit string
                 *
                 * \details allows for up to 128 bits. Optional field
                 *
                 ****************************************/
                MMS::DataTypes::VarSizeBitString localDetail;
            };
        }
    }
    namespace serialization
    {
        using MMS::PDU::Elements::Status_Response;

        PDU_IMPLICIT_FIELD(Status_Response, 0, Status_Response::vmdLogicalStatus);
        PDU_IMPLICIT_FIELD(Status_Response, 1, Status_Response::vmdPhysicalStatus);
        PDU_OPT_IMPLICIT_FIELD(Status_Response, 2, Status_Response::localDetail);

    }
}

