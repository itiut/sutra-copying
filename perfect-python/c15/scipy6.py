import math
import numpy
from scipy import interpolate
import pylab


def main():
    xs = numpy.linspace(0, 2*math.pi, 9)
    ys = numpy.sin(xs)

    xn = numpy.linspace(0, 2*math.pi, 180)
    f2 = interpolate.interp1d(xs, ys, kind='cubic')
    yn = f2(xn)

    pylab.plot(xs, ys, 'o-', xn, yn)
    pylab.show()


if __name__ == '__main__':
    main()
