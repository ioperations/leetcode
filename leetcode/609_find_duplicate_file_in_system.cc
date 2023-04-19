// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a list paths of directory info, including the directory path, and all the
files with contents in this directory, return all the duplicate files in the
file system in terms of their paths. You may return the answer in any order.

A group of duplicate files consists of at least two files that have the same
content.

A single directory info string in the input list has the following format:

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"
It means there are n files (f1.txt, f2.txt ... fn.txt) with content (f1_content,
f2_content ... fn_content) respectively in the directory "root/d1/d2/.../dm".
Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root
directory.

The output is a list of groups of duplicate file paths. For each group, it
contains all the file paths of the files that have the same content. A file path
is a string that has the following format:

"directory_path/file_name.txt"
*/

#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
class Solution {
    /*
        1 <= paths.length <= 2 * 104
        1 <= paths[i].length <= 3000
        1 <= sum(paths[i].length) <= 5 * 105
        paths[i] consist of English letters, digits, '/', '.', '(', ')',
        and ' '. You may assume no files or directories share the same name in
       the same directory. You may assume each given directory info represents a
       unique directory. A single blank space separates the directory path and
       file info.
    */
   public:
    vector<vector<string>> FindDuplicate(vector<string> &paths) {
        vector<vector<string>> ret;
        std::map<string, vector<string>> content_to_path_list;
        for (auto &ptr : paths) {
            stringstream kk;
            kk << ptr;
            string path;
            kk >> path;

            string tt;
            while (kk >> tt) {
                replace(tt.begin(), tt.end(), '(', ' ');
                replace(tt.begin(), tt.end(), ')', ' ');

                stringstream zz;
                zz << tt;

                string last_path;
                string content;
                zz >> last_path;
                zz >> content;

                content_to_path_list[content].push_back(path + '/' + last_path);
            }
        }

        for (auto &ptr : content_to_path_list) {
            if (ptr.second.size() >= 2) {
                ret.push_back(ptr.second);
            }
        }

        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> paths = {"root/a 1.txt(abcd) 2.txt(efgh)",
                            "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)",
                            "root 4.txt(efgh)"};
    vector<vector<string>> output = {
        {"root/a/2.txt", "root/c/d/4.txt", "root/4.txt"},
        {"root/a/1.txt", "root/c/3.txt"}};

    set<vector<string>> output_set(output.begin(), output.end());

    Solution sl;
    auto ret = sl.FindDuplicate(paths);

    set<vector<string>> ret_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, output_set);
}

TEST(t0, t2) {
    vector<string> paths = {"root/a 1.txt(abcd) 2.txt(efgh)",
                            "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)"};
    vector<vector<string>> output = {{"root/a/2.txt", "root/c/d/4.txt"},
                                     {"root/a/1.txt", "root/c/3.txt"}};
    set<vector<string>> output_set(output.begin(), output.end());

    Solution sl;
    auto ret = sl.FindDuplicate(paths);

    set<vector<string>> ret_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, output_set);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
