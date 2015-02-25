#include"thread_wrapper.hpp"
#include"monitor.hpp"

ThreadWrapper::ThreadWrapper() :
m_isFree(new std::atomic<bool>(true)),
m_result(new std::map<uint64_t, uint64_t>())
{

}

ThreadWrapper::~ThreadWrapper()
{

}

void ThreadWrapper::start(uint64_t a_number){
	(*m_isFree) = false;
	m_thread = std::thread(&ThreadWrapper::job, this, a_number);
	m_thread.detach();
}

void ThreadWrapper::job(uint64_t a_number) {
	
	std::shared_ptr<std::vector<uint64_t>> prime_numbers = Monitor::m_prime_numbers;
	std::map<uint64_t, uint64_t> factorization_result;
	uint64_t temp = a_number;

	while (temp != 1)
	{
		//Поиск ещё одного простого множителя
		for (auto it = prime_numbers->begin(); it != prime_numbers->end() && (*it) <= temp; ++it)
		{
			bool contain_prime_number = (temp % (*it)) == 0;

			if (contain_prime_number) {
				if (factorization_result.find(*it) != factorization_result.end()){
					factorization_result[*it] += 1;
				}
				else {
					factorization_result[*it] = 1;
				}

				temp = temp / (*it);

				break;
			}
		}
	}

	//Merge m_result and result
	for (auto it : factorization_result) {
		auto number = it.first;
		auto pow = it.second;

		auto merged = (*m_result).find(number);

		if ( merged != (*m_result).end()){
			auto merged_pow = merged->second;
			//Большое значение записываем.
			(*m_result)[number] = (merged_pow < pow) ? pow : merged_pow;
		} else {
			//Добавляем новое число
			(*m_result)[number] = pow;
		}
	}

	(*this->m_isFree).store(true);
}

bool ThreadWrapper::isFree(){
	return (*m_isFree).load();
}
