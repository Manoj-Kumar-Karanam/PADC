#include<bits/stdc++.h>

using namespace std;
class Solution {
private:
    int binSearch(vector<int> &nums,int target) {
        int low = 0,high = nums.size() - 1;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(target == nums[mid]) {
                return mid;
            }
            else if(target < nums[mid]) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return -1;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> sol(2, -1);
        if(nums.size() == 0) {
            return sol;
        }
        int index = binSearch(nums,target);
        if(index == -1) {
            return sol;
        }
        int i = index;
        while(i > -1 && nums[i - 1] == target) {
            i--;
        }
        sol[0] = i;
        i = index;
        while(i < nums.size() && nums[i + 1] == target)
            i ++;
            
        sol[1] = i;        
        return sol;
    }
};

int main() {
    std::vector<int> nums = {5,6,6,7,7,8};
    std::vector<int> res = Solution().searchRange(nums, -1);
    cout << res[0] << " ," << res[1] << "\n";
}