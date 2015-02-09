//-----------------------------------------------------------------------------
// <copyright file="ServiceErrorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 02:25:32</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Unit test for ServiceError super-duper structure
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "ServiceError.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "serialization.h"
#include "ServiceError.h"
using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;
using MMS::PDU::Elements::ErrorClass;
using MMS::PDU::Elements::Details::ServiceSpecificInformation;
using MMS::PDU::CommonEnum;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class ServiceErrorTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    ServiceErrorTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief Emit positive test case
 ****************************************/
TEST_F(ServiceErrorTest, TestEmitSimpleCase)
{
	MMS::PDU::Elements::ServiceError<std::string> CUT;
    CUT.m_errorClass.choice = ErrorClass::id_application_reference;
    CUT.m_errorClass.application_reference = ErrorClass::class_application_reference::application_unreachable;
    CUT.m_serviceSpecificInformation.choice = ServiceSpecificInformation<std::string>::id_resume;
    CUT.m_serviceSpecificInformation.m_resume_error = CommonEnum::ProgramInvocationState::running;

    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;


    // TODO: it all needs to be tested against something that can send back errors.
    // Not sure whether correct high bits are set in tags, i.e. no sure that "constructed" is correctly used
    ASSERT_EQ(11, offset);
    EXPECT_EQ(offset-1, testArray[testArray.size() - offset--]) << "Size";
    EXPECT_EQ(0xA0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]) << "length";
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]); 
    EXPECT_EQ(1, testArray[testArray.size() - offset--]); 
    EXPECT_EQ(0xA3, testArray[testArray.size() - offset--]); 
    EXPECT_EQ(3, testArray[testArray.size() - offset--]); 
    EXPECT_EQ(0x83, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
}


TEST_F(ServiceErrorTest, TestEmitAndFetchPlease)
{
    MMS::PDU::Elements::ServiceError<std::string> CUT;
    CUT.m_errorClass.choice = ErrorClass::id_application_reference;
    CUT.m_errorClass.application_reference = ErrorClass::class_application_reference::application_unreachable;
    CUT.m_serviceSpecificInformation.choice = ServiceSpecificInformation<std::string>::id_resume;
    CUT.m_serviceSpecificInformation.m_resume_error = CommonEnum::ProgramInvocationState::running;

    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;


    auto fetchContext = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Elements::ServiceError<std::string> Fetched;
    ASSERT_TRUE(fetch(fetchContext, Fetched));
    ASSERT_EQ(0, getContextSize(fetchContext));
    ASSERT_EQ(CUT.m_errorClass.choice, Fetched.m_errorClass.choice);
    ASSERT_EQ(CUT.m_errorClass._value, Fetched.m_errorClass._value);

    ASSERT_EQ(CUT.m_serviceSpecificInformation.choice, Fetched.m_serviceSpecificInformation.choice);
    ASSERT_EQ(CUT.m_serviceSpecificInformation.m_resume_error, Fetched.m_serviceSpecificInformation.m_resume_error);
}


TEST_F(ServiceErrorTest, TestEmitAndFetchWithAdditionalDescriptionPlease)
{
    MMS::PDU::Elements::ServiceError<std::string> CUT;
    CUT.m_errorClass.choice = ErrorClass::id_application_reference;
    CUT.m_errorClass.application_reference = ErrorClass::class_application_reference::application_unreachable;
    CUT.m_serviceSpecificInformation.choice = ServiceSpecificInformation<std::string>::id_resume;
    CUT.m_serviceSpecificInformation.m_resume_error = CommonEnum::ProgramInvocationState::running;
    CUT.m_additionalDescription = "Additional Description Please";

    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;


    auto fetchContext = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Elements::ServiceError<std::string> Fetched;
    ASSERT_TRUE(fetch(fetchContext, Fetched));
    ASSERT_EQ(0, getContextSize(fetchContext));
    ASSERT_EQ(CUT.m_errorClass.choice, Fetched.m_errorClass.choice);
    ASSERT_EQ(CUT.m_errorClass._value, Fetched.m_errorClass._value);

    ASSERT_EQ(CUT.m_serviceSpecificInformation.choice, Fetched.m_serviceSpecificInformation.choice);
    ASSERT_EQ(CUT.m_serviceSpecificInformation.m_resume_error, Fetched.m_serviceSpecificInformation.m_resume_error);

    ASSERT_EQ(CUT.m_additionalDescription, Fetched.m_additionalDescription);
}