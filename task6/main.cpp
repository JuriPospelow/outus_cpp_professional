#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <map>
#include <cassert>

using namespace std;

struct indexer{
    virtual int get_index(int ind) = 0;
};

template<typename T>
struct cell_owner{
    virtual void set_cell_value(T val, indexer* indr) = 0;
    virtual T get_cell_value(indexer* indr) = 0;
};


template<typename T, size_t N>
class cell_proxy:public indexer
{
    cell_owner<T>* m_cell_owwner;
    array<int,N> m_indexer;
    size_t _index = 0;
public:
    cell_proxy(int index, cell_owner<T>* cell){
        m_cell_owwner = cell;
        m_indexer[_index++] = index;
    }

    cell_proxy<T,N>& operator[](int index){
        m_indexer[_index++] = index;
        return *this;
    }

    cell_proxy& operator=(const T val){
        m_cell_owwner->set_cell_value(val, this);
        return *this;
    }

    int get_index(int ind) {
        return m_indexer[ind];
    }

    operator T ()
    {
      return m_cell_owwner->get_cell_value(this);
    }
};

template<typename T, size_t N, T def>
 class tensor{
    map<int,map<int,T>> m_cell;
    size_t _size=0;
public:
    std::vector<tuple<int, int, T>> adapter_tensor;

    void set_value(T val, indexer* indr){
        int i1 = indr->get_index(0);
        int i2 = indr->get_index(1);
        m_cell[i1][i2] = val;
        ++_size;
        adapter_tensor.push_back(make_tuple(i1,i2,val));
    }
    T get_value(indexer* indr){
        int i1 = indr->get_index(0);
        int i2 = indr->get_index(1);
        if(m_cell.find(i1) == m_cell.end()) {
            return def;
        } else if(m_cell[i1].find(i2) == m_cell[i1].end()){
            return def;
        }
        return m_cell[i1][i2];
    }

    size_t size(){
        return _size;
    }

};

template<typename T, size_t N, T def>
class Matrix:public cell_owner<T>{
    tensor<T,N,def> m_tensor;
public:
  cell_proxy<T,N> operator[](int ind){
      return cell_proxy<T,N>(ind, this);
  }
  void set_cell_value(T val, indexer* indr){
    m_tensor.set_value(val, indr);
  }
  T get_cell_value(indexer* indr){
    return m_tensor.get_value(indr);
  }
  size_t size(){
    return m_tensor.size();
  }

  typename vector<tuple<int,int,T>>::iterator  begin(){return m_tensor.adapter_tensor.begin();}
  typename vector<tuple<int,int,T>>::iterator end(){return m_tensor.adapter_tensor.end();}

};

int main()
{
    Matrix<int, 2, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    ((matrix[100][100] = 314) = 0) = 217;
    assert(matrix[100][100] == 217);

    // выведется одна строка
    // 100100314
    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

// При запуске программы необходимо создать матрицу с пустым значением 0, заполнить главную диагональ матрицы (от [0,0] до [9,9]) значениями от 0 до 9.
    Matrix<int, 2, 0> matrix2;
    auto tmp = matrix2[0][0];
    assert(tmp == 0);

    for (size_t i = 1; i < 10; ++i){
        matrix2[i][i] = i;
    }

    for (int i = 1; i < 10; ++i){
        assert(matrix2[i][i] == i);
    }

// Второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0.
    for (size_t i = 1; i < 10; ++i){
        matrix2[i][9-i] = 9-i;
    }

    for (int i = 1; i < 10; ++i){
        assert(matrix2[i][9-i] == 9-i);
    }

// вывести фрагмент матрицы от [1,1] до [8,8]. Между столбцами пробел.
    for (size_t i = 1; i < 9; ++i){
        for (size_t j = 1; j < 9; ++j){
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }

// количество занятых ячеек.
    cout << "size: " << matrix2.size() << endl;

// все занятые ячейки вместе со своими позициями.
    for(auto c: matrix2)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "x: " << x << " y: " << y << " value: " << v << std::endl;
    }


// каноническую форму оператора =, допускающую выражения
    ((matrix2[100][100] = 314) = 0) = 217;
    assert(matrix2[100][100] == 217);

    return 0;
}