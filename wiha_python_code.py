import serial
import csv
import os
from datetime import datetime

ser = serial.Serial('COM7', 9600)

file_path = r'C:\Users\Dinal\Documents\E24\Programming\CO Final Project\finalPRo\finalPro2\sensor_data_wiha3.csv'

file_exists = os.path.isfile(file_path) and os.path.getsize(file_path) > 0

with open(file_path, 'a', newline='') as file:
    writer = csv.writer(file)

    if not file_exists:
        writer.writerow(['Time', 'Humidity', 'Temperature','Heat Index'])

    while True:
        try:
            line = ser.readline().decode().strip()
            data = line.split(',')

            if len(data) == 3:
                current_time = datetime.now().strftime("%H:%M:%S")

                writer.writerow([current_time, data[0], data[1], data[2]])
                file.flush()

                print(f"{current_time} | Humidity {data[0]}% | Temp {data[1]}C | HI {data[2]}C")

        except KeyboardInterrupt:
            print("Stopping...")
            break

ser.close()