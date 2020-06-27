//
// Created by Amit on 6/24/2020.
//

#ifndef OOP_HW5_STREAM_H
#define OOP_HW5_STREAM_H

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include "StreamMap.h"
template <typename T>
class Stream{
protected:
    std::function<std::vector<T*>()> block;


//todo handle memory

    template <template<typename... Y> class N>
    void initFunction(N<T*>& m){
        block=[m]() -> std::vector<T*>{
            std::vector<T*> vec(m.size());
            std::copy(m.begin(),m.end(),vec.begin());
            return vec;
        };
    }

    std::function<std::vector<T*>()>& getFunctions(){
        return block;
    }
public:
    template <template<typename... Y> class N>
    Stream<T> static of(N<T*>& container){
        auto stream = new Stream(container);
        return *stream;
    }

    Stream(){};


    template <template<typename... Y> class N>
    Stream(N<T*>& m){
        initFunction(m);
    };

    Stream<T> filter(std::function<bool(const T*)> predicate){
        StreamFilter<T>* stream = new StreamFilter(*this);
        stream->block = [stream,predicate,this]()-> std::vector<T*> {
            auto vec = stream->getOldStream()->getFunctions()();
            std::vector<T*> return_vec(vec.size());
            auto resize_vec = std::copy_if(vec.begin(),vec.end(),return_vec.begin(),predicate);
            return_vec.resize(std::distance(return_vec.begin(),resize_vec));
            return return_vec;
        };
        return *stream;
    }

    template <typename R>
     Stream<R> map(std::function<R*(const T*)> transform){
        StreamMap<R> stream = StreamMap(*this);

        stream->block = [stream,transform,this]()-> std::vector<T*> {
            auto vec = stream->;
            std::vector<R*> return_vec(vec.size());
            auto resize_vec = std::transform(vec.begin(),vec.end(),return_vec.begin(),transform);
            return return_vec;
        };
        return *stream;
    }

    int count(){
        return this->block().size();
    }
    virtual ~Stream(){};
};

#endif