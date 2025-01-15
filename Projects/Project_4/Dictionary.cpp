// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <algorithm>
#include <utility>  // for swap
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int  maxBuckets) : m_maxBuckets(maxBuckets) 
    { m_buckets.resize(maxBuckets); }
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    vector<list<string>> m_buckets;
    int m_maxBuckets;
    int hashFunction(string word) const;
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if (!word.empty())
    {
        int bucketIndex = hashFunction(word);
        m_buckets[bucketIndex].push_back(word);
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;
    removeNonLetters(letters); // Modifying the string
    if (letters.empty())
        return;  
    int bucket = hashFunction(letters); // Find the bucket index

    sort(letters.begin(), letters.end());  // Sorting the letters 
    // Get the words in the bucket
    const list<string>& buckets = m_buckets[bucket];
    list<string>::const_iterator end = buckets.end();

    for(list<string>::const_iterator p = buckets.begin(); p != end; p++)
    {
        const string& s = *p;
        string word = s;
        sort(word.begin(), word.end());
        // Check if the sorted word matches
        if (word == letters)
        {
            // Call the callback function
            callback(s);
        }
    }
}

int DictionaryImpl::hashFunction(string word) const
{
    if (word.empty()) return-1;

    string temp = word;

   sort(temp.begin(), temp.end());

   unsigned int hash = 0;

   int size = temp.size();
    for (int i = 0; i < size; i++)
    {
        hash += temp[i];
        hash *= 31;
    }
    return (hash % m_maxBuckets);
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
