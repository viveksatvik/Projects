#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>

//function to perform addition of numbers from 1 to 500000000

int SingleThreadApproach(){
  uint64_t start = 1;
  uint64_t end = 500000000;
  uint64_t sum = 0;
  auto begin = std::chrono::steady_clock::now();
  for (uint64_t i = start; i < end+1; i++) {
    sum += i;
  }
  std::cout<<sum<<std::endl;
  auto stop = std::chrono::steady_clock::now();
  std::cout<<"Singlethread sum "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop-begin).count()<< " milliseconds" << std::endl;
  return 0;

}

//main function

int main() {
  //No of cores in the system
  unsigned int c = std::thread::hardware_concurrency();
  std::cout << " number of cores: " << c << std::endl;
  //Single Threaded approach
  SingleThreadApproach();
  return 0;
}