from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
# 读取数据
data = pd.read_excel('/Users/jerryw/Desktop/疫情.xlsx')
radius = data['累计']
countries = data['国家']
number = radius.count()
print(radius)
theta = np.arange(0, 2 * np.pi, 2 * np.pi / number) # 360度分成20份
# 在画图时用到的 plt.cm.spring_r(r)   r的范围要求时[0,1]
# 画图
fig = plt.figure(figsize = (30, 5), dpi = 350)
polar_coordinate = fig.add_subplot(projection = 'polar')  # 启用极坐标
bar = polar_coordinate.bar(theta, radius, width = 2 * np.pi / number)
print(bar)
polar_coordinate.set_theta_zero_location('N')  # 分别为N, NW, W, SW, S, SE, E, NE                  问题：最多的那个扇区不能朝上
polar_coordinate.set_rgrids([])  # 用于设置极径网格线显示          问题：极径长度网格线和角度网格线不能去掉
polar_coordinate.set_thetagrids([])  # 用于设置极坐标角度网格线显示
polar_coordinate.set_title('Novel coronavirus pneumonia global epidemic situation (accumulated)', fontdict={'fontsize': 10})
# 设置扇形各片的颜色
colors = ['#FAE927','#E9E416','#C9DA36','#9ECB3C','#6DBC49',
          '#37B44E','#3DBA78','#14ADCF','#209AC9','#1E91CA',
          '#2C6BA0','#2B55A1','#2D3D8E','#44388E','#6A368B',
          '#7D3990','#A63F98','#C31C88','#D52178','#D5225B',
          '#D02C2A','#D44C2D','#F57A34','#FA8F2F','#D99D21']
i = 0
for r, bar in zip(radius, bar):
    bar.set_facecolor(colors[i])
    if i <= 8:
        polar_coordinate.text(theta[i], radius[i], countries[i] + ":" + str(radius[i]), fontsize = 1.5)
    i += 1
    bar.set_alpha(0.8)
# 设置边框显示
for key, spine in polar_coordinate.spines.items():
    if key == 'polar':
        spine.set_visible(False)
plt.show()
