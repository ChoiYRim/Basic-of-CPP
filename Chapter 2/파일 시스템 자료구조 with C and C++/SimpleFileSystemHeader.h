#ifndef FileSystemHeader_h
#define FileSystemHeader_h

#define _GNU_SOURCE

// 일단 C언어 기반으로 개발

#include <iostream>
#include <vector>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

enum FileType
{
    REGULAR = 0,
    DIRECTORY,
    LINK,
    CDEVICE,
    BDEVICE,
    SOCKET
};

enum InputType
{
    SEARCH = 1,
    PRINT,
    ADD,
    CHANGE,
    END
};

struct FileNode
{
private:
    int depth;
    bool isItLast; // is it last node of the siblings?
    FileType fType; // file type flag
    FileNode* parent; // parent node
    std::string fName; // file name
    std::string rPath; // relative path
    std::string aPath; // absolute path
    std::vector<FileNode*> subs; // subordinate files
    
public:
    FileNode(FileNode* p,std::string rPath,std::string aPath,int initDepth) : rPath(rPath) , aPath(aPath) , depth(initDepth)
    {
        GetFileType();
        subs.clear();
        fName = GetFileName();
        parent = p;
        isItLast = false;
        
        if(this->fType == DIRECTORY)
            ReadChildren(aPath);
    }
    
    inline int GetDepth(void) { return this->depth; }
    
    inline void SetLast(bool value) { isItLast = value; }
    
    std::string GetFileName(void)
    {
        std::string ret = "";
        
        for(int i = (int)rPath.length()-1; i >= 0 && rPath[i] != '/'; i--)
            ret += rPath[i];
        std::reverse(ret.begin(),ret.end());
        
        return ret;
    }
    
    void AssignPointer(FileNode* p,FileNode*& fn,std::string rPath,std::string aPath,int initDepth)
    {
        fn = new FileNode(p,rPath,aPath,initDepth);
    }
    
    void ReadChildren(std::string cur)
    {
        int cnt = 0,i = 0;
        struct dirent** flist;
        char start[1024] = {0,};
        
        if((cnt = scandir(cur.c_str(), &flist, 0, alphasort)) < 0)
        {
            std::cerr << "scandir() error" << '\n';
            return;
        }
        
        if(getcwd(start, 1023) == NULL)
        {
            std::cerr << "getcwd() error" << '\n';
            return;
        }
        
        while(i < cnt)
        {
            if(!strcmp(flist[i]->d_name,".") || !strcmp(flist[i]->d_name,".."))
            {
                i++;
                continue;
            }
            
            FileNode* fn;
            struct stat statBuf;
            char childSub[1024] = {0,};
            
            if(lstat(flist[i]->d_name,&statBuf) < 0)
            {
                std::cerr << "lstat() error" << '\n';
                i++;
                continue;
            }
            
            if(!S_ISREG(statBuf.st_mode) && !S_ISDIR(statBuf.st_mode))
            {
                i++;
                continue;
            }
                
            if(realpath(flist[i]->d_name, childSub) == NULL)
            {
                std::cerr << "realpath() error" << '\n';
                i++;
                continue;
            }
            
            if(S_ISDIR(statBuf.st_mode))
            {
                chdir(flist[i]->d_name);
                AssignPointer(this,fn, flist[i]->d_name, childSub, this->depth+1);
                if(i == cnt-1)
                    fn->SetLast(true);
                this->subs.push_back(fn);
                chdir(start);
            }
            else
            {
                AssignPointer(this,fn, flist[i]->d_name, childSub, this->depth+1);
                if(i == cnt-1)
                    fn->SetLast(true);
                this->subs.push_back(fn);
            }
            
            i++;
        }
    }
    
    void GetFileType()
    {
        struct stat statBuf;
        
        if(lstat(aPath.c_str(),&statBuf) < 0)
        {
            std::cerr << "lstat() error for " << aPath << '\n';
            return;
        }
        
        if(S_ISREG(statBuf.st_mode))
            fType = REGULAR;
        else if(S_ISDIR(statBuf.st_mode))
            fType = DIRECTORY;
        else if(S_ISLNK(statBuf.st_mode))
            fType = LINK;
        else if(S_ISCHR(statBuf.st_mode))
            fType = CDEVICE;
        else if(S_ISBLK(statBuf.st_mode))
            fType = BDEVICE;
        else if(S_ISSOCK(statBuf.st_mode))
            fType = SOCKET;
    }
    
    FileNode* Find(std::string str)
    {
        if(this->aPath == str)
            return this;
                
        for(int i = 0; i < (int)subs.size(); i++)
        {
            FileNode* tmp = subs[i]->Find(str);
            
            if(tmp)
                return tmp;
        }
        
        return NULL;
    }
    
    void AddFile(std::string name)
    {
        FileNode* fn;
        char absolute[1024] = {0,};
        
        if(realpath(name.c_str(), absolute) == NULL)
        {
            std::cerr << "realpath() error\n";
            return;
        }
        
        subs[subs.size()-1]->SetLast(false);
        AssignPointer(this,fn, name, absolute, depth+1);
        fn->SetLast(true);
        subs.push_back(fn);
    }
    
