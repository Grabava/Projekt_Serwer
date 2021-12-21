
#include "ReceiveAndResend.h"
#include "DatabaseConnection.h"

DatabaseConnection dbConnect = DatabaseConnection();

ReceiveAndResend::ReceiveAndResend(std::string message) {
    json jsonWithData = json::parse(message);
    receiveAction(jsonWithData["id"], jsonWithData);
}

json ReceiveAndResend::getResult() {
    return result;
}


void ReceiveAndResend::receiveAction(int id, json jsonWithData) {

    switch (id) {
        case 1:
            result = Login(jsonWithData);
            break;
        case 2:
            result = Registration(jsonWithData);
            break;
        case 3:
            result = GetAllGroups();
            break;
        case 4:
            result = GetAllUsers();
            break;
        case 5:
            result = CreateGroup(jsonWithData);
            break;
        case 6:
            result = AddUserToGroup(jsonWithData);
            break;
        case 7:
            result = SendPrivateMessage(jsonWithData);
            break;
        case 8:
            result = SendGroupMessage(jsonWithData);
            break;
        case 9:
            result = GetRecentPrivateMessage(jsonWithData);
            break;
        case 10:
            result = GetAllPrivateMessages(jsonWithData);
            break;
        case 11:
            result = GetRecentGroupMessage(jsonWithData);
            break;
        case 12:
            result = GetAllGroupMessages(jsonWithData);
            break;
        default:
            cout << "Nie odnaleziono komendy";
    }
}

json ReceiveAndResend::Login(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 1;
    resultJSON["result"] = dbConnect.veryfiLogin(jsonWithData);

    return resultJSON;
}

json ReceiveAndResend::Registration(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 2;
    resultJSON["result"] = dbConnect.veryfiRegister(jsonWithData);

    return resultJSON;
}

json ReceiveAndResend::GetAllGroups() {

    json resultJSON;
    resultJSON["id"] = 3;

    return resultJSON;
}

json ReceiveAndResend::GetAllUsers() {

    json resultJSON;
    resultJSON["id"] = 4;

    return resultJSON;
}

json ReceiveAndResend::CreateGroup(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 5;
    resultJSON["result"] = "Group created!";

    return resultJSON;
}

json ReceiveAndResend::AddUserToGroup(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 6;
    resultJSON["result"] = "User added!";

    return resultJSON;
}

json ReceiveAndResend::SendPrivateMessage(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 7;
    resultJSON["result"] = dbConnect.sendPrivateMessage(jsonWithData);

    return resultJSON;
}

json ReceiveAndResend::SendGroupMessage(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 8;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}


json ReceiveAndResend::GetRecentPrivateMessage(json jsonWithData) {

    json resultJSON = dbConnect.getPrivateMessage(jsonWithData);

    return resultJSON;
}

json ReceiveAndResend::GetAllPrivateMessages(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 10;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}

json ReceiveAndResend::GetRecentGroupMessage(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 11;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}

json ReceiveAndResend::GetAllGroupMessages(json jsonWithData) {

    json resultJSON;
    resultJSON["id"] = 12;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}