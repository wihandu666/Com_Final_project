import serial
import csv

ser = serial.Serial('COM7',9600)

file = open('sensor_data.csv','w',newline='')
writer = csv.writer(file)

writer.writerow(['Temperature','Humidity'])

while True:

    line = ser.readline().decode().strip()

    data = line.split(',')

    if len(data) == 2:
        writer.writerow(data)
        print(data)