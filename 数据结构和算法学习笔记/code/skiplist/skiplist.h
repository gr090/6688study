#pragma once

#define MAX_LEVEL 32

//ԭʼ�ڵ�
struct Node {
public:
	Node(int val):m_val(val) {}
	~Node() {}
public:
	int m_val;
};

struct LevelNode
{
public:
	LevelNode(Node* node) :m_real(node),
		m_prev(nullptr),
		m_next(nullptr),
		m_up(nullptr),
		m_down(nullptr) {}
	~LevelNode() {}
public:
	Node* m_real;
	LevelNode* m_prev;	//ǰһ�ڵ�
	LevelNode* m_next;	//��һ�ڵ�
	LevelNode* m_up;	//���½ڵ�
	LevelNode* m_down;//���½ڵ�
};

//List��˫������
typedef LevelNode* List;

//����
class SkipList {
public:
	SkipList() {}
	~SkipList();
public:
	//��ʼ������,һ�� level ��(��0��)
	bool Init(int level, int span);
	int GetMaxLevel() { return m_level; }
	bool Insert(int val);
	bool Delete(int val);
	//�ҵ��� val ��ȵ�0���ڵ�
	LevelNode* FindNode(int val, int& level);
	//�ҵ����Բ��� val ��0���ڵ�ǰ��
	LevelNode* FindInsert(int val, LevelNode* spanNode);

	LevelNode* BuildIndex(LevelNode* spanNode);
	LevelNode* UpdateIndex(LevelNode* spanNode, LevelNode* lNode);
	void Print();
private:
	//���� val ���ڵĿ����������ڵ�
	LevelNode* FindSpan(int val, int& level);
private:
	//����༶����, 0��Ϊԭʼ����
	List* m_index;
	//��������
	int m_level;
	//�ڵ���;
	int m_span;
};
