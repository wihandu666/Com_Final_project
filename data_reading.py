import pandas as pd
import numpy as np
import time
from datetime import datetime

data = pd.read_csv(r'C:\Users\Dinal\Documents\E24\Programming\CO Final Project\finalPRo\sensor_data.csv')

print(data)


# temp = data["Temperature"].astype(float).to_numpy()
# hum = data["Humidity"].astype(float).to_numpy()
# print(hum)

# print(hum)


# print("Average temperature:", np.mean(temp))
# print("Maximum temperature:", np.max(temp))
# print("Minimum temperature:", np.min(temp))

# print("Average humidity:", np.mean(hum))