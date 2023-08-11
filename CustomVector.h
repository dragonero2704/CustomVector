#pragma once
#include <stdio.h>
#include "macros.h"
template <class Value>
class CustomVector {
private:
	size_t _capacity;
	size_t _size;
	Value* array;

	unsigned long long int newCapacity(size_t number) {
		size_t tmp = 1;
		while (tmp <= number) {
			tmp *= 2;
		}
		return tmp;
	}

	void buildArray() {
		
		if (this->array == nullptr) {
			this->array = new Value[_capacity];
			// set to 0
			for (int i = 0; i < _capacity; i++) {
				this->array[i] = 0;
			}
			return;
		}
		Value* tmp = this->array;
		this->array = new Value[_capacity];
		for (int i = 0; i < _capacity; i++) {
			if (i < _size) {
				array[i] = tmp[i];
			}
			else {
				array[i] = 0;
			}
		}
		delete[] tmp;
	}

public:
	CustomVector() {
		this->_size     = 0;
		this->_capacity = 0;
		this->array     = nullptr;
	}
	CustomVector(int size) {
		this->_size     = size;
		this->_capacity = size;
		this->array     = new Value[_capacity];
		for (int i = 0; i < _size; i++) 
		{
			this->array[i] = 0;
		}
	}

	~CustomVector() { delete[] this->array; }
	size_t size() {
		return this->_size;
	}

	void resize(size_t size) {
		this->_size   = size;
		this->_capacity = size;
		this->buildArray();
	}

	bool isempty() {
		return this->_size == 0;
	}

	void clear() {
		~CustomVector();
		this->_size     = 0;
		this->_capacity = 0;
		this->array     = nullptr;
	}

	void push_back(Value value) {
		if (this->_size >= _capacity) 
		{
			this->_capacity = this->_capacity == 0 ? 1 : newCapacity(this->_size);
			this->buildArray();
		}
		this->array[_size] = value;
		this->_size++;
	}

	void pop_back() 
	{
		this->array[_size - 1] = 0;
		this->_size--;
	}

	void assign(size_t newSize, const Value& value) {
		this->clear();
		this->_capacity = newCapacity(newSize);
		this->_size = newSize;
		this->array = new Value[_capacity];
		for (int i = 0; i < this->_size; i++) {
			this->array[i] = value;
		}
	}

	Value& operator[](size_t index) {
		return this->array[index];
	}

	Value& at(size_t index) {
		if (index >= this->_size) {
			// out of bounds
			throw std::exception("Out of bounds");
		}
		if (index < 0) {
			// go backwards
			if (abs(index) > this->_size) index %= this->_size;
			return this->array[this->_size - index];
		}
		return this->array[index];
	}
	Value& front() {
		return this->array[0];
	}
	Value& back() {
		return this->array[this->_size - 1];
	}

	size_t capacity() {
		return this->_capacity;
	}

	Value* cbegin() {
		return this->array;
	}

	Value* cend() {
		return this->array + this->_size;
	}

	Value* crbegin() {
		return this->array + (this->_size - 1);
	}
	Value* crend() {
		return this->array - 1;
	}

	Value* data() {
		return this->array;
	}

	class Iterator {
	private:
		Value* ptr;
		Value* end;
		Value* start;
	public:
	
		Iterator() {
			this->ptr   = nullptr;
			this->end   = nullptr;
			this->start = nullptr;
		}
		Iterator(Value* start, Value*end) {
			this->ptr   = start;
			this->end   = end;
			this->start = start;
		}
		~Iterator() {};
		
		void operator++(int) {
			this->ptr += 1;
			if (this->ptr == this->end) this->ptr = nullptr;
		};

		void operator--(int) {
			this->ptr -= 1;
			if (this->ptr < this->start) this->ptr = nullptr;
		};

		Value operator*() {
			
			return *(this->ptr);
		}

		Iterator* operator->() {
			return this;
		}

		bool operator!=(Iterator other) const {
			return other->ptr != this->ptr;
		}
		bool operator==(Iterator other) const {
			if (this->ptr == nullptr) return other->ptr == nullptr;
			return other->ptr == this->ptr;
		}

		Iterator& operator=(Iterator other) {
			this->start = other->start;
			this->end   = other->end;
			this->ptr   = other->ptr;
		}
	};

	Iterator begin() {
		return Iterator(this->array, this->array+this->_size);
	}

	Iterator end() {
		return Iterator();
	}

	class ReverseIterator {
	private:
		Value* ptr;
		Value* end;
		Value* start;
	public:

		ReverseIterator() {
			this->ptr   = nullptr;
			this->end   = nullptr;
			this->start = nullptr;
		}
		ReverseIterator(Value* start, Value* end) {
			this->ptr   = start;
			this->end   = end;
			this->start = start;
		}
		~ReverseIterator() {};

		void operator++(int) {
			this->ptr -= 1;
			if (this->ptr < this->start) this->ptr = nullptr;
		};

		void operator--(int) {
			this->ptr += 1;
			if (this->ptr == this->end) this->ptr = nullptr;
		};

		Value operator*() {
			return *(this->ptr);
		}

		ReverseIterator* operator->() {
			return this;
		}

		bool operator!=(ReverseIterator other) const {
			return other->ptr != this->ptr;
		}
		bool operator==(ReverseIterator other) const {
			if (this->ptr == nullptr) return other->ptr == nullptr;
			return other->ptr == this->ptr;
		}

		Iterator& operator=(Iterator other) {
			this->start = other->start;
			this->end = other->end;
			this->ptr = other->ptr;
		}
	};
	ReverseIterator rbegin() {
		return ReverseIterator(this->array, this->array + this->_size);
	}
	ReverseIterator rend() {
		return ReverseIterator();
	}
};