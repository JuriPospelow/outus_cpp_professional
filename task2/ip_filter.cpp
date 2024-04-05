#include <iostream>
#include "ip_adr_pool.hpp"

using namespace std;

ostream& operator<<(std::ostream& os, const vector<int> &ip)
      {
        auto separator = "";
        for(auto item : ip)
        {
          cout << separator << item ;
          separator = ".";
        }
          return os;
      }

int main(/* int argc, char const *argv[] */)
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
      pool.reverse();


      for (std::multiset<vector<int>>::reverse_iterator i(pool._ip_pool.rbegin()), end(pool._ip_pool.rend());
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

      std::multiset<vector<int>>::iterator itup;
      itup = pool._ip_pool.upper_bound({1,255,255,255});
      while(--itup != pool._ip_pool.end()){
        cout << *itup << endl;
      }
// cout << pool.filter("1");
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
      itup = pool._ip_pool.upper_bound({46,70,255,255});
      vector<int> tmp_vec = {46, 70, 0,0};
      while(--itup != pool._ip_pool.end() && *itup > tmp_vec){
        cout << *itup << endl;
      }
// cout << pool.filter("46","70");
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

      for (std::multiset<vector<int>>::reverse_iterator i(pool._ip_pool.rbegin()), end(pool._ip_pool.rend());
          i != end;
          ++i)
        {
          // Each element is a vector
          if(find((*i).begin(), (*i).end(), 46) != (*i).end()) {
            cout << *i << endl;
          }

        }


// // cout << pool << pool.filter("1") << pool.filter("46", "70") << pool.filter_any("46");

// cout << pool.filter_any("46");

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
