#include<iostream>
#include "skiplist.h"

SkipList::~SkipList() {

}

bool SkipList::Init(int level, int span) {
	if (level <= 0 || level >= MAX_LEVEL)
		level = MAX_LEVEL;
	if (span <= 0)
		span = 2;

	m_level = level;
	m_span = span;

	m_index = new List[ sizeof(List*) * m_level ];
	Node* header = new Node(0);
	LevelNode* up = nullptr;
	for (level = 0; level < m_level; level++) {
		m_index[level] = new LevelNode(header);

		if (level > 0) {
			m_index[level]->m_down = m_index[level - 1];
			m_index[level - 1]->m_up = m_index[level];
		}
	}
	return true;
}

bool SkipList::Insert(int val) {
	int level = m_level - 1;
	//找到起始跨度节点
	LevelNode* spanNode = FindSpan(val, level); //必然是最底层级的
	if (!spanNode) return false;
	LevelNode* preNode = FindInsert(val, spanNode);
	Node* newReal = new Node(val);
	if (!newReal) return false;
	LevelNode* newNode = new LevelNode(newReal);
	if (!newNode) return false;
	
	if (preNode->m_next) {
		newNode->m_next = preNode->m_next;
		preNode->m_next->m_prev = newNode;
	}
	newNode->m_prev = preNode;
	preNode->m_next = newNode;

	//从下往上更新层级索引
	LevelNode* newUp = nullptr;
	while (spanNode) {
		newUp = BuildIndex(spanNode);
		if (!newUp) break;

		//由于新建了一个 spanNode 的上层节点, 需要找到 spanNode 的当前层级的起始跨度节点, 再判断是否可以在上一层再建节点
		while (newUp && !newUp->m_up) {
			newUp = newUp->m_prev;
		}
		spanNode = newUp;
	}
	return true;
}

//计算交叉节点后面到下一个交叉节点(包含)的节点个数
//当原始链的一个跨度之间(两交叉节点之间)的节点个数 tailNum >= 2*span, 则找到他们中位数节点并将它设置为新的交叉节点
LevelNode* SkipList::BuildIndex(LevelNode* spanNode) {
	int tailNum = 0;
	LevelNode* slow = nullptr;
	LevelNode* fast = spanNode;
	do {
		fast = fast->m_next;
		if (slow) {
			slow = slow->m_next;
			tailNum++;
		}
		else {
			tailNum++;
			if (tailNum >= m_span) {
				slow = spanNode;
			} 
		}
	} while (fast && !fast->m_up);
	
	if (!slow || slow == spanNode) return nullptr;

	if (!(tailNum % m_span == 0 || tailNum >= 2 * m_span)) {
		return nullptr;
	}
	//已经过半跨度节点了
	return UpdateIndex(spanNode, slow);
}

//从下到上更新索引
LevelNode* SkipList::UpdateIndex(LevelNode* spanNode, LevelNode* newSpan) {
	LevelNode* up = spanNode->m_up;
	LevelNode* newUp = new LevelNode(newSpan->m_real);
	//前后节点链接
	if (up->m_next) {
		up->m_next->m_prev = newUp;
		newUp->m_next = up->m_next;
	}
	up->m_next = newUp;
	newUp->m_prev = up;

	//上下节点链接
	newUp->m_down = newSpan;
	newSpan->m_up = newUp;
	return newUp;
}

bool SkipList::Delete(int val) {
	int level = m_level - 1;
	LevelNode* node = FindNode(val, level);
	if (!node) return false;

	//直至到0级链表
	while (node->m_down) {
		node = node->m_down;
	}
	//删除0级原始链表的 m_real 节点
	delete node->m_real;
	node->m_real = nullptr;
	//如果是交叉节点(它的up指针不为空,因为是0级链表节点),则需要把它从相关的层级链表里移除
	LevelNode* up = node;
	while (up) {
		up->m_real = nullptr;
		if (up->m_next) {
			up->m_next->m_prev = up->m_prev;
			up->m_prev->m_next = up->m_next;
		}
		else {
			up->m_prev->m_next = nullptr;
		}
		node = up;
		up = node->m_up;
		delete node;
		node = nullptr;
	}

	return true;
}

//从上层到下层查找
LevelNode* SkipList::FindSpan(int val, int& level) {
	if (level < 0 || level >= m_level)
		return nullptr;
	
	LevelNode* lNode = nullptr;
	LevelNode* spanNode = nullptr;
	while (level >= 0) {
		int sLevel = level;
		lNode = (LevelNode*)m_index[level];
		if (lNode->m_down || lNode->m_up) { //记录跨度开始节点
			spanNode = lNode;
		}

		while (lNode && lNode->m_next) {
			//当前层级的各个节点比较,直到 val 找到当前层级的插入位置
			if (val >= lNode->m_next->m_real->m_val) {
				lNode = lNode->m_next;
				if (lNode->m_down || lNode->m_up) { //节点更换, 如果是跨度开始节点, 记录下来
					spanNode = lNode;
				}
			} 
			else {
				//下沉到下个层级索引
				if (spanNode->m_down) {
					level--;
					spanNode = spanNode->m_down;
					lNode = spanNode;
					continue;
				}
				else {
					break;
				}
			}
		}
		if (level != sLevel) { //在某个 level 层有找到符合的跨度
			break;
		}
		else {
			level--;
		}
	}

	//下沉到0级,即原始链表
	while (spanNode && spanNode->m_down) {
		spanNode = spanNode->m_down;
	}
	return spanNode;
}

LevelNode* SkipList::FindNode(int val, int& level) {
	LevelNode* lNode = nullptr;
	while (level >= 0) {
		int sLevel = level;
		lNode = (LevelNode*)m_index[level];
		while (lNode && lNode->m_next) {
			if (lNode->m_real->m_val == val) {
				return lNode;
			}
			else if(lNode->m_next->m_real->m_val == val) {
				return lNode->m_next;
			}
			
			if (val > lNode->m_next->m_real->m_val) {
				lNode = lNode->m_next;
			}
			else {
				//下沉到下个层级索引
				if (lNode->m_down) {
					level--;
					lNode = lNode->m_down;
				}
				else {
					break;
				}
			}
		}
		if (level != sLevel) { //在某个 level 层有找到符合的跨度
			break;
		}
		else {
			level--;
		}
	}
	while (lNode) {
		if (lNode->m_real->m_val == val)
			return lNode;
		else
			lNode = lNode->m_next;
	}
	return nullptr;
}

LevelNode* SkipList::FindInsert(int val, LevelNode* spanNode) {
	while (spanNode->m_next) {
		if (val >= spanNode->m_next->m_real->m_val) {
			spanNode = spanNode->m_next;
		}
		else {
			break;
		}
	}
	return spanNode;
}

void SkipList::Print() {
	std::cout << "===========\n";
	for (int level = m_level-1; level >= 0; level--) {
		std::cout << "level:" << level << "--";
		LevelNode* node = m_index[level];
		while (node) {
			std::cout << node->m_real->m_val << " ";
			node = node->m_next;
		}
		std::cout << std::endl;
	}
}