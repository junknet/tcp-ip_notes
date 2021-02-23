from os import popen
from multiprocess import pool

import time


def test(i):
    print(i)
    time.sleep(1)


if __name__ == "__main__":
    lists = [i for i in range(1, 100)]
    pool = pool.Pool(processes=100)  # 最大任务数
    pool.map(test, lists)    # 参数是迭代类型
    pool.close()  # 关闭池子开始运行
    pool.join()  # 阻塞当前线程，直到返回
