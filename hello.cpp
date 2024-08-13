#include <cassert>
#include <limits>
#include <type_traits>
import std;
import leetcode;
class Solution {
public:
  // https://leetcode.com/problems/contains-duplicate/
  bool containsDuplicate(std::vector<int> const& nums) noexcept {
    std::unordered_set<int> s;
    for (int const i : nums) {
      if (s.count(i)) return true;
      s.insert(i);
    }
    return false;
  }
  // https://leetcode.com/problems/valid-anagram/
  bool isAnagram(std::string const& s, std::string const& t) noexcept {
    if (s.size() != t.size()) return false;
    std::unordered_map<char, int> count;
    for (int i = 0; i < s.size(); i++)
      count[s[i]]++, count[t[i]]--;
    for (auto const& i : count)
      if (i.second != 0) return false;
    return true;
  }
  // https://leetcode.com/problems/two-sum
  std::vector<int> twoSum(std::vector<int> const& nums, int target) noexcept {
    std::unordered_map<int, int> num_idx;
    for (int i{}; int x : nums) {
      int y{target - x};                               // x = nums[i], y = target - nums[i]
      if (num_idx.contains(y)) return {i, num_idx[y]}; // If y already in Hashmap, return
      num_idx.insert({x, i++});                        // Otherwise insert to Hashmap
    }
    return {};
  }
  // https://leetcode.com/problems/group-anagrams/
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> const& strs) noexcept {
    std::unordered_map<std::string, std::vector<std::string>> count_strs;
    for (auto const& s : strs) {
      std::array<int, 26> k{};
      for (char const& c : s) k[c - 'a']++; // Construct char count as key
      count_strs[{k.cbegin(), k.cend()}].push_back(s);
    }
    std::vector<std::vector<std::string>> ret;
    ret.reserve(count_strs.size());
    for (auto const& p : count_strs) ret.push_back(p.second);
    return ret;
  }
  // https://leetcode.com/problems/top-k-frequent-elements/
  std::vector<int> topKFrequent(std::vector<int> const& nums, int k) noexcept {
    std::unordered_map<int, int> num_count;
    for (int const i : nums) num_count[i]++;
    std::vector<std::vector<int>> freqs(nums.size() + 1); // Ignore index 0, fill with initialized
    for (auto const& p : num_count) freqs[p.second].push_back(p.first);
    std::vector<int> ret;
    for (int i{static_cast<int>(nums.size())}; i > 0; i--)
      for (int const& l : freqs[i]) {
        ret.push_back(l);
        if (ret.size() == k) return ret;
      }
    return {};
  }
  // https://leetcode.com/problems/product-of-array-except-self/
  std::vector<int> productExceptSelf(std::vector<int> const& nums) noexcept {
    std::vector<int> ret(nums.size(), 1);
    // Pass 1: Calculate prefix
    for (int i{1}; i < nums.size(); i++) ret[i] = ret[i - 1] * nums[i - 1];
    // Pass 2 : Calculate output and postfix
    int postfix{nums[nums.size() - 1]};
    for (int i{static_cast<int>(nums.size()) - 2}; i >= 0; i--) {
      ret[i] *= postfix;
      postfix *= nums[i];
    }
    return ret;
  }
  // https://leetcode.com/problems/valid-sudoku/
  bool isValidSudoku(std::vector<std::vector<char>> const& board) noexcept {
    std::unordered_set<char> rows[9], cols[9], squares[9];
    for (int row{}; row < 9; row++)
      for (int col{}; col < 9; col++) {
        char c{board[row][col]};
        if (c == '.') continue;
        if (rows[row].count(c) || cols[col].count(c) ||
            squares[row / 3 * 3 + col / 3].count(c))
          return false;
        rows[row].insert(c);
        cols[col].insert(c);
        squares[row / 3 * 3 + col / 3].insert(c);
      }
    return true;
  }
  // https://leetcode.com/problems/longest-consecutive-sequence/
  int longestConsecutive(std::vector<int> const& nums) {
    std::unordered_set<int> set{nums.begin(), nums.end()};
    int longest{};
    for (int const& n : set)
      if (!set.contains(n - 1)) { // Found out start of the sequence
        int cur_len{1};
        while (set.contains(n + cur_len)) cur_len++; // Find to the last element of the sequence
        longest = std::max(longest, cur_len);
      }
    return longest;
  }
  // https://leetcode.com/problems/valid-palindrome/
  bool isPalindrome(std::string const& s) {
    for (int l{}, r{static_cast<int>(s.size()) - 1}; l < r; l++, r--) {
      auto not_alnum{[](char const& c) { return !(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9'); }};
      auto to_lower{[](char const& c) { return c > 'Z' ? c - ('a' - 'A') : c; }};
      while (not_alnum(s[l]) && l < r) l++; // Skip symbols and whitespaces
      while (not_alnum(s[r]) && l < r) r--;
      if (to_lower(s[l]) != to_lower(s[r])) return false;
    }
    return true;
  }
  // https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
  std::vector<int> twoSumII(std::vector<int> const& nums, int target) {
    int l{}, r{static_cast<int>(nums.size()) - 1};
    while (l < r) {
      int cur_sum{nums[l] + nums[r]};
      if (cur_sum > target) r--;
      else if (cur_sum < target) l++;
      else return {l + 1, r + 1}; // 1-indexed
    }
    return {};
  }
  // https://leetcode.com/problems/3sum/
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> ret;
    for (int x{}; x < nums.size(); x++) {            // x, y, z are indices
      if (nums[x] > 0) break;                        // Avoid nosense calc since positive nums[x] couldn't get result
      if (x > 0 && nums[x] == nums[x - 1]) continue; // x > 0 to excluse first loop
      // Two Sum II, nums[y] + nums[z] = -nums[x]
      for (int y{x + 1}, z{static_cast<int>(nums.size()) - 1}; y < z;) {
        if (nums[y] > -nums[x]) break; // Avoid nosense calc since it's sorted
        int cur_sum{nums[y] + nums[z]};
        if (cur_sum < -nums[x]) y++;
        else if (cur_sum > -nums[x]) z--;
        else {
          ret.push_back({nums[x], nums[y++], nums[z--]});
          while (nums[y] == nums[y - 1] && y < z) y++; // Prevent duplicate
        }
      }
    }
    return ret;
  }
  // https://leetcode.com/problems/container-with-most-water/
  int maxArea(std::vector<int> const& height) {
    int l{}, r{static_cast<int>(height.size()) - 1}, ret{};
    while (l < r) { // From outside to inside, goes lower side first
      ret = std::max(ret, (r - l) * std::min(height[l], height[r]));
      height[l] < height[r] ? l++ : r--;
    }
    return ret;
  }
  // https://leetcode.com/problems/trapping-rain-water/
  int trap(std::vector<int> const& height) {
    int l{}, r{static_cast<int>(height.size()) - 1}, l_max{height[0]}, r_max{height[r]}, ret{};
    while (l < r)
      if (l_max < r_max) {                    // Only the lower side matters, so from outside to inside, lower side first.
        l_max = std::max(l_max, height[++l]); // Try update max height, this also prevents negative trapped water
        ret += l_max - height[l];
      } else {
        r_max = std::max(r_max, height[--r]);
        ret += r_max - height[r];
      }
    return ret;
  }
  // https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
  int findMin(std::vector<int> const& nums) {
    int l{}, r{static_cast<int>(nums.size()) - 1}, ret{std::numeric_limits<int>::max()};
    while (l <= r) {
      int m{(l + r) / 2};
      ret = std::min(ret, nums[m]);
      if (nums[m] > nums[r]) l = m + 1; // In left subarray, min in right side
      else r = m - 1;                   // In right subarray, min either in left or current
    }
    return ret;
  }
};
template <class Res = std::chrono::milliseconds>
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
template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec) noexcept {
  os << '[';
  std::for_each(vec.cbegin(), vec.cend() - 1, [&os](T const& t) { os << t << ", "; });
  os << *(vec.cend() - 1) << ']';
  return os;
}
inline void leetcode_run() {
  Solution sol;
  Timer<std::chrono::microseconds> timer;
  std::println("Contains Duplicate: {}", sol.containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}));
  timer.count();

  std::println("Valid Anagram: {}", sol.isAnagram("anagram", "nagaram"));
  timer.count();

  std::println("Two Sum: {}", sol.twoSum({2, 7, 11, 15}, 9));
  timer.count();

  std::println("Group Anagrams: {}", sol.groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}));
  timer.count();

  std::println("Top K Frequent Elements: {}", sol.topKFrequent({1, 1, 1, 2, 2, 3}, 2));
  timer.count();

  std::println("Product of Array Except Self: {}", sol.productExceptSelf({-1, 1, 0, -3, 3}));
  timer.count();

  std::println("Valid Sudoku: {}",
               sol.isValidSudoku({{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}));
  timer.count();
  std::println("Valid Sudoku: {}",
               sol.isValidSudoku({{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}));
  timer.count();

  std::println("Longest Consecutive Sequence: {}", sol.longestConsecutive({100, 4, 200, 1, 3, 2}));
  timer.count();

  std::println("Valid Palindrome: {}", sol.isPalindrome("A man, a plan, a canal: Panama"));
  timer.count();
  std::println("Valid Palindrome: {}", sol.isPalindrome("race a car"));
  timer.count();

  std::println("Two Sum II - Input Array Is Sorted: {}", sol.twoSumII({2, 7, 11, 15}, 9));
  timer.count();
  {
    std::vector<int> three_sum_vec{-1, 0, 1, 2, -1, -4};
    timer.renew();
    std::println("3Sum: {}", sol.threeSum(three_sum_vec));
    timer.count();
  }
  std::println("Container With Most Water: {}", sol.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}));
  timer.count();

  std::println("Trapping Rain Water: {}", sol.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
  timer.count();

  std::println("Find Minimum in Rotated Sorted Array: {}", sol.findMin({4, 5, 6, 7, 0, 1, 2}));
  timer.count();
}
namespace custom {
constexpr double pow(double x, long n) noexcept {
  if (n > 0) return x * pow(x, n - 1);
  else return 1;
}
constexpr long fact(long n) noexcept {
  if (n > 1) return n * fact(n - 1);
  else return 1;
}
constexpr double cos(double x) noexcept {
  constexpr long precision{16L};
  double y{};
  for (auto n{0L}; n < precision; n += 2L) y += pow(x, n) / (n & 2L ? -fact(n) : fact(n));
  return y;
}
} // namespace custom
double gen_random() noexcept {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-1.0, 1.0);
  return dis(gen);
}
volatile double sink{}; // ensures a side effect

class Base {
public:
  Base() {}
  virtual ~Base() {}
};
class Derived : public Base {
  // ...
};

int main() {
  // Test the consistency with std::cos()
  // for (const auto x : {0.125, 0.25, 0.5, 1. / (1 << 26)})
  //   std::print("x = {1}\n{2:.{0}}\n{3:.{0}}\nIs equal: {4}\n", 53, x, std::cos(x), custom::cos(x), std::cos(x) == custom::cos(x));
  // auto benchmark = [](auto&& fun, auto rem) {
  //   auto const start{std::chrono::high_resolution_clock::now()};
  //   for (auto size{1UL}; size != 10'000'000UL; ++size) sink = fun(gen_random());
  //   std::chrono::duration<double> const diff{std::chrono::high_resolution_clock::now() - start};
  //   std::println("Time: {:f} sec {}", diff.count(), rem);
  // };
  // benchmark(custom::cos, "(custom::cos)");
  // benchmark([](double x) { return std::cos(x); }, "(std::cos)");
  int a{1};
  int& b{a};
  int& c{b};
  c = 2;
  std::println("a: {}", a);
  // leetcode_run();
}
