//-----------------------------------------------------------------------------
// <copyright file="InitiateErrorPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/23 12:33:02</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "ServiceError.h"
namespace MMS
{
	namespace PDU
    {
        template <class St>
        typedef MMS::PDU::Elements::ServiceError<St> InitiateError;
    }
}

