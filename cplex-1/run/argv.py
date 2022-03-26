import xlrd
import os

if __name__ == '__main__':
//脚本文件
    path = 'cd /home/chris/Documents/localsearch/cplex-1/run'
    xls_file = '/home/chris/Documents/localsearch/cplex-1/name/test.xls'

    workbook = xlrd.open_workbook(filename=xls_file)
    table = workbook.sheets()[0]
    nrows = int(table.nrows)
    for i in range(0,nrows):
       name = table.cell_value(rowx=i, colx=0)
       print("name", name)

       k1 = int(table.cell_value(rowx=i, colx=1))
       print("k1", k1)

       k2 = int(table.cell_value(rowx=i, colx=2))
       print("k2", k2)

       k3 = int(table.cell_value(rowx=i, colx=3))
       print("k3", k3)

       k4 = int(table.cell_value(rowx=i, colx=4))
       print("k4", k4)

       # os.system(" cd /home/chris/PycharmProjects/pythonProject/ && python cplexauto.py nDSJC1000.5 300 ")
       for i in [k1,k2,k3,k4]:
           if os.system(" {p0} && python cplexauto.py {p1} {p2} > {p1}{p2}.dat ".format(p0=path, p1=name, p2=i)) == 0:
              print(name,"成功")
           else:
              print(name,"失败")
