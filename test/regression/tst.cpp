# include <algorithm>
# include <vector>

int copy1_test(int, char**)
{
  char string[23] = "A string to be copied.";

  char result[23];
  std::copy(string, string + 23, result);
  //  cout << " Src: " << string << "\nDest: " << result << endl;
  return 0;
}


# if 0
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
