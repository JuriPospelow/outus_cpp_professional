#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

using namespace std;

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
vector<string> sortIPAddress(vector<string> arr) {
    // Sort the Array using Custom Comparator
    sort(arr.begin(), arr.end(), customComparator);
    return arr;
}


int main(/* int argc, char const *argv[] */)
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
// convert vector<vector<string>> to vector<string>
         vector<string> convertor;
         for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
         {
           string tmp;
           for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
           {
               if (ip_part != ip->cbegin())
               {
                   tmp += ".";
               }
               tmp += *ip_part;
           }
           convertor.push_back(tmp);
       }

        convertor = sortIPAddress(convertor);

        reverse(convertor.begin(), convertor.end());
        // stable_sort(convertor.begin(), convertor.end());
#if 0
       for(auto item : convertor)
       {
           cout << item << endl;
       }
#endif



        // for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        // {
        //     for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        //     {
        //         if (ip_part != ip->cbegin())
        //         {
        //             std::cout << ".";

        //         }
        //         std::cout << *ip_part;
        //     }
        //     std::cout << std::endl;
        // }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

       for(auto item : convertor)
       {
           if(item[0] == '1' && item[1] == '.') cout << item << endl;
       }



        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

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
