
#include "DatabaseConnection.h"

using namespace std;

json DatabaseConnection::veryfiLogin(json jsonData) {

    std::string query = "SELECT Id FROM Users WHERE Name = \"";
    query += jsonData["login"];
    query += "\" AND Token = \"";
    query += jsonData["password"];
    query += "\" ;";

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
    json resultJson;
    resultJson["result"] = false;
    while (res->next()) {
        resultJson["result"] = true;
        resultJson["userId"] = res->getInt("Id");
    }

    return resultJson;
}

bool DatabaseConnection::veryfiRegister(json jsonData) {

    std::string boolQuery = "SELECT Id FROM Users WHERE Name = \"";
    boolQuery += jsonData["login"];
    boolQuery += "\";";

    try {
        res = stmt->executeQuery(boolQuery);
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    int recordsCount = res->rowsCount();

    if (recordsCount == 0) {
        std::string insertQuery = "INSERT INTO Users (Name, Token) VALUES (\"";
        insertQuery += jsonData["login"];
        insertQuery += "\", \"";
        insertQuery += jsonData["password"];
        insertQuery += "\");";

        try {
            stmt = con->createStatement();
            stmt->execute(insertQuery);
        }
        catch(sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            return false;
        }
        return true;
    }
}

json DatabaseConnection::getAllGroups(json jsonData) {

    std::string query = "SELECT Id, Name FROM Groups_Table ";
                query += "INNER JOIN GroupMembers ON Groups_Table.Id = GroupMembers.GroupId ";
                query += "WHERE GroupMembers.UserId = ";
                query += to_string(jsonData["userId"]);
                query += ";";

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

    while(res->next())
    {
        resultJSON += json::array({ {"Id", res->getInt("Id")},
                                    {"Name", res->getString("Name")} });
    }
    return resultJSON;
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

    while(res->next())
    {
        resultJSON += json::array({ {"Id", res->getInt("Id")},
                                    {"Name", res->getString("Name")} });
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
    query += ");";

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
    query += to_string(jsonData["authorId"]);
    query += ", \"";
    query += jsonData["messageContent"];
    query += "\", ";
    query += to_string(jsonData["receiverId"]);
    query += ", ";
    query += to_string(jsonData["date"]);
    query += ");";

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

bool DatabaseConnection::sendGroupMessage(json jsonData) {

    std::string query = "INSERT INTO GroupMessage (AuthorId, Message, GroupId, Date) VALUES (";
    query += to_string(jsonData["authorId"]);
    query += ", \"";
    query += jsonData["messageContent"];
    query += "\", ";
    query += to_string(jsonData["groupId"]);
    query += ", ";
    query += to_string(jsonData["date"]);
    query += ");";

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

    std::string query = "SELECT Message, RecevierId, DATE_FORMAT(Date, '%d/%m/%Y %T') AS Date FROM PrivateMessage WHERE RecevierId = ";
                query += to_string(jsonData["receiverId"]);
                query += " AND AuthorId = ";
                query += to_string(jsonData["authorId"]);
                query += " GROUP BY Message, Date ORDER BY MAX(Date) DESC LIMIT 1;";

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

json DatabaseConnection::getPrivateMessages(json jsonData) {

    std::string query = "SELECT Message, RecevierId, DATE_FORMAT(Date, '%d/%m/%Y %T') AS Date FROM PrivateMessage WHERE RecevierId = ";
    query += to_string(jsonData["receiverId"]);
    query += " AND AuthorId = ";
    query += to_string(jsonData["authorId"]);
    query += " GROUP BY Message, Date ORDER BY Date;";

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

    while(res->next())
    {
        resultJSON += json::array({ {"receiverId", res->getInt("RecevierId")},
                                    {"message", res->getString("Message")},
                                    {"date", res->getString("Date")} });
    }
    return resultJSON;
}

json DatabaseConnection::getRecentGroupMessage(json jsonData) {

    std::string query = "SELECT AuthorId, Message, GroupId, DATE_FORMAT(Date, '%d/%m/%Y %T') AS Date FROM GroupMessage WHERE GroupId = ";
    query += to_string(jsonData["groupId"]);
    query += " GROUP BY Message, Date, AuthorId ORDER BY MAX(Date) DESC LIMIT 1;";

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
        resultJSON["authorId"] = res->getInt("AuthorId");
        resultJSON["message"] = res->getString("Message");
        resultJSON["groupId"] = res->getInt("GroupId");
        resultJSON["date"] = res->getString("Date");

        return resultJSON;
    }
}

json DatabaseConnection::getGroupMessages(json jsonData) {

    std::string query = "SELECT AuthorId, Message, GroupId, DATE_FORMAT(Date, '%d/%m/%Y %T') AS Date FROM GroupMessage WHERE GroupId = ";
    query += to_string(jsonData["groupId"]);
    query += " GROUP BY AuthorId, Message, Date ORDER BY Date DESC;";

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

    while(res->next())
    {
        resultJSON += json::array({ {"authorId", res->getInt("AuthorID")},
                                    {"message", res->getString("Message")},
                                    {"groupId", res->getInt("GroupId")},
                                    {"date", res->getString("Date")} });
    }
    return resultJSON;
}




