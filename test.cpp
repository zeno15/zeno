#include <cstdlib>
#include <iostream>

#include <zeno/Utility/XML.hpp>

int main(int _argc, char **_argv)
{
    zeno::XML xml;

    xml.loadFromFile("C:/Users/Mark/Desktop/test.xml");

    return EXIT_SUCCESS;
}
