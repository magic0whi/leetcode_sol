import std;
import leetcode;
import linalg;
int main() {
  std::vector<std::vector<int>> A{{1, 2},
                                  {3, 4}};
  std::vector<std::vector<int>> B{{5, 6},
                                  {7, 0}};
  try {
    std::println("{}", A * B);
  } catch (std::length_error const& e) { std::println("[Error] {}", e.what()); }

  constexpr std::array<std::array<int, 2>, 2> A2{{{1, 2}, {3, 4}}};
  constexpr std::array<std::array<int, 2>, 2> B2{{{5, 6}, {7, 8}}};
  try {
    std::println("{}", A2 * B2);
  } catch (std::length_error const& e) { std::println("[Error] {}", e.what()); }

  // leetcode_run();
}
