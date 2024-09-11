#include "CppUnitTest.h"
#include "../Lab3/Functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(TestFindMinOdd)
	{
	public:
		
		TEST_METHOD(FindMinOddDigitInStart)
		{
			int32_t result = Lab3::Functions::findMinOddDigitIndex(12543);
			Assert::AreEqual(5, result);
		}

		TEST_METHOD(ZeroMinOdd)
		{
			int32_t result = Lab3::Functions::findMinOddDigitIndex(0);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(OneEvenDigits)
		{
			int32_t result = Lab3::Functions::findMinOddDigitIndex(2);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(FindFirst)
		{
			int32_t result = Lab3::Functions::findMinOddDigitIndex(321);
			Assert::AreEqual(1, result);
		}
	};

	TEST_CLASS(TestShift)
	{
	public:

		TEST_METHOD(NegativNumber)
		{
			Assert::ExpectException<std::invalid_argument>([] {Lab3::Functions::cyclicLeftShift(-1236, 1); }, L"Number need be positiv!");
		}

		TEST_METHOD(StandartShift)
		{
			int64_t a = 12345;
			int8_t shift = 3;
			int64_t result = Lab3::Functions::cyclicLeftShift(a, shift);
			Assert::AreEqual(45123LL, result);
		}

		TEST_METHOD(NegativShift)
		{
			int64_t a = 12345;
			int8_t shift = -2;
			int64_t result = Lab3::Functions::cyclicLeftShift(a, shift);
			Assert::AreEqual(45123LL, result);
		}
	};

	TEST_CLASS(TestInsert)
	{
	public:

		TEST_METHOD(NegativN)
		{
			Assert::ExpectException<std::out_of_range>([] {Lab3::Functions::insertDigits(12345, 1, -1); }, L"Position n is out of range");
		}

		TEST_METHOD(OverN)
		{
			Assert::ExpectException<std::out_of_range>([] {Lab3::Functions::insertDigits(12345, 1, 6); }, L"Position n is out of range");
		}

		TEST_METHOD(Insert)
		{
			int64_t a = 123457;
			int64_t b = 6;
			int8_t n = 6;
			int64_t result = Lab3::Functions::insertDigits(123457, 6, 5);
			Assert::AreEqual(1234567LL, result);
		}
	};

	TEST_CLASS(TestMatrix)
	{
	public:

		TEST_METHOD(ZeroElementSMatrix)
		{
			std::vector<std::vector<double>> A = { {} };
			double result = Lab3::Functions::sumEvenBelowAntiDiagonal(A);
			Assert::AreEqual(0.0, result);
		}

		TEST_METHOD(MultipleElementMatrix)
		{
			std::vector<std::vector<double>> A = {
				{1.0, 2.0, 3.0},
				{4.0, 6.0, 8.0},
				{10.0, 12.0, 14.0}
			};
			double result = Lab3::Functions::sumEvenBelowAntiDiagonal(A);
			Assert::AreEqual(34.0, result);
		}

		TEST_METHOD(NoEvenBelowAntiDiagonal)
		{
			std::vector<std::vector<double>> A = {
				{1.1, 3.3},
				{5.5, 7.7}
			};
			double result = Lab3::Functions::sumEvenBelowAntiDiagonal(A);
			Assert::AreEqual(0.0, result);
		}
	};
}
