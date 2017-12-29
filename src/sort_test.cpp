#include<iostream>
#include<stdlib.h>
#include<time.h>
#include "Sort.h"
using namespace std;
typedef unsigned long long int ulli;

inline double d_rand(double dmin, double dmax){
    return dmin + (double)rand() / RAND_MAX * (dmax - dmin);
}

template <typename E>
void result(E* arr,ulli size){
  Sort<E> s(arr,size);

  cout<<"Unsorted array => ";
  s.print_array();
  cout<<"Array begins with "<<*(s.begin())<<endl;
  cout<<"Array ends with "<<*(s.end())<<endl;
  cout<<"Size of the array: "<<s.array_size()<<endl;
  cout<<s.max(0,s.array_size()-1)<<" is the largest element in the array."<<endl;
  cout<<s.min(0,s.array_size()-1)<<" is the smallest element in the array."<<endl;
  s.merge_sort();
  cout<<"Sorted array => ";
  s.print_array();
  cout<<endl<<endl;

}

void test_sort(int size_of_array, int min = -50,int max = 100,char low = 'a',double dmax = 1.0,double dmin = -1.0){
  int arr[size_of_array];
  double darr[size_of_array];
  char carr[size_of_array];
  string sarr[] = {"banana","orange","apple","avocado","cherry","grape","watermelon","kiwi"};

  srand (time(NULL));
  for(int i=0;i<size_of_array;++i){
      arr[i] =  min + (rand() % max) ;        //generate random [-50,..,50]
      carr[i] = low + (rand() % 26 );         //generate random [a,...,z]
      darr[i] = d_rand(dmax,dmin);            // [-1.0,1.0]
  }
  result(arr,size_of_array);
  result(darr,size_of_array);
  result(carr,size_of_array);
  result(sarr,sizeof(sarr)/sizeof(sarr[0]));
}

int main( void ){

  // pass the size of the array, range of integer, range of double for testing 
  test_sort(10);

  return 0;
}
