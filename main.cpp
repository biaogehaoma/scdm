#include <string>
#include <iostream>
#include <Windows.h>//头文件
using namespace std;//避免发生重命名问题

const int MAXSIZE = 3;
const int price = 5;

struct Car
{
	string num;//车牌号
	int time;//停车时间
};

struct Node //结构体队列元素结点
{
	Car * s_car;
	Node * next;
};
//栈中元素结点
class awaitStop  //链式队列类
{
private:
	Node * front ,* rear;//头指针，尾指针
public:
	awaitStop();
	~awaitStop();
	void EnQueue(Node&);//入队
	Car DelQueue();;//出队
	void clean();//清理
	void output();//输出
};

class stop //栈类
{
private:
	Car car[MAXSIZE];

public:
	int top;//栈
	stop();//构造函数
	~stop();//析构函数
	int push(Car);//入栈
	Car pop();//出栈
	void getout();//输出函数
};

stop::stop()// 栈的构造函数
{
	top = -1;//初始化
}

stop::~stop()//析构函数
{
	delete[]car;
}

int stop::push(Car t) //入栈函数
{
	if (top == MAXSIZE)
	{
		cout << "停车场已满!!!" << endl;
		return -1;
	}
	else
	{
		car[++top].num = t.num;
		car[top].time = t.time;
		cout<<car[top].time<<endl;
		return top;
	}
}
Car stop::pop()//出栈函数，删除栈顶元素
{
	if (top == -1)
		cout << "停车场内并没有车辆" << endl;
	else
		return car[top--];
}
void stop::getout()
{
	for (int i = 0; i <= top; i++)
		cout << "车牌号码：" << car[i].num << "   " << "到达时刻：" << car[i].time << endl << endl;

}


