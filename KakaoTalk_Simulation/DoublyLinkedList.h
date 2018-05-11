#pragma once


#include "DoublyIterator.h"
#include "DoublyNodeType.h"

/**
*	Soreted Doubly linked list.
*/
template  <typename T>
class DoublyLinkedList
{
	friend class DoublyIterator<T>;
public:
	/**
	*	default constructor.
	*/
	DoublyLinkedList()
	{
		Length = 0;
		Head = nullptr;
		Tail = nullptr;
	}

	/**
	*	destructor.
	*/
	~DoublyLinkedList() {}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Check whether it is empty or not.
	*	@pre	none.
	*	@post	none.
	*	@return	return 1 if it is empty otherwise return 0.
	*/
	bool IsEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	int Add(T data);

	/**
	*	@brief	delete a data of list.
	*	@pre	list should be non-empty.
	*	@post	If Id which you want to delete exists in list then delete it.
	*	@param	data	data of data you want to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Delete(T data);

	/**
	*	@brief	delete a data of list by Index.
	*	@pre	list should be non-empty.
	*	@post	If Id which you want to delete exists in list then delete it.
	*	@param	index	the index you want to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteByIndex(int index);

	/**
	*	@brief	Search Info with same Id.
	*	@pre	list should be non-empty.
	*	@post	If there is same Id which you enter in list then return its index.
	*	@param	data	data of data you want to search.
	*	@return	return its index if this function works well, otherwise -1.
	*/
	int Search(T data);

	/**
	*	@brief	(주소) Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item, int index);


	/**
	*	@brief	user's data .
	*	@pre	user's data is set.
	*	@param	index wanna get index
	*	@post	get user's data .
	*	@return	return data by index.
	*/
	T& operator[](int index);

private:
	DoublyNodeType<T>* Head;		///< Pointer for pointing a first node.
	DoublyNodeType<T>* Tail;
	int Length;					///< Number of node in the list.
};

// Make list empty.
template  <typename T>
void DoublyLinkedList<T>::MakeEmpty()
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	DoublyNodeType<T>* tempPtr;
	DoublyIterator<T> iter(*this);

	while (iter.NotNull())
	{
		tempPtr = iter.CurPointer;
		iter.Next();
		delete tempPtr;
	}
	Head = nullptr;
	Tail = nullptr;
	Length = 0;
}

// check whether it is empty or not.
template  <typename T>
bool DoublyLinkedList<T>::IsEmpty()
{
	if (Head == nullptr)
		return true;

	else return false;
}

// Get a number of records in current list.
template  <typename T>
int DoublyLinkedList<T>::GetLength()
{
	return Length;
}

// add a new data into list.
template  <typename T>
int DoublyLinkedList<T>::Add(T inData)
{
	//추가할 변수 받을 임시자료형
	DoublyNodeType<T>* node = new DoublyNodeType<T>;
	DoublyNodeType<T>* tmpPtr;

	node->component = inData;
	node->pre = nullptr;
	node->next = nullptr;


	// 비어있는 경우
	if (IsEmpty())
	{
		Head = node;
		Tail = Head;
	}
	// 1개 이상
	else {
		//MsgList를 고려해 뒤에서부터 삽입
		tmpPtr = Tail;
		while (tmpPtr != nullptr)
		{
			if (!(node->component < tmpPtr->component))
			{ // 넣으려고 하는게 더 크거나 같으면
				node->pre = tmpPtr;
				if (tmpPtr == Tail)
				{	// 맨 뒤
					node->pre = Tail;
					Tail->next = node;
					Tail = node;
				}
				else
				{	// 중간
					node->pre = tmpPtr;
					node->next = tmpPtr->next;
					tmpPtr->next->pre = node;
				}
				tmpPtr->next = node;
				break;
			}
			else
				tmpPtr = tmpPtr->pre;
		}
		if (tmpPtr == nullptr)
		{	// 맨 앞

			node->next = Head;
			Head->pre = node;
			Head = node;
		}
	}
	Length++;
	return 1;
}

// delete data of list.
template  <typename T>
int DoublyLinkedList<T>::Delete(T data)
{
	//삭제될 노드를 가리킬 노드
	DoublyNodeType<T>* pNode = Head;
	//리스트 안에 존재하는지 확인
	int positionIndex = Search(data);
	if (positionIndex != -1)
	{
		for (int i = 0; i < positionIndex; i++)
			pNode = pNode->next;
		if (pNode->next != nullptr)// 끝이 아니면
			pNode->next->pre = pNode->pre;
		else
			Tail = pNode->pre;
		if (pNode->pre != nullptr)// 처음이 아니면
			pNode->pre->next = pNode->next;
		else
			Head = pNode->next;
		delete pNode;
		Length--;
		return 1;
	}
	else
		return 0;
}


// delete data of list by index.
template  <typename T>
int DoublyLinkedList<T>::DeleteByIndex(int index)
{
	//만약 길이보다 인덱스가 낮으면
	if (index < Length)
	{
		//임시변수
		DoublyNodeType<T>* tempPtr;

		tempPtr = Head;

		//인덱스 진입
		for (int i = 0; i < index; i++)
			tempPtr = tempPtr->next;

		//만약 첫 노드 라면
		if (index == 0)
		{
			tempPtr->next->pre = nullptr;
			Head = tempPtr->next;
		}
		//마지막 노드라면
		else if (index == (Length - 1))
		{
			tempPtr->pre->next = nullptr;
			Tail = tempPtr->pre;
		}
		//중간 노드라면
		else
		{
			tempPtr->pre->next = tempPtr->next;
			tempPtr->next->pre = tempPtr->pre;
		}
		//노드 삭제
		delete tempPtr;
		Length--;

		return 1;
	}
	else
		return -1;
}

// Search Info
template  <typename T>
int DoublyLinkedList<T>::Search(T data)
{
	//길이가 0이면
	if (!Length)
		return -1;

	//찾는 노드를 가리키는 포인터
	DoublyNodeType<T>* tempPtr;
	tempPtr = Head;
	int index = 0;

	while (tempPtr != nullptr)
	{
		//노드가 찾는 노드라면
		if (tempPtr->component == data)
			return index;
		else
		{
			tempPtr = tempPtr->next;
			index++;
		}
	}
	return -1;
}

// Get info by index
template <typename T>
int DoublyLinkedList<T>::Get(T&item, int index)
{
	//리스트 안에 존재하면
	if (index >= 0)
	{
		item = (*this)[index];
		return 1;
	}
	else
		return 0;
}


// operator[]
template  <typename T>
T& DoublyLinkedList<T>::operator[](int index)
{
	DoublyNodeType<T>* tempPtr;

	tempPtr = Head;
	//인덱스 접근
	for (int i = 0; i < index; i++)
		tempPtr = tempPtr->next;

	return tempPtr->component;
}

