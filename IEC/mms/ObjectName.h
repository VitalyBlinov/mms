//-----------------------------------------------------------------------------
// <copyright file="ObjectName.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 14:15:31</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "VisibleString.h"
#include "serialization.h"

#ifndef OBJECT_NAME_LENGTH
#define OBJECT_NAME_LENGTH 255
#endif

namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            namespace Details
            {
                /************************************//**
                 * \brief Domain-specific object name
                 ****************************************/
                template <class St>
                struct Domain_specific
                {
                    MMS::DataTypes::VisibleString<St> domainId;
                    MMS::DataTypes::VisibleString<St> itemId;

                    template <class T>
                    bool operator == (const Domain_specific<T>& _what) const
                    {
                        return domainId == _what.domainId && itemId == _what.itemId;
                    }
                };
            }
            /************************************//**
             * \brief Object name structure
             *
             * \details  This is the key for almost every request
             *  where Object Name is involved
             *
             ****************************************/
            template <class St>
            struct ObjectName
            {
                enum { id_vmd_specific, id_domain_specific, id_aa_specific } choice;
                MMS::DataTypes::VisibleString<St> vmd_specific;
                Details::Domain_specific<St> domain_specific;
                MMS::DataTypes::VisibleString<St> aa_specific;

                template <class T>
                bool operator == (const ObjectName<T>& _what) const
                {
                    if (choice == _what.choice)
                    {
                        switch (choice)
                        {
                        case id_vmd_specific:
                            return vmd_specific == _what.vmd_specific;
                            break;
                        case id_domain_specific:
                            return domain_specific == _what.domain_specific;
                            break;
                        case id_aa_specific:
                            return aa_specific == _what.aa_specific;
                            break;
                        default:
                            return false;
                            break;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Elements::Details::Domain_specific;
                
        template <class St>
        T_PDU_EXPLICIT_FIELD(Domain_specific<St>, 0, Domain_specific<St>::domainId);
        template <class St>
        T_NOINDEX_FIELD(MMS::PDU::Elements::Details::Domain_specific<St>, 0);
        template <class St>
        T_PDU_EXPLICIT_FIELD(Domain_specific<St>, 1, Domain_specific<St>::itemId);
        template <class St>
        T_NOINDEX_FIELD(Domain_specific<St>, 1);

         using MMS::PDU::Elements::ObjectName;
 
         template <class St>
         T_PDU_IMPLICIT_FIELD(ObjectName<St>, 0, ObjectName<St>::vmd_specific);
         template <class St>
         T_PDU_IMPLICIT_FIELD(ObjectName<St>, 1, ObjectName<St>::domain_specific);
         template <class St>
         T_PDU_IMPLICIT_FIELD(ObjectName<St>, 2, ObjectName<St>::aa_specific);
    }
}

