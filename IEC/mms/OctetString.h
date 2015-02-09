//-----------------------------------------------------------------------------
// <copyright file="OctetString.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 23:36:50</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file OctetString variants
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <array>
#include <list>
#include "MMSTags.h"
#include "UniversalClass.h"
#include "ASN1Tag.h"

namespace MMS
{
    
    namespace Tags
    {
        /************************************//**
         * \brief MMS tags for octet string variants
         ****************************************/
        MMS_TAG_TYPE_DEF(std::vector<unsigned char>, MMS_TAGS::OCTET_STRING);
        template <int S>
        MMS_T_TAG_TYPE_DEF(std::array<unsigned char COMMA S>, MMS_TAGS::OCTET_STRING);
        MMS_TAG_TYPE_DEF(std::list<unsigned char>, MMS_TAGS::OCTET_STRING);
    }
}

namespace ASN1
{
    namespace Tags
    {
        // Defines ASN.1 tag for this type
        ASN_TAG_TYPE_DEF(std::vector<unsigned char>, ASN1::Tags::OCTETSTRING);
        template <int S>
        ASN_T_TAG_TYPE_DEF(std::array<unsigned char COMMA S>, ASN1::Tags::OCTETSTRING);
        ASN_TAG_TYPE_DEF(std::list<unsigned char>, ASN1::Tags::OCTETSTRING);
    }
}

