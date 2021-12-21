
#ifndef PROJEKT_RECEIVEANDRESEND_H
#define PROJEKT_RECEIVEANDRESEND_H

#include "../json.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

class ReceiveAndResend {

public:
    ReceiveAndResend(std::string message);
    json getResult();
    json result;

    inline void receiveAction(int id, json jsonWithData);

    json Login(json jsonWithData);

    json Registration(json jsonWithData);

    inline json GetAllGroups();

    inline json GetAllUsers();

    inline json CreateGroup(json jsonWithData);

    inline json AddUserToGroup(json jsonWithData);

    json SendPrivateMessage(json jsonWithData);

    inline json SendGroupMessage(json jsonWithData);

    json GetRecentPrivateMessage(json jsonWithData);

    inline json GetRecentGroupMessage(json jsonWithData);

    inline  json GetAllPrivateMessages(json jsonWithData);

    inline json GetAllGroupMessages(json jsonWithData);
};


#endif //PROJEKT_RECEIVEANDRESEND_H
