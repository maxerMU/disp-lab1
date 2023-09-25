#ifndef DUMMYSERVERHANDLER_H
#define DUMMYSERVERHANDLER_H

#include <reqresp/IResponseFactory.h>
#include <request_handlers/IServerReqHandler.h>
#include <config/IConfig.h>

class PersonsServerHandler : public IServerReqHandler
{
public:
    PersonsServerHandler(const IResponseFactoryPtr &respFactory);

    virtual void HandleRequest(const std::shared_ptr<IRequest> &req) override;
    virtual void MakeResponse(const std::shared_ptr<IResponse> &resp) override;

private:
    IResponseFactoryPtr m_respFactory;

    IResponsePtr m_resp;
};

#endif // DUMMYSERVERHANDLER_H
