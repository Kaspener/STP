#pragma once
#include "TPNumber.h"

namespace STP {

    class PNumber :
        public TPNumber
    {
    public:
        PNumber(double value, int base, int precision)
            : TPNumber(value, base, precision) {}

        PNumber(const std::string& value, const std::string &base, const std::string &precision)
            : TPNumber(value, base, precision) {}

        virtual TPNumber* operator+(const TPNumber& d) const override;
        virtual TPNumber* operator-(const TPNumber& d) const override;
        virtual TPNumber* operator*(const TPNumber& d) const override;
        virtual TPNumber* operator/(const TPNumber& d) const override;
        virtual PNumber operator+(const PNumber& d) const;
        virtual PNumber operator-(const PNumber& d) const;
        virtual PNumber operator*(const PNumber& d) const;
        virtual PNumber operator/(const PNumber& d) const;

        virtual TPNumber* Invert() const override;
        virtual TPNumber* Square() const noexcept override;

        ~PNumber() override = default;

    };

}

