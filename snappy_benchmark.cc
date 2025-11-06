#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <string>

/************************************************************************/
namespace snappy_104 {
size_t Compress(const char*, size_t, std::string*);
bool Uncompress(const char*, size_t, std::string*);
}  // namespace snappy_104
namespace snappy_113 {
size_t Compress(const char*, size_t, std::string*);
bool Uncompress(const char*, size_t, std::string*);
}  // namespace snappy_113
namespace snappy_1110 {
size_t Compress(const char*, size_t, std::string*);
bool Uncompress(const char*, size_t, std::string*);
}  // namespace snappy_1110
namespace snappy_121 {
size_t Compress(const char*, size_t, std::string*);
bool Uncompress(const char*, size_t, std::string*);
}  // namespace snappy_121
namespace snappy_122 {
size_t Compress(const char*, size_t, std::string*);
bool Uncompress(const char*, size_t, std::string*);
}  // namespace snappy_122

/************************************************************************/
template <typename Lambda>
double Benchmark(Lambda lambda) {
  std::chrono::steady_clock::duration total(0);
  size_t count = 0;
  for (;;) {
    auto begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < 100; ++i) {
      lambda();
      lambda();
      lambda();
      lambda();
      lambda();
      lambda();
      lambda();
      lambda();
      lambda();
      lambda();
    }
    auto end = std::chrono::steady_clock::now();
    total += end - begin;
    count += 1000;
    if (total >= std::chrono::milliseconds(1000)) {
      break;
    }
  }

  return (double)count / (double)std::chrono::duration_cast<std::chrono::milliseconds>(total).count();
}

/************************************************************************/
int main(int argc, char** argv) {
  size_t m = 1048576;
  if (argc >= 2) {
    m = (size_t)strtoull(argv[1], nullptr, 10);
  }

  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution<uint64_t> dist;
  std::string plain;
  std::string compressed;
  plain.resize(m);
  for (char& c : plain) {
    c = (char)dist(engine);
  }

  printf("Compressing %zu bytes.\n", m);
  printf("1.0.4=%.3lf ops/ms\n", Benchmark([&plain]() {
           std::string s;
           snappy_104::Compress(plain.data(), plain.size(), &s);
         }));
  printf("1.1.3=%.3lf ops/ms\n", Benchmark([&plain]() {
           std::string s;
           snappy_113::Compress(plain.data(), plain.size(), &s);
         }));
  printf("1.1.10=%.3lf ops/ms\n", Benchmark([&plain]() {
           std::string s;
           snappy_1110::Compress(plain.data(), plain.size(), &s);
         }));
  printf("1.2.1(STLStringResizeUninitialized)=%.3lf ops/ms\n", Benchmark([&plain]() {
           std::string s;
           snappy_121::Compress(plain.data(), plain.size(), &s);
         }));
  printf("1.2.2(STLStringResizeUninitialized)=%.3lf ops/ms\n", Benchmark([&plain]() {
           std::string s;
           snappy_122::Compress(plain.data(), plain.size(), &s);
         }));
  printf("\n");

  snappy_121::Compress(plain.data(), plain.size(), &compressed);
  printf("Uncompressing %zu bytes.\n", compressed.size());
  printf("1.0.4=%.3lf ops/ms\n", Benchmark([&compressed]() {
           std::string s;
           snappy_104::Uncompress(compressed.data(), compressed.size(), &s);
         }));
  printf("1.1.3=%.3lf ops/ms\n", Benchmark([&compressed]() {
           std::string s;
           snappy_113::Uncompress(compressed.data(), compressed.size(), &s);
         }));
  printf("1.1.10=%.3lf ops/ms\n", Benchmark([&compressed]() {
           std::string s;
           snappy_1110::Uncompress(compressed.data(), compressed.size(), &s);
         }));
  printf("1.2.1(STLStringResizeUninitialized)=%.3lf ops/ms\n", Benchmark([&compressed]() {
           std::string s;
           snappy_121::Uncompress(compressed.data(), compressed.size(), &s);
         }));
  printf("1.2.2(STLStringResizeUninitialized)=%.3lf ops/ms\n", Benchmark([&compressed]() {
           std::string s;
           snappy_122::Uncompress(compressed.data(), compressed.size(), &s);
         }));
  printf("\n");
  return 0;
}
