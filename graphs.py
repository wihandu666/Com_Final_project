import pandas as pd
import matplotlib.pyplot as plt

# read csv file
data = pd.read_csv(r'C:\Users\Dinal\Documents\E24\Programming\CO Final Project\finalPRo\sensor_data_wiha2.csv')

# extract columns
time = data["Time"]
temperature = data["Temperature"]
Humidity = data["Humidity"]


# time and temperature plot
plt.subplot(2, 1, 1)
plt.plot(time, temperature)
plt.xlabel("Time")
plt.ylabel("Temperature")
plt.title("Temperature vs Time")

plt.subplot(2, 1, 2)
plt.plot(time, Humidity)
plt.xlabel("Time")
plt.ylabel("Humidity")
plt.title("Humidity vs Time")


plt.show()