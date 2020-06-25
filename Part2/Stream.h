//
// Created by Amit on 6/24/2020.
//

#ifndef OOP_HW5_STREAM_H
#define OOP_HW5_STREAM_H

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>

template <typename T>
class Stream{
private:
    std::function<std::vector<T*>()> block;
    template <typename N>
    void initFunction(N& m){
        std::vector<T*> vec;
        block=[vec,m](){
            std::copy(m.begin(),m.end(),vec);
        };
    }
    void setFunction(std::function<std::vector<T*>()> block){
        this->block = block;
    }
    std::function<std::vector<T*>()>& getFunctions(){
        return block;
    }
public:
    template <typename N>
    Stream<T> static of(N& container){
        auto stream = new Stream(container);
        return stream;
    }

    Stream(){};

    template <class N>
    Stream(N& m){
     //   std::vector<T*> vec;
     //   auto first = m.begin();
     //   auto end = m.end();
        block=[m]() -> std::vector<T*>{

            return m;
        };
    };

    Stream<T> filter(std::function<bool(const T*)> predicate){
        Stream<T>* stream = new Stream();
        auto new_block = [predicate,this]{
            auto vec = getFunctions()();
            std::copy_if (vec.begin(), vec.end(), std::back_inserter(vec), [predicate](const T* t){return predicate(t);});
        };
       // stream->setFunction(new_block);
        return *stream;
    }

    int count(){
        return this->block().size();
    }
};














#endif //OOP_HW5_STREAM_H
