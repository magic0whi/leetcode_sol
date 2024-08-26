// import leetcode;
// import linalg;
import std;
template <class T> struct is_prvalue : std::true_type {};
template <class T> struct is_prvalue<T&> : std::false_type {};
template <class T> struct is_prvalue<T&&> : std::false_type {};

template <class T> struct is_lvalue : std::false_type {};
template <class T> struct is_lvalue<T&> : std::true_type {};
template <class T> struct is_lvalue<T&&> : std::false_type {};

template <class T> struct is_xvalue : std::false_type {};
template <class T> struct is_xvalue<T&> : std::false_type {};
template <class T> struct is_xvalue<T&&> : std::true_type {};

void f() {}
struct S {
  int a;
  enum e { A, B, C };
  S() {}
  S(int a) : a(a) {}
};
int main() {
  int a{42};
  int const& b{a};
  int&& c{std::move(a)};
  S s;
  // '(T)' treat T as an expression, otherwise decltype() gets its type
  static_assert(is_lvalue<decltype((f))>::value); // a function is lvalue,
  static_assert(is_lvalue<decltype((a))>::value && // variable names are lvalues
                is_lvalue<decltype((b))>::value && is_lvalue<decltype((c))>::value);

  static_assert(std::is_lvalue_reference_v<decltype(b)> && // Types and value categories are not correspondent
                std::is_rvalue_reference_v<decltype(c)>);

  static_assert(is_prvalue<decltype((42))>::value && is_prvalue<decltype((a + b))>::value &&
                is_prvalue<decltype((S{}))>::value);

  static_assert(is_prvalue<decltype((f()))>::value && // function's return value may be rvalue
                is_lvalue<decltype(([&a]() -> int& { return a; }()))>::value && // Unless its return type is lvalue reference
                is_prvalue<decltype((s.A))>::value // Member enumerators are rvalue
  );
  std::println("{}", (S{} = S{42}).a); // rvalue can be in left
  // f = []() {} // Also, lvalue don't mean it's assignable
}

// int main() { leetcode_run(); }
