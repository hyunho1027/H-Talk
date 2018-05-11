#include "Server.h"


void Server::Run(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext, int func_code)
{
	switch (func_code)
	{
	case 10010001:
		AddInfo(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10010002:
		MemberLogin(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10010003:
		DisplayAllInfo(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10010004:
		RetrieveById(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020001:
		GoFriendmanage(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020002:
		GoChatmanage(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020003:
		GoProfilemanage(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020004:
		MemberLogout(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030001:
		Addnewfriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030002:
		Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030003:
		Birthfriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030004:
		Recfriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030005:
		Searchfriends(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030006:
		Deletefriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10040001:
		AddChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10040002:
		Openchat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10040003:
		Displayallchats(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050001:
		EditPic(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050002:
		EditBackpic(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050003:
		EditBacktext(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050004:
		EditRecord(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050005:
		EditPw(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050006:
		Memleave(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060001:
		Sendmsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060002:
		Displayallmsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060003:
		LeaveChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060004:
		EditChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060005:
		AddMem(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060006:
		Deletemsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060007:
		ExitChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060008:
		SendEmotion(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060009:
		Searchmsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060010:
		Copymsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060011:
		Pastemsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060012:
		Delivermsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10090001:
		GoBack(Client, Client_Chat, status, alarm, display, temptext);
		break;
	default:
		break;
	}


	if (status != SERVER)
		//유저 접속정보 초기화
		u_List[u_List.Search(*Client)].SetLastDate();


}


//-------------------------SERVER-------------------------------


// Add new record into list. CDOE = 10010001
int Server::AddInfo(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	InfoType Info;
	Info.SetIdFromKB();

	//만약 아이디가 /0이면 되돌리기.
	if (Info.GetId() == "/0")
		return 0;

	//아이디 중복 검사
	if (u_List.Search(Info) == -1)
	{
		//나머지 정보 저장
		Info.SetPwFromKB();
		Info.SetNameFromKB();
		Info.SetPhonenumFromKB();
		Info.SetBirthFromKB();
		Info.SetGenderFromKB();

		//유저리스트에 추가.
		u_List.Add(Info);
		alarm = "Add Succesively.";

		//유저전용 DB 생성
		string Id = Info.GetId();
		Id.append("_db.txt");
		int leng = int(Id.length());

		//char* 형태로 파일이름 생성
		char* filename;
		filename = new char[leng];
		for (int i = 0; i <= leng; i++)
		{
			filename[i] = Id[i];
		}

		//DB 생성
		std::ofstream outfile(filename);

		return 1;
	}
	else
	{
		//아이디 중복시
		alarm = "This Id Exists already.";
		return -1;
	}

}

// Login. CODE = 10010002
int Server::MemberLogin(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	InfoType user;
	user.SetIdFromKB();
	//유저아이디 찾기
	int curIndex = u_List.Search(user);
	//유저아이디가 있을 경우
	if (curIndex != -1)
	{
		InfoType comp; //비교형 임시변수
		u_List.Get(comp, curIndex);
		user.SetPwFromKB();
		//Pw 확인
		if (user.CompareByPw(comp) == EQUAL)
		{
			// 인사말
			alarm = "Hello ";
			alarm.append(comp.GetName());
			alarm.append(" !\n");

			//최근접속정보 출력
			if (comp.GetLastdate().compare("none"))
			{
				alarm.append("\tLast date user on. : ");
				alarm.append(comp.GetLastdate());
			}

			//상태 LOGIN으로 변경
			status = LOGIN;

			//Client 현재 유저로 복사
			Client->SetRecord(comp.GetId(), comp.GetPw(), comp.GetName(), comp.GetPhonenum(), comp.GetBirth(), comp.GetGender());
			Client->SetPic(comp.GetPic());
			Client->SetBackpic(comp.GetBackpic());
			Client->SetBacktext(comp.GetBacktext());
			for (int i = 0; i < comp.GetFriendnum(); i++)
			{
				//친구 복사
				Client->AddFriend(comp.GetFriends()[i]);
			}
			//채팅갯수 복사
			Client->SetChatnum(comp.GetChatnum());


			return 1;
		}
		//Pw가 다를 경우
		else
		{
			alarm = "Check the Password again.";
			return 0;
		}
	}
	//유저아이디가 없을 경우
	else
	{
		alarm = "Check the ID again.";
		return 0;
	}
}

// Display all records in the list on screen. CODE = 10010003
void Server::DisplayAllInfo(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//유저가 없는경우
	if (u_List.GetLength() == 0)
	{

		cout << "\n\t Empty List." << endl;
	}
	//유저가 있으면
	else
	{

		cout << "\n\tCurrent list" << endl << endl;

		// list의 모든 데이터를 화면에 출력
		DoublyIterator<InfoType> iter(u_List);

		while (iter.NotNull())
			iter.Next().DisplayRecordOnScreen();
	}
}

// Display the record in the list on screen. CODE = 10010004
void Server::RetrieveById(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//유저가 없는경우
	if (u_List.GetLength() == 0)
	{
		cout << "\n\t Empty List." << endl;
	}
	//유저가 있으면
	else
	{
		//찾을 아이디의 임시변수
		string Id;
		cout << "\n\t Enter the ID you want to find. : ";
		cin >> Id;

		//되돌리기
		if (Id == "/0")
			return;

		//소문자로 변환
		transform(Id.begin(), Id.end(), Id.begin(), ::tolower);

		InfoType data;
		data.SetId(Id);
		//임시변수 있으면
		if (u_List.Search(data) != -1)
		{
			int curIndex = u_List.Search(data);
			InfoType data;
			u_List.Get(data, curIndex);
			data.DisplayRecordOnScreen();
		}

		//임시변수 없으면
		else
		{
			cout << "\n\t Can not find" << endl;
		}
	}
}

//-------------------------LOGIN-------------------------------

// move to friendmanage CODE = 10020001
void Server::GoFriendmanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = FRIENDMANAGE;
}

// move to chatmanage CODE = 10020002
void Server::GoChatmanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = CHATMANAGE;
	display = DISPLAYALLCHATS;
}

// move to profilemanage CODE = 10020003
void Server::GoProfilemanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = PROFILEMANAGE;
}

// Logout. CODE = 10020004
int Server::MemberLogout(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//유저 의사 확인
	cout << "\n\t Wanna Logout seriously? (Y/N): ";
	string ans;
	cin >> ans;

	//유저가 동의 하면
	if (ans == "Y" || ans == "y")
	{
		alarm = "Logouted Successively.";

		//마지막 이용시간 저장
		Client->SetLastDate();

		//상태 변경
		status = SERVER;
		Client->ResetRecord();
		return 1;
	}
	else
	{
		alarm = "Not Logouted.";
		return 0;
	}
}


//-------------------------FRIENDMANAGE-------------------------------

// Add new friend into u_friend list CODE = 10030001
int Server::Addnewfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	DisplayAllInfo(Client, Client_Chat, status, alarm, display, temptext);
	cout << "\n\t Who do you want." << endl;

	// 아이디 입력
	InfoType data;
	data.SetIdFromKB();

	//되돌리기
	if (data.GetId() == "/0")
		return 0;

	// 아이디가 리스트에 있으면
	if (!(u_List.Search(data) < 0))
	{
		// 아이디가 자기 자신이면
		if (data.GetId() == Client->GetId())
		{
			alarm = "Can not Add myself.";
			return -1;
		}

		// 아이디가 이미 친구이면
		else if (Client->Searchfriend(data.GetId()) != -1)
		{
			alarm = "Friend already.";
			return -1;
		}

		// 둘다 아니면
		else
		{
			//서버 유저 목록에 친구 추가
			u_List[u_List.Search(*Client)].AddFriend(data.GetId());
			//현재 로그인된 유저에도 친구추가.
			Client->AddFriend(data.GetId());
			alarm = "Add successively.";
			return 1;
		}
	}
	return -1;
}

// Display all friends On Screen CODE = 10030002
void Server::Displayallfriends(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	// 친구가 없다면
	if (Client->GetFriendnum() == 0)
	{
		cout << "\n\t No friends." << endl;
	}
	//친구가 있으면
	else
	{
		cout << "\n\t -----------Friends List-------------" << endl;

		// 출력용임시 벡터 변수
		std::vector<string> frd;
		// it 변수
		std::vector<string>::iterator it;
		// 친구Id 받을  두개의 임시 변수
		InfoType info, iinfo;
		// int형 임시 변수
		int index = 0;
		//현재 유저의 친구들을 이름순으로 새로 받음
		for (int i = 0; i < Client->GetFriendnum(); i++)
		{
			//처음에는 바로 저장
			if (i == 0)
				frd.push_back(Client->GetFriends()[i]);
			else
			{
				//iterator 초기화
				it = frd.begin();

				//frd에 들어갈 친구
				info.SetId(Client->GetFriends()[i]);
				while (1)
				{
					//frd에 있는 친구
					iinfo.SetId(*it);
					//들어올 친구가 현재 친구보다 이름이 작으면
					if (u_List[u_List.Search(info)].GetName() < iinfo.GetName())
					{
						frd.insert(it, Client->GetFriends()[i]);
						break;
					}
					//만약 frd의 마지막이면 마지막에 저장
					else if ((*it) == frd[i - 1])
					{
						frd.push_back(Client->GetFriends()[i]);
						break;
					}
					//아니면
					else
						it++;
				}
			}
		}
		for (int i = 0; i < Client->GetFriendnum(); i++)
		{
			//info 재활용
			info.SetId(frd[i]);
			u_List[u_List.Search(info)].DisplayRecordOnScreen();
			cout << endl;
		}

	}
}

// Display Birthday friends On Screen CODE = 10030003
void Server::Birthfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//친구 수 받기
	int frdnum = Client->GetFriendnum();
	if (frdnum > 0)
	{
		//생일인 친구 임시변수
		InfoType info;
		bool check = false;
		cout << "\n\t ----------Birth day friends-------------" << endl << endl;

		for (int i = 0; i < frdnum; i++)
		{
			// 친구리스트에서 아이디 받아오기
			info.SetId(Client->GetFriends()[i]);
			// 친구유저생일 한명씩 현재날짜랑 같은지 확인
			if (u_List[u_List.Search(info)].GetBirth() % 10000 == std::stoi(GetCurrentDate()))
			{
				u_List[u_List.Search(info)].DisplayRecordOnScreen();
				check = true;
			}
		}
		// 만약 생일인 친구가 없다면
		if (!check)
			cout << "\n\t Nobody birthday." << endl;
	}
	// 만약 친구가 없다면
	else
		cout << "\n\t Do not have friends." << endl;
}

// Display Recommend friend CODE = 10030004
void Server::Recfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	InfoType info;
	int leng = u_List.GetLength();
	bool check = false;

	cout << "\n\t ----------Recommend friends-------------" << endl << endl;

	for (int i = 0; i < leng; i++)
	{
		// i번째 유저가 Client가 아니고 Client의 친구가 아닐때
		if ((u_List[i].GetId() != Client->GetId()) && Client->Searchfriend(u_List[i].GetId()) == -1)
		{
			// i번째 유저의 친구리스트에 Client가 있을때
			if (u_List[i].Searchfriend(Client->GetId()) != -1)
			{
				u_List[i].DisplayRecordOnScreen();
				check = true;
			}
		}
	}
	// 만약 추천친구가 없으면
	if (!check)
		cout << "\n\t Nobody recommend" << endl;
}

// Display all friends On Screen CODE = 10030005
void Server::Searchfriends(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	// 친구가 없다면
	if (Client->GetFriendnum() == 0)
	{
		cout << "\n\t No friends." << endl;
	}
	//친구가 있으면
	else
	{
		//찾을 이름 임시변수
		string name;
		//유저 이름 받을 임시 변수
		InfoType tmpinfo;
		//bool형 임시 변수
		bool check = false;
		cout << "\n\t Enter the name you want to look for. : ";
		cin >> name;

		//되돌리기
		if (name == "/0")
			return;

		cout << "\n\t -----------Friends List-------------" << endl;

		// 클라이언트의 모든 친구 확인
		for (int i = 0; i < Client->GetFriendnum(); i++)
		{
			//임시변수에 아이디 set
			tmpinfo.SetId(Client->GetFriends()[i]);
			//원하는 단어가 이름에 포함되면
			if (0<u_List[u_List.Search(tmpinfo)].GetName().find(name) && u_List[u_List.Search(tmpinfo)].GetName().find(name)<u_List[u_List.Search(tmpinfo)].GetName().length())
			{
				//출력
				u_List[u_List.Search(tmpinfo)].DisplayRecordOnScreen();
				check = true;
			}
		}

		if (!check)
			cout << "\n\t No friends." << endl;
	}
}

// Delete friend into u_friend list CODE = 10030006
int Server::Deletefriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);
	cout << "\n\t Who do you want to delete. :";

	// 아이디 입력
	string data;
	cin >> data;

	//되돌리기
	if (data == "/0")
		return 0;

	if (Client->Searchfriend(data) != -1)
	{
		u_List[u_List.Search(*Client)].Deletefriend(data);
		Client->Deletefriend(data);
		alarm = "Delete successively.";
		return 1;
	}
	else
		return 0;
}

//-------------------------CHATMANAGE-------------------------------

// Add new record into list. CODE = 10040001 
int Server::AddChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{

	//대화할 수 있는 친구 출력
	Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);
	cout << "\n\t Who you want to talk." << endl;

	//UI 고려
	display = DISPLAYALLCHATS;

	// 대화상대 임시변수
	InfoType info;
	info.SetIdFromKB();

	//만약 아이디가 /0이면 되돌리기.
	if (info.GetId() == "/0")
		return 0;

	u_List.Get(info, u_List.Search(info));


	// 원하는 대화상대가 친구가 아니라면
	if (Client->Searchfriend(info.GetId())<0)
	{
		//UI 고려
		display = DISPLAYALLCHATS;

		alarm = "Dose not exists.";
		return -1;
	}
	else
	{
		//서버에 저장할 서버챗 임시변수
		ServerChat schat;
		schat.AddMembers(Client->GetId(), Client->GetName());
		schat.AddMembers(info.GetId(), info.GetName());
		schat.SetChatnameFromKB();
		schat.SetChatcode(c_List.GetLength());

		//리스트에 저장
		c_List.Add(schat);


		//현재 유저에 저장할 채팅 임시변수
		Chat chat;
		chat.SetChatcode(schat.GetChatcode());
		chat.SetChatname(schat.GetChatname());
		chat.SetMem(schat.GetMem());
		chat.SetMemnum();
		//현재 클라이언트에 저장
		Client->AddChat(chat);
		//유저리스트 목록의 현재 유저의 채팅수 증가
		u_List[u_List.Search(*Client)].SetChatnum(Client->GetChatnum());

		//현재 서버챗,챗 포인터 변환
		Curr_Schat = &c_List[c_List.GetLength() - 1];

		//Chat 은 마지막 날짜가 제일 큰게 맨 앞으로 오는 것을 고려
		Client_Chat = &Client->GetChats()[0];
		status = CHAT;

		//채팅방 만들어짐 공지
		Msg newmsg;
		newmsg.SetSendId("/SERVER");
		newmsg.SetText("Chat Open!");
		newmsg.SetDate();
		Curr_Schat->AddNewMsg(newmsg);

		//새로운 날짜를 알리는 공지를 함
		Msg alarmdate;
		alarmdate.SetSendId("/SERVER");
		alarmdate.SetDate();
		alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
		Curr_Schat->AddNewMsg(alarmdate);

		//UI고려
		display = DISPLAYALLMSG;
		return 1;
	}
	return -1;
}

// Open chat CODE = 10040002
int Server::Openchat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//만약 유저의 채팅이 있다면
	if (Client->GetChatnum())
	{

		cout << "\t Choose the Chat number--> ";
		//채팅방 번호 선택
		int getcommend;
		cin >> getcommend;

		int num = Client->GetChatnum();

		if (0 < getcommend&&getcommend <= num)
		{
			//현재 유저 채팅포인터 변환
			Client_Chat = &Client->GetChats()[getcommend - 1];

			//채팅방넘버 임시변수
			int Chatcode;

			//선택된 번호의 채팅방의 채팅방넘버 받기
			Chatcode = Client_Chat->GetChatcode();

			//현재 접속된 채팅방으로 접속
			Curr_Schat = &c_List[Chatcode];

			status = CHAT;
			display = DISPLAYALLMSG;
			return 1;
		}
		else
		{
			//UI 고려
			display = DISPLAYALLCHATS;
			alarm = "Check the number again.";
			return -1;
		}
	}
	else
	{
		alarm = "Does not Exist.";
		return-1;
	}
}

// Display all chats On Screen CODE = 10040003
void Server::Displayallchats(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//유저의 채팅 수가 0이라면
	if (!Client->GetChatnum())
		alarm = "Empty List.";
	else
	{
		cout << "\t -----------Chats List-------------" << endl;
		//채팅 수
		int num = Client->GetChatnum();

		for (int i = 0; i < num; i++)
		{
			cout << "\t" << i + 1 << ". " << endl;
			Client->GetChats()[i].DisplayChatOnScreen();
		}
	}
}


//-------------------------PROFILEMANAGE-------------------------------

// Edit users pic CODE = 10050001
void Server::EditPic(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	u_List[u_List.Search(*Client)].SetPicFromKB();
	Client->SetPic(u_List[u_List.Search(*Client)].GetPic());
	alarm = "Changed Successively.";

}

// Edit users pic  CODE = 10050002
void Server::EditBackpic(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	u_List[u_List.Search(*Client)].SetBackpicFromKB();
	Client->SetBackpic(u_List[u_List.Search(*Client)].GetBackpic());
	alarm = "Changed Successively.";

}

// Edit users pic CODE = 10050003
void Server::EditBacktext(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	u_List[u_List.Search(*Client)].SetBacktextFromKB();
	Client->SetBacktext(u_List[u_List.Search(*Client)].GetBacktext());
	alarm = "Changed Successively.";

}

// Edit users record CODE = 10050004
void Server::EditRecord(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//이름 변경
	u_List[u_List.Search(*Client)].SetNameFromKB();
	Client->SetName(u_List[u_List.Search(*Client)].GetName());
	//핸드폰 번호 변경
	u_List[u_List.Search(*Client)].SetPhonenumFromKB();
	Client->SetPhonenum(u_List[u_List.Search(*Client)].GetPhonenum());
	//생일 변경
	u_List[u_List.Search(*Client)].SetBirthFromKB();
	Client->SetBirth(u_List[u_List.Search(*Client)].GetBirth());
	//성별 변경
	u_List[u_List.Search(*Client)].SetGenderFromKB();
	Client->SetGender(u_List[u_List.Search(*Client)].GetGender());

	alarm = "Changed Successively.";
}

// Edit users password CODE = 10050005
void Server::EditPw(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//비밀번호 비교형 임시변수
	InfoType info;
	cout << "\n\t Enter the Password." << endl;
	info.SetPwFromKB();

	//비밀번호가 맞을 시
	if (Client->CompareByPw(info) == EQUAL)
	{
		cout << "\n\t Enter the New Password." << endl;
		//비밀번호 변경
		u_List[u_List.Search(*Client)].SetPwFromKB();
		Client->SetPw(u_List[u_List.Search(*Client)].GetPw());
		alarm = "Changed Successively.";
	}
	//비밀번호가 다를 시
	else
		alarm = "Check Password again.";
}

// Mem Leave by Client CODE = 10050006
void Server::Memleave(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//의사 확인
	cout << "\n\t Wanna delete seriously? (Y/N): ";

	//char형 임시변수
	char ans;
	cin >> ans;
	//동의하면
	if (ans == 'Y' || ans == 'y')
	{
		//c_List 전부
		for (int i = 0; i < c_List.GetLength(); i++)
		{
			//만약 서버챗 목록에 현재 유저가 있으면 (굳이 체크하는 이유는 만약 유저가 없는 채팅방의 멤버수가 많으면 그만큼 낭비.)
			if (c_List[i].Checkmem(Client->GetId()))
				//삭제
				c_List[i].Deletemem(Client->GetId());
		}

		//u_List전부
		for (int i = 0; i < u_List.GetLength(); i++)
		{
			//i번째 유저가 자기자신이면 넘어간다.
			if (u_List[i].GetId() == Client->GetId())
				continue;
			else
				//만약 현재 유저가 i번째 유저의 친구라면
				if (u_List[i].Searchfriend(Client->GetId()) != -1)
					//삭제
					u_List[i].Deletefriend(Client->GetId());
		}
		//유저 삭제
		u_List.Delete(*Client);
		//현재 유저포인터 변환
		Client->ResetRecord();
		//현재상태 변환
		status = SERVER;

		alarm = "Delete Successively.";
	}
	//거절하면
	else
	{
		alarm = "Not deleted.";
	}


}


//-------------------------CHAT-------------------------------

// Send msg in Client_Chat CODE = 10060001
void Server::Sendmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	Msg newmsg;
	newmsg.SetSendId(Client->GetId());
	newmsg.SetTextFromKB();
	newmsg.SetDate();
	//만약 채팅방 년 월 일이 달라졌으면
	if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
	{
		//새로운 날짜를 알리는 공지를 함
		Msg alarmdate;
		alarmdate.SetSendId("/SERVER");
		alarmdate.SetDate();
		alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
		Curr_Schat->AddNewMsg(alarmdate);

		//기존 메시지를 날짜알림 문자 뒤로 보내기
		newmsg.SetDate();
	}
	Curr_Schat->AddNewMsg(newmsg);
	display = DISPLAYALLMSG;
}

// Printallmsg CODE = 10060002
void Server::Displayallmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	Client_Chat->DisplayallMsgOnScreen(Client->GetId());
}

// Chat Leave by phonenum&name CODE = 10060003
void Server::LeaveChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//사람 나감 공지
	Msg newmsg;
	newmsg.SetSendId("/SERVER");
	newmsg.SetText("Good Bye " + Client->GetName() + " ~");
	newmsg.SetDate();
	Curr_Schat->AddNewMsg(newmsg);

	//현재 클라이언트에 채팅방 삭제
	Client->GetChats().Delete(*Client_Chat);
	//현재 유저리스트 채팅방 수 줄임
	u_List[u_List.Search(*Client)].SetChatnum(Client->GetChatnum());

	Client->SetChatnum();
	Curr_Schat->Deletemem(Client->GetId());

	status = CHATMANAGE;
	//배경 색 변환
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	//UI고려
	display = DISPLAYALLCHATS;
	Client_Chat = nullptr;
	Curr_Schat = nullptr;
}

// Edit chat info CODE = 10060004
void Server::EditChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI고려
	display = DISPLAYALLMSG;

	Curr_Schat->SetChatnameFromKB();
}

// Add new mem at chat CODE = 10060005
int Server::AddMem(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI고려
	display = DISPLAYALLMSG;

	Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);

	cout << "\n\t Who you want to talk." << endl;
	InfoType info;
	info.SetIdFromKB();

	//만약 원하는 대화상대가 유저의 친구라면
	if (Client->Searchfriend(info.GetId()) == -1)
	{
		alarm = "Dose not exists.";
		return -1;
	}
	//아니라면
	else
	{
		//유저 친구의 정보 받아오기
		u_List.Get(info, u_List.Search(info));

		//만약 이미 채팅방에 있는 친구라면
		if (Curr_Schat->Checkmem(info.GetId()) == 1)
		{
			alarm = "Exist already.";
			return -1;
		}
		//채팅방에 없다면
		else
		{
			Curr_Schat->AddMembers(info.GetId(), info.GetName());

			//새로운 사람 초대됨 공지
			Msg newmsg;
			newmsg.SetSendId("/SERVER");
			newmsg.SetText("Wellcome " + info.GetName() + " !");
			newmsg.SetDate();
			Curr_Schat->AddNewMsg(newmsg);

			return 1;
		}
	}
}

// Delete msg (if opponent does not check it then delete.) CODE = 10060006
int Server::Deletemsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI고려
	display = DISPLAYALLMSG;

	//밑에서부터 몇번째 메시지 인지 확인
	cout << "\t Enter the number from the bottom. : ";

	int index;
	cin >> index;

	//Msg 임시변수
	Msg msg;
	//삭제하려는 메시지 임시저장
	//위에서부터 몇번째인지로 바꿔서 대입
	Client_Chat->GetMsgList().Get(msg, Client_Chat->GetMsgnum() - index);

	//인덱스 유효한지 확인
	if (0 < index&&index <= Client_Chat->GetMsgnum())
	{
		// 서버 공지 메시지가 아니라면
		if (msg.GetSendId() != "/SERVER")
		{
			//현재 채팅방에서 삭제
			if (Client_Chat->Deletemsg(Client_Chat->GetMsgnum() - index) == 1)//성공하면
			{
				//상대방이 읽지 않은 메시지라면 서버에 저장되어있는 메시지 큐에서도 삭제
				for (int i = 0; i < Curr_Schat->GetMemnum(); i++)
				{
					//메시지큐안의 메시지 갯수만큼 확인
					for (int j = 0; j < Curr_Schat->GetMsgQueueList()[i].GetMsgnum(); j++)
					{
						//i번째 메시지큐의 j번째 메시지
						if (msg.GetSendId() == Curr_Schat->GetMsgQueueList()[i].GetMsgList()[j].GetSendId())//메시지와 송신자 이름이같고
							if (msg.GetText() == Curr_Schat->GetMsgQueueList()[i].GetMsgList()[j].GetText())//메시지와 텍스트 내용이 같고
								if (msg.GetDate() == Curr_Schat->GetMsgQueueList()[i].GetMsgList()[j].GetDate())//메시지와 보낸 시간이 같으면
								{
									//i번째 메시지 큐의 j번째 메시지 삭제
									Curr_Schat->GetMsgQueueList()[i].Deletemsg(j);
									break;
								}
					}
				}
				return 1;
			}
			else
				return -1;
		}
		// 서버 메시지 라면
		else
		{
			alarm = "Cannot delete Sever Msg.";
			return -1;
		}
	}
	//유효하지 않다면
	else
		return -1;
}

// Exit the chat. CODE = 10060007
void Server::ExitChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = CHATMANAGE;
	//배경 색 변환
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//UI고려
	display = DISPLAYALLCHATS;
	Client_Chat = nullptr;
	Curr_Schat = nullptr;
}

// Send msg in Client_Chat CODE = 10060008
void Server::SendEmotion(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//임시 감정 변수
	string emotion;
	string emotions[5] = { "(^ _ ^)","(♡_♡)","(ㅜ_ㅜ)","(- _ -)","(O _ O)" };

	for (int i = 0; i < 5; i++)
		cout << '\t' << i + 1 << ". " << emotions[i] << endl;

	//이모티콘 선택 변수
	int num;

	cout << "\n\t What do you want. : ";
	cin >> num;

	//인덱스로 변환
	num = num - 1;

	if (0 <= num && num < 5)
		emotion = emotions[num];
	else
	{
		alarm = "Wrong control.";
		return;
	}

	//임시 메시지 변수
	Msg newmsg;
	newmsg.SetSendId(Client->GetId());
	newmsg.SetText(emotion);
	newmsg.SetDate();
	//만약 채팅방 년 월 일이 달라졌으면
	if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
	{
		//새로운 날짜를 알리는 공지를 함
		Msg alarmdate;
		alarmdate.SetSendId("/SERVER");
		alarmdate.SetDate();
		alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
		Curr_Schat->AddNewMsg(alarmdate);

		//기존 메시지를 날짜알림 문자 뒤로 보내기
		newmsg.SetDate();
	}
	Curr_Schat->AddNewMsg(newmsg);
	display = DISPLAYALLMSG;
}

// Printallmsg CODE = 10060009
void Server::Searchmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI고려
	Displayallmsg(Client, Client_Chat, status, alarm, display, temptext);

	//찾고자 하는 텍스트
	string text;

	cout << "\n\t Enter the word wanna look for. :";
	cin.get();
	getline(cin, text);

	//UI고려
	system("cls");

	//메시지 찾기
	Client_Chat->SearchMsg(Client->GetId(), text);
}

