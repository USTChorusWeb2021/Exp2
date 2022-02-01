from sklearn.decomposition import PCA
import json

entityVectors = json.load(open("../Word2Vec/entity_vectors.json"))
relationVectors = json.load(open("../Word2Vec/relation_vectors.json"))

pca = PCA(n_components=64)

pca.fit(entityVectors + relationVectors)

newEntityVectors = pca.transform(entityVectors)
json.dump(newEntityVectors.tolist(), open("entity_vectors_pca.json", "w"))

newRelationVectors = pca.transform(relationVectors)
json.dump(newRelationVectors.tolist(), open("relation_vectors_pca.json", "w"))

print(pca.explained_variance_ratio_)
print(sum(pca.explained_variance_ratio_))
