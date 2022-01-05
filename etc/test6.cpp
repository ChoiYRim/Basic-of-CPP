#include <iostream>
#include <string>
#include <string_view>
#include <mutex>
#include <thread>
#include <queue>
#include <fstream>
#include <sstream>
#include <chrono>

class Logger
{
	public:
		// 로그 항목을 파일에 저장하는 백그라운드 스레드를 구현
		Logger();
		// 백그라운드 스레드를 정상적으로 종료시킨다.
		virtual ~Logger();

		// 복제 생성자와 대입 연산자를 삭제한다
		Logger(const Logger& src) = delete;
		Logger& operator=(const Logger& rhs) = delete;
		// 로그 항목을 큐에 저장하는 함수
		void log(std::string_view entry);

	private:
		// 백그라운드 스레드의 종료 여부를 표시하는 부울 변수
		bool mExit = false;			
		// 백그라운드 스레드에서 실행할 함수
		void processEntries();
		// 큐 동기화에 사용할 뮤텍스와 조건 변수
		std::mutex mMutex;
		std::condition_variable mCondVar;
		std::queue<std::string> mQueue;
		std::thread mThread;
};

Logger::Logger()
{
	// 백그라운드 스레드를 구동한다.
	mThread = std::thread{&Logger::processEntries, this};
}

Logger::~Logger()
{
	{
		std::unique_lock lock(mMutex);
		// mExit를 true로 설정하고 스레드에 알람을 보내서 스레드를 정상 종료시킨다.
		mExit = true;
		// 스레드를 깨우도록 조건 변수에 알람을 보낸다.
		mCondVar.notify_all();
	}

	// 스레드가 종료될 때까지 기다린다.
	mThread.join();
}

void Logger::log(std::string_view entry)
{
	// 뮤텍스에 락을 걸고 큐에 항목을 추가한다.
	std::unique_lock lock(mMutex);
	mQueue.push(std::string(entry));
	// 스레드를 깨우는 조건 변수에 알림을 보낸다.
	mCondVar.notify_all();
}

void Logger::processEntries()
{
	std::ofstream logFile("log.txt");
	if(logFile.fail())
	{
		std::cerr << "Failed to open log file." << std::endl;
		return;
	}

	std::unique_lock lock(mMutex);
	while(1)
	{
		// 알림이 오기를 기다린다.
		mCondVar.wait(lock);

		std::unique_lock lock(mMutex);
		while(1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			if(!mExit) // 종료 상황이 아니면 알람을 기다린다
			{
				mCondVar.wait(lock);
			}

			// 큐에 항목이 추가되거나 스레드를 종료시킬 상황이 발생하면
			// 조건 변수에 알람이 전달된다.
			lock.unlock();
			while(1)
			{
				lock.lock();
				if(mQueue.empty())
					break;
				else
				{
					logFile << mQueue.front() << std::endl;
					mQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}
	}
}

void logSomeMessages(int id,Logger& logger)
{
	for(int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "Log entry " << i << " from thread " << id;
		logger.log(ss.str());
	}
}

int main()
{
	Logger logger;
	std::vector<std::thread> threads;

	for(int i = 0; i < 10; i++)
		threads.emplace_back(logSomeMessages, i, std::ref(logger));
	for(auto& t : threads)
		t.join();

	return 0;
}
