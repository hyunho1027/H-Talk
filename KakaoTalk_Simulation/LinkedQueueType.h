#pragma once

#include "Msg.h"

using namespace std;

template <typename T>
struct NodeType
{
	T component;
	NodeType<T>* link;
};
/**
*	@brief	Exception class thrown by Dequeue when queue is empty.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	Display a message for empty queue on screen.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

/**
*	@brief	Queue class.
*	@details	This class processes as First In, First Out (FIFO), 템플릿을 적용해 다양한 변수 타입을 저장할 수 있다.
*/
template <typename T>
class LinkedQueueType
{
public:
	/**
	*	@brief	Allocate dynamic array whose size is maxQueue.
	*	@pre	The maxQueue is defined
	*	@post	Member of items points the allocated array.
	*/
	LinkedQueueType();


	/**
	*	@brief	Destruct the object. Free the array dynamically allocated.
	*	@pre	Release memory for queue pointer.
	*	@post	none.
	*/
	~LinkedQueueType();



	/**
	*	@brief	Determines whether the queue is empty.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is empty)
	*/
	bool IsEmpty();

	/**
	*	@brief	Makes the queue empty.
	*	@pre	Queue has been initialized.
	*	@post	m_iFront와 m_iRear is set same value as Constructer.
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds newItem to the last of the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is full), FullQueue exception is thrown; otherwise, newItem is at the last.
	*/
	void EnQueue(T item);

	/**
	*	@brief	Removes first item from the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is empty), EmptyQueue exception is thrown; otherwise, first element has been removed from queue. item gets value of removed item.
	*/
	void DeQueue(T&item);

	/**
	*	@brief	delete by index.
	*	@pre	List should be non empty.
	*	@param	index delete index you want to
	*	@post	data is deleted .
	*	@return	return 1 if success, otherwise return -1.
	*/
	int DeleteByIndex(int index);

	/**
	*	@brief	user's data .
	*	@pre	user's data is set.
	*	@param	index wanna get index
	*	@post	get user's data .
	*	@return	return data by index.
	*/
	T& operator[](int index);

private:
	NodeType<T>* q_iFront;		///< Nodepointer of one infront of the first element.
	NodeType<T>* q_iRear;		///< Nodepointer of the last element.
	int Length;					///< Length
};

//Allocate dynamic array whose size is maxQueue.
template <typename T>
LinkedQueueType<T>::LinkedQueueType()
{
	Length = 0;
	q_iFront = NULL;
	q_iRear = NULL;
}


//Destruct the object. Free the array dynamically allocated.
template <typename T>
LinkedQueueType<T>::~LinkedQueueType()
{}


//Determines whether the queue is empty.
template <typename T>
bool LinkedQueueType<T>::IsEmpty()
{
	if (!Length)
		return 1;	//q_iFront가 NULL인경우는 queue가 비어있는 상태이므로 1을 리턴한다.
	return 0;	//비어있지 않으면 0을 리턴한다.
}

//Makes the queue empty.
template <typename T>
void LinkedQueueType<T>::MakeEmpty()
{
	NodeType<T>* tempPtr;

	while (q_iRear != NULL)
	{
		tempPtr = q_iRear;
		q_iRear = q_iRear->link;
		delete tempPtr;
	}

	Length = 0;
}

//Adds newItem to the last of the queue.
template <typename T>
void LinkedQueueType<T>::EnQueue(T item)
{
	//인풋 데이타 받는 임시형 NodeType변수
	NodeType<T>* data = new NodeType<T>;
	data->component = item;
	data->link = NULL;

	//만약 노드가 하나도 없으면
	if (!Length)
	{
		q_iFront = data;
		q_iRear = data;
	}
	//노드안에 데이타가 존재하면
	else
	{
		//마지막 노드 지목
		q_iRear->link = data;

		//마지막 노드 뒤에 저장
		q_iRear = data;
	}
	Length++;
}

//Removes first item from the queue.
template <typename T>
void LinkedQueueType<T>::DeQueue(T& item)
{
	if (IsEmpty())
		throw EmptyQueue();	//비어있을땐 throw EmptyQueue
	else
	{
		//만약 노드가 1개라면
		if (Length == 1)
		{
			item = q_iFront->component;

			delete q_iFront;
			q_iFront = NULL;
			q_iRear = NULL;
		}
		else
		{
			NodeType<T>* tempPtr;
			tempPtr = q_iFront->link;

			//데이터 줌
			item = q_iFront->component;

			//첫번째 노드 삭제
			delete q_iFront;

			//두번째 노드를 첫번째 노드로 저장
			q_iFront = tempPtr;
		}
		Length--;
	}
}

// operator[]
template  <typename T>
T& LinkedQueueType<T>::operator[](int index)
{
	NodeType<T>* tempPtr;

	tempPtr = q_iFront;

	for (int i = 0; i < index; i++)
	{
		tempPtr = tempPtr->link;
	}

	return tempPtr->component;
}

// delete data of list by index.
template  <typename T>
int LinkedQueueType<T>::DeleteByIndex(int index)
{
	//만약 길이보다 인덱스가 낮으면
	if (index < Length)
	{
		//임시변수
		NodeType<T>* tempPtr;

		tempPtr = q_iFront;

		//인덱스 진입
		for (int i = 0; i < index; i++)
			tempPtr = tempPtr->link;

		//첫노드라면
		if (index == 0)
		{
			q_iFront = tempPtr->link;
		}
		//마지막 노드라면
		else if (index == (Length - 1))
		{
			NodeType<T>* prePtr = q_iFront;
			//마지막 전 노드 진입
			for (int i = 0; i < index - 1; i++)
				prePtr = prePtr->link;

			prePtr->link = nullptr;
			q_iRear = prePtr;
		}
		//중간노드라면
		else
		{
			NodeType<T>* prePtr = q_iFront;
			//마지막 전 노드 진입
			for (int i = 0; i < index - 1; i++)
				prePtr = prePtr->link;

			prePtr->link = tempPtr->link;
		}
		//노드 삭제
		delete tempPtr;
		Length--;

		return 1;
	}
	else
		return -1;
}