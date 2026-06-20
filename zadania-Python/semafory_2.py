import threading
from threading import Semaphore

import time

#POLECENIE: Zmodyfikuj klasę SemaphoresABC, aby cyklicznie wyświetlała powtarzającą się sekwencję liter:  AABCC
#---AABCC---

sA=Semaphore(1)
sB=Semaphore(0)
sC=Semaphore(0)

def wypiszA():
    while True:
        sA.acquire()
        print('A',end="")
        print('A', end="")
        sB.release()
        time.sleep(1)

def wypiszB():
    while True:
        sB.acquire()
        print('B',end="")
        sC.release()

def wypiszC():
    while True:
        sC.acquire()
        print('C',end="")
        print('C ', end="")
        sA.release()

wątekA=threading.Thread(target=wypiszA)
wątekB=threading.Thread(target=wypiszB)
wątekC=threading.Thread(target=wypiszC)

wątekA.start()
wątekB.start()
wątekC.start()
