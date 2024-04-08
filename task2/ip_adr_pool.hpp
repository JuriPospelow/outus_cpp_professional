#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <cstdint>

using namespace std;

using IP_Addr = array<int,4>;

class IP_Adr_Pool
{
public:
    IP_Adr_Pool(const vector<string>& tmp);
    vector<IP_Addr> filter_ip(const int search_value) const;
    vector<IP_Addr> filter(const std :: initializer_list <int> & search_value);

   multiset<IP_Addr> _ip_pool;
private:
    vector<string> _string_pool;
    bool sorted {};

    constexpr void update_trigger(IP_Addr& value, const std :: initializer_list <int> & search_value);

};
