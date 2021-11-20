#include<substd/vec.hpp>

int main(){
    ss::vec3<int> v1 = 1;
    ss::vec3i v2 = ss::vec3i::Unit<1>();

    ss::vec3<int> v3 = v1.Sum(v2);

    ss::vec3f v4 = 2.1f;

    std::cout<<v3;

    return 0;
}