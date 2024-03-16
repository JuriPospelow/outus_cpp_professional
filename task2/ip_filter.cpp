#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

#include <functional>

using namespace std;

class IP_Adr_Pool
{
public:
    IP_Adr_Pool() {
        for(std::string line; std::getline(std::cin, line);)
        {
            string tmp = line.substr(0,line.find('\t'));
            if(tmp.find('.')) _string_pool.push_back(tmp);
        }
    }
    void sort(){sortIPAddress(); sorted = true;}
    void reverse(){ if(!sorted) sort(); std::reverse(_string_pool.begin(), _string_pool.end());}
    vector<string> get() {return  _string_pool;}
    friend ostream& operator<<(std::ostream& os, const IP_Adr_Pool &ip)
    {
       for(auto item : ip._string_pool)
       {
           cout << item << endl;
       }
        return os;
    }
    vector<string> filter( const string str1, [[maybe_unused]] const string str2="")
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
    vector<string> filter_any( const string str1)
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
private:
   vector<string> _string_pool;
   bool sorted {};

// Custom Comparator to sort the array in increasing order
    bool customComparator(string a, string b) {
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
    // Function to sort the IP Addresses
    void sortIPAddress() {
        // Sort the Array using Custom Comparator
        std::sort(_string_pool.begin(), _string_pool.end(), bind(&IP_Adr_Pool::customComparator, this, std::placeholders::_1, std::placeholders::_2)); // wieso direct geht nicht???
    }
};

    ostream& operator<<(std::ostream& os, const vector<string> &ip)
    {
       for(auto item : ip)
       {
           cout << item << endl;
       }
        return os;
    }

int main(/* int argc, char const *argv[] */)
{
    try
    {

        // TODO reverse lexicographically sort
// convert vector<vector<string>> to vector<string>
        IP_Adr_Pool pool;
        pool.reverse();

        // auto convertor = pool.get();

        // for(auto item : convertor)
        // {
        //    cout << item << endl;
        // }


        // cout << pool ;
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

    //   for(auto item : convertor)
    //   {
    //       if(item[0] == '1' && item[1] == '.') cout << item << endl;
    //   }

// cout << pool.filter("1");
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

#if 0
       for(auto item : convertor)
       {
           if(item[0] == '4' && item[1] == '6' && item[2] == '.' && item[3] == '7' && item[4] == '0') cout << item << endl;
       }
#endif

// cout << pool.filter("46","70");
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

cout << pool << pool.filter("1") << pool.filter("46", "70") << pool.filter_any("46");

// cout << pool.filter_any("46");
#if 0
       for(auto item : convertor)
       {
           if((item[0] == '4' && item[1] == '6' && item[2] == '.')
                || (item[item.find(".") + 1] == '4' && item[item.find(".") + 2] == '6' && item[item.find(".") + 3] == '.')
                || (item[item.find(".", item.find(".")+1)+1] == '4' && item[item.find(".", item.find(".")+1) + 2] == '6' && item[item.find(".", item.find(".")+1) + 3] == '.')
                || (item[item.size() - 3] == '.' && item[item.size() - 2] == '4' && item[item.size()-1] == '6' ))
                    cout << item << endl;
       }
#endif

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
