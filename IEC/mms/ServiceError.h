//-----------------------------------------------------------------------------
// <copyright file="ServiceError.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/15 12:15:27</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "ErrorClass.h"
#include "VisibleString.h"
#include "PDUCommons.h"
#include "ObjectName.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            namespace Details
            {
                template <class St>
                struct ServiceSpecificInformation
                {

                    enum {
                        id_obtainFile, 
                        id_start, 
                        id_stop, 
                        id_resume, 
                        id_reset, 
                        id_deleteVariableAccess, 
                        id_deleteNamedVariableList, 
                        id_deleteNamedType, 
                        id_defineEventEnrollment_error,
                        id_fileRename
                        } choice;
                    // Warning - items below aren't exactly in order
                    union
                    {
                        int _value;
                        MMS::PDU::CommonEnum::FileOpError obtainFileError;                  //  0
                        MMS::PDU::CommonEnum::ProgramInvocationState m_start_error;         //  1
                        MMS::PDU::CommonEnum::ProgramInvocationState m_stop_error;          //  2
                        MMS::PDU::CommonEnum::ProgramInvocationState m_resume_error;        //  3
                        MMS::PDU::CommonEnum::ProgramInvocationState m_reset_error;         //  4
                        int m_deleteVariableAccessError;                                    //  5
                        int DeleteNamedVariableListError;                                   //  6
                        int DeleteNamedTypeError;                                           //  7
                        MMS::PDU::CommonEnum::FileOpError m_fileRename_error;               //  9
                    };
                    MMS::PDU::Elements::ObjectName<St> m_defineEventEnrollment_Error;       //  8
                    /************************************//**
                     * \brief Equal operator
                     ****************************************/
                    template <class T>
                    bool operator == (const ServiceSpecificInformation<T>& _what) const
                    {
                        return _value == _what._value && m_defineEventEnrollment_Error == _what.m_defineEventEnrollment_Error;
                    }

                    ServiceSpecificInformation():
                            _value(0)
                    {

                    }
                };
            }
            /************************************//**
             * \brief Service Error protocol element
             ****************************************/
            template <class St = std::string>
            struct ServiceError
            {
                ErrorClass                              m_errorClass;
                int                                     m_additionalCode;
                MMS::DataTypes::VisibleString<St>       m_additionalDescription;
                Details::ServiceSpecificInformation<St> m_serviceSpecificInformation;

                ServiceError():
                        m_additionalCode(0)
                {

                }
            };
        }
    }

    namespace serialization
    {
        using MMS::PDU::Elements::Details::ServiceSpecificInformation;

        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 0, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 1, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 2, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 3, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 4, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 5, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 6, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 7, ServiceSpecificInformation<St>::_value);
        template <class St>
        T_PDU_EXPLICIT_FIELD(ServiceSpecificInformation<St>, 8, ServiceSpecificInformation<St>::m_defineEventEnrollment_Error);
        template <class St>
        T_PDU_IMPLICIT_FIELD(ServiceSpecificInformation<St>, 9, ServiceSpecificInformation<St>::_value);

        using MMS::PDU::Elements::ServiceError;
        template <class St>
        T_PDU_EXPLICIT_FIELD(ServiceError<St>, 0, ServiceError<St>::m_errorClass);
        template <class St>
        T_OPT_IMPLICIT_FIELD(ServiceError<St>, 1, ServiceError<St>::m_additionalCode);
        template <class St>
        T_OPT_IMPLICIT_FIELD(ServiceError<St>, 2, ServiceError<St>::m_additionalDescription);
        template <class St>
        T_OPT_EXPLICIT_FIELD(ServiceError<St>, 3, ServiceError<St>::m_serviceSpecificInformation);
    }
}
