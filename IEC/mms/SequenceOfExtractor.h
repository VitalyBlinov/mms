//-----------------------------------------------------------------------------
// <copyright file="SequenceOfExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 02:39:03</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Extractor for sequences
//-----------------------------------------------------------------------------
#pragma once
#include "ExtractedSequenceOf.h"
#include "ContextMisc.h"
namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Extracts sequence from the context
             ****************************************/
            template <class C, class T>
            inline bool extract(C& _ctx, MMS::DataTypes::SequenceOf<C, T>& _out)
            {
                unsigned int length = 0;
                if (checkTag(_ctx, _out))
                {
                    if (fetchLength(_ctx, length))
                    {
                        _out = MMS::DataTypes::SequenceOf<C, T>(getSubContext(_ctx, length));
                        return true;
                    }
                }
                return false;
            }
        }

    }
}

