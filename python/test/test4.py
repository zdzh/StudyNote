#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#program  筛选出列表中的回数   

# def is_palindrome(n):
#     s = str(n)
#     for i in range(0,len(s)//2):
#         if s[i] != s[-i-1]:           # 倒数索引从-1开始
#             return False
#     return True

def is_palindrome(n):
    return n == int(str(n)[::-1])


# 测试:
output = filter(is_palindrome, range(1, 1000))
print('1~1000:', list(output))
if list(filter(is_palindrome, range(1, 200))) == [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99, 101, 111, 121, 131, 141, 151, 161, 171, 181, 191]:
    print('测试成功!')
else:
    print('测试失败!')

