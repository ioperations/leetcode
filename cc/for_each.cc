#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "for_each.hh"

namespace {
struct Statistic {
    int m_construct{0};
    int m_copy_construct{0};
    int m_move_construct{0};
    int m_copy_assignment{0};
    int m_move_assignment{0};
    int m_destruct{0};
};

inline Statistic& GetStatistic() {
    static thread_local Statistic stat;
    return stat;
}

struct DummyClass {
    int m_v{0};

    DummyClass(int val) : m_v(val) { GetStatistic().m_construct++; }
    DummyClass(const DummyClass& other) : m_v(other.m_v) { GetStatistic().m_copy_construct++; }
    DummyClass(DummyClass&& other) noexcept : m_v(other.m_v) { GetStatistic().m_move_construct++; }
    DummyClass& operator=(const DummyClass& other) {
        m_v = other.m_v;
        GetStatistic().m_copy_assignment++;
        return *this;
    }
    DummyClass& operator=(DummyClass&& other) noexcept {
        m_v = other.m_v;
        GetStatistic().m_move_assignment++;
        return *this;
    }
    ~DummyClass() { GetStatistic().m_destruct++; }
};

class AutoResetStatistic {
   public:
    AutoResetStatistic() { Reset(); }
    AutoResetStatistic(const AutoResetStatistic&) = default;
    AutoResetStatistic(AutoResetStatistic&&) = default;
    AutoResetStatistic& operator=(const AutoResetStatistic&) = default;
    AutoResetStatistic& operator=(AutoResetStatistic&&) = default;
    ~AutoResetStatistic() { Reset(); }

   private:
    void Reset() const;
};

}  // namespace

void AutoResetStatistic::Reset() const {
    auto& g_statistic = GetStatistic();
    g_statistic.m_construct = 0;
    g_statistic.m_copy_construct = 0;
    g_statistic.m_move_construct = 0;
    g_statistic.m_copy_assignment = 0;
    g_statistic.m_move_assignment = 0;
    g_statistic.m_destruct = 0;
}

TEST(forV, DISABLEDBasicTest) {
    AutoResetStatistic const auto_reset_statistic;
    {
        std::vector<std::vector<std::vector<DummyClass>>> v{{{1}, {2, 3}},
                                                            {{4, 5, 6}}};

        DfsForEach(v, [&](DummyClass& v) { v.m_v += 100; });

        std::vector<int> flattern;
        DfsForEach(v, [&](auto&& v) { flattern.push_back(v.m_v); });

        DfsForEach(std::vector<DummyClass>{1},
                   [&](auto&& v) { std::cout << "got v " << v.m_v << "\n"; });
        const std::vector<int> expected{101, 102, 103, 104, 105, 106};
        EXPECT_EQ(flattern, expected);
    }

    EXPECT_EQ(GetStatistic().m_construct, 7);
    EXPECT_EQ(GetStatistic().m_move_construct, 0);
    EXPECT_EQ(GetStatistic().m_copy_assignment, 0);
    EXPECT_EQ(GetStatistic().m_move_assignment, 0);
}