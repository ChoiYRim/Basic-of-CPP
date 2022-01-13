#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct n_ary_node
{
    std::string name;
    bool is_dir;
    std::vector<n_ary_node*> children;
};

class file_system
{
    using node = n_ary_node;
    using node_ptr = node*;
    
private:
    node_ptr root;
    node_ptr cwd;
    
    node_ptr find_impl(node_ptr directory,const std::string& path)
    {
        if(path.empty())
            return directory;
        
        auto sep = path.find('/');
        std::string current_path = sep == std::string::npos ? path : path.substr(0,sep);
        std::string rest_path = sep == std::string::npos ? "" : path.substr(sep+1);
        auto found = std::find_if(directory->children.begin(),directory->children.end(),
            [&](const node_ptr child)
        {
            return child->name == current_path;
        });
        
        if(found != directory->children.end())
            return find_impl(*found, rest_path);
        return nullptr;
    }
    
    bool add_impl(node_ptr directory,const std::string& path,bool is_dir)
    {
        if(not directory->is_dir)
        {
            std::cout << directory->name << "은(는) 파일입니다." << std::endl;
            return false;
        }
        
        auto sep = path.find('/');
        
        if(sep == std::string::npos)
        {
            auto found = std::find_if(directory->children.begin(),directory->children.end(),
            [&](const node_ptr child)
            {
                return child->name == path;
            });
            
            if(found != directory->children.end())
            {
                return false;
            }
            
            directory->children.push_back(new node{path,is_dir,{}});
            return true;
        }
        
        std::string next_dir = path.substr(0,sep);
        auto found = std::find_if(directory->children.begin(),directory->children.end(),
        [&](const node_ptr child)
        {
            return child->name == next_dir && child->is_dir;
        });
        
        if(found != directory->children.end())
            return add_impl(*found,path.substr(sep+1), is_dir);
        
        std::cout << directory->name << "에 " << next_dir << " 이름의 디렉토리가 없습니다." << std::endl;
        return false;
    }
    
public:
    file_system()
    {
        root = new node{"/",true,{}};
        cwd = root;
    }
    
    node_ptr find(const std::string& path)
    {
        if(path[0] == '/') // absolute path
            return find_impl(root,path.substr(1));
        return find_impl(cwd,path);
    }
    
    bool add(const std::string& path, bool is_dir)
    {
        if(path[0] == '/')
            return add_impl(root,path.substr(1),is_dir);
        return add_impl(cwd,path,is_dir);
    }
    
    bool change_dir(const std::string& path)
    {
        auto found = find(path);
        
        if(found && found->is_dir)
        {
            cwd = found;
            std::cout << "현재 디렉토리를 " << cwd->name << "로 이동합니다." << std::endl;
            return true;
        }
        
        std::cout << path << " 경로를 찾을 수 없습니다." << std::endl;
        return false;
    }
    
    void show_path(const std::string& path)
    {
        auto found = find(path);
        
        if(not found)
        {
            std::cout << path << " 경로가 존재하지 않습니다." << std::endl;
            return;
        }
        
        if(found->is_dir)
        {
            for(auto child : found->children)
                std::cout << (child->is_dir ? "d " : "- ") << child->name << std::endl;
        }
        else
            std::cout << "- " << found->name << std::endl;
    }
};
