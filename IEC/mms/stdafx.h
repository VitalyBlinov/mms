// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include <vector>
#include <bitset>
#include "ContextMisc.h"
#include "EmitContext.h"
#include "EmitOctet.h"
#include "IntegerEmitter.h"
#include "LengthEmitter.h"
#include "BoolEmitter.h"
#include "BitStringEmitter.h"
#include "FloatEmitter.h"
#include "TagEmitter.h"
#include "UnsignedEmitter.h"
#include "defaultFieldValue.h"
#include "serialization.h"
#include "InitiateRequestPDU.h"
#include "ParametersSupportOpts.h"
#include "ServiceSupportOpts.h"
#include "FetchContext.h"
#include "FetchOctet.h"
#include "LengthExtractor.h"
#include "TagExtractor.h"
#include "skipTLV.h"
#include "BoolExtractor.h"
#include "IntegerExtractor.h"
#include "FixedSizeBitString.h"
#include "BitStringExtractor.h"
#include "FloatExtractor.h"
#include "UnsignedExtractor.h"
#include "VisibleString.h"
#include "VisibleStringEmitter.h"
#include "VisibleStringExtractor.h"
#include "UniversalClass.h"
#include "ContextTraits.h"
#include "ASN1Tag.h"
#include "VarSizeBitString.h"
#include "evaluator.h"
#include "SequenceOfEmitter.h"
#include "SequenceOfExtractor.h"
#include "ExtractedSequenceOf.h"
#include "GetNameListResponse.h"
#include "OctetString.h"
#include "OctetStringExt.h"
#include "OctetStringEmitter.h"
#include "OctetStringExtractor.h"

#include "ErrorClass.h"
#include "InitiateResponsePDU.h"

