#include "Functions.h"

namespace Lab3 {

	int32_t Functions::findMinOddDigitIndex(int64_t a)
	{
		int32_t index = 1;
		int32_t minOddDigit = INT_MAX;
		int32_t minOddIndex = -1;

		while (a > 0) {
			uint16_t digit = a % 10;

			if (index % 2 == 1 && digit % 2 == 1) {
				if (digit < minOddDigit) {
					minOddDigit = digit;
					minOddIndex = index;
				}
			}
			a /= 10;
			index++;
		}

		return minOddIndex;

	}

	int64_t Functions::cyclicLeftShift(const int64_t& a, int16_t shift)
	{
		if (a < 0) {
			throw std::invalid_argument("Number need be positiv!");
		}
		std::string num = std::to_string(a);
		if (shift < 0)
			shift += num.length();
		shift %= num.length();
		std::string shiftedStr = num.substr(shift) + num.substr(0, shift);
		return std::stoll(shiftedStr);
	}

	int64_t Functions::insertDigits(int64_t a, int64_t b, int16_t n) {
		std::string strA = std::to_string(a);
		std::string strB = std::to_string(b);

		if (n < 1 || n > strA.length()) {
			throw std::out_of_range("Position n is out of range");
		}

		std::string result = strA.substr(0, n) + strB + strA.substr(n);

		return std::stoll(result);
	}

	double Functions::sumEvenBelowAntiDiagonal(const std::vector<std::vector<double>>& A)
	{
		int N = A.size();
		double sum = 0.0;

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (i + j >= N && static_cast<int>(A[i][j]) % 2 == 0) {
					sum += A[i][j];
				}
			}
		}

		return sum;
	}
}