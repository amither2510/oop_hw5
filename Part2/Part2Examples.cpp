#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <numeric>
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
    Stream<int>::of(vector)
            .map<Cell<int>>([](const int* a) { return new Cell<int>(*a); }).forEach(&Cell<int>::print);

//    auto num = Stream<int>::of(vector).distinct().collect<std::vector<int*>>();
    //std::cout<<"the number is  --> "<< num <<std::endl;

    /*
    std::vector<std::string*> vector1(vector.size());
    auto m=std::to_string(1);
    std::cout<< Stream<int>::of(vector).filter([](const int* val) { return *val != 2; } ).count() << std::endl;
    auto transform = [](const int* a)->std::string*{ return new std::string(boom(*a));};
    auto resize_vec = std::transform(vector.begin(),vector.end(),vector1.begin(),transform);
    for(auto res : vector1){
        std::cout<<*res<<std::endl;
    }
    std::cout<<"end"<<std::endl;
    Stream<int>::of(vector).map<Cell<int>>([](const int* a) { return new Cell<int>(*a); });
    //assert(Stream<int>::of(vector).filter([](const int* val) { return *val != 2; } ).count() == 8);
    //assert(Stream<int>::of(vector).distinct().count() == 9);

    //std::vector<int> other = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   // assert(compareValues(Stream<int>::of(vector).distinct().sorted().collect<std::vector<int*>>(), other));

   // assert(Stream<int>::of(vector).map<Cell<int>>([](const int* a) { return new Cell<int>(*a); }).distinct().count() == 9);

  //  int initial = 0;
   // assert(*Stream<int>::of(vector).reduce(&initial, [](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; }) == 47);


/*
    std::vector<int> a = {20,10, 4,-4,-10};
    std::vector<int> b (a.size());
    auto ti = std::copy_if(a.begin(),a.end(),b.begin(),[](int j){ return !(j<0);});
    b.resize(std::distance(b.begin(),ti));
    std::cout<<"b contains:";
    for (int& x:b) std::cout<<" "<<x;

    std::cout<<b.size() <<"\n";
    */
    return 0;
}

