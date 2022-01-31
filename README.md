# C++ Notes

## Code Template

- g++ -std=c++11 -O2 -Wall test.cpp -o test

```c
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
}
```
## Binary Search

- It is used when searching an element in an array if the array is sorted.
- O(logn)

### Method 1

```c
int size = 100;
vector<int> arr(size, 0);

int binarySearch(int searchedItem){
    int a=0, b=size-1;
    while(a<=b){
        int m = a + (b-a)/2;
        if(arr[m] == searchedItem){
            return m;
        }else if(arr[m] > searchedItem){
            b = m-1;
        }else if(arr[m] < searchedItem){
            a = m+1;
        }
    }
    return -1;
}
```
### Method 2
- This implementation is based on starting jumping long and becoming slower when getting close to the target.
```c
int size = 100;
vector<int> arr(size, 0);

int binarySearch(int searchedItem){
    int k=0;
    for(int b=size/2; b>=1; b/=2){ // b is jump size
        while(b+k<size && arr[b+k] <= searchedItem){
            k += b;
        }
    }

    if(arr[k] == searchedItem){
        return k;
    }else{
        return -1;
    }
}
```

## Integer

### Integer Limit Control
- Before adding one more digit to the end of an integer, check it is in the range of integer or not.
- 32 bit integer is between [-2<sup>31</sup>, 2<sup>31</sup> - 1]
```c
int res, added;
...
if (res > INT_MAX/10 || (res == INT_MAX / 10 && added > 7)){
  //Cannot add
}else if (res < INT_MIN/10 || (res == INT_MIN / 10 && added < -8)){
  //Cannot add
}else{
  res = res * 10 + added;
}
```


## String

### Substring

- The first value is the starting index and the second is the length of substring.
```c
string s = "123456789";
string sub_string = s.substr(2, 2); // "34"

```

## Sorting  
### Vector sorting
- It also works with strings.
- Pairs are primarily according to their first elements.

```c
vector<int> arr = {4,2,5,3,5,8,3};
sort(arr.begin(), arr.end()); //Increasing order
sort(arr.rbegin(), v.rend()); // Decreasing order
```

### Array sorting

```c
int n = 7; // array size 
int a[] = {4,2,5,3,5,8,3}; 
sort(a,a+n);
```

### Struct Comparison Operator
- Defining comparison function for struct provides sort function capability.
```c
struct P {
  int x, y;
  bool operator<(const P &p) { 
    if (x != p.x) return x < p.x; 
    else return y < p.y;
  } 
};

vector<P> arr;
sort(arr.begin(), arr.end());
```

### Comparison Function

```c
bool comp(string a, string b) { 
  if (a.size() != b.size()) return a.size() < b.size(); 
  return a < b;
}

sort(v.begin(), v.end(), comp);
```

### Lambda Comparison Function


```c
struct Edges{
    int a;
    int b;
};

sort(arr2.begin(), arr2.end(), [](const Edges &a1, const Edges &a2){return a1.a * a1.b < a2.a * a2.b;});
```
