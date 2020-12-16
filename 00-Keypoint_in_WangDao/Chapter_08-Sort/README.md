# 排序

## 链表排序常用方法
https://blog.csdn.net/baidu_30000217/article/details/77823084

## 同时按照两个属性进行排序

场景：

一组数据中，每个元素都包含两个属性：A和B

要求：

把所有元素按照属性B从小到大排序。对于属性B相同的元素，按照属性A从小到大排序

实现：

先按照A从小到大排序，然后对B进行<u>**稳定的**</u>从小到大排序