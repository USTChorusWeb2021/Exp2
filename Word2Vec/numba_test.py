import numba
import numpy
from typing import List, Dict, Tuple

@numba.jit(nopython=True)
def test(div: List[Tuple[int]], array: List[numpy.ndarray]):
    # array = numpy.array([3, 3, 5], dtype=numpy.float64)
    array[0] /= div[0][0]
    return array[0]

nparray = [numpy.array([3, 3, 5], dtype=numpy.float64)]
div: List[Tuple[int]] = [(2,)]
print(test(div, nparray).tolist())
