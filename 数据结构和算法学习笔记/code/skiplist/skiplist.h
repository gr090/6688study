#pragma once

#define MAX_LEVEL 32

//原始节点
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
	LevelNode* m_prev;	//前一节点
	LevelNode* m_next;	//后一节点
	LevelNode* m_up;	//向下节点
	LevelNode* m_down;//向下节点
};

//List是双向链表
typedef LevelNode* List;

//跳表
class SkipList {
public:
	SkipList() {}
	~SkipList();
public:
	//初始化跳表,一共 level 级(含0级)
	bool Init(int level, int span);
	int GetMaxLevel() { return m_level; }
	bool Insert(int val);
	bool Delete(int val);
	//找到和 val 相等的0级节点
	LevelNode* FindNode(int val, int& level);
	//找到可以插入 val 的0级节点前驱
	LevelNode* FindInsert(int val, LevelNode* spanNode);

	LevelNode* BuildIndex(LevelNode* spanNode);
	LevelNode* UpdateIndex(LevelNode* spanNode, LevelNode* lNode);
	void Print();
private:
	//查找 val 所在的跨度区间的起点节点
	LevelNode* FindSpan(int val, int& level);
private:
	//跳表多级索引, 0级为原始链表
	List* m_index;
	//索引级数
	int m_level;
	//节点跨度;
	int m_span;
};
