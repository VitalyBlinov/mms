//-----------------------------------------------------------------------------
// <copyright file="ErrorClass.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/15 19:40:24</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#pragma once
#include "IntegerExtractor.h"
#include "IntegerEmitter.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "EmitOctet.h"
#include "serialization.h"
namespace MMS
{
    namespace PDU
    {
        namespace Elements
        {
            /************************************//**
             * \brief Error class element of the ServiceError
             ****************************************/
            class ErrorClass
            {
            public:
                enum class class_vmd_state: int
                {	
                    other=0,			       
                    vmd_state_conflict=1,		
                    vmd_operational_problem=2, 
                    domain_transfer_problem=3,	
                    state_machine_id_invalid=4	
                };
                enum class class_application_reference: int
                {
                    other=0,
                    application_unreachable=1,
                    connection_lost=2,
                    application_reference_invalid=3,
                    context_unsupported=4
                };
                enum class class_definition: int
                {
                    other=0,
                    object_undefined=1,
                    invalid_address=2,
                    type_unsupported=3,
                    type_inconsistent=4,
                    object_exists=5,
                    object_attribute_inconsistent=6
                };
                enum class class_resource: int
                {
                    other=0,
                    memory_unavailable=1,
                    processor_resource_unavailable=2,
                    mass_storage_unavailable=3,
                    capability_unavailable=4,
                    capability_unknown=5
                };
                enum class class_service: int
                {	
                    other=0,
                    primitives_out_of_sequence=1,
                    object_sate_conflict=2,
                    pdu_size=3,
                    continuation_invalid=4,
                    object_constraint_conflict=5
                };
                enum class class_service_preempt: int
                {	
                    other=0,
                    timeout=1,
                    deadlock=2,
                    cancel=3
                };
                enum class class_time_resolution: int
                {	
                    other=0,
                    unsupportable_time_resolution=1
                };
                enum class class_access: int
                {
                    other=0,
                    object_access_unsupported=1,
                    object_non_existent=2,
                    object_access_denied=3,
                    object_invalidated=4
                };
                enum class class_initiate: int
                {
                    other=0,
                    version_incompatible=1,
                    max_segment_insufficient=2,
                    max_services_outstanding_calling_insufficient=3,
                    max_services_outstanding_called_insufficient=4,
                    service_CBB_insufficient=5,
                    parameter_CBB_insufficient=6,
                    nesting_level_insufficient=7
                };
                enum class class_conclude: int
                {
                    other=0,
                    further_communication_required=1
                };
                enum class class_cancel: int
                {
                    other=0,
                    invoke_id_unknown=1,
                    cancel_not_possible=2
                };
                enum class class_file: int
                {
                    other=0,
                    filename_ambiguous=1,
                    file_busy=2,
                    filename_syntax_error=3,
                    content_type_invalid=4,
                    position_invalid=5,
                    file_acces_denied=6,
                    file_non_existent=7,
                    duplicate_filename=8,
                    insufficient_space_in_filestore=9
                };


                enum : unsigned char{ 
                    id_vmd_state,
                    id_application_reference,
                    id_definition,
                    id_resource,
                    id_service,
                    id_service_preempt,
                    id_time_resolution,
                    id_access,
                    id_initiate,
                    id_conclude,
                    id_cancel,
                    id_file,
                    id_others} 
                choice;


                union
                {
                    int _value;
                    class_vmd_state vmd_state;
                    class_application_reference application_reference;
                    class_definition definition;
                    class_resource resource;
                    class_service service;
                    class_service_preempt service_preempt;
                    class_time_resolution time_resolution;
                    class_access access;
                    class_initiate initiate;
                    class_conclude conclude;
                    class_cancel cancel;
                    class_file file;
                    int others;
                };

            };
        }
    }


    namespace serialization
    {
        using MMS::PDU::Elements::ErrorClass;

        PDU_IMPLICIT_FIELD(ErrorClass, 0, ErrorClass::_value);
        PDU_IMPLICIT_FIELD(ErrorClass, 1, ErrorClass::_value);
        PDU_IMPLICIT_FIELD(ErrorClass, 2, ErrorClass::_value);

    }
}

