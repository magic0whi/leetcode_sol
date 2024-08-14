// clang-format off
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
_Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
import std;
_Pragma("GCC diagnostic pop")
import leetcode;
// clang-format on
struct Vector2 {
  float x, y;
};
union Point {
  struct Vector4 {
    float x, y, z, w;
  };
  struct Vector2x2 {
    Vector2 xy, zw;
  };
  Vector4 vec4;
  Vector2x2 vec2x2;
};
template <>
struct std::formatter<Point, char> {
  template <class ParseContext>
  constexpr auto parse(ParseContext const& ctx) { return ctx.begin(); } // Do noting, this methods use SFINAE
  template <class FmtContext>
  auto format(Point p, FmtContext& ctx) const {
    return std::format_to(ctx.out(), "[{}, {}, {}, {}]", p.vec4.x, p.vec4.y, p.vec4.z, p.vec4.w);
  }
};
template <>
struct std::formatter<Vector2, char> {
  template <class ParseContext>
  constexpr auto parse(ParseContext const& ctx) { return ctx.begin(); } // Do noting, this methods use SFINAE
  template <class FmtContext>
  auto format(Vector2 vec2, FmtContext& ctx) const {
    return std::format_to(ctx.out(), "[{}, {}]", vec2.x, vec2.y);
  }
};
int main() {
  std::println("{}", std::vector<int>{2, 3, 3, 4});
  Point pt{{1.0f, 2.0f, 3.0f, 4.0f}};
  std::println("{}", pt);
  std::print("{}", pt.vec2x2.xy), std::println("{}", pt.vec2x2.zw);
  std::println("------------------");
  pt.vec4.z = 500.0f;
  std::println("{}", pt);
  std::print("{}", pt.vec2x2.xy), std::println("{}", pt.vec2x2.zw);
  leetcode_run();
}
