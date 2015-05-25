from scipy import integrate


def echo(x):
    """ 受け取った値をそのまま返す """
    return x


result, error = integrate.quad(echo, 0, 10)
print(result)
print(error)
