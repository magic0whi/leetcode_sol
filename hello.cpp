// import leetcode;
// import linalg;
import std;
class String {
private:
  std::size_t m_size;
  char* m_data;
public:
  String() = default;
  String(std::string_view const str) : m_size(str.size()), m_data(new char[str.size()]) {
    std::println("Created!");
    std::copy_n(str.cbegin(), m_size, m_data);
  }
  // Copy constructor
  String(String const& other) : m_size(other.m_size), m_data(new char[other.m_size]) {
    std::println("Copied!");
    std::copy_n(other.m_data, m_size, m_data);
  }
  String(String&& older) noexcept : m_size(older.m_size), m_data{older.m_data} {
    std::println("Moved!");
    // There presents a problem: when the old one gets deleted, it's going to
    // delete the m_data here as well. So the major thing that we need to do is to
    // make the old one point to nothing.
    older.m_size = 0, older.m_data = nullptr;
  }
  String& operator=(String&& older) noexcept { // define move assignment
    if (this != &older) {
      delete[] m_data; // Move assignment assumes that there already exists data in currently class, we shall clean the current class
      std::println("Moved!\n");
      m_size = older.m_size, m_data = older.m_data;
      older.m_size = 0, older.m_data = nullptr;
    }
    return *this;
  }
  ~String() { std::println("Destroyed!"), delete[] m_data; }
  void print() {
    for (std::size_t i{}; i < m_size; i++) std::cout << m_data[i];
    std::println("");
  }
};

int main() {
  String apple{"Apple"}, dest;

  std::print("Apple: "), apple.print();
  std::print("Dest: "), dest.print();

  dest = std::move(apple); // With 'std::move()' invokes move assignment

  std::print("Apple: "), apple.print();
  std::print("Dest: "), dest.print();
}

// int main() { leetcode_run(); }
