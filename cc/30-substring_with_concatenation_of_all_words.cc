// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

// 151/176 test passed
/**
"pjzkrkevzztxductzzxmxsvwjkxpvukmfjywwetvfnujhweiybwvvsrfequzkhossmootkmyxgjgfordrpapjuunmqnxxdrqrfgkrsjqbszgiqlcfnrpjlcwdrvbumtotzylshdvccdmsqoadfrpsvnwpizlwszrtyclhgilklydbmfhuywotjmktnwrfvizvnmfvvqfiokkdprznnnjycttprkxpuykhmpchiksyucbmtabiqkisgbhxngmhezrrqvayfsxauampdpxtafniiwfvdufhtwajrbkxtjzqjnfocdhekumttuqwovfjrgulhekcpjszyynadxhnttgmnxkduqmmyhzfnjhducesctufqbumxbamalqudeibljgbspeotkgvddcwgxidaiqcvgwykhbysjzlzfbupkqunuqtraxrlptivshhbihtsigtpipguhbhctcvubnhqipncyxfjebdnjyetnlnvmuxhzsdahkrscewabejifmxombiamxvauuitoltyymsarqcuuoezcbqpdaprxmsrickwpgwpsoplhugbikbkotzrtqkscekkgwjycfnvwfgdzogjzjvpcvixnsqsxacfwndzvrwrycwxrcismdhqapoojegggkocyrdtkzmiekhxoppctytvphjynrhtcvxcobxbcjjivtfjiwmduhzjokkbctweqtigwfhzorjlkpuuliaipbtfldinyetoybvugevwvhhhweejogrghllsouipabfafcxnhukcbtmxzshoyyufjhzadhrelweszbfgwpkzlwxkogyogutscvuhcllphshivnoteztpxsaoaacgxyaztuixhunrowzljqfqrahosheukhahhbiaxqzfmmwcjxountkevsvpbzjnilwpoermxrtlfroqoclexxisrdhvfsindffslyekrzwzqkpeocilatftymodgztjgybtyheqgcpwogdcjlnlesefgvimwbxcbzvaibspdjnrpqtyeilkcspknyylbwndvkffmzuriilxagyerjptbgeqgebiaqnvdubrtxibhvakcyotkfonmseszhczapxdlauexehhaireihxsplgdgmxfvaevrbadbwjbdrkfbbjjkgcztkcbwagtcnrtqryuqixtzhaakjlurnumzyovawrcjiwabuwretmdamfkxrgqgcdgbrdbnugzecbgyxxdqmisaqcyjkqrntxqmdrczxbebemcblftxplafnyoxqimkhcykwamvdsxjezkpgdpvopddptdfbprjustquhlazkjfluxrzopqdstulybnqvyknrchbphcarknnhhovweaqawdyxsqsqahkepluypwrzjegqtdoxfgzdkydeoxvrfhxusrujnmjzqrrlxglcmkiykldbiasnhrjbjekystzilrwkzhontwmehrfsrzfaqrbbxncphbzuuxeteshyrveamjsfiaharkcqxefghgceeixkdgkuboupxnwhnfigpkwnqdvzlydpidcljmflbccarbiegsmweklwngvygbqpescpeichmfidgsjmkvkofvkuehsmkkbocgejoiqcnafvuokelwuqsgkyoekaroptuvekfvmtxtqshcwsztkrzwrpabqrrhnlerxjojemcxel"
["dhvf","sind","ffsl","yekr","zwzq","kpeo","cila","tfty","modg","ztjg","ybty","heqg","cpwo","gdcj","lnle","sefg","vimw","bxcb"]

*/
#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    Solution() = default;
    std::vector<int> FindSubString(std::string s,
                                   std::vector<std::string>& words) {
        std::sort(
            words.begin(), words.end(),
            [](std::string& left, std::string& right) { return left > right; });

        std::set<int> ret;
        do {
            std::string tmp = "";
            for (const auto& ptr : words) {
                tmp += ptr;
            }
            auto ret1 = AllSubString(s, tmp);

            ret.insert(ret1.begin(), ret1.end());
            // ret1 != -1 ? (void)(ret.emplace(ret1)) : (void)0;
        } while (std::prev_permutation(words.begin(), words.end()));
        std::vector<int> retvec(ret.begin(), ret.end());
        return retvec;
    }

   private:
    int IsOnlyOnce(const std::string& tofind, const std::string& candidate) {
        auto it = tofind.find(candidate);
        if (it != std::string::npos) {
            return tofind.substr(it, tofind.size()).find(candidate) !=
                           std::string::npos
                       ? it
                       : -1;
        }
        return -1;
    }
    static std::set<int> AllSubString(const std::string& tofind,
                                      const std::string& candidate,
                                      int index = 0) {
        auto it = tofind.find(candidate);
        if (it != std::string::npos) {
            const std::string substr = tofind.substr(it + 1, tofind.size());
            auto ret2 = AllSubString(substr, candidate, it + 1 + index);
            ret2.emplace(it + index);
            return ret2;
        }
        return std::set<int>{};
    }
};

TEST(_substringwith_concatenation_of_all_words, t1) {
    auto* s = new Solution();
    const std::string str = "wordgoodgoodgoodbestword";
    std::vector<std::string> words{"word", "good", "best", "word"};
    auto ret = s->FindSubString(str, words);

    const std::set<int> expect{};
    const std::set<int> retset(ret.begin(), ret.end());
    EXPECT_EQ(retset, expect);

    delete s;
}

TEST(_substringwith_concatenation_of_all_words, t2) {
    Solution s;
    const std::string str = "barfoofoobarthefoobarman";
    std::vector<std::string> words{"bar", "foo", "the"};
    auto ret = s.FindSubString(str, words);

    const std::set<int> expect{6, 9, 12};
    const std::set<int> retset(ret.begin(), ret.end());
    EXPECT_EQ(retset, expect);
}

TEST(_substringwith_concatenation_of_all_words, t3) {
    Solution s;
    const std::string str = "barfoothefoobarman";
    std::vector<std::string> words{"bar", "foo"};
    auto ret = s.FindSubString(str, words);

    const std::set<int> expect{0, 9};
    const std::set<int> retset(ret.begin(), ret.end());
    EXPECT_EQ(retset, expect);
}

TEST(_substringwith_concatenation_of_all_words, t4) {
    Solution s;
    const std::string str = "foobarfoobar";
    std::vector<std::string> words{"bar", "foo"};
    auto ret = s.FindSubString(str, words);

    const std::set<int> expect{0, 3, 6};
    const std::set<int> retset(ret.begin(), ret.end());
    EXPECT_EQ(retset, expect);
}

TEST(_substringwith_concatenation_of_all_words, t5) {
    Solution s;
    const std::string str = "aaaaaaaaaaaaaa";
    std::vector<std::string> words{"aa", "aa"};
    auto ret = s.FindSubString(str, words);

    const std::set<int> expect{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::set<int> retset(ret.begin(), ret.end());
    EXPECT_EQ(retset, expect);
}

}  // namespace
