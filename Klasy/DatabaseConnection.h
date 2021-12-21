
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
class DatabaseConnection {

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    int userID;
public:
    DatabaseConnection(){

        driver = get_driver_instance();
        con = driver->connect("localhost:3306", "admin", "zaq1@WSX");
        /* Connect to the MySQL test database */
        con->setSchema("Projekt");
        stmt=con->createStatement();

    }

    bool veryfiLogin(json jsonDATA);
    bool veryfiRegister(json jsonDATA);
    bool sendPrivateMessage(json jsonDATA);
    json getPrivateMessage(json jsonDaTA);
};


#endif //PROJEKT_DATABASECONNECTION_H
