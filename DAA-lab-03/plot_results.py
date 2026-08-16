import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results1.csv")
plt.figure(figsize=(10, 5))
plt.plot(df["ArraySize"], df["BinaryComparisons"], label="Binary Search", marker="o")
plt.plot(df["ArraySize"], df["TernaryComparisons"], label="Ternary Search", marker="s")
plt.xscale("log")
plt.xlabel("Array Size (n)")
plt.ylabel("Comparisons")
plt.title("Binary vs Ternary Search Performance")
plt.legend()
plt.grid(True)
plt.savefig("benchmark.png")
plt.show()
