//
// Created by admin on 12.12.2021.
//

#include "ClassWithIdAndName.h"

ClassWithIdAndName::ClassWithIdAndName(int id, const std::string &name) : Id(id), Name(name) {}

ClassWithIdAndName::~ClassWithIdAndName() {

}

int ClassWithIdAndName::getId() const {
    return Id;
}

void ClassWithIdAndName::setId(int id) {
    Id = id;
}

const std::string &ClassWithIdAndName::getName() const {
    return Name;
}

void ClassWithIdAndName::setName(const std::string &name) {
    Name = name;
}
