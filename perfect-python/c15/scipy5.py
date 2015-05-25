import math
import numpy
from scipy import interpolate
import pylab


def main():
    xs = numpy.linspace(0, 2*math.pi, 9)
    ys = numpy.sin(xs)

    pylab.plot(xs, ys, 'o-')
    pylab.show()


if __name__ == '__main__':
    main()
