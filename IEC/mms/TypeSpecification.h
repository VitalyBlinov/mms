//-----------------------------------------------------------------------------
// <copyright file="TypeSpecification.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/14 14:25:59</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file type specification 
//-----------------------------------------------------------------------------
#pragma once
#include "ObjectName.h"
#include "serialization.h"
namespace MMS
{
	namespace PDU
    {
        namespace Elements
        {
            namespace Details
            {
                /************************************//**
                 * \brief Array typedef
                 ****************************************/
                struct Array
                {
                    bool packed;            ///< [0]
                    int numberOfElements;   ///< [1]
                    // Heeeeelp! Recursion iz here!
                };
                /************************************//**
                 * \brief Structure components typedef
                 ****************************************/
                struct StructureComponents
                {
                    MMS::DataTypes::VisibleStringBuffer componentName;
                    // Heeeeelp! Recursion iz here!
                };
                /************************************//**
                 * \brief Structure Typedef
                 ****************************************/
                struct Structure
                {

                };
            }
            /************************************//**
             * \brief Type specification structure
             *
             * \details
             *
             ****************************************/
            struct TypeSpecification
            {

            };
        }
    }
}

