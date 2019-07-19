#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#program  用sorted()对上述列表分别按名字排序  

def by_name(t):
    return t[0].upper()

# 测试
L = [('Bob', 75), ('Adam', 92), ('Bart', 66), ('Lisa', 88)]
L2 = sorted(L, key=by_name)
print(L2)
