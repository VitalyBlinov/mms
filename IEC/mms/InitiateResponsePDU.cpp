//-----------------------------------------------------------------------------
// <copyright file="InitiateResponsePDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 05:52:43</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "InitiateResponsePDU.h"


using namespace MMS::PDU;

InitiateResponse::InitiateResponse():
        localDetailCalling(0),
        negotiatedMaxServicesOutstandingCalled(1),
        negotiatedMaxServicesOutstandingCalling(1),
        negotiatedDataStructureNestingLevel(0)
{
	
}



