//-----------------------------------------------------------------------------
// <copyright file="ProposedParametersCBB.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 04:55:08</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include <bitset>
#include "BitStringEmitter.h"
#include "BitStringExtractor.h"
#include "FixedSizeBitString.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Proposed parameters CBB 
             *
             * \details This is nothing else but a bit string
             *
             ****************************************/
            class ParametersSupportOpts:
                public ::MMS::DataTypes::FixedSizeBitString<11>
            {
            public:
                enum FLAG
                {
                    str1 = 0,
                    str2,
                    vnam,
                    valt,
                    vadr,
                    vsca,
                    tpy,
                    vlis,
                    real,
                    cei = 10
                };
                /************************************//**
                 * \brief Flag getter
                 ****************************************/
                bool IsSet(
                    FLAG _flag
                    ) const;
                /************************************//**
                 * \brief Flag setter
                 ****************************************/
                void SetFlag(
                    FLAG _flag,
                    bool value
                    );
            };
        }
    }
}

