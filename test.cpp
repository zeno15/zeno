#include <cstdlib>
#include <iostream>

#include <zeno/Utility/XML.hpp>

int main(int _argc, char **_argv)
{
    zeno::XML::Document d;
    d.loadFromFile("C:/Users/Mark/Desktop/test.xml");

    std::cout << d.dumpTree() << std::endl;

    return EXIT_SUCCESS;
}
