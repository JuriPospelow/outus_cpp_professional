#include <cstddef>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

std::ostream &operator<<(std::ostream &os, const vector<string> &container) {
	for (auto iter = std::begin(container); iter != std::end(container); ++iter) {
		if (iter != std::begin(container))
			std::cout << ".";
		os << *iter;
	}
	return os;
}

namespace juri {

template <typename T>
vector<string> print_ip(T bytes) {
	vector<string> tmp = {
		to_string(((bytes >> 56) & 0xff)),
		to_string(((bytes >> 48) & 0xff)),
		to_string(((bytes >> 40) & 0xff)),
		to_string(((bytes >> 32) & 0xff)),
		to_string(((bytes >> 24) & 0xff)),
		to_string(((bytes >> 16) & 0xff)),
		to_string(((bytes >>  8) & 0xff)),
		to_string(((bytes      ) & 0xff))
	};
	return tmp;
}

template <>
vector<string> print_ip(string bytes) {
	vector<string> tmp = {
		bytes
	};

	return tmp;
}

template <>
vector<string> print_ip(vector<int> bytes) {
	vector<string> tmp;
	tmp.reserve(bytes.size());
	for(size_t i=0; i < bytes.size(); ++i){
		tmp.push_back(to_string(bytes[i]));
	}
	return tmp;
}

template <>
vector<string> print_ip(list<short> bytes) {
	vector<string> tmp;
	tmp.reserve(bytes.size());
	for_each(bytes.cbegin(), bytes.cend(), [&] (const short t) {tmp.push_back(to_string(t));});
	return tmp;
}

template <>
vector<string> print_ip(int32_t bytes) {
	vector<string> tmp = {
		to_string(((bytes >> 24) & 0xff)),
		to_string(((bytes >> 16) & 0xff)),
		to_string(((bytes >>  8) & 0xff)),
		to_string(((bytes      ) & 0xff))
	};

	return tmp;
}

template <>
vector<string> print_ip(int16_t bytes) {
	vector<string> tmp = {
		to_string(((bytes >>  8) & 0xff)),
		to_string(((bytes      ) & 0xff))
	};

	return tmp;
}

template <>
vector<string> print_ip(int8_t bytes) {
vector<string> tmp = {
	to_string(((bytes      ) & 0xff))
		};
	return tmp;
}

}
/*
print_ip( int8_t{-1} ); // 255
print_ip( int16_t{0} ); // 0.0
print_ip( int32_t{2130706433} ); // 127.0.0.1
print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
print_ip( std::string{“Hello, World!”} ); // Hello, World!
print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100
print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
*/

int main() {

	cout << "juri::print_ip(int32_t{2130706433}): ";
	cout << juri::print_ip(int32_t{2130706433}) << endl;

	cout << "juri::print_ip(int16_t{0}): ";
	cout << juri::print_ip(int16_t{0}) << endl;

	cout << "juri::print_ip(int8_t{-1}: ";
	cout << juri::print_ip(int8_t{-1}) << endl;

	cout << "juri::print_ip(int64_t{8875824491850138409}: ";
	cout << juri::print_ip(int64_t{8875824491850138409}) << endl;

	cout << "juri::print_ip(string{“Hello, World!”}: ";
	cout << juri::print_ip(string{"Hello, World!"}) << endl;

	cout << "juri::print_ip(vector<int>{100, 200, 300, 400}: ";
	cout << juri::print_ip(vector<int>{100, 200, 300, 400}) << endl;

	cout << "juri::print_ip(list<short>{400, 300, 200, 100}: ";
	cout << juri::print_ip(list<short>{400, 300, 200, 100}) << endl;

	return 0;
}