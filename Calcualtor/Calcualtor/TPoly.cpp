#include "TPoly.h"

unsigned long long TPoly::degree() const noexcept
{
    if (polynom.empty()) {
        return 0;
    }
    return polynom.begin()->getDegree();
}

long long TPoly::coeff(unsigned long long degree) const noexcept
{
    for (auto& it : polynom) {
        if (it.getDegree() == degree) {
            return it.getCoeff();
        }
    }
    return 0;
}

void TPoly::addMember(long long coeff, unsigned long long degree)
{
    if (coeff == 0) {
        return;
    }
    auto it = polynom.find(TMember(coeff, degree));
    if (it != polynom.end()) {
        int newCoeff = it->getCoeff() + coeff;
        polynom.erase(it);
        if (newCoeff != 0) {
            polynom.insert(TMember(newCoeff, degree));
        }
    }
    else {
        polynom.insert(TMember(coeff, degree));
    }
}

void TPoly::clear()
{
    polynom.clear();
}

TPoly TPoly::add(const TPoly& other) const noexcept
{
    TPoly result = *this;
    for (const auto& member : other.polynom) {
        result.addMember(member.getCoeff(), member.getDegree());
    }
    return result;
}

TPoly TPoly::multiply(const TPoly& other) const noexcept
{
    TPoly result;
    for (const auto& member1 : polynom) {
        for (const auto& member2 : other.polynom) {
            result.addMember(member1.getCoeff() * member2.getCoeff(), member1.getDegree() + member2.getDegree());
        }
    }
    return result;
}

TPoly TPoly::subtract(const TPoly& other) const noexcept
{
    TPoly result = *this;
    for (const auto& member : other.polynom) {
        result.addMember(-member.getCoeff(), member.getDegree());
    }
    return result;
}

TPoly TPoly::negate() const noexcept
{
    TPoly result;
    for (const auto& member : polynom) {
        result.addMember(-member.getCoeff(), member.getDegree());
    }
    return result;
}

TPoly TPoly::differentiate() const noexcept
{
    TPoly result;
    for (const auto& member : polynom) {
        TMember diffMember = member.differentiate();
        if (diffMember.getCoeff() != 0) {
            result.addMember(diffMember.getCoeff(), diffMember.getDegree());
        }
    }
    return result;
}

long long TPoly::calculate(long long x) const noexcept
{
    double result = 0;
    for (const auto& member : polynom) {
        result += member.calculate(x);
    }
    return result;
}

TMember TPoly::at(size_t index) const
{
    if (index >= polynom.size()) {
        throw std::out_of_range("Index " + std::to_string(index) + " out of range");
    }
    auto it = polynom.begin();
    std::advance(it, index);
    return *it;
}
