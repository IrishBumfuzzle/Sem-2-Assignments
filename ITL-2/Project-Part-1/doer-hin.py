import re
import os
from bs4 import BeautifulSoup
import requests
import json

with open("text.txt", "r") as f:
    text = f.read()
text = text.split()

text_lemmatized = []
cat = re.compile(r"<(.*?)>")
lemma = re.compile(r"/(.*?)<")

for word in text:
    word_lemma = os.popen(f"echo {word} | lt-proc analyser.bin").read()
    word_cat = cat.search(word_lemma)
    if not word_cat:
        continue
    word_cat = word_cat.group(1)
    if word_cat == "n" or word_cat == "vblex" or word_cat == "vbser" and word_lemma not in text_lemmatized:
        word_lemma = lemma.search(word_lemma).group(1)
        text_lemmatized.append(word_lemma)

text_lemmatized = list(dict.fromkeys(text_lemmatized))

# print("Words identified: " + " ".join(text_lemmatized))


MAX_LENGTH_OF_PROPS = 3

syn_ids = {}
for word in text_lemmatized:
    soup = BeautifulSoup(requests.get(f"https://www.cfilt.iitb.ac.in/indowordnet/wordnet?langno=0&query={word}").text, "html.parser")
    try:
        syn_id = soup.find(id="s_id").text
        syn_ids.update({syn_id: word})
    except:
        # print(f"Word {word} not found in Indowordnet")
        pass


max_len = MAX_LENGTH_OF_PROPS
for syn_id in syn_ids:
    synset_url = f"https://www.cfilt.iitb.ac.in/indowordnet/fetch_synset?synset_id={syn_id}&langno=0&pos=noun&start=-25"
    synset_dict = requests.get(synset_url).json()

    hypernymy_url = f"https://www.cfilt.iitb.ac.in/indowordnet/fetch_hypernymy?synset_id={syn_id}&langno=0&pos=noun&start=-25"
    hypernymy_dict = requests.get(hypernymy_url).json()

    hyponymy_url = f"https://www.cfilt.iitb.ac.in/indowordnet/fetch_hyponymy?synset_id={syn_id}&langno=0&pos=noun&start=-25"
    hyponymy_dict = requests.get(hyponymy_url).json()

    meronymy_url = f"https://www.cfilt.iitb.ac.in/indowordnet/fetch_meronymy?synset_id={syn_id}&langno=0&pos=noun&start=-25"
    meronymy_dict = requests.get(meronymy_url).json()

    print()
    print(r"\item \begin{hindi}" + f"{syn_ids[syn_id]}" + r"\end{hindi}")

    if "error" in synset_dict:
        # print("No synonyms found")
        pass
    else:
        synset_dict = json.loads(synset_dict)
        synonyms = synset_dict["synonyms"][1:max_len+1] # Skipping the first one because it tends to be the same word
        if len(synonyms) != 0:
            print(f"Synonmys: " + r"\begin{hindi} " + ", ".join(synonyms) + r" \end{hindi}")


    if "error" in hypernymy_dict:
        # print("No hypernyms found for " + syn_ids[syn_id])
        pass
    else:
        hypernymy_dict = json.loads(hypernymy_dict)
        hypernyms = hypernymy_dict["0"][1][:max_len]
        print(f"Hypernyms: " + r"\begin{hindi} " + ", ".join(hypernyms) + r" \end{hindi}")

    if "error" in hyponymy_dict:
        # print("No hyponyms found for " + syn_ids[syn_id])
        pass
    else:
        hyponymy_dict = json.loads(hyponymy_dict)
        hyponyms = hyponymy_dict["0"][1][:max_len]
        print(f"Hyponyms: " + r"\begin{hindi} " + ", ".join(hyponyms) + r" \end{hindi}")

    if "error" in meronymy_dict:
        # print("No meronyms found for " + syn_ids[syn_id])
        pass
    else:
        meronymy_dict = json.loads(meronymy_dict)
        meronyms = meronymy_dict["0"][1][:max_len]
        print(f"Meronyms: " + r"\begin{hindi} " + ", ".join(meronyms) + r" \end{hindi}")