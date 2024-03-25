#include <iostream>
#include <map>

using namespace std;

int factorial(int n) {
  if(n > 1)
    return n * factorial(n - 1);
  else
    return 1;
}

int main ()
{
    map <int,int> map1;

    for(int i = 0; i < 10; ++i) {
     map1.insert ( std::pair<int,int>(i,factorial(i)));
    }

    for(auto item : map1){
        cout << item.first <<  " " << item.second << endl;
    }

    return 0;
}
