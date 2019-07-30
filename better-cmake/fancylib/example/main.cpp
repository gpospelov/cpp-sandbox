#include <iostream>
#include "fancyutils.h"
#include "coreutils.h"

int main()
{
    std::cout << "Local example: Hello World! " << std::endl;
    std::cout << fancy::get_number()  << "\n";
    std::cout << *fancy::fizzbuzz(42) << "\n";
    return 0;
}
