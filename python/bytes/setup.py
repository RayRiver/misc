# -*- coding: utf-8 -*-

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize

ext_modules = []

names = [
    'common.bytes'
]

includes = []
lib_dirs = ['./lib']

for name in names:
    ext_modules.append(
        Extension(name,
                  ['./%s.pyx' % name.replace('.', '/')],
                  language='c++',
                  include_dirs=includes,
                  library_dirs=lib_dirs,
        )
    )

setup(
    name = "cythontest extensions",
    ext_modules = cythonize(ext_modules)
)