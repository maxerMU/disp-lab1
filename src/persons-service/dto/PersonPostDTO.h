#pragma once

#include <string>
#include <compare>

struct PersonPostDTO
{
public:
    void FromJSON(const std::string& json);
    std::string ToJSON() const;

    std::string name;
    std::string address;
    std::string work;
    size_t age;

    auto operator<=>(const PersonPostDTO&) const = default;
};