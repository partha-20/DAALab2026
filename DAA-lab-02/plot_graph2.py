import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results2.csv")

plt.figure(figsize=(10, 6))

for ds, group in df.groupby("DataStructure"):
    plt.plot(group["N"], group["ExecutionTime"], marker='o', linewidth=2, label=ds)

plt.title("Order of Growth: 2-Way vs 3-Way Merge Sort", fontsize=14, fontweight='bold')
plt.xlabel("Input Size (N)", fontsize=12)
plt.ylabel("Execution Time (Microseconds)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title="Algorithm", fontsize=10)
plt.tight_layout()

plt.savefig("merge_sort_comparison.png", dpi=300)
plt.show()
