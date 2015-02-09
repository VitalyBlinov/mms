//-----------------------------------------------------------------------------
// <copyright file="unittest1.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 16:29:59</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "CppUnitTest.h"
#include "EmitOctet.h"
#include "EmitContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MMS::Emitters;

namespace emitTestNative
{		
	TEST_CLASS(EmitContextTests)
	{
	public:
		
		TEST_METHOD(TestConstructEmitContext)
		{
            unsigned char testArea[128] = {0};
			EmitContext<unsigned char*> CUT(testArea, testArea + sizeof(testArea));
		}

        TEST_METHOD(TestEmitOctetDirectly)
        {
            unsigned char testArea[128] = {0};
            EmitContext<unsigned char*> CUT(testArea, testArea + sizeof(testArea));
            Assert::AreEqual((unsigned char)0, testArea[127]);
            Assert::IsTrue(CUT.emitOctet(123));
            Assert::AreEqual((unsigned char)123, testArea[127]);
        }

        TEST_METHOD(TestEmitOctetUsingWraper)
        {
            unsigned char testArea[128] = {0};
            EmitContext<unsigned char*> CUT(testArea, testArea + sizeof(testArea));
            Assert::AreEqual((unsigned char)0, testArea[127]);
            CUT = emitOctet(CUT, 23);
            Assert::AreEqual((unsigned char)23, testArea[127]);
        }

        TEST_METHOD(TestEmitOctetUsingWraperTwice)
        {
            unsigned char testArea[128] = {0};
            EmitContext<unsigned char*> CUT(testArea, testArea + sizeof(testArea));
            Assert::AreEqual((unsigned char)0, testArea[127]);
            CUT = emitOctet(CUT, 23);
            Assert::AreEqual((unsigned char)23, testArea[127]);
            Assert::AreEqual((unsigned char)0, testArea[126]);
            CUT = emitOctet(CUT, 213);
            Assert::AreEqual((unsigned char)213, testArea[126]);
        }

	};
}