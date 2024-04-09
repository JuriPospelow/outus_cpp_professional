#include <iostream>
#include <map>
#include <cassert>
#include <array>

using namespace std;

int factorial(int n) {
  if(n > 1)
    return n * factorial(n - 1);
  else
    return 1;
}


template <class T, unsigned S>
struct std_11_simple_allocator {
    using value_type = T;
    unsigned max_size = S;
    void* memory = nullptr;
    unsigned cnt = 0;

    std_11_simple_allocator () noexcept {}
    template <class U, unsigned M> std_11_simple_allocator(const std_11_simple_allocator<U,M>& ) noexcept {}

    ~std_11_simple_allocator()
    {
        if(memory != nullptr){
            cnt = 0;
            free(memory);
            memory = nullptr;
        }
        cout << "all DTOR" << endl;
    }

    template <class U>
    struct rebind {
        using other = std_11_simple_allocator<U, S>;
    };

    T* allocate (std::size_t n)
    {
        if(memory == nullptr){
            memory = malloc(max_size*sizeof(T));
            if(memory == nullptr) throw bad_alloc();
            cout << "all init: " << (void*)memory <<endl;
        } else if(n > max_size) {
            cout << "all ERROR" << endl;
            throw bad_alloc();
        }
        if (cnt + n <= max_size) {
            auto chunk = reinterpret_cast<T *>(memory) + cnt;
            cnt += n;
            cout << "all: " << (void*)chunk << endl;
            return chunk;
        } else {
            cout << "all ERROR CNT" << endl;
            throw bad_alloc();
        }
    }

    void deallocate ([[maybe_unused]] T* p, [[maybe_unused]]std::size_t n)
    {
        // ::operator delete(p);
    }
};

template <class T, unsigned U,  class TA, unsigned UA>
constexpr bool operator== (const std_11_simple_allocator<T,U>& a1, const std_11_simple_allocator<TA,UA>& a2) noexcept
{
    return true;
}

template <class T, unsigned U, class TA, unsigned UA>
constexpr bool operator!= (const std_11_simple_allocator<T,U>& a1, const std_11_simple_allocator<TA,UA>& a2) noexcept
{
    return false;
}

template <typename T, size_t SIZE>
class FIFO {
public:
    void push_back([[maybe_unused]]T element) {}
    T pop() {return *_p_front;}
private:
    array <T,SIZE> _array;
    T* _p_back;
    T* _p_front;
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
