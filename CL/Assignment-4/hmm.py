from collections import Counter, defaultdict
from indicnlp.tokenize import sentence_tokenize, indic_tokenize
import nltk

class HMMModel:
    def __init__(self):
        self.transitions = defaultdict(Counter)
        self.emissions = defaultdict(Counter)
        self.initial = Counter()
        self.transitions_prob = dict()
        self.emissions_prob = dict()
        self.initial_prob = dict()
        self.tagset = set()
        self.vocabsize = 0
        self.delta = 1

    def map_to_bis(self, tag):
        mapping = {
            "NNPC": "NNP",
            "NNC": "NN",
            "SYM": "PUNCT",
            "DEM": "DM",
            "PRP": "PR",
            "QF": "QTF",
            "QC": "QTC",
            "QO": "QTO",
            "PRPC": "PR",
        }
        return mapping.get(tag, tag)

    def train(self, filename, BISMapping=False):

        vocab = set()

        with open(filename) as f:
            sentence = []

            for line in f:
                if line.startswith("#"):
                    continue

                elif line == "\n":
                    if len(sentence) == 0:
                        continue

                    self.initial[sentence[0][1]] += 1

                    for i in range(1, len(sentence)):
                        self.transitions[sentence[i - 1][1]][sentence[i][1]] += 1

                    for word, tag in sentence:
                        self.emissions[tag][word] += 1
                        self.tagset.add(tag)
                        vocab.add(word)

                    sentence = []

                else:
                    tokens = line.split()
                    word = tokens[1]
                    tag = tokens[3] if not BISMapping else self.map_to_bis(tokens[4])
                    if tag == "_":
                        vocab.add(word)
                        continue
                    sentence.append((word, tag))

        self.vocabsize = len(vocab)
        for tag in self.tagset:
            self.transitions_prob[tag] = dict()
            self.emissions_prob[tag] = dict()

        for tag in self.tagset:
            self.transitions_prob[tag].update(
                {
                    tag2: (count + self.delta)
                    / (
                        sum(self.transitions[tag].values())
                        + self.delta * len(self.tagset)
                    )
                    for tag2, count in self.transitions[tag].items()
                }
            )
            self.emissions_prob[tag].update(
                {
                    word: (count + self.delta)
                    / (sum(self.emissions[tag].values()) + self.delta * self.vocabsize)
                    for word, count in self.emissions[tag].items()
                }
            )
            self.initial_prob.update(
                {
                    tag: (count + self.delta)
                    / (sum(self.initial.values()) + self.delta * len(self.tagset))
                    for tag, count in self.initial.items()
                }
            )

    def viterbi(self, sentence):
        V = [{} for _ in range(len(sentence))]
        backpointer = [{} for _ in range(len(sentence))]
        tags = [None] * len(sentence)
        default_prob = lambda tag: self.delta / (
            sum(self.transitions[tag].values()) + self.delta * self.vocabsize
        )

        V[0] = {
            tag: self.initial_prob.get(tag, 0)
            * self.emissions_prob[tag].get(sentence[0], default_prob(tag))
            for tag in self.tagset
        }

        for i in range(1, len(sentence)):
            for tag in self.tagset:
                max_iters = [
                    (tag2, V[i - 1][tag2] * self.transitions_prob[tag2].get(tag, 0))
                    for tag2 in self.tagset
                ]
                max_prop = max(max_iters, key=lambda x: x[1])
                backpointer[i][tag] = max_prop[0]
                V[i][tag] = max_prop[1] * self.emissions_prob[tag].get(
                    sentence[i], default_prob(tag)
                )

        tags[-1] = max(V[-1], key=V[-1].get)
        for i in reversed(range(len(sentence) - 1)):
            tags[i] = backpointer[i + 1][tags[i + 1]]

        return tags

    def tag_file(self, filename, lang):
        with open(filename, "r") as f:
            data = nltk.sent_tokenize(f.read()) if lang == "eng" else sentence_tokenize.sentence_split(f.read().replace("\n", " "), lang="hi")

        tagged_sen = []

        for line in data:
            line = line.rstrip()
            if not line:
                continue
            sentence = nltk.word_tokenize(line) if lang == "eng" else indic_tokenize.trivial_tokenize(line)
            for i, word in enumerate(sentence):
                if word == "``" or word == "''":
                    sentence[i] = '"'
            tags = self.viterbi(sentence)
            for i in range(len(sentence)):
                tagged_sen.append((sentence[i], tags[i]))

        return tagged_sen


if __name__ == "__main__":
    hmm = HMMModel()
    hmm.train("ud-treebanks-v2.15/UD_English-EWT/en_ewt-ud-train.conllu")
    hmm.tag_file("eng.txt")

    # text = "what are the coach flights between here and there leaving august tenth and returning august twelve".split()

    # tags = hmm.viterbi(text)
    # for i in range(len(text)):
    #     print(text[i], tags[i])
