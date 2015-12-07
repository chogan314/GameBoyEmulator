#ifndef UTILS_H
#define UTILS_H

template <typename T>
bool TestBit(T data, int offset)
{
	T mask = 1 << offset;
	return (data & mask) > 0;
}

template <typename T>
void SetBit(T &data, int offset)
{
	T mask = 1 << offset;
	data |= mask;
}

template <typename T>
void ResetBit(T &data, int offset)
{
	T mask = 1 << offset;
	data &= ~mask;
}

#endif