    void PrintNode(bool isLast,FileNode* start,std::vector<std::vector<char>>& v,std::vector<std::string>& s)
    {
        int cur = GetDepth()-start->GetDepth();
        
        if(!cur)
        {
            v.push_back({'n'});
            s.push_back(this->fName);
            for(int i = 0; i < (int)subs.size(); i++)
            {
                if(i == (int)subs.size()-1)
                    subs[i]->PrintNode(true,start,v,s);
                else
                    subs[i]->PrintNode(false,start,v,s);
            }
        }
        else
        {
            std::vector<char> tmp;
            
            if(!isLast)
            {
                tmp.push_back('a'); // ├──
                CheckParents(this->parent,tmp,start);
            }
            else
            {
                tmp.push_back('b'); // └──
                CheckParents(this->parent,tmp,start);
            }
            
            v.push_back(tmp);
            s.push_back(this->fName);
            for(int i = 0; i < (int)subs.size(); i++)
            {
                if(i == (int)subs.size()-1)
                    subs[i]->PrintNode(true,start,v,s);
                else
                    subs[i]->PrintNode(false,start,v,s);
            }
        }
    }
    
    void CheckParents(FileNode* cur,std::vector<char>& v,FileNode* start)
    {
        if(!cur || cur == start->parent)
        {
            std::reverse(v.begin(),v.end());
            return;
        }
        
        if(!cur->isItLast && cur != start)
            v.push_back('c');
        else if(cur->isItLast && cur != start)
            v.push_back('t');
        
        CheckParents(cur->parent, v,start);
    }
};

struct FileTree
{
private:
    FileNode* node;
    std::string curDir;
    
public:
    // 지정된 루트 디렉토리로 초기화
    FileTree(std::string fPath,int initDepth)
    {
        char realPath[1024] = {0,};
        char src[512] = {0,};
        
        strcpy(src,fPath.c_str());
        if(realpath(src,realPath) == NULL)
        {
            std::cerr << "realpath() error" << '\n';
            return;
        }
        
        chdir(realPath);
        GetCurrentDir();
        node = new FileNode(NULL,fPath,realPath,initDepth);
    }

    // 현재 디렉토리를 저장할 데이터 멤버
    bool GetCurrentDir()
    {
        char cur[1024] = {0,};
        
        if(getcwd(cur,1023) == NULL)
        {
            std::cerr << "getcwd() error" << '\n';
            return false;
        }
        
        curDir = cur;
        return true;
    }
    
    // 경로명(상대,절대)를 인자로 받는 디렉토리/파일 검색 함수
    FileNode* Find(std::string name)
    {
        char absolute[1024] = {0,};
        char relative[1024] = {0,};
        
        strcpy(relative,name.c_str());
        if(realpath(relative,absolute) == NULL) // convert relative path to absolute path
        {
            std::cerr << "realpath() error" << '\n';
            return NULL;
        }
        
        return this->node->Find(absolute);
    }
    
    // 지정된 경로에서 디렉토리/파일을 추가하는 함수
    void AddFile(std::string name,FileType fType)
    {
        if(fType == DIRECTORY)
        {
            mkdir(name.c_str(), 0755);
            node->AddFile(name);
        }
        else if(fType == REGULAR)
        {
            int fd;
            
            if((fd = open(name.c_str(), O_CREAT | O_EXCL | O_RDWR)) < 0)
            {
                std::cerr << "open() error" << '\n';
                return;
            }
            close(fd);
            node->AddFile(name);
        }
    }
    
    void Print(std::string name)
    {
        // ├── └── │
        
        FileNode* target = nullptr;
        
        if((target = this->Find(name)))
        {
            std::vector<std::string> s;
            std::vector<std::vector<char>> v;
            target->PrintNode(false,target,v,s);
            
            for(int i = 0; i < (int)v.size(); i++)
            {
                for(int j = 0; j < (int)v[i].size(); j++)
                {
                    if(v[i][j] == 't')
                        std::cout << '\t';
                    else if(v[i][j] == 'a')
                        std::cout << "├── ";
                    else if(v[i][j] == 'b')
                        std::cout << "└── ";
                    else if(v[i][j] == 'c')
                        std::cout << "│   ";
                }
                
                std::cout << s[i] << '\n';
            }
            return;
        }
        else
        {
            std::cerr << "Can't print the file list\n";
            return;
        }
    }
    
    // 현재 디렉토리를 변경(디렉토리 이동)
    bool ChangeWorkingDir(std::string to)
    {
        if(chdir(to.c_str()) < 0)
        {
            std::cerr << "chdir() failed" << '\n';
            return false;
        }
        
        GetCurrentDir();
        return true;
    }
    
    void PrintCurrentDirectory()
    {
        std::cout << curDir << '\n';
    }
};

#endif /* FileSystemHeader_h */
