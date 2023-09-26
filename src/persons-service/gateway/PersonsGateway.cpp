#include "PersonsGateway.h"

#include <exceptions/logic_exceptions.h>
#include <router/router.h>
#include <logger/LoggerFactory.h>
#include "bl/PersonsFacade.h"

void Check(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
        return resp->SetStatus(net::CODE_503);

    resp->SetBody(params[0]);
    resp->SetStatus(net::CODE_200);
}

void Health(const IResponsePtr &resp, const IRequestPtr &)
{
    resp->SetStatus(net::CODE_200);
}

void GetPerson(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
    {
        LoggerFactory::GetLogger()->LogError("get person incorrect params count");
        resp->SetStatus(net::CODE_503);
        return;
    }

    size_t personId = std::stoul(params[0]);

    try
    {
        PersonDTO person = PersonsFacade::Instance()->GetPerson(personId);
        resp->SetBody(person.ToJSON());
        resp->SetStatus(net::CODE_200);
    }
    catch (const PersonNotFoundException &e)
    {
        LoggerFactory::GetLogger()->LogError((std::string("Person not found: ") + std::to_string(personId)).c_str());
        resp->SetBody("{\"message\": \"not found\"}");
        resp->SetStatus(net::CODE_404);
    }
}

void PatchPerson(const IResponsePtr &resp, const IRequestPtr &request, const std::vector<std::string> &params)
{
    if (params.size() != 1)
    {
        LoggerFactory::GetLogger()->LogError("patch person incorrect params count");
        resp->SetStatus(net::CODE_503);
        return;
    }

    size_t personId = std::stoul(params[0]);
    PersonPatchDTO person;
    person.FromJSON(request->GetBody());

    PersonDTO res = PersonsFacade::Instance()->PatchPerson(personId, person);

    resp->SetStatus(net::CODE_200);
    resp->SetBody(res.ToJSON());
}

void DeletePerson(const IResponsePtr &resp, const IRequestPtr &, const std::vector<std::string> &params)
{
    if (params.size() != 1)
    {
        LoggerFactory::GetLogger()->LogError("delete person incorrect params count");
        resp->SetStatus(net::CODE_503);
        return;
    }

    size_t personId = std::stoul(params[0]);

    PersonsFacade::Instance()->DeletePerson(personId);
    resp->SetStatus(net::CODE_204);
}

void GetPersons(const IResponsePtr &resp, const IRequestPtr &)
{
    PersonsDTO persons = PersonsFacade::Instance()->GetPersons();

    resp->SetBody(ToJSON(persons));
    resp->SetStatus(net::CODE_200);
}

void AddPerson(const IResponsePtr &resp, const IRequestPtr &request)
{
    PersonPostDTO person;
    person.FromJSON(request->GetBody());

    PersonsFacade::Instance()->AddPerson(person);

    resp->SetStatus(net::CODE_201);
}

void SetupRouter()
{
    RequestsRouter::Instanse()->AddStaticEndpoint({"/health", net::GET}, Health);
    RequestsRouter::Instanse()->AddStaticEndpoint({"/api/v1/persons", net::GET}, GetPersons);
    RequestsRouter::Instanse()->AddStaticEndpoint({"/api/v1/persons", net::POST}, AddPerson);
    RequestsRouter::Instanse()->AddDynamicEndpoint({std::regex("/api/v1/persons/([0-9\\-]+)"), net::GET}, GetPerson);
    RequestsRouter::Instanse()->AddDynamicEndpoint({std::regex("/api/v1/persons/([0-9\\-]+)"), net::DELETE}, DeletePerson);
    RequestsRouter::Instanse()->AddDynamicEndpoint({std::regex("/api/v1/persons/([0-9\\-]+)"), net::PATCH}, PatchPerson);
}
