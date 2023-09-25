#pragma once

#include <map>
#include <pqxx/pqxx>

#include <config/IConfig.h>
#include "IPersonsRepository.h"

class PostgresPersonsRepository 
    : public IPersonsRepository
{
public:
    PostgresPersonsRepository(const IConfigPtr &conf, const std::string &connectionSection);
    virtual void AddPerson(const PersonPostDTO& person) override;
    virtual PersonsDTO GetPersons() override;
    virtual PersonDTO GetPerson(size_t id) override;
    virtual PersonDTO PatchPerson(size_t id, const PersonPatchDTO& person) override;
    virtual void DeletePerson(size_t id) override;

private:
    void ReadConfig(const IConfigPtr &conf, const std::string &connectionSection);

    void Connect();
    void AddPrepareStatements();

    std::shared_ptr<pqxx::connection> m_connection;

    std::string m_name;
    std::string m_user;
    std::string m_userPassword;
    std::string m_host;
    size_t m_port;

    enum PreparedRequests { WRITE, READ_BY_ID, READ_ALL, PATCH, DELETE };

    std::map<PreparedRequests, std::string> m_requestsNames = {
        {WRITE, "add_person"},
        {READ_BY_ID, "get_person_by_id"},
        {READ_ALL, "get_all_persons"},
        {PATCH, "patch_person"},
        {DELETE, "delete_person_by_id"}
    };
};