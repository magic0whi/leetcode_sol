export module test;
import std;
template <typename T> concept Addable = requires(T a, T b) { a + b; };
template <typename T> concept Dividable = requires(T a, T b) { a / b; };
template <typename T> concept DivAddable = Addable<T> && Dividable<T>;

template <typename T, typename U> concept ExampleReq = requires(T x, U) {
  // simple requirement: expression must be valid
  x++;
  *x;
  // type requirement: T::value_type type must be a valid type
  typename T::value_type;
  typename std::vector<T>;
  // compound requirement: {expression}[noexcept][-> Concept];
  // {expression} -> Concept<A1, A2, ...> is equivalent to requires Concept<decltype((expression)), A1, A2, ...>
  { *x } noexcept;                                         // dereference must be noexcept
  { *x } noexcept -> std::same_as<typename T::value_type>; // dereference must return T::value_type
  // nested requirement: requires ConceptName<...>;
  requires Addable<T>;
};

template <typename T> requires Addable<T> // Use requires clause to constrain
T type_add(T a, T b) { return a + b; }
template <Addable T> // Directly use concept as template parameter (cleaner way)
T type_add2(T a, T b) { return a + b; }

template <typename T>
bool type_addable(T x) { // requires-expression render to a bool at compile-time
  if constexpr (Addable<T>) return true;
  // if constexpr (requires(T a, T b) { a + b; }) return true;
  else return false;
}

// CRTP
// Template template parameter can be constrained (Though not necessary)
// template <template <Addable This_Arg_Is_Optional> typename Templ_Derived, typename T>
template <template <typename T> requires Addable<T> typename Templ_Derived, typename T> // Requires clause also works)
class Base {
private:
  Base() {}
  friend Templ_Derived<T>;
public:
  void print_derived_add(T a, T b) {
    auto& derived{static_cast<Templ_Derived<T>&>(*this)};
    std::cout << derived.add(a, b) << '\n';
  }
};
export template <Addable T>
class Derived : public Base<Derived, T> {
public:
  T add(T a, T b) { return a + b; }
};
// STD concepts
// TODO: Supplement more
template <std::integral T>
constexpr void is_integral();

template <typename T>
constexpr std::string_view type_name() {
  std::string_view capt{std::source_location::current().function_name()};
  return {capt.cbegin() + capt.find('=') + 1, capt.cend() - 1};
}
