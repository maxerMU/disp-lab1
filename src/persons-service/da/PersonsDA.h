#pragma once

#include "IPersonsRepository.h"
#include <config/IConfig.h>

const std::string PersonsDBSection = "DB_PERSONS";

IPersonsRepositoryPtr CreatePersonsRepository(const IConfigPtr &conf, const std::string &connectionSection);