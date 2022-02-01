from gensim.models import Word2Vec, word2vec
from gensim.models.keyedvectors import KeyedVectors
from numba.core.errors import NumbaError
import numpy
import json
from typing import List, Dict
import numba
from numpy import core, empty
from numpy.lib.function_base import average

DIM = 100

model = Word2Vec.load("./word2vec.model")
corpusFile = open("./corpus.txt", "r")

entityVectors = []
emptyLine = 0

for id, line in enumerate(corpusFile.readlines()):
    line = line.split()
    average = numpy.array([0 for i in range(0, DIM)], numpy.float64)
    for item in line:
        try: # some words do not have vectors
            average += model.wv[int(item)]
        except Exception:
            pass
    if len(line) != 0:
        average /= len(line)
        pass
    else:
        emptyLine += 1
    entityVectors.append(average.tolist())

outputFile = open("entity_vectors.json", "w")
json.dump(entityVectors, outputFile)

print(len(entityVectors), emptyLine)
