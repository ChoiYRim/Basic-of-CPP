#pragma once

#include <iostream>
#include <queue>
#include <string>

class Job
{
private:
    int id;
    std::string user;
    int pages;
    static int count;
    
public:
    Job(const std::string& u, int p) : user(u), pages(p), id(++count) { }
    
    friend std::ostream& operator<<(std::ostream& os,const Job& j)
    {
        os << "id: " << j.id << ", 사용자: " << j.user << ", 페이지수: " << j.pages << "장";
        return os;
    }
};

int Job::count = 0;

template<size_t N>
class Printer
{
private:
    std::queue<Job> jobs;
    
public:
    bool addNewJob(const Job& job)
    {
        if(jobs.size() == N)
        {
            std::cout << "인쇄 대기열에 추가 실패: " << job << std::endl;
            return false;
        }
        
        std::cout << "인쇄 대기열에 추가: " << job << std::endl;
        jobs.push(job);
        return true;
    }
    
    void startPrinting()
    {
        while(not jobs.empty())
        {
            std::cout << "인쇄 중: " << jobs.front() << std::endl;
            jobs.pop();
        }
    }
};
