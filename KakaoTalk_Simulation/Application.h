#pragma once

#include "Server.h"
#include <windows.h>

/**
*	application class for Info management simply.
*/
class Application
{
	friend class Server;
public:
	/**
	*	default constructor.
	*/
	Application()
	{
		system("mode con cols=55");	// UI 고려 핸드폰 모양
		u_Command = 0;				//작동 번호
		Client = new InfoType;		//클라이언트
		Client_Chat = nullptr;		//클라이언트가 접속중인 대화창
		status = SERVER;			//상태 변수
		CODE = 0;					//서버에 보낼 코드번호
	}

	/**
	*	destructor.
	*/
	~Application() {}

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run_SERVER();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run_LOGIN();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run_FRIENDMANAGE();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run_CHATMANAGE();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run_PROFILEMANAGE();


	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run_CHAT();


	/**
	*	@brief	Display command on screen and get a input from keyboard when SERVER.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	char GetCommand_SERVER();

	/**
	*	@brief	Display command on screen and get a input from keyboard when LOGIN.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	char GetCommand_LOGIN();

	/**
	*	@brief	Display command on screen and get a input from keyboard when Friendmanage.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	char GetCommand_FRIENDMANAGE();

	/**
	*	@brief	Display command on screen and get a input from keyboard when Chatmanage.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	char GetCommand_CHATMANAGE();

	/**
	*	@brief	Display command on screen and get a input from keyboard when Profilemanage.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	char GetCommand_PROFILEMANAGE();

	/**
	*	@brief	Display command on screen and get a input from keyboard when CHAT.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	char GetCommand_CHAT();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char *fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char *fileName);

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int U_ReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int U_WriteDataToFile();


private:
	ifstream u_InFile;		///< input file descriptor.
	ofstream u_OutFile;		///< output file descriptor.
	StatusType status;		///< current status.
	char u_Command;			///< current command number.
	InfoType* Client;		///< current client
	Chat* Client_Chat;		///< current client chat
	Server server;			///< Server
	string alarm;			///< alarm
	string temptext;		///< temporarily text
	DisPlayType display;	///< display
	int CODE;				///<function code
};