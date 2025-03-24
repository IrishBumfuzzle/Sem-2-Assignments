# Theoretical Background of POS Tagging Approaches

## Hidden Markov Models (HMM)

### Fundamental Principles

- **Generative Model:**  
  HMM is a generative probabilistic model that defines a joint probability distribution over observed sequences (words) and hidden state sequences (POS tags). It models the probability  P(W, T)  where W is a sequence of words and T is a sequence of tags.

- **Markov Assumption:**  
  The model assumes that the tag of a word depends only on a limited number of previous tags (often just the previous tag in a first-order HMM), expressed as:  

  P(T<sub>i</sub> | T<sub>1</sub>, T<sub>2</sub>, ..., T<sub>i-1</sub>) ≈ P(T<sub>i</sub> | T<sub>i-1</sub>)

- **Output Independence Assumption:**  
  It also assumes that the observed word at a position depends only on the tag at that position, leading to the formulation:  
  
  P(W<sub>i</sub> | T<sub>1</sub>, T<sub>2</sub>, ..., T<sub>n</sub>, W<sub>1</sub>, W<sub>2</sub>, ..., W<sub>i-1</sub>) ≈ P(W<sub>i</sub> | T<sub>i</sub>)
  

- **Decoding with Viterbi Algorithm:**  
  The most likely sequence of tags for a given sentence is found using the Viterbi algorithm, which efficiently computes the maximum a posteriori estimate of the tag sequence.

### Strengths and Weaknesses

- **Strengths:**  
  - **Simplicity:** HMMs are conceptually simple and have well-understood training and decoding procedures.
  - **Efficient Inference:** Dynamic programming algorithms (e.g., Viterbi) make decoding computationally efficient.

- **Weaknesses:**  
  - **Independence Assumptions:** The strong assumptions (e.g., limited dependency on past tags and word emission independence) can oversimplify the actual language structure.
  - **Feature Limitations:** HMMs typically rely on simple lexical features, limiting the ability to incorporate rich, overlapping features of the context.

---

## Conditional Random Fields (CRF)

### Fundamental Principles

- **Discriminative Model:**  
  Unlike HMMs, CRFs model the conditional probability  P(T | W)  directly. This approach focuses on the boundary between classes rather than modeling the joint distribution of inputs and outputs.

- **Feature Flexibility:**  
  CRFs allow the incorporation of arbitrary, overlapping features (e.g., word shape, prefixes, suffixes, surrounding context) without making strong independence assumptions about the observed data. This flexibility can capture more complex patterns.

- **Global Normalization:**  
  CRFs perform global normalization over the entire sequence, which helps avoid the label bias problem often encountered in locally normalized models.

### Strengths and Weaknesses

- **Strengths:**  
  - **Rich Feature Integration:** The ability to include a wide range of features can lead to better performance in POS tagging, particularly when context is important.
  - **Fewer Independence Assumptions:** CRFs make fewer assumptions about the independence of observations, enabling a more accurate modeling of language.

- **Weaknesses:**  
  - **Computational Complexity:** Training CRFs can be computationally intensive, especially with large feature sets and long sequences.
  - **Parameter Estimation:** Finding the optimal parameters may require more sophisticated optimization techniques and more training data to avoid overfitting.

---

## Probabilistic vs. Discriminative Models

### Probabilistic Models (HMM)

- **Definition:**  
  Probabilistic models like HMMs model the joint distribution  P(W, T)  and require assumptions about the generative process of the data.
  
- **Characteristics:**  
  - Depend on generative assumptions (e.g., Markov and independence assumptions).
  - Generally simpler and faster to train.
  - Can be less flexible due to the necessity of modeling the joint distribution.

### Discriminative Models (CRF)

- **Definition:**  
  Discriminative models like CRFs model the conditional distribution  P(T | W)  directly, focusing on the relationship between inputs and outputs.

- **Characteristics:**  
  - Do not need to model the distribution of the input data.
  - Can incorporate diverse, overlapping features that better capture dependencies in the data.
  - Often achieve higher accuracy in tasks such as POS tagging, but at the cost of increased computational demands.

---

# Comparison of Performance

Confusion matrices are present in the images folder

