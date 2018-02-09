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
	_sortByFilename();

	// print file name then directory in given format
	for (auto&& i : _list)
	{
		// sort them by name of parent path
		sort(i.begin(), i.end(), 
			[](path& a, path& b) -> 
			bool {return a.parent_path() < b.parent_path(); });
		
		cout << i.front().filename().string() << endl;

		for (auto&& j : i)
			cout << '\t' << j.parent_path().string() << endl;
	}
}

void FindDuplicate::_sortByFilename()
{
	// go through duplicate list then sort alphabetically
	sort(_list.begin(), _list.end(),
		[](vector<path>& a, vector<path>& b) -> 
		bool {return a.front().filename() < b.front().filename(); });
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

#include <time.h>
// level 2 function, opens file and check the contents
bool FindDuplicate::_isSameContent(const path& p1, const path& p2)
{
	// check file size and return false if different
	if (file_size(p1) != file_size(p2)) return false;

	cout << "comparing size of " << file_size(p1) << endl;

	clock_t t = clock();

	// check hash and return false if different
	// check the content byte by byte
	// compare speed
	std::ifstream fptr1(p1.string(), ios::in|ios::binary);
	std::ifstream fptr2(p2.string(), ios::in|ios::binary);

	const int chunk = 1024*4;

	char buf1[chunk];
	char buf2[chunk];

	while (!fptr1.eof())
	{
		fptr1.read((char*)&buf1, chunk);
		fptr2.read((char*)&buf2, chunk);

		if (memcmp(buf1, buf2, chunk)) return false;
	}

	fptr1.close();
	fptr2.close();

	cout << "it took " << ((double)clock() - t)/CLOCKS_PER_SEC << " seconds" << endl;

	return true;
}

// level 3 function, group the files. 
void FindDuplicate::groupoutput()
{
	_removeSingleEntry();
	_sortByFilename();

	vector<vector<vector<path>*>> *groupTable = new vector<vector<vector<path>*>>;
	
	for (int x = 0; x < _list.size(); x++)
	{
		vector<vector<path>*> temp;
		
		bool check = true;

		// check if file is already gruoped
		for (auto&& i : *groupTable)
			for (auto&& j : i)
				if (j->front() == _list[x].front()) check = false;

		// if not grouped
		if (check) {
			temp.push_back(&_list[x]);

			// go through other file path
			for (int y = x + 1; y < _list.size(); y++)
			{
				// if they have same number of instances
				if (_list[x].size() == _list[y].size())
				{
					// compare _list[x].elements with _list[y].elements
					int counter = 0;
					for (int i = 0; i < _list[x].size(); i++)
					{
						for (int j = 0; j < _list[y].size(); j++)
						{
							if (_list[x][i].parent_path() == _list[y][j].parent_path())
							{
								counter++;
								break;
							}
						}
					}
					if (counter == _list[x].size())
					{
						// we have same group
						// cout << "same group " << _list[x].front().filename() << " and " << _list[y].front().filename() << endl;
						temp.push_back(&_list[y]);
					}
				}
			}
			groupTable->push_back(temp);
		}
	}

	// print out group table
	for (auto&& i : *groupTable)
	{
		for (int j = 0; j < i.size(); j++)
		{
			cout << i[j]->front().filename().string();
			if (j < i.size() - 1) cout << ", ";
			else cout << "" << endl;
		}
		for (auto&& k : *i.front())
			cout << '\t' << k.parent_path().string() << endl;
	}
	delete groupTable;
}
