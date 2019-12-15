#include "pch.h"
#include "Linko_Listo.h"
#include <iostream>
#include <cassert>
#pragma once

using namespace std;

////////////////****************That Priortiy Queue****************///////////////////
template <class T, class BOI>
class PriQ
{
public:
	PriQ(int size){
		assert(size > 0);
		m_size = size;
	}
	~PriQ() 
	{}
	void push(T val)
	{
		assert(m_elements.GetSize() < m_size);
		if (m_elements.GetSize() == 0) {
			m_elements.Push(val);
		}
		else {
			Link_buggy<T> it;
			it = m_elements.Begin();
			BOI boi; 

			while (it.isValid()){
				if (boi(val, *it)) {
					break;
				}
				it++;
			}
			if (it.isValid()) {
				m_elements.preGame(it, val);
			}
			else {
				m_elements.Push(val);
			}
		}

	}
	void pop() {
		m_elements.Pop_Front();
	}
	T& front() {
		Link_buggy<T> it;
		it = m_elements.Begin();
		return *it;
	}
	T& back() {
		Link_buggy<T> it;
		it = m_elements.Last();
		return *it;
	}
	int GetSize() {
		return m_elements.GetSize();
	}
	int GetMaxSize() {
		return m_size;
	}
	bool isEmpty() {
		return(m_elements.GetSize() == 0);
	}
	void Resize(int size) {
		assert(size > 0);
		m_size = size;
	}
private:
	#ifdef _DEBUG
	Ll
	#endif // _DEBUG
	<T> m_elements;
	int m_size;
};
///////////////////////******* COMPAIRISONS ****************/////////////////////
template<class T>
class smol_Comp {
public:
	inline bool operator()(T lVal, T rVal) {
		return (lVal < rVal);
	}
};
template<class T>
class wombo_Comp {
public:
	inline bool operator()(T lVal, T rVal) {
		return !(lVal < rVal);
	}
};
//////////////////////*******************GATHER*******************//////////////////
class getInfo {
public:
	getInfo() : m_priority(0), m_id("") {}
	getInfo(int p, string id) : m_priority(p), m_id(id) {}
	~getInfo() {}

	int GetPriority() {
		return m_priority;
	}
	string GetID() {
		return m_id;
	}
	bool operator<(getInfo& m) {
		if (m_priority < m.GetPriority()) {
			return true;
		}
		return false;
	}
	bool operator>(getInfo& m) {
		return !(*this < m);
	}
private:
	int m_priority;
	string m_id;
};
///////////////**************MAIN****************///////////////////////
int main() {
	cout << "Whats going on over there? Whats in the box? What was in the box " << endl << endl;

	const int size = 6;
	PriQ<getInfo, smol_Comp<getInfo> > que(size);


	que.push(getInfo(2, "Something that might be fun for exactly 48 seconds but has no use"));
	que.push(getInfo(2, "a bag of angry death claws"));
	que.push(getInfo(1, "Just rotten mole rat meat"));
	que.push(getInfo(2, "A plastic bag full of moldy, wet of pre-war clothing"));
	que.push(getInfo(4, "Literally nothing")); 
	que.push(getInfo(5, "200 ruined books"));

	cout << "Fallout 76 paid content loot box (Size - " << que.GetSize() << ") : " << endl;

	while (que.isEmpty() == false) {
		cout << "   Priority: " << que.front().GetPriority();
		cout << "   Items: " << que.front().GetID().c_str();
		cout << endl;
		que.pop();
	}
	cout << endl;

	if (que.isEmpty() == true){
		cout << "Opps, Guess it's empty" << endl;
	}
	else
{
		cout << "Hey look, its NOT empty" << endl;
	}
	cout << "Thank you for wast....I mean spending your money very wisely on our premium product, Enjoy!" << endl;
	return 1;
}