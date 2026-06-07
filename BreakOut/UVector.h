#pragma once

template<typename T>
class UVector
{
private:
	T* m_data;
	uint32_t _size;
	uint32_t _capacity;

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

	T& operator[](const uint32_t index)
	{
		return m_data[index];
	}



private:
	void reallocate(const uint32_t newCapacity)
	{
		T* newData = new T[newCapacity];
		for (uint32_t i = 0; i < _size; i++)
			newData[i] = m_data[i];
		delete[] m_data;
		m_data = newData;
		_capacity = newCapacity;
	}




};