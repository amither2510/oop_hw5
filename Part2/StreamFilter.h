//
// Created by Amit on 6/27/2020.
//

#ifndef OOP_HW5_STREAMFILTER_H
#define OOP_HW5_STREAMFILTER_H
#include "Stream.h"

template <typename T> class StreamFilter : public Stream<T>{
    Stream<T> old_stream;
public:
    StreamMap(Stream<T>& t):old_stream(t){};
    StreamMap(){};
    virtual ~StreamMap(){};
    Stream<T>& getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5_STREAMFILTER_H
