#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>

//-----------------------------------------------------
template <class T>
void PrintVector(std::vector<T> input) {
  std::cout << "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    std::cout<<"Thread "<<count<<" sum is ";
    std::cout << n<<std::endl;
    if (count < input.size()) std::cout << ", "<<std::endl;
    
  }
  std::cout << " }" << std::endl;
}
//-----------------------------------------------------
class AccumulateFunctor {
 public:
  void operator()(uint64_t start, uint64_t end) {
    _sum = 0;
    for (auto i = start; i < end; i++) {
      _sum += i;
    }
    std::cout << _sum << std::endl;
  }
  // ~AccumulateFunctor(){std::cout << "AccumulateFunctor Destructor." << std::endl;}
  uint64_t _sum;
};
//-----------------------------------------------------
void AccumulateRange(uint64_t &sum, uint64_t start, uint64_t end) {
  sum = 0;
  auto begin1 = std::chrono::steady_clock::now();
  for (uint64_t i = start+1; i < end+1; i++) {
    sum += i;
  }
  auto stop1 = std::chrono::steady_clock::now();
  std::cout<<" Execution time of the Thread "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop1-begin1).count()<< " milliseconds" << std::endl;
}
//-----------------------------------------------------

int SingleThreadApproach(){
  uint64_t start = 1;
  uint64_t end = 500000000;
  uint64_t sum = 0;
  auto begin = std::chrono::steady_clock::now();
  for (uint64_t i = start; i < end+1; i++) {
    sum += i;
  }
  auto stop = std::chrono::steady_clock::now();
  std::cout<<"Singlethread sum "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop-begin).count()<< " milliseconds" << std::endl;
  return 0;

}

int MultipleThreadApproach(){
  const int number_of_threads = 10;
  uint64_t number_of_elements = 500000000;
  uint64_t step = number_of_elements / number_of_threads;
  std::vector<std::thread> threads;
  std::vector<uint64_t> partial_sums(number_of_threads);

  for (uint64_t i = 0; i < number_of_threads; i++) {
    threads.push_back(std::thread([i+1, &partial_sums, step] {
      for (uint64_t j = i * step; j < (i + 1) * step; j++) {
        partial_sums[i] += j;
      }
    }));
  }

  for (std::thread &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }

  uint64_t total =
      std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));

  PrintVector(partial_sums);
  std::cout << "total: " << total << std::endl;

  return 0;

}

int main() {

  //Mutiple thread Approach
  MultipleThreadApproach();
  
}