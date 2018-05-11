#include "Application.h"

// Program driver.
void Application::Run()
{
	while (status != OFF)
	{
		//SERVER 실행
		//코드가 있다면 서버에게 원하는 함수코드를 전달함
		if (CODE)
			server.Run(Client, Client_Chat, status, alarm, display, temptext, CODE);

		server.WriteDataToFile();

		system("cls");

		if (status != SERVER)
		{
			//만약 직전 함수코드가 100010002, 즉 로그인 성공했다면
			if (CODE == 10010002)
				// Client 의 DB에서 정보 가져오기
				U_ReadDataFromFile();

			server.UpdateChats(Client, Client_Chat, status, alarm, display, temptext);
			Client->SetLastDate();
			U_WriteDataToFile();
			//소팅
			if (status == CHATMANAGE)
			{
				Client->GetChats().MakeEmpty();
				U_ReadDataFromFile();
			}
		}

		//CODE 초기화
		CODE = 0;

		if (status == CHAT)
			//알림 0으로 변환
			Client_Chat->ResetNewmsg();

		if (!alarm.empty())
		{
			cout << "\n\t " << alarm << endl;
			alarm.clear();
		}

		switch (display)
		{
		case NONE:
			break;
		case DISPLAYALLINFO:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10010003);
			display = NONE;
			break;
		case RETRIEVEBYID:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10010004);
			display = NONE;
			break;
		case DISPLAYALLFRIENDS:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10030002);
			display = NONE;
			break;
		case SEARCHFRIENDS:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10030005);
			display = NONE;
			break;
		case DISPLAYRECOMMENDFRIENDS:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10030004);
			display = NONE;
			break;
		case DISPLAYBIRTHFRIENDS:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10030003);
			display = NONE;
			break;
		case DISPLAYALLCHATS:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10040003);
			display = NONE;
			break;
		case DISPLAYMYINFO:
			cout << "\n\t ----------My info-------------" << endl << endl;
			Client->DisplayRecordOnScreen();
			display = NONE;
			break;
		case DISPLAYALLMSG:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10060002);
			display = NONE;
			break;
		case SEARCHMSG:
			server.Run(Client, Client_Chat, status, alarm, display, temptext, 10060009);
			display = NONE;
			break;
		default:
			break;
		}

		switch (status)
		{
		case SERVER:
			Run_SERVER();
			break;
		case LOGIN:
			Run_LOGIN();
			break;
		case FRIENDMANAGE:
			Run_FRIENDMANAGE();
			break;
		case CHATMANAGE:
			Run_CHATMANAGE();
			break;
		case PROFILEMANAGE:
			Run_PROFILEMANAGE();
			break;
		case CHAT:
			Run_CHAT();
			break;
		default:
			break;
		}

	}
}
// Program driver. CODE = 1001****
void Application::Run_SERVER()
{
	u_Command = GetCommand_SERVER();

	switch (u_Command)
	{
	case '1':		// read a record and add to list.
		CODE = 10010001;
		break;
	case '2':		// Login.
		CODE = 10010002;
		break;
	case '3':		// Ldisplay all the records in list on screen.
		display = DISPLAYALLINFO;
		break;
	case '4':		// // display the record in list on screen.
		display = RETRIEVEBYID;
		break;
	case '0':		//Quit the Kakaotalk
		status = OFF;
		return;
		break;
	default:
		alarm = "Illegal selection...";
		break;
	}
}
// Program driver. CODE = 1002****
void Application::Run_LOGIN()
{
	u_Command = GetCommand_LOGIN();

	switch (u_Command)
	{
	case '1':		// move to friendmanage
		CODE = 10020001;
		break;
	case '2':		// move to chatmanage
		CODE = 10020002;
		break;
	case '3':		// move to profilemanage
		CODE = 10020003;
		break;
	case '0':		// logout.
		CODE = 10020004;
		break;
	default:
		alarm = "Illegal selection...";
		break;
	}
}
// Program driver. CODE = 1003****
void Application::Run_FRIENDMANAGE()
{
	u_Command = GetCommand_FRIENDMANAGE();

	switch (u_Command)
	{
	case '1':		// add new friend.
		CODE = 10030001;
		break;
	case '2':		// display all friends.
		display = DISPLAYALLFRIENDS;
		break;
	case '3':		// display recommend friends.
		display = DISPLAYRECOMMENDFRIENDS;
		break;
	case '4':		// display birth friends.
		display = DISPLAYBIRTHFRIENDS;
		break;
	case '5':		// search friends.
		display = SEARCHFRIENDS;
		break;
	case '6':		// delete friend.
		CODE = 10030006;
		break;
	case '0':		// logout.
		CODE = 10090001;
		break;
	default:
		alarm = "Illegal selection...";
		break;
	}
}
// Program driver. CODE = 1004****
void Application::Run_CHATMANAGE()
{

	u_Command = GetCommand_CHATMANAGE();

	switch (u_Command)
	{
	case '1':		// add Chat to list.
		CODE = 10040001;
		break;
	case '2':		// open the chat.
		CODE = 10040002;
		break;
	case '3':		// display user's all chat.
		display = DISPLAYALLCHATS;
		break;
	case '0':		// logout.
		CODE = 10090001;
		break;
	default:
		alarm = "Illegal selection...";
		break;
	}
}
// Program driver. CODE = 1005****
void Application::Run_PROFILEMANAGE()
{
	u_Command = GetCommand_PROFILEMANAGE();

	switch (u_Command)
	{
	case '1':		// edit picture.
		display = DISPLAYMYINFO;
		break;
	case '2':		// edit picture.
		CODE = 10050001;
		break;
	case '3':		// edit backpicture.
		CODE = 10050002;
		break;
	case '4':		// edit backtext.
		CODE = 10050003;
		break;
	case '5':		// edit record.
		CODE = 10050004;
		break;
	case '6':		// edit password.
		CODE = 10050005;
		break;
	case '7':		// leave the member.
		CODE = 10050006;
		break;
	case '0':		// logout.
		CODE = 10090001;
		break;
	default:
		alarm = "Illegal selection...";
		break;
	}
}
// Program driver. CODE = 1006****
void Application::Run_CHAT()
{

	u_Command = GetCommand_CHAT();

	switch (u_Command)
	{
	case '1':		// send msg.
		CODE = 10060001;
		break;
	case '2':		// send emotion.
		CODE = 10060008;
		break;
	case '3':		// display the record in list on screen.
		display = DISPLAYALLMSG;
		break;
	case '4':		//Leave the chat.
		CODE = 10060003;
		break;
	case '5':		// edit chat name.
		CODE = 10060004;
		break;
	case '6':		// invite new mem.
		CODE = 10060005;
		break;
	case '7':		// delete msg.
		CODE = 10060006;
		break;
	case '8':		// display the record in list on screen.
		display = SEARCHMSG;
		break;
	case '9':		// copy msg.
		CODE = 10060010;
		break;
	case 'A':		// paste msg.
		CODE = 10060011;
		break;
	case 'B':		// paste msg.
		CODE = 10060012;
		break;
	case '0':		// Exit
		CODE = 10060007;
		break;
	default:
		alarm = "Illegal selection...";
		break;
	}
}



