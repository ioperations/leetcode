/*
A transformation sequence from word beginWord to word endWord using a
dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk
such that:

    Every adjacent pair of words differs by a single letter.
    Every si for 1 <= i <= k is in wordList. Note that beginWord does not need
    to be in wordList.
    sk == endWord

Given two words, beginWord and endWord, and a
dictionary wordList, return all the shortest transformation sequences from
beginWord to endWord, or an empty list if no such sequence exists. Each sequence
should be returned as a list of the words [beginWord, s1, s2, ..., sk].*/

#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
   public:
    bool Able(string s, string t) {
        if (s.length() != t.length()) return false;
        int c = 0;
        for (int i = 0; i < (int)s.length(); i++) c += (s[i] != t[i]);
        return c == 1;
    }
    void Bfs(vector<vector<int>>& g, vector<vector<int>>& parent, int n, int sr,
             int ds) {
        vector<int> dist(n, 1005);
        queue<int> q;
        q.push(sr);
        parent[sr] = {-1};
        dist[sr] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int u : g[x]) {
                if (dist[u] > dist[x] + 1) {
                    dist[u] = dist[x] + 1;
                    q.push(u);
                    parent[u].clear();
                    parent[u].push_back(x);
                } else if (dist[u] == dist[x] + 1)
                    parent[u].push_back(x);
            }
        }
    }
    void ShortestPaths(vector<vector<int>>& paths, vector<int>& path,
                       vector<vector<int>>& parent, int node) {
        if (node == -1) {
            paths.push_back(path);
            return;
        }
        for (auto u : parent[node]) {
            path.push_back(u);
            ShortestPaths(paths, path, parent, u);
            path.pop_back();
        }
    }
    vector<vector<string>> FindLadders(string begin_wordd, string end_word,
                                       vector<string>& word_list) {
        int n = word_list.size(), sr = -1, ds = -1;
        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (word_list[i] == begin_wordd) sr = i;
            if (word_list[i] == end_word) ds = i;
        }
        if (ds == -1) return ans;
        if (sr == -1) {
            word_list.emplace(word_list.begin(), begin_wordd);
            sr = 0;
            ds++;
            n++;
        }
        vector<vector<int>> g(n, vector<int>()), paths;
        vector<vector<int>> parent(n, vector<int>());
        vector<int> path;
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (Able(word_list[i], word_list[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
        Bfs(g, parent, n, sr, ds);
        ShortestPaths(paths, path, parent, ds);
        for (auto u : paths) {
            vector<string> now;
            for (int i = 0; i < (int)u.size() - 1; i++)
                now.push_back(word_list[u[i]]);
            reverse(now.begin(), now.end());
            now.push_back(word_list[ds]);
            ans.push_back(now);
        }
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string begin_word = "hit", end_word = "cog";
    vector<string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
    vector<vector<string>> output = {{"hit", "hot", "dot", "dog", "cog"},
                                     {"hit", "hot", "lot", "log", "cog"}};
    set<vector<string>> output_set(output.begin(), output.end());
    // Explanation: There are 2 shortest transformation sequences:
    // "hit" -> "hot" -> "dot" -> "dog" -> "cog"
    // "hit" -> "hot" -> "lot" -> "log" -> "cog"
    Solution sl;
    auto ret = sl.FindLadders(begin_word, end_word, word_list);
    set<vector<string>> set(ret.begin(), ret.end());
    EXPECT_EQ(set, output_set);
}

TEST(t0, t2) {
    string begin_word = "hit", end_word = "cog";
    vector<string> word_list = {"hot", "dot", "dog", "lot", "log"};
    vector<vector<string>> output = {};
    // Explanation: The endWord "cog" is not in wordList, therefore there is no
    // valid transformation sequence.
    Solution sl;
    auto ret = sl.FindLadders(begin_word, end_word, word_list);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string begin_word = "aaaaa", end_word = "ggggg";
    vector<string> word_list = {
        "aaaaa", "caaaa", "cbaaa", "daaaa", "dbaaa", "eaaaa", "ebaaa", "faaaa",
        "fbaaa", "gaaaa", "gbaaa", "haaaa", "hbaaa", "iaaaa", "ibaaa", "jaaaa",
        "jbaaa", "kaaaa", "kbaaa", "laaaa", "lbaaa", "maaaa", "mbaaa", "naaaa",
        "nbaaa", "oaaaa", "obaaa", "paaaa", "pbaaa", "bbaaa", "bbcaa", "bbcba",
        "bbdaa", "bbdba", "bbeaa", "bbeba", "bbfaa", "bbfba", "bbgaa", "bbgba",
        "bbhaa", "bbhba", "bbiaa", "bbiba", "bbjaa", "bbjba", "bbkaa", "bbkba",
        "bblaa", "bblba", "bbmaa", "bbmba", "bbnaa", "bbnba", "bboaa", "bboba",
        "bbpaa", "bbpba", "bbbba", "abbba", "acbba", "dbbba", "dcbba", "ebbba",
        "ecbba", "fbbba", "fcbba", "gbbba", "gcbba", "hbbba", "hcbba", "ibbba",
        "icbba", "jbbba", "jcbba", "kbbba", "kcbba", "lbbba", "lcbba", "mbbba",
        "mcbba", "nbbba", "ncbba", "obbba", "ocbba", "pbbba", "pcbba", "ccbba",
        "ccaba", "ccaca", "ccdba", "ccdca", "cceba", "cceca", "ccfba", "ccfca",
        "ccgba", "ccgca", "cchba", "cchca", "cciba", "ccica", "ccjba", "ccjca",
        "cckba", "cckca", "cclba", "cclca", "ccmba", "ccmca", "ccnba", "ccnca",
        "ccoba", "ccoca", "ccpba", "ccpca", "cccca", "accca", "adcca", "bccca",
        "bdcca", "eccca", "edcca", "fccca", "fdcca", "gccca", "gdcca", "hccca",
        "hdcca", "iccca", "idcca", "jccca", "jdcca", "kccca", "kdcca", "lccca",
        "ldcca", "mccca", "mdcca", "nccca", "ndcca", "occca", "odcca", "pccca",
        "pdcca", "ddcca", "ddaca", "ddada", "ddbca", "ddbda", "ddeca", "ddeda",
        "ddfca", "ddfda", "ddgca", "ddgda", "ddhca", "ddhda", "ddica", "ddida",
        "ddjca", "ddjda", "ddkca", "ddkda", "ddlca", "ddlda", "ddmca", "ddmda",
        "ddnca", "ddnda", "ddoca", "ddoda", "ddpca", "ddpda", "dddda", "addda",
        "aedda", "bddda", "bedda", "cddda", "cedda", "fddda", "fedda", "gddda",
        "gedda", "hddda", "hedda", "iddda", "iedda", "jddda", "jedda", "kddda",
        "kedda", "lddda", "ledda", "mddda", "medda", "nddda", "nedda", "oddda",
        "oedda", "pddda", "pedda", "eedda", "eeada", "eeaea", "eebda", "eebea",
        "eecda", "eecea", "eefda", "eefea", "eegda", "eegea", "eehda", "eehea",
        "eeida", "eeiea", "eejda", "eejea", "eekda", "eekea", "eelda", "eelea",
        "eemda", "eemea", "eenda", "eenea", "eeoda", "eeoea", "eepda", "eepea",
        "eeeea", "ggggg", "agggg", "ahggg", "bgggg", "bhggg", "cgggg", "chggg",
        "dgggg", "dhggg", "egggg", "ehggg", "fgggg", "fhggg", "igggg", "ihggg",
        "jgggg", "jhggg", "kgggg", "khggg", "lgggg", "lhggg", "mgggg", "mhggg",
        "ngggg", "nhggg", "ogggg", "ohggg", "pgggg", "phggg", "hhggg", "hhagg",
        "hhahg", "hhbgg", "hhbhg", "hhcgg", "hhchg", "hhdgg", "hhdhg", "hhegg",
        "hhehg", "hhfgg", "hhfhg", "hhigg", "hhihg", "hhjgg", "hhjhg", "hhkgg",
        "hhkhg", "hhlgg", "hhlhg", "hhmgg", "hhmhg", "hhngg", "hhnhg", "hhogg",
        "hhohg", "hhpgg", "hhphg", "hhhhg", "ahhhg", "aihhg", "bhhhg", "bihhg",
        "chhhg", "cihhg", "dhhhg", "dihhg", "ehhhg", "eihhg", "fhhhg", "fihhg",
        "ghhhg", "gihhg", "jhhhg", "jihhg", "khhhg", "kihhg", "lhhhg", "lihhg",
        "mhhhg", "mihhg", "nhhhg", "nihhg", "ohhhg", "oihhg", "phhhg", "pihhg",
        "iihhg", "iiahg", "iiaig", "iibhg", "iibig", "iichg", "iicig", "iidhg",
        "iidig", "iiehg", "iieig", "iifhg", "iifig", "iighg", "iigig", "iijhg",
        "iijig", "iikhg", "iikig", "iilhg", "iilig", "iimhg", "iimig", "iinhg",
        "iinig", "iiohg", "iioig", "iiphg", "iipig", "iiiig", "aiiig", "ajiig",
        "biiig", "bjiig", "ciiig", "cjiig", "diiig", "djiig", "eiiig", "ejiig",
        "fiiig", "fjiig", "giiig", "gjiig", "hiiig", "hjiig", "kiiig", "kjiig",
        "liiig", "ljiig", "miiig", "mjiig", "niiig", "njiig", "oiiig", "ojiig",
        "piiig", "pjiig", "jjiig", "jjaig", "jjajg", "jjbig", "jjbjg", "jjcig",
        "jjcjg", "jjdig", "jjdjg", "jjeig", "jjejg", "jjfig", "jjfjg", "jjgig",
        "jjgjg", "jjhig", "jjhjg", "jjkig", "jjkjg", "jjlig", "jjljg", "jjmig",
        "jjmjg", "jjnig", "jjnjg", "jjoig", "jjojg", "jjpig", "jjpjg", "jjjjg",
        "ajjjg", "akjjg", "bjjjg", "bkjjg", "cjjjg", "ckjjg", "djjjg", "dkjjg",
        "ejjjg", "ekjjg", "fjjjg", "fkjjg", "gjjjg", "gkjjg", "hjjjg", "hkjjg",
        "ijjjg", "ikjjg", "ljjjg", "lkjjg", "mjjjg", "mkjjg", "njjjg", "nkjjg",
        "ojjjg", "okjjg", "pjjjg", "pkjjg", "kkjjg", "kkajg", "kkakg", "kkbjg",
        "kkbkg", "kkcjg", "kkckg", "kkdjg", "kkdkg", "kkejg", "kkekg", "kkfjg",
        "kkfkg", "kkgjg", "kkgkg", "kkhjg", "kkhkg", "kkijg", "kkikg", "kkljg",
        "kklkg", "kkmjg", "kkmkg", "kknjg", "kknkg", "kkojg", "kkokg", "kkpjg",
        "kkpkg", "kkkkg", "ggggx", "gggxx", "ggxxx", "gxxxx", "xxxxx", "xxxxy",
        "xxxyy", "xxyyy", "xyyyy", "yyyyy", "yyyyw", "yyyww", "yywww", "ywwww",
        "wwwww", "wwvww", "wvvww", "vvvww", "vvvwz", "avvwz", "aavwz", "aaawz",
        "aaaaz"};

    vector<vector<string>> output = {
        {"aaaaa", "aaaaz", "aaawz", "aavwz", "avvwz", "vvvwz", "vvvww",
         "wvvww", "wwvww", "wwwww", "ywwww", "yywww", "yyyww", "yyyyw",
         "yyyyy", "xyyyy", "xxyyy", "xxxyy", "xxxxy", "xxxxx", "gxxxx",
         "ggxxx", "gggxx", "ggggx", "ggggg"}};
    // Explanation: The endWord "cog" is not in wordList, therefore there
    // is no valid transformation sequence.
    Solution sl;
    auto ret = sl.FindLadders(begin_word, end_word, word_list);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
