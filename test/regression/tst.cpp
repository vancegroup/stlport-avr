#include <string>
#include <iostream>			// regular I/O streams
#include <fstream>			// file streams

using namespace std;

int main()
{
    string fname("abc.def");
    fstream cfile;
    fstream dfile;

    cout << "Open " << fname << " for read" << endl;
    cfile.open(fname.c_str(), ios::in);
    if (cfile) {
	cout << fname << " exists" << endl;
	cfile.close();
    }
    cout << "Open " << fname << " for write" << endl;
    cfile.open(fname.c_str(), ios::out);
    if (!cfile) {
	cout << "Can't open " << fname << " for output" << endl;
	exit(1);
    }

    cout << fname << " has been opened for writing" << endl;
    cfile.close();
}

# if 0
# include <algorithm>
# include <vector>

# include <iostream>
# include <limits>
# include <stdio.h>

    #include <vector>

    int main()
    {
	vector<int> myVector;

	// const_iterator
	for (vector<int>::const_iterator i = myVector.begin();
	     i != myVector.end(); ++i) {
	}

	// reverse_iterator
	for (vector<int>::reverse_iterator i = myVector.rbegin();
	     i != myVector.rend(); ++i) {
	}

	// const_reverse_iterator
	//
	// no match for `reverse_iterator<const int *> & != reverse_iterator<int *>'
	for (vector<int>::const_reverse_iterator i = myVector.rbegin();
	     i != ((const vector<int>&)myVector).rend(); ++i) {
	}
    }

int main()
{
  long a = 17;
  //  while (cin >> a) 
  printf("%f %f\n", (double)(100.0/0.0), numeric_limits<double>::quiet_NaN());
}






int copy1_test(int, char**)
{
  char string[23] = "A string to be copied.";

  char result[23];
  std::copy(string, string + 23, result);
  //  cout << " Src: " << string << "\nDest: " << result << endl;
  return 0;
}

# include <hash_map>
#include <iostream>

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
    {
    return strcmp(s1, s2) == 0;
    }
};

int main()
{
  std::hash_map<const char*, int, std::hash<const char*>, eqstr> months;
  
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  
  std::cout << "february -> " << months["february"] << endl;
  std::cout << "april     -> " << months["april"] << endl;
  std::cout << "june      -> " << months["june"] << endl;
  std::cout << "december  -> " << months["december"] << endl;
}

# endif
