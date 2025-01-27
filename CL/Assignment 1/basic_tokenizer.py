import re
from typing import List

def sentence_tokenizer(fileName='cleaned_text.txt') -> List[str]:
    with open(fileName, 'r') as file:
        text = file.read()
        
        text = re.sub("\n", " ", text) # replaces newlines with spaces
        # sentences = re.split(r"(?<=\.|\?|!)(?<!mrs\.)(?<![dm]r\.) ", text) # splits text into sentences
        sentences = re.findall(r".*?(?<!mrs)(?<![dm]r)[.!?]\"?\s", text)
        return sentences
    
def word_tokenizer(sentences: List[str]) -> List[List[str]]:
    words = []
    for sentence in sentences:
        wordsInSentence = re.findall(r"\d+[\W\d]*\d+|(?:[A-z0-9-']|\.(?!$))+|[^\s]", sentence.strip()) # splits sentences into words
        words.append(wordsInSentence)
    return words

text = sentence_tokenizer()
text = word_tokenizer(text)

for sentence in text:
    print(sentence)
    print()