#include <iostream>
#include "UAEditor.h"

int main() {
	CEditor editor(5, 14);
	std::cout << editor.number() << std::endl;
	editor.toggleMinus();
	std::cout << editor.number() << std::endl;
	editor.addNumber(5);
	std::cout << editor.number() << std::endl;
	return 0;
}