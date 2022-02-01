import json
import pickle
import random
import joblib
from sklearn.ensemble import RandomForestClassifier

entityVectors = json.load(open("../PCA/entity_vectors_pca.json"))
relationVectors = json.load(open("../PCA/relation_vectors_pca.json"))
trainFile = open("./div0-9.txt")

dataX = []
dataY = []

lines = trainFile.read().splitlines()
n = int(lines[0])

for i in range(1, n + 1):
    triplet = lines[i].split(' ')
    for j in range(0, 3):
        triplet[j] = int(triplet[j])
    dataX.append(entityVectors[triplet[0]] + entityVectors[triplet[1]] + relationVectors[triplet[2]])
    dataY.append(1)

    # Negative sample
    dataX.append(entityVectors[triplet[0]] + entityVectors[random.randint(0, 14540)] + relationVectors[triplet[2]])
    dataY.append(0)

print("Data preparation finished")

model = RandomForestClassifier()
model.fit(dataX, dataY)

# pickle.dump(model, open("model.pkl", "wb"))
joblib.dump(model, "model.pkl")
