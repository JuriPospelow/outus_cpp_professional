#include <cstddef>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>

using namespace std;

template <
	template <typename> typename Container,
	typename Type,
	typename = std::enable_if_t<
		std::is_same_v<Container<Type>, std::vector<Type>> ||
		std::is_same_v<Container<Type>, std::list<Type>>
		>
	>
std::ostream &operator<<(std::ostream &os, const Container<Type> &container) {
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
	vector<string> tmp;
	for (long unsigned int i = sizeof(T)*8 - 8; i != 0; i=i-8) {
		tmp.push_back(to_string((( i > 0 ? bytes >>  i : bytes) & 0xff)));
	}
	tmp.push_back(to_string(((bytes) & 0xff)));
	return tmp;
}

template <>
vector<string> print_ip(string bytes) {
	vector<string> tmp = {
		bytes
	};

	return tmp;
}

template <
	template <typename> typename Container,
	typename Type,
	typename = std::enable_if_t<
		std::is_same_v<Container<Type>, std::vector<Type>> ||
		std::is_same_v<Container<Type>, std::list<Type>>
		>
	>
vector<string> print_ip(const Container<Type> bytes) {
	vector<string> tmp;
	tmp.reserve(bytes.size());
	for_each(bytes.cbegin(), bytes.cend(), [&] (const short t) {tmp.push_back(to_string(t));});
	return tmp;
}

// template <
// 	typename Types,
// 	template <typename> typename T,
// 	typename Fake = typename std::enable_if_t<
// 		std::is_same_v<<T<Types ...>, std::tuple<Types ...>>
// >
// vector<string> print_ip2(T bytes) {
// 	auto [p, q, r, s] = bytes;
// 	vector<string> tmp {to_string(p), to_string(q), to_string(r), to_string(s)};
// 	return tmp;
// }

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
	cout << "juri::print_ip(int8_t{-1}: ";
	cout << juri::print_ip(int8_t{-1}) << endl;

	cout << "juri::print_ip(int16_t{0}): ";
	cout << juri::print_ip(int16_t{0}) << endl;

	cout << "juri::print_ip(int32_t{2130706433}): ";
	cout << juri::print_ip(int32_t{2130706433}) << endl;

	cout << "juri::print_ip(int64_t{8875824491850138409}: ";
	cout << juri::print_ip(int64_t{8875824491850138409}) << endl;

	cout << "juri::print_ip(string{“Hello, World!”}: ";
	cout << juri::print_ip(string{"Hello, World!"}) << endl;

	cout << "juri::print_ip(vector<int>{100, 200, 300, 400}: ";
	cout << juri::print_ip(vector<int>{100, 200, 300, 400}) << endl;

	cout << "juri::print_ip(list<short>{400, 300, 200, 100}: ";
	cout << juri::print_ip(list<short>{400, 300, 200, 100}) << endl;

	// cout << "juri::print_ip(make_tuple(123, 456, 789, 0): ";
	// cout << juri::print_ip2(make_tuple(123, 456, 789, 0)) << endl;

	return 0;
}