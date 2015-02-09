//-----------------------------------------------------------------------------
// <copyright file="GetNameListReq.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/12 16:11:25</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "ObjectClass.h"
#include "ObjectScope.h"
#include "VisibleString.h"
namespace MMS
{
    namespace PDU
    {
        namespace Confirmed
        {
            /************************************//**
             * \brief GetNameList-Request structure
             ****************************************/
            template <class St>
            struct GetNameListRequest
            {
                MMS::PDU::Elements::ExtObjectClass extendedObjectClass;
                MMS::PDU::Elements::ObjectScope<St> object_scope;
                MMS::DataTypes::VisibleString<St> continueAfter;
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Confirmed::GetNameListRequest;

        template <class St>
        T_PDU_IMPLICIT_FIELD(GetNameListRequest<St>, 0, GetNameListRequest<St>::extendedObjectClass);
        template <class St>
        T_PDU_IMPLICIT_FIELD(GetNameListRequest<St>, 1, GetNameListRequest<St>::object_scope);
        template <class St>
        T_PDU_IMPLICIT_FIELD(GetNameListRequest<St>, 2, GetNameListRequest<St>::continueAfter);
    }
}

