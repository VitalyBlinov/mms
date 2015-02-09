//-----------------------------------------------------------------------------
// <copyright file="InitiateRequestPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/10 03:42:10</created>
// <author>Vital</author>
// <summary>IEC project</summary>
// Initiate-Request PDU type definition and serialization sequence
//-----------------------------------------------------------------------------
#pragma once
#include "EmitContext.h"
#include "LengthEmitter.h"
#include "IntegerEmitter.h"
#include "IntegerExtractor.h"
#include "LengthExtractor.h"
#include "serialization.h"
#include "InitiateRequestDetail.h"
namespace MMS
{
    /***********************************
     * \brief Protocol PDUs structures' definitions
     ****************************************/
    namespace PDU
    {
         /************************************//**
         * \brief Initiate-request PDU
         *
         * \details For more details, refer to MMS standard
         *
         ****************************************/
        struct InitiateRequest
        {
        public:
            typedef Elements::InitiateRequestDetail InitRequestDetail;
            ///	\brief InitiateRequestPDU constructor
            InitiateRequest();
            
            int localDetailCalling;                                     ///< Local detail calling. Optional field
            short proposedMaxServicesOutstandingCalling;                ///< Proposed Max Services Outstanding Calling
            short proposedMaxServicesOutstandingCalled;                 ///< Proposed Max services Outstanding Called
            char proposedDataStructureNestingLevel;                     ///< Proposed structure nesting level. Optional.
            InitRequestDetail initiateRequestDetails;                   ///< Initiate request details
        };
    }


    namespace serialization
    {
        using MMS::PDU::InitiateRequest;

        PDU_OPT_FIELD(InitiateRequest, 0, InitiateRequest::localDetailCalling);
        PDU_FIELD(InitiateRequest, 1, InitiateRequest::proposedMaxServicesOutstandingCalling);
        PDU_FIELD(InitiateRequest, 2, InitiateRequest::proposedMaxServicesOutstandingCalled);
        PDU_OPT_FIELD(InitiateRequest, 3, InitiateRequest::proposedDataStructureNestingLevel);
        PDU_IMPLICIT_FIELD(InitiateRequest, 4, InitiateRequest::initiateRequestDetails);
    }
}

