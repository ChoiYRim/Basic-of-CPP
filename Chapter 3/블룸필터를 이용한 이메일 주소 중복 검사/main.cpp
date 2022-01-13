#include <vector>
#include <iostream>
#include <openssl/md5.h>

class BloomFilter
{
    int nHashes;
    std::vector<bool> bits;
    
    static constexpr int hashSize = 128 / 8; // 128 bits ( 16 bytes )
    
    unsigned char hashValue[hashSize];
    
public:
    BloomFilter(int size,int hashes) : bits(size), nHashes(hashes)
    {
        if(nHashes > hashSize)
            throw("해시 함수 개수가 너무 많습니다.");
        if(size > 255)
            throw("블룸 필터 크기가 255보다 클 수 없습니다.");
    }
    
    void hash(const std::string& key)
    {
        MD5(reinterpret_cast<const unsigned char*>(key.data()),key.length(),hashValue);
    }
    
    void add(const std::string& key)
    {
        hash(key);
        for(auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            bits[*it % bits.size()] = true;
        }
        std::cout << "블룸 필터에 추가: " << key << std::endl;
    }
    
    bool mayContain(const std::string& key)
    {
        hash(key);
        for(auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            if(!bits[*it % bits.size()])
            {
                std::cout << key << " : 사용할 수 없는 이메일입니다." << std::endl;
                return false;
            }
        }
        
        std::cout << key << " : 이미 사용 중입니다." << std::endl;
        return true;
    }
};

int main()
{
    BloomFilter bloom(128,5);
    
    bloom.add("abc@naver.com");
    bloom.add("xyz@naver.com");
    
    bloom.mayContain("abc");
    bloom.mayContain("xyz@naver.com");
    bloom.mayContain("xyz");
    
    bloom.add("abcd@naver.com");
    bloom.add("ab@naver.com");
    
    bloom.mayContain("abcd");
    bloom.mayContain("ab@naver.com");
    
    return 0;
}
