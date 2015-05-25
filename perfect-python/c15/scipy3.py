from scipy import integrate
a = 0


def func(x):
    """ グローバル変数に依存する関数 """
    global a

    a += x
    return a


result, erorr = integrate.quad(func, 0, 10)
print(result)

result, erorr = integrate.quad(func, 0, 10)
print(result)
