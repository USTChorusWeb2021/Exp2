from gensim.models import Word2Vec, word2vec

dataFile = open("../dataset/entity_with_text_sorted.txt", "r")
corpusFile = open("./corpus.txt", "w")

expectId = 0

for line in dataFile.readlines():
    while int(line.split('\t')[0]) != expectId:
        expectId += 1
        corpusFile.write("\n")
    corpusFile.write(line.split('\t')[1])
    expectId += 1

print("Finished Extracting")

sentences = word2vec.LineSentence("./corpus.txt")
model = word2vec.Word2Vec(sentences, vector_size=100, window=5, min_count=1, workers=4, epochs=100)

model.save("word2vec.model")
