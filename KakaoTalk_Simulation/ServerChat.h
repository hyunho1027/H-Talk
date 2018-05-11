#pragma once

#include <map>
#include "DoublyLinkedList.h"
#include "MsgQueue.h"
using namespace std;



/**
*	Server Chat.
*/
class ServerChat
{
public:
	/**
	*	default constructor.
	*/
	ServerChat()
	{
		sc_Chatcode = 0;
		sc_Chatname = "";
		sc_Memnum = 0;
	}

	/**
	*	destructor.
	*/
	~ServerChat() {}

	/**
	*	@brief	Get chat num.
	*	@pre	chat is set.
	*	@post	none.
	*	@return	chat num.
	*/
	int GetChatcode()
	{
		return sc_Chatcode;
	}

	/**
	*	@brief	Get chat name.
	*	@pre	chat is set.
	*	@post	none.
	*	@return	chat name.
	*/
	string GetChatname()
	{
		return sc_Chatname;
	}

	/**
	*	@brief	Get MQList.
	*	@pre	chat is set.
	*	@post	none.
	*	@return	MQ List.
	*/
	DoublyLinkedList<MsgQueue>& GetMsgQueueList()
	{
		return sc_MQList;
	}

	/**
	*	@brief	Get Members id.
	*	@pre	Members id is set.
	*	@post	none.
	*	@return	recieve members id.
	*/
	map<string, string> GetMem()
	{
		return sc_Members;
	}

	/**
	*	@brief	Get number of members.
	*	@pre	none.
	*	@post	none.
	*	@return	number of members.
	*/
	int GetMemnum()
	{
		return sc_Memnum;
	}


	/**
	*	@brief	Set Chatname.
	*	@pre	none.
	*	@post	Chatname is set.
	*	@param	inChatname	Chatname.
	*/
	void SetChatcode(int inChatcode)
	{
		sc_Chatcode = inChatcode;
	}

	/**
	*	@brief	Set Chatname.
	*	@pre	none.
	*	@post	Chatname is set.
	*	@param	inChatname	Chatname.
	*/
	void SetChatname(string inChatname)
	{
		sc_Chatname = inChatname;
	}

	/**
	*	@brief	Recieve new msgs from client.
	*	@pre	none.
	*	@post	add new msg at MqList.
	*/
	void AddNewMsg(Msg msg)
	{
		for (int i = 0; i < sc_Memnum; i++)
			sc_MQList[i].SaveMsg(msg);
	}

	/**
	*	@brief	Set Members Id.
	*	@pre	none.
	*	@post	member Id is set.
	*	@param	inId	member invited Id.
	*/
	int AddMembers(string inid, string inname)
	{
		sc_Members[inid] = inname;
		sc_Memnum++;

		MsgQueue MsgQ;
		MsgQ.SetId(inid);

		AddNewMsgQueue(MsgQ);
		return 1;
	}

	/**
	*	@brief	Add new msgs.
	*	@pre	none.
	*	@post	none.
	*/
	void AddNewMsgQueue(MsgQueue msgq)
	{

		sc_MQList.Add(msgq);

	}


	/**
	*	@brief	Set num of mem.
	*	@pre	none.
	*	@post	none.
	*/
	void SetMemnum()
	{
		sc_Memnum = int(sc_Members.size());
	}


	/**
	*	@brief	Reset Chat record.
	*	@pre	Chat should be set.
	*	@post	user record is reset.
	*/
	void ResetRecord()
	{
		sc_MQList.MakeEmpty();
		sc_Members.clear();
		SetMemnum();
	}

	/**
	*	@brief	Set user pw from keyboard.
	*	@pre	none.
	*	@post	user pw is set.
	*/
	void SetChatnameFromKB();

	/**
	*	@brief	Chek mem in this chat.
	*	@pre	none.
	*	@post	none.
	*	@return	if mem is in the chat return 1, otherwise 0.
	*/
	int Checkmem(string Id);

	/**
	*	@brief	Delete mem in this chat.
	*	@pre	none.
	*	@post	none.
	*	@return	if delete mem in the chat return 1, otherwise 0.
	*/
	int Deletemem(string Id);


	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	user record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int sc_ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new user record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int sc_WriteDataToFile(ofstream& fout);

	/**
	*	Compare two Infotypes.
	*	@brief	Compare two Info types by Info id.
	*	@pre	two Info types should be initialized.
	*	@post	the target file is included the new Info record.
	*	@param	data	target Info for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByBase(const ServerChat &data);

	/**
	*	@brief	operator < with two ServerChats.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator<(const ServerChat& data);

	/**
	*	@brief	operator > with two ServerChats.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator>(const ServerChat& data);

	/**
	*	@brief	operator == with two ServerChats.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator==(const ServerChat& data);


protected:
	int sc_Chatcode;				///<  own number;
	string sc_Chatname;			///< chat name
	map<string, string> sc_Members;	///<  list of joinning members.
	int sc_Memnum;				///<  number of members.
	DoublyLinkedList<MsgQueue> sc_MQList;///< list of Msgs.
};

