import numpy as np
import cv2
from tkinter import Tk

tk=Tk()
tk.withdraw()
cap = cv2.VideoCapture(0)
ret = cap.set(3, 640)
ret = cap.set(4, 480)
font = cv2.FONT_HERSHEY_SIMPLEX
kernel = np.ones((5, 5), np.uint8)
text=""
 
def start():
    if cap.isOpened() is True:
        while(True):
            ret, frame = cap.read()
            frame = cv2.flip(frame,-180)
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

            lower_green = np.array([35, 50, 100])
            upper_green = np.array([77, 255, 255])

            mask = cv2.inRange(hsv, lower_green, upper_green)
            opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
            bila = cv2.bilateralFilter(mask, 10, 200, 200)
            edges = cv2.Canny(opening, 50, 100)

            circles = cv2.HoughCircles(
                edges, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=10, minRadius=10, maxRadius=500)
            if circles is not None:
                for circle in circles[0]:

                    x = int(circle[0])
                    y = int(circle[1])
                    r = int(circle[2])
                    cv2.circle(frame, (x, y), r, (0, 0, 255), 3)
                    cv2.circle(frame, (x, y), 3, (255, 255, 0), -1)
                    tk.clipboard_clear()
                    tk.clipboard_append(str(x)+' '+str(y))
                    tk.update()
                    #cv2.putText(frame, text, (10, 30), font, 1, (0, 255, 0), 2, cv2.LINE_AA, 0)  # 显示圆心位置
            else:
                tk.clipboard_clear()
                tk.clipboard_append("none")
                tk.update()
                #cv2.putText(frame, 'x: None y: None', (10, 30), font, 1, (0, 255, 0), 2, cv2.LINE_AA, 0)
            #cv2.imshow('frame', frame)
            #cv2.imshow('mask', mask)
            #cv2.imshow('edges', edges)
            #print(result)
            #k = cv2.waitKey(5) & 0xFF
            #if k == 27:
                #break
        cap.release()
        cv2.destroyAllWindows()
    else:
        print('cap is not opened!')

start()