//
// Created by Amit on 6/27/2020.
//

#ifndef OOP_HW5_STREAMMAP_H
#define OOP_HW5_STREAMMAP_H

#include "Stream.h"

template <typename R,typename T> class StreamMap : public Stream<R>{
    Stream<T> old_stream;
public:
    StreamMap(Stream<T>& t):old_stream(t){};
    StreamMap(){};
    virtual ~StreamMap(){};
    Stream<T>& getOldStream(){
        return old_stream;
    }

};


#endif //OOP_HW5_STREAMMAP_H
