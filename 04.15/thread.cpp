#include <thread>
#include <mutex>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <atomic>
#include <future>

//packaged_task

void func(int& res,std::atomic<int>& Ares, int* syncRes,
  std::mutex& mutex, int M){
  for(int i = 0; i < M; i++){
    mutex.lock();
    res++;
    mutex.unlock();
    __sync_fetch_and_add(syncRes, 1);
    Ares++;
  }
}

int asyncFunc(int M){
  int locRes = 0;
  for(int i = 0; i < M; i++)
    locRes++;
  return locRes;
}

void promiseFunc(std::promise<int> pro, int M){
  int locRes = 0;
  for(int i = 0; i < M; i++)
    locRes++;
  pro.set_value(locRes);
}
using std::cout;
using std::endl;

int main(int argc, char* argv[]){
  if(argc < 2)
    return -1;
  int res = 0;
  int syncRes = 0;
  std::atomic<int> atomicRes(0);
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  std::mutex mutex;
  std::cout << "Expected: " << N * M << std::endl;
  std::vector<std::thread> tVec;
  std::vector<std::future<int>> fut;

  std::vector<std::promise<int>> pPromise;
{  std::vector<std::future<int>> pFuture;
  std::vector<std::thread> pThread;

  for(int i = 0; i < N; i++){
    pPromise.push_back(std::promise<int>());
    pFuture.push_back(pPromise.back().get_future());
    pThread.push_back(std::thread(promiseFunc, std::move(pPromise.back()), M));
  }

  int promise_res = 0;
  try{
  for(auto& future : pFuture){
    future.wait();
    promise_res += future.get();
  }
}
  catch(const std::exception &e){
    cout << e.what();
  }
  cout << "Promise Result: " << promise_res << endl;

  for(auto& it : pThread)
    it.join();
}
  for(int i = 0; i < N; i++){
      fut.push_back(std::async(asyncFunc, M));
  }

  for(int i = 0; i < N; i++){
    tVec.push_back(std::thread(func, std::ref(res),
      std::ref(atomicRes), &syncRes, std::ref(mutex), M));
  }

  for(auto& it : tVec)
    it.join();

  int future_result = 0;
  for(auto& itF : fut){
    itF.wait();
    future_result += itF.get();
  }

  std::cout << "Result: " << res << std::endl;
  std::cout << "sync_fetch Result: " << syncRes << std::endl;
  std::cout << "Atomic Result: " << atomicRes << std::endl;

  std::cout << "Future Result: " << future_result << std::endl;

  return 0;
}
