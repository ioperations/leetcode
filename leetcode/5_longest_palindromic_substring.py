#!/usr/bin/env python3

# 中心扩展算法
class Solution:
    def longestPalindrome(self, s: str) -> str:
        #用n来装字符串长度，res来装答案
        n = len(s)  
        res = str()
        #字符串长度小于2，就返回本身
        if n < 2: return s
        for i in range(n-1):
            #oddstr是以i为中心的最长回文子串
            oddstr = self.__centerExtend(s,i,i)
            #evenstr是以i和i+1为中心的最长回文子串
            evenstr = self.__centerExtend(s,i,i+1)
            temp = oddstr if len(oddstr)>len(evenstr) else evenstr
            if len(temp)>len(res):res=temp
        
        return res

    def __centerExtend(self,s:str,left,right)->str:
        while left >= 0 and right < len(s) and s[left] == s[right]:
            left -= 1
            right += 1
        #这里要注意，跳出while循环时，恰好s[left] != s[right]
        return s[left+1:right]


if __name__ == "__main__":
    s = Solution()
    ret = s.longestPalindrome("bbb")
    
    print(ret)
