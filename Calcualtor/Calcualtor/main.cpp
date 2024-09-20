#include <iostream>
#include "UAEditor.h"
#include "UMemory.h"

int main() {
	std::unique_ptr<TANumber> com = std::make_unique<TComplex>(5, 13);
	std::unique_ptr<TANumber> b = std::make_unique<TComplex>(13, 13);
	std::unique_ptr<TANumber> now = std::make_unique<TComplex>(133, 13);
	TMemory<TComplex> a(com);
	a.write(now);
	a += *b;
	std::cout << a.take()->numberString() << std::endl;
	a.clear();
	return 0;
}