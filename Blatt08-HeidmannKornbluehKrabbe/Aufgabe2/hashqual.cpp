#include "hashqual-functions.h"
#include "tokenizer.hpp"
#include <iostream>
#include <iomanip>
#include <set>
#include <string>

typedef std::set<std::string> str_set;
typedef struct {
    float value;
    const char *name;
} result;

result hashqual(str_set words, Hashfunction hash_func)
{
    result out;
    unsigned int temp = 1;
    unsigned int sum = 0;
    unsigned int h = 0;
    unsigned int last;
    std::multiset<unsigned int> hashs;
    str_set::iterator it;
    std::multiset<unsigned int>::iterator et;
    
    for(it = words.begin(); it != words.end(); it++)
    {
	hashs.insert(hash_func.func((*it).c_str()));
    }

    last = *hashs.begin();
    for(et = ++(hashs.begin()); et != hashs.end(); et++)
    {
	if(*et == last)
	{
	    temp++;
	}
	else
	{
	    //std::cout << last << "\n";
	    sum += temp * temp;
	    temp = 1;
	    h++;
	}
	last = *et;
    }
    out.value = (float)sum/(float)h;
    out.name = hash_func.name;
    return out;
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
    result out[num];
    
    tokenizer(tokenhandler, &words);
    std::cout << "# different words in input: " << words.size() << "\n";
    for(i = 0; i < num; i++)
    {
	out[i] = hashqual(words, *hashfunction_get(i));
        
    }
    //sorting is missing here!!!!
    for(i = 0; i < num; i++)
    {
	std::cout << std::fixed << std::setprecision(8) << out[i].name << ": " << out[i].value << "\n";
    }
    return 0;
}
