#include "PNumber.h"

namespace STP {

    TPNumber* PNumber::operator+(const TPNumber& d) const
    {
        const PNumber* pNumberD = dynamic_cast<const PNumber*>(&d);
        if (pNumberD == nullptr) {
            throw std::invalid_argument("Operands must be of type PNumber");
        }

        if (base_ != pNumberD->base_ || precision_ != pNumberD->precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }

        double resultValue = number_ + pNumberD->number_;
        return new PNumber(resultValue, base_, precision_);
    }

    TPNumber* PNumber::operator-(const TPNumber& d) const
    {
        const PNumber* pNumberD = dynamic_cast<const PNumber*>(&d);
        if (pNumberD == nullptr) {
            throw std::invalid_argument("Operands must be of type PNumber");
        }

        if (base_ != pNumberD->base_ || precision_ != pNumberD->precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }

        double resultValue = number_ - pNumberD->number_;
        return new PNumber(resultValue, base_, precision_);
    }

    TPNumber* PNumber::operator*(const TPNumber& d) const
    {
        const PNumber* pNumberD = dynamic_cast<const PNumber*>(&d);
        if (pNumberD == nullptr) {
            throw std::invalid_argument("Operands must be of type PNumber");
        }

        if (base_ != pNumberD->base_ || precision_ != pNumberD->precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }

        double resultValue = number_ * pNumberD->number_;
        return new PNumber(resultValue, base_, precision_);
    }

    TPNumber* PNumber::operator/(const TPNumber& d) const
    {
        const PNumber* pNumberD = dynamic_cast<const PNumber*>(&d);
        if (pNumberD == nullptr) {
            throw std::invalid_argument("Operands must be of type PNumber");
        }

        if (base_ != pNumberD->base_ || precision_ != pNumberD->precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }

        if (pNumberD->number_ == 0.0) {
            throw std::invalid_argument("Division by zero");
        }

        double resultValue = number_ / pNumberD->number_;
        return new PNumber(resultValue, base_, precision_);
    }

    PNumber PNumber::operator+(const PNumber& d) const
    {
        if (base_ != d.base_ || precision_ != d.precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }
        double resultValue = number_ + d.number_;
        return PNumber(resultValue, base_, precision_);
    }

    PNumber PNumber::operator-(const PNumber& d) const
    {
        if (base_ != d.base_ || precision_ != d.precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }
        double resultValue = number_ - d.number_;
        return PNumber(resultValue, base_, precision_);
    }

    PNumber PNumber::operator*(const PNumber& d) const
    {
        if (base_ != d.base_ || precision_ != d.precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }
        double resultValue = number_ * d.number_;
        return PNumber(resultValue, base_, precision_);
    }

    PNumber PNumber::operator/(const PNumber& d) const
    {
        if (base_ != d.base_ || precision_ != d.precision_) {
            throw std::invalid_argument("Bases and precisions must match");
        }

        if (d.number_ == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        double resultValue = number_ / d.number_;
        return PNumber(resultValue, base_, precision_);
    }

    TPNumber* PNumber::Invert() const
    {
        if (number_ == 0.0) {
            throw std::invalid_argument("Cannot invert zero");
        }

        double resultValue = 1.0 / number_;
        return new PNumber(resultValue, base_, precision_);
    }

    TPNumber* PNumber::Square() const noexcept
    {
        double resultValue = number_ * number_;
        return new PNumber(resultValue, base_, precision_);
    }

}