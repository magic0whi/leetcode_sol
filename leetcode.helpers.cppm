export module leetcode:helpers;
// clang-format off
import std;
// clang-format on
export template <typename T> // Another way using function name with signature
consteval std::string_view type_name() noexcept {
  std::string_view capt{std::source_location::current().function_name()}; // Or "__PRETTY_FUNCTION__" for < c++20
  // e.g. "static_string type_name2() [T = const int &]"
  return {capt.cbegin() + capt.find('=') + 2, capt.cend() - 1};
}
export template <class Res = std::chrono::milliseconds> class Timer {
  using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                                   std::chrono::high_resolution_clock, std::chrono::steady_clock>;
private:
  std::chrono::time_point<Clock> const m_start_time;
  std::chrono::time_point<Clock> m_last_time;
public:
  Timer() noexcept : m_start_time(Clock::now()), m_last_time{Clock::now()} { std::println("Timer start!"); }
  ~Timer() {
    std::println("Time destructored, life time {}", std::chrono::duration_cast<Res>(Clock::now() - m_start_time));
  }
  inline void count() noexcept {
    std::println("Time took: {}", std::chrono::duration_cast<Res>(Clock::now() - m_last_time));
    m_last_time = Clock::now();
  }
  inline void renew() noexcept { m_last_time = Clock::now(); }
};
// No need anymore since C++23's std::print
// template <typename T>
// std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec) noexcept {
//   os << '[';
//   std::for_each(vec.cbegin(), vec.cend() - 1, [&os](T const& t) { os << t << ", "; });
//   os << *(vec.cend() - 1) << ']';
//   return os;
// }
