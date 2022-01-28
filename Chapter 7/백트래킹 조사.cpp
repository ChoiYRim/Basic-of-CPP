#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

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
        //cout << "부분집합의 원소 개수: " << size << endl;
        for(auto subset : allSubsets[size])
        {
            //cout << "\t{ ";
            
            int sum = 0;
            for(auto number : subset)
            {
                sum += number;
                //cout << number << " ";
            }
            
            //cout << "} = " << sum << endl;
            
            if(sum == target)
                return true;
        }
    }
    
    return false;
}

bool BackTracking_Search(const vector<int>& set,vector<bool>& visit,int sum,int target)
{
    if(target < sum)
        return false;
    if(target == sum)
        return true;
    
    for(auto i = 0; i < set.size(); i++)
    {
        if(!visit[i])
        {
            visit[i] = true;
            bool ret = BackTracking_Search(set,visit,sum+set[i],target);
            if(ret)
                return true;
            visit[i] = false;
        }
    }
    
    return false;
}

int main()
{
    chrono::system_clock::time_point begin,end;
    vector<int> set = {13,79,45,29};
    vector<bool> visit = {0,0,0,0};
    int target = 58;
    
    begin = chrono::system_clock::now();
    if(SubsetSum_BruteForce(set,target))
        cout << "원소의 합이 " << target << "인 부분집합이 존재합니다." << endl;
    else
        cout << "원소의 합이 " << target << "인 부분집합이 존재하지 않습니다." << endl;
    end = chrono::system_clock::now();
    auto result = chrono::duration_cast<chrono::microseconds>(end-begin);
    cout << "전수조사 시간 : " << result.count() << " usec" << endl;

    begin = chrono::system_clock::now();
    if(BackTracking_Search(set,visit,0,target))
        cout << "원소의 합이 " << target << "인 부분집합이 존재합니다." << endl;
    else
        cout << "원소의 합이 " << target << "인 부분집합이 존재하지 않습니다." << endl;
    end = chrono::system_clock::now();
    result = chrono::duration_cast<chrono::microseconds>(end-begin);
    cout << "백트래킹 시간 : " << result.count() << " usec" << endl;
    
    return 0;
}
