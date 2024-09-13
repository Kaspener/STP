#include <iostream>
#include "PNumber.h"

int main()
{
	try
	{
		STP::TPNumber *number = new STP::PNumber("E0.53333333", "16", "8");
		STP::TPNumber *number2 = new STP::PNumber("-A.B", "16", "8");
		STP::TPNumber *now = *number2 - *number;
		std::cout << number->number() << "\t" << number->numberString() << std::endl;
		std::cout << number2->number() << "\t" << number2->numberString() << std::endl;
		std::cout << now->number() << "\t" << now->numberString() << std::endl;
		now->setBase(10);
		std::cout << now->number() << "\t" << now->numberString() << std::endl;
		now->Invert();

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
