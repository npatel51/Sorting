#ifndef _SORT_UTIL_
#define _SORT_UTIL_
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef unsigned long long int ulli;

template <typename E>
class Sort{

 public:
  Sort(E* array, unsigned long long int size);

  ulli array_size();
  void swap( E * element_1, E* element_2);
  void print_array( );
  void bubble_sort( );
  void selection_sort();
  void insertion_sort( );
  void quick_sort( );
  void merge_sort( );

  inline E* begin(){ return this->array;}
  inline E* end(){  return (this->array+this->size)-1;}

  //fix to have default argument begin() and end()
  E max(ulli begin , ulli const end );
  ulli max_index(ulli begin , ulli const end );
  E min(ulli begin ,ulli const end );

 private:
  ulli size;
  E* array;
  void partition(E* begin,E* end, E*& pivot_index);
  void do_quick_sort(E* begin, E* end);
  void do_merge_sort(E* begin, E* end);
  void merge(E* left1, E* right1, E* left2, E* right2,E* begin);

};



//constructor
template <typename E>
Sort<E>::Sort(E* array, ulli size){
  this->array = array;
  this->size = size;
}

//Return the size of the array
template <typename  E>
ulli
Sort<E>::array_size() {
  return this->size;
}

//Swap
template <typename E>
void
Sort<E>::swap( E * element_1, E* element_2){

//  cout<<*element_1<<"  "<<*element_2<<endl;
  E temp = *element_1;
  *element_1 = *element_2;
  *element_2 = temp;

}

//find the largest element in the array
template <typename E>
E
Sort<E>::max(ulli begin , ulli const end ){

  E max_ele = array[begin];

  while( begin <= end ){
    if(max_ele < array[begin]){
       max_ele = array[begin];
     }
     begin++;
   }

  return max_ele;
}

//find the smallest element in the array
template <typename E>
E
Sort<E>::min(ulli begin , ulli const end ){

  E min_ele = array[begin];

  while( begin <= end ){
    if(min_ele > array[begin]){
       min_ele = array[begin];
     }
    begin++;
   }
   return min_ele;
}

//find the index of largest element in the array

template <typename E>
ulli
Sort<E>::max_index(ulli begin ,ulli const end ){

  E max_ele = array[begin];
  ulli max_index = begin;
  while( begin <= end ){
    if(max_ele < array[begin]){
        max_ele = array[begin];
        max_index = begin;
     }
      begin++;
  }
  return max_index;
}

//print the array

template <typename E>
void
Sort<E>::print_array(){
  cout<<"[";
  for(int i = 0 ; i<size-1 ; ++i){
    cout<<array[i]<<",";
  }
  cout<<array[size-1]<<"]"<<endl;
}

/* Bubble Sort: Swap two elements that are not in order,
   repeat the process n (no. of elements in array)  times
   Example: arr[] = {6,8,0,4,1};
   [6,8,0,4,1] 6 < 8
   [6,8,0,4,1] 8 > 0 swap(8,0)
   [6,0,8,4,1] 8 > 4 swap(8,4)
   [6,0,4,8,1] 8 > 1 swap(8,1)
   [6,0,4,1,8] //end of first iteration
       .
       .
       .
   [0,4,1,6,8] //after second iteration
       .
       .
       .
   [0,1,4,6,8]

   Time Complexity:

   Worst-case performance 	O ( n^2 )
   Best-case performance 	O ( n )
   Average performance 	O ( n^2 )
 */
template <typename E>
void
Sort<E>::bubble_sort(){

  unsigned long long int size  = array_size();
  bool swapped;


  for( int i = 0; i != size ; ++i ){
    swapped = false;
    // after the loop the last i element will be in correct position
    for ( int j = 0; j < size-i-1; ++j ){

      if( array[j] > array[j+1] ){
        	swap(&array[j],&array[j+1]);
        	swapped = true;
      }
    }
     this-> print_array();

     if( !swapped )
       break;
  }
}

// improves on the bubble sort by making only one exchange for every pass through the list.
// Find the largest element in the list [0...n-1] and put it the largest place, each pass
// places the element in the correct position giving us the sorted list after n-1 pass
template <typename E>
void
Sort<E>::selection_sort(){

  ulli right = size-1;
  ulli index  = 0;
  while(right>0){
    index = max_index(0,right);
    swap(&array[index],&array[right]);
    right--;
  }

}

