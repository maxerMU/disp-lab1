#include <network/net.h>
#include <config/config_creators.h>
#include <logger/LoggerFactory.h>
#include <router/router.h>

#include <memory>

#include "dummy_client_server_handler.h"
#include "DummyClientServerRoute.h"

void SetupRouter()
{
    std::vector<IClientServerRouteCreatorPtr> route{
        std::make_shared<ClientServerRouteCreator<DummyClientServerRoute>>()
    };
    RequestsRouter::Instanse()->AddStaticEndpoint({"/test", net::GET}, route);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    asio::io_context ioc;

    std::shared_ptr<IConfig> config = CreateYAMLConfig(std::string(argv[1]));
    LoggerFactory::InitLogger(config);

    auto handlerCreator = std::make_shared<ClientServerReqHandlerCreator<DummyClientServerHandler>>(config);
    auto sessionCreator = CreateClientServerSessionCreator(handlerCreator);
    auto connection = CreateClientServerConnection(ioc, sessionCreator, config);

    connection->Run();

    return 0;
}
