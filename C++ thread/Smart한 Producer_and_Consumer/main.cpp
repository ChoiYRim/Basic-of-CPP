#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <condition_variable> // 조건 변수

void producer(std::queue<std::string>* downloaded_pages,std::mutex* m,
              int index,std::condition_variable* cv)
{
    for(int i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100*index));
        std::string content = "Website : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";
        
        m->lock();
        downloaded_pages->push(content);
        m->unlock();
        
        cv->notify_one(); // consumer에게 content가 준비되었음을 알린다.
    }
}

void consumer(std::queue<std::string>* downloaded_pages,std::mutex* m,
              int* num_processed,std::condition_variable* cv)
{
    while(*num_processed < 25)
    {
        //m->lock();
        std::unique_lock<std::mutex> lk(*m);
        
        cv->wait(lk,[&]{ return !downloaded_pages->empty() || *num_processed == 25; });
        if(*num_processed == 25)
        {
            lk.unlock();
            return;
        }
        
        std::string content = downloaded_pages->front();
        downloaded_pages->pop();
        
        (*num_processed)++;
        //m->unlock();
        lk.unlock();
        
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}

int main()
{
    std::queue<std::string> downloaded_pages;
    std::mutex m;
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    std::condition_variable cv;
    int num_processed = 0;
    
    for(int i = 0; i < 5; i++)
        producers.push_back(std::thread(producer,&downloaded_pages,&m,i+1,&cv));
    for(int i = 0; i < 3; i++)
        consumers.push_back(std::thread(consumer,&downloaded_pages,&m,&num_processed,&cv));
    
    for(int i = 0; i < 5; i++)
        producers[i].join();
    
    // 나머지 자고 있는 쓰레드들을 모두 깨운다.
    cv.notify_all();
    
    for(int i = 0; i < 3; i++)
        consumers[i].join();
    
    return 0;
}
