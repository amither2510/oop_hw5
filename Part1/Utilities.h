#ifndef __UTILITIES_H
#define __UTILITIES_H
//============================List============================
template<typename... T>
struct List {
	constexpr static int size = 0;
};

template <typename T, typename... TT>
struct List<T, TT...> {
	typedef T head;
	typedef List<TT...> next;
	constexpr static int size = sizeof...(TT)+1; 
};

//______________PrependList_______________ 
template <typename H, typename L>
struct PrependList{};

template <typename H, typename... TT>
struct PrependList<H,List<TT...>> {
	typedef List<H,TT...> list;
};

//_________________ListGet_________________
template <int N, typename L>
struct ListGet{};

template <int N , typename T, typename... TT>
struct ListGet<N, List<T,TT...>> {
	typedef typename ListGet<N-1,List<TT...>>::value value;
};

template <typename T, typename... TT>
struct ListGet<0, List<T,TT...>> {
	typedef T value;
};

//_________________ListSet_________________
template <int N, typename V, typename L>
struct ListSet{};

template <int N, typename V, typename T, typename... TT>
struct ListSet <N, V, List<T,TT...>> {
	typedef typename PrependList<T, typename ListSet<N-1,V,List<TT...>>::list>::list list;
};

template< typename V, typename T, typename... TT>
struct ListSet <0,V, List<T,TT...>> {
	typedef  List<V,TT...> list;
};

//============================Int============================

template <int N>
struct Int{
	constexpr static int value = N;
};

#endif // __UTILITIES_H