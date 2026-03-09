import pandas as pd

# Load the dataset
df = pd.read_csv('sensor_data_wiha.csv')

# Calculate Sum, Mean, and Maximum
results = {
    'Sum': df.sum(),
    'Mean': df.mean(),
    'Maximum': df.max()
}

# Display the results
results_df = pd.DataFrame(results)
print(results_df)
