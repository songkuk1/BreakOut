#pragma once
#include <cstdint>
#include <initializer_list>

template<typename T>
class UVector
{
private:
	T* m_data;
	uint64_t _size;
	uint64_t _capacity;

public:
	UVector<T>()
	{
		_size = 0;
		_capacity = 1;
		m_data = new T[1];
	}

	UVector<T>(const int& Insize)
	{
		_size = Insize;
		_capacity = Insize;

		m_data = new T[Insize];
	}

	~UVector<T>()
	{
		delete[] m_data;
	}
	
	//리스트 대입초기화
	UVector& operator=(std::initializer_list<T> list) {

		for (const T& item : list) {
			push_back(item);
		}
		return *this;
	}

	void push_back(const T& value)
	{
		if(_size < _capacity)
			m_data[_size++] = value;
		else
		{
			reallocate(_capacity * 2);
			m_data[_size++] = value;
		}
	}

	void pop_back()
	{
		if(_size > 0)
			_size--;
	}

	T& operator[](const uint64_t index)
	{
		return m_data[index];
	}

	size_t size()
	{
		return _size;
	}

	const T* data() { return m_data;  };

	void Clear()
	{
		for(int i =0; i < _size; ++i)
		{
			m_data[i] = nullptr;
		}
		_size = 0;
	}


private:
	void reallocate(const uint64_t newCapacity)
	{
		T* newData = new T[newCapacity];
		for (uint64_t i = 0; i < _size; i++)
			newData[i] = m_data[i];
		delete[] m_data;
		m_data = newData;
		_capacity = newCapacity;
	}




};