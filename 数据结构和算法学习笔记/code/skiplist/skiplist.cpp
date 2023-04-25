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
	//�ҵ���ʼ��Ƚڵ�
	LevelNode* spanNode = FindSpan(val, level); //��Ȼ����ײ㼶��
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

	//�������ϸ��²㼶����
	LevelNode* newUp = nullptr;
	while (spanNode) {
		newUp = BuildIndex(spanNode);
		if (!newUp) break;

		//�����½���һ�� spanNode ���ϲ�ڵ�, ��Ҫ�ҵ� spanNode �ĵ�ǰ�㼶����ʼ��Ƚڵ�, ���ж��Ƿ��������һ���ٽ��ڵ�
		while (newUp && !newUp->m_up) {
			newUp = newUp->m_prev;
		}
		spanNode = newUp;
	}
	return true;
}

//���㽻��ڵ���浽��һ������ڵ�(����)�Ľڵ����
//��ԭʼ����һ�����֮��(������ڵ�֮��)�Ľڵ���� tailNum >= 2*span, ���ҵ�������λ���ڵ㲢��������Ϊ�µĽ���ڵ�
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
	//�Ѿ������Ƚڵ���
	return UpdateIndex(spanNode, slow);
}

//���µ��ϸ�������
LevelNode* SkipList::UpdateIndex(LevelNode* spanNode, LevelNode* newSpan) {
	LevelNode* up = spanNode->m_up;
	LevelNode* newUp = new LevelNode(newSpan->m_real);
	//ǰ��ڵ�����
	if (up->m_next) {
		up->m_next->m_prev = newUp;
		newUp->m_next = up->m_next;
	}
	up->m_next = newUp;
	newUp->m_prev = up;

	//���½ڵ�����
	newUp->m_down = newSpan;
	newSpan->m_up = newUp;
	return newUp;
}

bool SkipList::Delete(int val) {
	int level = m_level - 1;
	LevelNode* node = FindNode(val, level);
	if (!node) return false;

	//ֱ����0������
	while (node->m_down) {
		node = node->m_down;
	}
	//ɾ��0��ԭʼ����� m_real �ڵ�
	delete node->m_real;
	node->m_real = nullptr;
	//����ǽ���ڵ�(����upָ�벻Ϊ��,��Ϊ��0������ڵ�),����Ҫ��������صĲ㼶�������Ƴ�
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

//���ϲ㵽�²����
LevelNode* SkipList::FindSpan(int val, int& level) {
	if (level < 0 || level >= m_level)
		return nullptr;
	
	LevelNode* lNode = nullptr;
	LevelNode* spanNode = nullptr;
	while (level >= 0) {
		int sLevel = level;
		lNode = (LevelNode*)m_index[level];
		if (lNode->m_down || lNode->m_up) { //��¼��ȿ�ʼ�ڵ�
			spanNode = lNode;
		}

		while (lNode && lNode->m_next) {
			//��ǰ�㼶�ĸ����ڵ�Ƚ�,ֱ�� val �ҵ���ǰ�㼶�Ĳ���λ��
			if (val >= lNode->m_next->m_real->m_val) {
				lNode = lNode->m_next;
				if (lNode->m_down || lNode->m_up) { //�ڵ����, ����ǿ�ȿ�ʼ�ڵ�, ��¼����
					spanNode = lNode;
				}
			} 
			else {
				//�³����¸��㼶����
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
		if (level != sLevel) { //��ĳ�� level �����ҵ����ϵĿ��
			break;
		}
		else {
			level--;
		}
	}

	//�³���0��,��ԭʼ����
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
				//�³����¸��㼶����
				if (lNode->m_down) {
					level--;
					lNode = lNode->m_down;
				}
				else {
					break;
				}
			}
		}
		if (level != sLevel) { //��ĳ�� level �����ҵ����ϵĿ��
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