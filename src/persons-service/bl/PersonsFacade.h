#pragma once

#include <memory>

#include <dto/PersonDTO.h>
#include <dto/PersonPostDTO.h>
#include <dto/PersonPatchDTO.h>
#include <da/IPersonsRepository.h>

class PersonsFacade
{
public:
    static std::shared_ptr<PersonsFacade> Instance();
    void Init(const IPersonsRepositoryPtr& repository);

    void AddPerson(const PersonPostDTO& person);
    PersonsDTO GetPersons() const;
    PersonDTO GetPerson(size_t id) const;
    PersonDTO PatchPerson(size_t id, const PersonPatchDTO& person) const;
    void DeletePerson(size_t id) const;

private:
    PersonsFacade() = default;

    IPersonsRepositoryPtr m_repository;
};