import setuptools

setuptools.setup(
    name="carrier-sample",
    version="0.1.16",
    author="WingC",
    author_email="1018957763@qq.com",
    description="high speed acquisition card program for carrier && single && highlight",
    long_description="",
    url="https://github.com/KD-Group/Carrier.Sample",

    classifiers=(
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ),
    data_files=['cpp_build/carrier_sample.exe'],

    keywords='carrier sample',
    packages=["carrier_sample"],
    install_requires=['requests'],
    extras_require={'test': ['pytest']},
)
