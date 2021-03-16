import numpy as np

allServer1 = []
nums1 = []
allVM1 = []
vmnum1 = []
with open("training-1.txt") as data1:
    N = int(data1.readline())
    for n in range(N):
        ps = data1.readline()
        server = ps.strip('(\n)').split(',')
        model = server[0]
        core = int(server[1])
        ram = int(server[2])
        price = int(server[3])
        costpd = int(server[4])
        allServer1.append([model, core, ram, price, costpd])
        nums1.append([core, ram, price, costpd])
    M = int(data1.readline())
    for m in range(M):
        vm = data1.readline().strip('(\n)').split(',')
        model = vm[0]
        core = int(vm[1])
        ram = int(vm[2])
        node = int(vm[3])
        allVM1.append([model, core, ram, node])
        vmnum1.append([core, ram, node])

print("服务器平均值1", np.mean(nums1, axis=0))
print("虚拟机平均值1", np.mean(vmnum1, axis=0))

allServer2 = []
nums2 = []
allVM2 = []
vmnum2 = []
with open("training-2.txt") as data2:
    N = int(data2.readline())
    for n in range(N):
        ps = data2.readline()
        server = ps.strip('(\n)').split(',')
        model = server[0]
        core = int(server[1])
        ram = int(server[2])
        price = int(server[3])
        costpd = int(server[4])
        allServer2.append([model, core, ram, price, costpd])
        nums2.append([core, ram, price, costpd])
    M = int(data2.readline())
    for m in range(M):
        vm = data2.readline().strip('(\n)').split(',')
        model = vm[0]
        core = int(vm[1])
        ram = int(vm[2])
        node = int(vm[3])
        allVM2.append([model, core, ram, node])
        vmnum2.append([core, ram, node])


print("服务器平均值2", np.mean(nums2, axis=0))
print("虚拟机平均值2", np.mean(vmnum2, axis=0))
print("总服务器平均值", np.mean(nums1+nums2, axis=0))
print("总虚拟机平均值", np.mean(vmnum1+vmnum2, axis=0))


print("总服务器最大值", np.max(nums1+nums2, axis=0))
print("总虚拟机最大值", np.max(vmnum1+vmnum2, axis=0))


a = []
b = []
c = []
d = []
with open("an2.txt") as data2:
    N = int(data2.readline())
    for n in range(N):
        ps = data2.readline()
        server = ps.strip('(\n)').split(',')
        model = server[0]
        node = server[1]
        core = int(server[2])
        ram = int(server[3])
        if node == 'A':
            a.append([core, ram, 0, 0])
        elif node == 'B':
            a.append([0, 0, core, ram])
        else:
            a.append([core >> 1, ram >> 1, core >> 1, ram >> 1])
    N = int(data2.readline())
    for n in range(N):
        ps = data2.readline()
        server = ps.strip('(\n)').split(',')
        model = server[0]
        node = server[1]
        core = int(server[2])
        ram = int(server[3])
        if node == 'A':
            b.append([core, ram, 0, 0])
        elif node == 'B':
            b.append([0, 0, core, ram])
        else:
            b.append([core >> 1, ram >> 1, core >> 1, ram >> 1])

res = np.sum(a, axis=0)
print("0服务器", res)
print("0服务器", res[0]+res[2], res[1]+res[3])
res = np.sum(b, axis=0)
print("0服务器", res)
print("0服务器", res[0]+res[2], res[1]+res[3])
