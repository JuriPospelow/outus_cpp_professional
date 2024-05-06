#include <iostream>
#include <array>
#include <map>

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
struct cell_proxy:public indexer
{
    cell_owner<T>* m_cell_owwner;
    array<int,N> m_indexer;

    cell_proxy(int index, cell_owner<T>* cell){
        m_cell_owwner = cell;
        m_indexer[0] = index;
    }

    cell_proxy<T,N>& operator[](int index){
        m_indexer[1] = index;
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
 struct tensor{
    map<int,map<int,T>> m_cell;
    void set_value(T val, indexer* indr){
        int i1 = indr->get_index(0);
        int i2 = indr->get_index(1);
        m_cell[i1][i2] = val;
    }
    T get_value(indexer* indr){
        int i1 = indr->get_index(0);
        int i2 = indr->get_index(1);
        return m_cell[i1][i2];
    }

};

template<typename T, size_t N, T def>
struct Matrix:public cell_owner<T>{
    tensor<T,N,def> m_tensor;

  cell_proxy<T,N> operator[](int ind){
      return cell_proxy<T,N>(ind, this);
  }
  void set_cell_value(T val, indexer* indr){
    m_tensor.set_value(val, indr);
  }
  T get_cell_value(indexer* indr){
    return m_tensor.get_value(indr);
  }
};

int main()
{
    Matrix<int, 2, -1> m;
    m[1][10] = 5;
    std::cout<<m[1][10];

    return 0;
}