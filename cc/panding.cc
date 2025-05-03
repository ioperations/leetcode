#include <gtest/gtest.h>

#include <cstring>
#include <optional>
#include <string>
enum e_type { INT, STRING, NULL_ };

struct StackGrowth {
  int m_a{};
  char m_padding[4096]{};
  union {
    int m_i;
    char* m_p;
  };
  e_type m_type{NULL_};
  int m_size = 0;

  StackGrowth() {
    // padding
    m_p = m_padding;
  }

 public:
  void append(const char* q) {
    auto len = strlen(q);
    memcpy(m_p + m_size, q, len);
    m_size = m_size + len;

    m_p[m_size] = '\0';
    m_type = STRING;
  }

  void SetInt(int q) {
    m_i = q;
    m_type = INT;
  }

  [[nodiscard]] std::optional<std::string> GetString() const {
    if (m_type != STRING) {
      return {};
    }
    return m_p;
  }

  [[nodiscard]] std::optional<int> GetInt() const {
    if (m_type != INT) {
      return {};
    }
    return m_i;
  }
};

TEST(t0, t1) {
  StackGrowth stack_growth;

  stack_growth.append("TEST");
  EXPECT_EQ("TEST", *stack_growth.GetString());

  stack_growth.append("Hello");
  EXPECT_EQ("TESTHello", *stack_growth.GetString());
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
