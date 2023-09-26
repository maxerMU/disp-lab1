#include "PersonPostDTO.h"

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

#include <exceptions/server_exceptions.h>

void PersonPostDTO::FromJSON(const std::string &json)
{
    Json::Value value;
    Json::Reader reader;

    if (!reader.parse(json, value)) {
        throw JsonParserException("can't parse PersonDTO object");
    }

    name = value["name"].asString();
    address = value["address"].asString();
    work = value["work"].asString();
    age = value["age"].asUInt64();
}

std::string PersonPostDTO::ToJSON() const
{
    Json::Value root;

    root["name"] = name;
    root["address"] = address;
    root["work"] = work;
    root["age"] = (uint) age;

    Json::FastWriter writer;

    return writer.write(root);
}
