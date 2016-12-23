#include <iostream>  
#include <string>  
#include <vector>  
#include <list>  
using namespace std;

class Observer
{

public:
	Observer(){}
	virtual ~Observer(){}
	virtual void Update(){};
};

class QQzone
{
public:
	QQzone(){}
	virtual ~QQzone(){}

	void ADD(Observer* observer)
	{
		vec_observer.push_back(observer);
	}

	void DEL(Observer* observer)
	{
		vector<Observer*>::iterator iter;
		for (iter = vec_observer.begin(); iter != vec_observer.end(); ++iter)
		{
			if ((*iter) == observer)
				vec_observer.erase(iter);
		}
	}

	void Notify()
	{
		vector<Observer*>::iterator iter;
		for (iter = vec_observer.begin(); iter != vec_observer.end(); ++iter)
		{
			(*iter)->Update();
		}
	}

	virtual void SetStatus(string sts){}
	virtual string GetStatus() { return m_status; };

private:
	vector<Observer*> vec_observer;
protected:
	string m_status;
};

class ConcreteQQzone :public QQzone
{
public:
	ConcreteQQzone(string name) :m_QQzone_name(name){}
	~ConcreteQQzone(){}


	void SetStatus(string sts)
	{
		m_status = "Notify£º " + m_QQzone_name + sts;
	}

	string GetStatus()
	{
		return m_status;
	}

private:
	string m_QQzone_name;
};

class ConcreteObserver :public Observer
{
private:
	string m_observer_name;
	QQzone *m_QQzone;
public:
	ConcreteObserver(string name, QQzone* blog) :m_observer_name(name), m_QQzone(blog){}
	~ConcreteObserver(){}

	void Update()
	{
		string status = m_QQzone->GetStatus();
		cout << m_observer_name << "-----------" << status << endl;
	}
};

int main()
{
	QQzone *message = new ConcreteQQzone("Alice");
	Observer *ob1 = new ConcreteObserver("LiLi", message);
	Observer *ob2 = new ConcreteObserver("Simon", message);
	Observer*ob3 = new ConcreteObserver("David", message);
	message->ADD(ob1);
	message->ADD(ob2);
	message->ADD(ob3);
	message->SetStatus(" have published a new message!");
	message->Notify();

	delete message;
	delete ob1;
	delete ob2;
	delete ob3;
	system("pause");
	return 0;
}