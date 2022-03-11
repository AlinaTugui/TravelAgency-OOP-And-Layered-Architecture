#pragma once
#include <vector>
#include <algorithm>
using std::vector;

class Observer {
public:
	virtual void update() = 0;
};


class Observable {
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}
	void notifyObservers() {
		for (auto obs : observers) {
			obs->update();
		}
	}
};