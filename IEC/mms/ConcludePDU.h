//-----------------------------------------------------------------------------
// <copyright file="ConcludePDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 05:56:58</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "NULLValue.h"
#include "ServiceError.h"
namespace MMS
{
    namespace PDU
    {
        /************************************//**
         * \brief Conclude request PDU
         ****************************************/
        typedef MMS::DataTypes::NULLValue ConcludeRequest;
        /************************************//**
         * \brief Conclude response PDU
         ****************************************/
        typedef MMS::DataTypes::NULLValue ConcludeResponse;

        // Conclude error is nothing else but ServiceError
    }
}

