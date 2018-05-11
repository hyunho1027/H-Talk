#include "Chat.h"


// Set user chatname from keyboard.
void Chat::SetChatnameFromKB()
{
	cout << "\tChatname : ";
	cin >> c_Chatname;
}

// Display all msg
void Chat::DisplayallMsgOnScreen(string Id)
{
	//채팅방 정보 출력
	DisplayChatOnScreen();

	//메시지가 없으면
	if (c_Msgnum == 0)
	{
		cout << "\n\t No Message." << endl;
	}
	else
	{
		for (int i = 0; i < c_Msgnum; i++)
		{
			//서버전용 메시지라면
			if (c_MsgList[i].GetSendId() == "/SERVER")
			{
				//채팅방 중앙에 오도록 실시
				cout << endl;
				cout << setw(25 - c_MsgList[i].GetText().size() / 2) << "[[ " << c_MsgList[i].GetText() << " ]]" << endl << endl;
			}

			//메시지아이디와 Curr Id가 같으면 -> 메시지가 본인 메시지이면
			else if (c_MsgList[i].GetSendId() == Id)
			{

				//이전 메시지와 아이디가 같다면
				if (c_MsgList[i - 1].GetSendId() == Id)
				{
					//마지막 메시지면
					if (i == c_Msgnum - 1)
					{
						//메시지 인터페이스 작업이하 생략
						cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
						//본인 메시지 배경 색 변환
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
						//메시지 출력
						cout << " " << c_MsgList[i].GetText() << " ";
						//원래 색깔로
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << ' ';
						cout << endl;
					}
					// 마지막 메시지가 아니면
					else
					{
						//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i + 1].GetSendId() != Id)
						{
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						else// 다음 메시지와 시간이 같으면
						{
							cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
					}
				}
				//이전 메시지와 아이디가 다르다면
				else
				{
					//마지막 메시지면
					if (i == c_Msgnum - 1)
					{
						cout << setw(50 - c_Members[Id].size());
						cout << c_Members[Id] << endl;
						cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
						//본인 메시지 배경 색 변환
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
						//메시지 출력
						cout << " " << c_MsgList[i].GetText() << " ";
						//원래 색깔로
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << ' ';
						cout << endl;
					}
					// 마지막 메시지가 아니면
					else
					{
						//다음 메시지와 시간이 다르거나 송신자 아이디가 다르면
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						else// 다음 메시지와 시간이 같으면
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
					}
				}
			}

			//상대방 메시지이면
			else
			{
				//이전 메시지와 아이디가 같다면
				if (c_MsgList[i - 1].GetSendId() == c_MsgList[i].GetSendId())
				{
					//마지막 메시지면
					if (i == c_Msgnum - 1)
					{
						cout << "\t ";
						// 상대방 메시지 배경 색 변환
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
						// 메시지 작성
						cout << " " << c_MsgList[i].GetText() << " ";
						//원래 색깔로
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
					}
					// 마지막 메시지가 아니면
					else
					{
						//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
						{
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						else// 다음 메시지와 시간이 같으면
						{
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
					}
				}
				//이전 메시지와 아이디가 다르다면
				else
				{
					//마지막 메시지면
					if (i == c_Msgnum - 1)
					{
						cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
						cout << "\t ";
						// 상대방 메시지 배경 색 변환
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
						// 메시지 작성
						cout << " " << c_MsgList[i].GetText() << " ";
						//원래 색깔로
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
					}
					// 마지막 메시지가 아니면
					else
					{
						//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						else// 다음 메시지와 시간이 같으면
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;

						}
					}
				}

			}
		}
	}
}

// Display all msg look for
void Chat::SearchMsg(string Id, string text)
{
	//채팅방 정보 출력
	DisplayChatOnScreen();

	//메시지가 없으면
	if (c_Msgnum == 0)
	{
		cout << "\n\t No Message." << endl;
	}
	else
	{
		for (int i = 0; i < c_Msgnum; i++)
		{
			//서버전용 메시지라면
			if (c_MsgList[i].GetSendId() == "/SERVER")
			{
				//채팅방 중앙에 오도록 실시
				cout << endl;
				cout << setw(25 - c_MsgList[i].GetText().size() / 2) << "[[ " << c_MsgList[i].GetText() << " ]]" << endl << endl;
			}
			//찾는 문자열이 있을 경우
			else if (c_MsgList[i].GetText().find(text) < c_MsgList[i].GetText().length())
			{
				//메시지아이디와 Curr Id가 같으면 -> 메시지가 본인 메시지이면
				if (c_MsgList[i].GetSendId() == Id)
				{

					//이전 메시지와 아이디가 같다면
					if (c_MsgList[i - 1].GetSendId() == Id)
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							//메시지 인터페이스 작업이하 생략
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i + 1].GetSendId() != Id)
							{
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}
					//이전 메시지와 아이디가 다르다면
					else
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 송신자 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}
				}

				//상대방 메시지이면
				else
				{
					//이전 메시지와 아이디가 같다면
					if (c_MsgList[i - 1].GetSendId() == c_MsgList[i].GetSendId())
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5);
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5);
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}
					//이전 메시지와 아이디가 다르다면
					else
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5);
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5);
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}

				}
				cin.get();
			}
			//찾는 문자열이 없을 경우
			else
			{
				//메시지아이디와 Curr Id가 같으면 -> 메시지가 본인 메시지이면
				if (c_MsgList[i].GetSendId() == Id)
				{

					//이전 메시지와 아이디가 같다면
					if (c_MsgList[i - 1].GetSendId() == Id)
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							//메시지 인터페이스 작업이하 생략
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i + 1].GetSendId() != Id)
							{
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
						}
					}
					//이전 메시지와 아이디가 다르다면
					else
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//본인 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//메시지 출력
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 송신자 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//본인 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//메시지 출력
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
						}
					}
				}

				//상대방 메시지이면
				else
				{
					//이전 메시지와 아이디가 같다면
					if (c_MsgList[i - 1].GetSendId() == c_MsgList[i].GetSendId())
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
						}
					}
					//이전 메시지와 아이디가 다르다면
					else
					{
						//마지막 메시지면
						if (i == c_Msgnum - 1)
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// 상대방 메시지 배경 색 변환
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// 메시지 작성
							cout << " " << c_MsgList[i].GetText() << " ";
							//원래 색깔로
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						// 마지막 메시지가 아니면
						else
						{
							//다음 메시지와 시간이 다르거나 다음메시지와 송신 아이디가 다르면
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
							}
							else// 다음 메시지와 시간이 같으면
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// 상대방 메시지 배경 색 변환
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// 메시지 작성
								cout << " " << c_MsgList[i].GetText() << " ";
								//원래 색깔로
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;

							}
						}
					}

				}
			}
		}
	}
}

