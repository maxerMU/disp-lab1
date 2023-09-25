#include "PersonsDA.h"
#include "PostgresPersonsRepository.h"

IPersonsRepositoryPtr CreatePersonsRepository(const IConfigPtr &conf, const std::string &connectionSection) {
    return std::make_shared<PostgresPersonsRepository>(conf, connectionSection);
}
