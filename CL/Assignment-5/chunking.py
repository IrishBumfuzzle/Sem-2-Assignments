import pandas as pd
from sklearn_crfsuite import CRF, metrics
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix 
import matplotlib.pyplot as plt 

chunk_conversion = {
    "JJP": "ADJP",
    "VGF": "VP",
    "VGNF": "VP",
}

def load_data_from_csv(filepath):
    df = pd.read_csv(filepath, on_bad_lines='skip', skip_blank_lines=True) 
    df['sentence_id'] = (df['words'].isnull()).cumsum()
    df = df.dropna(subset=['words']) 
    grouped = df.groupby("sentence_id")
    sentences = []
    for _, group in grouped:
        sentences.append(group[["words", "POS", "chunk_tags"]].values.tolist())
    return sentences

def load_test_data_from_csv(filepath):
    df = pd.read_csv(filepath, on_bad_lines='skip', skip_blank_lines=True)
    df['sentence_id'] = (df['word'].isnull()).cumsum()
    df = df.dropna(subset=['word'])
    grouped = df.groupby("sentence_id")
    sentences = []
    for _, group in grouped:
        sentence = group[["word", "ner_tag", "chunk_tag"]].values.tolist()
        for token in sentence:
            token[2] = token[2][:2] + chunk_conversion.get(token[2][2:], token[2][2:])
        sentences.append(sentence)
    return sentences

data = load_data_from_csv('datasets/chunking/train.csv')
test_data = load_test_data_from_csv('datasets/annotated_data.csv')

def word2features(sent, i):
    word = sent[i][0]
    postag = sent[i][1]
    features = {
        'word.lower()': word.lower(),
        'word[-3:]': word[-3:],
        'word[-2:]': word[-2:],
        'word.isupper()': word.isupper(),
        'word.istitle()': word.istitle(),
        'word.isdigit()': word.isdigit(),
        'postag': postag,
        'postag[:2]': postag[:2],
    }
    if i > 0:
        word1 = sent[i-1][0]
        postag1 = sent[i-1][1]
        features.update({
            '-1:word.lower()': word1.lower(),
            '-1:postag': postag1,
            '-1:postag[:2]': postag1[:2],
        })
    else:
        features['BOS'] = True

    if i < len(sent)-1:
        word1 = sent[i+1][0]
        postag1 = sent[i+1][1]
        features.update({
            '+1:word.lower()': word1.lower(),
            '+1:postag': postag1,
            '+1:postag[:2]': postag1[:2],
        })
    else:
        features['EOS'] = True

    return features

def sent2features(sent):
    return [word2features(sent, i) for i in range(len(sent))]

def sent2labels(sent):
    return [label for _, _, label in sent]

def sent2tokens(sent):
    return [token for token, _, _ in sent]

test_sents = test_data 
train_sents, _ = train_test_split(data, test_size=0.2, random_state=42) 

X_train = [sent2features(s) for s in train_sents]
y_train = [sent2labels(s) for s in train_sents]
X_test = [sent2features(s) for s in test_sents]
y_test = [sent2labels(s) for s in test_sents]

crf = CRF(algorithm='lbfgs', c1=0.1, c2=0.1, max_iterations=100, all_possible_transitions=True)
crf.fit(X_train, y_train)

y_pred = crf.predict(X_test)
print(metrics.flat_classification_report(y_test, y_pred, labels=crf.classes_, zero_division=0)) 

flat_y_test = [label for sent in y_test for label in sent] 
flat_y_pred = [label for sent in y_pred for label in sent] 
conf_matrix = confusion_matrix(flat_y_test, flat_y_pred, labels=crf.classes_)
labels = list(crf.classes_)

plt.figure(figsize=(10, 8))
plt.imshow(conf_matrix, interpolation='nearest', cmap=plt.cm.Blues)
plt.title("Confusion Matrix")
plt.colorbar()
tick_marks = range(len(labels))
plt.xticks(tick_marks, labels, rotation=45)
plt.yticks(tick_marks, labels)

for i in range(len(labels)):
    for j in range(len(labels)):
        plt.text(j, i, conf_matrix[i, j], horizontalalignment="center", color="white" if conf_matrix[i, j] > conf_matrix.max() / 2 else "black")

plt.ylabel("True Labels")
plt.xlabel("Predicted Labels")
plt.tight_layout()

plt.savefig("metrics/chunking_confusion_matrix.png")
