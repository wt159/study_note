#include <iostream>
#include <dlfcn.h>
#include "singleton.h"
int main()
{
    using namespace std;

    // call singleton firstly
    singleton::instance().num = 100;
    cout << "singleton.num in main : "
         << singleton::instance().num << endl;

    // open the library
    void *handle = dlopen("./hello.so", RTLD_LAZY);
    if (!handle)
    {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // load the symbol
    typedef void (*hello_t)();

    // reset errors
    dlerror();
    hello_t hello = (hello_t)dlsym(handle, "hello");
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        cerr << "Cannot load symbol 'hello': "
             << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    hello(); // call method in the plugin
    // call singleton secondly
    cout << "singleton.num in main : "
         << singleton::instance().num << endl;
    dlclose(handle);
}