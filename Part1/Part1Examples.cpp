#include <iostream>
#include "MatrixOperations.h"

int main() {
    typedef List<Int<1>, Int<2>, Int<3>> list1;
	static_assert(list1::head::value == 1, "Failed"); // = Int<1>
	typedef typename list1::next list1Tail; // = List<Int<2>, Int<3>>
	static_assert(list1::size == 3, "Failed"); // = 3
	static_assert(list1Tail::size == 2, "Failed"); // = 2
	
	typedef List<Int<1>, Int<2>, Int<3>> list2;
	typedef typename PrependList<Int<4>, list2>::list newList2; // = List< Int<4>, Int<1>, Int<2>, Int<3>>
	static_assert(newList2::head::value == 4, "Failed");
	
	typedef List<Int<1>, Int<2>, Int<3>> list3;
	static_assert(ListGet<0, list3>::value::value == 1, "Failed"); // = Int<1>
	static_assert(ListGet<2, list3>::value::value == 3, "Failed"); // = Int<3>
	
	typedef List<
                List< Int<1>, Int<2>, Int<0> >,
                List< Int<0>, Int<1>, Int<0> >,
                List< Int<0>, Int<0>, Int<5> >
            > matrix11;
            
	typedef List<
					List< Int<7>, Int<6>, Int<0> >,
					List< Int<0>, Int<7>, Int<0> >,
					List< Int<8>, Int<0>, Int<3> >
				> matrix21;
				
	typedef typename Add<matrix11, matrix21>::result matrix31; // = List<
															   //			List< Int<8>, Int<8>, Int<0> >,
															   //			List< Int<0>, Int<8>, Int<0> >,
															   //			List< Int<8>, Int<0>, Int<8> >
															   //		 >
	static_assert(matrix31::head::head::value == 8, "Failed");

    constexpr static int sum = SumList<List< Int<1>, Int<2>, Int<10> >>::result;
    static_assert(sum == 13, "sum Failed");

    typedef typename ListMultiply<List<Int<2>>,List< Int<10> > >::result listMul1;
    static_assert(listMul1::head::value == 20, "ListMultiply Failed");

    typedef typename ListMultiply<List< Int<1>, Int<2> >,List< Int<10>, Int<20> >>::result listMul;
    static_assert(listMul::head::value == 10, "ListMultiply Failed");
    static_assert(listMul::next::head::value == 40, "ListMultiply Failed");
    constexpr static int sumAfterMullList = SumList<listMul>::result;
    static_assert(sumAfterMullList == 50, "sumAfterMullList Failed");

    typedef typename RowMultiply<List< Int<100>>,List<List< Int<5> > > >::result rowMul1;
    static_assert(rowMul1::head::value == 500, "RowMultiply Failed");

    typedef typename RowMultiply<List< Int<1>, Int<2> >,List<List< Int<10>,Int<20> >,List< Int<10>, Int<20> > >>::result rowMul;
    static_assert(rowMul::head::value == 50, "RowMultiply Failed");


	typedef List<
                List< Int<1>, Int<2> >,
                List< Int<0>, Int<1> >
            > matrix12;

	typedef List<
					List< Int<0>, Int<7> >,
					List< Int<8>, Int<0> >
				> matrix22;

	typedef typename Multiply<matrix12, matrix22>::result matrix32; // = List<
																    //			List< Int<16>, Int<7> >,
																    //			List< Int<8>, Int<0> >
																    //		  >

	static_assert(matrix32::head::head::value == 16, "Failed");



    std::cout << "Passed" << std::endl;
}