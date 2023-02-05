/*
 * @lc app=leetcode.cn id=350 lang=cpp
 *
 * [350] 两个数组的交集 II
 */

// @lc code=start
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size())
        {
            return intersect(nums2, nums1);
        }
        unordered_map<int, int> m;
        for(auto num : nums1) {
            ++m[num];
        }
        int k = 0;
        for (auto num : nums2) {
            auto it = m.find(num);
            if (it != end(m) && --it->second >= 0){
                nums1[k++] = num;
            }
            
        }
        return vector(begin(nums1), begin(nums1) + k);
        
    }
};
// @lc code=end

