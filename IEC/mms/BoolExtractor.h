//-----------------------------------------------------------------------------
// <copyright file="BoolExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 00:12:39</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "FetchOctet.h"
#include "TagExtractor.h"
#include "LengthExtractor.h"
namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
             /************************************//**
             * \brief Boolean type extractor
             *
             * \details extracts boolean value from the fetch context.
             *
             * \returns True if value is successfully extracted. False otherwise.
             *
             ****************************************/
            template <class Context>
            bool extract(Context& _ctx, bool& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    auto ptr = fetchOctets(_ctx, 2);
                    if (ptr != nullptr)
                    {
                        if (ptr[0] == 1)
                        {
                            _Value = (ptr[0] == 1 && ptr[1] != 0);
                            return true;
                        }
                    }
                }
                return false;
            };
        }
    }
}

