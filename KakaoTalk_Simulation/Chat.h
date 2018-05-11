#pragma once

#include <map>
#include <algorithm>
#include "Msg.h"
#include "DoublyLinkedList.h"
#include <windows.h>

using namespace std;



/**
*	array based simple vector.
*/
class Chat
{
public:
	/**
	*	default constructor.i
	*/
	Chat()
	{
		c_Chatname = "";
		c_Chatcode = -1;
		c_Memnum = 0;
		c_Msgnum = 0;
		c_Lastdate = GetCurrentTime();
		c_Newmsg = 0;
	}

	/**
	*	destructor.
	*/
	~Chat() {}

	/**
	*	@brief	Get chat name.
	*	@pre	chat is set.
	*	@post	none.
	*	@return	chat name.
	*/
	string GetChatname()
	{
		return c_Chatname;
	}

	/**
	*	@brief	Get Members id.
	*	@pre	Members id is set.
	*	@post	none.
	*	@return	recieve members id.
	*/
	map<string, string> GetMem()
	{
		return c_Members;
	}

	/**
	*	@brief	Get MsgList.
	*	@pre	non.
	*	@post	none.
	*	@return	MsgList.
	*/
	DoublyLinkedList<Msg> GetMsgList()
	{
		return c_MsgList;
	}

	/**
	*	@brief	Get number of members.
	*	@pre	none.
	*	@post	none.
	*	@return	number of members.
	*/
	int GetMemnum()
	{
		return c_Memnum;
	}

	/**
	*	@brief	Get number of msgs.
	*	@pre	none.
	*	@post	none.
	*	@return	number of msgs.
	*/
	int GetMsgnum()
	{
		return c_Msgnum;
	}

	/**
	*	@brief	Get number of new msgs.
	*	@pre	none.
	*	@post	none.
	*	@return	number of new msgs.
	*/
	int GetNewmsg()
	{
		return c_Newmsg;
	}

	/**
	*	@brief	Get number of Chatbers.
	*	@pre	none.
	*	@post	none.
	*	@return	number of Chatbers.
	*/
	int GetChatcode()
	{
		return c_Chatcode;
	}

	/**
	*	@brief	Get last chat day.
	*	@pre	none.
	*	@post	none.
	*	@return	last chat day.
	*/
	string GetLastdate()
	{
		return c_Lastdate;
	}


	/**
	*	@brief	Set Chatname.
	*	@pre	none.
	*	@post	Chatname is set.
	*	@param	inChatname	Chatname.
	*/
	void SetChatname(string inChatname)
	{
		c_Chatname = inChatname;
	}

	/**
	* @brief	Set Chatcode.
	*	@pre	none.
	*	@post	Chatcode is set.
	*	@param	inChatcode	Chatcode.
	*/
	void SetChatcode(int inChatcode)
	{
		c_Chatcode = inChatcode;
	}

	/**
	* @brief	Set Chatcode.
	*	@pre	none.
	*	@post	Chatcode is set.
	*	@param	inChatcode	Chatcode.
	*/
	void SetMem(map<string, string> inmem)
	{
		c_Members = inmem;
	}


	/**
	*	@brief	Set Members Id.
	*	@pre	none.
	*	@post	member Id is set.
	*	@param	inId	member invited Id.
	*/
	int AddMembers(string inid, string inname)
	{
		c_Members[inid] = inname;
		SetMemnum();
		DisplayMembersOnScreen();
		DisplayMemnumOnScreen();
		return 1;
	}

	/**
	*	@brief	Add new msgs.
	*	@pre	none.
	*	@post	none.
	*/
	void AddNewMsg(Msg data)
	{
		c_MsgList.Add(data);
		SetMsgnum();
		SetLastday();
	}

	/**
	*	@brief	Set num of mem.
	*	@pre	none.
	*	@post	none.
	*/
	void SetMemnum()
	{
		c_Memnum = int(c_Members.size());
	}

	/**
	*	@brief	Set num of msg.
	*	@pre	none.
	*	@post	none.
	*/
	void SetMsgnum()
	{
		c_Msgnum = int(c_MsgList.GetLength());
	}

	/**
	*	@brief	Reset num of msg.
	*	@pre	none.
	*	@post	none.
	*/
	void ResetMsgnum()
	{
		c_Msgnum = 0;
	}

	/**
	*	@brief	Set num of new msg.
	*	@pre	none.
	*	@post	Set new msg.
	*/
	void SetNewmsg(int innew)
	{
		c_Newmsg += innew;
	}

	/**
	*	@brief	Set last date of msg.
	*	@pre	none.
	*	@post	Update Lastdate.
	*/
	void SetLastday()
	{
		//만약 메시지가 존재하면
		if (c_Msgnum)
			c_Lastdate = c_MsgList[c_Msgnum - 1].GetDate();
		//존재하지 않으면
		else
			c_Lastdate = GetCurrentTime();
	}


