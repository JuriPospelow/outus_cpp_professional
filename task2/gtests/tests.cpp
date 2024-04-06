#include <gtest/gtest.h>

#include "../ip_adr_pool.hpp"

 TEST(CheckFiltration, ReverseLexicographical) {
    vector<string> tmp_v {"67.232.81.208", "85.254.10.197", "23.240.215.189", "1.29.168.152", "185.69.186.168"};
    vector<IP_Addr> expecteed = {{185,69,186,168}, {85,254,10,197}, {67,232,81,208}, {23,240,215,189}, {1,29,168,152}};

    IP_Adr_Pool pool(tmp_v);
    int mi = 0;
    int vi = 0;
   for (auto i(pool._ip_pool.rbegin()), end(pool._ip_pool.rend()); i != end; ++i) {
      for(auto item = (*i).cbegin(); item < (*i).cend(); ++item) {
         ASSERT_EQ(expecteed[mi][vi], *item);
         ++vi;
      }
      ++mi;
      vi = 0;
   }

}
