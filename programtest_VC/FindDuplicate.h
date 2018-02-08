#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

class FindDuplicate
{
public:

	FindDuplicate() {};
	~FindDuplicate() {};
	void lookThrough(const path& p);
	void output();

private:

	vector<vector<path>> _list;
	void _addToList(const path& p);
	void _removeSingleEntry();
	bool _isSameFile(const path& p1, const path& p2);
	bool _isSameContent(const path& p1, const path& p2);
};
