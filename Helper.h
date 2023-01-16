#ifndef HELPER_H
#define HELPER_H

#include <random>
#include <iterator>

int gen_rand_num(int min, int max);
enum Type{king, queen, bishop, knight, rook, pawn};
template<typename Iter, typename RandomGenerator>
Iter select_random_element(Iter start, Iter end, RandomGenerator& g){
    std::uniform_int_distribution<> dist(0,distance(start,end)-1);
    advance(start,dist(g));
    return start;
}
template<typename Iter>
Iter select_random_element(Iter start, Iter end){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_random_element(start,end,gen);
}
#endif 