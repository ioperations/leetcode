// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array of integers arr, find the sum of min(b), where b ranges over
 * every (contiguous) subarray of arr. Since the answer may be large, return the
 * answer modulo 109 + 7.*/

#include <stack>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int SumSubarrayMins(vector<int> &arr) {
        int size = arr.size();
        vector<int> nextsmaller(size, size);
        vector<int> prevsmaller(size, -1);

        stack<int> stack;

        // calculating the nextsmaller index
        for (int i = 0; i < size; i++) {
            while (stack.size() && arr[stack.top()] > arr[i]) {
                nextsmaller[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }

        // clear the stack;
        while (stack.size()) stack.pop();

        // calculating the prevsmaller index
        for (int i = size - 1; i >= 0; --i) {
            while (stack.size() && arr[stack.top()] >= arr[i]) {
                prevsmaller[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }
        int ret = 0;
        long long mod = 1e9 + 7;

        for (int i = 0; i < size; i++) {
            ret += (int)(arr[i] * (i - prevsmaller[i]) % mod) *
                   (nextsmaller[i] - i) % mod;
            ret %= mod;
        }
        return ret;
    }
};

TEST(sum_of_subarray_minimums, t1) {
    std::vector<int> arr{3, 1, 2, 4};
    int output = 17;
    Solution sl;
    int ret = sl.SumSubarrayMins(arr);
    /*Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4],
    [3,1,2,4]. Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1. Sum is 17.*/
    EXPECT_EQ(ret, output);
}

TEST(sum_of_subarray_minimums, t2) {
    std::vector<int> arr{11, 81, 94, 43, 3};
    int output = 444;
    Solution sl;
    int ret = sl.SumSubarrayMins(arr);
    EXPECT_EQ(ret, output);
}

TEST(sum_of_subarray_minimums, t3) {
    std::vector<int> arr{
        29959, 29867, 29822, 29704, 29676, 29650, 29577, 29488, 29286, 29255,
        29232, 29207, 29071, 29034, 28925, 28849, 28731, 28693, 28624, 28606,
        28591, 28397, 28357, 28308, 28295, 28210, 28119, 28090, 28004, 27903,
        27845, 27830, 27777, 27736, 27640, 27540, 27506, 27428, 27341, 27308,
        27182, 27152, 27122, 27029, 26928, 26872, 26796, 26765, 26663, 26597,
        26580, 26530, 26498, 26475, 26436, 26406, 26382, 26312, 26213, 26134,
        26088, 26025, 25943, 25912, 25875, 25845, 25810, 25702, 25638, 25614,
        25531, 25524, 25488, 25470, 25444, 25402, 25283, 25262, 25121, 24988,
        24958, 24886, 24769, 24697, 24635, 24595, 24490, 24456, 24453, 24346,
        24313, 24248, 24200, 24148, 24107, 24052, 24044, 24021, 23970, 23908,
        23897, 23835, 23752, 23741, 23714, 23661, 23596, 23545, 23509, 23470,
        23439, 23409, 23350, 23215, 23166, 23155, 23100, 23024, 22923, 22825,
        22793, 22627, 22613, 22536, 22450, 22383, 22312, 22268, 22205, 22175,
        22136, 22028, 21971, 21900, 21824, 21769, 21726, 21583, 21546, 21513,
        21494, 21428, 21327, 21264, 21254, 21174, 21140, 21112, 21000, 20921,
        20902, 20830, 20817, 20783, 20735, 20657, 20616, 20573, 20485, 20378,
        20363, 20305, 20259, 20210, 20114, 20002, 19846, 19785, 19747, 19667,
        19645, 19622, 19610, 19580, 19542, 19516, 19454, 19392, 19310, 19277,
        19194, 19131, 19090, 19004, 18883, 18845, 18791, 18781, 18668, 18591,
        18518, 18475, 18368, 18331, 18310, 18287, 18217, 18114, 18092, 18048,
        17990, 17964, 17912, 17836, 17740, 17704, 17630, 17613, 17573, 17428,
        17356, 17341, 17300, 17260, 17180, 17174, 17126, 17071, 17041, 16866,
        16850, 16828, 16672, 16618, 16577, 16499, 16407, 16357, 16318, 16293,
        16202, 16150, 16075, 16041, 15948, 15921, 15844, 15843, 15785, 15764,
        15668, 15626, 15579, 15473, 15387, 15255, 15190, 15139, 15062, 14996,
        14954, 14918, 14907, 14902, 14867, 14851, 14817, 14799, 14751, 14720,
        14536, 14506, 14474, 14353, 14303, 14280, 14185, 14107, 14012, 13932,
        13858, 13781, 13585, 13563, 13533, 13451, 13412, 13362, 13249, 13208,
        13181, 13064, 13037, 12961, 12926, 12892, 12786, 12731, 12611, 12573,
        12506, 12502, 12496, 12470, 12443, 12370, 12262, 12182, 12153, 12069,
        12000, 11847, 11806, 11781, 11708, 11687, 11593, 11550, 11445, 11372,
        11329, 11308, 11291, 11268, 11241, 11191, 11027, 10982, 10879, 10862,
        10776, 10695, 10603, 10502, 10464, 10350, 10338, 10305, 10273, 10176,
        10124, 10094, 10038, 9953,  9935,  9812,  9786,  9743,  9728,  9508,
        9472,  9383,  9349,  9236,  9215,  9130,  9124,  9042,  9008,  8988,
        8901,  8833,  8809,  8780,  8716,  8580,  8462,  8334,  8321,  8305,
        8280,  8257,  8246,  8137,  8077,  8043,  8016,  7984,  7955,  7927,
        7906,  7746,  7663,  7653,  7572,  7542,  7530,  7489,  7420,  7390,
        7361,  7337,  7245,  7210,  7188,  7175,  7096,  6898,  6846,  6745,
        6675,  6569,  6478,  6427,  6363,  6284,  6260,  6243,  6206,  6154,
        6135,  6078,  6061,  6017,  5995,  5917,  5863,  5836,  5793,  5763,
        5743,  5678,  5572,  5532,  5459,  5384,  5341,  5299,  5251,  5231,
        4995,  4933,  4861,  4740,  4672,  4625,  4496,  4445,  4361,  4282,
        4215,  4135,  4097,  4028,  3917,  3862,  3711,  3553,  3498,  3410,
        3388,  3384,  3288,  3279,  3244,  3221,  3181,  3171,  3150,  3060,
        3035,  2975,  2965,  2834,  2760,  2637,  2584,  2533,  2440,  2383,
        2311,  2285,  2255,  2211,  2192,  2121,  2054,  2010,  1964,  1850,
        1724,  1642,  1577,  1411,  1409,  1332,  1296,  1265,  1256,  1220,
        1195,  937,   903,   880,   811,   739,   720,   650,   609,   547,
        533,   459,   434,   384,   279,   231,   163,   102,   78,    30,
        5,     52,    100,   155,   217,   277,   328,   389,   446,   473,
        546,   583,   649,   702,   734,   768,   857,   882,   912,   1043,
        1219,  1243,  1258,  1290,  1325,  1359,  1409,  1567,  1642,  1679,
        1726,  1873,  1965,  2017,  2088,  2172,  2204,  2226,  2273,  2288,
        2316,  2434,  2522,  2558,  2622,  2678,  2790,  2933,  2965,  3025,
        3037,  3071,  3167,  3180,  3194,  3233,  3269,  3282,  3383,  3387,
        3401,  3465,  3528,  3595,  3801,  3910,  4020,  4078,  4128,  4213,
        4271,  4295,  4420,  4472,  4612,  4663,  4739,  4845,  4891,  4980,
        5109,  5241,  5284,  5335,  5379,  5388,  5478,  5546,  5639,  5705,
        5751,  5766,  5803,  5855,  5879,  5975,  6000,  6024,  6070,  6093,
        6137,  6156,  6212,  6256,  6276,  6304,  6421,  6441,  6537,  6614,
        6743,  6844,  6893,  7087,  7169,  7183,  7200,  7237,  7262,  7352,
        7376,  7398,  7441,  7491,  7541,  7564,  7602,  7656,  7707,  7814,
        7924,  7940,  7958,  8014,  8036,  8048,  8132,  8141,  8250,  8279,
        8288,  8321,  8331,  8374,  8515,  8655,  8723,  8807,  8825,  8878,
        8953,  8990,  9011,  9077,  9128,  9172,  9219,  9276,  9383,  9420,
        9499,  9535,  9736,  9744,  9801,  9900,  9951,  10038, 10093, 10119,
        10147, 10265, 10301, 10314, 10340, 10456, 10499, 10564, 10622, 10767,
        10802, 10876, 10882, 10997, 11063, 11217, 11243, 11276, 11299, 11314,
        11365, 11407, 11456, 11587, 11627, 11705, 11751, 11792, 11831, 11901,
        12012, 12118, 12180, 12240, 12296, 12385, 12469, 12473, 12497, 12503,
        12537, 12578, 12723, 12778, 12858, 12901, 12936, 13020, 13048, 13136,
        13195, 13232, 13325, 13377, 13424, 13493, 13547, 13564, 13724, 13856,
        13911, 13938, 14075, 14151, 14234, 14300, 14353, 14395, 14499, 14507,
        14705, 14724, 14796, 14802, 14823, 14858, 14882, 14905, 14914, 14936,
        14962, 15049, 15114, 15161, 15237, 15272, 15399, 15565, 15587, 15666,
        15749, 15778, 15830, 15843, 15864, 15928, 16039, 16075, 16141, 16163,
        16246, 16315, 16333, 16389, 16415, 16526, 16601, 16650, 16798, 16845,
        16861, 16991, 17046, 17090, 17140, 17178, 17186, 17292, 17305, 17343,
        17419, 17456, 17610, 17617, 17693, 17728, 17783, 17909, 17918, 17970,
        18032, 18083, 18104, 18114, 18223, 18296, 18330, 18363, 18428, 18496,
        18578, 18660, 18733, 18782, 18792, 18861, 18929, 19069, 19127, 19184,
        19269, 19279, 19355, 19394, 19494, 19539, 19559, 19599, 19612, 19643,
        19666, 19745, 19760, 19815, 19864, 20012, 20141, 20231, 20270, 20330,
        20370, 20380, 20500, 20595, 20617, 20690, 20751, 20811, 20824, 20843,
        20910, 20925, 21044, 21126, 21165, 21198, 21260, 21280, 21343, 21467,
        21505, 21531, 21564, 21640, 21755, 21817, 21885, 21929, 22010, 22103,
        22159, 22196, 22229, 22270, 22368, 22414, 22515, 22570, 22615, 22630,
        22806, 22864, 22951, 23030, 23107, 23155, 23191, 23226, 23399, 23438,
        23464, 23487, 23524, 23559, 23634, 23667, 23719, 23747, 23764, 23869,
        23901, 23936, 24012, 24022, 24045, 24074, 24141, 24185, 24204, 24272,
        24327, 24452, 24455, 24490, 24560, 24615, 24641, 24734, 24815, 24890,
        24963, 25025, 25242, 25282, 25283, 25414, 25446, 25475, 25489, 25527,
        25586, 25636, 25640, 25771, 25844, 25848, 25883, 25923, 26005, 26048,
        26106, 26157, 26312, 26359, 26395, 26429, 26465, 26491, 26513, 26558,
        26584, 26601, 26667, 26770, 26864, 26900, 26996, 27118, 27129, 27176,
        27272, 27313, 27389, 27478, 27517, 27580, 27700, 27761, 27811, 27844,
        27848, 27967, 28051, 28108, 28176, 28264, 28302, 28332, 28380, 28525,
        28591, 28617, 28681, 28727, 28744, 28874, 28994, 29047, 29123, 29221,
        29239, 29274, 29347, 29493, 29596, 29668, 29694, 29717, 29847, 29871};
    int output = 508796209;
    Solution sl;
    int ret = sl.SumSubarrayMins(arr);
    EXPECT_EQ(ret, output);
}
}  // namespace
