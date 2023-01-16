#include "Helper.h"
using namespace std;

int gen_rand_num(int min, int max){
    random_device rand;
    mt19937 eng(rand());
    std::uniform_int_distribution<> distr(min,max);
    return distr(eng);
}
