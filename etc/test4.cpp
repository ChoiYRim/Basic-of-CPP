// 사용 예시 2

#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;
thread_local unsigned int i = 0;

void threadFunc(int nId)
{
	++i;
	std::unique_lock<std::mutex> lock(mtx);
	std::cout << nId << "-thread : " << i << std::endl;
}

int main(int argc,char* argv[])
{
	std::thread t1(threadFunc,0),t2(threadFunc,1);

	std::unique_lock<std::mutex> lock(mtx);
	std::cout << "Main thread : " << i << std::endl;
	lock.unlock();

	t1.join();
	t2.join();

	return 0;
}
