import threading
from threading import Semaphore #Semaphore musi byc z duzej litery
import time

#POLECENIE:
#Wartość sumy:
#21
#56

p=21
d=56
s=p+d

a=Semaphore(1)
b=Semaphore(0)
c=Semaphore(0)

def printp():
    while True:
        a.acquire()
        print("\t",p,"+ ",end="")
        b.release()
        time.sleep(1)

def printd():
    while True:
        b.acquire()
        print(d,"= ",end="")
        c.release()

def prints():
    while True:
        c.acquire()
        print(s,end="")
        a.release()


wątekA=threading.Thread(target=printp)
wątekB=threading.Thread(target=printd)
wątekC=threading.Thread(target=prints)

wątekA.start()
wątekB.start()
wątekC.start()
