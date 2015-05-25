from scipy import integrate


def ret1(x):
    """ 常に1を返す """
    return 1


result, error = integrate.quad(ret1, 0, 10)
print(result)
print(error)
