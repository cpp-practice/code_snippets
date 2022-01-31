#pragma once

#include <string>
#include <vector>
#include <exception>
#include <iostream>

namespace simple_test {

class AssertionFailed : public std::exception {
};

struct TestRecord {
  const char *name;

  void (*fun)();
};

static std::vector<TestRecord> g_test_records;

struct TestContext {
  const char *name;
  size_t issues = 0;

  void add_issue(const char *file, int line, const char *condition) {
    std::cout << name << " : " << file << ":" << line << " : failed: " << condition << std::endl;
    issues++;
  }
};

static TestContext g_test_context;


bool run_test(const TestRecord &rec) {
  g_test_context = TestContext{rec.name, 0};
  std::cout << rec.name << " RUNNING..." << std::endl;
  try {
    rec.fun();
  } catch (AssertionFailed) {
    std::cout << "Ultimate assertion failed" << std::endl;
  } catch (...) {
    g_test_context.add_issue(__FILE__, __LINE__, "uncaught exception!");
  }
  if (g_test_context.issues == 0) {
    std::cout << rec.name << " PASSED." << std::endl;
    return true;
  } else {
    std::cout << rec.name << " FAILED." << std::endl;
    return false;
  }
}

bool run_all_tests() {
  size_t passed = 0, failed = 0;

  std::cout << "Will run " << std::size(g_test_records) << " tests." << std::endl;
  for (const auto &rec: g_test_records) {
    if (run_test(rec)) {
      passed++;
    } else {
      failed++;
    }
  }
  std::cout << "Passed " << passed << " and failed " << failed << " tests" << std::endl;
  return failed == 0;
}

}  // namespace simple_test


#define BEGIN do {
#define END } while (false)

#define REPORT(condition) ::simple_test::g_test_context.add_issue(__FILE__, __LINE__, #condition)

#define EXPECT(condition) \
  BEGIN \
    if (condition) {} else REPORT(condition); \
  END

#define ASSERT(condition) \
  BEGIN \
    if (condition) {} else { REPORT(condition); throw ::simple_test::AssertionFailed(); } \
  END

#define TEST(name) \
  static void name(); \
  auto registered_test_##name = (::simple_test::g_test_records.push_back(::simple_test::TestRecord{#name, name}), 0); \
  static void name()

#define RUN_ALL_TESTS() ::simple_test::run_all_tests()
