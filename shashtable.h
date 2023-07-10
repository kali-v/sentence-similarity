#include <bitset>
#include <iostream>
#include <vector>

class Dist0HashTable {
  public:
    std::vector<char*> table;
    ulong capacity;

    Dist0HashTable(int capacity);

    int hash(std::string sentence, int cap);
    int insert(char* value);
    char* get(int key);
};

class Dist1HashTable {
  public:
    std::vector<std::vector<std::vector<std::vector<int>>>> table;
    int wcm;
    int ccm;

    Dist1HashTable();

    int insert(std::string value);
};
