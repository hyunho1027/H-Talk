#pragma once

template <typename T>
struct DoublyNodeType
{
	T component;
	DoublyNodeType<T>* pre;
	DoublyNodeType<T>* next;
};
