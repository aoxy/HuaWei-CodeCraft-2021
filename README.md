# 2021 华为软件精英挑战赛`迪杰特斯拉`队

## 重要说明

各位不要在 main 分支上开发，pull 后迁出分支，在新分支上开发

```shell
git checkout main
git pull
git checkout -b newBranchName
# 开发好打算提交
git add .
git commit -m "提交说明"
git push
# 然后我来合并
```

## 比赛链接

https://competition.huaweicloud.com/codecraft2021

## 团队概况

### 队名

迪杰特斯拉(3/3)

### 队员

| 队员名       | 状态   |
| ------------ | ------ |
| hw10966629 ☆ | 已加入 |
| hw25612598   | 已加入 |
| hw664246401  | 已加入 |

## 运行方式

```bash
# 克隆仓库进入项目
git clone git@github.com:aoxy/HuaWei-CodeCraft-2021.git
cd HuaWei-CodeCraft-2021/SDK_C++/

# 编译源码
sh ./build.sh

# 运行程序
./bin/CodeCraft-2021

# 编译并运行
sh ./build_and_run.sh

# 打包提交
./CodeCraft_zip.sh

# 测试运行（结果输出到sampleout.txt文件）
./bin/CodeCraft-2021 < ../samplein.txt > ../sampleout.txt
# 或者
sh ./test.sh

# 大规模数据测试（结果输出到training-*out.txt文件）
sh ./train.sh
```
