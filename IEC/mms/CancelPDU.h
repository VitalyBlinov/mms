//-----------------------------------------------------------------------------
// <copyright file="CancelPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/23 12:25:31</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "IntegerEmitter.h"
#include "IntegerExtractor.h"
#include "ServiceError.h"
#include "serialization.h"
namespace MMS
{
    namespace PDU
    {
        typedef long CancelRequest;
        typedef long CancelResponse;

        /************************************//**
         * \brief Cancel-error PDU
         ****************************************/
        template <class St>
        struct CancelError
        {
            long m_originalInvokeID;
            MMS::PDU::Elements::ServiceError<St> m_serviceError;
        };
    }

    namespace serialization
    {
        using MMS::PDU::CancelError;

        template <class St>
        T_PDU_IMPLICIT_FIELD(CancelError<St>, 0, CancelError<St>::m_originalInvokeID);
        template <class St>
        T_PDU_IMPLICIT_FIELD(CancelError<St>, 1, CancelError<St>::m_serviceError);
    }
}

