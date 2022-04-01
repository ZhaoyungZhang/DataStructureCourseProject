from cyaron import * # 引入CYaRon的库
for i in range(1, 101) :
    test_data = IO(file_prefix="./data/input", data_id = i, disable_output=True) # 生成
    n = randint(4, 20) # 随机一个节点个数
    m = randint(n, n*(n-1)) # 随机一个边的条数
    c = randint(5, 100) # 最大边权
    test_data.input_writeln(n, m, c) # 写入到输入文件里，自动以空格分割并换行
    graph = Graph.DAG(n, m, weight_limit=c) # 生成一个n点，m边的随机图，边权限制为5
    test_data.input_writeln(graph) # 自动写入到输入文件里，以一行一组u v w的形式输出