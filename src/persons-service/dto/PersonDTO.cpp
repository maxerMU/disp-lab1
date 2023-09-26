#include "PersonDTO.h"

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

#include <exceptions/server_exceptions.h>

void PersonDTO::FromJSON(const std::string &json)
{
    Json::Value value;
    Json::Reader reader;

    if (!reader.parse(json, value)) {
        throw JsonParserException("can't parse PersonDTO object");
    }

    id = value["id"].asUInt64();
    name = value["name"].asString();
    address = value["address"].asString();
    work = value["work"].asString();
    age = value["age"].asUInt64();
}

Json::Value GetJSON(const PersonDTO& person)
{
    Json::Value root;

    root["id"] = (uint) person.id;
    root["name"] = person.name;
    root["address"] = person.address;
    root["work"] = person.work;
    root["age"] = (uint) person.age;

    return root;
}

std::string PersonDTO::ToJSON() const 
{
    Json::Value root = GetJSON(*this);

    Json::FastWriter writer;

    return writer.write(root);
}

std::string ToJSON(const PersonsDTO &persons)
{
    Json::Value arr = Json::arrayValue;

    for (auto person : persons) {
        Json::Value root = GetJSON(person);
        arr.append(root);
    }

    Json::FastWriter writer;

    return writer.write(arr);
}
