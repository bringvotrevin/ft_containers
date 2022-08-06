#include "vector.hpp"

vector<int>::iterator veci;
vector<int>::const_iterator vecic = veci; => int *
vector<int>::iterator veci2 = vecic; => const int *
vector<int>::const_iterator vecic2 = vecic; => const int *



