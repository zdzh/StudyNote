#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#program   将用户输入单词改为首字母大写，其他小写

def low(gra):
    return gra.lower()

def normalword(word):
    if not isinstance(word,str):
         raise TypeError('bad operand type')
    word = list(map(low, word))
    word[0] =  word[0].upper()
    return word


# 测试:
L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalword, L1))
print(L2)