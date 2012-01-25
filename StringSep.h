#ifndef _STRINGSEP_H_
#define _STRINGSEP_H_

#include <vector>
#include <string>

void SplitString(std::string str, std::string separator, std::vector<std::string>* results){
    int found = 0;

    found = str.find_first_of(separator);

    while(found != -1){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}

#endif // _STRINGSEP_H_
