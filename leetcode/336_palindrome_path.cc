/*

Given a list of unique words, return all the pairs of the distinct indices (i,
j) in the given list, so that the concatenation of the two words words[i] +
words[j] is a palindrome.

*/

#include <algorithm>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> PalindromePairs(vector<string>& words) {
        vector<vector<int>> ret;

        for (int i = 0; i < (int)words.size() - 1; i++) {
            for (int j = i + 1; j < (int)words.size(); j++) {
                if (IsPalindromePairs(words, i, j)) {
                    ret.push_back({i, j});
                }
                if (IsPalindromePairs(words, j, i)) {
                    ret.push_back({j, i});
                }
            }
        }

        return ret;
    }
    bool IsPalindromePairs(vector<string>& words, int i, int j) {
        // pass

        string tmp = words[i] + words[j];

        int begin = 0;
        int end = tmp.size() - 1;

        while (begin < end) {
            if (tmp[begin] == tmp[end]) {
                begin++;
                end--;
            } else {
                return false;
            }
        }

        return true;
    }

   private:
    vector<vector<int>> res;
    struct TrieNode {
        TrieNode() : word_index(-1), children(26, nullptr) {}
        int word_index;
        vector<TrieNode*> children;
        ~TrieNode() {
            for (auto& ptr : children) {
                delete ptr;
            }
        }
    };

    void Insert(TrieNode* root, string& word, int word_index) {
        for (auto c : word) {
            int index = c - 'a';
            if (root->children[index] == nullptr) {
                root->children[index] = new TrieNode();
            }
            root = root->children[index];
        }

        root->word_index = word_index;
    }

    bool IsPalindrome(const string& s) {
        int i = 0;
        int j = s.size() - 1;

        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            ++i;
            --j;
        }

        return true;
    }

    void Dfs(TrieNode* root, vector<int>& long_word_indices, string& str) {
        if (root == nullptr) {
            return;
        }

        // palindrome + reverse_word
        if (root->word_index != -1 && !str.empty() && IsPalindrome(str)) {
            long_word_indices.push_back(root->word_index);
        }

        for (int i = 0; i < 26; ++i) {
            str.push_back('a' + i);
            Dfs(root->children[i], long_word_indices, str);
            str.pop_back();
        }
    }

    void Find(TrieNode* root, string& word, int word_index) {
        // word is longer than its corresponding word.
        int index = 0;
        while (index < (int)word.length() && root != nullptr) {
            root = root->children[word[index++] - 'a'];
            if (root != nullptr && root->word_index != -1) {
                if (root->word_index != word_index &&
                    IsPalindrome(word.substr(index))) {
                    res.push_back({word_index, root->word_index});
                }
            }
        }

        // word is shorter than its corresponding word.
        if (index == (int)word.length()) {
            string str;
            vector<int> long_word_indices;
            Dfs(root, long_word_indices, str);
            for (int i : long_word_indices) {
                res.push_back({word_index, i});
            }
        }
    }

   public:
    vector<vector<int>> PalindromePairsV1(vector<string>& words) {
        TrieNode* root = new TrieNode();

        // Create Trie with reversed words
        for (int i = 0; i < (int)words.size(); ++i) {
            string reversed_word = words[i];
            reverse(reversed_word.begin(), reversed_word.end());
            Insert(root, reversed_word, i);
        }

        for (int i = 0; i < (int)words.size(); ++i) {
            string& word = words[i];
            // word is palindrome
            if (root->word_index != -1 && !word.empty() && IsPalindrome(word)) {
                res.push_back({i, root->word_index});
            }
            Find(root, word, i);
        }

        delete root;
        return res;
    }

   private:
    bool CheckPalindrome(string& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }

   public:
    vector<vector<int>> PalindromePairsV2(vector<string>& words) {
        unordered_map<string, int> rev;
        string temp;

        int n = words.size();

        for (int i = 0; i < n; i++) {
            temp = words[i];
            reverse(temp.begin(), temp.end());

            rev[temp] = i;
        }

        vector<vector<int>> ans;

        if (rev.find("") != rev.end()) {
            for (int i = 0; i < n; i++) {
                if (rev[""] == i) {
                    continue;
                }

                if (CheckPalindrome(words[i])) {
                    ans.push_back({i, rev[""]});
                }
            }
        }

        string left, right, word;

        for (int i = 0; i < n; i++) {
            word = words[i];

            left = "";
            right = word;

            int sz = word.size();

            for (int j = 0; j < sz; j++) {
                left.push_back(word[j]);
                right.erase(0, 1);

                if (rev.find(left) != rev.end() && rev[left] != i &&
                    CheckPalindrome(right)) {
                    ans.push_back({i, rev[left]});
                }

                if (rev.find(right) != rev.end() && rev[right] != i &&
                    CheckPalindrome(left)) {
                    ans.push_back({rev[right], i});
                }
            }
        }

        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> words = {"abcd", "dcba", "lls", "s", "sssll"};
    vector<vector<int>> output = {{0, 1}, {1, 0}, {3, 2}, {2, 4}};
    // Explanation: The palindromes are
    // ["dcbaabcd","abcddcba","slls","llssssll"]

    set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PalindromePairs(words);

    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    ret = sl.PalindromePairsV1(words);

    set<vector<int>> ret_set1(ret.begin(), ret.end());
    EXPECT_EQ(ret_set1, output_set);
    ret = sl.PalindromePairsV1(words);

    set<vector<int>> ret_set2(ret.begin(), ret.end());
    EXPECT_EQ(ret_set2, output_set);
}

