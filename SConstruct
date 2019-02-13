import sys

VariantDir('cpp_build', 'src', duplicate=0)

if sys.platform == 'win32':
    env = Environment(CCFLAGS=["/MD", "/EHsc", "-O2"])
    env.Program('cpp_build/carrier_sample.exe', Glob('cpp_build/*/*.cpp') + ['cpp_build/main.cpp'])
elif sys.platform == 'darwin':
    env = Environment(CPPFLAGS=['-std=c++11', "-O2"])
    env.Program('cpp_build/carrier_sample.exe', Glob('cpp_build/*/*.cpp') + ['cpp_build/main.cpp'])
else:
    env = Environment(CXX='g++-4.9', CPPFLAGS=['-std=c++11', '-pthread', "-O2"])
    env.Program('cpp_build/carrier_sample.exe', Glob('cpp_build/*/*.cpp') + ['cpp_build/main.cpp'], LIBS=['pthread'])
