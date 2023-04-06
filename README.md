# 取色器

+ 国产系统UOS桌面应用
+ 可以通过该软件获取屏幕的中某点的颜色。

![getColor 图标](./image/1.jpg)


# 编译
```
mkdir build
cmake ..
make
```

# 构建deb包

```
dpkg-buildpackage -us -uc -tc -b
```