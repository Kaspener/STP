#include "CppUnitTest.h"
#include "../Calcualtor/UAEditor.h"
#include "../Calcualtor/UMemory.h"
#include "../Calcualtor/UProcssr.h"
#include "../Calcualtor/TSet.h"
#include "../Calcualtor/TPoly.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> std::wstring ToString<CEditor::EditMode>(const CEditor::EditMode& mode) {
				switch (mode) {
				case CEditor::EditMode::Actual: return L"Actual";
				case CEditor::EditMode::Imaginary: return L"Imaginary";
				default: return L"Unknown";
				}
			}
		}
	}
}

namespace CalcucatorTest
{
	TEST_CLASS(CalcucatorTest)
	{
	public:

		TEST_METHOD(ConstructorDoubleBasePrecision)
		{
			TPNumber num2(234.153, 5, 8);
			Assert::AreEqual(std::string("1414.03403030"), num2.numberString());
		}

		TEST_METHOD(ConstructorDoubleBasePrecisionExceptions)
		{
			Assert::ExpectException<InvalidBaseException>([] {TPNumber num1(10.0, 20, 2); });
			Assert::ExpectException<InvalidBaseException>([] {TPNumber num1(10.0, 1, 2); });
			Assert::ExpectException<InvalidPrecisionException>([] {TPNumber num1(10.0, 6, -1); });
		}

		TEST_METHOD(ConstructorStringBasePrecisionExceptions)
		{
			Assert::ExpectException<InvalidBaseException>([] {TPNumber num1("10.0", "20", "2"); });
			Assert::ExpectException<InvalidBaseException>([] {TPNumber num1("10.0", "1", "2"); });
			Assert::ExpectException<InvalidPrecisionException>([] {TPNumber num1("10.0", "6", "-1"); });
			Assert::ExpectException<std::invalid_argument>([] {TPNumber num1("1~0.0", "6", "1"); });
			Assert::ExpectException<std::invalid_argument>([] {TPNumber num1("80.0", "6", "1"); });
			Assert::ExpectException<std::invalid_argument>([] {TPNumber num1("10.0", "Z", "2"); });

		}

		TEST_METHOD(ConstructorStringBasePrecision)
		{
			TPNumber num2("-A.B9", "16", "4");
			Assert::AreEqual(-10.7227, num2.number(), 0.0001);
			Assert::AreEqual(16, num2.base());
			Assert::AreEqual(4, num2.precision());
		}

		TEST_METHOD(SetBaseFromInt)
		{
			TPNumber num1(10.0, 10, 2);
			num1.setBase(2);
			Assert::AreEqual(2, num1.base());
		}

		TEST_METHOD(SetBaseFromIntExceptions)
		{
			TPNumber num1("10.0", "3", "2");
			Assert::ExpectException<InvalidBaseException>([&] { num1.setBase(20); });
			Assert::ExpectException<InvalidBaseException>([&] { num1.setBase(1); });
		}

		TEST_METHOD(SetBaseFromString)
		{
			TPNumber num1(10.0, 10, 2);
			num1.setBase("8");
			Assert::AreEqual(8, num1.base());
		}

		TEST_METHOD(SetBaseFromStringExceptions)
		{
			TPNumber num1("10.0", "3", "2");
			Assert::ExpectException<InvalidBaseException>([&] { num1.setBase("20"); });
			Assert::ExpectException<InvalidBaseException>([&] { num1.setBase("1"); });
			Assert::ExpectException<std::invalid_argument>([&] { num1.setBase("q`sdfa"); });
		}

		TEST_METHOD(SetPrecisionFromInt)
		{
			TPNumber num1(10.0, 10, 2);
			num1.setPrecision(4);
			Assert::AreEqual(4, num1.precision());
		}

		TEST_METHOD(SetPrecisionFromIntExceptions)
		{
			TPNumber num1("10.0", "3", "2");
			Assert::ExpectException<InvalidPrecisionException>([&] { num1.setPrecision(-1); });
		}

		TEST_METHOD(SetPrecisionFromString)
		{
			TPNumber num1(10.0, 10, 2);
			num1.setPrecision("5");
			Assert::AreEqual(5, num1.precision());
		}

		TEST_METHOD(SetPrecisionFromStringExceptions)
		{
			TPNumber num1("10.0", "3", "2");
			Assert::ExpectException<InvalidPrecisionException>([&] { num1.setPrecision("-1"); });
			Assert::ExpectException<std::invalid_argument>([&] { num1.setPrecision("`dsgfa"); });
		}

		TEST_METHOD(AdditionRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(20.0, 10, 2);
			std::unique_ptr<TANumber> result = *num1 + *num4;
			Assert::AreEqual(std::string("30.00"), result->numberString());
		}

		TEST_METHOD(OperationsExceptinsBaseRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 4, 2);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(20.0, 10, 2);
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 + *num4; });
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 - *num4; });
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 * *num4; });
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 / *num4; });
		}

		TEST_METHOD(OperationsExceptinsPrecisionRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 4);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(20.0, 10, 2);
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 + *num4; });
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 - *num4; });
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 * *num4; });
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 / *num4; });
		}

		TEST_METHOD(OperationsExceptinDivisionByZeroRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 4);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(0.0, 10, 4);
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = *num1 / *num4; });
		}

		TEST_METHOD(SubtractionRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(20.0, 10, 2);
			std::unique_ptr<TANumber> result = *num1 - *num4;
			Assert::AreEqual(std::string("-10.00"), result->numberString());
		}

		TEST_METHOD(MultiplicationRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(20.0, 10, 2);
			std::unique_ptr<TANumber> result = *num1 * *num4;
			Assert::AreEqual(std::string("200.00"), result->numberString());
		}

		TEST_METHOD(DivisionRef)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(20.0, 10, 2);
			std::unique_ptr<TANumber> result = *num4 / *num1;
			Assert::AreEqual(std::string("2.00"), result->numberString());
		}

		TEST_METHOD(Invert)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> result = num1->Invert();
			Assert::AreEqual(std::string("0.10"), result->numberString());
		}

		TEST_METHOD(InvertException)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(0.0, 10, 2);
			Assert::ExpectException<std::invalid_argument>([&] { std::unique_ptr<TANumber> result = num1->Invert(); });
		}

		TEST_METHOD(Square)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> result = num1->Square();
			Assert::AreEqual(std::string("100.00"), result->numberString());
		}

		TEST_METHOD(DivisionByZero)
		{
			std::unique_ptr<TANumber> num1 = std::make_unique<TPNumber>(10.0, 10, 2);
			std::unique_ptr<TANumber> num4 = std::make_unique<TPNumber>(0.0, 10, 2);
			Assert::ExpectException<std::invalid_argument>([&] {std::unique_ptr<TANumber> result = *num1 / *num4; });
		}

		TEST_METHOD(SetStringNumber)
		{
			TPNumber number(10.0, 10, 2);
			number.setNumber("8.000");
			Assert::AreEqual(std::string("8.00"), number.numberString());
		}

		TEST_METHOD(SetStringNumberException)
		{
			TPNumber number(30.0, 4, 2);
			Assert::ExpectException<InvalidBaseDigitException>([&] {number.setNumber("8.00"); });
		}
	};

	TEST_CLASS(TComplexTest)
	{
	public:
		TEST_METHOD(ConstructorAndSetNumber)
		{
			TComplex complex1(3, 4);
			Assert::AreEqual(std::string("3 + i * 4"), complex1.numberString());

			TComplex complex2;
			complex2.setNumber("5 - i * 6");
			Assert::AreEqual(std::string("5 - i * 6"), complex2.numberString());
		}

		TEST_METHOD(Invert)
		{
			TComplex complex1(3, 4);
			auto inverted = complex1.Invert();
			Assert::AreEqual(0.12, dynamic_cast<TComplex*>(inverted.get())->getActual(), 1e-9);
			Assert::AreEqual(-0.16, dynamic_cast<TComplex*>(inverted.get())->getImaginary(), 1e-9);

			TComplex complex2(1, 0);
			auto inverted2 = complex2.Invert();
			Assert::AreEqual(1.0, dynamic_cast<TComplex*>(inverted2.get())->getActual());
			Assert::AreEqual(0.0, dynamic_cast<TComplex*>(inverted2.get())->getImaginary());
		}

		TEST_METHOD(Square)
		{
			TComplex complex1(3, 4);
			auto squared = complex1.Square();
			Assert::AreEqual(-7.0, dynamic_cast<TComplex*>(squared.get())->getActual(), 1e-9);
			Assert::AreEqual(24.0, dynamic_cast<TComplex*>(squared.get())->getImaginary(), 1e-9);

			TComplex complex2(1, 2);
			auto squared2 = complex2.Square();
			Assert::AreEqual(-3.0, dynamic_cast<TComplex*>(squared2.get())->getActual());
			Assert::AreEqual(4.0, dynamic_cast<TComplex*>(squared2.get())->getImaginary());
		}

		TEST_METHOD(SetNumberInvalidFormat)
		{
			TComplex complex;
			Assert::ExpectException<ComplexNumberParseException>([&] {complex.setNumber("invalid_format"); });
			Assert::ExpectException<ComplexNumberParseException>([&] {complex.setNumber("2 + 3i"); });
		}

		TEST_METHOD(InvertZero)
		{
			TComplex complex(0, 0);
			Assert::ExpectException<DivisionByZeroException>([&] {complex.Invert(); });
		}

		TEST_METHOD(SquareZero)
		{
			TComplex complex(0, 0);
			auto squared = complex.Square();
			Assert::AreEqual(0.0, dynamic_cast<TComplex*>(squared.get())->getActual());
			Assert::AreEqual(0.0, dynamic_cast<TComplex*>(squared.get())->getImaginary());
		}

		TEST_METHOD(Modulus)
		{
			TComplex complex1(3, 4);
			Assert::AreEqual(5.0, complex1.Modulus(), 1e-9);

			TComplex complex2(5, 12);
			Assert::AreEqual(13.0, complex2.Modulus(), 1e-9);
		}

		TEST_METHOD(AngleInRadians)
		{
			TComplex complex1(1, 1);
			Assert::AreEqual(M_PI / 4, complex1.AngleInRadians(), 1e-9);

			TComplex complex2(-1, 1);
			Assert::AreEqual(3 * M_PI / 4, complex2.AngleInRadians(), 1e-9);
		}

		TEST_METHOD(AngleInDegrees)
		{
			TComplex complex1(1, 1);
			Assert::AreEqual(45.0, complex1.AngleInDegrees(), 1e-9);

			TComplex complex2(-1, 1);
			Assert::AreEqual(135.0, complex2.AngleInDegrees(), 1e-9);
		}

		TEST_METHOD(Power)
		{
			TComplex complex1(1, 1);
			auto powered = complex1.Power(3);
			Assert::AreEqual(-2.0, dynamic_cast<TComplex*>(powered.get())->getActual(), 1e-9);
			Assert::AreEqual(2.0, dynamic_cast<TComplex*>(powered.get())->getImaginary(), 1e-9);

			TComplex complex2(0, 1);
			auto powered2 = complex2.Power(4);
			Assert::AreEqual(1.0, dynamic_cast<TComplex*>(powered2.get())->getActual(), 1e-9);
			Assert::AreEqual(0.0, dynamic_cast<TComplex*>(powered2.get())->getImaginary(), 1e-9);
		}

		TEST_METHOD(Sqrt)
		{
			TComplex complex1(4, 0);
			auto sqrt1 = complex1.Sqrt();
			Assert::AreEqual(2.0, dynamic_cast<TComplex*>(sqrt1.get())->getActual(), 1e-5);
			Assert::AreEqual(0.0, dynamic_cast<TComplex*>(sqrt1.get())->getImaginary(), 1e-5);

			TComplex complex2(0, 9);
			auto sqrt2 = complex2.Sqrt();
			Assert::AreEqual(2.12132, dynamic_cast<TComplex*>(sqrt2.get())->getActual(), 1e-5);
			Assert::AreEqual(2.12132, dynamic_cast<TComplex*>(sqrt2.get())->getImaginary(), 1e-5);
		}
	};

	TEST_CLASS(ÑEditorTests)
	{
	public:

		TEST_METHOD(TestConstructorDefault)
		{
			CEditor editor;
			Assert::AreEqual(std::string("0 + i * 0"), editor.number());
		}

		TEST_METHOD(TestConstructorWithDoublesPositiveImaginary)
		{
			CEditor editor(5.0, 3.0);
			Assert::AreEqual(std::string("5 + i * 3"), editor.number());
		}

		TEST_METHOD(TestConstructorWithDoublesNegativeImaginary)
		{
			CEditor editor(5.0, -3.0);
			Assert::AreEqual(std::string("5 - i * 3"), editor.number());
		}

		TEST_METHOD(TestConstructorWithStringPositiveImaginary)
		{
			CEditor editor("5 + i * 3");
			Assert::AreEqual(std::string("5 + i * 3"), editor.number());
		}

		TEST_METHOD(TestConstructorWithStringNegativeImaginary)
		{
			CEditor editor("5 - i * 3");
			Assert::AreEqual(std::string("5 - i * 3"), editor.number());
		}

		TEST_METHOD(TestSetNumber)
		{
			CEditor editor;
			editor.setNumber("3 + i * 4");
			Assert::AreEqual(std::string("3 + i * 4"), editor.number());
		}

		TEST_METHOD(TestToggleMinusPositive)
		{
			CEditor editor(5.0, 3.0);
			Assert::AreEqual(std::string("-5 + i * 3"), editor.toggleMinus());
		}

		TEST_METHOD(TestToggleMinusNegative)
		{
			CEditor editor(-5.0, 3.0);
			Assert::AreEqual(std::string("5 + i * 3"), editor.toggleMinus());
		}

		TEST_METHOD(TestAddNumber)
		{
			CEditor editor(1.0, 2.0);
			Assert::AreEqual(std::string("16 + i * 2"), editor.addNumber(6));
		}

		TEST_METHOD(TestAddZero)
		{
			CEditor editor;
			Assert::AreEqual(std::string("0 + i * 0"), editor.addZero());
		}

		TEST_METHOD(TestBackSpace)
		{
			CEditor editor("12 + i * 34");
			Assert::AreEqual(std::string("1 + i * 34"), editor.BackSpace());
		}

		TEST_METHOD(TestCE)
		{
			CEditor editor("12 + i * 34");
			Assert::AreEqual(std::string("0 + i * 0"), editor.CE());
		}

		TEST_METHOD(TestChangeEditMode)
		{
			CEditor editor;
			Assert::AreEqual(CEditor::EditMode::Imaginary, editor.changeEditMode());
			Assert::AreEqual(CEditor::EditMode::Actual, editor.changeEditMode());
		}

		TEST_METHOD(TestBackSpaceRight)
		{
			CEditor editor("12 + i * 3");
			editor.changeEditMode();
			Assert::AreEqual(std::string("12 + i * 0"), editor.BackSpace());
		}

		TEST_METHOD(TestAddSeparator_SeparatorAlreadyPresent)
		{
			CEditor editor("5 + i * 3");
			Assert::AreEqual(std::string("5 + i * 3"), editor.addSeparator());
		}

		TEST_METHOD(TestAddNumberSeparator_ActualWithoutDot)
		{
			CEditor editor("5 + i * 3");
			Assert::AreEqual(std::string("5. + i * 3"), editor.addNumberSeparator());
		}

		TEST_METHOD(TestAddNumberSeparator_ActualWithDot)
		{
			CEditor editor("5. + i * 3");
			Assert::AreEqual(std::string("5. + i * 3"), editor.addNumberSeparator());
		}

		TEST_METHOD(TestAddNumberSeparator_ImaginaryWithoutDot)
		{
			CEditor editor("5 + i * 3");
			editor.changeEditMode();
			Assert::AreEqual(std::string("5 + i * 3."), editor.addNumberSeparator());
		}

		TEST_METHOD(TestAddNumberSeparator_ImaginaryWithDot)
		{
			CEditor editor("5 + i * 3.");
			editor.changeEditMode();
			Assert::AreEqual(std::string("5 + i * 3."), editor.addNumberSeparator());
		}
	};

	TEST_CLASS(MemoryTest)
	{
	public:

		TEST_METHOD(TestWriteAndTake)
		{
			TMemory<TComplex> memory;
			TComplex complexNumber(5, 13);

			memory.write(complexNumber);
			auto result = memory.take();

			TComplex* resultComplex = dynamic_cast<TComplex*>(result.get());
			Assert::IsNotNull(resultComplex);
			Assert::AreEqual(5.0, resultComplex->getActual());
			Assert::AreEqual(13.0, resultComplex->getImaginary());
		}

		TEST_METHOD(TestAdd)
		{
			TMemory<TComplex> memory;
			std::unique_ptr<TANumber> complexNumber1 = std::make_unique<TComplex>(3, 4);
			std::unique_ptr<TANumber> complexNumber2 = std::make_unique<TComplex>(1, 2);

			memory.write(complexNumber1);
			memory += *complexNumber2;
			std::unique_ptr<TANumber> result = memory.take();

			TComplex* resultComplex = dynamic_cast<TComplex*>(result.get());
			Assert::IsNotNull(resultComplex);
			Assert::AreEqual(4.0, resultComplex->getActual());
			Assert::AreEqual(6.0, resultComplex->getImaginary());
		}

		TEST_METHOD(TestClear)
		{
			TMemory<TComplex> memory;
			TComplex complexNumber(5, 13);

			memory.write(complexNumber);
			memory.clear();
			auto result = memory.take();

			TComplex* resultComplex = dynamic_cast<TComplex*>(result.get());
			Assert::IsNotNull(resultComplex);
			Assert::AreEqual(0.0, resultComplex->getActual());
			Assert::AreEqual(0.0, resultComplex->getImaginary());
		}
	};

	TEST_CLASS(TProcTests)
	{
	public:

		TEST_METHOD(TestResetProc)
		{
			TProc<TComplex> processor;

			processor.resetProc();

			Assert::IsTrue(processor.getLeftOperand() != nullptr);
			Assert::IsTrue(processor.getRightOperand() != nullptr);
			Assert::AreEqual(static_cast<int>(TProc<TComplex>::None), static_cast<int>(processor.getOperation()));
		}

		TEST_METHOD(TestSetLeftOperand)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> complexNumber = std::make_unique<TComplex>(1, 1);

			processor.setLeftOperand(complexNumber);

			Assert::AreEqual(complexNumber->numberString(), processor.getLeftOperand()->numberString());
		}

		TEST_METHOD(TestSetRightOperand)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> complexNumber = std::make_unique<TComplex>(2, 2);

			processor.setRightOperand(complexNumber);

			Assert::AreEqual(complexNumber->numberString(), processor.getRightOperand()->numberString());
		}

		TEST_METHOD(TestAdditionOperation)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> leftNumber = std::make_unique<TComplex>(1, 1);
			std::unique_ptr<TANumber> rightNumber = std::make_unique<TComplex>(2, 2);
			processor.setLeftOperand(leftNumber);
			processor.setRightOperand(rightNumber);
			processor.setOperation(TProc<TComplex>::Add);

			processor.doOperation();

			Assert::AreEqual(TComplex(3, 3).numberString(), processor.getLeftOperand()->numberString());
		}

		TEST_METHOD(TestSubtractionOperation)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> leftNumber = std::make_unique<TComplex>(5, 5);
			std::unique_ptr<TANumber> rightNumber = std::make_unique<TComplex>(2, 2);
			processor.setLeftOperand(leftNumber);
			processor.setRightOperand(rightNumber);
			processor.setOperation(TProc<TComplex>::Sub);

			processor.doOperation();

			Assert::AreEqual(TComplex(3, 3).numberString(), processor.getLeftOperand()->numberString());
		}

		TEST_METHOD(TestMultiplicationOperation)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> leftNumber = std::make_unique<TComplex>(1, 1);
			std::unique_ptr<TANumber> rightNumber = std::make_unique<TComplex>(2, 2);
			processor.setLeftOperand(leftNumber);
			processor.setRightOperand(rightNumber);
			processor.setOperation(TProc<TComplex>::Mul);

			processor.doOperation();

			Assert::AreEqual(TComplex(0, 4).numberString(), processor.getLeftOperand()->numberString());
		}

		TEST_METHOD(TestDivisionOperation)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> leftNumber = std::make_unique<TComplex>(1, 1);
			std::unique_ptr<TANumber> rightNumber = std::make_unique<TComplex>(1, -1);
			processor.setLeftOperand(leftNumber);
			processor.setRightOperand(rightNumber);
			processor.setOperation(TProc<TComplex>::Div);

			processor.doOperation();

			Assert::AreEqual(TComplex(0, 1).numberString(), processor.getLeftOperand()->numberString());
		}

		TEST_METHOD(TestSquareFunction)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> rightNumber = std::make_unique<TComplex>(2, 3);
			processor.setRightOperand(rightNumber);

			processor.doFunction(TProc<TComplex>::Sqr);

			Assert::AreEqual(TComplex(-5, 12).numberString(), processor.getRightOperand()->numberString());
		}

		TEST_METHOD(TestInvertFunction)
		{
			TProc<TComplex> processor;
			std::unique_ptr<TANumber> rightNumber = std::make_unique<TComplex>(2, 3);
			processor.setRightOperand(rightNumber);

			processor.doFunction(TProc<TComplex>::Rev);

			Assert::AreEqual(TComplex(0.153846, -0.230769).numberString(), processor.getRightOperand()->numberString());
		}
	};

	TEST_CLASS(TFracTests)
	{
	public:

		TEST_METHOD(TestFractionCreation)
		{
			TFrac frac(3, 4);
			Assert::AreEqual(3LL, frac.getNumerator());
			Assert::AreEqual(4LL, frac.getDenominator());
		}

		TEST_METHOD(TestInvalidDenominator)
		{
			Assert::ExpectException<DivisionByZeroException>([]() {
				TFrac frac(1, 0);
				});
		}

		TEST_METHOD(TestAddition)
		{
			TFrac frac1(1, 2);
			TFrac frac2(1, 3);

			auto result = frac1 + frac2;
			TFrac* fracResult = dynamic_cast<TFrac*>(result.get());

			Assert::AreEqual(5LL, fracResult->getNumerator());
			Assert::AreEqual(6LL, fracResult->getDenominator());
		}

		TEST_METHOD(TestSubtraction)
		{
			TFrac frac1(3, 4);
			TFrac frac2(1, 4);

			auto result = frac1 - frac2;
			TFrac* fracResult = dynamic_cast<TFrac*>(result.get());

			Assert::AreEqual(1LL, fracResult->getNumerator());
			Assert::AreEqual(2LL, fracResult->getDenominator());
		}

		TEST_METHOD(TestMultiplication)
		{
			TFrac frac1(2, 3);
			TFrac frac2(3, 4);

			auto result = frac1 * frac2;
			TFrac* fracResult = dynamic_cast<TFrac*>(result.get());

			Assert::AreEqual(1LL, fracResult->getNumerator());
			Assert::AreEqual(2LL, fracResult->getDenominator());
		}

		TEST_METHOD(TestDivision)
		{
			TFrac frac1(2, 3);
			TFrac frac2(3, 4);

			auto result = frac1 / frac2;
			TFrac* fracResult = dynamic_cast<TFrac*>(result.get());

			Assert::AreEqual(8LL, fracResult->getNumerator());
			Assert::AreEqual(9LL, fracResult->getDenominator());
		}

		TEST_METHOD(TestDivisionByZero)
		{
			TFrac frac1(1, 2);
			TFrac frac2(0, 1);

			Assert::ExpectException<DivisionByZeroException>([&]() {
				frac1 / frac2;
				});
		}

		TEST_METHOD(TestInvert)
		{
			TFrac frac(2, 3);

			auto inverted = frac.Invert();
			TFrac* fracInverted = dynamic_cast<TFrac*>(inverted.get());

			Assert::AreEqual(3LL, fracInverted->getNumerator());
			Assert::AreEqual(2LL, fracInverted->getDenominator());
		}

		TEST_METHOD(TestSquare)
		{
			TFrac frac(2, 3);

			auto squared = frac.Square();
			TFrac* fracSquared = dynamic_cast<TFrac*>(squared.get());

			Assert::AreEqual(4LL, fracSquared->getNumerator());
			Assert::AreEqual(9LL, fracSquared->getDenominator());
		}

		TEST_METHOD(TestEquality)
		{
			TFrac frac1(2, 3);
			TFrac frac2(4, 6);

			Assert::IsTrue(frac1 == frac2);
		}

		TEST_METHOD(TestInequality)
		{
			TFrac frac1(1, 2);
			TFrac frac2(2, 3);

			Assert::IsTrue(frac1 != frac2);
		}

		TEST_METHOD(TestValidStringInput)
		{
			TFrac frac;
			frac.setNumber("3/4");

			Assert::AreEqual(3LL, frac.getNumerator());
			Assert::AreEqual(4LL, frac.getDenominator());
		}

		TEST_METHOD(TestValidStringInputNegative)
		{
			TFrac frac;
			frac.setNumber("-3/5");

			Assert::AreEqual(-3LL, frac.getNumerator());
			Assert::AreEqual(5LL, frac.getDenominator());
		}

		TEST_METHOD(TestInvalidStringInputFormat)
		{
			TFrac frac;
			Assert::ExpectException<FracNumberParseException>([&]() {
				frac.setNumber("34");
				});
		}

		TEST_METHOD(TestInvalidStringInputDenominatorZero)
		{
			TFrac frac;
			Assert::ExpectException<DivisionByZeroException>([&]() {
				frac.setNumber("3/0");
				});
		}

		TEST_METHOD(TestInvalidStringInputNonNumeric)
		{
			TFrac frac;
			Assert::ExpectException<FracNumberParseException>([&]() {
				frac.setNumber("abc/3");
				});

			Assert::ExpectException<FracNumberParseException>([&]() {
				frac.setNumber("4/xyz");
				});
		}

		TEST_METHOD(TestValidStringInputWithSpaces)
		{
			TFrac frac;
			frac.setNumber("  6 / 8  ");

			Assert::AreEqual(3LL, frac.getNumerator());
			Assert::AreEqual(4LL, frac.getDenominator());
		}
	};

	TEST_CLASS(TSetTests)
	{
	public:

		TEST_METHOD(TestAdd)
		{
			TSet<int> set;
			set.add(1);
			Assert::IsTrue(set.belongs(1));
			Assert::AreEqual(static_cast<size_t>(1), set.size());
		}

		TEST_METHOD(TestRemove)
		{
			TSet<int> set;
			set.add(1);
			set.remove(1);
			Assert::IsFalse(set.belongs(1));
			Assert::AreEqual(static_cast<size_t>(0), set.size());
		}

		TEST_METHOD(TestEmpty)
		{
			TSet<int> set;
			Assert::IsTrue(set.empty());
			set.add(1);
			Assert::IsFalse(set.empty());
		}

		TEST_METHOD(TestSize)
		{
			TSet<int> set;
			set.add(1);
			set.add(2);
			Assert::AreEqual(static_cast<size_t>(2), set.size());
		}

		TEST_METHOD(TestUnions)
		{
			TSet<int> set1;
			set1.add(1);
			set1.add(2);

			TSet<int> set2;
			set2.add(2);
			set2.add(3);

			TSet<int> result = set1.unions(set2);
			Assert::AreEqual(static_cast<size_t>(3), result.size());
			Assert::IsTrue(result.belongs(1));
			Assert::IsTrue(result.belongs(2));
			Assert::IsTrue(result.belongs(3));
		}

		TEST_METHOD(TestSubtract)
		{
			TSet<int> set1;
			set1.add(1);
			set1.add(2);

			TSet<int> set2;
			set2.add(2);
			set2.add(3);

			TSet<int> result = set1.subtract(set2);
			Assert::AreEqual(static_cast<size_t>(1), result.size());
			Assert::IsTrue(result.belongs(1));
			Assert::IsFalse(result.belongs(2));
			Assert::IsFalse(result.belongs(3));
		}

		TEST_METHOD(TestMultiply)
		{
			TSet<int> set1;
			set1.add(1);
			set1.add(2);

			TSet<int> set2;
			set2.add(2);
			set2.add(3);

			TSet<int> result = set1.multiply(set2);
			Assert::AreEqual(static_cast<size_t>(1), result.size());
			Assert::IsTrue(result.belongs(2));
		}

		TEST_METHOD(TestAt)
		{
			TSet<int> set;
			set.add(1);
			set.add(2);

			Assert::AreEqual(1, set.at(0));
			Assert::AreEqual(2, set.at(1));

			Assert::ExpectException<std::out_of_range>([&set] { set.at(2); });
		}

		TEST_METHOD(TestClear)
		{
			TSet<int> set;
			set.add(1);
			set.add(2);

			set.clear();
			Assert::IsTrue(set.empty());
		}

		TEST_METHOD(TestAddTFrac)
		{
			TSet<TFrac> fracSet;
			TFrac frac1(1, 2);
			TFrac frac2(3, 4);

			fracSet.add(frac1);
			fracSet.add(frac2);

			Assert::AreEqual((size_t)2, fracSet.size());
			Assert::IsTrue(fracSet.belongs(frac1));
			Assert::IsTrue(fracSet.belongs(frac2));
		}

		TEST_METHOD(TestRemoveTFrac)
		{
			TSet<TFrac> fracSet;
			TFrac frac1(1, 2);
			TFrac frac2(3, 4);
			fracSet.add(frac1);
			fracSet.add(frac2);

			fracSet.remove(frac1);

			Assert::AreEqual((size_t)1, fracSet.size());
			Assert::IsFalse(fracSet.belongs(frac1));
			Assert::IsTrue(fracSet.belongs(frac2));
		}

		TEST_METHOD(TestUnionsTFrac)
		{
			TSet<TFrac> fracSet1;
			TSet<TFrac> fracSet2;
			TFrac frac1(1, 2);
			TFrac frac2(3, 4);
			TFrac frac3(5, 6);
			fracSet1.add(frac1);
			fracSet1.add(frac2);
			fracSet2.add(frac2);
			fracSet2.add(frac3);

			TSet<TFrac> unionSet = fracSet1.unions(fracSet2);

			Assert::AreEqual((size_t)3, unionSet.size());
			Assert::IsTrue(unionSet.belongs(frac1));
			Assert::IsTrue(unionSet.belongs(frac2));
			Assert::IsTrue(unionSet.belongs(frac3));
		}

		TEST_METHOD(TestSubtractTFrac)
		{
			TSet<TFrac> fracSet1;
			TSet<TFrac> fracSet2;
			TFrac frac1(1, 2);
			TFrac frac2(3, 4);
			TFrac frac3(5, 6);
			fracSet1.add(frac1);
			fracSet1.add(frac2);
			fracSet2.add(frac2);
			fracSet2.add(frac3);

			TSet<TFrac> subtractSet = fracSet1.subtract(fracSet2);

			Assert::AreEqual((size_t)1, subtractSet.size());
			Assert::IsTrue(subtractSet.belongs(frac1));
			Assert::IsFalse(subtractSet.belongs(frac2));
		}

		TEST_METHOD(TestMultiplyTFrac)
		{
			TSet<TFrac> fracSet1;
			TSet<TFrac> fracSet2;
			TFrac frac1(1, 2);
			TFrac frac2(3, 4);
			TFrac frac3(5, 6);
			fracSet1.add(frac1);
			fracSet1.add(frac2);
			fracSet2.add(frac2);
			fracSet2.add(frac3);

			TSet<TFrac> multiplySet = fracSet1.multiply(fracSet2);

			Assert::AreEqual((size_t)1, multiplySet.size());
			Assert::IsTrue(multiplySet.belongs(frac2));
		}

		TEST_METHOD(TestAtTFrac)
		{
			TSet<TFrac> fracSet;
			TFrac frac1(1, 2);
			TFrac frac2(3, 4);
			fracSet.add(frac1);
			fracSet.add(frac2);

			Assert::IsTrue(frac1 == fracSet.at(0));
			Assert::IsTrue(frac2 == fracSet.at(1));
		}

		TEST_METHOD(TestAtOutOfRange)
		{
			TSet<TFrac> fracSet;
			TFrac frac1(1, 2);
			fracSet.add(frac1);
			
			Assert::ExpectException<std::out_of_range>([&fracSet]() { fracSet.at(2); });
		}
	};

	TEST_CLASS(TPolyTests)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			TPoly poly(5, 3);
			unsigned long long res = poly.degree();
			auto t = poly.coeff(3);
			Assert::AreEqual(3ull, poly.degree());
			Assert::AreEqual(5ll, poly.coeff(3));
		}

		TEST_METHOD(ZeroPolyTest)
		{
			TPoly poly(0, 0);
			Assert::AreEqual(0ull, poly.degree());
			Assert::AreEqual(0ll, poly.coeff(0));
		}

		TEST_METHOD(AddTest)
		{
			TPoly poly1(3, 2);
			TPoly poly2(5, 2);
			TPoly result = poly1.add(poly2);
			Assert::AreEqual(2ull, result.degree());
			Assert::AreEqual(8ll, result.coeff(2));
		}

		TEST_METHOD(MultiplyTest)
		{
			TPoly poly1(2, 1);
			TPoly poly2(3, 2);
			TPoly result = poly1.multiply(poly2);
			Assert::AreEqual(3ull, result.degree());
			Assert::AreEqual(6ll, result.coeff(3));
		}

		TEST_METHOD(SubtractTest)
		{
			TPoly poly1(7, 3);
			TPoly poly2(2, 3);
			TPoly result = poly1.subtract(poly2);
			Assert::AreEqual(3ull, result.degree());
			Assert::AreEqual(5ll, result.coeff(3));
		}

		TEST_METHOD(DifferentiateTest)
		{
			TPoly poly(4, 3);
			TPoly result = poly.differentiate();
			Assert::AreEqual(2ull, result.degree());
			Assert::AreEqual(12ll, result.coeff(2));
		}

		TEST_METHOD(CalculateTest)
		{
			TPoly poly(2, 2);
			long long result = poly.calculate(3);
			Assert::AreEqual(18ll, result);
		}

		TEST_METHOD(AtTest)
		{
			TPoly poly;
			poly.addMember(6, 4);
			TMember member = poly.at(0);
			Assert::AreEqual(6ll, member.getCoeff());
			Assert::AreEqual(4ull, member.getDegree());
		}
	};
}