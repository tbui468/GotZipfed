// GotZipfed.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
Features to add
*************
Refactor graphing code and put into function (inside GotZipfed.cpp file)
Call graphing function three times on Pride and Prejudice, Moby Dick and Edgar Allan Poe texts
Each graph can be distinguished by different color
Graph the ideal Zipf curve to compare
Have the graph function include an optional logarithmic version
*/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <boost/lambda/lambda.hpp> //not used.  Just testing integration of boost library
#include "SDL.h"
#include "Zipf.h"
#include "Screen.h"

void plot(const std::string& title, Screen& screen) {
    Zipf zipf(title);
    std::multimap<int, std::string>* map = zipf.get_map();

    int count = 0;
    int unique_words = map->size() / 32;
    int max_words = (--map->end())->first;
    int x_start = 50;
    int y_start = 550;
    for (std::multimap<int, std::string > ::iterator iter = map->end(); iter != map->begin(); --iter) {
        if (iter == map->end()) iter--;
        //std::cout << count << ". " << iter->second << ": " << iter->first << std::endl;
        ++count;

        //if (count > 30) break;
        double x_shift = ((double)count / unique_words) * 700;
        double y_shift = -((double)iter->first / max_words) * 500;
        screen.draw_pixel(x_start + 1 + x_shift, y_start +y_shift);
        screen.draw_pixel(x_start + 1 + x_shift+1, y_start + y_shift);
        screen.draw_pixel(x_start + 1 + x_shift, y_start + y_shift+1);
        screen.draw_pixel(x_start + 2 + x_shift, y_start + y_shift+1);
        if (count > unique_words) break;
    }

    std::cout << "number of different words: " << unique_words << std::endl;
}


int main(int argc, char* args[])
{

    Screen screen;
    screen.init();

    screen.set_color(255, 100, 100);
    plot("Moby Dick.txt", screen);
    screen.set_color(0, 255, 0);
    plot("Pride and Prejudice.txt", screen);
    screen.set_color(100, 100, 255);
    plot("Crime and Punishment.txt", screen);

    screen.set_color(255, 255, 255);
    screen.draw_line(50, 50, 50, 550);
    screen.draw_line(50, 550, 750, 550);
    screen.update();

    while (screen.process_events()) {

    }

    screen.close();

    return 0;

    /* TESTING BOOST LIBRARY INTEGRATION
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
