#include <gtest/gtest.h>

#include "../ip_adr_pool.hpp"

 TEST(CheckFiltration, ReverseLexicographical) {
    vector<string> tmp_v {"67.232.81.208", "85.254.10.197", "23.240.215.189", "1.29.168.152", "185.69.186.168"};
    vector<string> expecteed = {"185.69.186.168", "85.254.10.197", "67.232.81.208", "23.240.215.189", "1.29.168.152"};

    IP_Adr_Pool pool(tmp_v);
    pool.reverse();
    auto result = pool.get();

    for(auto i = 0; i < expecteed.size(); ++i) {
       ASSERT_EQ(expecteed[i], result[i]);
    }

}
