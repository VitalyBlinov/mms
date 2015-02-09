//-----------------------------------------------------------------------------
// <copyright file="ObjectClass.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/12 16:13:56</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "serialization.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Extended object class structure
             *
             * \details Intended to be a CHOICE, but only
             *  one selection is available so far
             *
             ****************************************/
            struct ExtObjectClass
            {
                enum : int{ 
                    id_objectClass
                } 
                choice;

                enum: int{
                    nammedVariable,
                    scatteredAccess,
                    namedVariableList,
                    namedType,
                    semaphore,
                    eventCondition,
                    eventAction,
                    eventEnrollment,
                    journal,
                    domain,
                    programInvocation,
                    operatorStation
                } _value;
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Elements::ExtObjectClass;

        PDU_IMPLICIT_FIELD(ExtObjectClass, 0, ExtObjectClass::_value);

    }
}

