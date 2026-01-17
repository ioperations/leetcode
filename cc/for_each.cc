
#include <gtest/gtest.h>

#include <cstdio>
#include <vector>

#include "for_each.hh"

namespace {
struct Statisc {
    int construct{0};
    int copyConstruct{0};
    int moveConstruct{0};
    int copyAssignment{0};
    int moveAssignment{0};
    int destruct{0};
};
thread_local Statisc g_statistic;

struct DummyClass {
    DummyClass(int v) {
        g_statistic.construct++;
        this->v = v;
    }
    DummyClass(const DummyClass& other) {
        this->v = other.v;
        g_statistic.copyConstruct++;
    }
    DummyClass(DummyClass&& other) {
        this->v = other.v;
        g_statistic.moveConstruct++;
    }
    DummyClass& operator=(const DummyClass& other) {
        this->v = other.v;
        g_statistic.copyAssignment++;
        return *this;
    }
    DummyClass& operator=(DummyClass&& other) {
        this->v = other.v;
        g_statistic.moveAssignment++;
        return *this;
    }
    ~DummyClass() { g_statistic.destruct++; }
    int v = 0;
};

class AutoResetStatistic {
   public:
    AutoResetStatistic() { Reset(); }
    ~AutoResetStatistic() { Reset(); }

   private:
    void Reset() {
        g_statistic.construct = 0;
        g_statistic.copyConstruct = 0;
        g_statistic.moveConstruct = 0;
        g_statistic.copyAssignment = 0;
        g_statistic.moveAssignment = 0;
        g_statistic.destruct = 0;
    }
};

}  // namespace

TEST(for_each, DISABLED_basic_test) {
    AutoResetStatistic auto_reset_statistic;
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
    EXPECT_EQ(g_statistic.copyConstruct, 19);
    EXPECT_EQ(g_statistic.moveConstruct, 0);
    EXPECT_EQ(g_statistic.copyAssignment, 0);
    EXPECT_EQ(g_statistic.moveAssignment, 0);
    EXPECT_EQ(g_statistic.destruct, 26);
}
