import cv2
import numpy as np
import imutils
import serial
import time
import datetime
ser = serial.Serial('/dev/ttyUSB0', 9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)
colors = [
    ("Yellow", np.array([25, 70, 125]), np.array([35, 255, 255]), (0, 255, 255)),
    ("Green", np.array([65, 60, 60]), np.array([80, 255, 255]), (0, 255, 0)),
    ("Red", np.array([0, 70, 150]), np.array([15, 255, 255]), (0, 0, 255)),
    ("Blue", np.array([90, 60, 70]), np.array([114, 255, 255]), (255, 0, 0)),
    ("Purple", np.array([125, 30, 50]), np.array([140, 255, 255]), (128, 0, 128)),
    ("Black", np.array([0, 0, 0]), np.array([180, 255, 30]), (0, 0, 0)),
    ("Orange", np.array([5, 50, 50]), np.array([15, 255, 255]), (0, 165, 255))
]
while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)
    overlay = frame.copy()
    alpha = 1 
    pink_color = (0, 165, 255)
    cv2.rectangle(overlay, (0, 0), (120, 65), pink_color, -1)
    cv2.addWeighted(overlay, alpha, frame, 1 - alpha, 0, frame)
    dt_string = datetime.datetime.now().strftime("%d/%m/%Y")
    cv2.putText(frame, dt_string, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, cv2.LINE_AA)
    time_string = datetime.datetime.now().strftime("%H:%M:%S")
    cv2.putText(frame, time_string, (10, 55), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1, cv2.LINE_AA)
    cv2.rectangle(frame, (0, 450), (640, 480), (0, 0, 0), 2) 
    cv2.rectangle(frame, (0, 450), (640, 480), (255, 255, 255), -1) 
    cv2.putText(frame, "GVHD: Ths. NGUYEN DUY THAO  SVTH: DO HOANG THANG - 21161191  CAO THI LAN ANH - 21161390", (10, 470), cv2.FONT_HERSHEY_SIMPLEX, 0.38, (0, 0, 0), 1, cv2.LINE_AA)
    #làm mờ khung hình và chuyển đổi sang không gian màu HSV
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

    #lặp qua từng màu trong danh sách màu
    for color_name, lower, upper, color in colors:
        #tạo mask dựa trên ngưỡng màu
        mask = cv2.inRange(hsv, lower, upper)
        #loại bỏ các nhiễu và cải thiện mask bằng bitwise_and
        mask = cv2.bitwise_and(mask, mask, mask=cv2.inRange(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), 10, 255))
        #tìm contours trong mask
        cnts = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        #duyệt qua các contour tìm được
        for c in cnts:
            area = cv2.contourArea(c)
            if area > 5000:
                #vẽ khung giới hạn và ghi tên màu
                x, y, w, h = cv2.boundingRect(c)
                cv2.rectangle(frame, (x, y), (x + w, y + h), color, 3)
                cv2.putText(frame, color_name, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2)
                if color_name == "Yellow":
                    ser.write(b'0\n')
                elif color_name == "Green":
                    ser.write(b'1\n')
                elif color_name == "Red":
                    ser.write(b'2\n')
                elif color_name == "Blue":
                    ser.write(b'3\n')
                elif color_name == "Purple":
                    ser.write(b'4\n')
                elif color_name == "Black":
                    ser.write(b'5\n')
                elif color_name == "Orange":
                    ser.write(b'6\n')
                filename = f"{color_name}.jpg"
                cv2.imwrite(filename, frame)
                print(f"Captured image: {filename}")
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) == ord("q"):
        break
cap.release()
cv2.destroyAllWindows()