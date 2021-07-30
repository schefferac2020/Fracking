#include <iostream>
#include <iomanip>
#include "xcode_redirect.hpp"
#include "GenerateFractal.h"

using namespace std;


int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);

    xcode_redirect(argc, argv);

    try {
        GenerateFractal generator;
    }catch( char const * exception){
        cerr << "OOPS YA SCREWED UP!" << endl;
        return 1;
    }
}