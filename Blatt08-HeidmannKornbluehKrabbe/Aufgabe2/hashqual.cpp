#include "hashqual-functions.h"
#include "tokenizer.hpp"
#include <iostream>
#include <set>
#include <string>

typedef std::set<std::string> str_set;

float hashqual(str_set words, Hashfunction hash_func)
{
    for(str_set::iterator it = words.begin(); it != words.end(); it++)
    {
	std::cout << *it << hash_func.func((*it).c_str()) << "\n";
    }
    return -1.0;
}

void tokenhandler(const char *word, void *data)
{
    static_cast<str_set*>(data)->insert(word);
    // ((str_set)data).insert(word);
}

int main (void)
{
    unsigned int num = hashfunction_number();
    unsigned int i;
    str_set words;
    
    tokenizer(tokenhandler, &words);
    for(i = 0; i < num; i++)
    {
	std::cout << hashqual(words, *hashfunction_get(i)) << "\n";
    }
    return 0;
}
