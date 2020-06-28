#include <iostream>
#include <vector>
#include <cassert>
#include "Stream.h"
#include <list>
#include <map>
#include <string>

template <typename T>
struct Cell {
    T value;

    explicit Cell(const T value) : value(value) {}

    bool operator==(const Cell<T>& other) const {
        return other.value == value;
    }


};

template <typename T>
bool compareValues(std::vector<T*> vPointer, std::vector<T> v) {
    for(int i = 0 ; i < vPointer.size() ; i++){
        if(*vPointer[i] != v[i]){
            return false;
        }
    }
    return true;
}

template <typename Container1 , typename Container2>
bool Compare(Container1& c1, Container2 c2) {
    auto  it1 = c1.begin();
    auto  it2 = c2.begin();
    for (; it1 != c1.end(); it1++,it2++){
        if(**it1!= **it2){
            return false;
        }
    }
    return true;
}


void TestOf(  std::vector<std::string*> empty_vec ,std::map<int,int*> empty_map ,
              std::map<int,int*> map1 ,std::map<int,std::string*> map_strings ,  std::vector<std::string*> vec_strings){

    std::list<std::string*> lst = Stream<std::string>::of(empty_vec).collect<std::list<std::string*>>();
    assert(lst.empty());
    Stream<int>::of(empty_map);
    Stream<int>::of(map1);
    Stream<std::string>::of( map_strings);
    Stream<std::string>::of( vec_strings);
    lst = Stream<std::string>::of(vec_strings).collect<std::list<std::string*>>();
    assert(lst.size() == 3);
    Compare(vec_strings,lst);
}


void TestFilter(std::vector<std::string*>& empty_vec , std::map<int,int*>& empty_map  ,  std::map<int,std::string*>& map_strings,
                std::vector<std::string*>& vec_strings, std::vector<std::string*> vec_strings_b_c ,std::vector<std::string*> vec_strings_c
        ,std::vector<std::string*> vec_strings_a_a_a){

    assert(Stream<std::string>::of(empty_vec).filter([](const std::string* str) { return *str != "d"; } )
                   .collect<std::list<std::string*>>().empty() )  ;

//    Stream<int>::of(empty_map).filter([](const int* val) { return *val != 2; } );
    assert(Compare (vec_strings,
                    Stream<std::string>::of(vec_strings).filter([](const std::string* str) { return *str != "d"; } )
                            .collect<std::list<std::string*>>()  ) )  ;

    std::list<std::string*> lst ( Stream<std::string>::of(vec_strings).filter([](const std::string* str) { return *str != "a"; } )
                                .collect<std::list<std::string*>>() ) ;
    assert(Compare (vec_strings_b_c, lst)  );

    std::list<std::string*> lst_c ( Stream<std::string>::of(lst).filter([](const std::string* str) { return *str != "b"; } )
                                  .collect<std::list<std::string*>>() ) ;
    assert(Compare (vec_strings_c, lst_c)  );

    assert(Stream<std::string>::of(lst_c).filter([](const std::string* str) { return *str != "c"; } )
                   .collect<std::list<std::string*>>().empty() )  ;
    assert(Stream<std::string>::of(vec_strings_a_a_a).filter([](const std::string* str) { return *str != "a"; } )
                   .collect<std::list<std::string*>>().empty() )  ;

    //check lazy,should work because the lazy eval.
    int* a = nullptr;
  //  Stream<std::string>::of(vec_strings_a_a_a).filter([&a](const std::string* str) { *a = 3; return *str != "a"; } )  ;
    assert(Compare(vec_strings_c, Stream<std::string>::of(vec_strings).filter([](const std::string* str) { return *str != "a"; } )
            .filter([](const std::string* str) { return *str != "b"; } ).collect<std::list<std::string*>>() ) ) ;

 }


