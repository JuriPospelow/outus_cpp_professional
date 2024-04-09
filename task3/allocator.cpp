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

template <typename T, size_t SIZE>
class FIFO {
public:
    void push_back([[maybe_unused]]T element)
    {
        _array[_p_back++] = element;
    }

    T pop()
    {
        if(_p_front >=  static_cast<T>(SIZE)) exit(EXIT_FAILURE);
        return _array[_p_front++];
    }

private:
    array <T,SIZE> _array;
    T _p_back{0};
    T _p_front{0};
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
    for(int i = 0; i < 10; ++i) {
        int tmp = queue.pop();
        assert(tmp == i);
        cout << tmp << endl;
    }

    return 0;
}
