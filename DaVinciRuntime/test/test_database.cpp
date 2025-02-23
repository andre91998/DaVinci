#include "database.h"
#include "gtest/gtest.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <filesystem>

class DatabaseTest : public ::testing::Test {
protected:
    std::string test_db_path = "test.db";
    Database* db;

    void SetUp() override {
        // Initialize the database instance
        db = Database::getInstance(test_db_path);
    }

    void TearDown() override {
        // Clean up the database instance
        Database::destroyInstance();
        std::filesystem::remove(test_db_path);
    }
};

TEST_F(DatabaseTest, DatabaseOpenCloseTest) {
    EXPECT_NO_THROW({
        Database* db = Database::getInstance(test_db_path);
        Database::destroyInstance();
    });
}

TEST_F(DatabaseTest, ExecuteValidQueryTest) {
    EXPECT_NO_THROW({
        db->execute("CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, name TEXT);");
    });
}

TEST_F(DatabaseTest, ExecuteInvalidQueryTest) {
    EXPECT_THROW({
        db->execute("INVALID SQL QUERY");
    }, std::runtime_error);
}

TEST_F(DatabaseTest, QueryTest) {
    db->execute("CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, name TEXT);");
    db->execute("INSERT INTO test_table (name) VALUES ('test_name');");

    std::vector<std::vector<std::string>> result;
    EXPECT_NO_THROW({
        result = db->query("SELECT * FROM test_table;");
    });

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][1], "test_name");
}

TEST_F(DatabaseTest, QueryInvalidSQLTest) {
    EXPECT_THROW({
        db->query("INVALID SQL QUERY");
    }, std::runtime_error);
}

TEST_F(DatabaseTest, QueryEmptyResultTest) {
    db->execute("CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, name TEXT);");

    std::vector<std::vector<std::string>> result;
    EXPECT_NO_THROW({
        result = db->query("SELECT * FROM test_table WHERE name = 'nonexistent';");
    });

    EXPECT_EQ(result.size(), 0);
}