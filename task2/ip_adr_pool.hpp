#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <cstdint>

using namespace std;

using IP_Addr = vector<int>;

class IP_Adr_Pool
{
public:
    IP_Adr_Pool(vector<string>& tmp);
    vector<IP_Addr> filter(const IP_Addr& search_value);
    vector<IP_Addr> filter_ip(int search_value);

   multiset<vector<int>> _ip_pool;
private:
    vector<string> _string_pool;
    bool sorted {};

    void update_trigger(IP_Addr& value, const IP_Addr& search_value);

};
