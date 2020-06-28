//
// Created by Amit on 6/27/2020.
//

#ifndef OOP_HW5_STREAMFILTER_H
#define OOP_HW5_STREAMFILTER_H

#include "Stream.h"



template <typename T> class StreamFilter : public T{
    T* old_stream;
public:
    StreamFilter(T* old_stream){
       this->old_stream= new T(*old_stream);
    }
    StreamFilter(){}
    virtual ~StreamFilter(){
        delete(old_stream);
    }
    T* getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5_STREAMFILTER_H
