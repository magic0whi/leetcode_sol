export module leetcode;
export import :helpers;
// clang-format off
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
_Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
import std;
_Pragma("GCC diagnostic pop")
import :impl;
// clang-format on
export inline void leetcode_run() {
  auto check{[](bool b) {
    if (!b) throw std::runtime_error("Wrong Answer");
    std::println("Accepted");
  }};
  Solution sol;
  Timer<std::chrono::microseconds> timer;
  std::print("Contains Duplicate: ");
  check(sol.containsDuplicate({1, 2, 3, 1}) == true && //
        sol.containsDuplicate({1, 2, 3, 4}) == false && //
        sol.containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}) == true);
  timer.count();

  std::print("Valid Anagram: ");
  check(sol.isAnagram("anagram", "nagaram") == true && //
        sol.isAnagram("rat", "car") == false);
  timer.count();

  std::print("Two Sum: ");
  {
    check(is_permutation(sol.twoSum({2, 7, 11, 15}, 9), std::vector{0, 1}) && //
          is_permutation(sol.twoSum({3, 2, 4}, 6), std::vector{1, 2}) && //
          is_permutation(sol.twoSum({3, 3}, 6), std::vector{0, 1}));
    timer.count();
  }

  std::println("Group Anagrams: ");
  {
    check(is_permutation(sol.groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}),
                         std::vector<std::vector<std::string>>{{"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}}) &&
          is_permutation(sol.groupAnagrams({""}), std::vector<std::vector<std::string>>{{""}}) &&
          is_permutation(sol.groupAnagrams({{"a"}}), std::vector<std::vector<std::string>>{{"a"}}));
    timer.count();
  }

  std::println("Top K Frequent Elements: {}", sol.topKFrequent({1, 1, 1, 2, 2, 3}, 2)), timer.count();

  std::println("Product of Array Except Self: {}", sol.productExceptSelf({-1, 1, 0, -3, 3})), timer.count();

  std::println("Valid Sudoku: {}", sol.isValidSudoku({{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                                      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                                      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                                      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                                      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                                      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                                      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                                      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                                      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}));
  timer.count();
  std::println("Valid Sudoku: {}", sol.isValidSudoku({{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                                      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                                      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                                      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                                      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                                      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                                      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                                      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                                      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}));
  timer.count();

  std::println("Longest Consecutive Sequence: {}", sol.longestConsecutive({100, 4, 200, 1, 3, 2})), timer.count();

  std::println("Valid Palindrome: {}", sol.isPalindrome("A man, a plan, a canal: Panama")), timer.count();
  std::println("Valid Palindrome: {}", sol.isPalindrome("race a car")), timer.count();

  std::println("Two Sum II - Input Array Is Sorted: {}", sol.twoSumII({2, 7, 11, 15}, 9)), timer.count();
  {
    std::vector<int> three_sum_vec{-1, 0, 1, 2, -1, -4};
    timer.renew();
    std::println("3Sum: {}", sol.threeSum(three_sum_vec)), timer.count();
  }
  std::println("Container With Most Water: {}", sol.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7})), timer.count();

  std::println("Trapping Rain Water: {}", sol.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1})), timer.count();

  std::println("Best Time to Buy and Sell Stock: {}", sol.maxProfit({7, 1, 5, 3, 6, 4})), timer.count();

  std::println("Longest Substring Without Repeating Characters: {}", sol.lengthOfLongestSubstring("abcabcbb")),
    timer.count();

  std::println("Permutation in String: {}", sol.checkInclusion("ab", "eidbaooo")), timer.count();
  std::println("Permutation in String: {}", sol.checkInclusion("ab", "eidboaoo")), timer.count();

  std::println("Minimum Window Substring: \"{}\"", sol.minWindow("ADOBECODEBANC", "ABC")), timer.count();
  std::println("Minimum Window Substring: \"{}\"", sol.minWindow("a", "aa")), timer.count();

  std::println("Sliding Window Maximum: {}", sol.maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3)), timer.count();

  std::println("Valid Parentheses: {}", sol.isValid("()[]{}")), timer.count();
  std::println("Valid Parentheses: {}", sol.isValid("(]")), timer.count();
  {
    Solution::MinStack stk;
    timer.renew();
    stk.push(-2), stk.push(0), stk.push(-3);
    std::println("Min Stack: {}, {}", stk.getMin(), (stk.pop(), stk.pop(), stk.getMin())), timer.count();
  }
  std::println("Evaluate Reverse Polish Notation: {}", sol.evalRPN({"2", "1", "+", "3", "*"})), timer.count();
  std::println("Evaluate Reverse Polish Notation: {}", sol.evalRPN({"4", "13", "5", "/", "+"})), timer.count();
  std::println("Evaluate Reverse Polish Notation: {}",
               sol.evalRPN({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"})),
    timer.count();

  std::println("Find Minimum in Rotated Sorted Array: {}", sol.findMin({4, 5, 6, 7, 0, 1, 2})), timer.count();
  std::println("Search in Rotated Sorted Array {}", sol.search({4, 5, 6, 7, 0, 1, 2}, 0)), timer.count();
  {
    Solution::TimeMap timemap;
    timer.renew();
    timemap.set("foo", "bar", 1);
    std::println("Time Based Key-Value Store: {}, {}", timemap.get("foo", 1), timemap.get("foo", 3)), timer.count();
    timemap.set("foo", "bar2", 4);
    std::println("Time Based Key-Value Store: {}, {}", timemap.get("foo", 4), timemap.get("foo", 5)), timer.count();
  }
  std::println("Median of Two Sorted Arrays: {}", sol.findMedianSortedArrays({1, 2, 3, 4}, {1, 2, 3, 4, 5, 6, 7, 8})),
    timer.count();
  std::println("Median of Two Sorted Arrays: {}",
               sol.findMedianSortedArrays({1, 2, 3, 4}, {1, 2, 3, 4, 5, 6, 7, 8, 9})),
    timer.count();
  std::println("Median of Two Sorted Arrays: {}", sol.findMedianSortedArrays({1, 3}, {2})), timer.count();
  std::println("Median of Two Sorted Arrays: {}", sol.findMedianSortedArrays({1, 2}, {3, 4})), timer.count();
  {
    auto list{new Solution::ListNode{1, 2, 3, 4, 5}};
    std::println("Reverse Linked List"), timer.renew();
    list = sol.reverseList(list);
    timer.count();
    std::print("Reverse Linked List: {}", list->val);
    for (Solution::ListNode* head{list->next}; head; head = head->next) std::print(" {}", head->val);
    std::println("");
    delete list;
    timer.count();
  }
  {
    auto list1{new Solution::ListNode{1, 2, 4}}, list2{new Solution::ListNode{1, 3, 4}};
    std::println("Merge Two Sorted Lists"), timer.renew();
    auto merged_list{sol.mergeTwoLists(list1, list2)};
    std::print("Merged Linked List: {}", merged_list->val);
    for (Solution::ListNode* head{merged_list->next}; head; head = head->next) std::print(" {}", head->val);
    std::println("");
    delete merged_list;
  }
  {
    auto list{new Solution::ListNode{1, 2, 3, 4}};
    std::println("Reorder List (1/2)"), timer.renew();
    sol.reorderList(list);
    timer.count();
    std::print("ReorderLinked List:");
    for (Solution::ListNode* cur{list}; int i : {1, 4, 2, 3}) {
      if (!(cur->val == i)) throw std::runtime_error("Wrong Answer");
      std::print(" {}", cur->val), cur = cur->next;
    }
    std::println("");
    delete list;

    list = new Solution::ListNode{1, 2, 3, 4, 5};
    std::println("Reorder List (2/2)"), timer.renew();
    sol.reorderList(list);
    timer.count();
    std::print("ReorderLinked List:");
    for (Solution::ListNode* cur{list}; int i : {1, 5, 2, 4, 3}) {
      if (!(cur->val == i)) throw std::runtime_error("Wrong Answer");
      std::print(" {}", cur->val), cur = cur->next;
    }
    std::println("");
    delete list;
  }
}
