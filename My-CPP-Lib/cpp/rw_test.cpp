#include "WritePriorityLock.h"
#include <iostream>
#include <thread>
#include "MyLog.h"

using namespace WTP;
using namespace std;

int num = 0;
WritePriorityLock rwlock;

void write_func(int id)
{
    while(1)
    {
        rwlock.writeLock();
        num++;
        MLOGI("id:%d,num;%d\n", id, num);
        if(num >= 10) {
            rwlock.writeUnlock();
            break;
        }
        rwlock.writeUnlock();
        this_thread::sleep_for(Ms(15));
    }
}

void read_func(int id)
{
    while(1)
    {
        rwlock.readLock();
        MLOGI("id:%d,num;%d\n", id, num);
        if(num >= 10) {
            rwlock.readUnlock();
            break;
        }
        rwlock.readUnlock();
        this_thread::sleep_for(Ms(10));
    }
}

int main(int argc, char const *argv[])
{
    thread w1(write_func, 1);
    thread w2(write_func, 2);

    thread r1(read_func, 3);
    thread r2(read_func, 4);
    thread r3(read_func, 5);
    thread r4(read_func, 6);

    // std::this_thread::sleep_for(Ss(2));

    w1.join();
    w2.join();
    r1.join();
    r2.join();
    r3.join();
    r4.join();

    return 0;
}
