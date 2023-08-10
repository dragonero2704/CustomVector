#pragma once
#include <stdio.h>
#include "macros.h"
template <class Typename>
class CustomVector {
private:
	size_t MAXSIZE;
	size_t _size;
	Typename* array;

	unsigned long long int nearest2pow(int number) {
		int tmp = 1;
		while (tmp < number) {
			tmp *= 2;
		}
		return tmp;
	}

public:
	CustomVector() {
		this->_size = 0;
		this->MAXSIZE = 0;
		this->array = nullptr;
	}
	CustomVector(int size) {
		this->_size = size;
		this->MAXSIZE = size;
		this->array = new Typename[MAXSIZE];
		for (int i = 0; i < _size; i++) {
			this->array[i] = 0;
		}
	}

	~CustomVector() {
		if (this->array != nullptr) delete this->array;
	}
	size_t size() {
		return this->_size;
	}

	void resize(size_t size) {
		this->_size = size;
		this->MAXSIZE = size;
	}

	void resize() {

	}

	bool isempty() {
		return this->_size == 0;
	}

	void empty() {
		~CustomVector();
		this->_size = 0;
		this->MAXSIZE = 0;
	}

	void push(Typename value) {
		if (this->_size >= MAXSIZE) {
			this->MAXSIZE *= 2;
			this->resize();
		}
		this->array[_size] = value;
		this->_size++;
	}

	Typename& operator[](int index) {
		return this->array[index];
	}
};