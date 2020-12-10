#ifndef FORBID_H
#define FORBID_H
#include <vector>

class forbid
{
public:
	int check(std::vector<std::vector<int> > map, int x, int y);
	bool fb33(std::vector<std::vector<int> > map, int x, int y);
	bool fb44(std::vector<std::vector<int> > map, int x, int y);
	bool fbol(std::vector<std::vector<int> > map, int x, int y);
};

#endif // FORBID_H