TEST(t0, t2) {
    vector<string> words = {"bat", "tab", "cat"};
    vector<vector<int>> output = {{0, 1}, {1, 0}};
    // Explanation: The palindromes are
    // The palindromes are ["battab","tabbat"]

    set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PalindromePairs(words);

    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    ret = sl.PalindromePairsV1(words);

    set<vector<int>> ret_set1(ret.begin(), ret.end());
    EXPECT_EQ(ret_set1, output_set);
    ret = sl.PalindromePairsV1(words);

    set<vector<int>> ret_set2(ret.begin(), ret.end());
    EXPECT_EQ(ret_set2, output_set);
}

vector<string> words = {"efajifg",
                        "gcbdgjjgbbgihcf",
                        "diaeabiaeeg",
                        "behbhhjba",
                        "hejb",
                        "aca",
                        "ddcccif",
                        "cecaafceefha",
                        "jeaceiceejbhcdafgeic",
                        "ijcjgjhacifaaadfcja",
                        "cbagfechifbfahhhhj",
                        "fid",
                        "jhc",
                        "hjdd",
                        "cceiedfhifdabdfif",
                        "jjibgchedhcbdhbgf",
                        "hejeaihcbccjeaichefd",
                        "ijbji",
                        "gfhegfhddbg",
                        "agcbhccgjb",
                        "cfheiejjhhj",
                        "a",
                        "jdcjdighicdjccbfhbc",
                        "fjahjfegdjd",
                        "jhgeiaccjb",
                        "hbiefbfhajhddfca",
                        "jaeifbifjahhjjgehhb",
                        "fhjba",
                        "hheccjaejbaididgbfj",
                        "ie",
                        "dhhhebjhbaahahj",
                        "jgahfceibahg",
                        "jfi",
                        "cjbchhe",
                        "icich",
                        "cebjdfiheiegbacdeee",
                        "jah",
                        "gidghccchfc",
                        "e",
                        "ceacdhecijfgfhji",
                        "g",
                        "dbfdeh",
                        "hifaa",
                        "dacb",
                        "gddgbfejhf",
                        "ga",
                        "gecddd",
                        "d",
                        "cfifaf",
                        "becfgedhci",
                        "dceafecadehibid",
                        "hcchfcaeiehhbfedc",
                        "ajbgdbhaicbgeidda",
                        "gdid",
                        "hcd",
                        "fdiiafdc",
                        "ieihaaafdegjddbbacf",
                        "aaihbdae",
                        "bagbcbifjc",
                        "adfeefjdh",
                        "cjjdgfcefejefjdi",
                        "eijbjbjhjadefhhbehia",
                        "ihbdcgdfcjefceeeafcd",
                        "bcfjfebfiihe",
                        "cgdheehgieaijgdc",
                        "iajghf",
                        "dag",
                        "abjebcf",
                        "afiaejcdff",
                        "jbfgdidbaf",
                        "hcbfbibjfggfbfdjh",
                        "ibchhiecbddcffgbdbgc",
                        "ejhibba",
                        "faibadhg",
                        "dbaheegafed",
                        "bdddgeacgg",
                        "djdefghffcdhjaj",
                        "haghejc",
                        "agdaja",
                        "fhheijbedabiiajc",
                        "gdgajih",
                        "bcgdaadefbdihjai",
                        "ddbihjfbegeeb",
                        "cdcadcjj",
                        "fda",
                        "gjfejegehcaghahe",
                        "cgjjaad",
                        "fcecegagbaf",
                        "feibd",
                        "feiahhcgabejgaf",
                        "i",
                        "ecibajbedac",
                        "dfgcigjbffbdfcfaihah",
                        "dfgfhaihbgdg",
                        "giiiha",
                        "jhfadiefbfchi",
                        "eeacehcjjfiiiag",
                        "ijbhijhjbgc",
                        "ceigbjbjiagehcgcihf",
                        "dff",
                        "hdhgjhbc",
                        "ifjhdfjejifbeiid",
                        "chfi",
                        "ebaecc",
                        "aebicidj",
                        "chgec",
                        "agjdbbcchbei",
                        "jcbeeeijiidaacja",
                        "chfcddfgaibdhi",
                        "edjiaaebc",
                        "bgahcfeaheigfd",
                        "jjdbebaifhchgcjbb",
                        "cfhjfjjdggfac",
                        "edgciiheae",
                        "aciii",
                        "fgfficdjdedb",
                        "cabddgbchheedhjcgc",
                        "edhbbbechfhebicgbhd",
                        "gaid",
                        "ihddgfagbhjiad",
                        "jaaaidfdhehf",
                        "acfieecdeac",
                        "jaecaifhdgg",
                        "hiacdgbgjcbijbjaccg",
                        "gciafdidfdach",
                        "jbadhabi",
                        "ajifhedcjhgfhijieage",
                        "egaec",
                        "ida",
                        "dgiiaiaadh",
                        "jbgjib",
                        "bggfjiadddegdjeggdeb",
                        "chfaibffhcjihja",
                        "gda",
                        "abfehjacjgacgiica",
                        "iegcb",
                        "ahgihfbjdhhcahgggghj",
                        "dbacgfbajce",
                        "ibbajdjedhb",
                        "iaaaaigafeghdjdbe",
                        "eigiaheacjjideaibhci",
                        "jeb",
                        "cagacfaddjcag",
                        "jeagfgdahieehbgiedjb",
                        "aefeciigjafjig",
                        "bcffffiaijaajbafi",
                        "ijfbeajbjfhddcjd",
                        "giaihafaiiibicffah",
                        "f",
                        "hb",
                        "addj",
                        "hfaheccje",
                        "gihfcjgibjbhjihcej",
                        "edjigajefiffaja",
                        "dciibfhbcajcijjchf",
                        "dgefcigfbhjfg",
                        "ijbijdcaaifcj",
                        "ggbjbajibbjahghfgg",
                        "agcafbieebdfabaagh",
                        "fai",
                        "agaeaeccj",
                        "cibdedcbcdfjfhah",
                        "hdaiiccd",
                        "afcjggacegfhiifcch",
                        "ddcedccc",
                        "j",
                        "hghhbfid",
                        "je",
                        "fjhfhfbecbafjhebcef",
                        "cf",
                        "jh",
                        "ecifidj",
                        "cj",
                        "gdihaaadgacjhcgcb",
                        "dfddccfhhaefgficgd",
                        "faddaebhh",
                        "acch",
                        "ifjd",
                        "hegjd",
                        "aha",
                        "dccai",
                        "cdjdfjgjfjfaffddjdcd",
                        "jeghgaaaehbidgchfaf",
                        "djiibee",
                        "ibga",
                        "djdjbjfdg",
                        "ei",
                        "cjihfj",
                        "iaj",
                        "hjai",
                        "gidjjdfjdefjhebaebd",
                        "gggcccfd",
                        "acbefehjbjfjeedb",
                        "afaehccdhhdjahicjhd",
                        "effdgggc",
                        "h",
                        "gabgbdgedgd",
                        "agihddfggiheaeffigb",
                        "haeh",
                        "cafgf",
                        "abafcfbfadfiifcd",
                        "bbfccga",
                        "ijcdhhihfbggbhaajj",
                        "fdgei",
                        "dgebgbhheaccbefajdbg",
                        "ffiefjhggiiccfbgaj",
                        "hceafcjaghigdgei",
                        "ggadibagfcjcjbcj",
                        "habjcdjgiadgag",
                        "bgf",
                        "jbdgbbg",
                        "cgbbc",
                        "jibjhejf",
                        "jehadadecacfaiej",
                        "ci",
                        "beaghdiidicchjcjjif",
                        "fgfib",
                        "jbhe",
                        "ebbibaaidbdiihhb",
                        "jfacbbfj",
                        "decjcicdfjbgbfchhfa",
                        "dbgjbachadeechfabaja",
                        "fjacifjcbbeii",
                        "bjdfa",
                        "adcgcbieh",
                        "hfdicdfi",
                        "ef",
                        "aabgebcehfej",
                        "dd",
                        "jgf",
                        "chfhaedjedihcehb",
                        "dhecaheddajig",
                        "dbhcajaj",
                        "igcaddjjjcjgfccheb",
                        "eiadbhdaggjcce",
                        "dbhfjcagghdhgi",
                        "bhbhhbhdjafbfbaf",
                        "fhefhcgdhadachhjg",
                        "efgj",
                        "bgbdbdjdajgjcifbie",
                        "ja",
                        "iia",
                        "fihiadfjghafdifh",
                        "jebcbfaddbbagi",
                        "hjceafggiffijcd",
                        "bgcebdiebiicd",
                        "gcdgac",
                        "iddgdfjhag",
                        "ffbdgbhiebgae",
                        "cjbbaab",
                        "dgiagjbajcijgfhc",
                        "chcjdjg",
                        "eddciihhhhj",
                        "chaaidfieaea",
                        "ebedeib",
                        "gdhf",
                        "cicaabjha",
                        "gdegb",
                        "aecajgfibec",
                        "aafdhdeihcajebijijag",
                        "ecdjhhhfj",
                        "djfa",
                        "gffeaaaba",
                        "jbideccjgebbiicbjhd",
                        "acdbdieji",
                        "ic",
                        "fif",
                        "fcdeefigijbfgceca",
                        "bbacafbhd",
                        "jgijaajifhjgb",
                        "gaj",
                        "gbgadacfeiiefgf",
                        "hdhaihdjjedf",
                        "hfigjba",
                        "gijcaaihibhdfhfadj",
                        "ieicebcgihghbge",
                        "icjiigiadehibjaaihf",
                        "ecfbjfg",
                        "jijgafi",
                        "decjjbjje",
                        "adgdhefiihhe",
                        "icchjgbajfafgci",
                        "jgjdafjeag",
                        "igehebfedhb",
                        "hafiic",
                        "ecdcfhhfead",
                        "igbihiefafb",
                        "da",
                        "ihjjbedjej",
                        "cfgigfafecbdcfbjchbf",
                        "hfjbjbeafaghhejh",
                        "iibgbgjgfaiejgf",
                        "cbjiaideeiagibfegaah",
                        "jiheehgbfdbfd",
                        "egdgahcgaifhacac",
                        "jgggeedegbachffb",
                        "cegfc",
                        "cgj",
                        "fefciacacdfidebja",
                        "fhjgc",
                        "deeeiadgibideaeif",
                        "ejdc",
                        "bebajabbfbhdiah",
                        "cajhjefe",
                        "gbiggjjjichgigdba",
                        "deafdji",
                        "hggejgd",
                        "efaaifdhgjjhfd",
                        "fdigb",
                        "hf",
                        "gcbdc",
                        "jhejbegdfa",
                        "chfcihceja",
                        "idcbgcj",
                        "hbihachd",
                        "cfegfefi",
                        "ebjaidf",
                        "ieejabigaje",
                        "aaedhdiejegiajhhg",
                        "ji",
                        "hjaijgdeaicii",
                        "hhfababcj",
                        "ifhjgeabgfjcaadceii",
                        "bbheecbihhhiecbb",
                        "afdbeacjibgfci",
                        "jf",
                        "iaabe",
                        "dfjgffih",
                        "ehjdhjcbdj",
                        "bh",
                        "hdibegjhadhhcdeijh",
                        "ggifbgaibfbbegj",
                        "eghccaj",
                        "bhbdj",
                        "igdjbbaf",
                        "gic",
                        "deideihaadj",
                        "fiea",
                        "ahjeegciccbfhechfege",
                        "dabcejjechacejhb",
                        "gcifiicabfce",
                        "dgfjjcbddahdgjgdd",
                        "jgejcbfjabjbi",
                        "jb",
                        "hddeifjcgccejg",
                        "babdfadgbegfgd",
                        "gcceaddedibgbaiei",
                        "cbf",
                        "de",
                        "hbfjddj",
                        "fbcgfdaehgigcjejjbfc",
                        "icjcdegdgecbdiggf",
                        "aggfggcd",
                        "eiaafifcdeeicebgf",
                        "fhiiijccjeafaceegaf",
                        "eiefgedbhajegifi",
                        "bciaaiejgifgad",
                        "jbcjcfgegiadfc",
                        "iaabhccggiaihgiggccj",
                        "bca",
                        "ebhdcbbicc",
                        "hddfjdfbfdbc",
                        "gdaaiijecefgjh",
                        "cdhdajgdbdcf",
                        "egadhaecdadcehfjjji",
                        "fecbagiigdecbiii",
                        "jdbfeaic",
                        "diefbcedjjghfc",
                        "bhaigcjja",
                        "dfghc",
                        "c",
                        "icijh",
                        "hffeegfi",
                        "fdd",
                        "hifgijbbeadeegai",
                        "ieghfcjf",
                        "egegjgfhffa",
                        "iichjbhagafejhifaf",
                        "dabjehadjecfafdheeh",
                        "jacedbaahjcfca",
                        "jfbejigaidjgdcfcec",
                        "jcbadidadeehadjgj",
                        "hdhggcij",
                        "bhjeibihdfhfbci",
                        "eie",
                        "bjhcdfiafjhje",
                        "bcd",
                        "bacfbhejeghe",
                        "fjjbdhh",
                        "gcajiad",
                        "adgiehfgebjgibdcfg",
                        "feeeaejbejgeaaehae",
                        "eccbecdjdffbdjh",
                        "cceegbbjj",
                        "bhjjbe",
                        "ehdjeiciaacib",
                        "ebhadi",
                        "hdehfcj",
                        "ahjfaaiifgghegfddejd",
                        "hg",
                        "ccdhcfgj",
                        "beeidgjiiggegcceabgi",
                        "jicfjchdgbgjdejbab",
                        "abehbcebfjcg",
                        "eicaccfbfjehhb",
                        "ibiicjgba",
                        "febefb",
                        "jdib",
                        "ccei",
                        "jfggbegabebeejgg",
                        "ajefff",
                        "ejchdhjhfbbgia",
                        "ddiaajfeahdeb",
                        "jgbcbaecejadcjefc",
                        "gaheabjhcdchhbjefgid",
                        "iaafhce",
                        "aibehcddeffe",
                        "ibcedbcbjhdfbgehbc",
                        "hcjeihd",
                        "djeegigaefbfcg",
                        "bbdbjdegjbdfjggebfgb",
                        "jbehjdcjcegagg",
                        "gdebaddcejhee",
                        "eccihb",
                        "iggibifeejdafcd",
                        "ajfahahjbccaibehahj",
                        "adgffeedjj",
                        "cihdahfeibegchaj",
                        "dbheeih",
                        "gbijbd",
                        "efjfhdhefjihhcjb",
                        "defcecibeaehfj",
                        "fdfhjeeibdhieabef",
                        "iichjgffb",
                        "fehbdbhbhjhbe",
                        "hjfaebhhcbhedi",
                        "aabeiahhieabjf",
                        "ffacaighffi",
                        "iegibcd",
                        "gihbjcccjhfejdbieiif",
                        "cfhahhehecajdggcih",
                        "bfdg",
                        "chbhbcdabjda",
                        "aahj",
                        "efe",
                        "b",
                        "ibdee",
                        "bhficjdgacdcahbcbdfb",
                        "ddihih",
                        "fhheiijbdededfi",
                        "gbehihgiejeihd",
                        "hie",
                        "ig",
                        "efehijidcjc",
                        "faeejecjhaiib",
                        "gfij",
                        "bbieif",
                        "bhjeac",
                        "hcabecfedfddhih",
                        "hjdhhdjdbjabbicjd",
                        "dga",
                        "cabbh",
                        "ifcieigd",
                        "ghceacabgcfedhhbd",
                        "dj",
                        "bceeeiececf",
                        "dbibjgdcaiidhhi",
                        "gjhigije",
                        "egaacidjdifbaiejcbib",
                        "jcgghefhhabecibj",
                        "ebiiiibbbd",
                        "gddjdhgdhgag",
                        "febehdfahgdidi",
                        "ehjiadh",
                        "ddehajciebcdhg",
                        "iiiieghddehihgjc",
                        "gbhgji",
                        "jfaajecdfa",
                        "fifaacbiaiibc",
                        "aiacbgbdjhbbbf",
                        "bfghdj",
                        "ccgeg",
                        "ddhcdi",
                        "dagciicagfjdbihci",
                        "ddgahdbhfb",
                        "gadcgdjgffee",
                        "afh",
                        "edjggbgbgbiag",
                        "jefegiaihfggc",
                        "bjfffcigjjd",
                        "abccjfbbhehaaefj",
                        "gaidhbbehjfabiga",
                        "fgdfajde",
                        "ghbdiahcbb",
                        "ffgbgcdgiacibjjeghih",
                        "hfaf",
                        "ghdchjbiih",
                        "bibdj",
                        "fdbac",
                        "cfchfadcfdgg",
                        "igbbdciecaeacad",
                        "dg",
                        "afdfghbhjhi",
                        "aedcifcdcbhfdg",
                        "jeca",
                        "cdabdffeebiaaagbhacf",
                        "hhffcjhdcbdbh",
                        "agjddh",
                        "jbfbcdbcib",
                        "dgaefgfjehhdcfdi",
                        "dhhhbcjj",
                        "iaeiafgafcjjgcijcbj",
                        "iiaahcccbgibafdacg",
                        "fggcjddeb",
                        "fdgiachci",
                        "eabgceb",
                        "ajeg",
                        "afeadjfidjgi",
                        "gfjadhfc",
                        "dbbcgfjaicheiif",
                        "ejbdjdb",
                        "bddbecif",
                        "ehdbhcbihgf",
                        "ggbeefhjf",
                        "ehc",
                        "higefdfjbej",
                        "daefab",
                        "ghjgcfhcdceddaajdbh",
                        "cdahfchbejhfbcad",
                        "iddicahbej",
                        "efcaihcefce",
                        "jafgbifbefeaaj",
                        "bgag",
                        "af",
                        "fbbffhadhgif",
                        "jajfbjcihcedeiaeda",
                        "bebchdfhcjehfjfafif",
                        "heeddfb",
                        "cibfh",
                        "jbe",
                        "bjjgejeghiefegicche",
                        "eebie",
                        "gcdgfgbajgacgcdegah",
                        "ahije",
                        "badbidbadjacbi",
                        "fhchdjjiibhbci",
                        "ecigifegjbfgch",
                        "jgdhdhbbcihgbig",
                        "ejdha",
                        "cefbd",
                        "ajjhbaiciggaebfjcj",
                        "ideed",
                        "ciihh",
                        "jabgihhifbjagaced",
                        "jehajjjjhdabeajbhgc",
                        "cdejgegfffcbca",
                        "aiheighbd",
                        "fhecehii",
                        "gcbaccjhaidbidde",
                        "iag",
                        "jbghigfgechjiiadbjbg",
                        "hedhbcjedgi",
                        "ffdccdcegbgcbagcac",
                        "cegjcjaeaihcgid",
                        "ahfdfffacchb",
                        "ifgfajiafjfai",
                        "di",
                        "fjdjhcfachaih",
                        "dddgbhhhjbjdcfecdcfe",
                        "bedhfj",
                        "chcigcfjhgfefbeh",
                        "bffdejjghgehgdbiada",
                        "ijaeigdecjccaafghi",
                        "gijafbedgfj",
                        "djfcdfjebjj",
                        "bgaghafjhaeidhahib",
                        "agage",
                        "ij",
                        "bfhjb",
                        "bbfadbfib",
                        "jihabeaajda",
                        "bjeegdjeade",
                        "jgiggcjcfdbajjihdhad",
                        "ghgiigjgabbjiagjh",
                        "ahaieacbedhide",
                        "afjgbfafiegbbcigdef",
                        "fchffdhcddgfgjahc",
                        "fbgeijegbdjehajbbgai",
                        "hejdgejfbjfhe",
                        "dbgeaghdhhf",
                        "gihgfjefdehg",
                        "aiajdejhajgced",
                        "djehgdggfeibfbdba",
                        "cchcebjecgeaffgchi",
                        "ahhjjeigjgeefe",
                        "ddbgbjdc",
                        "fjeageifibbcecefi",
                        "gacfa",
                        "fhajfjaeaeaddcei",
                        "jihdacccffeahdhejh",
                        "hbgjjcciheggag",
                        "hdedfee",
                        "dafe",
                        "efbhiag",
                        "aeh",
                        "fhhchcgdgibah",
                        "jhaecgjbdbiag",
                        "hdbbibjfaiifgfebff",
                        "jhcbcfghagcj",
                        "ahbaj",
                        "jahdheddffjecf",
                        "aibdhie",
                        "aiebiic",
                        "djijchhggdfihaibiii",
                        "bdcfcceedcijifffbhb",
                        "cjffeijeiecjedjcgefe",
                        "igdfbjbicfgecaied",
                        "bhhdgjaccfaj",
                        "gfcchaaji",
                        "dcjjciggjbfdhd"};

