// OptimizerBug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <string>
#include <iostream>
#include "EmitContext.h"
#include "ContextMisc.h"
#include "VisibleString.h"
#include "VisibleStringEmitter.h"
#include "serialization.h"


using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;
using namespace serialization;


typedef MMS::DataTypes::VisibleString<std::string> MyTestString;
struct TestStruc
{
    MyTestString blah;
};

PDU_EXPLICIT_FIELD(TestStruc, 0, TestStruc::blah);

typedef MMS::Emitters::Details::EmitContext<MMS::ContextTraits<false>> ExplicitEmitContextASN;
typedef MMS::Emitters::Details::EmitContext<MMS::ContextTraits<true>> ImplicitEmitContextASN;

int _tmain(int argc, _TCHAR* argv[])
{
    std::array<unsigned char, 128> testArray;
    testArray.fill(0);

    TestStruc Req;
    Req.blah = "testing...";

    auto ctx = ImplicitEmitContextASN(createContext<ExplicitEmitContextASN>(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;


    if (offset != 15)
    {
        std::cerr << "Oh shi..... offset = " << offset << ", expected : " << Req.blah.length() + 4 << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "All OK....." << std::endl;
        return 0;
    }
}

