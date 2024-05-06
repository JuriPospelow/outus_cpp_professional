#include <iostream>
#include <array>
#include <cassert>
#include <tuple>
#include <vector>
#include <map>

using namespace std;
#if 0
template<typename T, size_t S>
struct Array{
  T*p;
  size_t size_array = 0;
  Array(){
      p = new T [S];
  }
  int& operator[](int index){

      return  p[index];
  }

};

template<typename T, size_t S, T defVal>
struct Array2Dimensional{
    Array<T,S>*p;
    size_t size_ = 0;

    size_t size(){

        for (size_t i = 0; i < S; ++i){
            for (size_t j = 0; j < S; ++j){
                if(p[i][j] != defVal) ++size_;
            }
        }

        return size_;
    }

    Array2Dimensional(){
        p = new Array<T,S> [S];
        for (size_t i = 0; i < S; ++i){
            for (size_t j = 0; j < S; ++j){
                p[i][j] = defVal;
            }
        }
    }


    Array<T,S>& operator[](int ind){
        return p[ind];
    }

    vector<tuple<size_t, size_t, T>> getAll(){
        vector<tuple<size_t, size_t, T>>  tp;
        tuple<size_t, size_t, T> tmp;
         for (size_t i = 0; i < S; ++i){
            for (size_t j = 0; j < S; ++j){
                tmp = make_tuple(i,j,p[i][j]);
                tp.push_back(tmp);
            }
        }
        return tp;
    }
};

Array2Dimensional <int, 10, -1> ad;
#endif
#if 0
template<typename T, T defVal>
struct proxy{
    vector<T> v;
    operator T ()
    {
        return defVal;
    }
    proxy& operator=(const proxy& anather){

    }
};

template<typename T, T defVal>
 struct cell{
    map<int,proxy<T, defVal>> m;
    proxy<T, defVal>& operator[](int ind){
        return m[ind];
    }
 };

 template<typename T, T defVal>
 struct Matrix: public cell<T, defVal>
 {
    map<int,cell<T, defVal>> m;
    cell<T, defVal>& operator[](int ind){
        return m[ind];
    }
 };
 #endif

// struct sparse_matrix {
//     map<int,cell<T, defVal>> sparse_matrix;
// };

struct proxy{
    array<int,2> last_ind;
};

template<typename T>
struct proxy2{
    void set_value(const T val);
};

 template<typename T, T defVal>
 struct cell:public proxy{
    map<int,T> m;
    proxy2<T>* cell_owner;

    T& operator[](int ind){
        last_ind[1] = ind;
        return m[ind];
    }
    cell& operator=(const T val){
        cell_owner->set_value(val);
        return *this;
    }
 };

 template<typename T, T defVal>
 struct Matrix: public proxy, public cell<T,defVal> , public proxy2<T>
 {
    map<int,cell<T, defVal>> sparse_matrix;

    void set_value(const T val){
        sparse_matrix[last_ind[0]][last_ind[1]] = val;
    }

    cell<T, defVal>& operator[](int ind){
        last_ind[0] = ind;
        return sparse_matrix[ind];
    }
    size_t size(){
        return sparse_matrix.size();
    }
 };

// При запуске программы необходимо создать матрицу с пустым значением 0

int main()
{
#if 0
    assert(ad.size() == 0); // все ячейки свободны

    auto a = ad[0][0];
    assert(a == -1);
// заполнить главную диагональ матрицы (от [0,0] до [9,9]) значениями от 0 до 9.
    for (size_t i = 0; i < 9; ++i){
        ad[i][i] = i;
    }

// заполнить второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0.
    for (size_t i = 0; i < 9; ++i){
       ad[i][9-i] = 9-i;
    }

    // вывести фрагмент матрицы от [1,1] до [8,8]. Между столбцами пробел. Каждая строка матрицы на новой строке консоли.
    for (size_t i = 1; i < 9; ++i){
        for(size_t j = 1; j <9; ++j){
            std::cout<<ad[i][j] << " ";
        }
        std::cout << std::endl;
    }
    cout << ad.size() << endl;

    for(auto c: ad.getAll())
    {
        size_t x;
        size_t y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
#endif
Matrix<int,-1> pc;
pc[0][0] = 12;
auto e = pc[0][1];
e = pc[0][12];
pc[100][100] = 120;
pc[1000][100] = 120;
cout << e << " " << pc[100][100] << " " << pc.size() << endl;
    return 0;
}