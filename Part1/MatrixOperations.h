#ifndef __MATRIX_H
#define __MATRIX_H

#include "Transpose.h"

//============================Matrix============================

//------------ListAdd------------
template<typename L1, typename L2>
struct ListAdd{};

template<typename T1,typename... TT1,typename T2,typename... TT2>
struct ListAdd<List<T1,TT1...>,List<T2,TT2...>> {
    typedef typename PrependList <Int<T1::value + T2::value>, typename ListAdd<List<TT1...>,List<TT2...>>::result>::list result;
};

template <typename N1,typename N2>
struct ListAdd<List<N1>,List<N2>>{
    typedef  List<Int<N1::value + N2::value>> result;
};

//-------------InitAdd-------------
template<typename M1, typename M2>
struct InitAdd{};

template<typename L1,typename... LL1, typename L2, typename... LL2>
struct InitAdd<List<L1,LL1...>,List<L2,LL2...>> {
    typedef typename PrependList <typename ListAdd<L1,L2>::result, typename InitAdd<List<LL1...>,List<LL2...>>::result>::list result;
};

template<typename L1,typename L2>
struct InitAdd<List<L1>,List<L2>> {
    typedef  List<typename ListAdd<L1,L2>::result> result;
};

//-------------Add-------------
template<typename M1, typename M2>
struct Add {
    static_assert(M1::size == M2::size, "add matrix is undef");
    typedef typename InitAdd<M1,M2>::result result;


};


//-------------SumList-------------
template<typename L>
struct SumList{};

template<typename T,typename... TT>
struct SumList<List<T,TT...>>{
    constexpr static int result = T::value + SumList<List<TT...>>::result;
};

template<typename T>
struct SumList<List<T>>{
    constexpr static int result = T::value;
};


//------------ListMultiply------------
template<typename L1, typename L2>
struct ListMultiply{};

template<typename T1,typename... TT1,typename T2,typename... TT2>
struct ListMultiply<List<T1,TT1...>,List<T2,TT2...>> {
    typedef typename PrependList <Int<T1::value * T2::value>, typename ListMultiply<List<TT1...>,List<TT2...>>::result>::list result;
};
template <typename N1,typename N2>
struct ListMultiply<List<N1>,List<N2>>{
    typedef  List<Int<N1::value * N2::value>> result;
};

//------------RowMultiply------------
template<typename L1, typename M >
struct RowMultiply{};

template<typename... L1,typename... T,typename... TT>
struct RowMultiply<List<L1...>,List<List<T...>,TT...>> {
    typedef typename PrependList < Int<SumList< typename ListMultiply<List<L1...>,List<T...>>::result>::result>,
            typename RowMultiply<List<L1...>,List<TT...>>::result>::list result;
};

template <typename... L1,typename... L2>
struct RowMultiply<List<L1...>,List<List<L2...>>>{
    typedef  List<Int<SumList< typename ListMultiply<List<L1...>,List<L2...>>::result>::result>> result;
};

//-------------InitMultiply-------------
template<typename M1, typename M2>
struct InitMultiply{};

template<typename... L1,typename... LL1, typename... L2,  typename... LL2>
struct InitMultiply<List<List<L1...>,LL1...>,List<List<L2...>,LL2...>> {
typedef typename PrependList <typename RowMultiply<List<L1...>,List<List<L2...>,LL2...>>::result,
typename InitMultiply<List<LL1...>,List<List<L2...>,LL2...>>::result>::list result;
};

template<typename... L1,typename... LL1, typename... L2>
struct InitMultiply<List<List<L1...>,LL1...>,List<List<L2...>>> {
    typedef typename PrependList <typename RowMultiply<List<L1...>,List<List<L2...>>>::result,
            typename InitMultiply<List<LL1...>,List<List<L2...>>>::result>::list result;
};

template<typename... L1,typename... L2, typename... LL2>
struct InitMultiply<List<List<L1...>>,List<List<L2...>,LL2...>> {
    typedef List<typename RowMultiply<List<L1...>,List<List<L2...>,LL2...>>::result> result;
};

template<typename... L1,typename... L2>
struct InitMultiply<List<List<L1...>>,List<List<L2...>>> {
        typedef List<typename RowMultiply<List<L1...>,List<List<L2...>>>::result> result;
};

//-------------Multiply-------------
template<typename M1, typename M2>
struct Multiply{
    static_assert(M1::size == Transpose<M2>::matrix::size, "matrix multiplication is undefined");
    static_assert(Transpose<M1>::matrix::size == M2::size, "matrix multiplication is undefined");
    typedef typename InitMultiply<M1,typename Transpose<M2>::matrix>::result result;

};


#endif // __MATRIX_H

