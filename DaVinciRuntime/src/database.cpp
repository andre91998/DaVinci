#include "database.h"
#include <iostream>

// Initialize the static member
Database* Database::instance = nullptr;

Database::Database(const std::string& db_path) {
    if (sqlite3_open(db_path.c_str(), &db_) != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db_) << std::endl;
        throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(db_)));
    } else {
        std::cout << "Database opened successfully: " << db_path << std::endl;
    }
}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
        std::cout << "Database closed successfully." << std::endl;
    }
}

Database* Database::getInstance(const std::string& db_path) {
    if (instance == nullptr) {
        instance = new Database(db_path);
    }
    return instance;
}

void Database::destroyInstance() {
    delete instance;
    instance = nullptr;
}

void Database::execute(const std::string& query) {
    char* errmsg = nullptr;
    std::cout << "Executing query: " << query << std::endl;
    if (sqlite3_exec(db_, query.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
        std::string error_message = "SQL error: " + std::string(errmsg);
        sqlite3_free(errmsg);
        std::cerr << error_message << std::endl;
        throw std::runtime_error(error_message);
    } else {
        std::cout << "Query executed successfully: " << query << std::endl;
    }
}

std::vector<std::vector<std::string>> Database::query(const std::string& query) {
    sqlite3_stmt* stmt;
    std::vector<std::vector<std::string>> result;

    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db_)));
    }

    int cols = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int col = 0; col < cols; ++col) {
            const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, col));
            row.push_back(text ? text : "");
        }
        result.push_back(row);
    }

    sqlite3_finalize(stmt);
    return result;
}