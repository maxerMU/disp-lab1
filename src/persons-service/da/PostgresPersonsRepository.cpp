#include "PostgresPersonsRepository.h"

#include <config/base_sections.h>
#include <exceptions/database_exceptions.h>
#include <logger/LoggerFactory.h>

PostgresPersonsRepository::PostgresPersonsRepository(const IConfigPtr &conf, const std::string &connectionSection)
{
    ReadConfig(conf, connectionSection);
    Connect();
    AddPrepareStatements();
}

void PostgresPersonsRepository::ReadConfig(const IConfigPtr &conf, const std::string &connectionSection)
{
    m_name = conf->GetStringField({connectionSection, DbNameSection});
    m_user = conf->GetStringField({connectionSection, DbUserSection});
    m_userPassword = conf->GetStringField({connectionSection, DbUserPasswordSection});
    m_host = conf->GetStringField({connectionSection, DbHostSection});
    m_port = conf->GetUintField({connectionSection, DbPortSection});
}

void PostgresPersonsRepository::Connect()
{
    std::string connectionString = "dbname = " + m_name + " user = " + m_user + " password = " + m_userPassword +
                                   " host = " + m_host + " port = " + std::to_string(m_port);

    try
    {
        m_connection = std::shared_ptr<pqxx::connection>(new pqxx::connection(connectionString.c_str()));

        if (!m_connection->is_open())
            throw DatabaseConnectException("can't connect to " + m_name);
        else
            LoggerFactory::GetLogger()->LogInfo((std::string("Connected to db ") + m_name).c_str());
    }
    catch (std::exception &ex)
    {
        throw DatabaseConnectException("can't connect to " + m_name + " " + ex.what());
    }
}

void PostgresPersonsRepository::AddPrepareStatements()
{
    m_connection->prepare(m_requestsNames[READ_ALL], "SELECT * FROM T_Persons");
    m_connection->prepare(m_requestsNames[READ_BY_ID], "SELECT * FROM T_Persons WHERE id=$1");
    m_connection->prepare(m_requestsNames[DELETE], "DELETE FROM T_Persons WHERE id=$1");
    m_connection->prepare(m_requestsNames[WRITE],
                          "INSERT INTO T_Persons (name, age, address, work) VALUES ($1, $2, $3, $4)");
    m_connection->prepare(m_requestsNames[PATCH],
                          "UPDATE T_Persons SET name=$2, age=$3, address=$4, work=$5 WHERE id=$1");
}

void PostgresPersonsRepository::AddPerson(const PersonPostDTO &person)
{
    try
    {
        pqxx::work w(*m_connection);
        w.exec_prepared(m_requestsNames[WRITE], person.name, person.age, person.address, person.work);
        w.commit();
    }
    catch (...)
    {
        throw DatabaseExecutionException("can't execute prepared");
    }
}


PersonsDTO PostgresPersonsRepository::GetPersons()
{
    pqxx::result rows;
    try
    {
        pqxx::work w(*m_connection);
        rows = w.exec_prepared(m_requestsNames[READ_ALL]);
        w.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException(ex.what());
    }

    PersonsDTO persons;
    persons.reserve(rows.size());
    for (const auto &row : rows)
    {
        PersonDTO person{row["id"].as<size_t>(), row["name"].as<std::string>(), row["address"].as<std::string>(),
                         row["work"].as<std::string>(), row["age"].as<size_t>()};

        persons.push_back(person);
    }

    return persons;
}

PersonDTO PostgresPersonsRepository::GetPerson(size_t id)
{
    pqxx::result rows;
    try
    {
        pqxx::work w(*m_connection);
        rows = w.exec_prepared(m_requestsNames[READ_BY_ID], id);
        w.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException(ex.what());
    }

    if (rows.empty())
        throw DatabaseNotFoundException("person not found");

    PersonDTO person{rows[0]["id"].as<size_t>(), rows[0]["name"].as<std::string>(), rows[0]["address"].as<std::string>(),
                     rows[0]["work"].as<std::string>(), rows[0]["age"].as<size_t>()};

    return person;
}

PersonDTO PostgresPersonsRepository::PatchPerson(size_t id, const PersonPatchDTO &person)
{
    try
    {
        pqxx::work w(*m_connection);
        w.exec_prepared(m_requestsNames[PATCH], id, person.name, person.age, person.address, person.work);
        w.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException(ex.what());
    }

    return GetPerson(id);
}

void PostgresPersonsRepository::DeletePerson(size_t id)
{
    try
    {
        pqxx::work w(*m_connection);
        w.exec_prepared(m_requestsNames[DELETE], id);
        w.commit();
    }
    catch (std::exception &ex)
    {
        throw DatabaseExecutionException(ex.what());
    }
}
