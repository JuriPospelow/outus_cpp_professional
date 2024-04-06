#include <iostream>
#include "ip_adr_pool.hpp"

using namespace std;

ostream& operator<<(std::ostream& os, const IP_Addr& ip)
      {
        auto separator = "";
        for(auto item : ip)
        {
          cout << separator << item ;
          separator = ".";
        }
          return os;
      }


void print(vector<IP_Addr> data)
{
  for (auto i = data.cbegin(); i < data.cend(); ++i){
    cout << *i << endl;
  }
}

int main()
{
    try
    {

      vector<string> tmp_v;
      for(std::string line; std::getline(std::cin, line);)
      {
          string tmp = line.substr(0,line.find('\t'));
          if(tmp.find('.')) tmp_v.push_back(tmp);
      }
      IP_Adr_Pool pool(tmp_v);

      for (auto i(pool._ip_pool.rbegin()), end(pool._ip_pool.rend());
          i != end;
          ++i)
      {
        cout << *i << endl;
      }
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

      print(pool.filter(IP_Addr{1}));

// cout << pool.filter("1");
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
      print(pool.filter(IP_Addr{46,70}));

// cout << pool.filter("46","70");
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

      print(pool.filter_ip(46));

// // cout << pool << pool.filter("1") << pool.filter("46", "70") << pool.filter_any("46");

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
