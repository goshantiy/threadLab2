#pragma once
#include <mutex>
#include <queue>
#include <thread>
template <typename T>
class SafeQueue
{
public:
	explicit SafeQueue() = default;
	void push(const T& value);
	void pop();
	bool empty();
	T& front();
	T& back();
	size_t size();
private:
	std::queue<T> q;
	mutable std::mutex mute;
};
template<typename T>
T& SafeQueue<T>::front()
{
	std::lock_guard<std::mutex> lock(mute);
	return q.front();
}
template<typename T>
T& SafeQueue<T>::back()
{
	std::lock_guard<std::mutex> lock(mute);
	return q.back();
}
template<typename T>
size_t SafeQueue<T>::size()
{
	std::lock_guard<std::mutex> lock(mute);
	return q.size();
}
template<typename T>
void SafeQueue<T>::push(const T& value)
{
	std::lock_guard<std::mutex> lock(mute);
	q.push(value);
}
template<typename T>
void SafeQueue<T>::pop()
{
	std::lock_guard<std::mutex> lock(mute);
	q.pop();
}

template<typename T>
inline bool SafeQueue<T>::empty()
{
	std::lock_guard<std::mutex> lock(mute);
	return q.empty();
}