vector<vector<int>> output = {
    {13, 170},  {21, 45},   {21, 240},  {21, 241},  {21, 287},  {29, 90},
    {29, 186},  {29, 408},  {38, 29},   {38, 167},  {38, 348},  {40, 399},
    {40, 452},  {40, 501},  {45, 40},   {45, 66},   {45, 559},  {47, 228},
    {53, 40},   {78, 460},  {90, 186},  {90, 214},  {90, 319},  {90, 566},
    {99, 47},   {118, 559}, {128, 566}, {133, 501}, {148, 169}, {148, 226},
    {148, 309}, {148, 325}, {149, 195}, {149, 329}, {159, 533}, {165, 172},
    {165, 464}, {165, 577}, {167, 165}, {169, 370}, {170, 165}, {170, 443},
    {172, 370}, {177, 32},  {186, 38},  {186, 29},  {186, 384}, {186, 451},
    {188, 189}, {195, 329}, {195, 170}, {214, 370}, {214, 265}, {214, 335},
    {226, 38},  {226, 444}, {228, 47},  {228, 373}, {229, 238}, {240, 165},
    {240, 270}, {240, 188}, {265, 90},  {265, 214}, {287, 47},  {309, 195},
    {309, 486}, {319, 165}, {319, 577}, {325, 165}, {329, 445}, {329, 149},
    {335, 452}, {343, 165}, {348, 47},  {359, 43},  {370, 265}, {373, 148},
    {384, 29},  {399, 195}, {445, 406}, {445, 149}, {445, 343}, {452, 90},
    {464, 47},  {495, 195}, {495, 486}, {501, 47},  {520, 167}, {532, 445},
    {533, 21},  {551, 90},  {566, 47},  {566, 11},  {577, 90},  {577, 319},
    {13, 170},  {21, 287},  {21, 45},   {21, 241},  {21, 240},  {29, 90},
    {29, 186},  {29, 408},  {38, 348},  {38, 29},   {38, 167},  {40, 501},
    {40, 399},  {40, 452},  {45, 40},   {45, 66},   {45, 559},  {47, 228},
    {53, 40},   {78, 460},  {90, 214},  {90, 566},  {90, 186},  {90, 319},
    {99, 47},   {118, 559}, {128, 566}, {133, 501}, {148, 533}, {148, 169},
    {148, 226}, {148, 309}, {148, 325}, {149, 195}, {149, 329}, {159, 533},
    {165, 172}, {165, 464}, {165, 577}, {167, 165}, {169, 370}, {170, 165},
    {170, 443}, {172, 370}, {177, 32},  {186, 38},  {186, 29},  {186, 384},
    {186, 451}, {188, 189}, {195, 329}, {195, 170}, {214, 370}, {214, 265},
    {214, 335}, {226, 38},  {226, 444}, {228, 47},  {228, 373}, {229, 238},
    {240, 165}, {240, 270}, {240, 188}, {265, 90},  {265, 214}, {287, 47},
    {309, 195}, {309, 486}, {319, 165}, {319, 577}, {325, 165}, {329, 445},
    {329, 149}, {335, 452}, {343, 165}, {348, 47},  {359, 43},  {370, 265},
    {373, 148}, {384, 29},  {399, 195}, {445, 406}, {445, 149}, {445, 343},
    {452, 90},  {464, 47},  {495, 195}, {495, 486}, {501, 47},  {520, 167},
    {532, 445}, {533, 21},  {551, 90},  {566, 47},  {566, 11},  {577, 90},
    {577, 319}};
