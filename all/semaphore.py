# -*- coding: utf-8 -*-

import threading  
import time   

south_bridge = -1
north_bridge = -1
middle1 = -1
middle2 = -1

class Person(threading.Thread):  

    def __init__(self,idnumber,load,north,south,output):
        threading.Thread.__init__(self)
        self.idno = idnumber
        self.load  = load
        self.north = north
        self.south = south
        self.output = output
        
    def go_south(self):
        self.load.acquire()
        self.north.acquire()
        self.printout("过北段桥")
        self.printout("到桥中间")
        self.north.release()
        self.south.acquire()
        self.printout("过南段桥")
        self.printout("到达南岸")
        self.south.release()
        self.load.release()

    def go_north(self):
        self.load.acquire()
        self.south.acquire()
        self.printout("过南段桥")
        self.printout("到桥中间")
        self.south.release()
        self.north.acquire()
        self.printout("过北段桥")
        self.printout("到达北岸")
        self.north.release()
        self.load.release()
    def run(self):
        self.go_north()

    def printout(self,s):
        output.acquire()
        print str(self.idno) + ":" + s
        output.release()
      
if __name__ == "__main__":
    output = threading.Semaphore(1)
    load =  threading.Semaphore(2)
    south = threading.Semaphore(1)
    north = threading.Semaphore(1)
    
for i in range(0, 10):
    my_thread = Person(i,load,north,south,output)
    my_thread.start()