// Copy msg CODE = 10060010
int Server::Copymsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI고려
	display = DISPLAYALLMSG;

	//밑에서부터 몇번째 메시지 인지 확인
	cout << "\t Enter the number from the bottom. : ";

	//임시 인덱스
	int index;
	cin >> index;

	//Msg 임시변수
	Msg msg;

	//인덱스 유효한지 확인
	if (0 < index&&index <= Client_Chat->GetMsgnum())
	{
		//위에서부터 몇번째인지로 바꿔서 대입
		Client_Chat->GetMsgList().Get(msg, Client_Chat->GetMsgnum() - index);

		//메시지 복사
		temptext = msg.GetText();
		return 1;
	}
	else
		return 0;
}

// Paste msg in Client_Chat CODE = 10060011
int Server::Pastemsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//만약 붙여넣기 할 것이 없다면
	if (temptext.empty())
	{
		alarm = "Nothing to Paste.";

		//UI고려
		display = DISPLAYALLMSG;
		return 0;
	}
	else
	{
		Msg newmsg;
		newmsg.SetSendId(Client->GetId());
		newmsg.SetText(temptext);
		newmsg.SetDate();
		//만약 채팅방 년 월 일이 달라졌으면
		if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
		{
			//새로운 날짜를 알리는 공지를 함
			Msg alarmdate;
			alarmdate.SetSendId("/SERVER");
			alarmdate.SetDate();
			alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
			Curr_Schat->AddNewMsg(alarmdate);

			//기존 메시지를 날짜알림 문자 뒤로 보내기
			newmsg.SetDate();
		}
		Curr_Schat->AddNewMsg(newmsg);
		display = DISPLAYALLMSG;
		return 1;
	}
}

