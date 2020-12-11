#ifndef FORBID_H
#define FORBID_H
#include <vector>

class forbid
{
public:
	static int check(const std::vector<std::vector<int> >& map, int x, int y);
	static bool fb33(std::vector<std::vector<int> > map, int x, int y);
	static bool fb44(std::vector<std::vector<int> > map, int x, int y);
	static bool fbol(std::vector<std::vector<int> > map, int x, int y);
};

#endif // FORBID_H
