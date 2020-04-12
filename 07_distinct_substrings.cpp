#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

void createSubstrsOf(string &str, list<string> &substrs)
{
    size_t length = str.length();

    // I'm ignoring the substring that is the whole string (< length)
    for (size_t subsstrSize = 1; subsstrSize < length; subsstrSize++)
    {
        int numOfSubstrs = length - subsstrSize + 1;

        for (size_t i = 0; i < numOfSubstrs; i++)
        {
            substrs.push_back(str.substr(i, subsstrSize));
        }
    }
}

int countDistinctSubstrsOf(string &str)
{
    int numOfDistinctSubstrs = 0;
    list<string> substrs;
    createSubstrsOf(str, substrs);

    for (auto i = substrs.begin(); i != substrs.end();)
    {
        auto element = *i;
        i = substrs.erase(i);

        if (find(substrs.begin(), substrs.end(), element) == substrs.end())
            numOfDistinctSubstrs++;
        else
        {
            while (*i == element)
                i = substrs.erase(i);

            substrs.remove(element);
        }
    }

    return numOfDistinctSubstrs;
}

int main()
{
    int numOfCases;
    cin >> numOfCases;

    for (size_t i = 0; i < numOfCases; i++)
    {
        string str0, str1;
        cin >> str0 >> str1;
        cout << (countDistinctSubstrsOf(str0) == countDistinctSubstrsOf(str1) ? "s" : "n") << endl;
    }

    return 0;
}
