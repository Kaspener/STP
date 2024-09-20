#pragma once
#include <iostream>
#include <string>
class TMember
{
public:
	TMember(long long coeff, unsigned long long degree) : FCoeff(coeff), FDegree(degree)
	{
		if (FCoeff == 0) {
			FDegree = 0;
		}
	}

	unsigned long long getDegree() const noexcept { return FDegree; }
	void setDegree(unsigned long long degree) { FDegree = degree; }
	long long getCoeff() const noexcept { return FCoeff; }
	void setCoeff(long long coeff);

	TMember differentiate() const noexcept;
	long long calculate(int x) const noexcept;
	std::string toString() const noexcept;

	bool operator ==(const TMember& other) const noexcept { return FCoeff == other.FCoeff && FDegree == other.FDegree; }

	bool operator<(const TMember& other) const noexcept { return FDegree > other.FDegree; }

private:
	long long FCoeff;
	unsigned long long FDegree;
};

inline void TMember::setCoeff(long long coeff) {
	FCoeff = coeff;
	if (FCoeff == 0)
		FDegree = 0;
}

inline TMember TMember::differentiate() const noexcept
{
	if (FDegree == 0)
	{
		return TMember(0, 0);
	}
	return TMember(FCoeff * FDegree, FDegree - 1);
}

inline long long TMember::calculate(int x) const noexcept
{
	return FCoeff * pow(x, FDegree);
}

inline std::string TMember::toString() const noexcept
{
	std::string str;
	if (FCoeff != 0) {
		str = std::to_string(FCoeff);
		if (FDegree > 0) {
			str += "x";
			if (FDegree > 1) {
				str += "^" + std::to_string(FDegree);
			}
		}
	}
	else {
		str = "0";
	}
	return str;
}
