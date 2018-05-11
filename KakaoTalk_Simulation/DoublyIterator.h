#pragma once
#pragma once

#include "DoublyLinkedList.h"
#include "DoublyNodeType.h"


/**
*	template 참조 에러 방지
*/
template <typename T>
class DoublyLinkedList;

/**
*	Iterator class for DoublyLinkedList.  (not using header and trailer nodes).
*	제시된 ADT에 대한 견해
*	- 객체 return하는 메서드에서 결과가 null인 경우 return이 없는 문제 발생
*	- 객체 보다는 포인터가 (nullptr의 존재) 더 안정적인 분기문 형성이 되지 않을 까 예상.
*/
template <typename T>
class DoublyIterator
{
	friend class DoublyLinkedList<T>;

public:
	/**
	*	Initialize List and CurPointer. (constructor overloading)
	*/
	DoublyIterator(const DoublyLinkedList<T>& list) : List(list), CurPointer(list.Head) {}

	/**
	*	@brief	현재 노드를 가리키는 포인터가 null인지 아닌지 판단하는 메서드.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool NotNull();

	/**
	*	@brief	현재 노드 포인터의 다음 노드가 null인지 아닌지 판단하는 메서드.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool NextNotNull();

	/**
	*	@brief	Get first data of the list.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the first node.
	*	@return	Return first data of the list.
	*/
	T First();

	/**
	*	@brief	Get next data of the current pointer.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the next node.
	*	@return	Return next data of the list.
	*/
	T Next();

	/**
	*	@brief	Get current data of the list and go to the next node. 현재 노드. 객체반환은 return by value
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to next node.
	*	@return	Return current data of the list.
	*/
	DoublyNodeType<T> GetCurrentNode();

private:
	const DoublyLinkedList<T>& List;	///< 사용할 리스트의 참조 변수
	DoublyNodeType<T>* CurPointer;	///< Node pointer for pointing current node to use iteration.
};


// 현재 원소가 null인지 검사
template <typename T>
bool DoublyIterator<T>::NotNull() {
	if (CurPointer == nullptr)
		return false;

	else return true;
}

// 다음 원소가 null인지 검사
template <typename T>
bool DoublyIterator<T>::NextNotNull()
{
	if (CurPointer->next == nullptr)
		return false;

	else return true;
}

// 첫 번째 node
template <typename T>
T DoublyIterator<T>::First()
{
	if (List.IsEmpty())
	{
		CurPointer = List.Head;
		return CurPointer->component;
	}
}

// 다음 node로 이동 후 item을 return.
template <typename T>
T DoublyIterator<T>::Next()
{
	T output = CurPointer->component;
	if (NotNull())
		CurPointer = CurPointer->next;
	return output;
}

// 현재 node를 return
template <typename T>
DoublyNodeType<T> DoublyIterator<T>::GetCurrentNode()
{
	return *CurPointer;
}