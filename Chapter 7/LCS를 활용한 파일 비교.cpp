#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <string_view>
#include <set>

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
    
    std::string memoization(size_t idx1,size_t idx2,
                            const std::string& str1,
                            const std::string& str2,
                            std::string cur)
    {
        auto it = set.find(cur);
        if(it != set.end())
            return it->data();
        if(idx1 >= str1.length() || idx2 >= str2.length())
            return "";
        
        if(str1[idx1] != str2[idx2])
        {
            auto result1 = memoization(idx1+1,idx2,str1,str2,cur);
            auto result2 = memoization(idx1,idx2+1,str1,str2,cur);
            
            if(result1.length() > result2.length())
            {
                set.insert(result1);
                return result1;
            }
            
            set.insert(result2);
            return result2;
        }
        
        auto result = str1[idx1] + memoization(idx1+1,idx2+1,str1,str2,cur);
        set.insert(result);
        
        return result;
    }
    
    std::string lcsAlgorithm(void)
    {
        std::string result = "";
        std::string strFromFile1,strFromFile2;
        size_t sizeOfFile1 = 0,sizeOfFile2 = 0;
        
        sizeOfFile1 = getFileSize(prev);
        sizeOfFile2 = getFileSize(curr);
        
        strFromFile1.resize(sizeOfFile1);
        strFromFile2.resize(sizeOfFile2);
        
        prev.read(&strFromFile1[0],sizeOfFile1);
        curr.read(&strFromFile2[0],sizeOfFile2);
        
        result = set.find(memoization(0,0,strFromFile1,strFromFile2,""))->data();
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
    std::set<std::string> set;
};

int main(int argc,char* argv[])
{
    CompareDocuments docs("path1","path2");
    
    std::cout << docs.lcsAlgorithm() << std::endl;
    return 0;
}
