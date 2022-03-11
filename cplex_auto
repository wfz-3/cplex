import cplex
from cplex.exceptions import CplexError
import xlrd
from func_timeout import func_set_timeout
import time
import func_timeout



xls_file = "/home/chris/Documents/localsearch/cplex-1/name/1.xls"

workbook = xlrd.open_workbook(filename=xls_file)
table = workbook.sheets()[0]
nrows = int(table.nrows)

i=0
namelist=[]
while i < nrows:
   name = table.cell_value(rowx=i, colx=0)
   # print("name", name)

   k1 = int(table.cell_value(rowx=i, colx=1))
   # print("k1", k1)

   k2 = int(table.cell_value(rowx=i, colx=2))
   # print("k2", k2)

   k3 = int(table.cell_value(rowx=i, colx=3))
   # print("k3", k3)

   k4 = int(table.cell_value(rowx=i, colx=4))
   # print("k4", k4)
   namelist.append([name,k1,k2,k3,k4])
   i+=1

print(namelist)


path = "/home/chris/Documents/localsearch/cplex-1/"

for i in namelist:

    text_file = open(path+i[0]+".dat",'r')
    v_num = int(text_file.readline().replace(';\n', '').replace('V_num = ',''))
    print('v_num:', v_num)
    print('name',i[0])
    f = text_file.readlines()[1:-1]

    for j in i[1:]:
        k=j
        print('k',k)
        # list element
        list_a = []
        for x in f:
            y = x.replace(',\n', '').replace('<','').replace('>','')
            m=y.index(',')
            l_a = list(map(int, y.split(',')))
            list_a.append(l_a)
            # print(list_a)
        list_edge=list_a
        # print("list_edge:",list_edge)
        print("list_edge_len:",len(list_edge))

        #rows  设置约束的系数
        row_1=[]
        for i in range(v_num):
            row_1 = row_1 + ['x'+str(i+1)]
        row=[]              # the first line constraint
        row.append(row_1)
        row.append([1]*v_num)
        rows=[row]
        j=1
        for i in list_edge:
            rows.append([['x'+str(i[0]),'x'+str(i[1]),'y'+str(j)],[1,1,-1]])
            j=j+1
        # rows.append(row)
        # print(row)
        # print('rows:',rows)


        my_colnames = []    # 变量名
        for i in range(v_num):
            my_colnames.append('x'+str(i+1))
        for j in range(len(list_edge)):
            my_colnames.append('y'+str(j+1))
        # print("colnames:",my_colnames)

        my_rhs = [k]+[0]*len(list_edge)    # 约束右端的值

        my_rownames = [] # 约束名
        for i in range(1+len(list_edge)):
            my_rownames.append('r'+ str(i))
        # print('my_rownames:',my_rownames)

        my_obj = [0]*v_num + len(list_edge)*[1]   # 系数
        my_ub = [1]*(v_num+len(list_edge)) # 变量上界
        my_lb = [0]*(v_num+len(list_edge))    # 变量下界
        my_ctype = "I"*(v_num+len(list_edge))
        my_colnames                  # 变量名
        my_rhs                      # 约束右端的值
        my_rownames                 # 约束名
        my_sense = "E"+"G"*len(list_edge)




        # main function

        def populatebyrow(prob):
            prob.objective.set_sense(prob.objective.sense.maximize) # 求最大值 maximize

            prob.variables.add(obj=my_obj, lb=my_lb, ub=my_ub, types=my_ctype,
                               names=my_colnames)# 导入刚才设置变量相关的值

            rows # 设置约束的系数

            prob.linear_constraints.add(lin_expr=rows, senses=my_sense,
                                        rhs=my_rhs, names=my_rownames)# 填充线性参数进模型


        my_prob = cplex.Cplex()         # 调用函数填充模型
        handle = populatebyrow(my_prob)
        @func_set_timeout(3600)
        def exc():
            try:
                my_prob.solve()

            except CplexError as exc:
                print(exc)

            print()
            # solution.get_status() returns an integer code
            print("Solution status = ", my_prob.solution.get_status(), ":", end=' ')
            # the following line prints the corresponding string
            print(my_prob.solution.status[my_prob.solution.get_status()])
            print("Solution value  = ", my_prob.solution.get_objective_value()) # 获取最优解的值

            numcols = my_prob.variables.get_num()
            numrows = my_prob.linear_constraints.get_num()#

            slack = my_prob.solution.get_linear_slacks()
            x = my_prob.solution.get_values()   # 获取取得最优解的变量值

            print('x: ')
            print(x)

        try:
            exc()
        except func_timeout.exceptions.FunctionTimedOut:
            # my_prob.end()
            print('task func_timeout')

