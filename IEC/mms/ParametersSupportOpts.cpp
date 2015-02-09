//-----------------------------------------------------------------------------
// <copyright file="ProposedParametersCBB.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 05:00:54</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include "ParametersSupportOpts.h"


using namespace MMS::PDU::Elements;


bool MMS::PDU::Elements::ParametersSupportOpts::IsSet( FLAG _flag ) const
{
    return m_flags[_flag];
}

void MMS::PDU::Elements::ParametersSupportOpts::SetFlag( FLAG _flag, bool value )
{
    m_flags[_flag] = value;
}
