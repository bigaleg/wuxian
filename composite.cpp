#include <iostream>
#include <list>
#include <algorithm>

using namespace std;


// Component������࣬Ϊ����еĶ��������ӿ�,�������๲�нӿڵ�ȱʡ��Ϊ(�������Add,Remove,GetChild����),

class Componet
{
public:
	Componet()
	{
	}
	virtual ~Componet()
	{
	}
	// �麯��,�ṩ�ӿ�

	virtual void Operation() = 0;
	virtual void Add(Componet *PChild)

	{
	}
	virtual void Remove(Componet *PChild)

	{
	}
	virtual Componet* GetChild(int index)
	{
		return NULL;
	}

};

//Ҷ�ӽڵ�
class Leaf :public Componet
{
public:
	Leaf()
	{
	}
	virtual ~Leaf()
	{}

	virtual void Operation()
	{
		cout << "leaf is completed" << endl;
	}
};

//composite

class Composite :public Componet
{
public:
	Composite()
	{
	}

	virtual ~Composite()
	{
		list<Componet*>::iterator it1, t;
		for (it1 = m_ListOfComponet.begin(); it1 != m_ListOfComponet.end();)
		{
			t = it1;
			it1++;
			delete(*t);
		}

	}

	virtual void Operation()
	{
		cout << "composite is completed" << endl;
		list<Componet*>::iterator it1;
		for (it1 = m_ListOfComponet.begin(); it1 != m_ListOfComponet.end(); it1++)
		{
			(*it1)->Operation();
		}

	}
	virtual void Add(Componet *PChild)
	{
		m_ListOfComponet.push_back(PChild);
	}
	virtual void Remove(Componet *pChild)
	{
		list<Componet*>::iterator iter;
		iter = find(m_ListOfComponet.begin(), m_ListOfComponet.end(), pChild);
		if (m_ListOfComponet.end() != iter)
		{
			m_ListOfComponet.erase(iter);
		}
		else
			cout << "warning" << endl;
	}

	virtual Componet* GetChild(int index)
	{
		if (index <= 0 || index> m_ListOfComponet.size())
			return NULL;

		list<Componet*>::iterator iter1, iter2;
		int i;
		for (i = 1, iter1 = m_ListOfComponet.begin(), iter2 = m_ListOfComponet.end(); iter1 != iter2; ++iter1, ++i)
		{
			if (i == index)
				break;
		}
		cout << "success" << endl;
		return *iter1;
	}

private:
	list<Componet*> m_ListOfComponet;

};
int main()
{

	
	Composite* pComposite = new Composite();

	Leaf *pLeaf1 = new Leaf();
	Leaf *pLeaf2 = new Leaf();
	Leaf *pLeaf3 = new Leaf();
	
	pComposite->Add(pLeaf1);
	pComposite->Add(pLeaf2);


	pComposite->Operation();
	pComposite->Remove(pLeaf3);//���������û��pleaf3�����Ի���ʾwarning
	pComposite->GetChild(2)->Operation();

	delete pComposite;
	system("PAUSE");
	return 0;
}