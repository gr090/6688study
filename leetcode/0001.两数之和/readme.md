# 1.两数之和

## 题目描述 [https://leetcode-cn.com/problems/two-sum/](https://leetcode-cn.com/problems/two-sum/)

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

示例：

> 给定nums = [2, 7, 11, 15], target = 9
> 因为nums[0] + nums[1] = 2 + 7 = 9  
> 所以返回[0, 1]

## 题目分析

暴力法很简单，遍历每个元素x，并查找是否存在一个值与target - x相等的目标元素。
暴力法时间复杂度O(n^2)，空间复杂度O(1)。
为了对运行时间复杂度进行优化，我们需要一种更有效的方法来检查数组中是否存在目标元素。如果存在，我们需要找出它的索引。保持数组中的每个元素与其索引相互对应的最好方法是什么？哈希表。
通过以空间换取速度的方式，我们可以将查找时间从 O(n) 降低到 O(1)。哈希表正是为此目的而构建的，它支持以*近似*恒定的时间进行快速查找。我用“近似”来描述，是因为一旦出现冲突，查找用时可能会退化到 O(n)。但只要你仔细地挑选哈希函数，在哈希表中进行查找的用时应当被摊销为 O(1)。

## 题目解答

* 使用哈希表保存数组中每个元素对应的索引。
* 在进行迭代并将元素插入到表中的同时，我们还会回过头来检查表中是否已经存在当前元素所对应的目标元素。如果它存在，那我们已经找到了对应解，并立即将其返回。

C++代码

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
		map<int, int> numsMap;
		int len = nums.size();
		for(int i = 0; i < len; i++){
			int complement = target - nums[i];
			//在进行迭代并将元素插入到表中的同时，检查表中是否已经存在当前元素对应的目标元素 
			map<int, int>::iterator iter = numsMap.find(complement);
			if(iter != numsMap.end()){
				result.push_back(iter->second);
                result.push_back(i);
				return result;
			}
			//numsMap.insert(map<int, int>::value_type(nums[i], i));
			numsMap[nums[i]] = i;
		} 
        return result;
    }
};
```

TypeScript代码

```typescript
function twoSum(nums: number[], target: number): number[] {
    let len = nums.length;
    let numMap:{[num:number]:number}={};
    for(let i = 0; i < len; i++){
        let element = target - nums[i];
        if(numMap[element] != null){
            let index = numMap[element];
            return [index, i];
        }
        numMap[nums[i]] = i;
    }
    return [];
};
```

复杂度分析：

* 时间复杂度：O(n)， 我们只遍历了包含有 n 个元素的列表一次。在表中进行的每次查找只花费 O(1) 的时间。
* 空间复杂度：O(n)， 所需的额外空间取决于哈希表中存储的元素数量，该表最多需要存储 n 个元素。

