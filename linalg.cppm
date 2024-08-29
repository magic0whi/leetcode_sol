export module linalg;
import std;

export std::vector<std::vector<int>> operator*(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
  if (A[0].size() != B.size()) throw std::out_of_range("The matrix A's columns should be same with B's rows");
  std::vector<std::vector<int>> ret{A.size(), std::vector<int>(B[0].size())};
  for (std::size_t i{}; i < A.size(); i++)
    for (std::size_t j{}; j < B[0].size(); j++) // Column lengthdepend on B's column length
      for (std::size_t k{}; k < B.size(); k++) ret[i][j] += A[i][k] * B[k][j];
  return ret;
}
export template <typename A, typename B> constexpr auto operator*(A a, B b) {
  if (a[0].size() != b.size()) throw std::length_error("The matrix A's columns should be same with B's rows");
  std::array<std::array<int, b[0].size()>, a.size()> ret;
  for (std::size_t i{}; i < a.size(); i++)
    for (std::size_t j{}; j < b[0].size(); j++) // Column lengthdepend on B's column length
      for (std::size_t k{}; k < b.size(); k++) ret[i][j] += a[i][k] * b[k][j];
  return ret;
}
