# -*- coding: utf-8 -*-
__author__ = 'xiaoxiaoming'

import random


class SkipListNode(object):
    def __init__(self, val, max_level=1):
        self.data = val  # �ڵ�洢��ֵ
        self.forwards = [None] * max_level  # �ڵ��Ӧ����������


class SkipList(object):
    """
        �����һ��ʵ�ַ�����
        �����д�����ǲ��ظ�����������
    """

    def __init__(self):
        self.__MAX_LEVEL = 16  # �������������
        self.SKIPLIST_P = 0.5  # �������ɲ������������
        self._level_count = 1  # ��������
        self._head = SkipListNode(None, self.__MAX_LEVEL)  # ��ͷ����

    def find(self, val):
        p = self._head
        # �������Ķ���, ��㶨λҪ���ҵ�ֵ
        # �����������Ƕ�Ӧ��, �²���������һ����������С�ڲ���ֵ�����ֵ��Ӧ�Ľڵ�
        for i in range(self._level_count - 1, -1, -1):
            # ͬһ��������, ����С�ڲ���ֵ�����ֵ��Ӧ�Ľڵ�
            while p.forwards[i] and p.forwards[i].data < val:
                p = p.forwards[i]
        if p.forwards[0] and p.forwards[0].data == val:
            return p.forwards[0]
        return None

    def insert(self, val):
        '''
        ����ʱ, ͨ�����������ȡҪ���µ���������,
        Ҫ�Ե��ڸ����߶ȵ�����������½���ָ��
        '''
        level = self.random_level()
        # ����������������
        if self._level_count < level: self._level_count = level
        new_node = SkipListNode(val, level)  # �����½��
        # cache���������Ӧ��������С�ڲ���ֵ�����ڵ�
        cache = [None] * level
        # �ڵ�������߶ȵ�ÿһ��������Ѱ��С�ڲ���ֵ�Ľڵ�
        p = self._head
        # ����ÿһ�������㶨λС�ڲ���ֵ�Ľڵ�
        for i in range(level - 1, -1, -1):
            while p.forwards[i] and p.forwards[i].data < val:
                p = p.forwards[i]
            cache[i] = p
        # ��С�ڸ߶ȵ�ÿ���������в����½��
        for i in range(level):
            new_node.forwards[i] = cache[i].forwards[i]
            cache[i].forwards[i] = new_node

    def delete(self, val):
        '''
        ɾ��ʱ, Ҫ��ÿ���������ж�Ӧ�Ľڵ㶼ɾ��
        '''
        # cache���������Ӧ��������С�ڲ���ֵ�����ڵ�
        cache = [None] * self._level_count
        p = self._head
        # ����ÿһ�������㶨λС�ڲ���ֵ�Ľڵ�
        for i in range(self._level_count - 1, -1, -1):
            while p.forwards[i] and p.forwards[i].data < val:
                p = p.forwards[i]
            cache[i] = p
        # ���������ֵ����, �����������ж�Ӧ�Ľڵ�
        if p.forwards[0] and p.forwards[0].data == val:
            for i in range(self._level_count):
                if cache[i].forwards[i] and cache[i].forwards[i].data == val:
                    cache[i].forwards[i] = cache[i].forwards[i].forwards[i]
        # ������������
        while self._level_count > 1 and self._head.forwards[self._level_count] == None:
            self._level_count -= 1

    def random_level(self):
        """
        һ��������Ԫ�ظ���Ӧ��ռԭʼ���ݵ� SKIPLIST_P,����������Ԫ�ظ���ռSKIPLIST_P^2,��������SKIPLIST_P^3,һֱ����㡣
        ÿһ��Ľ��������� SKIPLIST_P������ÿһ���²���Ľڵ㣬����Ҫ���� randomLevel ����һ������Ĳ�����
        �� randomLevel ������������� 1~MAX_LEVEL ֮�����
        :return: �����ʷ��� 1-MAX_LEVEL�е�һ��ֵ
        """
        level = 1
        while random.random() < self.SKIPLIST_P and level < self.__MAX_LEVEL:
            level += 1
        return level

    def __repr__(self):
        vals = []
        p = self._head
        while p.forwards[0]:
            vals.append(str(p.forwards[0].data))
            p = p.forwards[0]
        return '->'.join(vals)

    def print_all(self):
        for i in range(self._level_count - 1, -1, -1):
            p = self._head
            print("level:", i)
            while p.forwards[i]:
                print(str(p.forwards[i].data), end="->")
                p = p.forwards[i]
            print()


if __name__ == '__main__':
    sl = SkipList()
    for i in range(100):
        sl.insert(i)
        if i % 10 == 5:
            sl.print_all()
    sl.print_all()
    p = sl.find(7)
    print(p.data)
    sl.delete(37)
    print(sl)
    sl.delete(37.5)
    print(sl)
