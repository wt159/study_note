#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>

using namespace std;

std::map<std::string, std::function<void()>> commands;

template<typename ftor>
void install_command(std::string name, ftor && handler)
{
  commands.insert({
    std::move(name),
    std::forward<ftor>(handler)
  });
}

void fnA() 
{ 
    cout << "Function A." << endl; 
}

function<void()> fnB = [&]() -> void 
{
    cout << "Function B." << endl;
};

void RunTest() 
{
    install_command("#1", fnA);
    install_command("#2", move(fnA));
    install_command("#3", fnB);
    install_command("#4", move(fnB));

    fnA();
    fnB();

    for (const auto& p : commands) {
        cout << p.first.c_str() << ": " << &p.second << endl;
    }
}

int main() {
    RunTest();
    return 0;
}