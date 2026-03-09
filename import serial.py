import serial
import csv
import pandas as pd
import time
from datetime import datetime

ser = serial.Serial('COM7',9600)

file = open(r'C:\Users\Dinal\Documents\E24\Programming\CO Final Project\finalPRo\sensor_data.csv','a',newline='')
writer = csv.writer(file)

writer.writerow(['Temperature','Humidity'])

while True:

    line = ser.readline().decode().strip()

    data = line.split(',')

    if len(data) == 2:
        current_time = datetime.now().strftime("%H:%M:%S")
        writer.writerow([current_time] + data)
        print(f"{current_time} | Humidity {data[0]}% | Temp {data[1]}C")
