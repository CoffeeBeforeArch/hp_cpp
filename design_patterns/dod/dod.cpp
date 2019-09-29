// This program shows off the basics of data-oriented-design in C++
// By: Nick from CoffeeBeforeArch

#include <benchmark/benchmark.h>
#include <algorithm>
#include <iterator>
#include <vector>

using std::back_inserter;
using std::fill_n;
using std::vector;

// A simple struct aligned in such a way no two instances will be on
// the same cache line (64 bytes cache lines, 64 byte alignment)
struct SimpleStruct {
  // Struct with a 16 integer fields
  int v0 = 0;
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  int v4 = 0;
  int v5 = 0;
  int v6 = 0;
  int v7 = 0;
  int v8 = 0;
  int v9 = 0;
  int v10 = 0;
  int v11 = 0;
  int v12 = 0;
  int v13 = 0;
  int v14 = 0;
  int v15 = 0;

  // Method to increment the field (only 1 here for brevity)
  void inc_v0() { v0++; }
};

// A simple struct that contains an array the fields stored in the
// other object
struct SoA {
  // Simple constructor that resizes the vector to store N values
  SoA(int N) {
    // Zero-initialized by default
    v0s.resize(N);
    v1s.resize(N);
    v2s.resize(N);
    v3s.resize(N);
    v4s.resize(N);
    v5s.resize(N);
    v6s.resize(N);
    v7s.resize(N);
    v8s.resize(N);
    v9s.resize(N);
    v10s.resize(N);
    v11s.resize(N);
    v12s.resize(N);
    v13s.resize(N);
    v14s.resize(N);
    v15s.resize(N);
  }

  // Update method that increments each value
  // Only for v0 for the sake of brevity
  void update_v0() {
    for (auto &i : v0s) {
      i++;
    }
  }

  // Vector of values
  vector<int> v0s;
  vector<int> v1s;
  vector<int> v2s;
  vector<int> v3s;
  vector<int> v4s;
  vector<int> v5s;
  vector<int> v6s;
  vector<int> v7s;
  vector<int> v8s;
  vector<int> v9s;
  vector<int> v10s;
  vector<int> v11s;
  vector<int> v12s;
  vector<int> v13s;
  vector<int> v14s;
  vector<int> v15s;
};

// Benchmark for classic OO approach
static void ArrayOfStructs_Bench(benchmark::State &s) {
  // Extract the number of objects we want
  int N = 1 << s.range(0);

  // Create a vector for the PaddedStruct
  vector<SimpleStruct> v;
  fill_n(back_inserter(v), N, SimpleStruct());

  // Profile the update for each field
  while (s.KeepRunning()) {
    // Increment the field for each struct
    for (auto &i : v) {
      i.inc_v0();
    }
  }
}
// Register the SoA benchmark
BENCHMARK(ArrayOfStructs_Bench)->DenseRange(8, 16);

// Benchmark for DoD approach
static void StructOfArrays_Bench(benchmark::State &s) {
  // Extract the number of objects we want
  int N = 1 << s.range(0);

  // Create an Struct of Arrays
  SoA struct_of_arrays(N);

  // Profile the update of each field
  while (s.KeepRunning()) {
    struct_of_arrays.update_v0();
  }
}
// Register the AoS benchmark
BENCHMARK(StructOfArrays_Bench)->DenseRange(8, 16);

// Main function for the benchmarks
BENCHMARK_MAIN();
