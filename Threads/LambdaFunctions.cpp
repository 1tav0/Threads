#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <numeric>
using namespace std;

//function to print out a vector
void printVector(vector<int> v){
  //lambda expression to print out the vector list 
  for_each(v.begin(), v.end(), [](int i){
    cout << i << " " ;
  });
}

int main(){

  vector<int> v = {1, 2, 3, 4,4,4,4,4, 5, 6, 7, 8, 9, 10};
  printVector(v);

  //find the first number greater than 4
  //find_if searches for an element for which functio returns true
  vector<int>::iterator p = find_if(v.begin(), v.end(), [](int i){
    return i>4;
  });

  cout << endl << "First number greater than 4 is: " << *p << endl;

  //lambda expression for sorting in non-increasing order
  //compiler can make return type bool but shown here just for explanation
  sort(v.begin(), v.end(), [](const int &a, const int &b) -> bool{
    return a > b;
  });
  printVector(v);
  cout << endl;

  //lamnda expression for counting numbers greater than or equal to 5
  int greater_5 = count_if(v.begin(), v.end(), [](int a){
    return (a>=5);
  });
  cout << "The number of elements grater than or equal to 5 is: " << greater_5 << endl;

  //function for removing all duplicate elements (after sorting all duplicate comes)
  //The lambda function (int a, int b) { return a == b; } checks if two elements a and b are equal, and if they are, unique removes the second occurrence.
  //After running this code, the range [v.begin(), v.end()) will have consecutive duplicate elements removed, and p will point to the position after the last unique element.
  //Vector after unique: 10 9 8 7 6 5 4 3 2 1
  //The p iterator now points to the position after the last unique element (in this case, it's the position after 1).
  p = unique(v.begin(), v.end(), [](int a, int b){
    return a == b;
  });

  //This line resizes the vector v based on the distance between v.begin() (the beginning of the vector) and p (the position after the last unique element). The distance function calculates the number of elements in this range.
  //As a result, the vector v is resized to include only the unique elements (i.e., consecutive duplicates have been removed).
  //Finally, the code resizes the vector v based on the distance between v.begin() and p. The distance function calculates the number of elements in this range.
  //Resized Vector: 10 9 8 7 6 5 4 3 2 1
  //The vector is resized to include the elements from the beginning of the vector up to (but not including) the position pointed to by the iterator p.
  //After these steps, the vector contains the unique elements, and p points to the position after the last unique element, which is also the end of the resized vector.
  v.resize(distance(v.begin(), p));
  printVector(v);

  //accumulate function 
  //accumulate the container on the basis of the function privided as the third argument
  //arr and arr + 10 define the range over which the accumulation is performed. It includes elements from arr (beginning) to arr + 10 (one past the end), effectively including all elements from the array
  //1 is the initial value for the accumulation.
  //The lambda function (int i, int j) { return i * j; } specifies the operation to be performed on each element during the accumulation. It multiplies the current accumulated value i by the current element j.
  //The result of the accumulate function, which is the factorial of 10, is stored in the variable f.
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int f = accumulate(arr, arr+10, 1, [](int i, int j){
    return i*j;
  });
  cout << "Factorial of 10 is: " << f << endl;

  // we can also store the lambda function in a variable
  auto square = [](int i)
  {
    return i * i;
  };
  cout << "Square of 5 is: " << square(5) << endl;

  //passing by reference using lambda
  vector<int> v1 = {3, 1, 7, 9};
  vector<int> v2 = {10, 2, 7, 16, 9};
  //access v1 & v2 by reference
  auto pushinto = [&](int i)
  {
    v1.push_back(i);
    v2.push_back(i);
  };

  pushinto(20);

  //access v1 by copy
  [v1]()
  {
    for(auto p=v1.begin(); p!=v1.end(); p++)
    {
      cout << *p << " ";
    }
  };

  int N = 5;
  //find first number greater than N
  //[N] denotes, can access only N by value
  vector<int>::iterator it = find_if(v.begin(), v.end(), [N](int i){
    return i>N;
  });

  cout << "first number greater than 5 is: " << *it << endl;

  //function to count numbers greater than or equal to N 
  //[=] denotes, can access all variable
  int count_N = count_if(v.begin(), v.end(), [=](int a){
    return (a >= N);
  });

  cout << "The number of elements greater than or equal to 5 is: " << count_N << endl;

  return 0;
}