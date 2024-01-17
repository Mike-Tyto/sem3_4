#include "array_sequence.h"

template <typename T>
using Mapper = T (*)(T&);

template <typename T>
using Condition = bool (*)(T&);

template <typename T>
using Reducer = T (*)(T&, T&);

template <typename T>
class Queue
{
private:
	Sequence<T>* items;

public:
	Queue() {
		this->items = new ArraySequence<T>();
	}

	Queue(T* items, size_t size)
	{
		this->items = new ArraySequence<T>(items, size);
	}

	Queue(const Queue<T>& queue)
	{
		Sequence<T>* copy = new ArraySequence<T>();
		this->items = copy->Create();
		for (int i = 0; i < queue.Count(); i++)
			this->Enqueue(queue.Peek(i));
	}

	Queue(Queue<T>&& queue)
	{
		this->items = queue.items;
		queue.items = nullptr;
	}

	Queue(const Sequence<T>* sequence)
	{
		this->items = sequence->Create();

		for (int i = 0; i < sequence->GetLength(); i++)
			this->items->Append(sequence->Get(i));
	}

	template <typename... Args>
	Queue(T head, Args... args)
	{
		items = new ArraySequence<T>(head, args...);
	}

	~Queue()
	{
		delete items;
	}

	Queue& operator=(const Queue<T>& queue)
	{
		delete this->items;

		Sequence<T>* copy = new ArraySequence<T>();
		this->items = copy->Create();
		for (int i = 0; i < queue.Count(); i++)
			this->Enqueue(queue.Peek(i));

		return *this;
	}

	Queue& operator=(Queue<T>&& queue)
	{
		delete this->items;

		this->items = queue.items;
		queue.items = nullptr;

		return *this;
	}

	bool IsEmpty() const noexcept
	{
		return this->items->IsEmpty();
	}

	const T& Peek(size_t index) const
	{
		return this->items->Get(index);
	}

	size_t Count() const noexcept
	{
		return this->items->GetLength();
	}

	void Enqueue(const T& val) noexcept
	{
		this->items->Append(val);
	}

	T Dequeue()
	{
		T first = this->items->GetFirst();
		this->items->Remove(0);
		return first;
	}

	friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue)
	{
		os << queue.items;
		return os;
	}

	Queue<T> Map(Mapper<T> func)
	{
		auto copy = this->items->Map(func);
		Queue<T> res = copy;
		delete copy;
		return res;
	}

	Queue<T> Where(Condition<T> filter)
	{
		auto copy = this->items->Where(filter);
		Queue<T> res = copy;
		delete copy;
		return res;
	}

	T Reduce(Reducer<T> reduce, T base) const
	{
		return this->items->Reduce(reduce, base);
	}

	Queue<T> Concat(const Queue<T>& queue)
	{
		auto copy1 = queue.items;
		auto copy2 = this->items->Concat(copy1);
		Queue<T> res = copy2;
		delete copy2;
		return res;
	}

	Queue<T> GetSubQueue(int startIndex, int endIndex)
	{
		auto copy = this->items->GetSubsequence(startIndex, endIndex);
		Queue<T> res = copy;
		delete copy;
		return res;
	}
};