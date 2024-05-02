#include <iostream>
#include <array>
#include <cassert>

using namespace std;

template<typename T, size_t S, T defVal>
struct Array{
  T*p;
  size_t size_array = 0;
  Array(){
      p = new T [S];
  }
  int& operator[](int index){

      return  p[index];
  }

//   int operator[](int index){

//       return  defVal;
//   }

};

template<typename T, size_t S, T defVal>
struct Array2Dimensional{
    Array<T,S, defVal>*p;
    size_t size_ = 0;
    size_t size(){
        return size_;
    }

    Array2Dimensional(){
        p = new Array<T,S,defVal> [S];
    }

    Array<T,S,defVal>& operator[](int ind){
        return p[ind];
    }

};

Array2Dimensional <int, 10, -1> ad;



// При запуске программы необходимо создать матрицу с пустым значением 0

int main()
{

    assert(ad.size() == 0); // все ячейки свободны

    // auto a = ad[0][0];

    // assert(a == -1);
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


    return 0;
}