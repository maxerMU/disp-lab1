#include "dummy_server_handler_creator.h"

DummyServerReqHandlerCreator::DummyServerReqHandlerCreator(const IResponseFactoryPtr &factory) : m_factory(factory)
{
}

std::shared_ptr<IServerReqHandler> DummyServerReqHandlerCreator::CreateHandler() const
{
    return std::make_shared<DummyServerHandler>(m_factory);
}
