#pragma once

#include "base_exception.h"

PROJECT_EXCEPTION(LogicException, BaseException, "(Logic error)")
PROJECT_EXCEPTION(InvalidAuthDataException, LogicException, "(Invalid auth data)")
PROJECT_EXCEPTION(RecomendationStrategyException, LogicException, "(Recomendation Strategy)")
PROJECT_EXCEPTION(CritertionException, RecomendationStrategyException, "(Criterion)")
