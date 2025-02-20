#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <stdexcept>

class Database {
public:
    static Database* getInstance(const std::string& db_path = "davinci.db");
    static void destroyInstance();
    void execute(const std::string& query);
    std::vector<std::vector<std::string>> query(const std::string& query);

private:
    Database(const std::string& db_path); // Private constructor
    ~Database();
    createTables();

    static Database* instance;
    sqlite3* db_;
};

#endif // DATABASE_H