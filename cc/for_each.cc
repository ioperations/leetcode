
#include <gtest/gtest.h>

#include <cstdio>
#include <vector>

#include "for_each.hh"

namespace {
struct Statistic {
    int construct{0};
    int copy_construct{0};
    int move_construct{0};
    int copy_assignment{0};
    int move_assignment{0};
    int destruct{0};
};
thread_local Statistic g_statistic;

struct DummyClass {
    int v{0};

    DummyClass(int val) : v(val) { g_statistic.construct++; }
    DummyClass(const DummyClass& other) : v(other.v) { g_statistic.copy_construct++; }
    DummyClass(DummyClass&& other) noexcept : v(other.v) { g_statistic.move_construct++; }
    DummyClass& operator=(const DummyClass& other) {
        v = other.v;
        g_statistic.copy_assignment++;
        return *this;
    }
    DummyClass& operator=(DummyClass&& other) noexcept {
        v = other.v;
        g_statistic.move_assignment++;
        return *this;
    }
    ~DummyClass() { g_statistic.destruct++; }
};

class AutoResetStatistic {
   public:
    AutoResetStatistic() { Reset(); }
    ~AutoResetStatistic() { Reset(); }

   private:
    void Reset() const;
};

}  // namespace

void AutoResetStatistic::Reset() const {
    g_statistic.construct = 0;
    g_statistic.copy_construct = 0;
    g_statistic.move_construct = 0;
    g_statistic.copy_assignment = 0;
    g_statistic.move_assignment = 0;
    g_statistic.destruct = 0;
}

TEST(forV, DISABLEDBasicTest) {
    AutoResetStatistic const auto_reset_statistic;
    {
        std::vector<std::vector<std::vector<DummyClass>>> v{{{1}, {2, 3}},
                                                            {{4, 5, 6}}};

        DfsForEach(v, [&](DummyClass& v) { v.v += 100; });

        std::vector<int> flattern;
        DfsForEach(v, [&](auto&& v) { flattern.push_back(v.v); });

        DfsForEach(std::vector<DummyClass>{1},
                   [&](auto&& v) { printf("got v %d\n", v.v); });
        const std::vector<int> expected{101, 102, 103, 104, 105, 106};
        EXPECT_EQ(flattern, expected);
    }

    EXPECT_EQ(g_statistic.construct, 7);
    // EXPECT_EQ(g_statistic.copy_construct, 19);
    EXPECT_EQ(g_statistic.move_construct, 0);
    EXPECT_EQ(g_statistic.copy_assignment, 0);
    EXPECT_EQ(g_statistic.move_assignment, 0);
    // EXPECT_EQ(g_statistic.destruct, 26);
}
