#pragma once
#include <set>
#include <algorithm>

template <class T>
class TSet
{
public:
	TSet() {};
	TSet(const std::set<T>& st) : m_set(st) {};
	void clear() { m_set.clear(); }
	void add(const T& item) { m_set.insert(item); }
	void remove(const T& removable) { m_set.erase(removable); }
	bool empty() const noexcept { return m_set.empty(); }
	bool belongs(const T& item) { return m_set.count(item); }
	size_t size() { return m_set.size(); }
	TSet<T> unions(const TSet<T>& st);
	TSet<T> subtract(const TSet<T>& st);
	TSet<T> multiply(const TSet<T>& st);
	T at(size_t index);

private:
	std::set<T> m_set;
};

template<class T>
inline TSet<T> TSet<T>::unions(const TSet<T>& st)
{
	std::set<T> res;
	std::set_union(m_set.cbegin(), m_set.cend(), 
		st.m_set.cbegin(), st.m_set.cend(), 
		std::inserter(res, res.begin()));
	return TSet<T>(res);
}

template<class T>
inline TSet<T> TSet<T>::subtract(const TSet<T>& st)
{
	std::set<T> res;
	std::set_difference(m_set.cbegin(), m_set.cend(),
		st.m_set.cbegin(), st.m_set.cend(),
		std::inserter(res, res.begin()));
	return TSet<T>(res);
}

template<class T>
inline TSet<T> TSet<T>::multiply(const TSet<T>& st)
{
	std::set<T> res;
	std::set_intersection(m_set.cbegin(), m_set.cend(),
		st.m_set.cbegin(), st.m_set.cend(),
		std::inserter(res, res.begin()));
	return TSet<T>(res);
}

template<class T>
inline T TSet<T>::at(size_t index)
{
	if (index >= m_set.size()) {
		throw std::out_of_range("Index " + std::to_string(index) + " out of range");
	}
	auto it = m_set.begin();
	std::advance(it, index);
	return *it;
}
