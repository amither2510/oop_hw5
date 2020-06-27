//
// Created by Amit on 6/24/2020.
//

#ifndef OOP_HW5_STREAM_H
#define OOP_HW5_STREAM_H

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include "StreamFilter.h"
#include "StreamMap.h"
#include "StreamDistinct.h"
#include "StreamSorted.h"
#define UNIQUE_COMPRATOR [](const int* val,const int* val1)->bool { return *val == *val1; }
#define SORT_COMPRATOR   [](const int* val,const int* val1)->bool { return *val < *val1; }

template <typename T>
class Stream{
protected:



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
    std::function<std::vector<T*>()> block;
    template <template<typename... Y> class N>
    Stream<T> static of(N<T*>& container){
        auto stream = new Stream(container);
        return *stream;
    };

    Stream(){};
    /*
    Stream(Stream<T>& s){
        this->block=s.block;
    };*/


    template <template<typename... Y> class N>
    Stream(N<T*>& m){
        initFunction(m);
    };

    Stream<T> filter(std::function<bool(const T*)> predicate){
        StreamFilter<Stream<T>>* stream = new StreamFilter<Stream<T>>(*this);

        stream->block = [stream,predicate]()-> std::vector<T*> {
            auto vec = stream->getOldStream().getFunctions()();
            std::vector<T*> return_vec(vec.size());
            auto resize_vec = std::copy_if(vec.begin(),vec.end(),return_vec.begin(),predicate);
            return_vec.resize(std::distance(return_vec.begin(),resize_vec));
            return return_vec;
        };
        return *stream;
    }

    template <typename R>
    Stream<R> map(std::function<R*(const T*)> transform){
        StreamMap<Stream<R>,Stream<T>>* stream = new StreamMap<Stream<R>,Stream<T>>(*this);
        stream->block=[stream,transform]()-> std::vector<R*> {
            auto vec = stream->getOldStream().getFunctions()();
            std::vector<R*> return_vec(vec.size());
            auto resize_vec = std::transform(vec.begin(),vec.end(),return_vec.begin(),transform);
            return return_vec;
        };
        return *stream;
    }

    Stream<T> distinct(std::function<bool(const T*,const T*)>  compartor = UNIQUE_COMPRATOR){
        StreamDistinct<Stream<T>>* stream = new StreamDistinct<Stream<T>>(*this);
        stream->block = [stream,compartor]()-> std::vector<T*> {
            auto vec = stream->getOldStream().getFunctions()();
            auto compartor1 = SORT_COMPRATOR;
            sort( vec.begin(), vec.end(),compartor1 );
            vec.erase( unique( vec.begin(), vec.end(),compartor ), vec.end() );
            return vec;
        };
        return *stream;
    }
    Stream<T> sorted(std::function<bool(const T*,const T*)>  compartor = SORT_COMPRATOR){
        StreamSorted<Stream<T>>* stream = new StreamSorted<Stream<T>>(*this);
        stream->block = [stream,compartor]()-> std::vector<T*> {
            auto vec = stream->getOldStream().getFunctions()();
            auto compartor1 = SORT_COMPRATOR;
            sort( vec.begin(), vec.end(),compartor1 );
            return vec;
        };
        return *stream;
    }
    int count(){
        return this->block().size();
    }

    //template <template<typename... X> class C,typename E>
    template<typename C>
    C collect(){
        auto m=block();
        C vec(m.size());
        std::copy(m.begin(),m.end(),vec.begin());
        return vec;
    }

    template <typename F>
    void forEach(std::function<void (F)> f){
        auto vec = this->block();
        std::for_each(vec.begin(),vec.end(),f);
    }
//    void forEach(std::function<void (const T)> f){
//        auto vec = this->block();
//        std::for_each(vec.begin(),vec.end(),f);
//    }

    virtual ~Stream(){};
};


#endif