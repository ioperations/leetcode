#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
   public:
    int LengthOfLongestSubstring(string s) {
        int n = s.size();
        int ans = INT_MIN, i = 0, j = 0;
        unordered_map<char, int> m;
        if (n == 0) return 0;
        for (j = 0; j < n; j++) {
            m[s[j]]++;
            if ((int)m.size() == j - i + 1) {
                ans = max(ans, j - i + 1);
            } else if ((int)m.size() < j - i + 1) {
                while ((int)m.size() < j - i + 1) {
                    m[s[i]]--;
                    if (m[s[i]] == 0) m.erase(s[i]);
                    i++;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution *s = new Solution();

    std::string sb("ancbbsdsdax");

    int ret = s->LengthOfLongestSubstring(sb);
    std::cout << "lengthOfLongestSubstring of \"ancbbsdsdax\" is : " << ret
              << std::endl;
    delete s;
}
