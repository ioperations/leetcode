#include <gtest/gtest.h>

#include <cstring>
#include <optional>
#include <stack>
#include <string>
enum EType { INT, STRING, NULL_ };

struct stack_growth {
    int a;
    char padding[4096];
    union {
        int i;
        char *p;
    };
    EType type{NULL_};
    int size = 0;

    stack_growth() {
        // padding
        p = padding;
    }

   public:
    void append(const char *q) {
        auto len = strlen(q);
        memcpy(p + size, q, len);
        size = size + len;

        p[size + 1] = '\0';
        type = STRING;
    }

    void SetInt(int q) {
        i = q;
        type = INT;
    }

    std::optional<std::string> getString() const {
        if (type != STRING) {
            return std::optional<std::string>();
        }
        return p;
    }

    std::optional<int> getInt() const {
        if (type != INT) {
            return std::optional<int>();
        }
        return i;
    }
};

TEST(t0, t1) {
    stack_growth stack_growth;

    stack_growth.append("TEST");
    EXPECT_EQ("TEST", *stack_growth.getString());

    stack_growth.append("Hello");
    EXPECT_EQ("TESTHello", *stack_growth.getString());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
