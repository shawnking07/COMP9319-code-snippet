import pandas as pd
from scipy.stats import entropy

data=list("ABCBabaBCABaCaaba")
pd_series = pd.Series(data)
counts = pd_series.value_counts()
entropy = entropy(counts, base=2)

print(counts, len(data))
print(entropy)