void TestMap(std::vector<std::string*>& empty_vec , std::map<int,int*>& empty_map  ,  std::map<int,std::string*>& map_strings, std::vector<std::string*>& vec_strings, std::vector<std::string*>& vec_strings_b_c
        ,std::vector<std::string*> vec_strings_a_a_a,std::vector<int*> vec_int_0_1_2, int* x){


    Stream<std::string>::of(empty_vec).map<int>([x](const std::string* a) {  return x; });
    Stream<int>::of(empty_map).map<int>([x](const int* a) { return x; });
    int array[3]={0,1,2};
    int i = -1;
    std::list<int*> lst = Stream<std::string>::of(vec_strings).map<int>([&i,&array](const std::string* a) {i++;return (int*)(array+i); })
            .collect< std::list<int*> >();
    assert (Compare(vec_int_0_1_2 ,lst  ));

    //check lazy before map
    int* a = nullptr;
    Stream<std::string>::of(vec_strings_a_a_a).filter([&a](const std::string* str) { *a = 3; return *str != "a"; } )
            .map<int>([&a](const std::string* b) {return a; });
    //check lazy  aftter map
    Stream<std::string>::of(vec_strings_a_a_a).filter([](const std::string* str) { ; return *str != "a"; } )
            .map<int>([&a](const std::string* b) {*a=3;return (a); });
    int array2[3]={0,1,2};
    int j = 0;
    lst = Stream<std::string>::of(vec_strings).filter([](const std::string* str) { return *str != "a"; } )
            .map<int>([&j,&array2](const std::string* a) {j++;return (int*)(array2+j); }) // 1 2
            .filter([](const int* a) { return *a != 1; } ).collect< std::list<int*> >();
    *x =2;
    std::vector<int*> vec({x});
    assert(Compare(vec,lst));
}

void TesTDistinct(std::vector<std::string*>& empty_vec , std::map<int,int*>& empty_map  ,  std::map<int,std::string*>& map_strings,
                  std::vector<std::string*>& vec_strings, std::vector<std::string*>& vec_strings_b_c ,std::vector<std::string*>& vec_strings_c
        ,std::vector<std::string*> vec_strings_a_a_a,std::vector<int*>& vec_int_0_1_2 , std::vector<std::string*> vec_strings_a ){

    Stream<std::string>::of(empty_vec).distinct( [] (const std::string* s1 , const std::string* s2) {return true;} );
    Stream<int>::of(empty_map).distinct( [] (const int* s1 , const int* s2) {return true;} );
    assert(  Compare(vec_strings_a,
                     Stream<std::string>::of(vec_strings_a_a_a).distinct( [] (const std::string* s1 , const std::string* s2) {return( *s1 == *s2);} ).collect< std::list<std::string*> >() ));

    assert(   Stream<std::string>::of(vec_strings_a_a_a).distinct( [] (const std::string* s1 , const std::string* s2) {return( *s1 == "b");} ).count() == 3  );
    int *a = nullptr;
    Stream<std::string>::of(vec_strings_a_a_a).distinct( [a] (const std::string* s1 , const std::string* s2) {*a = 3; return true;} );

}

void TestSorted(std::vector<std::string*>& empty_vec , std::map<int,int*>& empty_map  ,  std::map<int,std::string*>& map_strings,
                std::vector<std::string*>& vec_strings,std::vector<std::string*>& vec_strings_a_a_a,std::vector<int*>& vec_int_0_1_2, int* x , std::vector<std::string*>& vec_strings_a ,std::vector<std::string*>& vec_strings_c_b_a ){

    Stream<std::string>::of(empty_vec).sorted( [] (const std::string* s1 , const std::string* s2) {return true;} );
    Stream<int>::of(empty_map).sorted( [] (const int* s1 , const int* s2) {return true;} );
    assert(Compare(vec_strings,
                   Stream<std::string>::of(vec_strings_c_b_a).sorted( [] (const std::string* s1 , const std::string* s2)
                                                                 {return( *s1 < *s2);} ).collect< std::list<std::string*> >() ));

}

void TestForEach(std::vector<std::string*>& empty_vec , std::map<int,int*>& empty_map  ,  std::map<int,std::string*>& map_strings,
                 std::vector<std::string*>& vec_strings ,std::vector<std::string*> vec_strings_c
        ,std::vector<std::string*> vec_strings_a_a_a,std::vector<int*> vec_int_0_1_2, int* x , std::vector<std::string*> vec_strings_a ,std::vector<std::string*> vec_strings_c_b_a ){

    Stream<std::string>::of(empty_vec).forEach( [] (const std::string* s1 ) {;} );
    Stream<int>::of(empty_map).forEach( [] (const int* s1 ) {;} );
    std::vector<int*> vec;
    Stream<int>::of(vec_int_0_1_2).forEach( [&vec] (int* s) {vec.push_back(s);});
    assert( Compare(vec_int_0_1_2,vec) );
}

