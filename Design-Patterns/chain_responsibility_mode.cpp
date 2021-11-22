#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

class Handler
{
public:
    virtual Handler *setNext(Handler *handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler
{
private:
    Handler *next_handler_;
public:
    AbstractHandler() : next_handler_(nullptr) {}
    Handler* setNext(Handler* handler) override
    {
        next_handler_ = handler;
        return handler;
    }
    std::string Handle(std::string request) override
    {
        if(next_handler_)
        {
            return next_handler_->Handle(request);
        }
        return {};
    }
};

void clientCode()
{

}

int main()
{
    clientCode();
    return 0;
}