// Delive msg CODE = 10060012
int Server::Delivermsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{

	//밑에서부터 몇번째 메시지 인지 확인
	cout << "\t Enter the number from the bottom. : ";

	//임시 인덱스
	int index;
	cin >> index;

	//Msg 임시변수
	Msg msg;

	//인덱스 유효한지 확인
	if (0 < index&&index <= Client_Chat->GetMsgnum())
	{
		//위에서부터 몇번째인지로 바꿔서 대입
		Client_Chat->GetMsgList().Get(msg, Client_Chat->GetMsgnum() - index);

		Msg newmsg;
		newmsg.SetSendId(Client->GetId());
		newmsg.SetText(msg.GetText());
		newmsg.SetDate();

		//전달할 채팅방 고름
		Displayallchats(Client, Client_Chat, status, alarm, display, temptext);

		cout << "\t Choose the Chat number to deliver--> ";
		//채팅방 번호 선택
		int getcommend;
		cin >> getcommend;

		int num = Client->GetChatnum();

		if (0 < getcommend&&getcommend <= num)
		{
			//현재 유저 채팅포인터 변환
			Client_Chat = &Client->GetChats()[getcommend - 1];

			//채팅방넘버 임시변수
			int Chatcode;

			//선택된 번호의 채팅방의 채팅방넘버 받기
			Chatcode = Client_Chat->GetChatcode();

			//현재 접속된 채팅방으로 접속
			Curr_Schat = &c_List[Chatcode];


			//만약 채팅방 년 월 일이 달라졌으면
			if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
			{
				//새로운 날짜를 알리는 공지를 함
				Msg alarmdate;
				alarmdate.SetSendId("/SERVER");
				alarmdate.SetDate();
				alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
				Curr_Schat->AddNewMsg(alarmdate);

				//기존 메시지를 날짜알림 문자 뒤로 보내기
				newmsg.SetDate();
			}
			//메시지 보내기
			Curr_Schat->AddNewMsg(newmsg);
			display = DISPLAYALLMSG;
			return 1;
		}
		else
		{
			alarm = "Check the number again.";
			return -1;
		}
	}
	else
		return 0;

}

