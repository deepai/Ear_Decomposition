#ifndef _H_QUEUE
#define _H_QUEUE

template <class T>
class queue
{
	T *elements;
	int max_size;

	int curr_size;
	int curr_head;
	int curr_tail;

public:
	queue(int N)
	{
		max_size = N;
		elements = new T[max_size];
	}

	queue()
	{
	}

	void resize(int N)
	{
		max_size = N;
		elements = new T[N];
	}

	inline void push(T val)
	{
		elements[curr_tail++] = val;
	}

	inline T pop()
	{
		return elements[curr_head++];
	}

	inline bool isEmpty()
	{
		return (curr_head >= curr_tail);
	}

	~queue()
	{
		delete[] elements;
	}
};

#endif