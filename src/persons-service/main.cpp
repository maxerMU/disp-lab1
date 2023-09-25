#include <network/net.h>
#include <config/config_creators.h>
#include <logger/LoggerFactory.h>

#include <memory>

#include "gateway/PersonsServerHandler.h"
#include "gateway/PersonsGateway.h"
#include "da/PersonsDA.h"
#include "bl/PersonsFacade.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    std::shared_ptr<IConfig> config = CreateYAMLConfig(std::string(argv[1]));
    LoggerFactory::InitLogger(config);

    PersonsFacade::Instance()->Init(CreatePersonsRepository(config, PersonsDBSection));

    SetupRouter();

    auto respFactory = CreateResponceFactory();
    auto handlerCreator = std::make_shared<ServerReqHandlerCreator<PersonsServerHandler>>(respFactory);
    auto sessionCreator = CreateServerSessionCreator(handlerCreator);

    asio::io_context ioc;
    auto connection = CreateServerConnection(ioc, sessionCreator, config);
    connection->Run();

    return 0;
}
