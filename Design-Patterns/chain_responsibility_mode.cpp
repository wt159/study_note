#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

// #define DEBUG 1

class Handler
{
public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler
{
private:
    Handler *next_handler_;
#ifdef DEBUG
    std::vector<Handler *> _next_handler_vec;
#endif // DEBUG

public:
    AbstractHandler() : next_handler_(nullptr) {}
    Handler *SetNext(Handler *handler) override
    {
        next_handler_ = handler;
#ifdef DEBUG
        _next_handler_vec.emplace(_next_handler_vec.begin(), handler);
#endif // DEBUG

        return handler;
    }
    std::string Handle(std::string request) override
    {
        if (next_handler_)
        {
            return next_handler_->Handle(request);
        }
#ifdef DEBUG
        auto iter = _next_handler_vec.begin();
        for (; iter != _next_handler_vec.end(); ++iter)
        {
            (*iter)->Handle(request);
        }
#endif // DEBUG
        return {};
    }
};

/**
 * All Concrete Handlers either handle a request or pass it to the next handler
 * in the chain.
 */
class MonkeyHandler : public AbstractHandler
{
public:
    std::string Handle(std::string request) override
    {
        if (request == "Banana")
        {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        else
        {
            return AbstractHandler::Handle(request);
        }
    }
};
class SquirrelHandler : public AbstractHandler
{
public:
    std::string Handle(std::string request) override
    {
        if (request == "Nut")
        {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        else
        {
            return AbstractHandler::Handle(request);
        }
    }
};
class DogHandler : public AbstractHandler
{
public:
    std::string Handle(std::string request) override
    {
        if (request == "MeatBall")
        {
            return "Dog: I'll eat the " + request + ".\n";
        }
        else
        {
            return AbstractHandler::Handle(request);
        }
    }
};
/**
 * The client code is usually suited to work with a single handler. In most
 * cases, it is not even aware that the handler is part of a chain.
 */
void ClientCode(Handler &handler)
{
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const std::string &f : food)
    {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty())
        {
            std::cout << "  " << result;
        }
        else
        {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}

/**
 * The other part of the client code constructs the actual chain.
 */
int main()
{
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    /**
   * The client should be able to send a request to any handler, not just the
   * first one in the chain.
   */
    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}