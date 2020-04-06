#include <iostream>
using namespace std;

template <class T>
class Compare
{
public:
	Compare(T a, T b) : x(a), y(b) {}
	T max() { return x > y ? x : y; }
	T min() { return x < y ? x : y; }

private:
	T x;
	T y;
};

int main()
{
	Compare<int> c1(10, 20);
	cout << "max = " << c1.max() << endl;
	cout << "min = " << c1.min() << endl;

	Compare<double> c2(12.5, 23.6);
	cout << "max = " << c2.max() << endl;
	cout << "min = " << c2.min() << endl;

	Compare<char> c3('A', 'a');
	cout << "max = " << c3.max() << endl;
	cout << "min = " << c3.min() << endl;

	return 0;
}