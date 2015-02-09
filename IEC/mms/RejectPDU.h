//-----------------------------------------------------------------------------
// <copyright file="RejectPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 06:48:52</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once

namespace MMS
{
    namespace PDU
    {
        namespace Details
        {
            /************************************//**
             * \brief Reject reason structure
             ****************************************/
            struct rejectReason
            {
                enum class class_confirmed_requestPDU
                {
                    other=0,
                    unrecognized_service=1,
                    unrecognized_modifier=2,
                    invalid_invokeID=3,
                    invalid_argument=4,
                    invalid_modifier=5,
                    max_serv_outstanding_exceeded=6,
                    max_recursion_exceeded=8,
                    value_out_of_range=9
                };

                enum class class_confirmed_responsePDU		 
                {
                    other=0,
                    unrecognized_service=1,
                    invalid_invokeID=2,
                    invalid_result=3,
                    max_recursion_exceeded=5,
                    value_out_of_range=6 	
                };	

                enum class class_confirmed_errorPDU		
                {
                    other=0,
                    unrecognized_service=1,
                    invalid_invokeID=2,
                    invalid_serviceError=3,
                    value_out_of_range=4 	
                };			

                enum class class_unconfirmedPDU			
                {
                    other=0,
                    unrecognized_service=1,
                    invalid_argument=2,
                    max_recursion_exceeded=3,
                    value_out_of_range=4 	
                };

                enum class class_pdu_error			
                {
                    unknown_pdu_type=0,
                    invalid_pdu=1,
                    illegal_acse_mapping=2
                };

                enum class class_cancel_requestPDU		
                {
                    other=0,
                    invalid_invokeID=1	
                };	

                enum class class_cancel_responsePDU	        
                {
                    other=0,
                    invalid_invokeID=1	
                };

                enum class class_cancel_errorPDU			
                {
                    other=0,
                    invalid_invokeID=1,
                    invalid_serviceError=2,
                    value_out_of_range=3 	
                };

                enum class class_conclude_requestPDU		
                {
                    other=0,
                    invalid_argument=1	
                };	

                enum class class_conclude_responsePDU	        
                {
                    other=0,
                    invalid_result=1	
                };

                enum class class_conclude_errorPDU		
                {
                    other=0,
                    invalid_serviceError=1,
                    value_out_of_range=2 	
                };

                enum {
                    id_padding,
                    id_confirmed_requestPDU,	 
                    id_confirmed_responsePDU,	 
                    id_confirmed_errorPDU,	
                    id_unconfirmedPDU,		
                    id_pdu_error,		
                    id_cancel_requestPDU,	
                    id_cancel_responsePDU,        
                    id_cancel_errorPDU,		
                    id_conclude_requestPDU,	
                    id_conclude_responsePDU,        
                    id_conclude_errorPDU
                } choice;

                union 
                {
                    int _value;
                    class_confirmed_requestPDU confirmed_requestPDU;	 
                    class_confirmed_responsePDU confirmed_responsePDU;	 
                    class_confirmed_errorPDU confirmed_errorPDU;	
                    class_unconfirmedPDU unconfirmedPDU;		
                    class_pdu_error pdu_error;		
                    class_cancel_requestPDU cancel_requestPDU;	
                    class_cancel_responsePDU cancel_responsePDU;        
                    class_cancel_errorPDU cancel_errorPDU;		
                    class_conclude_requestPDU conclude_requestPDU;	
                    class_conclude_responsePDU conclude_responsePDU;        
                    class_conclude_errorPDU conclude_errorPDU;	
                };

                rejectReason();
            };
        }
        /************************************//**
         * \brief Reject PDU structure
         ****************************************/
        struct Reject
        {
        public:
            ///	\brief RejectPDU constructor
            Reject();

            typedef Details::rejectReason rejectReason;
            int originalInvokeID;
            rejectReason Reason;
        };
    }

    namespace serialization
    {
        using MMS::PDU::Details::rejectReason;

        PDU_IMPLICIT_FIELD(rejectReason, 0, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 1, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 2, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 3, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 4, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 5, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 6, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 7, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 8, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 9, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 10, rejectReason::_value);
        PDU_IMPLICIT_FIELD(rejectReason, 11, rejectReason::_value);

        using MMS::PDU::Reject;

        PDU_OPT_IMPLICIT_FIELD(Reject, 0, Reject::originalInvokeID);
        PDU_EXPLICIT_FIELD(Reject, 1, Reject::Reason);
        NOINDEX_FIELD(Reject, 1);

    }

}

