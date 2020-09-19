"""Tests para los algoritmos de NPM"""

import unittest
import subprocess

class TestNPM(unittest.TestCase):
    """Tests para NPM. Todos asumen que ya esta buildeado"""

    def test_pd(self):

        subprocess.run("./../build/npm PD < test-0.in")


