from gensim.models import Word2Vec, word2vec
from gensim.models.keyedvectors import KeyedVectors
from numba.core.errors import NumbaError
import numpy
import json
from typing import List, Dict
import numba
from numpy import core, double
from numpy.lib.function_base import average

entityFile = open("entity_vectors.json", "r")
tripletsFile = open("div0-9-sorted_by_relation.txt", "r")

entities: List[List[float]] = json.load(entityFile)

triplets = tripletsFile.read().split('\n')

n = int(triplets[0])
triplets = triplets[1:]
for i in range(0, n):
    triplets[i] = triplets[i].split(' ')
    for j in range(0, 3):
        triplets[i][j] = int(triplets[i][j])

tripletsTyped: List[List[int]] = triplets

# @numba.jit(nopython=True, parallel=True)
def computeAverageRelation(triplets: List[List[int]], entities: List[numpy.ndarray]):
    currentR: int = 0
    currentRCount: int = 0
    average: numpy.ndarray = numpy.array([0 for i in range(0, 100)], numpy.float64)
    ret: List[numpy.ndarray] = []

    for index, triplet in enumerate(triplets):
        h: int = triplet[0]
        t: int = triplet[1]
        r: int = triplet[2]

        if r != currentR or index == len(triplets) - 1:
            if currentR == 10:
                print(average.tolist())
            average /= currentRCount
            currentRCount = 0
            ret.append(average)
            average = numpy.array([0 for i in range(0, 100)], numpy.float64)
            print("Relation", currentR)
            currentR = r
        else:
            if currentR == 10:
                print(average.tolist())
            average += entities[t] - entities[h]
            currentRCount += 1

    return ret

print(len(entities))

for i in range(0, len(entities)):
    entities[i] = numpy.array(entities[i], numpy.float64)

result = computeAverageRelation(tripletsTyped, entities)

result = [item.tolist() for item in result]

outputFile = open("relation_vectors.json", "w")
json.dump(result, outputFile)
