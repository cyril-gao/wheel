from typing import List


'''
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:
Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
'''

def read_binary_watch(num: int) -> List[str]:
    def build_time_string(buf: List[bool]):
        hour = 0
        v = 1
        for i in range(4):
            if buf[i]:
                hour += v
            v <<= 1
        minute = 0
        v = 1
        for i in range(4, 10):
            if buf[i]:
                minute += v
            v <<= 1
        return [hour < 12 and minute < 60, "%d:%02d" % (hour, minute)]

    def next(
        num: int,
        start: int,
        buf: List[bool],
        result: List[str]
    ):
        if num > 0:
            for i in range(start, 11-num):
                buf[i] = True
                next(num-1, i+1, buf, result)
                buf[i] = False
        else:
            r = build_time_string(buf)
            if r[0]:
                result.append(r[1])
        
    if num < 10:
        retval = []
        buf = [False for _ in range(10)]
        next(num, 0, buf, retval)
        return retval
    else:
        return ["11:59"]
