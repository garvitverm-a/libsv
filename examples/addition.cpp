#include <iostream>
#include "sv.h"

using namespace sv;

int main(void)
{
    using namespace string_literals;
    string sv                = "hello world"_sv;
    string::builder s        = sv.as_builder();
    string::builder greeting = sv.substring(5).as_builder();

    std::cout << sv << std::endl;
    std::cout << greeting + " someone"_sv << std::endl;
    std::cout << sv.substring(5) << std::endl;
    std::cout << s.substring(5) << std::endl;

    return 0;
}