// Display command on screen and get a input from keyboard when SERVER.
char Application::GetCommand_SERVER()
{
	char command;
	cout << endl << endl;
	cout << "\t---#--- Command ----- " << endl;
	cout << "\t   1 : Add New Info" << endl;
	cout << "\t   2 : Login" << endl;
	cout << "\t   3 : Print all on screen" << endl;
	cout << "\t   4 : Print someone's Info" << endl;
	cout << "\t   0 : Quit" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;
}

// Display command on screen and get a input from keyboard when LOGIN.
char Application::GetCommand_LOGIN()
{
	char command;
	cout << endl << endl;
	cout << "\t user: " << Client->GetName() << endl;
	cout << "\t---#--- Command ----- " << endl;
	cout << "\t   1 : Move to FriendManager" << endl;
	cout << "\t   2 : Move to ChatManager" << endl;
	cout << "\t   3 : Move to ProfileManager" << endl;
	cout << "\t   0 : Logout" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;

}

// Display command on screen and get a input from keyboard when FRIENDMANAGE.
char Application::GetCommand_FRIENDMANAGE()
{
	char command;
	cout << endl << endl;
	cout << "\t user: " << Client->GetName() << " - FriendManger" << endl;
	cout << "\t---#--- Command ----- " << endl;
	cout << "\t   1 : Add new friend" << endl;
	cout << "\t   2 : Print all friends" << endl;
	cout << "\t   3 : Print recommend friends" << endl;
	cout << "\t   4 : Print birth friends" << endl;
	cout << "\t   5 : Search friend" << endl;
	cout << "\t   6 : Delete friend" << endl;
	cout << "\t   0 : Go back" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;

}

