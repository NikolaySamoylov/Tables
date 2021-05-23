#pragma once

#include "polynomial.h"
#include <vector>
#include <algorithm>
#include <list>

const size_t P = 9973;

template<class T>
class Table {
public:
	// вставка данных
	virtual void insert(size_t key, const T& elem) = 0;
	// удаление данных
	virtual void erase(size_t key) = 0;
	// поиск данных
	virtual std::pair<size_t, T> find(size_t key) = 0;
	// получить размер таблицы
	virtual size_t get_size() = 0;
	// очистить таблицу
	virtual void clear() = 0;
	// проверка таблицы на пустоту
	virtual bool empty() = 0;
};

template<class T, class Cell = std::pair<size_t, T>>
class ArrayTable : public Table<T> {
protected:
	// строка таблицы
	std::vector<Cell> data;
	// размер таблицы
	size_t size;
public:
	// конструктор без параметров
	ArrayTable() { data = std::vector<Cell>(); size = 0; }
	// конструктор копирования
	ArrayTable(const ArrayTable& t) { data = t.data; size = t.size; }
	// получить размер таблицы
	size_t get_size() override { return size; }
	// очистить таблицу
	void clear() override { data.clear(); size = 0; }
	// проверка таблицы на пустоту
	bool empty() override { return (size == 0); }
	// вывод таблицы на экран
	void print()
	{
		if (empty() == true)
			throw "Table is empty!";
		else
		{
			std::cout << "Table's size is " << get_size() << '\n' << "Key:" << '\t' << '|' << '\t' << "Value:" << '\n';
			for (size_t i = 0; i < size; i++)
				std::cout << data[i].first << '\t' << '|' << '\t' << data[i].second << '\n';
		}
	}
};

template<class T = Polynomial>
class UnorderedTable : public ArrayTable<T> {
public:
	// конструктор без параметров
	UnorderedTable() : ArrayTable() {};
	// конструктор копирования
	UnorderedTable(const ArrayTable& t) : ArrayTable(t) {};
	// вставка данных
	void insert(size_t key, const T& elem) override
	{
		bool k = true;
		for (size_t i = 0; i < size; i++)
		{
			if (data[i].first == key)
				k = false;
				break;
		}
		if (k == false)
			throw "Data with the same key have already existed in the table!";
		else
		{
			data.push_back(std::make_pair(key, elem));
			size++;
		}
	}
	// удаление данных
	void erase(size_t key) override
	{
		bool k = false;
		for (size_t i = 0; i < size; i++)
			if (data[i].first == key)
			{
				data[i] = data[size - 1];
				size--;
				k = true;
				break;
			}
		if (k == false)
			throw "Data with such key does not exist in the table!";
	}
	// поиск данных
	std::pair<size_t, T> find(size_t key) override
	{
		std::pair<size_t, T> res;
		bool k = false;
		for (size_t i = 0; i < size; i++)
			if (data[i].first == key)
			{
				res = std::make_pair(key, data[i].second);
				k = true;
				break;
			}
		if (k == false)
			throw "Data with such key does not exist in the table!";
		return res;
	}
};

template<class T = Polynomial>
class OrderedTable : public ArrayTable<T> {
public:
	// конструктор без параметров
	OrderedTable() : ArrayTable() {};
	// конструктор копирования
	OrderedTable(const ArrayTable& t) : ArrayTable(t) {};
	// вставка данных
	void insert(size_t key, const T& elem) override
	{
		bool k = true;
		for (size_t i = 0; i < size; i++)
		{
			if (data[i].first == key)
				k = false;
			break;
		}
		if (k == false)
			throw "Data with the same key have already existed in the table!";
		else
		{
			auto lower = lower_bound(data.begin(), data.end(), std::make_pair(key, elem));
			data.insert(lower, std::make_pair(key, elem));
			size++;
		}
	}
	// удаление данных
	void erase(size_t key) override
	{
		bool k = false;
		for (size_t i = 0; i < size; i++)
			if (data[i].first == key)
			{
				data.erase(data.begin() + i);
				size--;
				k = true;
				break;
			}
		if (k == false)
			throw "Data with such key does not exist in the table!";
	}
	// поиск данных
	std::pair<size_t, T> find(size_t key)
	{
		size_t st, fn, mid;
		size_t res = -1;
		st = 0;
		fn = size - 1;
		while (st < fn)
		{
			mid = (st + fn) / 2;
			if (key == data[mid].first)
				res = mid;
			if (key < data[mid].first)
				fn = mid - 1;
			else 
				st = mid + 1;
		}
		if (key == data[st].first)
			res = st;
		if (st + 1 < size)
			if (key == data[st + 1].first)
				res = st + 1;
		if (res == -1)
			throw "Data with such key does not exist in the table!";
		return data[res];
	}
};

template<class T = Polynomial>
class HashTable : public Table<T> {
private:
	std::vector<std::list<std::pair<size_t, T>>> data;
	size_t size;
	size_t max_size;
	size_t a, b;
	size_t hash_function(size_t x) {return ((a * x + b) % P) % max_size;}
public:
	// конструктор с параметрами
	HashTable(size_t m)
	{
		a = rand() % P;
		b = rand() % P;
		size = 0;
		max_size = m * m;
		data.resize(max_size);
	}
	// конструктор копирования
	HashTable(HashTable& h)
	{
		data = h.data;
		size = h.size;
		max_size = h.max_size;
		a = h.a;
		b = h.b;
	}
	// вставка данных
	void insert(size_t key, const T& elem) override
	{
		size_t i = hash_function(key);
		for(auto this_it = data[i].begin(); this_it != data[i].end(); this_it++)
			if (this_it->first == key)
				throw "Data with the same key have already existed in the table!";
		data[i].push_front(std::make_pair(key, elem));
		size++;
	}
	// удаление данных
	void erase(size_t key) override
	{
		size_t i = hash_function(key);
		bool k = false;
		for (auto this_it = data[i].begin(); this_it != data[i].end(); this_it++)
			if (this_it->first == key)
			{
				data[i].erase(this_it);
				size--;
				k = true;
				break;
			}
		if (k == false)
			throw "Data with such key does not exist in the table!";
	}
	// поиск данных
	std::pair<size_t, T> find(size_t key) override
	{
		size_t i = hash_function(key);
		bool k = false;
		for (auto this_it = data[i].begin(); this_it != data[i].end(); this_it++)
			if (this_it->first == key)
			{
				k = true;
				return std::make_pair(k, this_it->second);
			}
		if (k == false)
			throw "Data with such key does not exist in the table!";
	}
	// получить размер таблицы
	size_t get_size() override { return size; }
	// очистить таблицу
	void clear() override { data.clear(); size = 0; }
	// проверка таблицы на пустоту
	bool empty() override { return (size == 0); }
};