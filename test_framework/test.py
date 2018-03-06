import pytest
import subprocess

def test_test1():
    my_c_program = subprocess.run('test_framework/main')
    print(my_c_program)
