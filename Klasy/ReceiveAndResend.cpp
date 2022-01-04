
#include "ReceiveAndResend.h"
#include "DatabaseConnection.h"

DatabaseConnection dbConnect = DatabaseConnection();

ReceiveAndResend::ReceiveAndResend(std::string message) {
    json jsonData = json::parse(message);
    receiveAction(jsonData["id"], jsonData);
}

json ReceiveAndResend::getResult() {
    return result;
}

void ReceiveAndResend::receiveAction(int id, json jsonData) {

    switch (id) {
        case 1:
            result = Login(jsonData);
            break;
        case 2:
            result = Registration(jsonData);
            break;
        case 3:
            result = GetAllGroups();
            break;
        case 4:
            result = GetAllUsers();
            break;
        case 5:
            result = CreateGroup(jsonData);
            break;
        case 6:
            result = AddUserToGroup(jsonData);
            break;
        case 7:
            result = SendPrivateMessage(jsonData);
            break;
        case 8:
            result = SendGroupMessage(jsonData);
            break;
        case 9:
            result = GetRecentPrivateMessage(jsonData);
            break;
        case 10:
            result = GetAllPrivateMessages(jsonData);
            break;
        case 11:
            result = GetRecentGroupMessage(jsonData);
            break;
        case 12:
            result = GetAllGroupMessages(jsonData);
            break;
        default:
            cout << "Nie odnaleziono komendy";
    }
}

json ReceiveAndResend::Login(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 1;
    resultJSON["result"] = dbConnect.veryfiLogin(jsonData);

    return resultJSON;
}

json ReceiveAndResend::Registration(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 2;
    resultJSON["result"] = dbConnect.veryfiRegister(jsonData);

    return resultJSON;
}

json ReceiveAndResend::GetAllGroups() {

    json resultJSON;
    resultJSON["id"] = 3;

    return resultJSON;
}

json ReceiveAndResend::GetAllUsers() {

    json resultJSON;
    //resultJSON["id"] = 4;
    resultJSON = dbConnect.getAllUsers();

    std::string teststst = resultJSON.dump();

    return resultJSON;
}

json ReceiveAndResend::CreateGroup(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 5;
    resultJSON["result"] = dbConnect.createGroup(jsonData);

    return resultJSON;
}

json ReceiveAndResend::AddUserToGroup(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 6;
    resultJSON["result"] = dbConnect.addUserToGroup(jsonData);

    return resultJSON;
}

json ReceiveAndResend::SendPrivateMessage(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 7;
    resultJSON["result"] = dbConnect.sendPrivateMessage(jsonData);

    return resultJSON;
}

json ReceiveAndResend::SendGroupMessage(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 8;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}


json ReceiveAndResend::GetRecentPrivateMessage(json jsonData) {

    json resultJSON = dbConnect.getRecentPrivateMessage(jsonData);

    return resultJSON;
}

json ReceiveAndResend::GetAllPrivateMessages(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 10;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}

json ReceiveAndResend::GetRecentGroupMessage(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 11;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}

json ReceiveAndResend::GetAllGroupMessages(json jsonData) {

    json resultJSON;
    resultJSON["id"] = 12;
    resultJSON["result"] = "Group message send";

    return resultJSON;
}