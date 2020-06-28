//
// Created by Yahav Rashuk on 27/06/2020.
//

#ifndef OOP_HW5__STREAMSORTED_H
#define OOP_HW5__STREAMSORTED_H

#include "Stream.h"

template <typename T> class StreamSorted : public T{
    T* old_stream;
public:
    StreamSorted(T* old_stream){
        this->old_stream= new T(*old_stream);
    }
    StreamSorted(){}
    virtual ~StreamSorted(){
        delete(old_stream);
    }
    T* getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5__STREAMSORTED_H
