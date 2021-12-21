
#include "DatabaseConnection.h"
using namespace std;
bool DatabaseConnection::veryfiLogin(json jsonDATA){
    std::string query = "SELECT id FROM Users AS u WHERE Name = \"";
    query += jsonDATA["login"];
    query += "\" AND Token = \"";
    query += jsonDATA["password"];
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
    std::string boolQuery = "SELECT Id FROM Users WHERE Name = \"";
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

return false;
}

bool DatabaseConnection::sendPrivateMessage(json jsonData){

    std::string query = "INSERT INTO PrivateMessage (AuthorId, Message, RecevierId, Date) VALUES (";
    query += userID;
    query += ", \"";
    query += jsonData["messageContent"];
    query += "\", ";
    query += jsonData["receiverId"];
    query += ", NOW());";

    try {
        stmt->executeQuery(query);

        return true;
    }
    catch(sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

json DatabaseConnection::getPrivateMessage(json jsonData) {

    std::string query = "SELECT Message, RecevierId, Date FROM PrivateMessage WHERE RecevierId = ";
                query += userID;
                query += " AND AuthorId = ";
                query += jsonData["recevierId"];
                query += " AND MAX(Date);";

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
        json message;
        message["receiverId"] = res->getInt("RecevierId");
        message["message"] = res->getString("Message");
        message["date"] = res->getString("Date");

        return message;
    }
}



