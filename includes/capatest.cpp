#include <iostream>
#include <vector>

using namespace std;

int	main()
{
	vector<int> v(5, 2);
	cout << v[0] << endl;
	// cout << v[1] << endl;
	cout << "capacity : " << v.capacity() << endl;
	cout << "size : " << v.size() << endl << endl;
	v.push_back(5);
	cout << "new capacity : " << v.capacity() << endl;
	cout << "new size : " << v.size() << endl;

	vector<int> v2(5, 1);
	v2.insert(2, 9);
	cout << "vector contatins : ";
	for (vector<int>::iterator bg = v2.begin(), ed = v2.end(); bg != ed; bg++)
		cout << *bg << " ";
	return 0;
}