TEST(t0, t3) {
    // Explanation: The palindromes are
    // The palindromes are ["battab","tabbat"]

    set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PalindromePairs(words);

    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
    ret = sl.PalindromePairsV1(words);

    set<vector<int>> ret_set1(ret.begin(), ret.end());
    EXPECT_EQ(ret_set1, output_set);

    ret = sl.PalindromePairsV1(words);

    set<vector<int>> ret_set2(ret.begin(), ret.end());
    EXPECT_EQ(ret_set2, output_set);
}

#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

static void BenchMarkV0(benchmark::State& state) {
    for (auto _ : state) {
        set<vector<int>> output_set(output.begin(), output.end());
        Solution sl;
        auto ret = sl.PalindromePairs(words);

        set<vector<int>> ret_set(ret.begin(), ret.end());
        EXPECT_EQ(ret_set, output_set);
    }
}
BENCHMARK(BenchMarkV0);

static void BenchMarkV1(benchmark::State& state) {
    for (auto _ : state) {
        set<vector<int>> output_set(output.begin(), output.end());
        Solution sl;
        auto ret = sl.PalindromePairsV2(words);

        set<vector<int>> ret_set(ret.begin(), ret.end());
        EXPECT_EQ(ret_set, output_set);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State& state) {
    for (auto _ : state) {
        // Explanation: The palindromes are
        // ["dcbaabcd","abcddcba","slls","llssssll"]

        set<vector<int>> output_set(output.begin(), output.end());
        Solution sl;
        auto ret = sl.PalindromePairsV2(words);

        set<vector<int>> ret_set(ret.begin(), ret.end());
        EXPECT_EQ(ret_set, output_set);
    }
}
BENCHMARK(BenchMarkV2);

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
