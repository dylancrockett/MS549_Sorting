#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "sorting_test.hpp"

using namespace std;
using namespace sorting_testing;

int main() {
	//enable unicode in wcout
	_setmode(_fileno(stdout), _O_U16TEXT);

	test_performance();

    return 0;
}