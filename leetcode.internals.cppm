module leetcode:impl;
// clang-format off
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
_Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
import std;
_Pragma("GCC diagnostic pop");
// clang-format on
class MinStack {
private:
  std::stack<std::pair<int, int>> m_stk;
public:
  void push(int val) noexcept { m_stk.push({val, m_stk.empty() ? val : std::min(val, m_stk.top().second)}); }
  void pop() noexcept { m_stk.pop(); }
  int top() noexcept { return m_stk.top().first; }
  int getMin() noexcept { return m_stk.top().second; }
};
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
    for (int i = 0; i < static_cast<int>(s.size()); i++)
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
        if (static_cast<int>(ret.size()) == k) return ret;
      }
    return {};
  }
  // https://leetcode.com/problems/product-of-array-except-self/
  std::vector<int> productExceptSelf(std::vector<int> const& nums) noexcept {
    std::vector<int> ret(nums.size(), 1);
    // Pass 1: Calculate prefix
    for (int i{1}; i < static_cast<int>(nums.size()); i++) ret[i] = ret[i - 1] * nums[i - 1];
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
  int longestConsecutive(std::vector<int> const& nums) noexcept {
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
  bool isPalindrome(std::string const& s) noexcept {
    for (int l{}, r{static_cast<int>(s.size()) - 1}; l < r; l++, r--) {
      auto not_alnum{[](char const& c) { return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')); }};
      auto to_lower{[](char const& c) { return c > 'Z' ? c - ('a' - 'A') : c; }};
      while (not_alnum(s[l]) && l < r) l++; // Skip symbols and whitespaces
      while (not_alnum(s[r]) && l < r) r--;
      if (to_lower(s[l]) != to_lower(s[r])) return false;
    }
    return true;
  }
  // https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
  std::vector<int> twoSumII(std::vector<int> const& nums, int target) noexcept {
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
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) noexcept {
    sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> ret;
    for (int x{}; x < static_cast<int>(nums.size()); x++) { // x, y, z are indices
      if (nums[x] > 0) break;                               // Avoid nosense calc since positive nums[x] couldn't get result
      if (x > 0 && nums[x] == nums[x - 1]) continue;        // x > 0 to excluse first loop
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
  int maxArea(std::vector<int> const& height) noexcept {
    int l{}, r{static_cast<int>(height.size()) - 1}, ret{};
    while (l < r) { // From outside to inside, goes lower side first
      ret = std::max(ret, (r - l) * std::min(height[l], height[r]));
      height[l] < height[r] ? l++ : r--;
    }
    return ret;
  }
  // https://leetcode.com/problems/trapping-rain-water/
  int trap(std::vector<int> const& height) noexcept {
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
  int findMin(std::vector<int> const& nums) noexcept {
    int l{}, r{static_cast<int>(nums.size()) - 1}, ret{std::numeric_limits<int>::max()};
    while (l <= r) {
      int m{(l + r) / 2};
      ret = std::min(ret, nums[m]);
      if (nums[m] > nums[r]) l = m + 1; // In left subarray, min in right side
      else r = m - 1;                   // In right subarray, min either in left or current
    }
    return ret;
  }
  // https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
  int maxProfit(std::vector<int> const& prices) noexcept {
    int lowest{prices[0]}, ret{};
    for (int const p : prices)                         // lowest is left pointer, p is right pointer in the window
      if (p > lowest) ret = std::max(ret, p - lowest); // Whether profitable, try update the return value
      else lowest = p;                                 // Or found new history lowest, window shrink
    return ret;
  }
  // https://leetcode.com/problems/longest-substring-without-repeating-characters/
  int lengthOfLongestSubstring(std::string const& s) noexcept {
    std::unordered_set<char> char_set;
    int ret{};
    for (int l{}, r{}; r < static_cast<int>(s.size()); r++) {
      while (char_set.find(s[r]) != char_set.end()) char_set.erase(s[l++]); // If already in hashset, shrink the window's left to that char
      char_set.insert(s[r]);
      ret = std::max(ret, r - l + 1); // Update the size of the sliding window
    }
    return ret;
  }
  // https://leetcode.com/problems/permutation-in-string/
  bool checkInclusion(std::string const& s1, std::string const& s2) noexcept {
    if (s1.size() > s2.size()) return false;
    std::array<int, 26> s1_count{0}, s2_count{0};
    for (int i{0}; i < static_cast<int>(s1.size()); i++) // Construct a char count array for s1 as well as starting `s1.size()` of s2
      s1_count[s1[i] - 'a']++, s2_count[s2[i] - 'a']++;
    int matches{0}; // We don't need compare full hashmap each loop
    for (int i{0}; i < 26; i++)
      if (s1_count[i] == s2_count[i]) matches++;                                                // Window startup
    for (int l{0}, r{static_cast<int>(s1.size())}; r < static_cast<int>(s2.size()); r++, l++) { // Start r at the end of s1, window size fixed
      if (matches == 26) return true;
      // Right-side process
      int i{s2[r] - 'a'};
      if (s1_count[i] == s2_count[i]++) matches--; // If before same, now it +1, so matches -1
      if (s1_count[i] == s2_count[i]) matches++;
      // Left-side process
      i = s2[l] - 'a';
      if (s1_count[i] == s2_count[i]--) matches--;
      if (s1_count[i] == s2_count[i]) matches++; // If before bigger 1 and now same, matches +1
    }
    return matches == 26;
  }
  // https://leetcode.com/problems/minimum-window-substring/
  std::string minWindow(std::string const& s, std::string const& t) noexcept {
    if (s.size() < t.size()) return "";
    std::unordered_map<char, int> t_diff;
    for (char c : t) t_diff[c]++;
    int diff{static_cast<int>(t_diff.size())}, min_l{}, min_len{std::numeric_limits<int>::max()};
    for (int l{}, r{}; r < static_cast<int>(s.size()); r++) {
      if (--t_diff[s[r]] == 0) diff--; // diff only -1 at condition just met, ignore further same chars
      for (; diff == 0; l++)           // If now valid window, shrinking window from left
        if (++t_diff[s[l]] > 0) {      // diff only +1 at condition just no longer satisfy, and try update minimum length
          diff++;
          if (r - l + 1 < min_len) min_l = l, min_len = r - l + 1;
        }
    }
    return min_len != std::numeric_limits<int>::max() ? s.substr(min_l, min_len) : "";
  }
  // https://leetcode.com/problems/sliding-window-maximum/
  std::vector<int> maxSlidingWindow(std::vector<int> const& nums, int k) noexcept {
    std::vector<int> ret(nums.size() - k + 1); // Initialize with size "nums.size()-k-1" and fill with integer's default zeros, otherwise operations like "ret[i] = 114514" don't work
    std::deque<int> q;                         // Dual end queue, stores indices
    int state{k - 1};
    for (int l{}, r{}; r < static_cast<int>(nums.size()); r++) {
      while (!q.empty() && nums[q.back()] < nums[r]) q.pop_back(); // Let queue be monotonic descending
      q.push_back(r);
      if (l > q.front()) q.pop_front(); // Remove out-bounded element in queue
      // if (r >= k - 1) ret[l++] = nums[q.front()]; // Recording maximum start from index k-1
      switch (state) {
      case 0:
        ret[l++] = nums[q.front()];
        break;
      default:
        state--;
      }
    }
    return ret;
  }
  bool isValid(std::string const& s) noexcept {
    std::stack<char> open_parens;
    std::unordered_map<char, char> close_open = {{')', '('}, {'}', '{'}, {']', '['}};
    for (char const c : s)
      if (!close_open.contains(c)) open_parens.push(c);                                 // If opening parenthese, store to stack.
      else if (open_parens.empty() || open_parens.top() != close_open[c]) return false; // If closing parenthese, check whether stack is empty or a corresponding opening parenthese in the top of stack.
      else open_parens.pop();
    return open_parens.empty();
  }
  int evalRPN(std::vector<std::string> const& tokens) noexcept {
    std::stack<int> stk;
    auto pop{[&stk]() noexcept { int tmp{stk.top()}; stk.pop(); return tmp; }};
    for (std::string const& c : tokens)
      if (c == "+") stk.push(pop() + pop());
      else if (c == "-") stk.push(-pop() + pop());
      else if (c == "*") stk.push(pop() * pop());
      else if (c == "/") {
        int b{pop()}, a{pop()};
        stk.push(static_cast<int>(a / b));
      } else stk.push(stoi(c));
    return stk.top();
  }
  // https://leetcode.com/problems/search-in-rotated-sorted-array/
  int search(std::vector<int> const& nums, int target) {
    for (int l{}, r{static_cast<int>(nums.size()) - 1}; l <= r;) {
      int m{(l + r) / 2};
      if (nums[m] == target) return m;
      if (nums[m] < nums[l])                                  // In right sub array, so certainly right-hand is monotonic ascending
        if (nums[m] < target && target <= nums[r]) l = m + 1; // Check whether target is in right-hand side
        else r = m - 1;
      else // In left sub array
        if (nums[l] <= target && target < nums[m]) r = m - 1;
        else l = m + 1;
    }
    return -1;
  }
};
// template <typename T>
// std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec) noexcept {
//   os << '[';
//   std::for_each(vec.cbegin(), vec.cend() - 1, [&os](T const& t) { os << t << ", "; });
//   os << *(vec.cend() - 1) << ']';
//   return os;
// }