	/**
	*	@brief	Reset num of new msg.
	*	@pre	none.
	*	@post	Newmsg is 0.
	*/
	void ResetNewmsg()
	{
		c_Newmsg = 0;
	}

	/**
	*	@brief	Reset Chat record.
	*	@pre	Chat should be set.
	*	@post	user record is reset.
	*/
	void ResetRecord()
	{
		SetChatname("");
		c_MsgList.MakeEmpty();
		c_Members.clear();
		SetMemnum();
		SetMsgnum();
		ResetNewmsg();
		SetChatcode(-1);
	}

	/**
	*	@brief	Display chatname on screen.
	*	@pre	chatname is set.
	*	@post	chatname is on screen.
	*/
	void DisplayChatnameOnScreen()
	{
		cout << "\tChatname   : " << c_Chatname << endl;
	}

	/**
	*	@brief	Display Members on screen.
	*	@pre	Members are set.
	*	@post	 on screen.
	*/
	void DisplayMembersOnScreen()
	{
		cout << "\tMember: ";
		map<string, string>::iterator it = c_Members.begin();
		while (it != c_Members.end())
		{
			cout << (*it).second << "/ ";
			it++;
		}
	}

	/**
	*	@brief	Display text on screen.
	*	@pre	text is set.
	*	@post	text is on screen.
	*/
	void DisplayMemnumOnScreen()
	{
		cout << "(" << c_Memnum << ")" << endl;
	}

	/**
	*	@brief	Display last msg on screen.
	*	@pre	last msg is set.
	*	@post	last msg is on screen.
	*/
	void DisplayLastMsgOnScreen()
	{
		if (c_MsgList.GetLength())
		{
			cout << "\t" << c_Members[c_MsgList[c_Msgnum - 1].GetSendId()];
			c_MsgList[c_Msgnum - 1].DisplayMsgOnScreen();
		}
	}

	/**
	*	@brief	Display new msg on screen.
	*	@pre	none.
	*	@post	new msg is on screen.
	*/
	void DisplayNewmsgOnScreen()
	{
		//알림이 있다면
		if (c_Newmsg)
			cout << "\tNew: " << c_Newmsg << endl;
	}

	/**
	*	@brief	Display Chat on screen.
	*	@pre	Chat is set.
	*	@post	Chat is on screen.
	*/
	void DisplayChatOnScreen()
	{
		DisplayChatnameOnScreen();
		DisplayMembersOnScreen();
		DisplayMemnumOnScreen();
		DisplayNewmsgOnScreen();
		DisplayLastMsgOnScreen();
		cout << "\t-----------------------------------" << endl;
	}

	/**
	*	@brief	Display Msg in this chat on screen.
	*	@pre	Chat is set.
	*	@post	Chat is on screen.
	*/
	void DisplayallMsgOnScreen(string Id);

	/**
	*	@brief	Display Msg we are looking for in this chat on screen.
	*	@pre	Chat is set.
	*	@post	Chat is on screen.
	*/
	void SearchMsg(string Id, string text);

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
	*	@brief	Delete msg in this chat.
	*	@pre	none.
	*	@post	msg is deleted.
	*	@param	fin	file descriptor.
	*	@return	if delete mem in the chat return 1, otherwise 0.
	*/
	int Deletemsg(int index);


	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	user record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int c_ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new user record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int c_WriteDataToFile(ofstream& fout);

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
	RelationType CompareByBase(const Chat &data);

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
	RelationType CompareByChatcode(const Chat &data);

	/**
	*	@brief	operator < with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator<(const Chat& data);

	/**
	*	@brief	operator > with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator>(const Chat& data);

	/**
	*	@brief	operator == with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator==(const Chat& data);

	/**
	*	@brief Get current time
	*	@return buff current time with string
	*/
	string GetCurrentTime()
	{
		time_t timer;
		struct tm t;
		char buff[80];

		// 현재 시스템의 시간정보를 얻어온다.
		timer = time(NULL);
		localtime_s(&t, &timer);

		// 시간정보로 (년월일시간) 문자열을 만들어 반환.
		strftime(buff, sizeof(buff), "%Y-%m-%d/%H:%M:%S", &t);

		return buff;
	}

protected:
	int c_Chatcode;				///< num of Chat frome server
	string c_Chatname;			///<  name of Chat.
	map<string, string> c_Members;	///<  list of joinning members.
	int c_Memnum;				///<  number of members.
	DoublyLinkedList<Msg> c_MsgList;		///< list of Msgs.
	int c_Msgnum;				///< number of msgs.
	string c_Lastdate;			///< chat's last date.
	int c_Newmsg;				///< number of new msgs
};

