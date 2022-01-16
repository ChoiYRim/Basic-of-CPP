#include <cstdio>
#include <functional>
#include <condition_variable>
#include <chrono>
#include <future>
#include <mutex>
#include <queue>
#include <vector>

namespace ThreadPool {
class ThreadPool
{
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    
    // add a job
    template <class F,class... Args>
    std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F&& f,Args&&... args);
    
private:
    // worker thread의 개수
    size_t num_threads_;
    // worker threads
    std::vector<std::thread> worker_threads_;
    // 할 일들을 보관하는 job queue
    std::queue<std::function<void()>> jobs_;
    // job queue를 위한 condition_variable, mutex
    std::condition_variable cv_job_q_;
    std::mutex m_job_q_;
    
    // 모든 thread 종료
    bool stop_all;
    
    // worker thread
    void WorkerThread();
};

ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false)
{
    worker_threads_.reserve(num_threads_);
    for(size_t i = 0; i < num_threads_; i++)
    {
        worker_threads_.emplace_back([this]() { return this->WorkerThread(); });
    }
}

void ThreadPool::WorkerThread()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m_job_q_);
        cv_job_q_.wait(lock,[this]() { return !this->jobs_.empty() || stop_all; });
        if(stop_all && this->jobs_.empty())
            return;
    
        std::function<void()> job = std::move(jobs_.front());
        jobs_.pop();
        lock.unlock();
        
        job();
    }
}

ThreadPool::~ThreadPool()
{
    stop_all = true;
    cv_job_q_.notify_all();
    
    for(auto& t : worker_threads_)
        t.join();
}

template <class F,class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob(F&& f, Args&&... args)
{
    if(stop_all)
        throw std::runtime_error("ThreadPool 사용중지됨");
    
    using return_type = typename std::result_of<F(Args...)>::type;
    auto job = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f),std::forward<Args>(args)...));
    std::future<return_type> job_result_future = job->get_future();
    {
        std::lock_guard<std::mutex> lock(m_job_q_);
        jobs_.push([job]() { (*job)(); });
    }
    cv_job_q_.notify_one();
    
    return job_result_future;
}

}

int work(int t,int id)
{
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
    
    return t+id;
}

int main()
{
    ThreadPool::ThreadPool pool(3);
    std::vector<std::future<int>> futures;
    
    for(int i = 0; i < 10; i++)
    {
        futures.emplace_back(pool.EnqueueJob(work, i%3+1,i));
    }
    for(auto& f : futures)
    {
        printf("result : %d\n", f.get());
    }
}
