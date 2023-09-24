#include "dummy_client_server_handler.h"

#include <network/net.h>
#include <router/router.h>

DummyClientServerHandler::DummyClientServerHandler(const IConfigPtr &config)
  : m_config(config)
{
}

IClientServerReqHandler::state_t DummyClientServerHandler::HandleRequest(const std::shared_ptr<IRequest> &request)
{
    m_context = CreateRequestsHandlerContext();
    m_context->GetCurrentRequest()->copy(request);

    m_routes = RequestsRouter::Instanse()->RouteClientServerReq(request->GetTarget(), request->GetMethod());
    if (m_routes.empty())
    {
        m_context->GetCurrentResponse()->SetStatus(net::CODE_404);
        m_context->GetCurrentResponse()->SetBody("not found");
        return RES_END;
    }

    m_currentRoute = 0;

    return RES_CONTINUE;
}

IClientServerReqHandler::state_t DummyClientServerHandler::GetNextRequest(IRequestPtr &request, size_t &clientIndex)
{
    if (m_currentRoute == m_routes.size())
        return RES_END;
    
    m_routes[m_currentRoute]->Init(m_context, m_clientIndexes);
    m_routes[m_currentRoute]->ProcessRequest(request, clientIndex);

    return RES_CONTINUE;
}

IClientServerReqHandler::state_t DummyClientServerHandler::HandleResponse(const IResponsePtr &response)
{
    m_routes[m_currentRoute++]->ProcessResponse(response);
    if (m_currentRoute == m_routes.size())
        return RES_END;

    return RES_CONTINUE;
}

void DummyClientServerHandler::MakeResponse(const IResponsePtr &resp)
{
    resp->copy(m_context->GetCurrentResponse());
}
