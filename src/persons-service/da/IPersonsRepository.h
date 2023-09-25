#pragma once

#include <memory>

#include <dto/PersonDTO.h>
#include <dto/PersonPostDTO.h>
#include <dto/PersonPatchDTO.h>

class IPersonsRepository
{
public:
    virtual ~IPersonsRepository() = default;

    virtual void AddPerson(const PersonPostDTO& person) = 0;
    virtual PersonsDTO GetPersons() = 0;
    virtual PersonDTO GetPerson(size_t id) = 0;
    virtual PersonDTO PatchPerson(size_t id, const PersonPatchDTO& person) = 0;
    virtual void DeletePerson(size_t id) = 0;
};

using IPersonsRepositoryPtr = std::shared_ptr<IPersonsRepository>;