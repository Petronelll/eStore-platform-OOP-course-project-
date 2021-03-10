#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity)
{
	this->capacity = capacity;
	this->size = 0;
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	for (auto requests_it = requestsNo.begin(); requests_it != requestsNo.end(); requests_it ++) {
		bool request_gasit_in_lru = false;
		
		//cauta requestul cerut in lru
		for (auto lru_it = lru.begin(); lru_it != lru.end(); lru_it ++) {

			//daca exista requestul cerut in lru, acesta 
			//este mutat la inceputul lui lru
			if (*lru_it == *requests_it) {
				lru.erase(lru_it);
				lru.insert(lru.begin(), *requests_it);
				request_gasit_in_lru = true;
				break;
			}
		}
		if (request_gasit_in_lru) continue;

		//daca nu mai incap requesturi noi in cache,
		// se sterge cel mai putin utilizat request din cache
		if (size == capacity) {
			lru.pop_back();
			size --;
		}

		//insereaza un nou request in lru cache
		if (!request_gasit_in_lru) {
			lru.insert(lru.begin(), *requests_it);
			size ++;
		}
	}

	return lru;
}

int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	return lru.capacity();
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	lru = aux;
}