//-------------------------SUB-------------------------------

// move to Login CDOE = 10090001
void Server::GoBack(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = LOGIN;
}

// Update Chats from server
void Server::UpdateChats(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//만약 서버에 아무 채팅도 없다면

	if (!c_List.GetLength())
		return;


	//유저의 채팅코드를 받을 변수
	vector<int> code;
	//유저의 채팅방 수
	int num = Client->GetChatnum();

	//chat받을 임시 변수
	Chat* chat;
	//msg받을 임시 변수
	Msg msg;



	//유저채팅의 마지막 코드를 담을 임시변수
	int lastcode;
	//만약 유저 채팅방이 없다면
	if (!num)
		lastcode = 0;
	else
	{
		for (int i = 0; i < num; i++)
		{
			//순차적으로 채팅방 코드를 받아옴
			code.push_back(Client->GetChats()[i].GetChatcode());
			// 코드번호 오름차순으로 소팅
			std::sort(code.begin(), code.end());
		}
		lastcode = code[num - 1] + 1;
	}

	//새로운 대화가 생겼는지 확인
	for (int i = lastcode; i < c_List.GetLength(); i++)//현재 대화창에 있는 맨마지막 코드가 제일 마지막에 생긴 채팅 ->제일마지막 에생긴 코드 다음부터 찾기
	{
		//새로운 대화가 있다면
		if (c_List[i].Checkmem(Client->GetId()) == 1)
		{
			chat = new Chat;
			//chat에 임시저장
			(*chat).SetChatcode(c_List[i].GetChatcode());
			(*chat).SetChatname(c_List[i].GetChatname());
			(*chat).SetMem(c_List[i].GetMem());
			(*chat).SetMemnum();

			//현재 유저에게 채팅 추가
			Client->AddChat((*chat));
			//code배열에 추가해줌
			code.push_back(c_List[i].GetChatcode());
			num++;
		}
	}

	//code vector 다시 초기화
	code.clear();
	//재입력
	for (int i = 0; i < num; i++)
		//순차적으로 채팅방 코드를 받아옴
		code.push_back(Client->GetChats()[i].GetChatcode());


	for (int i = 0; i < num; i++)
	{
		//채팅방이름 다운로드
		Client->GetChats()[i].SetChatname(c_List[code[i]].GetChatname());

		//채팅방유저 다운로드
		Client->GetChats()[i].SetMem(c_List[code[i]].GetMem());
		Client->GetChats()[i].SetMemnum();

		//메시지 리스트를 받아옴
		for (int j = 0; j < c_List[code[i]].GetMemnum(); j++)
		{
			// 현재 code를 가지고 있는 채팅방의 MQ리스트가 현재 유저의 것이면
			if (c_List[code[i]].GetMsgQueueList()[j].GetId() == Client->GetId())
			{
				//MsgQ에 쌓여있던 메시지 만큼 새로운 알림으로 변환
				Client->GetChats()[i].SetNewmsg(c_List[code[i]].GetMsgQueueList()[j].GetMsgnum());

				//메시지 큐가 empty가 될때 까지
				while (!c_List[code[i]].GetMsgQueueList()[j].GetMsgList().IsEmpty())
				{
					// Msg를 하나씩 꺼내서 옮긴다.
					c_List[code[i]].GetMsgQueueList()[j].GetMsgList().DeQueue(msg);
					Client->GetChats()[i].AddNewMsg(msg);
				}
				c_List[code[i]].GetMsgQueueList()[j].ResetMsgnum();
				break;
			}
		}
	}
}

