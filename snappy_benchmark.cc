#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
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
std::string ReadFile(const char* file) {
  std::ifstream ifs(file);
  if (ifs) {
    std::ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
  } else {
    return "";
  }
}

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
  const char* file = "testdata/geo.protodata";
  if (argc >= 2) {
    file = argv[1];
  }
  printf("Benchmarking with file \"%s\".\n\n", file);

  std::string uc = ReadFile(file);
  std::string c;
  std::string s;
  if (uc.empty()) {
    printf("Invalid file \"%s\".\n", file);
    return 1;
  }

  printf("Compressing %zu bytes.\n", uc.size());
  printf("1.0.4=%.3lf ops/ms\n", Benchmark([&uc, &s]() { snappy_104::Compress(uc.data(), uc.size(), &s); }));
  printf("1.1.3=%.3lf ops/ms\n", Benchmark([&uc, &s]() { snappy_113::Compress(uc.data(), uc.size(), &s); }));
  printf("1.1.10=%.3lf ops/ms\n", Benchmark([&uc, &s]() { snappy_1110::Compress(uc.data(), uc.size(), &s); }));
  printf("1.2.1(STLStringResizeUninitialized)=%.3lf ops/ms\n",
         Benchmark([&uc, &s]() { snappy_121::Compress(uc.data(), uc.size(), &s); }));
  printf("1.2.2(STLStringResizeUninitialized)=%.3lf ops/ms\n",
         Benchmark([&uc, &s]() { snappy_122::Compress(uc.data(), uc.size(), &s); }));
  printf("\n");

  snappy_122::Compress(uc.data(), uc.size(), &c);
  printf("Uncompressing %zu bytes.\n", c.size());
  printf("1.0.4=%.3lf ops/ms\n", Benchmark([&c, &s]() { snappy_104::Uncompress(c.data(), c.size(), &s); }));
  printf("1.1.3=%.3lf ops/ms\n", Benchmark([&c, &s]() { snappy_113::Uncompress(c.data(), c.size(), &s); }));
  printf("1.1.10=%.3lf ops/ms\n", Benchmark([&c, &s]() { snappy_1110::Uncompress(c.data(), c.size(), &s); }));
  printf("1.2.1(STLStringResizeUninitialized)=%.3lf ops/ms\n",
         Benchmark([&c, &s]() { snappy_121::Uncompress(c.data(), c.size(), &s); }));
  printf("1.2.2(STLStringResizeUninitialized)=%.3lf ops/ms\n",
         Benchmark([&c, &s]() { snappy_122::Uncompress(c.data(), c.size(), &s); }));
  printf("\n");
  return 0;
}
