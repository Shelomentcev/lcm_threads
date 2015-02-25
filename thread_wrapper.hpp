#include<memory>
#include<thread>
#include<atomic>
#include<map>
#include<vector>
#include<iostream>

#pragma once

class ThreadWrapper {
public:
	ThreadWrapper();
	~ThreadWrapper();

	bool isFree();

	void start(uint64_t a_number);

	//число максимальная степень
	std::shared_ptr<std::map<uint64_t, uint64_t>> m_result;

private:
	void job(uint64_t a_number);

	std::thread m_thread;
	
	std::shared_ptr<std::atomic<bool>> m_isFree;
};