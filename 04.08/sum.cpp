/*
1)C for
2) for(auto;;a)
s+=a[i];

*/
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>

struct Sum{
  int x;
  //Sum(int i = 0) : x(i) {};
  Sum(int i = 0) : x(i) {};
  //Sum(int );

  ~Sum(){};
  void operator() (int n){
    x += n;
  }
  operator int(){
    return x;
  }
};


class Sum2{
public:
  int& x;
  Sum2(int &i) : x(i) {};
  void operator()(int n){
    x += n;
  }

};

int result = 0;
void summator (int i){
  result += i;
}

void summator2(int i, int& res)
{
  res += i;
}


class myString : public std::string{
public:
  myString& operator=(const myString& copy){
    return *this;
  }
  myString& operator+(int x){
    if(!empty())
      (*this) += "+";
    (*this) += std::to_string(x);
    return *this;
  }
};

int main(){
  std::vector<int> v = {1, 2, 3, 4, 5};
  int sum = 0;

  for(int i = 0; i < 100500; i++)
    v.push_back(rand() % 15);

  for(auto i : v)
    sum += i;
  std::cout << sum << std::endl;
  sum = 0;

  std::for_each(v.begin(), v.end(), summator);
  std::cout << result << std::endl;
  result = 0;

  std::for_each(v.begin(), v.end(), [&](int i){
    sum += i;
  });
  std::cout << sum << std::endl;
  sum = 0;

  int x = 0;

  Sum s(x);
  s = std::for_each(v.begin(), v.end(), Sum(x));
  std::cout << s.x << std::endl;
  s.x = 0;

  sum = std::for_each(v.begin(), v.end(), Sum(x));
  std::cout << sum << std::endl;
  sum = 0;

  std::for_each(v.begin(), v.end(), Sum2(x));
  std::cout << "x = " << x << std::endl;

  std::for_each(v.begin(), v.end(), std::bind<void>(summator2, std::placeholders::_1, std::ref(sum)));
  std::cout << sum << std::endl;
  sum = 0;

  sum = std::accumulate(v.begin(),  v.end(), 0);
  std::cout << sum << std::endl;
  sum = 0;

  sum = std::accumulate(v.begin(),  v.end(), 0);
  std::cout << sum << std::endl;
  sum = 0;

  sum = std::accumulate(v.begin(),  v.end(), 1, [](int a, int b) -> int {
    return a * b;
  });
  std::cout << sum << std::endl;
  sum = 0;

  std::string str = "";

  str = std::accumulate(v.begin(), v.end(), str, [](std::string a, int b) -> std::string
  {
    return a + (a.empty() ? "" : "+") + std::to_string(b);
  });
  std::cout << str << std::endl;

  myString my_str;
  str = std::accumulate(v.begin(), v.end(), my_str);
  std::cout << str << std::endl;

  return 0;
}
