from queue import Queue
from threading import Thread


def echo_client(q):
    print(q)


def echo_server(nworker):
    q = Queue()
    for n in range(nworker):
        t = Thread(target=echo_client, args=(q,))  # 参数是元组类型
        t.daemon = True  # 守护进程，默认适合False，从main中继承，否则报错 RuntimeError
        t.start()


echo_server(128)
