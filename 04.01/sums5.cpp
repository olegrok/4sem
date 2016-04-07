#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <functional>

void _sum(int a, int* sum){
  (*sum) += a;
}

int _plus(int a, int b, int* result){
  (*result) += a;
  return a;
}

bool _compare(int a, int b, int* result){
  (*result) += b;
  return false;
}

bool _uCompare(int a, int* result){
  (*result) += a;
  return false;
}

int main(){
  int n = 6;
  std::vector<int> v(n);
  for(int i = 0; i < n; i++){
    v[i] = rand() % 10;
    std::cout << "v[" << i <<"]= " << v[i] << std::endl;
  }
  int result = 0;

  auto vSum = std::bind<void>(_sum, std::placeholders::_1, &result);
  std::for_each(v.begin(), v.end(), vSum);
  std::cout << result << std::endl;

  std::all_of(v.begin(), v.end(), [&](int i){
    result += i;
    return true;
  });
  std::cout << result << std::endl;

  auto iSum = std::bind<int>(_plus, std::placeholders::_1, std::placeholders::_2, &result);
  std::transform (v.begin(), v.end(), v.begin(), v.begin(), iSum);
  std::cout << result << std::endl;

  auto bSum = std::bind<bool>(_compare, std::placeholders::_1, std::placeholders::_2, &result);
  std::merge(v.begin(), v.end(), v.begin(),v.end(), std::vector<int>(2*n).begin(), bSum);
  std::cout << result << std::endl;

  std::find_if_not(v.begin(), v.end(), [&](int i){
      result += i;
      return true;
  });
  std::cout << result << std::endl;


  for(auto i = v.begin(); i != v.end(); i++)
    std::cout << *i << std::endl;
  return 0;
}
