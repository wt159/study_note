// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <memory>
#include <map>

using std::cout;
using std::endl;

std::mutex mtx;           // mutex for critical section

class A {
public:
    A():_num(0) {cout << "construct A" << endl; }
    ~A() { cout << "destruct A" << endl;}
    void pintfa(){ std::cout << "class A print:num=" << _num <<  std::endl; }
    void setNum(int num){ _num = num; }
    void closea() { cout << "class A close" << endl; }
private:
    int _num;
};

struct MutexGroup{
    A *_a;
    std::mutex *_mutex;  
    MutexGroup():_mutex(nullptr),_a(nullptr)
    {
        cout << "construct MutexGroup" << endl;
    }
    ~MutexGroup()
    {
        if(_a) {
            _a->closea();
            delete _a;
            _a = nullptr;
            cout << "delete A" << endl;
        }
        if(_mutex) {
            delete _mutex;
            _mutex = nullptr;
            cout << "delete mutex" << endl;
        }
    }
};

void print_block (MutexGroup *p) 
{
  // critical section (exclusive access to std::cout signaled by locking mtx):
  for(int i=0; i<10; ++i) {
      std::unique_lock<std::mutex> lock(*(p->_mutex));
      p->_a->pintfa();
  }
}

std::map<std::string, std::shared_ptr<MutexGroup>> _strMap;
std::string s("weitaiping");

void test()
{
    cout << "test start construct" << endl;
    // MutexGroup temp;
    // temp._a = new A;
    // temp._mutex = new std::mutex;
    // temp._a->setNum(2);
    // temp._a->pintfa();
    MutexGroup* temp = new MutexGroup;
    temp->_a = new A;
    temp->_mutex = new std::mutex;
    temp->_a->setNum(3);
    temp->_a->pintfa();
    _strMap[s]= std::make_shared<MutexGroup>(*temp);

}

int main ()
{
//     MutexGroup mg;
//     mg._a = new A;
//     mg._mutex = new std::mutex;
    
//   std::thread th1 (print_block, &mg);
//   std::thread th2 (print_block, &mg);

//   th1.join();
//   th2.join();

  test();
    cout << "1111111\n" << endl;
    auto it = _strMap.find(s);
    if(it != _strMap.end()) {
        it->second->_a->pintfa();
    }

    cout << "------------\n" << endl;
    _strMap.erase(s);
    cout << "------------\n" << endl;
    
  return 0;
}