import matplotlib.pyplot as plt
import numpy as np

def get_word_frequency(filename='brown_corpus.txt'):
    with open(filename, 'r') as f:
        words = f.read().split()
    word_freq = dict()
    for word in words:
        if any(_.isalpha() for _ in word):
            word_freq[word.lower()] = word_freq.get(word.lower(), 0) + 1
    return dict(sorted(word_freq.items(), key=lambda item: item[1]))

def plot_graph(word_freq: dict):
    n = word_freq.__len__()
    x_actual = (np.arange(1, n+1))
    y_actual = (1 / x_actual) * max(word_freq.values())
    x = list(i for i in reversed(range(1, n + 1)))
    y = list(word_freq.values())


    plt.plot(x_actual, y_actual, label='Ideal')
    plt.plot(x, y, label='Empirical')
    plt.xlabel('Rank')
    plt.ylabel('Frequency')
    plt.title('Zipf\'s Law')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.show()

f = get_word_frequency()
plot_graph(f)