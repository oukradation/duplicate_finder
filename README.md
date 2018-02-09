# Programming test
This is a c++ program that scans a given path and finds and lists out duplicates by their path. It was written with boost library and visual studio compiler. This program covers level 1 requirements and suggests some solution for level 2 and level 3.

## Overview
FindDuplicate class is written for the purpose of recyling code. The class has a public method to scan given path for duplicates and output method that prints out results. It scans through all the directories in given path, and add path object(boost.filesystem) to a 2d vector container for further processing. Once scanning is done, output functions are called which cleans up non-duplicate entries and sort the remaining entries in the alphabetical order. Then results are printed on the console. 

## Working methods
* Method `lookThrough(const path& p)` is a recursive function which scans all the directory in the given path. It iterates through directory elements while it calls itself when the element is a directory or calls private method to save the path when the element is a file.

* Private method `_addToList(const path& p)` checks the existing 2d-vector, looking for the same file. If it finds the same file, the file is added to the vector element. Otherwise new vector is created.

* Path to all the scanned files are saved into a 2-dimensional vector, with same files making a 1-d vector element.  

* Files are considered same if it has same name and size.

* Experimentary Level 2 file content checking function : Currently it opens up the two files and compare them with low level memory function `memcmp` by given chunk of memory size. This is by no means efficient way to compare two files, but it ensures 100% certainty that the files are same. Ideal method will be comparing hash of the two files. By using an external library such as `crypto++` or `openSSL`, we can easily compute something like MD5 and compare the results.

* Experitary level 3 output function `groupoutput()` : It creates a temporary 2D vector which holds pointer to 1D vector object which are filled with path with duplicate files. It acts as map of grouped files. It requires further refining, perhaps more careful integrated design to level 1 functionality.

## Some reflections
#### Choice of tools
* In order to support Windows compatibility, program is written and compiled with visual studio. For cross compatibility, we could migrating whole project into CMake project with GNU compiler support for unix systems.

* Boost library was chosen, due to its stability - compared to homebrewed code, and it's wide usage over industries. C++17 does support the filesystem classes, but It is still experimental feature and maynot be compatible with large industry level code bases.

### Time spent
This program was written over 3 evenings, each 3-6 hours of researching and coding. Most time was spent on researching to setup windows dev environment and learning boost library.
