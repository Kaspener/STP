#include "CppUnitTest.h"
#include "../Lab5/PNumber.h"

using namespace STP;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TPNumberTest
{
	TEST_CLASS(TPNumberTest)
	{
	public:
		
        TEST_METHOD(ConstructorDoubleBasePrecision)
        {
            PNumber num1(10.0, 10, 2);
            Assert::AreEqual(10.0, num1.number());
            Assert::AreEqual(10, num1.base());
            Assert::AreEqual(2, num1.precision());
            PNumber num2(234.153, 5, 8);
            Assert::AreEqual(std::string("1414.03403030"), num2.numberString());
            Assert::AreEqual(5, num2.base());
            Assert::AreEqual(8, num2.precision());
        }

        TEST_METHOD(ConstructorDoubleBasePrecisionExceptions)
        {
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1(10.0, 20, 2); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1(10.0, 1, 2); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1(10.0, 6, -1); });
        }

        TEST_METHOD(ConstructorStringBasePrecisionExceptions)
        {
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1("10.0", "20", "2"); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1("10.0", "1", "2"); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1("10.0", "6", "-1"); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1("1~0.0", "6", "1"); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1("80.0", "6", "1"); });
            Assert::ExpectException<std::invalid_argument>([] {PNumber num1("10.0", "Z", "2"); });

        }

        TEST_METHOD(ConstructorStringBasePrecision)
        {
            PNumber num2("-A.B9", "16", "4");
            Assert::AreEqual(-10.7227, num2.number(), 0.0001);
            Assert::AreEqual(16, num2.base());
            Assert::AreEqual(4, num2.precision());
        }

        TEST_METHOD(SetBaseFromInt)
        {
            PNumber num1(10.0, 10, 2);
            num1.setBase(2);
            Assert::AreEqual(2, num1.base());
        }

        TEST_METHOD(SetBaseFromIntExceptions)
        {
            PNumber num1("10.0", "3", "2");
            Assert::ExpectException<std::out_of_range>([&] { num1.setBase(20); });
            Assert::ExpectException<std::out_of_range>([&] { num1.setBase(1); });
        }

        TEST_METHOD(SetBaseFromString)
        {
            PNumber num1(10.0, 10, 2);
            num1.setBase("8");
            Assert::AreEqual(8, num1.base());
        }

        TEST_METHOD(SetBaseFromStringExceptions)
        {
            PNumber num1("10.0", "3", "2");
            Assert::ExpectException<std::out_of_range>([&] { num1.setBase("20"); });
            Assert::ExpectException<std::out_of_range>([&] { num1.setBase("1"); });
            Assert::ExpectException<std::invalid_argument>([&] { num1.setBase("q`sdfa"); });
        }

        TEST_METHOD(SetPrecisionFromInt)
        {
            PNumber num1(10.0, 10, 2);
            num1.setPrecision(4);
            Assert::AreEqual(4, num1.precision());
        }

        TEST_METHOD(SetPrecisionFromIntExceptions)
        {
            PNumber num1("10.0", "3", "2");
            Assert::ExpectException<std::invalid_argument>([&] { num1.setPrecision(-1); });
        }

        TEST_METHOD(SetPrecisionFromString)
        {
            PNumber num1(10.0, 10, 2);
            num1.setPrecision("5");
            Assert::AreEqual(5, num1.precision());
        }

        TEST_METHOD(SetPrecisionFromStringExceptions)
        {
            PNumber num1("10.0", "3", "2");
            Assert::ExpectException<std::invalid_argument>([&] { num1.setPrecision("-1"); });
            Assert::ExpectException<std::invalid_argument>([&] { num1.setPrecision("`dsgfa"); });
        }

        TEST_METHOD(Addition)
        {
            PNumber num1(10.0, 10, 2);
            PNumber num4(20.0, 10, 2);
            PNumber result = num1 + num4;
            Assert::AreEqual(30.0, result.number());
            Assert::AreEqual(10, result.base());
            Assert::AreEqual(2, result.precision());
        }

        TEST_METHOD(OperationsExceptinsBase)
        {
            PNumber num1(10.0, 10, 2);
            PNumber num4(20.0, 12, 2);
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 + num4; });
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 - num4; });
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 * num4; });
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 / num4; });
        }

        TEST_METHOD(OperationsExceptinsPrecision)
        {
            PNumber num1(10.0, 10, 4);
            PNumber num4(20.0, 10, 2);
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 + num4; });
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 - num4; });
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 * num4; });
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 / num4; });
        }

        TEST_METHOD(OperationsExceptinDivisionByZero)
        {
            PNumber num1(10.0, 10, 4);
            PNumber num4(0.0, 10, 4);
            Assert::ExpectException<std::invalid_argument>([&] { PNumber result = num1 / num4; });
        }

        TEST_METHOD(Subtraction)
        {
            PNumber num1(10.0, 10, 2);
            PNumber num4(20.0, 10, 2);
            PNumber result = num4 - num1;
            Assert::AreEqual(10.0, result.number());
            Assert::AreEqual(10, result.base());
            Assert::AreEqual(2, result.precision());
        }

        TEST_METHOD(Multiplication)
        {
            PNumber num1(10.0, 10, 2);
            PNumber num4(20.0, 10, 2);
            PNumber result = num1 * num4;
            Assert::AreEqual(200.0, result.number());
            Assert::AreEqual(10, result.base());
            Assert::AreEqual(2, result.precision());
        }

        TEST_METHOD(Division)
        {
            PNumber num1(10.0, 10, 2);
            PNumber num4(20.0, 10, 2);
            PNumber result = num4 / num1;
            Assert::AreEqual(2.0, result.number());
            Assert::AreEqual(10, result.base());
            Assert::AreEqual(2, result.precision());
        }

        TEST_METHOD(AdditionRef)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 2);
            TPNumber *num4 = new PNumber(20.0, 10, 2);
            TPNumber *result = *num1 + *num4;
            Assert::AreEqual(30.0, result->number());
            Assert::AreEqual(10, result->base());
            Assert::AreEqual(2, result->precision());
        }

        TEST_METHOD(OperationsExceptinsBaseRef)
        {
            TPNumber* num1 = new PNumber(10.0, 4, 2);
            TPNumber* num4 = new PNumber(20.0, 10, 2);
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber *result = *num1 + *num4; });
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber *result = *num1 - *num4; });
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber *result = *num1 * *num4; });
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber *result = *num1 / *num4; });
        }

        TEST_METHOD(OperationsExceptinsPrecisionRef)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 4);
            TPNumber* num4 = new PNumber(20.0, 10, 2);
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber* result = *num1 + *num4; });
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber* result = *num1 - *num4; });
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber* result = *num1 * *num4; });
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber* result = *num1 / *num4; });
        }

        TEST_METHOD(OperationsExceptinDivisionByZeroRef)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 4);
            TPNumber* num4 = new PNumber(0.0, 10, 4);
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber* result = *num1 / *num4; });
        }

        TEST_METHOD(SubtractionRef)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 2);
            TPNumber* num4 = new PNumber(20.0, 10, 2);
            TPNumber* result = *num1 - *num4;
            Assert::AreEqual(-10.0, result->number());
            Assert::AreEqual(10, result->base());
            Assert::AreEqual(2, result->precision());
        }

        TEST_METHOD(MultiplicationRef)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 2);
            TPNumber* num4 = new PNumber(20.0, 10, 2);
            TPNumber* result = *num1 * *num4;
            Assert::AreEqual(200.0, result->number());
            Assert::AreEqual(10, result->base());
            Assert::AreEqual(2, result->precision());
        }

        TEST_METHOD(DivisionRef)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 2);
            TPNumber* num4 = new PNumber(20.0, 10, 2);
            TPNumber* result = *num4 / *num1;
            Assert::AreEqual(2.0, result->number());
            Assert::AreEqual(10, result->base());
            Assert::AreEqual(2, result->precision());
        }

        TEST_METHOD(Invert)
        {
            TPNumber *num1 = new PNumber(10.0, 10, 2);
            TPNumber* result = num1->Invert();
            Assert::AreEqual(0.1, result->number());
            Assert::AreEqual(10, result->base());
            Assert::AreEqual(2, result->precision());
            delete num1;
            delete result;
        }

        TEST_METHOD(InvertException)
        {
            TPNumber* num1 = new PNumber(0.0, 10, 2);
            Assert::ExpectException<std::invalid_argument>([&] { TPNumber* result = num1->Invert(); });
        }

        TEST_METHOD(Square)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 2);
            TPNumber* result = num1->Square();
            Assert::AreEqual(100.0, result->number());
            Assert::AreEqual(10, result->base());
            Assert::AreEqual(2, result->precision());
            delete num1;
            delete result;
        }

        TEST_METHOD(DivisionByZero)
        {
            TPNumber* num1 = new PNumber(10.0, 10, 2);
            TPNumber* num4 = new PNumber(0.0, 10, 2);
            Assert::ExpectException<std::invalid_argument>([&] {TPNumber* result = *num1 / *num4; });
            delete num1;
            delete num4;
        }
	};
}
