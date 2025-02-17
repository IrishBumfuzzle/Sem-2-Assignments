import re

class BPETokenizer:
    def __init__(self, vocab_size):
        self.vocab_size = vocab_size

    def clean(self, text):
        text = text.lower()
        text = re.sub(r'[^A-Za-z\s]', '', text)
        return text.split()

    def train(self, corpus="brown_corpus.txt"):
        with open(corpus, "r") as f:
            text = self.clean(f.read())
            word_freq = dict()
            vocab = list()
            for i, word in enumerate(text):
                text[i] += '_'
                word += '_'
                word_freq[word.lower()] = word_freq.get(word.lower(), 0) + 1
                for char in word.lower():
                    if char not in vocab:
                        vocab.append(char)
            vocab_split = dict()
            for key, value in word_freq.items():
                word_split = tuple(list(key))
                vocab_split[word_split] = value

            while len(vocab) < self.vocab_size:
                new_vocab_split = dict()
                pair_freq = dict()
                for key, value in vocab_split.items():
                    for i in range(len(key) - 1):
                        pair = (key[i], key[i + 1])
                        pair_freq[pair] = pair_freq.get(pair, 0) + value
                max_pair = sorted(pair_freq.items(), key=lambda item: item[1])[-1]
                vocab.append(max_pair[0][0] + max_pair[0][1])
                for key, value in vocab_split.items():
                    new_key = tuple()
                    i = 0
                    while i < len(key):
                        if i < len(key) - 1 and key[i] == max_pair[0][0] and key[i + 1] == max_pair[0][1]:
                            new_key += (key[i] + key[i + 1],)
                            i += 2
                        else:
                            new_key += (key[i],)
                            i += 1
                    new_vocab_split[new_key] = value
                vocab_split = new_vocab_split
            self.vocab = vocab

    def encode(self, text):
        text: list = self.clean(text)
        
        for i, word in enumerate(text):
            word += '_'
            text[i] = tuple(list(word))

        changed = True
        while changed == True:
            changed = False
            for j, word in enumerate(text):
                new_word = list()
                i = 0
                while i < len(word):
                    if i == len(word) - 1:
                        new_word.append(word[i])
                        break
                    pair = word[i]+word[i + 1]
                    if pair in self.vocab:
                        changed = True
                        new_word.append(pair)
                        i += 2
                    else:
                        new_word.append(word[i])
                        i += 1
                text[j] = tuple(new_word)
        for j, word in enumerate(text):
            for i, token in enumerate(word):
                if token not in self.vocab:
                    text[j] = text[j][:i] + ('<unk>',) + text[j][i+1:]
        return text

                
BPE = BPETokenizer(100)
BPE.train()