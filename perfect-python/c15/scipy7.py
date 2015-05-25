import math
import numpy
from scipy import interpolate
import pylab


def main():
    xs = numpy.linspace(0, 2*math.pi, 9)
    ys = numpy.sin(xs)

    xn = numpy.linspace(0, 2*math.pi, 180)
    ius = interpolate.InterpolatedUnivariateSpline(xs, ys)
    yn = ius(xn)

    pylab.plot(xs, ys, 'o-', xn, yn)
    pylab.show()


if __name__ == '__main__':
    main()
