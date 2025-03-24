from conllu import parse
import sklearn_crfsuite
import nltk
from indicnlp.tokenize import sentence_tokenize, indic_tokenize

def read_conllu(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        data = f.read()
    sentences = parse(data)
    return sentences


class CRFModel:

    def __init__(self):
        self.crf_model = None

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

    def word2features(self, sent, i):
        word = sent[i]["form"]
        features = {
            "bias": 1.0,
            "word.lower()": word.lower(),
            "word[-3:]": word[-3:],
            "word[-2:]": word[-2:],
            "word.isupper()": word.isupper(),
            "word.istitle()": word.istitle(),
            "word.isdigit()": word.isdigit(),
        }

        if i > 0:
            prev_word = sent[i - 1]["form"]
            features.update(
                {
                    "-1:word.lower()": prev_word.lower(),
                    "-1:word.istitle()": prev_word.istitle(),
                    "-1:word.isupper()": prev_word.isupper(),
                }
            )
        else:
            features["BOS"] = True

        if i < len(sent) - 1:
            next_word = sent[i + 1]["form"]
            features.update(
                {
                    "+1:word.lower()": next_word.lower(),
                    "+1:word.istitle()": next_word.istitle(),
                    "+1:word.isupper()": next_word.isupper(),
                }
            )
        else:
            features["EOS"] = True

        return features

    def sent2features(self, sent):
        return [self.word2features(sent, i) for i in range(len(sent))]

    def sent2labels(self, sent, BIS=False):
        return [token["upos"] if not BIS else self.map_to_bis(token["xpos"]) for token in sent]

    def train(self, filename, BIS=False):
        sentences = read_conllu(filename)
        data = list(sentences)
        X = [self.sent2features(sent) for sent in data]
        y = [self.sent2labels(sent, BIS=BIS) for sent in data]
        crf = sklearn_crfsuite.CRF(
            algorithm="lbfgs", max_iterations=100, all_possible_transitions=True
        )
        crf.fit(X, y)
        self.crf_model = crf

    def tag_string(self, line, lang):
        line = line.rstrip()
        if not line:
            return []
        tokens = nltk.word_tokenize(line) if lang == "eng" else indic_tokenize.trivial_tokenize(line)
        sentence = [
            {"form": token if token != "``" and token != "''" else '"'}
            for token in tokens
        ]
        features = self.sent2features(sentence)
        predicted_tags = self.crf_model.predict([features])[0]
        tagged_tokens = list(zip(tokens, predicted_tags))
        return tagged_tokens

    def tag_file(self, filename, lang):
        with open(filename, "r") as f:
            data = nltk.sent_tokenize(f.read()) if lang == "eng" else sentence_tokenize.sentence_split(f.read().replace("\n", " "), lang="hi")
        tagged_sen = []
        for line in data:
            tagged_sen += self.tag_string(line, lang)
        return tagged_sen


if __name__ == "__main__":
    crf = CRFModel()
    crf.train("ud-treebanks-v2.15/UD_Hindi-HDTB/hi_hdtb-ud-train.conllu", BIS=True)
    # tagged_sen = crf.tag_file("hin.txt")
    # for token in tagged_sen:
    #     print(token)
    t = crf.tag_string("भारतीय रेलवे एक बड़ा संगठन है।")
    from indicnlp.tokenize import sentence_tokenize, indic_tokenize
    with open("hin.txt", "r") as f:
        hotspot = sentence_tokenize.sentence_split(f.read(), lang="hi")
    tags = []
    for t in hotspot:
        tokens = indic_tokenize.trivial_tokenize(t)
        s = [{"form": token} for token in tokens]
        features = crf.sent2features(s)
        predicted_tags = crf.crf_model.predict([features])[0]
        tagged_tokens = list(zip(tokens, predicted_tags))
        tags.append(tagged_tokens)


    for sen in tags:
        for word, token in sen:
            print(word + "\t" + token)
