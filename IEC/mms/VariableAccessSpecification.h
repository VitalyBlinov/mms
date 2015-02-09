//-----------------------------------------------------------------------------
// <copyright file="VariableAccessSpecification.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/14 14:21:46</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Variable access specification protocol element definition
//-----------------------------------------------------------------------------
#pragma once
#include "ObjectName.h"
#include "Address.h"
#include "NULLValue.h"
#include "serialization.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Variable access specification type
             ****************************************/
            template <class St>
            struct VariableAccessSpecification
            {
                enum: char{
                    id_objectName,
                    id_address,
                    id_variableDescription,
                    id_scatteredAccessDescription,
                    id_invalidated
                } choice;
                ObjectName<St>  objectName;         ///< [0]
                Address         address;            ///< [1]
                // TODO
            };
        }
    }

}

