#include "CppUnitTest.h"
#include "../Calcualtor/UAEditor.h"

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
            Assert::AreEqual(std::string( "100.00"), result->numberString());
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
            Assert::ExpectException<ComplexNumberParseException>([&] {complex.Invert(); });
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
}