// Display command on screen and get a input from keyboard when CHATMANAGE.
char Application::GetCommand_CHATMANAGE()
{
	char command;
	cout << endl << endl;
	cout << "\t user: " << Client->GetName() << " - ChatManager" << endl;
	cout << "\t---#--- Command ----- " << endl;
	cout << "\t   1 : Add new chat" << endl;
	cout << "\t   2 : Open chat" << endl;
	cout << "\t   3 : Print all chats" << endl;
	cout << "\t   0 : Go back" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;

}

// Display command on screen and get a input from keyboard when PROFILEMANAGE.
char Application::GetCommand_PROFILEMANAGE()
{
	char command;
	cout << endl << endl;
	cout << "\t user: " << Client->GetName() << " - ProfileManager" << endl;
	cout << "\t---#--- Command ----- " << endl;
	cout << "\t   1 : Display my Info" << endl;
	cout << "\t   2 : Edit picture" << endl;
	cout << "\t   3 : Edit backpicture" << endl;
	cout << "\t   4 : Edit backtext" << endl;
	cout << "\t   5 : Edit record" << endl;
	cout << "\t   6 : Edit password" << endl;
	cout << "\t   7 : Leave Mem" << endl;
	cout << "\t   0 : Go back" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;

}

// Display command on screen and get a input from keyboard when CHAT.
char Application::GetCommand_CHAT()
{
	char command;
	cout << endl << endl;
	cout << "\t user: " << Client->GetName() << endl << endl;
	cout << "\t---#--- Command ----- " << endl;
	cout << "\t   1 : Send Message" << endl;
	cout << "\t   2 : Send Emotion" << endl;
	cout << "\t   3 : Display Messages" << endl;
	cout << "\t   4 : Leave this Chat" << endl;
	cout << "\t   5 : Edit chatname" << endl;
	cout << "\t   6 : Add Member" << endl;
	cout << "\t   7 : Delete Msg" << endl;
	cout << "\t   8 : Search Msg" << endl;
	cout << "\t   9 : Copy Msg" << endl;
	cout << "\t   A : Paste Msg" << endl;
	cout << "\t   B : Deliver Msg" << endl;
	cout << "\t   0 : Exit" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;
}


// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	u_InFile.open(fileName);	// file open for reading.

								// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!u_InFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	u_OutFile.open(fileName);	// file open for writing.

								// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!u_OutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::U_ReadDataFromFile()
{
	//유저전용 DB 이름변수 생성
	string filename_user = Client->GetId();
	filename_user.append("_db.txt");
	int leng = int(filename_user.length());

	//char* 형태로 파일이름 생성
	char* filename;
	filename = new char[leng];
	for (int i = 0; i <= leng; i++)
	{
		filename[i] = filename_user[i];
	}

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
		return 0;

	Chat* chat;	// 읽기용 임시 변수


				// 파일의 모든 내용을 읽어 list에 추가
	while (!u_InFile.eof())
	{
		chat = new Chat;
		// array에 학생들의 정보가 들어있는 structure 저장
		(*chat).c_ReadDataFromFile(u_InFile);
		if ((*chat).GetChatname() != "")
		{
			//만약 유저 채팅리스트에 없다면
			if (Client->SearchChatcode((*chat).GetChatcode()) == -1)
				Client->AddChat(*chat);
		}
		else
			delete chat;
	}

	u_InFile.close();	// file close

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::U_WriteDataToFile()
{
	//유저전용 DB 이름변수 생성
	string filename_user = Client->GetId();
	filename_user.append("_db.txt");
	int leng = int(filename_user.length());

	//char* 형태로 파일이름 생성
	char* filename;
	filename = new char[leng];
	for (int i = 0; i <= leng; i++)
	{
		filename[i] = filename_user[i];
	}

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return 0;

	DoublyLinkedList<Chat> chats;// 출력용 임시변수
	int chatsnum; // 출력할 채팅방 갯수

	chats = Client->GetChats();
	chatsnum = Client->GetChatnum();
	// list의 모든 데이터를 파일에 쓰기
	for (int i = 0; i < chatsnum; i++)
	{
		chats[i].c_WriteDataToFile(u_OutFile);
	}
	u_OutFile.close();	// file close

	return 1;
}
