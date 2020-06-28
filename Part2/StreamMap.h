//
// Created by Amit on 6/27/2020.
//

#ifndef OOP_HW5_STREAMMAP_H
#define OOP_HW5_STREAMMAP_H

#include "Stream.h"
template <typename R,typename T> class StreamMap : public R {
    T* old_stream;
public:
    StreamMap(T* old_stream) {
        this->old_stream= new T(*old_stream);

    }
    StreamMap(){}
    virtual ~StreamMap(){
        delete(old_stream);
    }
    T* getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5_STREAMMAP_H
