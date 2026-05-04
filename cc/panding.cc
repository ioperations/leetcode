#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>

namespace {
enum class e_type : std::uint8_t { INT, STRING, NULL_ };

struct StackGrowth {
    int m_a{};
    std::array<char, 4096> m_padding{};
    union {
        int m_i;
        char* m_p;
    };
    e_type m_type{e_type::NULL_};
    int m_size = 0;

    StackGrowth() {
        m_p = m_padding.data();  // NOLINT cppcoreguidelines-pro-type-union-access
    }

   public:
    void append(const char* q) {
        const auto len = strlen(q);
        memcpy(m_p + m_size, q, len);  // NOLINT cppcoreguidelines-pro-bounds-pointer-arithmetic cppcoreguidelines-pro-type-union-access
        m_size = m_size + static_cast<int>(len);

        m_p[static_cast<size_t>(m_size)] = '\0';  // NOLINT cppcoreguidelines-pro-bounds-pointer-arithmetic cppcoreguidelines-pro-type-union-access
        m_type = e_type::STRING;
    }

    void SetInt(int q) {
        m_i = q;  // NOLINT cppcoreguidelines-pro-type-union-access
        m_type = e_type::INT;
    }

    [[nodiscard]] std::optional<std::string> GetString() const {
        if (m_type != e_type::STRING) {
            return {};
        }
        return std::string(m_p);  // NOLINT cppcoreguidelines-pro-type-union-access
    }

    [[nodiscard]] std::optional<int> GetInt() const {
        if (m_type != e_type::INT) {
            return {};
        }
        return m_i;  // NOLINT cppcoreguidelines-pro-type-union-access
    }
};
}  // namespace

TEST(T0, t1) {
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
