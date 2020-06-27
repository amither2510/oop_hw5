//
// Created by Yahav Rashuk on 27/06/2020.
//

#ifndef OOP_HW5__STREAMDISTINCT_H
#define OOP_HW5__STREAMDISTINCT_H
#include "Stream.h"

template <typename T> class StreamDistinct : public T{
    T old_stream;
public:
    StreamDistinct(const T old_stream) : old_stream(old_stream){}
    StreamDistinct(){}
    virtual ~StreamDistinct(){}
    T& getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5__STREAMDISTINCT_H
