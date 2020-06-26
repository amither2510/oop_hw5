//
// Created by Amit on 6/24/2020.
//

#ifndef OOP_HW5_STREAM_H
#define OOP_HW5_STREAM_H

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>

template <typename M>
class Stream{
private:
    std::function<std::vector<Stream<M>*>()> block;
    template <Object T>
    struct collection{
        constexpr static T result = std::copy(T);
    };

public:

    Stream<M> static of(M& buffer){
        collection<buffer>::result;
    }




};














#endif //OOP_HW5_STREAM_H
