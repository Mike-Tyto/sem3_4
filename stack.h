#include "array_sequence.h"

template <typename T>
using Mapper = T (*)(T&);

template <typename T>
using Condition = bool (*)(T&);

template <typename T>
using Reducer = T (*)(T&, T&);

template <typename T>
class Stack
{
private:
	Sequence<T>* items;

public:
	Stack() {
		this->items = new ArraySequence<T>();
	}

	Stack(T* items, size_t size)
	{
		this->items = new ArraySequence<T>(items, size);
	}

	Stack(const Stack<T>& stack)
	{
		Sequence<T>* copy = new ArraySequence<T>();
		this->items = copy->Create();
		for (int i = 0; i < stack.Count(); i++)
			this->Push(stack.Peek(i));
	}

	Stack(Stack<T>&& stack)
	{
		this->items = stack.items;
		stack.items = nullptr;
	}

	Stack(const Sequence<T>* sequence)
	{
		this->items = sequence->Create();

		for (int i = 0; i < sequence->GetLength(); i++)
			this->items->Append(sequence->Get(i));
	}

	template <typename... Args>
	Stack(T head, Args... args)
	{
		items = new ArraySequence<T>(head, args...);
	}

	~Stack()
	{
		delete items;
	}

	Stack& operator=(const Stack<T>& stack)
	{
		delete this->items;

		Sequence<T>* copy = new ArraySequence<T>();
		this->items = copy->Create();
		for (int i = 0; i < stack.Count(); i++)
			this->EnStack(stack.Peek(i));

		return *this;
	}

	Stack& operator=(Stack<T>&& stack)
	{
		delete this->items;

		this->items = stack.items;
		stack.items = nullptr;

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

	void Push(const T& val) noexcept
	{
		this->items->Append(val);
	}

	T Pop()
	{
		T last = this->items->GetLast();
		this->items->Remove(this->items->GetLength() - 1);
		return last;
	}

	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& Stack)
	{
		os << Stack.items;
		return os;
	}

	Stack<T> Map(Mapper<T> func)
	{
		auto copy = this->items->Map(func);
		Stack<T> res = copy;
		delete copy;
		return res;
	}

	Stack<T> Where(Condition<T> filter)
	{
		auto copy = this->items->Where(filter);
		Stack<T> res = copy;
		delete copy;
		return res;
	}

	T Reduce(Reducer<T> reduce, T base) const
	{
		return this->items->Reduce(reduce, base);
	}

	Stack<T> Concat(const Stack<T>& stack)
	{
		auto copy1 = stack.items;
		auto copy2 = this->items->Concat(copy1);
		Stack<T> res = copy2;
		delete copy2;
		return res;
	}

	Stack<T> GetSubStack(int startIndex, int endIndex)
	{
		auto copy = this->items->GetSubsequence(startIndex, endIndex);
		Stack<T> res = copy;
		delete copy;
		return res;
	}
};