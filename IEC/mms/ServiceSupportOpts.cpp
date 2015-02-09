//-----------------------------------------------------------------------------
// <copyright file="ServiceSupportOpts.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 05:31:58</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "ServiceSupportOpts.h"


using namespace MMS::PDU::Elements;

bool MMS::PDU::Elements::ServiceSupportOpts::IsSet( FLAG _flag ) const
{
    return m_flags[_flag];
}

void MMS::PDU::Elements::ServiceSupportOpts::SetFlag( FLAG _flag, bool value )
{
    m_flags[_flag] = value;
}
