#include "ontology.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "web.hpp"

SINGLETON_DEFINITOR(onto, Ontology)

onto::Ontology::Ontology() noexcept : core::Module("ontology")
{
    // std::ifstream file("test.cpp");
    // std::string data;
    // std::getline(file, data, '\0');
    // Web web;
    // web.applyData(data);
}
