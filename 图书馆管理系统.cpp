#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>  
#include <vector>                               //vector 顺序容器 比数组优越 .at()访问
#include <algorithm>                            //模板库  
#include <fstream>
#include <cctype>                               //字符处理库   字符测试、映射
#include <iomanip>                              //流操作符头文件
using namespace std;
//学生信息
struct student
{
	static int s1;
	int id;//读者编号
	string name;//读者姓名
	int borrowsum;;//已借阅书本量
	int number;//还有多少未还
	int b[10];//所借书编号

};
//图书信息
struct book
{
	int idbook;//图书编号
	int BorrowCount;//图书借阅量
	string name;//书名
	int sum;//总库存
	int nowsum;//现存
	bool ok;//是否可借阅
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
	vector<int> betoil;//新书存入图书馆，存储编号
public:
	Library();
	void ShowAllBook();
	void AddBook(book NewBook);//增加图书
	void DeleteBook(string author,string bookname);//删除图书
	void BorrowBook(string name,string author);//图书借阅
	void BackBook(string name,string author,int k);//还书
	void SearchBookName(string thebook);//查询图书
	int SearchBookAB(string author,string bookname);
	int GetStudent();
	int SearchStudent(int id);
	void HaveStudent(int id);//查询会员
	void AddStudent(student a);//增加会员
	void DeleteStudent(int id);//删除会员
	void PrintStudent(int kid);//借书信息
	void SaveBook();//存入图书馆文件
	void SaveStudent();//存入学生文件
	void PrintBook(book a);//输出某书的所有信息
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
//增加图书
void Library::AddBook(book NewBook)
{
	DataBook.push_back(NewBook);
}
//增加会员
void Library::AddStudent(student newstudent)
{
	DataStudent.push_back(newstudent);
}
//删除图书
void Library::DeleteBook(string author,string bookname)
{
	int num = SearchBookAB(author,bookname);
	if(num != -1)
	{
		DataBook.erase(DataBook.begin()+num);
		SaveBook();
		cout<<"删除成功"<<endl;
		return;
	}
	else 
		cout<<"查无此书！ \n";
}
//图书借阅
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
				cout<<"借书读者的读者号为：";
				cin>>sid;
				if(DataStudent[sid-1].number>10)
				{
					cout<<"你已经超过最大借书数，不可再借!"<<endl;
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
				cout<<"借阅成功"<<endl;
			}
			else
			{
				cout<<"图书馆无多余藏书，无法借阅"<<endl;
			}
		}
	}
	if(!flag)
		cout<<"抱歉，无法找到您想要的书"<<endl;
}
//还书
void Library::BackBook(string name,string author,int k)
{
	int c=-1;
	{
		cout<<"请输入你的id：";
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
	cout<<"还书成功"<<endl;

}
//书本信息
void Library::PrintBook(book a)
{
	cout<<"编号："<<setw(12)<<a.idbook;
	cout<<"名字："<<setw(14)<<a.name;
	cout<<"作者："<<setw(14)<<a.author<<endl;
	cout<<"价格："<<setw(14)<<fixed<<setprecision(2)<<a.price;
	cout<<"总库存量："<<setw(10)<<a.sum;
	cout<<"现库存量："<<setw(10)<<a.nowsum;
	cout<<"借阅量："<<setw(14)<<a.BorrowCount<<endl;
	cout<<"状态："<<setw(14)<<(a.ok==0?"不可借":"可借");
	cout<<endl<<endl;
}
//借书信息
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
	cout<<"所有图书:"<<endl;
	for(int i=0;i<(int)DataBook.size();i++)
	{
		PrintBook(DataBook[i]);
	}
}
//查询会员
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
	if(!flag) cout<<"查无此人";
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
//查询图书
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
	if(!flag) cout<<"查无此书!\n";
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
			cout<<"查无此书!";
	}
	return -1;
}
//删除会员
void Library::DeleteStudent(int id)
{
	int num = SearchStudent(id);
	if(num != -1)
	{
		DataStudent.erase(DataStudent.begin()+num);
		SaveStudent();
		cout<<"删除成功"<<endl;
		return;
	}
	else cout<<"查无此人！ \n";
}
//将书信息存入文件
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
//将学生信息存入文件
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
	cout.setf(ios::left);//左对齐
	Library mybook;
	cout<<"**************图书管管理系统***************"<<endl<<endl;
	cout<<"请输入读者编号登录"<<endl;
	int mm=110;
	int bh,k=0,z=0,cho;
	cin>>bh;
	if(bh==mm)
	{
		cout<<"欢迎使用"<<endl;
		k=2;
	}
	else z=3;

	if(k==2)
	{
		do
		{
			cout<<"欢迎进入管理员系统"<<endl;
			cin.clear();
			cin.sync();
			cout<<"1.图书目录"<<endl;
			cout<<"2.查询图书"<<endl;
			cout<<"3.添加图书"<<endl;
			cout<<"4.删除图书"<<endl;
			cout<<"5.删除学生"<<endl;
			cout<<"6.查询会员"<<endl;
			cout<<"------------------------------------"<<endl;
			cout<<"请选择功能，输入指令"<<endl;
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
					cout<<"请输入书名："<<endl;
					cin>>Name;
					mybook.SearchBookName(Name);
					break;
				}
			case 3:
				{
					book temp;
					cin.clear();
				    cin.sync();
					cout << "编号:";
					cin >> temp.idbook;
					cout << "书名:";
					cin >> temp.name;
					cout << "作者：";
					cin >> temp.author;
					cout << "价格:";
					cin >> temp.price;
					cout << "数量:";
					cin >> temp.sum;
					temp.nowsum = temp.sum;
					temp.BorrowCount = 0;
					temp.ok = true;
					mybook.AddBook(temp);
					mybook.SaveBook();
					cout << "信息保存成功" << endl;
					break;
				}
			case 4:
				{
					string bookname,author;
					cout<<"请输入书名和作者："<<endl;
					cin>>bookname>>author;
					mybook.DeleteBook(author,bookname);
					break;
				}
			case 5:
				{
					int id;
					cout<<"请输入学生id:"<<endl;
					cin>>id;
					mybook.DeleteStudent(id);
					break;
				}
			case 6:
				{
					int id;
					cout<<"请输入学生id:"<<endl;
					cin>>id;
					cout<<setw(8)<<"学生id"<<setw(8)<<"学生姓名"<<setw(8)<<"借阅书籍数量"<<endl;
					mybook.HaveStudent(id);
					break;
				}
			}
		}while(cho>=1&&cho<=5);
		{
			cout<<"请重新输入"<<endl;
			system("pause");
		}
	}
	if(z==3)
	{
		if(mybook.SearchStudent(bh)==-1)
		{
			int n;
			cout<<"你为注册会员，是否注册？\n";
			cout<<"         1.注册\n";
			cout<<"         2.退出\n";
			cin>>n;
			student temp;
			if(n==1)
			{
				cout<<"请输入你的名字：";
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
				cout<<"------------------注册成功---------\n";
				cout<<"------------------姓名："<<temp.name<<endl;
				cout<<"------------------读者号："<<temp.id<<endl;
				k = temp.id;
				do
				{
					cin.clear();
					cin.sync();
					cout<<"1.查询图书"<<endl;
					cout<<"2.借阅图书"<<endl;
					cout<<"3.归还图书"<<endl;
					cout<<"4.查询读者信息"<<endl;
					cout<<"------------------------------------"<<endl;
					cout<<"请选择功能，输入指令"<<endl;
					cin>>cho;
					switch(cho)
					{
					case 1:
						{
							string Name;
							cout<<"请输入书名："<<endl;
							cin>>Name;
							mybook.SearchBookName(Name);
							break;
						}
					case 2:
						{
							string bookname,bookauthor;
							cout<<"请输入书名和作者："<<endl;
							cin>>bookname>>bookauthor;
							mybook.BorrowBook(bookname,bookauthor);
							mybook.SaveBook();
							system("pause");
							break;
						}
					case 3:
						{
							string bookname,bookauthor;
							cout<<"请输入还的书名和作者："<<endl;
							cin>>bookname>>bookauthor;
							mybook.BackBook(bookname,bookauthor,-1);
							mybook.SaveBook();
							system("pause");
							break;
						}
					case 4:
						{
							cout<<setw(8)<<"读者号"<<setw(8)<<"姓名"<<setw(8)<<"现在借阅书个数"<<endl;
							mybook.PrintStudent(k);
							system("pause");
							break;
						}
					}			
				}while(cho>=1&&cho<=4);
				{
					cout<<"请重新输入"<<endl;
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
			cout<<"1.查询图书"<<endl;
			cout<<"2.借阅图书"<<endl;
			cout<<"3.归还图书"<<endl;
			cout<<"4.查询读者信息"<<endl;
			cout<<"------------------------------------"<<endl;
			cout<<"请选择功能，输入指令"<<endl;
			cin>>cho;
			switch(cho)
			{
			case 1:
				{
					string Name;
					cout<<"请输入书名："<<endl;
					cin>>Name;
					mybook.SearchBookName(Name);
					break;
				}
			case 2:
				{
					string bookname,bookauthor;
					cout<<"请输入书名和作者："<<endl;
					cin>>bookname>>bookauthor;
					mybook.BorrowBook(bookname,bookauthor);
					mybook.SaveBook();
					system("pause");
					break;
				}
			case 3:
				{
					string bookname,bookauthor;
					cout<<"请输入还的书名和作者："<<endl;
					cin>>bookname>>bookauthor;
					mybook.BackBook(bookname,bookauthor,-1);
					mybook.SaveBook();
					system("pause");
					break;
				}
			case 4:
				{
					cout<<setw(8)<<"读者号"<<setw(8)<<"姓名"<<setw(8)<<"现在借阅书个数"<<endl;
					mybook.PrintStudent(k);
					system("pause");
					break;
				}
			}
		}while(cho>=1&&cho<=4);
		{
			cout<<"请重新输入"<<endl;
			system("pause");
		}
	}
}