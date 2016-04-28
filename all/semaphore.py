# -*- coding: utf-8 -*-

import threading  
import time
import random

south_bridge = -1
north_bridge = -1
middle1 = -1
middle2 = -1

def update_middle(i):
    global south_bridge,north_bridge,middle1,middle2
    if middle1 == -1:
        middle1 = i
    elif middle2 == -1:
        middle2 = i

def remove_middle(i):
    global south_bridge,north_bridge,middle1,middle2
    if middle1 == i:
        middle1 = -1
    elif middle2 == i:
        middle2 = -1

class Person(threading.Thread):  
    
    def __init__(self,going,idnumber,load,north,south,output,res):
        threading.Thread.__init__(self)
        self.going = going
        self.idno = idnumber
        self.load  = load
        self.north = north
        self.south = south
        self.output = output
        self.res = res
        going_str = ""
        if self.going == 1:
            going_str = " is going north:"
        else:
            going_str = " is going south:"
        print str(self.idno) + going_str
        
    def go_south(self):
        global south_bridge,north_bridge,middle1,middle2
        
        self.load.acquire()
        self.north.acquire()

        #self.printout("过北段桥")
        self.res.acquire()
        north_bridge = self.idno
        self.res.release()
        self.print_bridge()

        #self.printout("到桥中间")
        self.res.acquire()
        north_bridge = -1
        update_middle(self.idno)
        self.res.release()
        self.print_bridge()

        self.north.release()
        self.south.acquire()

        #self.printout("过南段桥")
        self.res.acquire()
        remove_middle(self.idno)
        south_bridge = self.idno
        self.res.release()
        self.print_bridge()
        self.res.acquire()
        south_bridge = self.idno
        self.res.release()

        #self.printout("到达南岸")
        self.south.release()
        self.load.release()

    def go_north(self):
        global south_bridge,north_bridge,middle1,middle2
        
        self.load.acquire()
        self.south.acquire()

        #self.printout("过南段桥")
        self.res.acquire()
        south_bridge = self.idno
        self.res.release()
        self.print_bridge()

        #self.printout("到桥中间")
        self.res.acquire()
        south_bridge = -1
        update_middle(self.idno)
        self.res.release()
        self.print_bridge()

        self.south.release()
        self.north.acquire()

        #self.printout("过北段桥")
        self.res.acquire()
        remove_middle(self.idno)
        north_bridge = self.idno
        self.res.release()
        self.print_bridge()
        self.res.acquire()
        north_bridge = self.idno
        self.res.release()

        #self.printout("到达北岸")
        self.north.release()
        self.load.release()
    def run(self):
        if self.going == 1:
            self.go_north()
        else:
            self.go_south()

    def printout(self,s):
        output.acquire()
        print str(self.idno) + ":" + s
        output.release()

    def print_bridge(self):
        global south_bridge,north_bridge,middle1,middle2
        self.res.acquire()
        output.acquire()
        
        print "(" + str(north_bridge) + ") (" + str(middle1)+"," + str(middle2) + ") (" + str(south_bridge) + ")" 
        output.release()
        self.res.release()
      
if __name__ == "__main__":
    output = threading.Semaphore(1)
    load =  threading.Semaphore(2)
    south = threading.Semaphore(1)
    north = threading.Semaphore(1)
    res = threading.Semaphore(1)
    
for i in range(0, 10):
    r = random.randint(0,1)
    my_thread = Person(r,i,load,north,south,output,res)
    my_thread.start()
