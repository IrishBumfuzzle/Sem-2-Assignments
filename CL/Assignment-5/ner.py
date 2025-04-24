from sklearn_crfsuite import CRF
import pandas as pd
from sklearn.metrics import classification_report, confusion_matrix
import re
import matplotlib.pyplot as plt
import seaborn as sns

train_to_tag_mapping = {
    0: "O",
    1: "B-PER",
    2: "I-PER",
    3: "B-ORG",
    4: "I-ORG",
    5: "B-LOC",
    6: "I-LOC",
    7: "B-MISC",
    8: "I-MISC",
}
ilmt_to_ConLL_mapping = {
    "NEP": "PER",
    "NEL": "LOC",
    "NEO": "ORG",
    "NEDA": "MISC",
    "NETI": "MISC",
    "NEAR": "MISC",
    "NEF": "LOC",
    "NEU": "O",
    "NEMI": "MISC",
    "NEN": "O",
    "NETE": "O"
}


def load_conll2003_data(file_path, is_test=False):
    if is_test:
        data = pd.read_csv(file_path)
        sentences = []
        sentence, labels = [], []
        
        for _, row in data.iterrows():
            if pd.isna(row['word']): 
                if sentence:
                    sentences.append((sentence, labels))
                    sentence, labels = [], []
            else:
                sentence.append(row['word'])
                labels.append(row['ner_tag'][:2] + ilmt_to_ConLL_mapping.get(row['ner_tag'][2:], row['ner_tag'][2:]))
        
        if sentence: 
            sentences.append((sentence, labels))
    else:
        data = pd.read_csv(file_path, usecols=[1, 4])
        sentences = []
        for _, row in data.iterrows():
            sentence: str = row['tokens'][1:-1] if row['tokens'][0] == '[' else row['tokens'][2:-2]
            sentence = re.findall(r"(?:'|\")([\S]+)(?:'|\")", sentence)
            labels = [train_to_tag_mapping[int(i)] for i in row['ner_tags'][1:-1].split()]
            sentences.append((sentence, labels))
    
    return sentences

def extract_features(sentence, index):
    word = sentence[index]
    features = {
        'word': word,
        'is_first': index == 0,
        'is_last': index == len(sentence) - 1,
        'is_capitalized': word[0].upper() == word[0],
        'is_all_caps': word.upper() == word,
        'is_all_lower': word.lower() == word,
        'prefix-1': word[:1],
        'prefix-2': word[:2],
        'prefix-3': word[:3],
        'suffix-1': word[-1:],
        'suffix-2': word[-2:],
        'suffix-3': word[-3:],
        'has_hyphen': '-' in word,
        'is_numeric': word.isdigit(),
        'capitals_inside': word[1:].lower() != word[1:]
    }
    return features

def prepare_data(sentences):
    X, y = [], []
    for sentence, labels in sentences:
        X.append([extract_features(sentence, i) for i in range(len(sentence))])
        y.append(labels) 
    return X, y

train_data = load_conll2003_data('datasets/ner/train.csv', is_test=False)
test_data = load_conll2003_data('datasets/annotated_data.csv', is_test=True)

X_train, y_train = prepare_data(train_data)
X_test, y_test = prepare_data(test_data)

crf = CRF(algorithm='lbfgs', c1=0.1, c2=0.1, max_iterations=100, all_possible_transitions=True)
crf.fit(X_train, y_train)

y_pred = crf.predict(X_test)

y_test_flat = [label for seq in y_test for label in seq]
y_pred_flat = [label for seq in y_pred for label in seq]

print("Classification Report:")
print(classification_report(y_test_flat, y_pred_flat, zero_division=0))

labels = list(crf.classes_)
conf_matrix = confusion_matrix(y_test_flat, y_pred_flat, labels=labels)
conf_matrix_df = pd.DataFrame(conf_matrix, index=labels, columns=labels)

plt.figure(figsize=(10, 8))
sns.heatmap(conf_matrix_df, annot=True, fmt='d', cmap='Blues', xticklabels=labels, yticklabels=labels)
plt.title("Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.savefig("metrics/ner_confusion_matrix.png")
plt.close()