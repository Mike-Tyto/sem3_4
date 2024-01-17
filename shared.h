#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>

template <class T>
class SharedPtr
{
private:
	T* ptr;
	int* counter;

	int* GetCounter() const
	{
		return counter;
	}

	// std::move

public:
	SharedPtr() noexcept
	    : ptr(nullptr)
	    , counter(new int(0))
	{
	}

	SharedPtr(std::nullptr_t) noexcept
	    : ptr(nullptr)
	    , counter(new int(0))
	{
	}

	SharedPtr(T* object) noexcept
	    : ptr(object)
	    , counter(new int(1))
	{
	}

	SharedPtr(const SharedPtr<T>& other) noexcept
	    : ptr(other.ptr)
	    , counter(other.counter)
	{
		if (other.counter)
		{
			(*counter)++;
		}
	}

	~SharedPtr() noexcept
	{
		cleanup();
	}

	static SharedPtr<T> makeShared(T&& val) {
		return SharedPtr<T>(new T(val));
	}

	static SharedPtr<T> makeShared() {
		return SharedPtr<T>(new T());
	}

	SharedPtr<T>& operator=(const SharedPtr<T>& other) noexcept
	{
		cleanup();
		this->ptr = other.ptr;
		this->counter = other.counter;
		if (counter)
		{
			(*counter)++;
		}

		return *this;
	}

	SharedPtr<T>& operator=(std::nullptr_t) noexcept
	{
		reset();

		return *this;
	}

	SharedPtr<T>& operator=(SharedPtr<T>&& other)
	{

		ptr = other.ptr;
		counter = other.counter;

		other.ptr = nullptr;
		other.counter = nullptr;

		return *this;
	}

	SharedPtr<T>& operator=(T* other) {
		cleanup();
		ptr = other;
		counter = new int(1);
		return *this;
	}

	T* operator->() const
	{
		return ptr;
	}

	T& operator*() const
	{
		return *ptr;
	}

	T& operator[](int index) const
	{
		return ptr[index];
	}

	operator bool() const
	{
		return ptr;
	}

	bool operator==(T* other) const
	{
		return ptr == other;
	}

	bool operator==(std::nullptr_t) const
	{
		return ptr == nullptr;
	}

	T* Get() const noexcept
	{
		return this->ptr;
	}

	T* release() noexcept
	{
		T* result = nullptr;
		std::swap(result, ptr);
		*counter = 0;
		return result;
	}

	void swap(SharedPtr<T>& other) noexcept
	{
		std::swap(ptr, other.ptr);
		std::swap(counter, other.counter);
	}

	int UseCount() const
	{
		return *(this->counter);
	}

	bool Unique() const
	{
		return UseCount() == 1;
	}

	void reset() noexcept
	{
		T* temp = release();
		*counter = 0;
		delete temp;
	}

private:
	void cleanup() noexcept
	{
		if (counter)
		{
			(*counter)--;

			if (*counter <= 0)
			{
				if (ptr != nullptr)
				{
					delete ptr;
				}

				delete counter;
			}
		}
	}
};

template <class T>
void swap(SharedPtr<T>& left, SharedPtr<T>& right)
{
	left.swap(right);
}

template <class T>
class SharedPtr<T[]>
{
private:
	T* ptr;
	int* counter;

	int* GetCounter() const
	{
		return counter;
	}

public:
	SharedPtr(T* object) noexcept
	    : ptr(object)
	    , counter(new int(1))
	{
	}

	SharedPtr() noexcept
	    : ptr(nullptr)
	    , counter(new int(0))
	{
	}

	SharedPtr(std::nullptr_t) noexcept
	    : ptr(nullptr)
	    , counter(new int(0))
	{
	}

	SharedPtr(const SharedPtr<T[]>& other) noexcept
	    : ptr(other.ptr)
	    , counter(other.counter)
	{
		if (other.counter)
		{
			(*counter)++;
		}
	}

	~SharedPtr() noexcept
	{
		cleanup();
	}

	static SharedPtr<T[]> makeShared(std::initializer_list<T>&& val, size_t size) {
		T* res = new T[size];
		int i = 0;
		for (T x: val) {
			res[i++] = x;
		}
		return SharedPtr<T[]>(res);
	}

	static SharedPtr<T[]> makeShared(size_t size) {
		return SharedPtr<T[]>(new T[size]);
	}

	SharedPtr<T[]>& operator=(const SharedPtr<T[]>& other) noexcept
	{
		cleanup();
		this->ptr = other.ptr;
		this->counter = other.counter;
		if (counter)
		{
			(*counter)++;
		}

		return *this;
	}

	SharedPtr<T[]>& operator=(std::nullptr_t) noexcept
	{
		reset();

		return *this;
	}

	SharedPtr<T[]>& operator=(SharedPtr<T[]>&& other)
	{

		ptr = other.ptr;
		counter = other.counter;

		other.ptr = nullptr;
		other.counter = nullptr;

		return *this;
	}

	SharedPtr<T[]>& operator=(T* other) {
		cleanup();
		ptr = other;
		counter = new int(1);
		return *this;
	}

	T* operator->() const
	{
		return ptr;
	}

	T& operator*() const
	{
		return *ptr;
	}

	T& operator[](int index) const
	{
		return ptr[index];
	}

	operator bool() const
	{
		return ptr;
	}

	bool operator==(T* other) const
	{
		return ptr == other;
	}

	bool operator==(std::nullptr_t) const
	{
		return ptr == nullptr;
	}

	T* Get() const noexcept
	{
		return this->ptr;
	}

	T* release() noexcept
	{
		T* result = nullptr;
		std::swap(result, ptr);
		*counter = 0;
		return result;
	}

	void swap(SharedPtr<T[]>& other) noexcept
	{
		std::swap(ptr, other.ptr);
		std::swap(counter, other.counter);
	}

	int UseCount() const
	{
		return *(this->counter);
	}

	bool Unique() const
	{
		return UseCount() == 1;
	}

	void reset() noexcept
	{
		T* temp = release();
		*counter = 0;
		delete[] temp;
	}

private:
	void cleanup() noexcept
	{
		if (counter)
		{
			(*counter)--;

			if (*counter <= 0)
			{
				if (ptr != nullptr)
				{
					delete[] ptr;
				}

				delete counter;
			}
		}
	}
};
