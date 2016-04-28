# -*- coding: utf-8 -*-

import threading  
import time   
   
class Person(threading.Thread):  

    def __init__(self,load,north,south,output):
        threading.Thread.__init__(self)  
        self.load  = load
        self.north = north
        self.south = south
        self.output = output
        
    def go_south(self):
        load.acquire()
        north.acquire()
        self.printout("过北段桥")
        self.printout("到桥中间")
        north.release()
        south.acquire()
        self.printout("过南段桥")
        self.printout("到达南岸")
        south.release()
        load.release()

    def go_north(self):
        load.acquire()
        south.acquire()
        self.printout("过南段桥")
        self.printout("到桥中间")
        south.release()
        
        north.acquire()
        self.printout("过北段桥")
        self.printout("到达北岸")
        south.release()
        load.release()
    def run(self):
        self.go_north()

    def printout(self,s):
        output.acquire()
        print s
        output.release()
      
if __name__ == "__main__":
    output = threading.Semaphore(1)
    load =  threading.Semaphore(2)
    south = threading.Semaphore(1)
    north = threading.Semaphore(1)
    
for i in range(0, 2):
    my_thread = Person(load,north,south,output)
    my_thread.start()
