
#include "DatabaseConnection.h"
#include "ClassWithIdAndName.h"
using namespace std;
bool DatabaseConnection::veryfiLogin(json jsonData) {
    std::string query = "SELECT id FROM Users AS u WHERE Name = \"";
    query += jsonData["login"];
    query += "\" AND Token = \"";
    query += jsonData["password"];
    query += "\" ;";
    try{
        res = stmt->executeQuery(query);

    }catch(sql::SQLException &e){
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    while (res->next()){
        return true;
    }
    return false;
}

bool DatabaseConnection::veryfiRegister(json jsonData) {
  /*  std::string boolQuery = "SELECT Id FROM Users WHERE Name = \"";
    boolQuery += jsonData["login"];
    boolQuery += "\";";

    try {
        res = stmt->executeQuery(boolQuery);
    }
    catch(sql::SQLException &e){
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    if(!res->next())
    {
        std::string insertQuery = "INSERT INTO Users (Name, Token) VALUES (\"";
        insertQuery += jsonData["login"];
        insertQuery += "\", \"";
        insertQuery += jsonData["password"];
        insertQuery += "\");";

        try {
            stmt->executeQuery(insertQuery);
        }
        catch(sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }

        return true;

    }
*/
return false;
}


json DatabaseConnection::getAllGroups(json jsonData) {


}
json DatabaseConnection::getAllUsers() {

    std::string query = "SELECT * FROM Users;";

    try {
        res = stmt->executeQuery(query);
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    json resultJSON;

    res_meta = res -> getMetaData();
    while(res->next())
    {
        resultJSON += json::array({ {"Id", res->getInt("Id")}, {"Name", res->getString("Name")} });
    }
    return resultJSON;
}

bool DatabaseConnection::createGroup(json jsonData) {

    std::string query = "INSERT INTO Groups_Table (Name) VALUES (";
    query += "\"";
    query += jsonData["groupName"];
    query += "\");";

    try {
        stmt = con->createStatement();
        stmt->execute(query);
        return true;
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return false;
}

bool DatabaseConnection::addUserToGroup(json jsonData) {

    std::string query = "INSERT INTO GroupMembers (GroupId, UserId) VALUES ( ";
    query += to_string(jsonData["groupId"]);
    query += ", ";
    query += to_string(jsonData["userId"]);
    query += " );";

    try {
        stmt = con->createStatement();
        stmt->execute(query);
        return true;
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return false;
}

bool DatabaseConnection::sendPrivateMessage(json jsonData) {

    std::string query = "INSERT INTO PrivateMessage (AuthorId, Message, RecevierId, Date) VALUES (";
    query += userID;
    query += ", \"";
    query += jsonData["messageContent"];
    query += "\", ";
    query += jsonData["receiverId"];
    query += ", NOW());";

    try {
        stmt = con->createStatement();
        stmt->execute(query);
        return true;
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return false;
}

json DatabaseConnection::getRecentPrivateMessage(json jsonData) {

    std::string query = "SELECT Message, RecevierId, MAX(Date) FROM PrivateMessage WHERE RecevierId = ";
                query += userID;
                query += " AND AuthorId = \"";
                query += jsonData["recevierId"];
                query += "\";";

    try {
        res = stmt->executeQuery(query);
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    while(res->next())
    {
        json resultJSON;
        resultJSON["receiverId"] = res->getInt("RecevierId");
        resultJSON["message"] = res->getString("Message");
        resultJSON["date"] = res->getString("Date");

        return resultJSON;
    }
}



