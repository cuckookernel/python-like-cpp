#include <iostream>
#include <cassert> 
#include "py.h"

using namespace std; 
using py::range;
using py::str_join; 
using py::Str;
using py::enumerate;

void test_range( ) {
    vector<long> v1 = range(10);
    assert( v1[0] == 0 && v1.size() == 10 && v1[v1.size()-1] == 9  && v1[1] == 1);  

    vector<long> v2 = range(-10,-5);
    assert( v2[0] == -10 && v2.size() == 5 && v2[v2.size()-1] == -6   && v2[1] == -9);  

    vector<long> v3 = range(-5, -10, -1);
    assert( v3[0] == -5 && v3.size() == 5 && v3[v3.size()-1] == -9   && v3[1] == -6);  

    cout << "test_range OK" << endl;
}

void test_str_join( ) {
    vector<int> v1{ 1, 2, 3};

    auto a_str = str_join( v1, "||" );
    
    assert( a_str == "1||2||3" );

    auto a_str2 = Str("||").join( vector<int>({1,2,3}) );
    assert( a_str2 == "1||2||3" );

    auto a_str3 = Str("||").join( vector<long>(range(3)) );
    assert( a_str3 == "0||1||2" );
            
    cout << "test_str_join OK" << endl;
}

void test_enumerate( ){

    vector<int> v{1,7,8};

    string m = "Mateo";

    for ( auto i : enumerate<string>(m)) {
        cout << i.first << "  " << i.second << endl;
    }
}


int main() {
    // test_range();
    // test_str_join();
    test_enumerate();

    return 0;
}
