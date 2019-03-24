#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>

using std::string;

/*
	Need:
	less, greater comparators
	default constructor
*/
template<typename T, typename Comparator = std::less<typename T::value_type>>
typename T::value_type binsearch(T container, const typename T::value_type& item) {
	std::sort(container.begin(), container.end());
	size_t size = container.size();
	size_t start = 0, mid = size / 2, end = size,  i = 0 ;

	if (std::greater_equal<T::value_type>()(container[start], item) &&
		std::less_equal<T::value_type>()(container[end - 1], item)) {
		return T::value_type();
	}

	while (start != end) {
		typename T::value_type value = container[mid];
		++i;
		
		if (Comparator()(value, item)) {	/* |______/xxxxxxx| */
			start = mid + (start + end) % 2;
		}
		else {								/* |xxxxxxx/______| */		
			end = mid;
		}
		mid = (start + end) / 2;
	}
	std::cout << "Iterations: " << i << '\n';
	return container[start];
}


int main() {
	std::vector<int> v = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144,
		233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657,
		46368, 75025, 121393, 196418, 317811 };
	//std::vector<string> vs = {"a", "b", "ab", "ac", "zzz"};
	//std::cout << "Value: " << binsearch(vs, "ac") <<"\n";
	for (auto i : v) {
		auto s = binsearch(v, i);
		if (s != i)
			std::cout << "Value: " << i << "\tFound: " << s << "\tERROR\n";
	}
	std::cout << "exiting ...";
	std::cin.get();
}