## Performance of HMM
```
+--------------------------------------+
|             HMM English              |
+---------+-----------+--------+-------+
|   Tag   | Precision | Recall |   F1  |
+---------+-----------+--------+-------+
|   ADJ   |   0.550   | 0.917  | 0.687 |
|   ADP   |   0.881   | 0.983  | 0.929 |
|   ADV   |   0.933   | 0.737  | 0.824 |
|   AUX   |   0.680   | 1.000  | 0.810 |
|  CCONJ  |   1.000   | 1.000  | 1.000 |
|   DET   |   0.844   | 1.000  | 0.915 |
|   NOUN  |   0.871   | 0.846  | 0.859 |
|   NUM   |   1.000   | 0.500  | 0.667 |
|   PART  |   0.333   | 0.400  | 0.364 |
|   PRON  |   0.483   | 1.000  | 0.651 |
|  PROPN  |   0.867   | 0.491  | 0.627 |
|  PUNCT  |   0.935   | 1.000  | 0.967 |
|  SCONJ  |   0.000   | 0.000  |   0   |
|   VERB  |   1.000   | 0.769  | 0.870 |
| Overall |   0.838   | 0.838  | 0.838 |
+---------+-----------+--------+-------+
+--------------------------------------+
|              HMM Hindi               |
+---------+-----------+--------+-------+
|   Tag   | Precision | Recall |   F1  |
+---------+-----------+--------+-------+
|    CC   |   0.611   | 1.000  | 0.759 |
|    DM   |   0.400   | 0.500  | 0.444 |
|    JJ   |   0.526   | 0.833  | 0.645 |
|   NEG   |   0.667   | 0.400  | 0.500 |
|    NN   |   0.795   | 0.729  | 0.761 |
|   NNP   |   0.688   | 0.440  | 0.537 |
|   NST   |   0.909   | 1.000  | 0.952 |
|    PR   |   0.707   | 0.815  | 0.757 |
|   PSP   |   0.783   | 0.979  | 0.870 |
|  PUNCT  |   0.879   | 0.718  | 0.791 |
|   QTC   |   0.667   | 1.000  | 0.800 |
|   QTF   |   0.750   | 0.667  | 0.706 |
|    RB   |   1.000   | 0.333  | 0.500 |
|    RP   |   0.778   | 0.368  | 0.500 |
|   VAUX  |   0.651   | 0.824  | 0.727 |
|    VM   |   0.750   | 0.770  | 0.760 |
|    WQ   |   1.000   | 0.500  | 0.667 |
| Overall |   0.742   | 0.742  | 0.742 |
+---------+-----------+--------+-------+
```
## Performance of CRF
```
+--------------------------------------+
|             CRF English              |
+---------+-----------+--------+-------+
|   Tag   | Precision | Recall |   F1  |
+---------+-----------+--------+-------+
|   ADJ   |   0.857   | 1.000  | 0.923 |
|   ADP   |   1.000   | 0.933  | 0.966 |
|   ADV   |   0.850   | 0.895  | 0.872 |
|   AUX   |   1.000   | 1.000  | 1.000 |
|  CCONJ  |   1.000   | 1.000  | 1.000 |
|   DET   |   0.982   | 1.000  | 0.991 |
|   NOUN  |   0.952   | 0.962  | 0.957 |
|   NUM   |   1.000   | 0.875  | 0.933 |
|   PART  |   0.444   | 0.800  | 0.571 |
|   PRON  |   1.000   | 0.929  | 0.963 |
|  PROPN  |   0.980   | 0.906  | 0.941 |
|  PUNCT  |   1.000   | 1.000  | 1.000 |
|  SCONJ  |   0.250   | 1.000  | 0.400 |
|   VERB  |   0.944   | 0.981  | 0.962 |
| Overall |   0.952   | 0.952  | 0.952 |
+---------+-----------+--------+-------+
+--------------------------------------+
|              CRF Hindi               |
+---------+-----------+--------+-------+
|   Tag   | Precision | Recall |   F1  |
+---------+-----------+--------+-------+
|    CC   |   1.000   | 0.818  | 0.900 |
|    DM   |   0.833   | 0.625  | 0.714 |
|   INTF  |   1.000   | 1.000  | 1.000 |
|    JJ   |   0.611   | 0.917  | 0.733 |
|   NEG   |   0.800   | 0.800  | 0.800 |
|    NN   |   0.683   | 0.835  | 0.751 |
|   NNP   |   0.410   | 0.640  | 0.500 |
|   NST   |   1.000   | 1.000  | 1.000 |
|    PR   |   0.889   | 0.738  | 0.807 |
|   PSP   |   0.960   | 1.000  | 0.980 |
|  PUNCT  |   1.000   | 0.732  | 0.846 |
|   QTC   |   1.000   | 1.000  | 1.000 |
|   QTF   |   1.000   | 0.778  | 0.875 |
|   QTO   |   1.000   | 1.000  | 1.000 |
|    RB   |   1.000   | 0.333  | 0.500 |
|    RP   |   0.929   | 0.684  | 0.788 |
|   VAUX  |   0.886   | 0.912  | 0.899 |
|    VM   |   0.857   | 0.892  | 0.874 |
|    WQ   |   1.000   | 1.000  | 1.000 |
| Overall |   0.818   | 0.818  | 0.818 |
+---------+-----------+--------+-------+
```
# Observations

As we can clearly see in the above heading that CRF outperforms the HMM model in both the languages.
This is due the earlier discussed facts, since HMM assumes a degree of independence of each tag which is not particulary the case for POS tagging, i.e. a sequence of tags is more likely to occur, which is the exact case CRF handles for.

For English, a major chunk of errors is due the mistagging of proper nouns. Although CRF gets kind of close with many proper nouns being tagged as nouns and sometimes as adjectives such as tagging "secret" as an adjective in "Secret Service", HMM completely misses the mark with some proper nouns being tagged as pronouns. 
Other errors include adjective, adverb confusion and conjugation, adverb confusion. For HMM, it can be bettered a lot with better smoothing algorithms to tag unknown/unseen words. CRF models can benefit from looking at capitals of words and getting its position in the sentence.

For Hindi, a major major part was just due to mistagging of punctutation, this was due to not many punctuation marks given in the Hindi dataset as compared to English one. This is trivial to fix with any special characters being tagged as a symbol.
And the second part is that in the training set, there are a lot of proper nouns and nouns but not all the morphological variants of pronouns or adjectives etc (such as the word तेरी not being present) which lead to these unseen variants being tagged as NNP or NN. The fix would be to train on a better dataset which has more morphological variation. 
