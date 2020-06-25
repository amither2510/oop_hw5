#ifndef __MATRIX_H
#define __MATRIX_H

#include "Transpose.h"


/*
template<int N, int M, typename T>
struct MatrixGet {
	typedef typename ListGet<M, typename ListGet<N, T>::value>::value value;
};


template<int N, int M, typename T, typename L>
struct MatrixSet {
	typedef typename ListGet<N, L>::value listA;
	typedef typename ListSet<M, T, listA>::list updated;
	typedef typename ListSet<N, updated, L>::list list;
};

template<int N, typename L1, typename L2>
struct ListSum {};

template<int N, typename T1, typename... TT1, typename T2, typename... TT2>
struct ListSum<N, List<T1, TT1...>, List<T2, TT2...>> {
	static constexpr  int sum = T1::value*T2::value + ListSum<N-1,List<TT1...>,List<TT2...>>::sum;
};

template<typename T1, typename... TT1, typename T2, typename... TT2>
struct ListSum<0, List<T1, TT1...>, List<T2, TT2...>> {
	static constexpr int sum = T1::value*T2::value;
};
template<int N>
struct N_List {
	typedef typename PrependList<Int<0>,typename N_List<N-1>::list>::list list;
};

template<>
struct N_List<0> {
	typedef List<> list;
};

template<int N, int M>
struct NxM_Matrix {
	typedef typename PrependList<typename N_List<M>::list, typename NxM_Matrix<N-1,M>::matrix>::list matrix;
};

template<int M>
struct NxM_Matrix<0,M> {
	typedef List<> matrix;
};


template<int N, int M, typename L1, typename L2>
struct MultiplyAux {
	typedef typename MatrixSet<N-1,M-1,
			Int<ListSum<ListGet<N-1, L1>::value::size - 1,
					typename ListGet<N-1,L1>::value,
					typename ListGet<M-1, L2>::value>::sum>,
			typename MultiplyAux<N, M-1,L1,L2>::result>::list result;
};

template<int N, typename L1, typename L2>
struct MultiplyAux<N,0,L1,L2> {
	typedef typename MultiplyAux<N-1, L2::size, L1, L2>::result result;
};

template<typename L1, typename L2>
struct MultiplyAux<1,0,L1,L2> {
	typedef typename NxM_Matrix<L1::size, L2::size>::matrix result;
};

template<typename L1, typename L2>
struct Multiply {
	typedef typename Transpose<L2>::matrix transposed;
	typedef typename Transpose<L1>::matrix size_check;
	static_assert(size_check::size == L2::size, "matrix multiplication is undefined");
	typedef typename MultiplyAux<L1::size, transposed::size, L1, transposed>::result result;

};



*/


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
//-------------Add-------------


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
		 typename RowMultiply<List<L1...>,List<TT...>>::result>::list result;
};
template <typename... L1,typename L2>
struct RowMultiply<List<L1...>,List<List<L2>>>{
	typedef  List<Int<SumList< typename ListMultiply<List<L1...>,List<L2>>::result>::value>> result;
};

//-------------InitMultiply-------------
template<typename M1, typename M2>
struct InitMultiply{};
template<typename L1,typename... LL1, typename M2>
struct InitMultiply<List<L1,LL1...>,M2> {
	typedef typename PrependList <typename RowMultiply<L1,M2>::result,
			typename InitMultiply<<List<LL1...>,M2>::result>::list result;
};

template<typename L1,typename M2>
struct InitMultiply<List<List<L1>>,M2> {
	typedef  List<typename RowMultiply<List<L1>,M2>::result> result;
};



//-------------Multiply-------------
template<typename M1, typename M2>
struct Multiply{
	static_assert(M1::size == Transpose<M2>::matrix::size, "matrix multiplication is undefined");
	static_assert(Transpose<M1>::matrix::size == M2::size, "matrix multiplication is undefined");
	//typedef typename Transpose< M2>::matrix matrix2;
	typedef typename InitMultiply<M1,typename Transpose< M2>::matrix>::result result;

};


#endif // __MATRIX_H

