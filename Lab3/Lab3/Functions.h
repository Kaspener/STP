#pragma once
#include <string>
#include <stdexcept>
#include <vector>

namespace Lab3 {

	class Functions {
		Functions() = delete;
		Functions(const Functions& other) = delete;
		Functions(Functions&& other) = delete;

	public:
		static int32_t findMinOddDigitIndex(int64_t a);
		static int64_t cyclicLeftShift(const int64_t& a, int16_t shift);
		static int64_t insertDigits(int64_t a, int64_t b, int16_t n);
		static double sumEvenBelowAntiDiagonal(const std::vector<std::vector<double>>& A);
	};
}