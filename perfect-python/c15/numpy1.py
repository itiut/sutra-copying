import numpy
import math


def make_rotate_matrix(rad):
    """ 回転行列を生成する  """
    return numpy.array([[math.cos(rad), - math.sin(rad)],
                        [math.sin(rad), math.cos(rad)]]).transpose()


def main():
    num = 20
    base = numpy.array([1, 0])
    print('degree \t result')

    for x in range(num+1):
        rad = x * math.pi * 2 / 20
        rot = make_rotate_matrix(rad)
        deg = 360 / num * x
        result = numpy.dot(base, rot)
        print(deg, '\t', result)


if __name__ == '__main__':
    main()
