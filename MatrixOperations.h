#ifndef __MATRIX_H
#define __MATRIX_H

#include "Transpose.h"

//============================Matrix============================
//------------ListAdd------------
template<typename L1, typename L2>
struct ListAdd{};

template<typename T1,typename... TT1,typename T2,typename... TT2>
struct ListAdd<List<T1,TT1...>,List<T2,TT2...>> {
	typedef typename PrependList <Int<T1::value + T2::value>, typename ListAdd<TT1...,TT2...>::result>::list result;
};
template <typename N1,typename N2>
struct ListAdd<List<N1>,List<N2>>{
	typedef  List<Int<N1::value + N2::value>> result;
};
//-------------Add-------------
template<typename M1, typename M2>
struct Add{};

template<typename L1,typename... LL1, typename L2, typename... LL2>
struct Add<List<L1,LL1...>,List<L2,LL2...>> {
	typedef typename PrependList <typename ListAdd<L1,L2>::result, typename Add<List<LL1...>,List<LL2...>>::result>::list result;
};

template<typename L1,typename L2>
struct Add<List<L1>,List<L2>> {
	typedef  List<typename ListAdd<L1,L2>::result> result;
};



//-------------SumList-------------
template<typename L>
struct SumList{};

template<typename T,typename... TT>
struct SumList<List<T,TT...>>{
	 constexpr static int result = T::value + SumList<List<TT...>>::value; 
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
	typedef typename PrependList <Int<T1::value * T2::value>, typename ListMultiply<TT1...,TT2...>::result>::list result;
};
template <typename N1,typename N2>
struct ListMultiply<List<N1>,List<N2>>{
	typedef  List<Int<N1::value * N2::value>> result;
};

//------------RowMultiply------------
template<typename L1, typename M >
struct RowMultiply{};

template<typename... L1,typename T,typename... TT>
struct RowMultiply<List<L1...>,List<List<T>,TT...>> {
	typedef typename PrependList <  Int<SumList< typename ListMultiply<List<L1...>,List<T>>::result>::value>,
		 typename RowMultiply<List<L1...>,TT...>::result>::list result;
};
template <typename... L1,typename L2>
struct RowMultiply<List<L1...>,List<L2>>{
	typedef  List<Int<SumList< typename ListMultiply<List<L1...>,L2>::result>::value>> result;
};




//-------------Multiply-------------
template<typename M1, typename M2>
struct Multiply{
	static_assert(M1::size == Transpose<M2>::matrix::size, "matrix multiplication is undefined");
	static_assert(Transpose<M1>::matrix::size == M2::size, "matrix multiplication is undefined");
	typedef typename Transpose< M2>::matrix matrix2;
	typedef typename InitMultiply<M1,matrix2>::result result; 

};


#endif // __MATRIX_H

