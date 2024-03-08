#include "build/version.h"
#include "lib.h"

#include <iostream>

int main (int, char **)
{

    // std::cout << "build " << BUILD_VERSION << std::endl;
    std::cout << "Version: " << version() << std::endl;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
