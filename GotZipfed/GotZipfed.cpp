// GotZipfed.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Zipf.h"
#include <iterator>
#include <algorithm>

#include <boost/lambda/lambda.hpp>


int main()
{
    

    Zipf zipf("Pride and Prejudice Short.txt");
    std::multimap<int, std::string>* map = zipf.get_map();
    std::pair<int, std::string> top_word(0, "test");
    for (std::multimap<int, std::string > ::iterator iter = map->begin(); iter != map->end(); ++iter) {
        std::cout << iter->second << ": " << iter->first << std::endl;
        if (iter->first > top_word.first) {
            top_word.first = iter->first;
            top_word.second = iter->second;
        }
    }

    std::cout << "The most common word is '" << top_word.first << "' with " << top_word.second << " occurrences." << std::endl;

    /*
    std::cout << "Test" << std::endl;
    const char* c = "test";
    std::cout << c[1] << std::endl;

    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " ");
 */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
