
#include <iostream>
#include <string>
#include <sstream>
#include "Tree.hpp"

int main(int argv, char *argc[])
{

    Node topNode{8};
    topNode.Left(512);
    topNode.Right(14);
    topNode.Left().Right(125);

    std::cout << topNode;

    return 0;
}
