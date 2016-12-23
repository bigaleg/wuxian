#include<iostream>
#include <string>
#include<vector>
#include <stack>

using namespace std;

//先定义一个命令接口

class Command
{
public:
	Command(){}
	virtual ~Command(){}

	virtual void Execute() = 0;
};


class InputCommand : public Command
{
public:

	InputCommand(const string &input)
	{
		mInput = input;
	}
	~InputCommand()
	{}

	void Execute()
	{
		cout << "current string is:" << mInput.c_str() << endl;//输入完成

	}

private:

	string mInput;
};

class Commander
{
public:
	Commander(Command *pCmd)
	{
		//最初的命令数据  
		mUndo.push(pCmd);
	}
	~Commander()
	{
		while (mUndo.empty() == false)
		{
			delete mUndo.top();
			mUndo.pop();
		}
		while (mRedo.empty() == false)
		{
			delete mRedo.top();
			mRedo.pop();
		}
	}

	void ExecuteCommand(Command *pCmd)
	{
		pCmd->Execute();
		mUndo.push(pCmd);
	}

	void Undo()
	{
		if (mUndo.size() < 2)
		{
			//无法后退撤销没有数据  
			cout << "undo failed.\n" << endl;
			return;
		}

		cout << "undo:\n" << endl;

		//当前命令  
		auto pCmd = mUndo.top();

		//保存当前命令  
		mRedo.push(pCmd);

		//弹出  
		mUndo.pop();

		//还原到上个命令  
		pCmd = mUndo.top();

		pCmd->Execute();
	}

	void Redo()
	{
		if (mRedo.empty())
		{
			//无法前进重做没有数据  
			printf("redo failed.\n");
			return;
		}

		printf("redo:\n");

		auto pCmd = mRedo.top();

		pCmd->Execute();

		mRedo.pop();

		mUndo.push(pCmd);
	}

private:
	stack< Command* > mUndo;
	stack< Command* > mRedo;
};
//模拟输入字符串,然后对输入的字符串进行undo redo操作  
int main()
{
	Commander *q = new Commander(new InputCommand("[empty]"));
	int p=0;
	string r;
	int c = 0;
	for (c = 0; c < 50;c++)
	{
		cin >> p;
		if (p == 1)
		{
			q->Undo();
		}
		else if (p == 2)
		{
			q->Redo();
		}
		else if (p == 3)
		{
			cin >> r;
			q->ExecuteCommand(new InputCommand(r));
		}
	
	}
}