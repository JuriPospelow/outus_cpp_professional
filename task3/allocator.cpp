#include <iostream>
#include <map>
#include <cassert>
#include <array>
#include "custom_allocator.hpp"
#include <stdlib.h>

using namespace std;

int factorial(int n) {
  if(n > 1)
    return n * factorial(n - 1);
  else
    return 1;
}

template <typename T, size_t SIZE, typename Allocator = std::allocator<T>>
class FIFO {
    using allocator_type = Allocator;
public:
    // FIFO():_alloc(Allocator()) {}
    void push_back([[maybe_unused]]T element)
    {

        _p_array[_p_back] = _alloc.allocate(1);
        _alloc.construct(_p_array[_p_back], element);
        ++_p_back;
    }

    T pop()
    {
        if(_p_front >= SIZE) exit(EXIT_FAILURE);
        T* front_ptr = _p_array[_p_front];
        _p_front++;
        T tmp = *front_ptr;
        _alloc.destroy(front_ptr);
        _alloc.deallocate(front_ptr,1);
        return tmp;
    }

    bool is_empty() {return _p_front == _p_back;}
    size_t size() {return _p_back - _p_front;}

private:
    allocator_type _alloc;
    // *T _p_array[SIZE];
    array <T*,SIZE> _p_array;
    size_t _p_back{0};
    size_t _p_front{0};
};

int main ()
{
    map <int,int> map1;

    for(int i = 0; i < 10; ++i) {
     map1.insert ( std::pair<int,int>(i,factorial(i)));
    }

    for(auto item : map1){
        cout << item.first <<  " " << item.second << endl;
    }

    std::map<int, int, std::less<int>, std_11_simple_allocator<std::pair<const int, int>, 10 > > map2;

    for(int i = 0; i < 10; ++i) {
     map2.insert ( std::pair<int,int>(i,factorial(i)));
    }

    cout << "size of map2: " << map2.size() << endl;

    for(auto item : map2){
        cout << item.first <<  " " << item.second << endl;
    }


    FIFO <int, 10> queue;
    for(int i = 0; i < 10; ++i) {
        queue.push_back(i);
    }
    cout << "EMPTY: " << queue.is_empty() << endl;
    cout << "SIZE: " << queue.size() << endl;

    for(int i = 0; i < 10; ++i) {
        int tmp = queue.pop();
        assert(tmp == i);
        cout << tmp << endl;
    }

    FIFO <int, 10, std_11_simple_allocator<int, 10 >> queue_cust_alloc;
    for(int i = 0; i < 10; ++i) {
        queue_cust_alloc.push_back(i);
    }
    for(int i = 0; i < 10; ++i) {
        int tmp = queue_cust_alloc.pop();
        assert(tmp == i);
        cout << tmp << endl;
    }

    return 0;
}
