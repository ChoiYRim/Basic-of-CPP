#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>

class CompareDocuments
{
public:
    bool fileOpen(std::fstream& file,const std::string_view& file_name)
    {
        file.open(file_name.data());
        if(!file.is_open())
            return false;
        return true;
    }
    
    CompareDocuments() = delete;
    
    CompareDocuments(const std::string_view& sv1,const std::string_view& sv2)
    {
        if(!fileOpen(prev,sv1.data()) || !fileOpen(curr,sv2.data()))
        {
            std::cerr << "files open failed..." << std::endl;
            return;
        }
    }
    
    size_t getFileSize(std::fstream& f)
    {
        size_t Size = 0;
        
        f.seekg(0,std::ios::end);
        Size = f.tellg();
        f.seekg(0,std::ios::beg);
        
        return Size;
    }
    
    int memoization(size_t idx1,size_t idx2,
                     const std::string& str1,
                     const std::string& str2)
    {
        if(dp[idx1][idx2] != 0)
            return dp[idx1][idx2];
        if(idx1 >= str1.length() || idx2 >= str2.length())
            return 0;
        
        if(str1[idx1] != str2[idx2])
            dp[idx1][idx2] = std::max(memoization(idx1+1,idx2,str1,str2),memoization(idx1,idx2+1,str1,str2));
        else
            dp[idx1][idx2] = memoization(idx1+1,idx2+1,str1,str2)+1;
        return dp[idx1][idx2];
    }
    
    std::string lcsAlgorithm(void)
    {
        std::string strFromFile1,strFromFile2;
        size_t len1 = 0,len2 = 0;
        
        len1 = getFileSize(prev);
        len2 = getFileSize(curr);
        
        strFromFile1.resize(len1);
        strFromFile2.resize(len2);
        
        prev.read(&strFromFile1[0],len1);
        curr.read(&strFromFile2[0],len2);
        
        dp.clear();
        dp = std::vector<std::vector<int>>(len1+1,std::vector<int>(len2+1,0));
        int idx = memoization(0,0,strFromFile1,strFromFile2);
        
        std::string result(idx+1,0);
        
        idx = 0;
        len1 = len2 = 0;
        while(dp[len1][len2] != 0)
        {
            if(dp[len1][len2] == dp[len1+1][len2])
                len1++;
            else if(dp[len1][len2] == dp[len1][len2+1])
                len2++;
            else
            {
                result[idx] = strFromFile1[len1];
                idx++; len1++; len2++;
            }
        }
        
        return result;
    }

    void printCommonString(const std::string& str)
    {
        std::cout << str << std::endl;
    }
    
    virtual ~CompareDocuments()
    {
        prev.close();
        curr.close();
    }
    
private:
    std::fstream prev,curr;
    std::vector<std::vector<int>> dp;
};

int main(int argc,char* argv[])
{
    CompareDocuments docs("version1.txt","version2.txt");
    
    std::cout << docs.lcsAlgorithm() << std::endl;
    return 0;
}
