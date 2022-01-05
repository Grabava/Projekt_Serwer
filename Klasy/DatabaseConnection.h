
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "../json.h"

#ifndef PROJEKT_DATABASECONNECTION_H
#define PROJEKT_DATABASECONNECTION_H

using json = nlohmann::json;
using namespace sql::mysql;
using namespace std;

class DatabaseConnection {

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    int userId = 1;

public:
    DatabaseConnection(){

        driver = get_driver_instance();
        con = driver->connect("localhost:3306", "admin", "zaq1@WSX");
        /* Connect to the MySQL test database */
        con->setSchema("Projekt");
        stmt=con->createStatement();

    }

    bool veryfiLogin(json jsonData);
    bool veryfiRegister(json jsonData);
    json getAllGroups();
    json getAllUsers();
    bool createGroup(json jsonData);
    bool addUserToGroup(json jsonData);
    bool sendPrivateMessage(json jsonData);
    bool sendGroupMessage(json jsonData);
    json getRecentPrivateMessage(json jsonData);
    json getPrivateMessages(json jsonData);
    json getRecentGroupMessage(json jsonData);
    json getGroupMessages(json jsonData);

};

#endif //PROJEKT_DATABASECONNECTION_H
