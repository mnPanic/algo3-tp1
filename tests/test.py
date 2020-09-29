"""Tests para los algoritmos de NPM"""

import os
import unittest
import subprocess

algorithms = ["FB", "BT", "BT-F", "BT-O-G", "BT-O-C", "DP"]
def get_expected(file: str) -> str:
    with open(file) as f:
        return f.read().split(" ")[-1]


class TestNPM(unittest.TestCase):
    """Tests para NPM. Todos asumen que ya esta buildeado"""

    def test_FB(self):
        for algorithm in algorithms:
            for test in os.listdir("tests/files"):
                test_name = "Test: "+test

                with self.subTest(test_name):
                    test = "tests/files/" + test
                    res = subprocess.run(f"./build/npm {algorithm} < {test}", shell=True, capture_output=True)

                    assert res.stdout.rstrip().decode("utf-8") == get_expected(test), f"falló el test {test} en el algoritmo {algorithm}"


if __name__ == "__main__":
    unittest.main()