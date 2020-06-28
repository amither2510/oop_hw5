//
// Created by Amit on 6/24/2020.
//

#ifndef OOP_HW5_STREAM_H
#define OOP_HW5_STREAM_H

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>
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

    void forEach(std::function<void (T*)> f){
        auto vec = this->block();
        std::for_each(vec.begin(),vec.end(),f);
    }

    T* reduce(T* s, std::function<T*(const T*,const T*)> f){
        auto m = block();
        for(auto it : m){
            *s= *(f(it,s));
        }
        return s;
    }


    T* min(){
        auto m = block();
        return (T*)(*std::min_element(m.begin(),m.end()));
    }

    T* max(){
        auto m = block();
        return (T*)(*std::max_element(m.begin(),m.end()));
    }

    bool anyMatch(std::function<bool(const T*)> p){
        auto m = block();
        return std::any_of(m.begin(),m.end(),p);
    }
    bool allMatch(std::function<bool(const T*)> p){
        auto m = block();
        return std::all_of(m.begin(),m.end(),p);
    }

    T* findFirst(std::function<bool(const T*)> p){
        auto m = block();
        auto result= std::find_if(m.begin(),m.end(),p);
        if(result==m.end()){
            return nullptr;
        }
        return (T*)(*result);

    }

    virtual ~Stream(){};
};


#endif