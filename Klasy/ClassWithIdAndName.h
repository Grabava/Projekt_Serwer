#ifndef PROJEKT_CLASSWITHIDANDNAME_H
#define PROJEKT_CLASSWITHIDANDNAME_H

#include <string>

class ClassWithIdAndName {
    int Id;
    std::string Name;

public:
    ClassWithIdAndName(int id, const std::string &name);

    virtual ~ClassWithIdAndName();

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);
};


#endif //PROJEKT_CLASSWITHIDANDNAME_H