void TestReduce(){
    double array[4] = { 1, 2, 3,4};
    std::vector<double*> vector;
    for(int i = 0 ; i < 4; i++) {
        vector.push_back(array + i);
    }
    double initial = 2;
    //if it doesnt work, check the order of reduce.

 //  assert( (*Stream<double>::of(vector).reduce(&initial, [](const double * a, const double* b) { auto * c = new double; *c = *a / *b; return c; }) ) == (double)(4/3.0) );

}

void Mix(){
    double array[4] = { 1, 2, 3,4};
    double array2[4] = { 4,3, 1};
    std::vector<double*> vector2({array2,array2+1,array2+2});
    std::vector<double*> vector;

    for(int i = 0 ; i < 4; i++) {
        vector.push_back(array + i);
    }


    double initial = 2;
    assert ( Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).distinct( [] (const double* s1 , const double * s2) {return true;} ).count() == 1 );
    assert ( Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).distinct( [] (const double* s1 , const double * s2) {return *s1==*s2;} ).count() == 3 );
    assert ( Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).distinct( [] (const double* s1 , const double * s2) {return *s1==*s2;} ).count() == 3 );

   assert (Compare(vector2  , Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).sorted( [] (const double* s1 , const double * s2) {return *s1 >*s2;} ).collect< std::list<double*> >() ));

}

int main() {

    int array[10] = { 1, 2, 3, 2, 4, 6, 5, 7, 8, 9 };
    std::string strings[3] = { "a", "b", "c" };


    std::string strings_2[2] = {  "b", "c" };
    std::string strings_3[1] = {  "c" };
    std::string strings_4[3] = { "a", "a", "a" };
    std::string strings_5[1] = {"a"};
    std::string strings_6[3] = {"c","b","a"};
    std::vector<std::string*> vec_strings_c_b_a;
    std::vector<std::string*> vec_strings_a({strings_5});
    int array_0_1_2[3] = { 0,1,2};
    std::vector<int*> vec_int_0_1_2;
    std::vector<std::string*> vec_strings_a_a_a;
    std::vector<std::string*> vec_strings_c({strings_3+0});
    std::vector<std::string*> vec_strings_b_c( {( strings_2 + 0),strings_2+1 });
    std::map<int,std::string*> map_strings;
    std::vector<std::string*> vec_strings;

    for(int i = 0 ; i < 3; i++) {
        map_strings.insert({i, &strings[i]});
        vec_strings.push_back(strings + i);
        vec_strings_a_a_a.push_back(strings_4+i);
        vec_int_0_1_2.push_back(array_0_1_2+i);
        vec_strings_c_b_a.push_back(strings_6+i);
    }
    std::vector<int*> vec1;
    std::map<int,int*> empty_map;
    std::map<int,int*> map1;
    for(int i = 0 ; i < 10 ; i++) {
        map1.insert({i,&array[i]});
        vec1.push_back(array + i);
    }
    std::vector<std::string*> empty_vec;


    int x = 3;
   // TestOf(empty_vec,empty_map,map1,map_strings,vec_strings);
    TestFilter(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_b_c,vec_strings_c , vec_strings_a_a_a);

    TestMap(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_b_c , vec_strings_a_a_a,vec_int_0_1_2 ,&x);

    TesTDistinct(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_b_c,vec_strings_c , vec_strings_a_a_a,vec_int_0_1_2 , vec_strings_a);
    TestSorted(empty_vec,empty_map, map_strings ,vec_strings , vec_strings_a_a_a,vec_int_0_1_2 ,&x,vec_strings_a
            ,vec_strings_c_b_a);
    TestForEach(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_c , vec_strings_a_a_a,vec_int_0_1_2 ,&x,vec_strings_a
            ,vec_strings_c_b_a);
    TestReduce();
    Mix();


    std::vector<int*> vector;
    for(int i = 0 ; i < 10 ; i++) vector.push_back(array + i);
    assert(Stream<int>::of(vector).filter([](const int* val) { return *val != 2; } ).count() == 8);
    assert(Stream<int>::of(vector).distinct().count() == 10);
    std::vector<int> other = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(compareValues(Stream<int>::of(vector).distinct().sorted().collect<std::vector<int*>>(), other));

    assert(Stream<int>::of(vector).map<Cell<int>>([](const int* a) { return new Cell<int>(*a); }).distinct().count() == 9);

    int initial = 0;
    assert(*Stream<int>::of(vector).reduce(&initial, [](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; }) == 47);
    std::cout<<"passed part2";

    return 0;
}

