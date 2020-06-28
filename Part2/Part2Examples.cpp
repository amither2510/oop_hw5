#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <numeric>
#include <map>
#include <algorithm>
#include "Stream.h"
#include <string>
template <typename T>
struct Cell {
    T value;

    Cell(const T value) : value(value) {}

    bool operator==(const Cell<T>& other) const {
        return other.value == value;
    }

    void print() {
        std::cout << "Cell: " << value << std::endl;
    }
};

template <typename T>
bool compareValues(std::vector<T*> vPointer, std::vector<T> v) {
    for(int i = 0 ; i < vPointer.size() ; i++){
        if(*vPointer[i] != v[i]){
            return false;
        }
    }
    return true;
}

std::string boom(int i){
    if(i<4){
        return "a";
    }
    return "b";
}

int main() {

    int array[10] = { 1, 2, 3, 2, 4, 6, 5, 7, 8, 9 };
    std::vector<int*> vector;
    for(int i = 0 ; i < 10 ; i++) vector.push_back(array + i);
        assert(Stream<int>::of(vector).filter([](const int* val) { return *val != 2; } ).count() == 8);
        std::cout<<Stream<int>::of(vector).map<Cell<int>>([](const int* a) { return new Cell<int>(*a); }).count();
        assert(Stream<int>::of(vector).distinct().count() == 9);

    std::vector<int> other = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int initial = 0;
    //std::cout<<*std::accumulate(vector.begin(),vector.end(),&initial,[](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; });
    Stream<int>::of(vector)
            .map<Cell<int>>([](const int* a) { return new Cell<int>(*a); })
            .forEach(&Cell<int>::print);
    int* minimal = Stream<int>::of(vector).min();
    std::cout<<*minimal<<std::endl;
    int* maximal = Stream<int>::of(vector).max();
    std::cout<<*maximal<<std::endl;
    bool result = Stream<int>::of(vector).anyMatch([](const int* a) { return *a == 7; });
    std::cout<<result<<std::endl;
    bool result1 = Stream<int>::of(vector).allMatch([](const int* a) { return *a < 10; });
    std::cout<<result1<<std::endl;
    int* result2 = Stream<int>::of(vector).findFirst([](const int* a) { return *a > 6; });
    if(!result2){
        std::cout<<"null!!"<<std::endl;
    } else {
        std::cout << *result2 << std::endl;
    };
    std::map<char,int*> first;
    std::cout<<"map:"<<std::endl<<std::endl;
    first['a']=array+0;
    first['b']=array+1;
    first['c']=array+2;
    first['d']=array+3;
    for(auto it: first){
        std::cout<<*it.second<<std::endl;
    };
    std::cout<<std::endl;
    std::cout<<Stream<int>::of(first).distinct().count()<<std::endl;


    //assert(compareValues(Stream<int>::of(vector).distinct().sorted().collect<std::vector<int*>>(), other));
//    int initial = 0;
//    int s=*Stream<int>::of(vector).reduce(&initial, [](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; });
//    std::cout<<std::endl<<s<<std::endl;
//    assert(*Stream<int>::of(vector).reduce(&initial, [](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; }) == 47);
//

    return 0;
}

