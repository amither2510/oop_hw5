#include <iostream>
#include "Utilities.h"

#define check 2

template <int N>
struct Int {
	constexpr static int val = N;
};

using namespace std;

void testList() {
	typedef List<Int<1>, Int<2>, Int<3>> list;
	static_assert(list::size == 3, "Once Upon a time there was a noob who thouht he can program...");
	static_assert(list::head::val == 1, "bad");
	static_assert(list::next::head::val == 2, "bad");
	static_assert(list::next::next::head::val == 3, "bad");
	
	// if you want to check on runtime (though I see no need...)
	/* int flag = 0;
	 if (list::head::val != 1) flag++;
	 if (list::next::head::val != 2) flag++;
	 if (list::next::next::head::val != 3) flag++;
	 if (flag != 0) cout << "You have a problem" << endl;
	else cout << "success" << endl;*/
}

void testPrependList() {
	typedef List<Int<1>, Int<2>, Int<3>> list;
	typedef typename PrependList<Int<4>, list>::list newList; // = List< Int<4>, Int<1>, Int<2>, Int<3>>
	static_assert(newList::size == 4, "Your programing sucks. Maybe you should think about a career in driving autonimic garbage trucks");
	static_assert(newList::head::val == 4, "bad");
	static_assert(newList::next::head::val == 1, "bad");
	static_assert(newList::next::next::head::val == 2, "bad");
	static_assert(newList::next::next::next::head::val == 3, "bad");
	
	/*
	int flag = 0;
	if (newList::head::val != 4) flag++;
	if (newList::next::head::val != 1) flag++;
	if (newList::next::next::head::val != 2) flag++;
	if (newList::next::next::next::head::val != 3) flag++;
	if (flag != 0) cout << "You have a problem" << endl;
	else cout << "success" << endl;*/
}

void testGet() {
	int flag = 0;
	typedef List< Int<1>, Int<2>, Int<3> > list;
	typedef typename ListGet<0, list>::value v1;
	typedef typename ListGet<1, list>::value v2;
	typedef typename ListGet<2, list>::value v3;
	static_assert(list::size == 3, "seriouslt?! againg?!");
	static_assert(v1::val == 1, "My grandma cant use a smart phone and know how to write tamplates better than you!");
	static_assert(v2::val == 2, "bad");
	static_assert(v3::val == 3, "bad");
	/*
	if (v1::val != 1) flag++;
	if (v2::val != 2) flag++;
	if (v3::val != 3) flag++;
	if (flag != 0) cout << "You have a problem" << endl;
	else cout << "success" << endl;*/
}

void testSet() {
	typedef List<Int<1>, Int<2>, Int<3>> list;
	typedef List<Int<1>, Int<2>, Int<3>> list2;
	typedef List<Int<1>, Int<2>, Int<3>> list3;

	typedef typename ListSet<0, Int<5>, list>::list listA; // = List<Int<5>, Int<2>, Int<3>>
	static_assert(listA::size == 3, "The ListSet is actualy a hard function... took me time to fix it to");
	static_assert(listA::head::val == 5, "But it does not mean your of the hook with insults");
	static_assert(listA::next::head::val == 2, "bad");
	static_assert(listA::next::next::head::val == 3, "bad");
	
	// int flag = 0;
	/*if (listA::head::val != 5) flag++;
	if (listA::next::head::val != 2) flag++;
	if (listA::next::next::head::val != 3) flag++;
	if (flag != 0) cout << "You have a problem" << endl;
	else cout << "success" << endl;*/
	
	typedef typename ListSet<2, Int<7>, list2>::list listB; // = List<Int<1>, Int<2>, Int<7>>
	static_assert(listB::size == 3, "bad");
	static_assert(listB::head::val == 1, "Well. maybe you suck at OOP but it is not imporatnt for life");
	static_assert(listB::next::head::val == 2, "Well. maybe you suck at OOP but it is not imporatnt for life");
	static_assert(listB::next::next::head::val == 7, "Well. maybe you suck at OOP but it is not imporatnt for life");
	
	/*if (listB::head::val != 1) flag++;
	if (listB::next::head::val != 2) flag++;
	if (listB::next::next::head::val != 7) flag++;
	if (flag != 0) cout << "You have a problem" << endl;
	else cout << "success" << endl;*/
	
	typedef typename ListSet<1, Int<42>, list3>::list listC; // = List<Int<1>, Int<42>, Int<3>>
	static_assert(listC::size == 3, "bad");
	static_assert(listC::head::val == 1, "Did you know? the word noob comes from the root 'noob', wich means noob");
	static_assert(listC::next::head::val == 42, "Did you know? the word noob comes from the root 'noob', wich means noob");
	static_assert(listC::next::next::head::val == 3, "Did you know? the word noob comes from the root 'noob', wich means noob");
	
	/*	if (listC::head::val != 1) flag++;
	if (listC::next::head::val != 42) flag++;
	if (listC::next::next::head::val != 3) flag++;
	if (flag != 0) cout << "You have a problem" << endl;
	else cout << "success" << endl; */
}

void veryHardTest() {
	static_assert(1 == check, "If you failed this test, you should think of rewriting your program again..."); 
	// Just kidding, erase this assert
}

int main() { 
	/*
		This test is for the Utilities.h library in OOP hw5 part1. For anny questions you can adrres me at my twitter an linkdin 
		profiles who do not exist, or at my call of duty user VIP_CS_TECH.
		Enjoy debugging!
	*/
	testList();
	testPrependList();
	testGet();
	testSet();
	
}