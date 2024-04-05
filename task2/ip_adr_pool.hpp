#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <cstdint>

using namespace std;

class IP_Adr_Pool
{
public:
    IP_Adr_Pool(vector<string>& tmp);
    void sort(){sortIPAddress(); sorted = true;}
    void reverse(){ if(!sorted) sort(); std::reverse(_string_pool.begin(), _string_pool.end());}
    // void reverse(int t){ ++t; std::reverse(_ip_pool.begin(), _ip_pool.end());}
    vector<string> get() {return  _string_pool;}
    friend ostream& operator<<(std::ostream& os, const IP_Adr_Pool &ip);
    vector<string> filter( const string str1, [[maybe_unused]] const string str2="");
    vector<string> filter_any( const string str1);
   
   multiset<vector<int>> _ip_pool;
private:
   vector<string> _string_pool;
   bool sorted {};

// Custom Comparator to sort the array in increasing order
    bool customComparator(string a, string b);
    // Function to sort the IP Addresses
    void sortIPAddress() {
        // Sort the Array using Custom Comparator
        std::sort(_string_pool.begin(), _string_pool.end(), bind(&IP_Adr_Pool::customComparator, this, std::placeholders::_1, std::placeholders::_2)); // wieso direct geht nicht???
    }
};
