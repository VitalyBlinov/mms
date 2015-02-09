//-----------------------------------------------------------------------------
// <copyright file="ObjectScope.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/12 16:38:13</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "serialization.h"
#include "NULLValue.h"
#include "VisibleString.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Object Scope structure
             *
             * \details This is a choice of tree options
             *
             ****************************************/
            template <class St>
            struct ObjectScope
            {
                enum : int{ 
                    id_vmd_specific,
                    id_domain_specific,
                    id_aa_specific
                } 
                choice;

                MMS::DataTypes::NULLValue _nullValue;               ///< when id_vmd_specific or id_aa_specific, no data is included 
                MMS::DataTypes::VarSizeBitString<St> identifier;   ///< Set when id_domain_specific is selected
            };
        }
    }
    namespace serialization
    {
        using MMS::PDU::Elements::ObjectScope;

        template <class St>
        T_PDU_IMPLICIT_FIELD(ObjectScope<St>, 0, ObjectScope<St>::_nullValue);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ObjectScope<St>, 1, ObjectScope<St>::identifier);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ObjectScope<St>, 2, ObjectScope<St>::_nullValue);
    }
}

