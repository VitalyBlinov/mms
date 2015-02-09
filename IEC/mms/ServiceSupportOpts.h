//-----------------------------------------------------------------------------
// <copyright file="ServiceSupportOpts.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 05:28:53</created>
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
            ///	\brief ServiceSupportOpts class
            /// 
            class ServiceSupportOpts:
                public ::MMS::DataTypes::FixedSizeBitString<85>
            {
            public:
                enum FLAG
                {
                    status					=0,	
                    getNameList				=1, 	
                    identify				=2, 		
                    rename					=3,	
                    read					=4,	
                    write					=5,	
                    getVariableAccessAttributes		=6,	
                    defineNamedVariable			=7,	
                    defineScatteredAccess			=8,	
                    getScatteredAccessAttributes		=9,	
                    deleteVariableAccess			=10,		
                    defineNamedVariableList			=11,	
                    getNamedVariableListAttributes		=12,	
                    deleteNamedVariableList			=13,	
                    defineNamedType				=14,		
                    getNamedTypeAttributes			=15,	
                    deleteNamedType				=16,	
                    input					=17,	
                    output					=18,	
                    takeControl				=19,	
                    relinquishControl			=20,	
                    defineSemaphore				=21,	
                    deleteSemaphore				=22,	
                    reportSemaphoreStatus			=23,	
                    reportPoolSemaphoreStatus		=24,	
                    reportSemaphoreEntryStatus		=25,	
                    initiateDownloadSequence		=26,	
                    downloadSegment				=27,	
                    terminateDownloadSequence		=28,	
                    initiateUploadSequence			=29,
                    uploadSegment				=30,	
                    terminateUploadSequence			=31,	
                    requestDomainDownload			=32,	
                    requestDomainUpload			=33,	
                    loadDomainContent			=34,	
                    storeDomainContent			=35,	
                    deleteDomain				=36,	
                    getDomainAttributes			=37,	
                    createProgramInvocation			=38,	
                    deleteProgramInvocation			=39,	
                    start					=40,	
                    stop					=41,	
                    resume					=42,	
                    reset					=43,	
                    kill					=44,	
                    getProgramInvocationAttributes		=45,	
                    obtainFile				=46,	
                    defineEventCondition			=47,	
                    deleteEventCondition			=48,	
                    getEventConditionAttributes		=49,	
                    reportEventConditionStatus		=50,	
                    alterEventConditionMonitoring		=51,	
                    triggerEvent				=52,	
                    defineEventAction			=53,	
                    deleteEventAction			=54,	
                    getEventActionAttributes		=55,	
                    reportActionStatus			=56,	
                    defineEventEnrollment			=57,	
                    deleteEventEnrollment			=58,	
                    alterEventEnrollment			=59,	
                    reportEventEnrollmentStatus		=60,	
                    getEventEnrollmentAttributes		=61,	
                    acknowledgeEventNotification		=62,	
                    getAlarmSummary				=63,	
                    getAlarmEnrollmentSummary		=64,	
                    readJournal				=65,	
                    writeJournal				=66,	
                    initializeJournal			=67,	
                    reportJournalStatus			=68,	
                    createJournal				=69,	
                    deleteJournal				=70,	
                    getCapabilityList			=71,	
                    fileOpen				=72,	
                    fileRead				=73,	
                    fileClose				=74,	
                    fileRename				=75,	
                    fileDelete				=76,	
                    fileDirectory				=77,	
                    unsolicitedStatus			=78,
                    informationReport			=79,
                    eventNotification			=80,
                    attachToEventCondition			=81,
                    attachToSemaphore			=82,
                    conclude				=83,
                    cancel					=84
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

