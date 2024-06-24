from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
        Pybind11Extension(
            "sample",
            ["sample.cpp"],
            language='c++',
            extra_compile_args=['-std=c++17'],
        ),
    ]

setup(
        name="miniproyect2",
        version="0.1",
        author="Jerimy",
        description="A mini project using pybind11",
        ext_modules=ext_modules,
        cmdclass={"build_ext": build_ext},
        )

