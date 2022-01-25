# C++ Notes

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
