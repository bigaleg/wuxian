#include<iostream>
#include <string>
#include<vector>
#include <stack>

using namespace std;

//�ȶ���һ������ӿ�

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
		cout << "current string is:" << mInput.c_str() << endl;//�������

	}

private:

	string mInput;
};

class Commander
{
public:
	Commander(Command *pCmd)
	{
		//�������������  
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
			//�޷����˳���û������  
			cout << "undo failed.\n" << endl;
			return;
		}

		cout << "undo:\n" << endl;

		//��ǰ����  
		auto pCmd = mUndo.top();

		//���浱ǰ����  
		mRedo.push(pCmd);

		//����  
		mUndo.pop();

		//��ԭ���ϸ�����  
		pCmd = mUndo.top();

		pCmd->Execute();
	}

	void Redo()
	{
		if (mRedo.empty())
		{
			//�޷�ǰ������û������  
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
//ģ�������ַ���,Ȼ���������ַ�������undo redo����  
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