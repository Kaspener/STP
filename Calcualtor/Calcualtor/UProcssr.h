#pragma once
#include "UANumber.h"

template <class T>
class TProc
{
public:
	enum Operation {
		None,
		Add,
		Sub,
		Mul,
		Div
	};

	enum Function {
		Sqr,
		Rev
	};

	TProc();
	void resetProc();
	void resetOper() { m_operation = None; }
	void doOperation();
	void doFunction(Function function);
	std::unique_ptr<TANumber> getLeftOperand() const noexcept { return m_leftOperand->Clone(); }
	std::unique_ptr<TANumber> getRightOperand() const noexcept { return m_rightOperand->Clone(); }
	void setLeftOperand(const std::unique_ptr<TANumber>& number);
	void setRightOperand(const std::unique_ptr<TANumber>& number);
	Operation getOperation() const noexcept { return m_operation; }
	void setOperation(Operation operation) noexcept { m_operation = operation; }

private:
	std::unique_ptr<TANumber> m_leftOperand;
	std::unique_ptr<TANumber> m_rightOperand;
	Operation m_operation;
};

template<class T>
inline TProc<T>::TProc()
{
	resetProc();
}

template<class T>
inline void TProc<T>::resetProc()
{
	m_leftOperand = std::make_unique<T>();
	m_rightOperand = std::make_unique<T>();
	m_operation = None;
}

template<class T>
inline void TProc<T>::doOperation()
{
	try {
		switch (m_operation)
		{
		case Add:
			m_leftOperand = *m_leftOperand + *m_rightOperand;
			break;
		case Sub:
			m_leftOperand = *m_leftOperand - *m_rightOperand;
			break;
		case Mul:
			m_leftOperand = *m_leftOperand * *m_rightOperand;
			break;
		case Div:
			m_leftOperand = *m_leftOperand / *m_rightOperand;
			break;
		default:
			break;
		}
	}
	catch (DivisionByZeroException& ex)
	{

	}
	catch (DifferentBaseOrPrecision& ex)
	{

	}
	//TODO: сделать нормальное перенаправление в ERROR
}

template<class T>
inline void TProc<T>::doFunction(Function function)
{
	try {
		switch (function)
		{
		case Sqr:
			m_rightOperand = m_rightOperand->Square();
			break;
		case Rev:
			m_rightOperand = m_rightOperand->Invert();
			break;
		default:
			break;
		}
	}
	catch (DivisionByZeroException& ex)
	{
	}
	catch (DifferentBaseOrPrecision& ex)
	{
	}
	//TODO: сделать нормальное перенаправление в ERROR
}

template<class T>
inline void TProc<T>::setLeftOperand(const std::unique_ptr<TANumber>& number)
{
	const T* pB = dynamic_cast<const T*>(number.get());
	if (!pB)
	{
		throw TypeMismatchException();
	}
	m_leftOperand = number->Clone();
}

template<class T>
inline void TProc<T>::setRightOperand(const std::unique_ptr<TANumber>& number)
{
	const T* pB = dynamic_cast<const T*>(number.get());
	if (!pB)
	{
		throw TypeMismatchException();
	}
	m_rightOperand = number->Clone();
}