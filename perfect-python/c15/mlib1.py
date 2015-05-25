import math
import numpy
import matplotlib.pyplot as plt


def make_rotate_matrix(rad):
    return numpy.array([[math.cos(rad), - math.sin(rad)],
                        [math.sin(rad), math.cos(rad)]]).transpose()


def main():
    num = 20
    base = numpy.array([1, 0])
    print('degree \t result')

    x_positions = []
    y_positions = []

    for x in range(num+1):
        rad = x * math.pi * 2 / 20
        rot = make_rotate_matrix(rad)
        deg = 360 / num * x
        result = numpy.dot(base, rot)
        print(deg, '\t', result)

        x_positions.append(result[0])
        y_positions.append(result[1])

    lines = plt.plot(x_positions, y_positions)
    line = lines[0]
    line.set_linestyle('--')
    line.set_marker('+')
    line.set_color('#FF0000')
    plt.ylabel('Y-asis')
    plt.xlabel('X-axis')
    plt.show()


if __name__ == '__main__':
    main()
