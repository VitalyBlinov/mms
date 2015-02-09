//-----------------------------------------------------------------------------
// <copyright file="InitiateResponsePDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/15 12:08:32</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "InitiateRequestDetail.h"
namespace MMS
{
    namespace PDU
    {
        /************************************//**
         * \brief Initiate-Response PDU
         ****************************************/
        struct InitiateResponse
        {
            enum PDU_TAG
            {
                tag = 0xa9
            };
            ///	\brief InitiateResponsePDU constructor
            InitiateResponse();


            typedef Elements::InitiateRequestDetail InitRequestDetail;

            int localDetailCalling;                                         ///< Local detail calling. Optional field
            short negotiatedMaxServicesOutstandingCalling;                  ///< Negotiated Max Services Outstanding Calling
            short negotiatedMaxServicesOutstandingCalled;                   ///< Negotiated Max services Outstanding Called
            char negotiatedDataStructureNestingLevel;                       ///< Negotiated structure nesting level. Optional.
            InitRequestDetail initiateRequestDetails;                       ///< Initiate request details
        };
    }

    namespace serialization
    {
        using MMS::PDU::InitiateResponse;

        PDU_OPT_FIELD(InitiateResponse, 0, InitiateResponse::localDetailCalling);
        PDU_FIELD(InitiateResponse, 1, InitiateResponse::negotiatedMaxServicesOutstandingCalling);
        PDU_FIELD(InitiateResponse, 2, InitiateResponse::negotiatedMaxServicesOutstandingCalled);
        PDU_OPT_FIELD(InitiateResponse, 3, InitiateResponse::negotiatedDataStructureNestingLevel);
        PDU_FIELD(InitiateResponse, 4, InitiateResponse::initiateRequestDetails);
    }

}

