#include <stdio.h>
#include "macros.h"
#include <exception>

typedef unsigned long long size_t;

template <class Value>
class CustomVector
{
private:
	size_t _capacity;
	size_t _size;
	Value *array;

	unsigned long long int newCapacity(size_t number)
	{
		size_t tmp = 1;
		while (tmp < number)
		{
			tmp *= 2;
		}
		return tmp;
	}

	void buildArray()
	{
		if (this->array == nullptr)
		{
			this->array = new Value[this->_capacity];
			// set to 0
			for (int i = 0; i < this->_capacity; i++)
			{
				this->array[i] = 0;
			}
			return;
		}
		Value *tmp = this->array;
		this->array = new Value[this->_capacity];
		for (int i = 0; i < this->_capacity; i++)
		{
			if (i < _size)
			{
				this->array[i] = tmp[i];
			}
			else
			{
				this->array[i] = 0;
			}
		}
		delete[] tmp;
	}

	class BaseIterator
	{
	protected:
		Value *ptr;
		Value *end;
		Value *start;

	public:
		bool operator==(const BaseIterator &other)
		{
			return this->ptr == other.ptr;
		}

		bool operator!=(const BaseIterator &other)
		{
			return this->ptr != other.ptr;
		}

		Value &operator*()
		{
			return *(this->ptr);
		}
		BaseIterator operator->()
		{
			return this;
		}
		BaseIterator &operator=(const BaseIterator &other)
		{
			this->ptr = other->ptr;
			this->start = other->start;
			this->end = other->end;
		}
	};

public:
	CustomVector()
	{
		this->_size = 0;
		this->_capacity = 0;
		this->array = nullptr;
	}
	CustomVector(const int &size)
	{
		this->assign(size, 0);
	}

	~CustomVector()
	{
		delete[] this->array;
		this->_size = 0;
		this->_capacity = 0;
	}
	size_t size()
	{
		return this->_size;
	}

	void resize(size_t size)
	{
		this->_size = size;
		this->_capacity = size;
		this->buildArray();
	}

	bool isempty()
	{
		return this->_size == 0;
	}

	void clear()
	{
		this->~CustomVector();
		this->_size = 0;
		this->_capacity = 0;
		this->array = nullptr;
	}

	void push_back(const Value &value)
	{
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

	void assign(const size_t &newSize, const Value &value)
	{
		this->clear();
		this->_capacity = newCapacity(newSize);
		this->_size = newSize;
		this->array = new Value[_capacity];
		for (int i = 0; i < this->_size; i++)
		{
			this->array[i] = value;
		}
	}

	Value &operator[](const size_t &index)
	{
		return this->array[index];
	}

	Value &at(size_t index)
	{
		if (index >= this->_size)
		{
			// out of bounds
			throw std::exception("Out of bounds");
		}
		if (index < 0)
		{
			// go backwards
			if (index * -1 > this->_size)
				index %= this->_size;
			return this->array[this->_size - index];
		}
		return this->array[index];
	}
	Value &front()
	{
		return this->array[0];
	}
	Value &back()
	{
		return this->array[this->_size - 1];
	}

	size_t capacity()
	{
		return this->_capacity;
	}

	Value *data()
	{
		return this->array;
	}

	class Iterator : public BaseIterator
	{
	public:
		Iterator()
		{
			this->ptr = nullptr;
			this->end = nullptr;
			this->start = nullptr;
		}
		Iterator(Value *ptr, Value *start, Value *end)
		{
			this->ptr = ptr;
			this->end = end;
			this->start = start;
		}
		~Iterator() {}

		void operator++(int)
		{
			this->ptr += 1;
			if (this->ptr == this->end)
				this->ptr = nullptr;
		}

		void operator--(int)
		{
			this->ptr -= 1;
			if (this->ptr < this->start)
				this->ptr = nullptr;
		}
	};

	Iterator begin()
	{
		return Iterator(this->array, this->array, this->array + this->_size);
	}

	Iterator end()
	{
		return Iterator();
	}

	const Iterator cbegin()
	{
		return this->begin();
	}

	const Iterator cend()
	{
		return this->end();
	}

	class ReverseIterator : public BaseIterator
	{
	public:
		ReverseIterator()
		{
			this->ptr = nullptr;
			this->end = nullptr;
			this->start = nullptr;
		}
		ReverseIterator(Value *ptr, Value *start, Value *end)
		{
			this->ptr = ptr;
			this->end = end;
			this->start = start;
		}
		~ReverseIterator(){};

		void operator++(int)
		{
			this->ptr -= 1;
			if (this->ptr < this->start)
				this->ptr = nullptr;
		};

		void operator--(int)
		{
			this->ptr += 1;
			if (this->ptr == this->end)
				this->ptr = nullptr;
		};
	};

	ReverseIterator rbegin()
	{
		return ReverseIterator(this->array, this->array + this->_size);
	}

	ReverseIterator rend()
	{
		return ReverseIterator();
	}

	const ReverseIterator crbegin()
	{
		return this->rbegin();
	}
	const ReverseIterator crend()
	{
		return this->rend();
	}
};
