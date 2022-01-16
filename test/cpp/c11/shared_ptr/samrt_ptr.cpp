#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

class shared_count
{
public:
    shared_count() : _count(1)
    {
    }
    void add_count()
    {
        ++_count;
    }
    long reduce_count()
    {
        return --_count;
    }
    long get_count() const
    {
        return _count;
    }

private:
    long _count = 1;
};

template <typename T>
class smart_ptr
{
public:
    template <typename U>
    friend class smart_ptr;

    smart_ptr(T *ptr = nullptr) noexcept
        : _ptr(ptr)
    {
        if (_ptr)
        {
            _sharedCount = new shared_count();
        }
    }

    smart_ptr(const smart_ptr &other) noexcept
        : _ptr(other._ptr)
    {
        if (_ptr)
        {
            other._sharedCount->add_count();
            _sharedCount = other._sharedCount;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U> &other) noexcept
        : _ptr(other._ptr)
    {
        if (_ptr)
        {
            other._sharedCount->add_count();
            _sharedCount = other._sharedCount;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U> &&other) noexcept
        : _ptr(other._ptr)
    {
        if (_ptr)
        {
            _sharedCount = other._sharedCount;
        }
    }

    ~smart_ptr() noexcept
    {
        if (_ptr && _sharedCount->reduce_count() == 0)
        {
            delete _ptr;
            _ptr = nullptr;
            delete _sharedCount;
            _sharedCount = nullptr;
        }
    }

    void swap(smart_ptr &other) noexcept
    {
        using std::swap;
        swap(_ptr, other._ptr);
        swap(_sharedCount, other._sharedCount);
    }

    T *get() noexcept { return _ptr; }
    T &operator*() const noexcept { return *_ptr; }
    T *operator->() const noexcept { return _ptr; }
    operator bool() const noexcept { return _ptr; }

    smart_ptr &operator=(smart_ptr other) noexcept
    {
        other.swap(*this);
        return *this;
    }

    long use_count() const noexcept
    {
        if (_ptr)
        {
            return _sharedCount->get_count();
        }
        else
        {
            return 0;
        }
    }

private:
    T *_ptr = nullptr;
    shared_count *_sharedCount = nullptr;
};


class shape {
public:
  virtual ~shape() {}
};

class circle : public shape {
public:
  ~circle() { puts("~circle()"); }
};

int main()
{
  smart_ptr<circle> ptr1(new circle());
  printf("use count of ptr1 is %ld\n",
         ptr1.use_count());
  smart_ptr<shape> ptr2;
  printf("use count of ptr2 was %ld\n",
         ptr2.use_count());
  ptr2 = ptr1;
  printf("use count of ptr2 is now %ld\n",
         ptr2.use_count());
  if (ptr1) {
    puts("ptr1 is not empty");
  }
}