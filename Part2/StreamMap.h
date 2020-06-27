//
// Created by Amit on 6/27/2020.
//

#ifndef OOP_HW5_STREAMMAP_H
#define OOP_HW5_STREAMMAP_H

#include "Stream.h"
template <typename R,typename T> class StreamMap : public R {
    T old_stream;
public:
    StreamMap(const T old_stream) : old_stream(old_stream){}
    StreamMap(){}
    virtual ~StreamMap(){}
    T& getOldStream(){
        return old_stream;
    }

};
#endif //OOP_HW5_STREAMMAP_H
