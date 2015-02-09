//-----------------------------------------------------------------------------
// <copyright file="OctetStringExtractor.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/14 00:03:48</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Octet string extractor
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <list>
#include <array>
#include "OctetStringExt.h"

namespace MMS
{
    namespace Extractors
    {
        namespace Details
        {
            /************************************//**
             * \brief Validates the tag, extracts length and octet string value
             ****************************************/
            template <class Context>
            inline bool doExtractOctetString(Context& _ctx, MMS::DataTypes::OctetStringBuffer& _Value)
            {
                if (checkTag(_ctx, _Value))
                {
                    if (fetchLength(_ctx, _Value.length))
                    {
                        _Value.pPtr = fetchOctets(_ctx, _Value.length);
                        return _Value.pPtr != nullptr;
                    }
                }
                return false;
            };
            /************************************//**
             * \brief Octet string extractor
             *
             * \details Extracts the octet string
             *
             ****************************************/
            ///@{
            template <class Context>
            inline bool extract(Context& _ctx, MMS::DataTypes::OctetStringBuffer& _Value)
            {
                return doExtractOctetString(_ctx, _Value);
            };

            template <class Context, class T>
            inline typename std::enable_if<(MMS::Tags::TagDef<T>::TAG == MMS::Tags::OCTET_STRING || ASN1::Tags::TagDef<T>::TAG == ASN1::Tags::OCTETSTRING), 
                bool>::type extract(Context& _ctx, T& _Value)
            {
                MMS::DataTypes::OctetStringBuffer extracted;
                if (doExtractOctetString(_ctx, extracted))
                {
                    std::swap(_Value, T(extracted.pPtr, extracted.pPtr + extracted.length));
                    return true;
                }
                return false;
            };
            ///@}
        }
    }

}

