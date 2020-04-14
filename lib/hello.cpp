#include "hello.hpp"
#include <vector>
#include <set>

enum class MyClass { };

bool isBig_endian()
{
    typedef union big_endian {
        int num;
        char ch[sizeof(int)];
    }ENDIAN;
    ENDIAN big;
    big.num = 0x12345678;

    return big.ch[0] == 0x12;
}

int removeDuplicates(std::vector<int>& nums) 
{
    std::vector<int> set;
    int num;

    if(nums.size() <= 1)
    {
        return (int)nums.size();
    }

    num = nums[0];
    set.push_back(nums[0]);
    for(int i = 1; i < nums.size(); i ++)
    {
        if(num != nums[i])
        {
            num = nums[i];
            set.push_back(num);
        }
    }
    nums.clear();
    
    for(int i = 0; i < set.size(); i++)
    {
        nums.push_back(set[i]);
    }
    return (int)set.size();
}

int removeDuplicates1(std::vector<int>& nums)
{
    std::set<int> set;

    for(int i = 0; i < nums.size(); i ++)
    {
        set.insert(nums[i]);
    }

    nums.clear();
    std::set<int>::iterator it;
    for(it = set.begin(); it !=set.end(); it++)
    {
        nums.push_back(*it);
    }
    
    return (int)set.size();
}