#include "struct.hpp"
#include <iostream>
int main()
{

    Person p;

    auto &&[name, age] = p;
    name = "Fred";
    age = 42;

    std::cout<< p.age;
};