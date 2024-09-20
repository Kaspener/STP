#include <iostream>
#include "UAEditor.h"
#include "UMemory.h"
#include "TPoly.h"

int main() {
	TPoly poly(5, 3);
	std::cout << poly.degree() << std::endl;
	return 0;
}