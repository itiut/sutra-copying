from scipy import integrate


def func(x):
    print(x)
    return x


integrate.quad(func, 0, 10)
