#include "PersonsFacade.h"

#include <exceptions/logic_exceptions.h>
#include <exceptions/database_exceptions.h>

std::shared_ptr<PersonsFacade> PersonsFacade::Instance()
{
    static std::shared_ptr<PersonsFacade> instance(new PersonsFacade());
    return instance;
}

void PersonsFacade::Init(const IPersonsRepositoryPtr &repository)
{
    m_repository = repository;
}

void PersonsFacade::AddPerson(const PersonPostDTO &person)
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");
    
    m_repository->AddPerson(person);
}

PersonsDTO PersonsFacade::GetPersons() const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");
    
    return m_repository->GetPersons();
}

PersonDTO PersonsFacade::GetPerson(size_t id) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");
    
    try
    {
        return m_repository->GetPerson(id);
    }
    catch(const DatabaseNotFoundException& e)
    {
        throw PersonNotFoundException(e.what());
    }
}

PersonDTO PersonsFacade::PatchPerson(size_t id, const PersonPatchDTO &person) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");

    return m_repository->PatchPerson(id, person);
}

void PersonsFacade::DeletePerson(size_t id) const
{
    if (!m_repository)
        throw NotInitializedException("repository doesn't initilized");

    m_repository->DeletePerson(id);
}
