#include "ip_adr_pool.hpp"

std::vector<int> split(const std::string &str, char d)
{
    std::vector<int> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(/*static_cast<uint8_t>*/(stoi(str.substr(start, stop - start))));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(/*static_cast<uint8_t>*/(stoi(str.substr(start))));

    return r;
}


IP_Adr_Pool::IP_Adr_Pool(vector<string>& tmp) :_string_pool(tmp) {
    for(auto item : tmp) {
        _ip_pool.insert(split(item, '.'));
    }
}

void IP_Adr_Pool::update_trigger(IP_Addr& value, const IP_Addr& search_value)
{
  for(size_t i = 0; i < search_value.size(); ++i){
    value[i] = search_value[i];
  }
}

vector<IP_Addr> IP_Adr_Pool::filter(const IP_Addr& search_value)
{
  IP_Addr low_trigger = {0,0,0,0}; //search_value,
  IP_Addr upper_trigger = {255,255,255,255};//trigger

  update_trigger(low_trigger,   search_value);
  update_trigger(upper_trigger, search_value);

  vector<IP_Addr> tmp;
  std::multiset<IP_Addr>::iterator itup;
  itup = _ip_pool.upper_bound(upper_trigger);
  while(--itup != _ip_pool.end()  && *itup > low_trigger){
    tmp.push_back(*itup);
  }
  return tmp;
}

vector<IP_Addr> IP_Adr_Pool::filter_ip(int search_value)
{
  vector<IP_Addr> tmp;
  for (auto i(_ip_pool.rbegin()), end(_ip_pool.rend());
      i != end;
      ++i)
    {
      // Each element is a vector
      if(find((*i).begin(), (*i).end(), search_value) != (*i).end()) {
        tmp.push_back(*i);
      }
    }
    return tmp;
 }
