import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

plt.figure(figsize=(10, 5))

for ds, group in df.groupby("DataStructure"):
    plt.plot(group["N"], group["SearchTime"], marker='o', linewidth=2, label=ds)

plt.title("Order of Growth: Search Time Comparison", fontsize=14, fontweight='bold')
plt.xlabel("Input Size (N)", fontsize=12)
plt.ylabel("Execution Time (Microseconds)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title="Data Structure", fontsize=10)
plt.tight_layout()

plt.savefig("order_of_growth.png", dpi=300)
plt.show()
