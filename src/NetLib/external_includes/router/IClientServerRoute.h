#pragma once

#include <functional>
#include <router/IRequestHandlerContext.h>

class IClientServerRoute
{
public:
    virtual ~IClientServerRoute() = default;

    virtual void Init(const IRequestHandlerContextPtr& context, const std::map<std::string, size_t> clients) = 0;
    virtual void SetRequestParameters(const std::vector<std::string>& params) = 0;
    virtual void ProcessRequest(const IRequestPtr& request, size_t& clientIndex) = 0;
    virtual void ProcessResponse(const IResponsePtr& responseFromClient) = 0;
};

using IClientServerRoutePtr = std::shared_ptr<IClientServerRoute>;

// ==================================

class IClientServerRouteCreator
{
public:
    virtual ~IClientServerRouteCreator() = default;

    virtual IClientServerRoutePtr Create() const = 0;
};

using IClientServerRouteCreatorPtr = std::shared_ptr<IClientServerRouteCreator>;

template <class T>
concept BaseClientServerRoute = std::is_base_of<IClientServerRoute, T>::value;

template <BaseClientServerRoute T>
class ClientServerRouteCreator : public IClientServerRouteCreator
{
public:
    template <typename... Args>
    ClientServerRouteCreator(Args... args)
    {
        m_createFunc = [args...]() { return std::make_shared<T>(args...); };
    }

    virtual ~ClientServerRouteCreator() = default;

    IClientServerRoutePtr Create() const override
    {
        return m_createFunc();
    }

private:
    std::function<IClientServerRoutePtr()> m_createFunc;
};