/*Insertion sort: Start with the 2nd element of the array,
  store it as a key and and compare it with previous element/s
  if element is greater move the previous element one position ahead.
  Repeat the process with 3,4,5,..,n elements.

  Example: [6,8,0,4,1]
  Iteration #1
  key:= 8
  [6,8,0,4,1] 6 < 8

  Iteration #2
  key:= 0, j = 1
  [6,8,0,4,1] 8 > 0 -> a[j+1] = a[j]
  [6,8,8,4,1] 6 > 0
  [6,6,8,4,1] j=-1
  a[0] = 0 ( key )
  [0,6,8,4,1]

  Iteration #3
  key:= 4, j = 2
  [0,6,8,4,1]  8 > 4 ->a[j+1] = a[j]
  [0,6,8,8,1]  6 > 4
  [0,6,6,8,1]  0 < 4
  [0,4,6,8,1]    a[0+1] = 4
       .
       .
  Worst-case performance (n^2) comparisons, swaps
  Best-case performance 	O(n) comparisons, O(1) swaps
  Average performance 	(n^2) comparisons, swaps

 */

template <typename E>
void
Sort<E>::insertion_sort(){

  for( int i = 1; i !=size ; ++i){
  //  this->print_array();
    int key = array[i];
    int j = i-1;
  //  cout<<key<<" : ";

    while( j>=0 && array[j]>key){
        array[j+1] = array[j];
        --j;
    }

    array[j+1] = key;
  //  this->print_array();
  }

}

//The quick sort algorithm

template <typename E>
void
Sort<E>::partition(E* left, E* right, E*& pivot){
  //base case:
  if(left > right){             // split point: when leftmark and rightmark crosses each other
    swap(right,pivot);
    pivot = right;             // split point: left value are lesser and right value are greater
    return ;
  }

  //adjust the pointer accordingly

  if(*left <= *pivot){                          //keep moving to the right by advancing the left pointer
    ++left;
  } else if(*left > *pivot  && *right < *pivot){  //if leftmark value is greater than the pivot and lesser than the rightmark
    swap(left,right);
    left++; right--;                              //advance both left and right pointer
  } else {                                        // move the right pointer to the left
    --right;
  }

  partition(left,right,pivot);
}

//Do the partition

template <typename E>
void
Sort<E>::do_quick_sort(E* begin, E* end){

  if( begin<end){
    E* pivot_index = begin;
    partition(begin+1,end,pivot_index);
    do_quick_sort(begin,pivot_index-1);
    do_quick_sort(pivot_index+1,end);

  }
}


template <typename E>
void
Sort<E>::quick_sort(){
  do_quick_sort(this->begin(),this->end());
}


template <typename E>
void
Sort<E>::merge(E* l1, E* r1, E* l2, E* r2,E* begin){

  //offset adjustment
  int l_size = (r1-l1)+1;
  int r_size = (r2-l2)+1;
  //create temp arrays
  E* l = new E[l_size];
  E* r = new E[r_size];

  //copy left subarray in l in and right subarray in r
  for(int i=0;i<l_size;++i)
      l[i] = *(l1+i);
  for(int i=0;i<r_size;++i)
      r[i] = *(l2+i);

  int i = 0,j = 0;

  //If element in the left subarray is samller than the element in the right
  //subarray assign begin to the left subarray and vice versa
  while( i < l_size && j < r_size )
    *begin++ = (l[i]<=r[j])?l[i++]:r[j++];

  // copy the reamining in the array
  while(i<l_size)
    *begin++ = l[i++];

  while(j<r_size)
    *begin++ = r[j++];

  //free memory
  delete [] l;
  delete [] r;

}

template <typename E>
void
Sort<E>::do_merge_sort(E* begin, E* end){

  E* mid  =  begin+(end-begin)/2;

  //base case: If there is more than one element in the array
  if( end - begin > 0){
    do_merge_sort(begin,mid);
    do_merge_sort(mid+1,end);
    merge(begin,mid,mid+1,end,begin);
    //this->print_array();
    //cout<<"begin1:"<<*begin<<" end1:"<<*mid<<"  begin2:"<<*(mid+1)<<" end2: "<<*end<<endl;
  }
}

//merge sort algorithm

template <typename E>
void
Sort<E>::merge_sort(){
  do_merge_sort(this->begin(),this->end());
}

#endif
