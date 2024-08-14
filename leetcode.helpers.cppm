export module leetcode:helpers;
// clang-format off
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
_Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
import std;
_Pragma("GCC diagnostic pop");
// clang-format on
export template <class Res = std::chrono::milliseconds>
class Timer {
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
