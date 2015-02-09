//-----------------------------------------------------------------------------
// <copyright file="InitiateRequestDetail.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 05:04:47</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "EmitContext.h"
#include "LengthEmitter.h"
#include "IntegerEmitter.h"
#include "serialization.h"
#include "ParametersSupportOpts.h"
#include "ServiceSupportOpts.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            ///	\brief InitiateRequestDetail class
            /// 
            class InitiateRequestDetail
            {
            public:
                ///	\brief InitiateRequestDetail constructor
                InitiateRequestDetail();

                short proposedVersionNumber;
                ParametersSupportOpts proposedParametersCBB;
                ServiceSupportOpts serviceSuportOptions;
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Elements::InitiateRequestDetail;

        PDU_FIELD(InitiateRequestDetail, 0, InitiateRequestDetail::proposedVersionNumber);
        PDU_FIELD(InitiateRequestDetail, 1, InitiateRequestDetail::proposedParametersCBB);
        PDU_FIELD(InitiateRequestDetail, 2, InitiateRequestDetail::serviceSuportOptions);
    }
}

