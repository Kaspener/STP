#include "UAEditor.h"

AEditor::~AEditor() = default;

CEditor::CEditor()
{
	m_number = TComplex().numberString();
	m_separator = " + i * ";
	editMode = EditMode::Actual;
}

CEditor::CEditor(double actual, double imaginary)
{
	m_number = TComplex(actual, imaginary).numberString();
	m_separator = imaginary >= 0 ? " + i * " : " - i * ";
	editMode = EditMode::Actual;
}

CEditor::CEditor(const std::string& number)
{
	TComplex num(number);
	m_number = num.numberString();
	m_separator = num.getImaginary() >= 0 ? " + i * " : " - i * ";
	editMode = EditMode::Actual;
}

void CEditor::setNumber(const std::string& number)
{
	m_number = TComplex(number).numberString();
}

bool CEditor::isNull() const noexcept
{
	return TComplex(m_number).isNull();
}

std::string CEditor::toggleMinus() noexcept
{
	if (editMode == EditMode::Actual) 
	{
		if (m_number[0] == '-') 
		{
			m_number = m_number.substr(1);
		}
		else
		{
			m_number = "-" + m_number;
		}
	}
	else
	{
		size_t position = m_number.find(m_separator);
		if (m_separator[1] == '+') m_separator[1] = '-';
		else m_separator[1] = '+';
		m_number = m_number.substr(0, position) + m_separator + m_number.substr(position + m_separator.length());
	}
	return m_number;
}

std::string CEditor::addNumber(int number)
{
	size_t position = m_number.find(m_separator);
	std::string left = m_number.substr(0, position);
	std::string right = m_number.substr(position + m_separator.length());
	if (editMode == EditMode::Actual) 
	{
		if (left == "0")
			m_number = std::to_string(number) + m_separator + right;
		else 
			m_number = left + std::to_string(number) + m_separator + right;
	}
	else
	{
		if (right == "0")
			m_number.pop_back();
		m_number += std::to_string(number);
	}
	return m_number;
}

std::string CEditor::addSeparator()
{
	size_t position = m_number.find(m_separator);
	if (position == std::string::npos) {
		m_number += m_separator + "0";
	}
	return m_number;
}

std::string CEditor::addNumberSeparator()
{
	size_t position = m_number.find(m_separator);
	std::string left = m_number.substr(0, position);
	std::string right = m_number.substr(position + m_separator.length());
	if (editMode == EditMode::Actual)
	{
		if (left.find(".") == std::string::npos)
			m_number = left + "." + m_separator + right;
	}
	else
	{
		if (right.find(".") == std::string::npos)
			m_number += ".";
	}
	return m_number;
}

CEditor::EditMode CEditor::changeEditMode()
{
	if (editMode == EditMode::Actual)
		editMode = EditMode::Imaginary;
	else
		editMode = EditMode::Actual;
	return editMode;
}

std::string CEditor::addZero()
{
	size_t position = m_number.find(m_separator);
	std::string left = m_number.substr(0, position);
	std::string right = m_number.substr(position + m_separator.length());
	if (editMode == EditMode::Actual)
	{
		if (left.find(".") != std::string::npos || left.length() == 0)
			m_number = left + "0" + m_separator + right;
	}
	else
	{
		if (right.find(".") != std::string::npos || right.length() == 0)
			m_number += "0";
	}
	return m_number;
}

std::string CEditor::BackSpace()
{
	size_t position = m_number.find(m_separator);
	std::string left = m_number.substr(0, position);
	std::string right = m_number.substr(position + m_separator.length());
	if (editMode == EditMode::Actual)
	{
		if (left != "0") 
		{
			left.pop_back();
			if (left.length() == 0 || left == "-")
				left = "0";
		}
	}
	else
	{
		if (right != "0")
		{
			right.pop_back();
			if (right.length() == 0 || right == "-")
				right = "0";
		}
	}
	m_number = left + m_separator + right;
	return m_number;
}

std::string CEditor::CE()
{
	*this = CEditor();
	return m_number;
}

std::string CEditor::Edit(Command command)
{
	switch (command)
	{
	case AEditor::cZero:
		addZero();
		break;
	case AEditor::cOne:
		addNumber(1);
		break;
	case AEditor::cTwo:
		addNumber(2);
		break;
	case AEditor::cThree:
		addNumber(3);
		break;
	case AEditor::cFour:
		addNumber(4);
		break;
	case AEditor::cFive:
		addNumber(5);
		break;
	case AEditor::cSize:
		addNumber(6);
		break;
	case AEditor::cSeven:
		addNumber(7);
		break;
	case AEditor::cEight:
		addNumber(8);
		break;
	case AEditor::cNine:
		addNumber(9);
		break;
	case AEditor::cSign:
		toggleMinus();
		break;
	case AEditor::cSeparatorFR:
		addNumberSeparator();
		break;
	case AEditor::cSeparatorC:
		addSeparator();
		break;
	case AEditor::cBS:
		BackSpace();
		break;
	case AEditor::cCE:
		CE();
		break;
	default:
		break;
	}
	return m_number;
}
