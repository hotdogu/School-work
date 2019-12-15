#pragma once
#include <cassert>

template<class T> class Link_buggy;
template<class T> class Ll;
/////////////////**************NODLES*******************//////////////////////
template <class T>
class Node_le {
	friend class Link_buggy<T>;
	friend class Ll<T>;
private:
	T m_data;
	Node_le* m_next;
	Node_le* m_previous;
};
////////////////////************Makin changes to the list*****************//////////////
template <class T>
class Link_buggy {
public:
	friend class Ll<T>;

	Link_buggy() {
		m_node = NULL;
	}
	~Link_buggy() {
	}
	void operator=(Node_le<T>* node){
		m_node = node;
	}
	T& operator*(){
		assert(m_node != NULL);
		return m_node->m_data;
	}
	void operator++() {
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	void operator++(int) {
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	void operator--() {
		assert(m_node != NULL);
		m_node = m_node->m_previous;
	}
	void operator--(int) {
		assert(m_node != NULL);
		m_node = m_node->m_previous;
	}
	bool operator!=(Node_le<T>* node) {
		return (m_node != node);
	}
	bool operator==(Node_le<T>* node) {
		return (m_node == node);
	}
	bool isValid() {
		return (m_node != NULL);
	}
private:
	Node_le<T>* m_node;
};

////////////////////**********LINK LIST big boio***************////////////////
template <class T>
class Ll {
public:
	Ll() : m_size(0), m_root(0), m_lastNode(0) {
	}
	~Ll() {
		while (m_root) {
			Pop();
		}
	}
	Node_le<T>* Begin() {
		assert(m_root != NULL);
		return m_root;
	}
	Node_le<T>* End() {
		return NULL;
	}
	Node_le<T>* Last() {
		return m_lastNode;
	}
	void preGame(Link_buggy<T>& it, T newData) {
		assert(it.m_node != NULL);

		Node_le<T>* node = new Node_le<T>;
		assert(node != NULL);

		node->m_data = newData;
		node->m_next = it.m_node;
		node->m_previous = it.m_node->m_previous;

		if (node->m_previous != NULL) {
			node->m_previous->m_next = node; 
		}
		it.m_node->m_previous = node;

		if (it.m_node == m_root) {
			m_root = node;
		}
		m_size++;
	}
	void postGame(Link_buggy<T>& it, T newData) {
		assert(it.m_node != NULL);

		Node_le<T>* node = new Node_le<T>;
		assert(node != NULL);

		node->m_data = newData;
		node->m_next = it.m_node->m_next;
		node->m_previous = it.m_node;

		if (node->m_next != NULL) {
			node->m_next->m_previous = node;
		}
		it.m_node->m_next = node;

		if (it.m_node == m_lastNode){
			m_lastNode = node;
		}
		m_size++;
	}
	void Push_Front(T newData) {
		Node_le<T>* node = new Node_le<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;
		node->m_previous = NULL;

		if (m_root != NULL) {
			node->m_next = m_root;
			m_root->m_previous = node;
			m_root = node;
		}
		else {
			m_root = node;
			m_lastNode = node;
		}
		m_size++;
	}
	void Pop_Front() {
		assert(m_root != NULL);
		Node_le<T>* temp = m_root;

		m_root = m_root->m_next;

		if (m_root != NULL) {
			m_root->m_previous = NULL;
		}
		else {
			m_lastNode = NULL;
		}
		delete temp;
		temp = NULL;
		m_size = (m_size == 0 ? m_size : m_size - 1);
	}
	void Push(T newData) {
		Node_le<T>* node = new Node_le<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;
		node->m_previous = NULL;

		if (m_lastNode != NULL) {
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode;
		}
		else {
			m_root = node;
		}
		m_lastNode = node;
		m_size++;
	}
	void Pop(){
		assert(m_root != NULL);

		if (m_root->m_next == NULL) {
			delete m_root;
			m_root = NULL;
			m_lastNode = NULL;
		}
		else {
			Node_le<T>* prevNode = m_lastNode->m_previous;
			prevNode->m_next = NULL;
			delete m_lastNode;
			m_lastNode = prevNode;
			prevNode = NULL;
		}
		m_size = (m_size == 0 ? m_size : m_size - 1);
	}
	int GetSize() {
		return m_size;
	}
private:
	int m_size;				
	Node_le<T>* m_root;	
	Node_le<T>* m_lastNode;
};