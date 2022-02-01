import json
import joblib
from sklearn.linear_model import LogisticRegression

entityVectors = json.load(open("../PCA/entity_vectors_pca.json"))
relationVectors = json.load(open("../PCA/relation_vectors_pca.json"))
filterFile = open("../dataset/all_triplets.txt", "r")
testFile = open("../dataset/util/test_release.txt", "r")
outputFile = open("./hit5.txt", "w")

model: LogisticRegression = joblib.load("model.pkl")

print("Finished Initializing")

# print(model.predict_proba([entityVectors[435] + entityVectors[435] + relationVectors[10]]))

filter = set()
lines = filterFile.readlines()
n = int(lines[0])
for i in range(1, n + 1):
    triplet = lines[i].split(' ')
    for j in range(0, 3):
        triplet[j] = int(triplet[j])
    filter.add((triplet[0], triplet[1], triplet[2]))


lines = testFile.readlines()

n = int(lines[0])
for i in range(1, n + 1):
    triplet = lines[i].split(' ')
    for j in range(0, 3):
        triplet[j] = int(triplet[j])
    
    results = []
    # for j in range(0, len(entityVectors)):
    predictList = [entityVectors[triplet[0]] + entityVectors[j] + relationVectors[triplet[2]] for j in range(0, len(entityVectors))]
    results = [item.tolist() for item in model.predict_proba(predictList)]
    # results = model.predict_proba(entityVectors)
    results = [[results[j][0], j] if (triplet[0], j, triplet[2]) not in filter else [1, j] for j in range(0, len(entityVectors))]
    results.sort()

    outputFile.write("{}\t{} {}\t".format(i, triplet[0], triplet[2]))
    for j in range(0, 5):
        outputFile.write("{} {} ".format(results[j][1], results[j][0]))
    outputFile.write("\n")
    print(i)

    # results = model.predict_proba([entityVectors[triplet[0]] + [triplet[2]]]).tolist()
    # results = [[1 - results[j], j] if (triplet[0], j, triplet[2]) not in filter else [1, j] for j in range(0, len(results))]
    # results.sort()

    # outputFile.write("{}\t{} {}\t".format(i, triplet[0], triplet[2]))
    # for j in range(0, 5):
    #     outputFile.write("{} {} ".format(results[j][1], results[j][0]))
    # outputFile.write("\n")
    # print(i)
