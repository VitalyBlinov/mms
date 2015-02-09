//-----------------------------------------------------------------------------
// <copyright file="InitiateRequestPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 03:11:08</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "InitiateRequestPDU.h"


using namespace MMS::PDU;

InitiateRequest::InitiateRequest():
        localDetailCalling(0),
        proposedMaxServicesOutstandingCalling(1),
        proposedMaxServicesOutstandingCalled(1),
        proposedDataStructureNestingLevel(0)
{
	
}
