import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import rcParams
from matplotlib.ticker import FormatStrFormatter

# 日本語対応フォントを設定
rcParams['font.family'] = 'Yu Gothic'

# CSVファイルの読み込み
file_path = 'result.csv'  # 適切なパスに変更
df = pd.read_csv(file_path)

# 列の取得
labels = df.iloc[:, 0]  # 1列目: ラベル
y_values = df.iloc[:, 3]  # 4列目: 計算時間
x_values = df.iloc[:, 1]  # 2列目: 計算結果

print()

## Y軸の値を正規化
#y_min = y_values.min()
#y_max = y_values.max()
#y_normalized = (y_values - y_min) / (y_max - y_min)  # 0～1にスケール変換

# ラベルごとに散布図を作成
unique_labels = labels.unique()

plt.figure(figsize=(14, 8))
for label in unique_labels:
    subset = df[labels == label]
    plt.scatter(subset.iloc[:, 3], subset.iloc[:, 1], label=label, alpha=0.7, s=500)


# y = -0.001 の横線を描画
plt.axhline(y=-0.001, color='green', label='真値', linestyle='-')

# Y軸を対数スケールにする場合（必要に応じてコメントアウト解除）
#plt.yscale('')

plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%.8f'))

# グラフの詳細設定
plt.xlabel('計算時間', fontsize=24)
plt.ylabel('計算結果', fontsize=24)
plt.title("$dy/dx = xy^{2}$の計算結果と計算時間", fontsize=24)
plt.legend(fontsize=12, markerscale=0.45)
plt.grid(True)
plt.show()

