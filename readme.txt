功能描述：
	对顾客信息、订单信息、商品信息三个数据文件建立笛卡尔表，能够生成可执行文件并按照要求查找并列出所需数据。
开发环境：
	ubuntu-19.10
	gcc 9.2.1
测试DEMO:
	用gcc -Wall lab0.c -o lab0对代码lab0.c进行编译得到lab0
	用./lab0 customer.txt orders.txt lineitem.txt 1 BUILDING 1995-03-29 1995-03-27 5执行lab0得到结果