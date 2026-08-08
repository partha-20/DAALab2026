import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results3.csv")

plt.figure(figsize=(10, 6))

for ds, group in df.groupby("DataStructure"):
    plt.plot(group["K"], group["ExecutionTime"], marker='o', linewidth=2, label=ds)

plt.title("Merging k Sorted Arrays: Iterative O(nk^2) vs Pairwise O(nk log k)", fontsize=13, fontweight='bold')
plt.xlabel("Number of Arrays (k)", fontsize=12)
plt.ylabel("Execution Time (Microseconds)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title="Algorithm", fontsize=10)
plt.tight_layout()

plt.savefig("k_way_merge_comparison.png", dpi=300)
plt.show()
