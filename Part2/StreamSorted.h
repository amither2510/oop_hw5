//
// Created by Yahav Rashuk on 27/06/2020.
//

#ifndef OOP_HW5__STREAMSORTED_H
#define OOP_HW5__STREAMSORTED_H

#include "Stream.h"

template <typename T> class StreamSorted : public T{
    T& old_stream;
public:
    StreamSorted(T& old_stream) : old_stream(old_stream){}
    StreamSorted(){}
    virtual ~StreamSorted(){}
    T& getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5__STREAMSORTED_H
