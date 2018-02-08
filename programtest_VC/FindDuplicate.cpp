#include "stdafx.h"
#include "FindDuplicate.h"

// A recursive function to look through all file in given path
void FindDuplicate::lookThrough(const path& p)
{
	if (!exists(p))
	{
		cout << "Path dose not exist!" << endl;
		return;
	}
	// get iterater
	// for each check directory or file
	for (directory_entry& i : directory_iterator(p))
	{
		// 	if directory call itself
		if (is_directory(i)) lookThrough(i.path());

		// 	else if file add to list then return
		else if (is_regular_file(i))
		{
			// add to 2d vector
			_addToList(i.path());
		}
		else cout << "neither directory nor file " << i.path() << endl;
	}
}

// A procedure to output the vectorlist in alphabetical order
void FindDuplicate::output()
{
	_removeSingleEntry();
	// go through duplicate list then sort alphabetically
	sort(_list.begin(), _list.end(),
		[](vector<path>& a, vector<path>& b) -> 
		bool {return a.front().filename() < b.front().filename(); });

	// print file name then directory in given format
	for (auto&& i : _list)
	{
		// sort them by number of elements in the path
		sort(i.begin(), i.end(), 
			[](path& a, path& b) -> 
			bool {return a.size() < b.size(); });
		
		cout << i.front().filename() << endl;

		for (auto&& j : i)
			cout << '\t' << j.parent_path() << endl;
	}
}

void FindDuplicate::_addToList(const path& p) 
{
	// iterate through the list and see if they are same ( by name and size )
	for (auto&& i : _list)
		// if same, add to that list
		if (_isSameFile(i.front(), p))
		{
			i.push_back(p);
			return;
		}
	
	// same not found -> make new vector
	_list.push_back(vector<path>(1, p));

}

void FindDuplicate::_removeSingleEntry()
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].size() == 1)
			_list.erase(_list.begin() + i);
	}
}

// A function to find duplicates (check name and size)
bool FindDuplicate::_isSameFile(const path& p1, const path& p2)
{
	return (file_size(p1) == file_size(p2)) && (p1.filename() == p2.filename());
}

// level 2 function, opens file and check the contents
bool FindDuplicate::_isSameContent(const path& p1, const path& p2)
{
	// check file size and return false if different
	return _isSameFile(p1, p2);
	// check hash and return false if different

	// check the content byte by byte
	// compare speed
	return true;
}

// level 3 function, group the files. check if the duplicates are all in same directories
// in 2d vector we have the map of all the files.
// size > 1 are duplicates. we can say two file are one group if they have same directory for every copy.
// first check if length of vector is same -> not same group if different
// then go through every components, if one component don't finda pair return false
// once they are identified as a group

