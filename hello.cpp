// import leetcode;
// import linalg;
import std;
template <typename T> consteval std::string_view type_name() noexcept {
  std::string_view capt{std::source_location::current().function_name()};
  return {capt.cbegin() + capt.find('=') + 2, capt.cend() - 1};
}

auto f(auto&&) { std::println("f(T&&) matched"); }
auto f(auto const&) { std::println("f(T const&) matched"); }

template <typename T> void wrapper(T&& arg) {
  f<T>(arg); // Forwarding reference will let it invokes f(T&&), so we need explicitly specify f<T>.
  f<T>(std::forward<T>(arg)); // Perfect forwarding
}
int main() {
  wrapper(1);
  int a{1};
  wrapper(a); // Compiler will deduce to 'int&', equivalent to wrapper(auto(a))
  wrapper(std::move(a));
  std::println(
    "{}, {}", type_name<decltype(std::move(a))>(), // std::decay gets the type as if passing to function arguments
    type_name<std::decay_t<decltype(std::move(a))>>()); // (array of 'T' gets 'T*'; function types gets function pointer type; remove cv-qualifier).
}

// int main() { leetcode_run(); }
