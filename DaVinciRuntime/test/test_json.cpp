#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>

class JSONTest : public ::testing::Test {
protected:
    Json::Value root;

    void SetUp() override {
        // Initialize the JSON value with test data if needed
        root["mqtt_broker"] = "localhost";
        root["mqtt_port"] = 1883;
        root["database_path"] = "/path/to/database";
        root["grpc_port"] = 50051;
        Json::Value topics(Json::arrayValue);
        topics.append("DaVinci-Plug-1/events/rpc");
        topics.append("DaVinci-Dimmer-1/events/rpc");
        topics.append("DaVinci-Temp-1/events/rpc");
        root["mqtt_topics"] = topics;
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

TEST_F(JSONTest, ParseJSONString) {
    std::string jsonString = R"({
        "mqtt_broker": "localhost",
        "mqtt_port": 1883,
        "database_path": "/path/to/database",
        "grpc_port": 50051,
        "mqtt_topics": ["DaVinci-Plug-1/events/rpc", "DaVinci-Dimmer-1/events/rpc", "DaVinci-Temp-1/events/rpc"]
    })";

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;
    bool parsingSuccessful = reader->parse(jsonString.c_str(), jsonString.c_str() + jsonString.size(), &root, &errors);
    delete reader;

    EXPECT_TRUE(parsingSuccessful);
    EXPECT_EQ(root["mqtt_broker"].asString(), "localhost");
    EXPECT_EQ(root["mqtt_port"].asInt(), 1883);
    EXPECT_EQ(root["database_path"].asString(), "/path/to/database");
    EXPECT_EQ(root["grpc_port"].asInt(), 50051);

    auto topics = root["mqtt_topics"];
    EXPECT_EQ(topics.size(), 3);
    EXPECT_EQ(topics[0].asString(), "DaVinci-Plug-1/events/rpc");
}

TEST_F(JSONTest, SerializeToJSONString) {
    Json::StreamWriterBuilder writer;
    std::string output = Json::writeString(writer, root);

    Json::CharReaderBuilder readerBuilder;
    Json::CharReader* reader = readerBuilder.newCharReader();
    Json::Value parsedRoot;
    std::string errors;
    bool parsingSuccessful = reader->parse(output.c_str(), output.c_str() + output.size(), &parsedRoot, &errors);
    delete reader;

    EXPECT_TRUE(parsingSuccessful);
    EXPECT_EQ(parsedRoot["mqtt_broker"].asString(), "localhost");
    EXPECT_EQ(parsedRoot["mqtt_port"].asInt(), 1883);
    EXPECT_EQ(parsedRoot["database_path"].asString(), "/path/to/database");
    EXPECT_EQ(parsedRoot["grpc_port"].asInt(), 50051);

    auto topics = parsedRoot["mqtt_topics"];
    EXPECT_EQ(topics.size(), 3);
    EXPECT_EQ(topics[0].asString(), "DaVinci-Plug-1/events/rpc");
}