from distutils.core import setup, Extension
setup(
    name='spam',
    version='1.0',
    ext_modules=[Extension('spam', ['spam_type2.c'])]
)