#pragma once

#include <string>
#include <vector>
#include <compare>

struct PersonDTO
{
public:
    void FromJSON(const std::string& json);
    std::string ToJSON() const;

    size_t id;
    std::string name;
    std::string address;
    std::string work;
    size_t age;

    auto operator<=>(const PersonDTO&) const = default;
};

using PersonsDTO = std::vector<PersonDTO>;

std::string ToJSON(const PersonsDTO& persons);