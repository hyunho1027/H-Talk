#pragma once
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "RelationType.h"
using namespace std;



/**
*	Info information class.
*/
class Msg
{
public:
	/**
	*	default constructor.
	*/
	Msg()
	{
		m_SendId = "";
		m_Text = "";
		m_Date = "";
	}

	/**
	*	destructor.
	*/
	~Msg() {}

	/**
	*	@brief	Get send user id.
	*	@pre	send user id is set.
	*	@post	none.
	*	@return	send user id.
	*/
	string GetSendId()
	{
		return m_SendId;
	}

	/**
	*	@brief	Get text date.
	*	@pre	non.
	*	@post	none.
	*	@return	text date.
	*/
	string GetDate()
	{
		return m_Date;
	}

	/**
	*	@brief	Get text.
	*	@pre	non.
	*	@post	none.
	*	@return	text.
	*/
	string GetText()
	{
		return m_Text;
	}

	/**
	*	@brief	Set Send user Id.
	*	@pre	none.
	*	@post	send user Id is set.
	*	@param	inId	Send user Id.
	*/
	void SetSendId(string inId)
	{
		m_SendId = inId;
	}

	/**
	*	@brief	Set text date.
	*	@pre	none.
	*	@post	text date is set.
	*	@param	inDate	textdate.
	*/
	void SetDate()
	{
		m_Date = GetCurrentTime();
	}

	/**
	*	@brief	Set user text.
	*	@pre	none.
	*	@post	user text is set.
	*	@param	inText user text.
	*/
	void SetText(string inText)
	{
		m_Text = inText;
	}

	/**
	*	@brief	Set user name from keyboard.
	*	@pre	none.
	*	@post	user name is set.
	*/
	void SetTextFromKB();

	/**
	*	@brief	Set msg record.
	*	@pre	none.
	*	@post	user record is set.
	*	@param	inSendId	sneduser id.
	*	@param	inRecieveId	recieveuser id.
	*	@param	inText	text.
	*/
	void SetRecord(string inSendId, string inText)
	{
		SetSendId(inSendId);
		SetDate();
		SetText(inText);
	}

	/**
	*	@brief	Display msg on screen.
	*	@pre	msg is set.
	*	@post	msg is on screen.
	*/
	void DisplayMsgOnScreen()
	{
		cout << ": [ " << m_Text << " ] " << m_Date.substr(11, 5) << endl;
	};


	/**
	*	Compare two Msges.
	*	@brief	Compare two Info types by Info id.
	*	@pre	two Msg should be initialized.
	*	@post	the target file is included the new Info record.
	*	@param	data	target Info for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByBase(const Msg &data);

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	user record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int m_ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new user record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int m_WriteDataToFile(ofstream& fout);


	/**
	*	@brief	operator < with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator<(const Msg& data);

	/**
	*	@brief	operator > with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator>(const Msg& data);

	/**
	*	@brief	operator == with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator==(const Msg& data);

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
	string m_SendId;		///<  Id of user sended.
	string m_Text;		///< Text.
	string m_Date;		///< Day at Text.
};

