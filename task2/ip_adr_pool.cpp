#include "ip_adr_pool.hpp"

ostream& operator<<(std::ostream& os, const IP_Adr_Pool &ip)
{
   for(auto item : ip._string_pool)
   {
       cout << item << endl;
   }
    return os;
}

vector<string> IP_Adr_Pool::filter( const string str1, [[maybe_unused]] const string str2)
{
    vector<string> tmp;
    for(auto item : _string_pool)
    {
        if(str2 == ""){
            if(item.find(str1 + ".") == 0) tmp.push_back(item);
        } else {
            if(item.find(str1 + ".") == 0 && item.find(str2 + ".") == item.find(".")+1) tmp.push_back(item);
        }
    }
    return tmp;
}

vector<string> IP_Adr_Pool::filter_any( const string str1)
{
    vector<string> tmp;
    auto first_byte = [&str1](string str){return str.find(str1 + ".") == 0;};
    auto middle_bytes = [&str1](string str){return str.find("." + str1 + ".") != string::npos;};
    auto last_byte = [&str1](string str){return str.find("." + str1) == str.size() - str1.size() - 1;};
    for(auto item : _string_pool)
    {
        if(first_byte(item) || middle_bytes(item) || last_byte(item)) tmp.push_back(item);
    }
    return tmp;
}


// Custom Comparator to sort the array in increasing order
bool IP_Adr_Pool::customComparator(string a, string b) {
    // Breaking into the octets
    vector<string> octetsA;
    vector<string> octetsB;
    string octet = "";
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] == '.') {
            octetsA.push_back(octet);
            octet = "";
        } else {
            octet += a[i];
        }
    }
    octetsA.push_back(octet);
    octet = "";
    for (size_t i = 0; i < b.size(); i++) {
        if (b[i] == '.') {
            octetsB.push_back(octet);
            octet = "";
        } else {
            octet += b[i];
        }
    }
    octetsB.push_back(octet);
    // Condition if the IP Address is same then return false
    if (octetsA == octetsB) {
        return false;
    }
    // Compare the octets and return the result
    for (int i = 0; i < 4; i++) {
        if (stoi(octetsA[i]) > stoi(octetsB[i])) {
            return false;
        } else if (stoi(octetsA[i]) < stoi(octetsB[i])) {
            return true;
        }
    }
    return false;
}