// Check member in the chat.
int Chat::Checkmem(string Id)
{
	//멤버가 없다면
	if (c_Members.find(Id) == c_Members.end())
	{
		return -1;
	}
	//멤버가 있다면
	else
	{
		return 1;
	}
}

// Delete member in the chat.
int Chat::Deletemem(string Id)
{
	map<string, string>::iterator it = c_Members.begin();
	// 멤버를 찾기 시작

	while (it != c_Members.end())
	{
		//찾는 멤버가 있다면 삭제
		if (it->first == Id)
		{
			c_Members.erase(it++);
			SetMemnum();
			return 1;
		}
		else
		{
			it++;
		}
	}
	return -1;
}

// Delete msg in the chat
int Chat::Deletemsg(int index)
{
	//msg 지우기 성공하면
	if (c_MsgList.DeleteByIndex(index) == 1)
	{
		c_Msgnum--;
		return 1;
	}
	else
		return -1;
}
// Compare two Infotypes.
RelationType Chat::CompareByBase(const Chat &data)
{
	if (this->GetLastdate() > data.c_Lastdate)
		return GREATER;
	else if (this->GetLastdate() < data.c_Lastdate)
		return LESS;
	else
		return EQUAL;
}

// Compare two Infotypes.
RelationType Chat::CompareByChatcode(const Chat &data)
{
	if (this->GetChatcode() > data.c_Chatcode)
		return GREATER;
	else if (this->GetChatcode() < data.c_Chatcode)
		return LESS;
	else
		return EQUAL;
}

// Read a record from file.
int Chat::c_ReadDataFromFile(ifstream& fin)
{
	fin >> c_Chatcode;
	fin >> c_Chatname;
	fin >> c_Newmsg;
	fin >> c_Memnum;

	string inId;
	string inName;
	for (int i = 0; i < c_Memnum; i++)
	{
		fin >> inId;
		fin >> inName;
		c_Members[inId] = inName;
	}
	int Msgnum = 0;
	fin >> Msgnum;
	Msg* msg; // 읽기용 임시변수
	for (int i = 0; i < Msgnum; i++)
	{
		msg = new Msg;
		(*msg).m_ReadDataFromFile(fin);
		AddNewMsg(*msg);
	}

	return 1;
}

// Write a record into file.
int Chat::c_WriteDataToFile(ofstream& fout)
{
	fout << c_Chatcode << " ";
	fout << c_Chatname << " ";
	fout << c_Newmsg << " ";
	fout << c_Memnum << " ";
	map<string, string>::iterator it = c_Members.begin();
	while (it != c_Members.end())
	{
		fout << (*it).first << " " << (*it).second << " ";
		it++;
	}
	fout << c_Msgnum << " ";
	for (int i = 0; i<c_Msgnum; i++)
		c_MsgList[i].m_WriteDataToFile(fout);

	return 1;
}

// Operator < with two Chats. 마지막날짜가 더 최신이면 더 우선순위를 줌
bool Chat::operator<(const Chat& data)
{
	if (this->CompareByBase(data) == GREATER)
		return true;
	else
		return false;
}

// Operator > with two Chats. 마지막날짜가 더 전이면 우선순위를 낮게줌
bool Chat::operator>(const Chat& data)
{
	if (this->CompareByBase(data) == LESS)
		return true;
	else
		return false;
}

// Operator == with two Chats.
bool Chat::operator==(const Chat& data)
{
	if (this->CompareByBase(data) == EQUAL)
		return true;
	else
		return false;
}