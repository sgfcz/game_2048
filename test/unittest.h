// Copyright Contributors to the Pystring project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/imageworks/pystring/blob/master/LICENSE

#ifndef INCLUDED_QT_CPP2048_UNITTEST_H
#define INCLUDED_QT_CPP2048_UNITTEST_H

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

extern int unit_test_failures;

void unittest_fail();

using QtCpp2048TestFunc = void (*)();

struct QtCpp2048Test {
  QtCpp2048Test(std::string testgroup, std::string testname, const QtCpp2048TestFunc test)
      : group(std::move(testgroup)), name(std::move(testname)), function(test) {};
  std::string group, name;
  QtCpp2048TestFunc function;
};

using UnitTests = std::vector<QtCpp2048Test*>;

UnitTests& GetUnitTests();

struct AddTest {
  explicit AddTest(QtCpp2048Test* test);
};

/// QTCPP2048_CHECK_* macros checks if the conditions is met, and if not,
/// prints an error message indicating the module and line where the
/// error occurred, but does NOT abort.  This is helpful for unit tests
/// where we do not want one failure.
#define QTCPP2048_CHECK_ASSERT(x)                            \
  ((x) ? ((void)0)                                           \
       : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n" \
                     << "FAILED: " << #x << "\n"),           \
          (void)++unit_test_failures))

#define QTCPP2048_CHECK_EQUAL(x, y)                                                        \
  std::string xout, yout;                                                                  \
  for (auto j : x) xout = xout + std::to_string(j) + " ";                                  \
  for (auto j : y) yout = yout + std::to_string(j) + " ";                                  \
  (((x) == (y)) ? ((void)0)                                                                \
                : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                      \
                              << "FAILED: " << #x << " == " << #y << "\n"                  \
                              << "\tvalues were '" << xout << "' and '" << yout << "'\n"), \
                   (void)++unit_test_failures))

#define QTCPP2048_CHECK_NE(x, y)                                                         \
  (((x) != (y)) ? ((void)0)                                                              \
                : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                    \
                              << "FAILED: " << #x << " != " << #y << "\n"                \
                              << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
                   (void)++unit_test_failures))

#define QTCPP2048_CHECK_LT(x, y)                                                        \
  (((x) < (y)) ? ((void)0)                                                              \
               : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                    \
                             << "FAILED: " << #x << " < " << #y << "\n"                 \
                             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
                  (void)++unit_test_failures))

#define QTCPP2048_CHECK_GT(x, y)                                                        \
  (((x) > (y)) ? ((void)0)                                                              \
               : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                    \
                             << "FAILED: " << #x << " > " << #y << "\n"                 \
                             << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
                  (void)++unit_test_failures))

#define QTCPP2048_CHECK_LE(x, y)                                                         \
  (((x) <= (y)) ? ((void)0)                                                              \
                : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                    \
                              << "FAILED: " << #x << " <= " << #y << "\n"                \
                              << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
                   (void)++unit_test_failures))

#define QTCPP2048_CHECK_GE(x, y)                                                         \
  (((x) >= (y)) ? ((void)0)                                                              \
                : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                    \
                              << "FAILED: " << #x << " >= " << #y << "\n"                \
                              << "\tvalues were '" << (x) << "' and '" << (y) << "'\n"), \
                   (void)++unit_test_failures))

#define QTCPP2048_CHECK_CLOSE(x, y, tol)                                                           \
  ((std::abs((x) - (y)) < tol)                                                                     \
       ? ((void)0)                                                                                 \
       : ((std::cout << __FILE__ << ":" << __LINE__ << ":\n"                                       \
                     << "FAILED: abs(" << #x << " - " << #y << ") < " << #tol << "\n"              \
                     << "\tvalues were '" << (x) << "', '" << (y) << "' and '" << (tol) << "'\n"), \
          (void)++unit_test_failures))

#define QTCPP2048_CHECK_THOW(S, E)                                  \
  try {                                                             \
    S;                                                              \
    throw "throwanything";                                          \
  } catch (E const& ex) {                                           \
  } catch (...) {                                                   \
    std::cout << __FILE__ << ":" << __LINE__ << ":\n"               \
              << "FAILED: " << #E << " is expected to be thrown\n"; \
    ++unit_test_failures;                                           \
  }

#define QTCPP2048_CHECK_NO_THOW(S)                               \
  try {                                                          \
    S;                                                           \
  } catch (...) {                                                \
    std::cout << __FILE__ << ":" << __LINE__ << ":\n"            \
              << "FAILED: exception thrown from " << #S << "\n"; \
    ++unit_test_failures;                                        \
  }

#define QTCPP2048_ADD_TEST(group, name)                                                                       \
  static void QtCpp2048Test_##group##_##name();                                                               \
  AddTest pystringaddtest_##group##_##name(new QtCpp2048Test(#group, #name, QtCpp2048Test_##group##_##name)); \
  static void QtCpp2048Test_##group##_##name()

#define QTCPP2048_TEST_SETUP() int unit_test_failures = 0

#define QTCPP2048_TEST_APP(app)                                                                        \
  std::vector<QtCpp2048Test*>& GetUnitTests() {                                                        \
    static std::vector<QtCpp2048Test*> qtcpp2048_unit_tests;                                           \
    return qtcpp2048_unit_tests;                                                                       \
  }                                                                                                    \
  AddTest::AddTest(QtCpp2048Test* test) { GetUnitTests().push_back(test); };                           \
  QTCPP2048_TEST_SETUP();                                                                              \
  int main(int, char**) {                                                                              \
    std::cerr << "\n" << #app << "\n\n";                                                               \
    for (size_t i = 0; i < GetUnitTests().size(); ++i) {                                               \
      int _tmp = unit_test_failures;                                                                   \
      GetUnitTests()[i]->function();                                                                   \
      std::cerr << "Test [" << GetUnitTests()[i]->group << "] [" << GetUnitTests()[i]->name << "] - "; \
      std::cerr << (_tmp == unit_test_failures ? "PASSED" : "FAILED") << "\n";                         \
    }                                                                                                  \
    std::cerr << "\n" << unit_test_failures << " tests failed\n\n";                                    \
    return unit_test_failures;                                                                         \
  }

#endif
