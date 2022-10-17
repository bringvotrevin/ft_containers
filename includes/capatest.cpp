#include <iostream>
#include <vector>
#include "vector.hpp"

using namespace std;

int	main()
{
	ft::vector<int> v(5, 2);
	cout << v[0] << endl;
	cout << v[1] << endl;
	cout << "capacity : " << v.capacity() << endl;
	cout << "size : " << v.size() << endl << endl;
	v.push_back(5);
	cout << "new capacity : " << v.capacity() << endl;
	cout << "new size : " << v.size() << endl;

	ft::vector<int> v2(5, 1);
	v2.insert(v2.begin(), 9);
	cout << "vector contatins : ";
	for (ft::vector<int>::iterator bg = v2.begin(), ed = v2.end(); bg != ed; bg++)
		cout << *bg << " ";
	return 0;
}