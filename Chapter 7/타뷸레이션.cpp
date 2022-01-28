#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

vector<vector<int>> memo;

void GetAllSubsets(vector<int> set,vector<int> subset,int index,
                   vector<vector<vector<int>>>& allSubsets)
{
    // 집합 set의 끝에 다다른 경우
    if(index == set.size())
    {
        // 부분집합 크기를 인덱스로 사용하여 부분집합을 allSubset에 추가
        allSubsets[subset.size()].push_back(subset);
        return;
    }
    
    // 원소를 추가하지 않고 재귀 호출
    GetAllSubsets(set,subset,index+1,allSubsets);
    
    // 원소를 부분집합에 추가한 후 재귀 호출
    subset.push_back(set[index]);
    GetAllSubsets(set,subset,index+1,allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set,int target)
{
    // 부분집합의 크기가 0 ~ set.size()까지 존재하므로
    vector<vector<vector<int>>> allSubsets(set.size()+1);
    
    GetAllSubsets(set,{},0,allSubsets);
    for(int size = 0; size <= set.size(); size++)
    {
        //PRINT("부분집합의 원소 개수: " << size << endl);
        for(auto subset : allSubsets[size])
        {
            //PRINT("\t{ ");
            
            int sum = 0;
            for(auto number : subset)
            {
                sum += number;
                //PRINT(number << " ");
            }
            
            //PRINT("} = " << sum << endl);
            
            if(sum == target)
                return true;
        }
    }
    
    return false;
}

bool BackTracking_Search(const vector<int>& set,int idx,int sum)
{
    if(sum == 0)
        return true;
    if(idx == set.size() || set[idx] > sum)
        return false;
    
    return BackTracking_Search(set,idx+1,sum-set[idx]) || BackTracking_Search(set,idx+1,sum);
}

bool memoization(int idx,int sum,const vector<int>& set)
{
    if(sum == 0)
        return true;
    if(idx >= set.size() || set[idx] > sum)
        return false;
    
    if(memo[idx][sum] != 0)
        return memo[idx][sum];
    
    return (memoization(idx+1,sum-set[idx],set) || memoization(idx+1,sum,set));
}

bool tabulation(int target,const vector<int>& set)
{
    int maxSum = 0;
    for(const auto& ele : set)
        maxSum += ele;
    
    for(auto i = 0; i < set.size(); i++)
        memo[i][0] = 1;
    for(auto i = 1; i <= set.size(); i++)
    {
        for(int sum = 1; sum <= maxSum; sum++)
        {
            if(sum < set[i-1])
                memo[i][sum] = memo[i-1][sum];
            else
                memo[i][sum] = memo[i-1][sum] || memo[i-1][sum-set[i-1]];
        }
    }
    
    return memo[set.size()][target];
}

inline void print_timer(const string& message,chrono::microseconds usec)
{
    cout << message << " : " << usec.count() << " usec" << endl;
}

int main()
{
    vector<int> set = {16,1058,22,13,46,55,3,92,47,7,
                       98,367,807,106,333,85,577,9,3059};
    const int target = 6076,tests = 4;
    
    for(int i = 0; i < tests; i++)
    {
        bool found = false;
        string message;
        chrono::system_clock::time_point begin,end;
        
        begin = chrono::system_clock::now();
        switch(i)
        {
            case 0:
            {
                message = "Brute Force"s;
                found = SubsetSum_BruteForce(set,target);
                break;
            }
            case 1:
            {
                message = "Back Tracking"s;
                found = BackTracking_Search(set,0,target);
                break;
            }
            case 2:
            {
                message = "Memoization"s;
                memo = vector<vector<int>>(set.size()+1,vector<int>(accumulate(set.begin(),set.end(),0)+1,0));
                found = memoization(0,target,set);
                break;
            }
            case 3:
            {
                message = "Tabulation"s;
                memo = vector<vector<int>>(set.size()+1,vector<int>(accumulate(set.begin(),set.end(),0)+1,0));
                found = tabulation(target,set);
                break;
            }
        }
        end = chrono::system_clock::now();
        
        if(found)
        {
            chrono::microseconds result = chrono::duration_cast<chrono::microseconds>(end-begin);
            print_timer(message,result);
        }
    }
    
    return 0;
}