awaitStop::awaitStop()//构造函数
{
	clean();
	rear = front = new Node;//对尾=对头

}
awaitStop::~awaitStop()//析构函数
{
	delete front, rear;//对头，队尾
}
void awaitStop::EnQueue(Node& e)//入队
{
	Node *p = new Node;//指向所分配的内存的首地址，新地址
	p = &e;
	if (p)
	{
		rear->next = p;//新结点入队的操作，原来的最后一个结点的指针域里的指针指向了p,p入队了，成为链队的最后一个结点。
		rear = rear->next;//移动队尾指针到新节点
	}
	else
		cout << "候车区已满" << endl;
}
Car awaitStop::DelQueue()//出队函数
{
	Car p;
	p.num = "";
	p.time = 0;
	if (front == rear)
	{
		cout << "候车区无车!!!" << endl;
		return p;
	}
	else
	{
		Node* q;
		q = new Node;
		q = front->next;
		p = *(q->s_car); //将队列中数据给P
		front->next = q->next; //front指向后面一个元素
		if (rear == front) // 如果队列为空，使队尾指针指向对头
			rear = front;
		return p;
	}
}
void awaitStop::clean()  //队列清空
{
	if (rear == front)
		cout << "便道为空！！" << endl;
	else{
		Node * p = new Node;//指向所分配的内存的首地址，新地址
		while (front->next != NULL)//队头的next域指向的结构体的next域的值不为空
		{
			p = front->next;
			front->next = p->next;
			delete p;
		}
		rear = front;
	}
}
void awaitStop::output()//输出队列元素
{
	for (Node* p = front->next; p != NULL; p = p->next)//判断 执行 增加
		cout << "车牌号码；" << p->s_car->num << endl << endl;
}
void mainscreen(stop& sto, awaitStop& await);//主屏幕函数声明
void inStop(stop& sto, awaitStop& await)//进入停车场函数
{
	int i = -1;
	Car s;
	s.time = 0;
	Node l_car;
	l_car.s_car = &s;
	l_car.next = NULL;
	cout << "请输入车辆信息"<<endl;
	cout << "车牌号码：";
	cin >> s.num;
	cout << "到达时间：";
	SYSTEMTIME sys;//调用系统时间
	GetLocalTime(&sys);//调用系统时间
	cout <<""<<sys.wYear<<" "<<sys.wMonth<<" "<<sys.wDay<<" "<<sys.wHour<<" "<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "<<sys.wDayOfWeek;//调用系统时间
   //cin>>s.time;//栈中数据输入........
	if (sto.top == MAXSIZE - 1)//栈满条件
	{
		cout << "停车场已满，已将车辆停入便道" << endl;
		await.EnQueue(l_car);
	}
	else{
		i = sto.push(s);//出栈
		cout << "已将车辆停入停车场，序号为；" << i + 1 << endl;
	}
	cout << "是否继续停车?(1是继续，0是返回)";
	int choice = -1;
	cin >> choice;
	if (choice == 0) //判断下一步进行指令
		mainscreen(sto, await);
	else{
		if (choice == 1)
			inStop(sto, await);
		else{
			exit(1);
		}
	}
}
void outStop(stop& sto, awaitStop& await)//出停车场函数
{
	sto.getout();
	string s;
	stop sto_sup;
	cout << "请输入要开出的车辆车牌号：";
	cin >> s;
	cout << endl;
	Car sup;
	sup.time = 0;
	sup = sto.pop();
	while (s != sup.num)//将栈中元素存入辅助栈
	{
		sto_sup.push(sup);//出
		sup = sto.pop();
	}
	cout << "车牌号码：" << sup.num << endl << endl;
	int outStoptime;
	cout << "请输入此刻时间：(此刻时间应大于入厂时间）：";
	SYSTEMTIME sys;//调用系统时间
	GetLocalTime(&sys);//调用系统函数
	cout <<""<<sys.wYear<<" "<<sys.wMonth<<" "<<sys.wDay<<" "<<sys.wHour<<" "<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "<<sys.wDayOfWeek;//调用系统时间
	cin >> outStoptime;
	cout << endl;
	int count, money;
	count = outStoptime - sup.time;
	money = count *price; //计算费用
	cout << "应付费用为：" << money << endl << endl;
	while (sto_sup.top != -1)//辅助栈中元素进入栈中
	{
		sup = sto_sup.pop();
		sto.push(sup);
	}
	sup = await.DelQueue();//队列中第一个元素出队
	cout << "车牌号码：" << sup.num << " " << ",准备进入停车场" << endl << endl;

	cout << "请输入此刻时间：";
	cin >> sup.time; //用此刻输入时间覆盖之前的时间
	sto.push(sup);//出
	int choice;
	cout << endl;
	cout << "是否继续将车辆开出停车场?(1是继续，0是返回)";
	cin >> choice;
	if (choice == 0)
		mainscreen(sto, await);
	else
		if (choice == 1)
			outStop(sto, await);
		else
			exit(1);

}
void carInquire(stop& sto, awaitStop& await)//查询停车场内车辆函数
{
	sto.getout();
	int choice;
	cout << "是否返回主界面(1是退出，0是返回主界面)";
	cin >> choice;
	if (choice == 0)
		mainscreen(sto, await);
	else
		if (choice == 1)
			exit(0);
		else
			exit(1);
}
void shortcutInquire(stop& sto, awaitStop& await)//查询便道中车辆函数
{
	await.output();
	int choice;
	cout << "返回主界面(1是退出，0是返回)";
	cin >> choice;
	if (choice == 0)
		mainscreen(sto, await);//主屏幕
	else
		if (choice == 1)
			exit(0);
		else
			exit(1);
}
void mainscreen(stop& sto, awaitStop& await)//主界面函数
{
	system("cls");
	cout << "\t**********欢迎使用停车场模拟系统**********" << endl;
	cout << "\t******************************************" << endl;
	cout << "\t**         1. 车辆进入                  **" << endl;
	cout << "\t**         2. 车辆开出                  **" << endl;
	cout << "\t**         3. 查看停车场内车辆          **" << endl;
	cout << "\t**         4. 查看便道中车辆            **" << endl;
	cout << "\t**         5. 退出                      **" << endl;
	cout << "\t******************************************" << endl;
	int choice;
	cout << "请输入选择：";
	cin >> choice;
	switch (choice)
	{
	case 1:
		inStop(sto, await);
		break;
	case 2:
		outStop(sto, await);
		break;
	case 3:
		carInquire(sto, await);
		break;
	case 4:
		shortcutInquire(sto, await);
		break;
	case 5:
		exit(0);
	}
}
int main()
{
	stop sto;//栈
	awaitStop c;//队列
	mainscreen(sto, c);
	return 0;
}
