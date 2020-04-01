import os
import time
import _thread
import serial
from tkinter import Tk

tk=Tk()
tk.withdraw()
x1=160
x2=195
y1=290
y2=410
height=y2-y1
width=x2-x1

def keep_connection():
    os.system("sudo sh keep_connection.sh")
    print('ok')

_thread.start_new_thread(keep_connection,())
time.sleep(2.5)
ser = serial.Serial('/dev/rfcomm6',9600)
os.system("adb connect 192.168.1.40:5555")
time.sleep(2.5)

def get_distance():
    while ser.inWaiting()<=0:
        pass
    return int(ser.read(ser.inWaiting()))

def get_position():
    text=tk.clipboard_get()
    if text!='none':
        texts=text.split()
    else:
        texts=['-1','-1']
    return (int(texts[0]),int(texts[1]))

def tap(x,y):
    os.system("adb shell input tap "+str(x)+' '+str(y))

def swipe(x_,y_,x,y):
    os.system("adb shell input swipe "+str(x_)+' '+str(y_)+' '+str(x)+' '+str(y))

def keyevent(key):
    if key==0: #HOME
        os.system("adb shell input keyevent 3")
    else: #BACK
        os.system("adb shell input keyevent 4")

def isInArea():
    position=get_position()
    if position[0] > x1 and position[0] < x2 and position[1] > y1 and position[1] < y2 :
        return True
    else:
        return False

def convert(x,y):
    return ((x-x1)/width*1080,(y-y1)/height*1920)

while 1:
    global state #0:点击 1：滑动
    state=0
    if isInArea():
        if get_distance()<30:
            start_position=get_position()
            start_time=time.time()
            while get_distance()<30:
                if time.time()-start_time > 2:
                    state=1
            if state==1:
                end_position=get_position()
                swipe(convert(start_position),convert(end_position))
            else:
                tap(convert(start_position))