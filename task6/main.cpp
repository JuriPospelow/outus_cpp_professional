#include <iostream>
#include <array>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

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



// При запуске программы необходимо создать матрицу с пустым значением 0

int main()
{

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


    return 0;
}