// Open a file by file descriptor as an input file.
int Server::OpenInFile(char *fileName)
{
	u_InFile.open(fileName);	// file open for reading.

								// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!u_InFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Server::OpenOutFile(char *fileName)
{
	u_OutFile.open(fileName);	// file open for writing.

								// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!u_OutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Server::ReadDataFromFile()
{
	int index = 0;
	InfoType* data;	// 읽기용 임시 변수

	char filename_user[FILENAMESIZE];
	for (int i = 0; i <= NAMESIZE_USER; i++)
		filename_user[i] = FILENAME_USER[i];

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename_user))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!u_InFile.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data = new InfoType;
		(*data).ReadDataFromFile(u_InFile);
		if (!u_InFile.eof())
			u_List.Add(*data);
		else
			delete data;
	}

	u_InFile.close();	// file close

	ServerChat* schat;	// 읽기용 임시 변수
	MsgQueue* msgq;      // 읽기용 임시 변수
	char filename_chat[FILENAMESIZE];
	for (int i = 0; i <= NAMESIZE_CHAT; i++)
		filename_chat[i] = FILENAME_CHAT[i];

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename_chat))
		return 0;

	//임시상수
	index = 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!u_InFile.eof())
	{
		schat = new ServerChat;
		// Serverchat 에 읽어오기
		(*schat).sc_ReadDataFromFile(u_InFile);
		if (!u_InFile.eof())
		{
			c_List.Add(*schat);
			for (int i = 0; i < (*schat).GetMemnum(); i++)
			{
				msgq = new MsgQueue;
				(*msgq).mq_ReadDataFromFile(u_InFile);
				c_List[index].AddNewMsgQueue(*msgq);
			}
			index++;
		}
		else
			delete schat;
	}

	u_InFile.close();	// file close

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Server::WriteDataToFile()
{
	InfoType data;	// 쓰기용 임시 변수

	char filename_user[FILENAMESIZE];

	for (int i = 0; i <= NAMESIZE_USER; i++)
	{
		filename_user[i] = FILENAME_USER[i];
	}

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename_user))
		return 0;

	// list의 모든 데이터를 파일에 쓰기
	int length = u_List.GetLength();
	for (int i = 0; i < length; i++)
	{
		u_List[i].WriteDataToFile(u_OutFile);
	}

	u_OutFile.close();	// file close


	char filename_chat[FILENAMESIZE];


	for (int i = 0; i <= NAMESIZE_CHAT; i++)
	{
		filename_chat[i] = FILENAME_CHAT[i];
	}

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename_chat))
		return 0;


	// list의 모든 데이터를 파일에 쓰기
	length = c_List.GetLength();
	for (int i = 0; i < length; i++)
	{
		c_List[i].sc_WriteDataToFile(u_OutFile);
		for (int j = 0; j < c_List[i].GetMemnum(); j++)
		{
			c_List[i].GetMsgQueueList()[j].mq_WriteDataToFile(u_OutFile);
		}
	}

	u_OutFile.close();	// file close

	return 1;
}