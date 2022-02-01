# README

## 运行环境

CPU：Intel(R) Core(TM) i7-8700 CPU

RAM：16.0 GB

GPU：无独立显卡

宿主机操作系统：Windows 10 专业教育版 21H1

WSL虚拟机操作系统：Ubuntu 20.04 LTS (GNU/Linux 4.4.0-19041-Microsoft x86_64)

gcc：gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

python：Python 3.8.10

numpy：numpy 1.20.3

pytorch：torch 1.10.0

## 关键目录结构

```
./
│  README.md
│  实验报告.pdf
├─dataset
│  └─util
│          divide_triplets.cpp // 三元组划分程序
│          hit_test.cpp // 本地测试程序
│          merge_hit5s.cpp // 用于本地测试的融合方法
│          merge_hit5s_release.cpp // 用于提交的融合方法
├─report
├─src
│  ├─OpenKE-OpenKE-PyTorch
│  │  │  train_transe_exp2_100epochs.py // TransE-100的模型生成及预测程序
│  │  │  train_transe_exp2_3epochs.py // TransE-1的模型生成及预测程序
│  │  ├─openke // OpenKE的源代码，经过修改
│  │  └─train // 对应外层两个程序的相关数据
│  │      ├─100epochs
│  │      └─3epochs
│  ├─PCA
│  │      pca.py // 主成分分析程序
│  ├─RandomForest
│  │      model_gen.py // 随机森林模型生成程序
│  │      predict_tail.py // 随机森林预测程序
│  └─Word2Vec
│          average_entities.py // 实体向量平均程序
│          average_relation.py // 关系向量平均程序
│          model_gen.py // Word2Vec模型生成程序
│          predict_tail.cpp // Word2Vec尾实体预测程序
└─submit
        best_result.txt // 基于TransE-100的最佳结果
        submit_records.txt // 其他提交结果的摘要
```

