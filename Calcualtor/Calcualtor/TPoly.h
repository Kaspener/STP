#pragma once
#include <set>
#include "TMember.h"

class TPoly
{
public:
	TPoly() {}
	TPoly(long long coeff, unsigned long long degree) { polynom.insert(TMember(coeff, degree)); }
	unsigned long long degree() const noexcept;
	long long coeff(unsigned long long degree) const noexcept;
	void addMember(long long coeff, unsigned long long degree);
	void clear();
	TPoly add(const TPoly& other) const noexcept;
	TPoly multiply(const TPoly& other) const noexcept;
	TPoly subtract(const TPoly& other) const noexcept;
	TPoly negate() const noexcept;
	TPoly differentiate() const noexcept;
	long long calculate(long long x) const noexcept;
	TMember at(size_t index) const;

	bool operator==(const TPoly& other) const noexcept { return polynom == other.polynom; }
private:
	std::set<TMember> polynom;
};

