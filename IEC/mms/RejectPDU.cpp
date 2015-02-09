//-----------------------------------------------------------------------------
// <copyright file="RejectPDU.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 07:16:02</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "RejectPDU.h"


using namespace MMS::PDU;

Reject::Reject():
        originalInvokeID(0)
{
	
}





MMS::PDU::Details::rejectReason::rejectReason():
    choice(id_confirmed_requestPDU),
    _value(0)
{

}
