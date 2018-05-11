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
	//ä�ù� ���� ���
	DisplayChatOnScreen();

	//�޽����� ������
	if (c_Msgnum == 0)
	{
		cout << "\n\t No Message." << endl;
	}
	else
	{
		for (int i = 0; i < c_Msgnum; i++)
		{
			//�������� �޽������
			if (c_MsgList[i].GetSendId() == "/SERVER")
			{
				//ä�ù� �߾ӿ� ������ �ǽ�
				cout << endl;
				cout << setw(25 - c_MsgList[i].GetText().size() / 2) << "[[ " << c_MsgList[i].GetText() << " ]]" << endl << endl;
			}

			//�޽������̵�� Curr Id�� ������ -> �޽����� ���� �޽����̸�
			else if (c_MsgList[i].GetSendId() == Id)
			{

				//���� �޽����� ���̵� ���ٸ�
				if (c_MsgList[i - 1].GetSendId() == Id)
				{
					//������ �޽�����
					if (i == c_Msgnum - 1)
					{
						//�޽��� �������̽� �۾����� ����
						cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
						//���� �޽��� ��� �� ��ȯ
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
						//�޽��� ���
						cout << " " << c_MsgList[i].GetText() << " ";
						//���� �����
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << ' ';
						cout << endl;
					}
					// ������ �޽����� �ƴϸ�
					else
					{
						//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i + 1].GetSendId() != Id)
						{
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						else// ���� �޽����� �ð��� ������
						{
							cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
					}
				}
				//���� �޽����� ���̵� �ٸ��ٸ�
				else
				{
					//������ �޽�����
					if (i == c_Msgnum - 1)
					{
						cout << setw(50 - c_Members[Id].size());
						cout << c_Members[Id] << endl;
						cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
						//���� �޽��� ��� �� ��ȯ
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
						//�޽��� ���
						cout << " " << c_MsgList[i].GetText() << " ";
						//���� �����
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << ' ';
						cout << endl;
					}
					// ������ �޽����� �ƴϸ�
					else
					{
						//���� �޽����� �ð��� �ٸ��ų� �۽��� ���̵� �ٸ���
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						else// ���� �޽����� �ð��� ������
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
					}
				}
			}

			//���� �޽����̸�
			else
			{
				//���� �޽����� ���̵� ���ٸ�
				if (c_MsgList[i - 1].GetSendId() == c_MsgList[i].GetSendId())
				{
					//������ �޽�����
					if (i == c_Msgnum - 1)
					{
						cout << "\t ";
						// ���� �޽��� ��� �� ��ȯ
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
						// �޽��� �ۼ�
						cout << " " << c_MsgList[i].GetText() << " ";
						//���� �����
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
					}
					// ������ �޽����� �ƴϸ�
					else
					{
						//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
						{
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						else// ���� �޽����� �ð��� ������
						{
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
					}
				}
				//���� �޽����� ���̵� �ٸ��ٸ�
				else
				{
					//������ �޽�����
					if (i == c_Msgnum - 1)
					{
						cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
						cout << "\t ";
						// ���� �޽��� ��� �� ��ȯ
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
						// �޽��� �ۼ�
						cout << " " << c_MsgList[i].GetText() << " ";
						//���� �����
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
					}
					// ������ �޽����� �ƴϸ�
					else
					{
						//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
						if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << " " << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						else// ���� �޽����� �ð��� ������
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
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
	//ä�ù� ���� ���
	DisplayChatOnScreen();

	//�޽����� ������
	if (c_Msgnum == 0)
	{
		cout << "\n\t No Message." << endl;
	}
	else
	{
		for (int i = 0; i < c_Msgnum; i++)
		{
			//�������� �޽������
			if (c_MsgList[i].GetSendId() == "/SERVER")
			{
				//ä�ù� �߾ӿ� ������ �ǽ�
				cout << endl;
				cout << setw(25 - c_MsgList[i].GetText().size() / 2) << "[[ " << c_MsgList[i].GetText() << " ]]" << endl << endl;
			}
			//ã�� ���ڿ��� ���� ���
			else if (c_MsgList[i].GetText().find(text) < c_MsgList[i].GetText().length())
			{
				//�޽������̵�� Curr Id�� ������ -> �޽����� ���� �޽����̸�
				if (c_MsgList[i].GetSendId() == Id)
				{

					//���� �޽����� ���̵� ���ٸ�
					if (c_MsgList[i - 1].GetSendId() == Id)
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							//�޽��� �������̽� �۾����� ����
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i + 1].GetSendId() != Id)
							{
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}
					//���� �޽����� ���̵� �ٸ��ٸ�
					else
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �۽��� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}
				}

				//���� �޽����̸�
				else
				{
					//���� �޽����� ���̵� ���ٸ�
					if (c_MsgList[i - 1].GetSendId() == c_MsgList[i].GetSendId())
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5);
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5);
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}
					//���� �޽����� ���̵� �ٸ��ٸ�
					else
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5);
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5);
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
							}
						}
					}

				}
				cin.get();
			}
			//ã�� ���ڿ��� ���� ���
			else
			{
				//�޽������̵�� Curr Id�� ������ -> �޽����� ���� �޽����̸�
				if (c_MsgList[i].GetSendId() == Id)
				{

					//���� �޽����� ���̵� ���ٸ�
					if (c_MsgList[i - 1].GetSendId() == Id)
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							//�޽��� �������̽� �۾����� ����
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i + 1].GetSendId() != Id)
							{
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
						}
					}
					//���� �޽����� ���̵� �ٸ��ٸ�
					else
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							cout << setw(50 - c_Members[Id].size());
							cout << c_Members[Id] << endl;
							cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
							//���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
							//�޽��� ���
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << ' ';
							cout << endl;
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �۽��� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(41 - c_MsgList[i].GetText().size()) << c_MsgList[i].GetDate().substr(11, 5) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << setw(50 - c_Members[Id].size());
								cout << c_Members[Id] << endl;
								cout << setw(43 - c_MsgList[i].GetText().size()) << "  ";
								//���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								//�޽��� ���
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
						}
					}
				}

				//���� �޽����̸�
				else
				{
					//���� �޽����� ���̵� ���ٸ�
					if (c_MsgList[i - 1].GetSendId() == c_MsgList[i].GetSendId())
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << ' ';
								cout << endl;
							}
						}
					}
					//���� �޽����� ���̵� �ٸ��ٸ�
					else
					{
						//������ �޽�����
						if (i == c_Msgnum - 1)
						{
							cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
							cout << "\t ";
							// ���� �޽��� ��� �� ��ȯ
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
							// �޽��� �ۼ�
							cout << " " << c_MsgList[i].GetText() << " ";
							//���� �����
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
						}
						// ������ �޽����� �ƴϸ�
						else
						{
							//���� �޽����� �ð��� �ٸ��ų� �����޽����� �۽� ���̵� �ٸ���
							if (c_MsgList[i].GetDate().substr(11, 5) != c_MsgList[i + 1].GetDate().substr(11, 5) || c_MsgList[i].GetSendId() != c_MsgList[i + 1].GetSendId())
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								cout << c_MsgList[i].GetDate().substr(11, 5) << endl;
							}
							else// ���� �޽����� �ð��� ������
							{
								cout << "\t" << c_Members[c_MsgList[i].GetSendId()] << endl;
								cout << "\t ";
								// ���� �޽��� ��� �� ��ȯ
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
								// �޽��� �ۼ�
								cout << " " << c_MsgList[i].GetText() << " ";
								//���� �����
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
	//����� ���ٸ�
	if (c_Members.find(Id) == c_Members.end())
	{
		return -1;
	}
	//����� �ִٸ�
	else
	{
		return 1;
	}
}

// Delete member in the chat.
int Chat::Deletemem(string Id)
{
	map<string, string>::iterator it = c_Members.begin();
	// ����� ã�� ����

	while (it != c_Members.end())
	{
		//ã�� ����� �ִٸ� ����
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
	//msg ����� �����ϸ�
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
	Msg* msg; // �б�� �ӽú���
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

// Operator < with two Chats. ��������¥�� �� �ֽ��̸� �� �켱������ ��
bool Chat::operator<(const Chat& data)
{
	if (this->CompareByBase(data) == GREATER)
		return true;
	else
		return false;
}

// Operator > with two Chats. ��������¥�� �� ���̸� �켱������ ������
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