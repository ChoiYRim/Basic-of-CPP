#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
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
    
    void compareOuputStrings(const std::string& stringFromCurr,const std::string& lcs)
    {
        std::string line_first,line_second;
        std::istringstream input(stringFromCurr),comp(lcs);
        
        std::getline(comp,line_second);
        while(std::getline(input,line_first))
        {
            if(line_first != line_second)
            {
                outputs.push_back({false,line_first});
                continue;
            }
            
            outputs.push_back({true,line_first});
            std::getline(comp,line_second);
        }
    }
    
    void lcsAlgorithm(void)
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
        
        compareOuputStrings(strFromFile2,result);
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
    
    friend std::ostream& operator<<(std::ostream& os,const CompareDocuments& docs);
    
private:
    std::fstream prev,curr;
    std::vector<std::vector<int>> dp;
    std::vector<std::pair<bool,std::string>> outputs;
};

std::ostream& operator<<(std::ostream& os,const CompareDocuments& docs)
{
    for(auto& output : docs.outputs)
    {
        if(output.first != 0)
            os << "[ " << output.second << " ]\n";
        else
            os << output.second << "\n";
    }
    
    return os;
}

int main(int argc,char* argv[])
{
    CompareDocuments docs("version1.txt","version2.txt");
    
    docs.lcsAlgorithm();
    std::cout << docs << std::endl;
    return 0;
}

