#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>  
#include <vector>                               //vector ˳������ ��������Խ .at()����
#include <algorithm>                            //ģ���  
#include <fstream>
#include <cctype>                               //�ַ������   �ַ����ԡ�ӳ��
#include <iomanip>                              //��������ͷ�ļ�
using namespace std;
//ѧ����Ϣ
struct student
{
	static int s1;
	int id;//���߱��
	string name;//��������
	int borrowsum;;//�ѽ����鱾��
	int number;//���ж���δ��
	int b[10];//��������

};
//ͼ����Ϣ
struct book
{
	int idbook;//ͼ����
	int BorrowCount;//ͼ�������
	string name;//����
	int sum;//�ܿ��
	int nowsum;//�ִ�
	bool ok;//�Ƿ�ɽ���
	string author;
	double price;
};
bool cmpByidbook(book a,book b)
{
	return a.idbook<b.idbook;
}
bool cmpByCount(book a,book b)
{
	return a.BorrowCount>b.BorrowCount;
}
bool cmpByBorrowsum(student a,student b)
{
	return a.borrowsum>b.borrowsum;
}
bool smpByid(student a,student b)
{
	return a.id<b.id;
}
class Library
{
private:
	vector<book> DataBook;
	vector<student> DataStudent;
	vector<int> betoil;//�������ͼ��ݣ��洢���
public:
	Library();
	void ShowAllBook();
	void AddBook(book NewBook);//����ͼ��
	void DeleteBook(string author,string bookname);//ɾ��ͼ��
	void BorrowBook(string name,string author);//ͼ�����
	void BackBook(string name,string author,int k);//����
	void SearchBookName(string thebook);//��ѯͼ��
	int SearchBookAB(string author,string bookname);
	int GetStudent();
	int SearchStudent(int id);
	void HaveStudent(int id);//��ѯ��Ա
	void AddStudent(student a);//���ӻ�Ա
	void DeleteStudent(int id);//ɾ����Ա
	void PrintStudent(int kid);//������Ϣ
	void SaveBook();//����ͼ����ļ�
	void SaveStudent();//����ѧ���ļ�
	void PrintBook(book a);//���ĳ���������Ϣ
};

