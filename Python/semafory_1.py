import threading
from threading import Semaphore
import time #wprowadza czas

semA=Semaphore(1)
semB=Semaphore(0)
semC=Semaphore(0)

#semA.acquire()
#semB.release()


#POLECENIE: Zmodyfikuj klasę SemaphoresABC, aby cyklicznie wyświetlała powtarzającą się sekwencję liter: ABAC

def printA():
    while (True):
        semA.acquire()
        print('A', end="")
        semB.release()
        semA.acquire()  # <--- Czekaj na sygnał od B
        print('A(2)', end="")
        semC.release()
        time.sleep(1) #czeka 1 sekunde pomiedzy nastepnymi wykonaniami sekwencji


def printB():
    while (True):
        semB.acquire()
        print('B', end="")
        semA.release()


def printC():
    while (True):
        semC.acquire()
        print('C ', end="")
        semA.release()


# Utworzenie wątków
thread_A = threading.Thread(target=printA)
thread_B = threading.Thread(target=printB)
thread_C = threading.Thread(target=printC)

# Uruchomienie wątków
thread_A.start()
thread_B.start()
thread_C.start()