import pickle
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix, classification_report
import seaborn as sns
from hmm import HMMModel
from crf import CRFModel
import os
from prettytable import PrettyTable

training_filename_eng = "training_sets/eng.conllu"
training_filename_hin = "training_sets/hin.conllu"
testing_text_eng_tagged = "testing_text/eng-tagged.txt"
testing_text_eng = "testing_text/eng.txt"
testing_text_hin_tagged = "testing_text/hin-tagged.txt"
testing_text_hin = "testing_text/hin.txt"

os.makedirs("saved_models", exist_ok=True)
os.makedirs("images", exist_ok=True)
try:
    with open("saved_models/hmm-eng.pkl", "rb") as f:
        hmm_eng = pickle.load(f)
    print("Found English HMM model")
except:
    print("Training English HMM model")
    hmm_eng = HMMModel()
    hmm_eng.train(training_filename_eng)
    with open("saved_models/hmm-eng.pkl", "wb") as f:
        pickle.dump(hmm_eng, f)

try:
    with open("saved_models/crf-eng.pkl", "rb") as f:
        crf_eng = pickle.load(f)
    print("Found English CRF model")
except:
    print("Training English CRF model")
    crf_eng = CRFModel()
    crf_eng.train(training_filename_eng)
    with open("saved_models/crf-eng.pkl", "wb") as f:
        pickle.dump(crf_eng, f)

try:
    with open("saved_models/hmm-hin.pkl", "rb") as f:
        hmm_hin = pickle.load(f)
    print("Found Hindi HMM model")
except:
    print("Training Hindi HMM model")
    hmm_hin = HMMModel()
    hmm_hin.train(training_filename_hin, BISMapping=True)
    with open("saved_models/hmm-hin.pkl", "wb") as f:
        pickle.dump(hmm_hin, f)

try:
    with open("saved_models/crf-hin.pkl", "rb") as f:
        crf_hin = pickle.load(f)
    print("Found Hindi CRF model")
except:
    print("Training Hindi CRF model")
    crf_hin = CRFModel()
    crf_hin.train(training_filename_hin, BIS=True)
    with open("saved_models/crf-hin.pkl", "wb") as f:
        pickle.dump(crf_hin, f)


def bis_to_ud(word):
    tag_mapping = {
        "NN": "NOUN",
        "NNV": "NOUN",
        "NST": "NOUN",
        "NNP": "PROPN",
        "PRP": "PRON",
        "PRF": "PRON",
        "PRL": "PRON",
        "PRC": "PRON",
        "PRQ": "PRON",
        "PRI": "PRON",
        "DMD": "DET",
        "DMR": "DET",
        "DMQ": "DET",
        "DMI": "DET",
        "VM": "VERB",
        "VNF": "VERB",
        "VNIF": "VERB",
        "VNG": "VERB",
        "VAUX": "AUX",
        "JJ": "ADJ",
        "RB": "ADV",
        "PSP": "ADP",
        "CCS": "SCONJ",
        "UT": "SCONJ",
        "CCD": "CCONJ",
        "RPD": "PART",
        "INJ": "INTJ",
        "INTF": "PART",
        "CL": "PART",
        "NEG": "PART",
        "QTF": "PART",
        "QTC": "NUM",
        "QTO": "NUM",
        "PUNC": "PUNCT",
        "SYM": "SYM",
        "RDF": "X",
        "UNK": "X",
        "DT": "DET",
    }
    return tag_mapping.get(word, word)


def plot_pos_tags(filename, result_filename):
    with open(filename, "r") as f:
        data = f.readlines()
    tags = dict()
    for sen in data:
        sen = sen.strip().split()
        tags[sen[1]] = tags.get(sen[1], 0) + 1
    tags = dict(sorted(tags.items(), key=lambda x: x[1], reverse=True))

    fig, ax = plt.subplots()
    fig.set_figwidth(12)
    ax.bar(tags.keys(), tags.values(), width=0.6)
    fig.savefig(f"{result_filename}.png")


def make_table(tagset, table_name, tp, fp, fn, precision, recall, f1):
    table = PrettyTable(["Tag", "Precision", "Recall", "F1"])
    table.title = table_name
    table.float_format = ".3"
    for tag in tagset:
        table.add_row([tag, precision[tag], recall[tag], f1[tag]])

    avg_precision = sum(tp.values()) / (sum(tp.values()) + sum(fp.values()))
    avg_recall = sum(tp.values()) / (sum(tp.values()) + sum(fn.values()))
    table.add_row(
        [
            "Overall",
            avg_precision,
            avg_recall,
            2 * avg_precision * avg_recall / (avg_precision + avg_recall),
        ]
    )
    print(table)

def check(filename_tagged, filename_untagged, table_name, model, lang):
    with open(filename_tagged, "r") as f:
        data = f.readlines()

    gold_standard_tags = []
    tagset = set()
    for sen in data:
        sen = sen.strip().split()
        gold_standard_tags.append(bis_to_ud(sen[1]) if lang == "eng" else sen[1])

    tags = model.tag_file(filename_untagged, lang)
    tp = {}
    fp = {}
    fn = {}
    precision = {}
    recall = {}
    f1 = {}
    for i in range(len(gold_standard_tags)):
        tagset.add(tags[i][1])
        if gold_standard_tags[i] == tags[i][1]:
            tp[gold_standard_tags[i]] = tp.get(gold_standard_tags[i], 0) + 1
        else:
            fp[tags[i][1]] = fp.get(tags[i][1], 0) + 1
            fn[gold_standard_tags[i]] = fn.get(gold_standard_tags[i], 0) + 1
            # print(f"Predicted: {tags[i][1]}, Actual: {gold_standard_tags[i]}", "Word:", tags[i][0], "Index: ", i+1)

    for tag in tagset:
        try:
            precision[tag] = tp.get(tag, 0) / (
                tp.get(tag, 0) + fp.get(tag, 0)
            )
        except:
            precision[tag] = 0
        try:
            recall[tag] = tp.get(tag, 0) / (tp.get(tag, 0) + fn.get(tag, 0))
        except:
            recall[tag] = 0
        try:
            f1[tag] = (
                2
                * precision[tag]
                * recall[tag]
                / (precision[tag] + recall[tag])
            )
        except:
            f1[tag] = 0

    tagset = list(tagset)
    tagset.sort()

    make_table(tagset, table_name, tp, fp, fn, precision, recall, f1)

    labels = tagset
    pred_labels = [tag for word, tag in tags]
    cm = confusion_matrix(gold_standard_tags, pred_labels, labels=labels)

    plt.figure(figsize=(10, 8))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=labels, yticklabels=labels)
    plt.xlabel("Predicted Tags")
    plt.ylabel("True Tags")
    plt.title(f"{table_name} POS Tagging Confusion Matrix")
    plt.savefig(f"images/{table_name}.png")


check(testing_text_eng_tagged, testing_text_eng, "HMM English", hmm_eng, "eng")
check(testing_text_eng_tagged, testing_text_eng, "CRF English", crf_eng, "eng")
plot_pos_tags(testing_text_eng_tagged, "images/English POS Frequency")

check(testing_text_hin_tagged, testing_text_hin, "HMM Hindi", hmm_hin, "hin")
check(testing_text_hin_tagged, testing_text_hin, "CRF Hindi", crf_hin, "hin")
plot_pos_tags(testing_text_hin_tagged, "images/Hindi POS Frequency")