Library::Library()
{
	int AllBook,AllStudent;
	ifstream fin("book.txt");
	if(fin)
	{
		fin>>AllBook;
		for(int i=0;i<AllBook;i++)
		{
			book tem;
			fin>>tem.idbook>>tem.name>>tem.author>>tem.price>>tem.sum>>tem.nowsum>>tem.BorrowCount>>tem.ok;
			DataBook.push_back(tem);
		}
		fin.close();
	}
	ifstream tfin("student.txt");
	if(tfin)
	{
		tfin>>AllStudent;
		for(int i=0;i<AllStudent;i++)
		{
			student tem;
			tfin>>tem.id>>tem.name>>tem.borrowsum>>tem.number;
			for(int j=0;j<10;j++)
			{
				tfin>>tem.b[j];
			}
			DataStudent.push_back(tem);
		}
		tfin.close();
	}
}
int Library::GetStudent()
{
	int k=(int)DataStudent.size();
	return k+1;
}
//����ͼ��
void Library::AddBook(book NewBook)
{
	DataBook.push_back(NewBook);
}
//���ӻ�Ա
void Library::AddStudent(student newstudent)
{
	DataStudent.push_back(newstudent);
}
//ɾ��ͼ��
void Library::DeleteBook(string author,string bookname)
{
	int num = SearchBookAB(author,bookname);
	if(num != -1)
	{
		DataBook.erase(DataBook.begin()+num);
		SaveBook();
		cout<<"ɾ���ɹ�"<<endl;
		return;
	}
	else 
		cout<<"���޴��飡 \n";
}
//ͼ�����
void Library::BorrowBook(string name,string author)
{
	int flag=0;
	int sid=-1;
	for(int i=0;i<(int)DataBook.size();i++)
	{
		if(DataBook[i].name == name&&DataBook[i].author==author)
		{
			if(DataBook[i].nowsum)
			{
				cout<<"������ߵĶ��ߺ�Ϊ��";
				cin>>sid;
				if(DataStudent[sid-1].number>10)
				{
					cout<<"���Ѿ��������������������ٽ�!"<<endl;
					break;
				}
				flag=1;
				DataBook[i].nowsum=DataBook[i].nowsum-1;
				DataBook[i].BorrowCount=DataBook[i].BorrowCount+1;
				DataBook[i].ok=bool(DataBook[i].nowsum);
				DataStudent[sid-1].number++;
				for(int j=0;j<10;j++)
				{
					if(DataStudent[sid-1].b[j]==0) 
						DataStudent[sid-1].b[j]=DataBook[i].idbook;
					SaveBook();
					SaveStudent();
				}
				cout<<"���ĳɹ�"<<endl;
			}
			else
			{
				cout<<"ͼ����޶�����飬�޷�����"<<endl;
			}
		}
	}
	if(!flag)
		cout<<"��Ǹ���޷��ҵ�����Ҫ����"<<endl;
}
//����
void Library::BackBook(string name,string author,int k)
{
	int c=-1;
	{
		cout<<"���������id��";
		cin>>c;
		c=c-1;
	}
	for(int i=0;i < (int)DataBook.size();i++)
	{
		if(DataBook[i].name==name&&DataBook[i].author==author)
		{
			DataBook[i].nowsum=DataBook[i].nowsum+1;
			DataBook[i].ok=bool(DataBook[i].nowsum);
			for(int j=0;j<10;j++)
			{
				if(DataStudent[c].b[j]==DataBook[i].idbook) 
					DataStudent[c].b[j]=0;
			}
			DataStudent[c].number--;
			break;
		}
	}
	SaveBook();
	SaveStudent();
	cout<<"����ɹ�"<<endl;

}
//�鱾��Ϣ
void Library::PrintBook(book a)
{
	cout<<"��ţ�"<<setw(12)<<a.idbook;
	cout<<"���֣�"<<setw(14)<<a.name;
	cout<<"���ߣ�"<<setw(14)<<a.author<<endl;
	cout<<"�۸�"<<setw(14)<<fixed<<setprecision(2)<<a.price;
	cout<<"�ܿ������"<<setw(10)<<a.sum;
	cout<<"�ֿ������"<<setw(10)<<a.nowsum;
	cout<<"��������"<<setw(14)<<a.BorrowCount<<endl;
	cout<<"״̬��"<<setw(14)<<(a.ok==0?"���ɽ�":"�ɽ�");
	cout<<endl<<endl;
}
//������Ϣ
void Library::PrintStudent(int kid)
{
	int id=kid-1;
	cout<<setw(8)<<DataStudent[id].id;
	cout<<setw(8)<<DataStudent[id].name;
	cout<<setw(18)<<DataStudent[id].number;

}
void Library::ShowAllBook()
{
	system("cls");
	cout<<"����ͼ��:"<<endl;
	for(int i=0;i<(int)DataBook.size();i++)
	{
		PrintBook(DataBook[i]);
	}
}
//��ѯ��Ա
void Library::HaveStudent(int id )
{
	bool flag=false;
	for (int i = 0; i < (int)DataStudent.size(); i++)
	{
		if (DataStudent[i].id == id)
		{
			flag=true;
			PrintStudent(id);
		}
	}
	if(!flag) cout<<"���޴���";
}
int Library::SearchStudent(int id)
{
	int m=-1;
	for(int i=0;i<(int)DataStudent.size();i++)
	{
		if(DataStudent[i].id==id)
		{
			return i;
		}
	}
	return m;
}
//��ѯͼ��
void Library::SearchBookName(string thebook)
{
	int flag=0;
	for(int i=0;i<(int)DataBook.size();i++)
	{
		if(DataBook[i].name==thebook)
		{
			PrintBook(DataBook[i]);
			flag=1;
		}
	}
	if(!flag) cout<<"���޴���!\n";
}
int Library::SearchBookAB(string theauthor,string thebook)
{
	for(int i=0;i<(int)DataBook.size();++i)
	{
		if(DataBook[i].author==theauthor&&DataBook[i].name==thebook)
		{
			PrintBook(DataBook[i]);
			return -1;
		}
		else
			cout<<"���޴���!";
	}
	return -1;
}
//ɾ����Ա
void Library::DeleteStudent(int id)
{
	int num = SearchStudent(id);
	if(num != -1)
	{
		DataStudent.erase(DataStudent.begin()+num);
		SaveStudent();
		cout<<"ɾ���ɹ�"<<endl;
		return;
	}
	else cout<<"���޴��ˣ� \n";
}
//������Ϣ�����ļ�
void Library::SaveBook()
{
	ofstream fout("book.txt");
	if(fout)
	{
		fout<<DataBook.size()<<endl;
		for(int i=0;i<(int)DataBook.size();i++)
		{
			fout<<DataBook[i].idbook<<" "<<DataBook[i].name<<" "<<DataBook[i].author<<" "<<DataBook[i].price<<" "<<DataBook[i].sum<<" "<<DataBook[i].nowsum<<" "<<DataBook[i].BorrowCount<<" "<<DataBook[i].ok<<" "<<endl;
		}
		fout.close();
	}
}
//��ѧ����Ϣ�����ļ�
void Library::SaveStudent()
{
	ofstream fout("student.txt");
	if(fout)
	{
		fout<<DataStudent.size()<<endl;
		for(int i=0;i<(int)DataStudent.size();i++)
		{
			fout<<DataStudent[i].id<<" "<<DataStudent[i].name<<" "<<DataStudent[i].borrowsum<<" "<<DataStudent[i].number;
			for(int j=0;j<10;j++)
			{
				fout<<" "<<DataStudent[i].b[j];
			}
			fout<<endl;
		}
		fout.close();
	}
}
int main()
{
	cout.setf(ios::left);//�����
	Library mybook;
	cout<<"**************ͼ��ܹ���ϵͳ***************"<<endl<<endl;
	cout<<"��������߱�ŵ�¼"<<endl;
	int mm=110;
	int bh,k=0,z=0,cho;
	cin>>bh;
	if(bh==mm)
	{
		cout<<"��ӭʹ��"<<endl;
		k=2;
	}
	else z=3;

	if(k==2)
	{
		do
		{
			cout<<"��ӭ�������Աϵͳ"<<endl;
			cin.clear();
			cin.sync();
			cout<<"1.ͼ��Ŀ¼"<<endl;
			cout<<"2.��ѯͼ��"<<endl;
			cout<<"3.���ͼ��"<<endl;
			cout<<"4.ɾ��ͼ��"<<endl;
			cout<<"5.ɾ��ѧ��"<<endl;
			cout<<"6.��ѯ��Ա"<<endl;
			cout<<"------------------------------------"<<endl;
			cout<<"��ѡ���ܣ�����ָ��"<<endl;
			cin>>cho;
			switch(cho)
			{
			case 1:
				{
					int cho2;
					mybook.ShowAllBook();
					cout<<"------------------------------"<<endl;
					cin>>cho2;
					break;
				}
			case 2:
				{
					string Name;
					cout<<"������������"<<endl;
					cin>>Name;
					mybook.SearchBookName(Name);
					break;
				}
			case 3:
				{
					book temp;
					cin.clear();
				    cin.sync();
					cout << "���:";
					cin >> temp.idbook;
					cout << "����:";
					cin >> temp.name;
					cout << "���ߣ�";
					cin >> temp.author;
					cout << "�۸�:";
					cin >> temp.price;
					cout << "����:";
					cin >> temp.sum;
					temp.nowsum = temp.sum;
					temp.BorrowCount = 0;
					temp.ok = true;
					mybook.AddBook(temp);
					mybook.SaveBook();
					cout << "��Ϣ����ɹ�" << endl;
					break;
				}
			case 4:
				{
					string bookname,author;
					cout<<"���������������ߣ�"<<endl;
					cin>>bookname>>author;
					mybook.DeleteBook(author,bookname);
					break;
				}
			case 5:
				{
					int id;
					cout<<"������ѧ��id:"<<endl;
					cin>>id;
					mybook.DeleteStudent(id);
					break;
				}
			case 6:
				{
					int id;
					cout<<"������ѧ��id:"<<endl;
					cin>>id;
					cout<<setw(8)<<"ѧ��id"<<setw(8)<<"ѧ������"<<setw(8)<<"�����鼮����"<<endl;
					mybook.HaveStudent(id);
					break;
				}
			}
		}while(cho>=1&&cho<=5);
		{
			cout<<"����������"<<endl;
			system("pause");
		}
	}
	if(z==3)
	{
		if(mybook.SearchStudent(bh)==-1)
		{
			int n;
			cout<<"��Ϊע���Ա���Ƿ�ע�᣿\n";
			cout<<"         1.ע��\n";
			cout<<"         2.�˳�\n";
			cin>>n;
			student temp;
			if(n==1)
			{
				cout<<"������������֣�";
				cin>>temp.name;
				cin.clear();
				cin.sync();
				temp.id=mybook.GetStudent();
				temp.borrowsum=0;
				temp.number=0;
				for(int i=0;i<10;i++)
				{
					temp.b[i]=0;
				}
				mybook.AddStudent(temp);
				mybook.SaveStudent();
				cout<<"------------------ע��ɹ�---------\n";
				cout<<"------------------������"<<temp.name<<endl;
				cout<<"------------------���ߺţ�"<<temp.id<<endl;
				k = temp.id;
				do
				{
					cin.clear();
					cin.sync();
					cout<<"1.��ѯͼ��"<<endl;
					cout<<"2.����ͼ��"<<endl;
					cout<<"3.�黹ͼ��"<<endl;
					cout<<"4.��ѯ������Ϣ"<<endl;
					cout<<"------------------------------------"<<endl;
					cout<<"��ѡ���ܣ�����ָ��"<<endl;
					cin>>cho;
					switch(cho)
					{
					case 1:
						{
							string Name;
							cout<<"������������"<<endl;
							cin>>Name;
							mybook.SearchBookName(Name);
							break;
						}
					case 2:
						{
							string bookname,bookauthor;
							cout<<"���������������ߣ�"<<endl;
							cin>>bookname>>bookauthor;
							mybook.BorrowBook(bookname,bookauthor);
							mybook.SaveBook();
							system("pause");
							break;
						}
					case 3:
						{
							string bookname,bookauthor;
							cout<<"�����뻹�����������ߣ�"<<endl;
							cin>>bookname>>bookauthor;
							mybook.BackBook(bookname,bookauthor,-1);
							mybook.SaveBook();
							system("pause");
							break;
						}
					case 4:
						{
							cout<<setw(8)<<"���ߺ�"<<setw(8)<<"����"<<setw(8)<<"���ڽ��������"<<endl;
							mybook.PrintStudent(k);
							system("pause");
							break;
						}
					}			
				}while(cho>=1&&cho<=4);
				{
					cout<<"����������"<<endl;
					system("pause");
				}
			}
			else 
				return (0);
		}
		else
		{
			k=bh;
		}
		do
		{
			cin.clear();
			cin.sync();
			cout<<"1.��ѯͼ��"<<endl;
			cout<<"2.����ͼ��"<<endl;
			cout<<"3.�黹ͼ��"<<endl;
			cout<<"4.��ѯ������Ϣ"<<endl;
			cout<<"------------------------------------"<<endl;
			cout<<"��ѡ���ܣ�����ָ��"<<endl;
			cin>>cho;
			switch(cho)
			{
			case 1:
				{
					string Name;
					cout<<"������������"<<endl;
					cin>>Name;
					mybook.SearchBookName(Name);
					break;
				}
			case 2:
				{
					string bookname,bookauthor;
					cout<<"���������������ߣ�"<<endl;
					cin>>bookname>>bookauthor;
					mybook.BorrowBook(bookname,bookauthor);
					mybook.SaveBook();
					system("pause");
					break;
				}
			case 3:
				{
					string bookname,bookauthor;
					cout<<"�����뻹�����������ߣ�"<<endl;
					cin>>bookname>>bookauthor;
					mybook.BackBook(bookname,bookauthor,-1);
					mybook.SaveBook();
					system("pause");
					break;
				}
			case 4:
				{
					cout<<setw(8)<<"���ߺ�"<<setw(8)<<"����"<<setw(8)<<"���ڽ��������"<<endl;
					mybook.PrintStudent(k);
					system("pause");
					break;
				}
			}
		}while(cho>=1&&cho<=4);
		{
			cout<<"����������"<<endl;
			system("pause");
		}
	}
}