#include<memory>
#include<thread>
#include<vector>
#include<set>
#include<map>

#include"thread_wrapper.hpp"

#pragma once

class Monitor {
public:
	Monitor();

	~Monitor();

	static const std::shared_ptr<std::vector<uint64_t>> m_prime_numbers;
private:
	std::vector<std::unique_ptr<ThreadWrapper>> m_thread_pool;
	std::map<uint64_t, uint64_t> m_lcm;
	std::set<uint64_t> m_numbers;
};
