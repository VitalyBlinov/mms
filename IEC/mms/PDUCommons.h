//-----------------------------------------------------------------------------
// <copyright file="PDUCommons.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 02:03:14</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file defines some enumerations and data structures used in several PDUs and elements
//-----------------------------------------------------------------------------
#pragma once

namespace MMS
{
    namespace PDU
    {
        struct CommonEnum
        {
            /************************************//**
             * \brief Program Invocation State enumerations
             ****************************************/
            enum ProgramInvocationState: int 
            {
                non_existent,
                unrunable,
                idle,
                running,
                stopped,
                starting,
                stopping,
                resuming,
                resetting
            };

            enum FileOpError
            {
                source_file,
                destination_file
            };
        };
    }

}

