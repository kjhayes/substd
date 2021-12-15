#include "substd/vec.hpp"

int main(int argc, const char** argv){
    ss::vec<float,2> v2f = {1.0f, 2.0f};
    if(v2f[0] != 2.0f){return 1;}
    if(v2f[1] != 2.0f){return 2;}
}