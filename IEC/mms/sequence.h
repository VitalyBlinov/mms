//-----------------------------------------------------------------------------
// <copyright file="sequence.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 15:48:06</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace MMS
{
    namespace PDU
    {
        /************************************//**
         * \brief Generic sequence structure
         *
         * \details Basic structure for emitting and fetching
         * of sequences of same type
         *
         * \todo To partially emit a sequence which may
         *  be longer than can fit in one PDU, need to perform
         *  two steps. First, evaluate the end() of the original
         *  range that can fit in the context. Second, emit elements
         *  in reverse order. 
         *  Finding the limits of sequence's portion that can fit in
         *  the PDU requires us to be able to calculate the number of
         *  octets the value will take in the context without actually emitting
         *  it, if possible. sometimes it is easier to emit it first and then
         *  discard resulting context.
         *  
         *
         ****************************************/
        template <typename T>
        struct sequence
        {

        };
    }
}

