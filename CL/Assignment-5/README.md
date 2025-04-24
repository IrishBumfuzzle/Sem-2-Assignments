# NER Model
## Classification Report:
```
              precision    recall  f1-score   support

       B-LOC       0.30      0.60      0.40         5
      B-MISC       0.25      0.12      0.17         8
       B-ORG       0.21      0.17      0.19        18
       B-PER       0.42      0.33      0.37        30
       I-LOC       0.00      0.00      0.00         5
      I-MISC       0.00      0.00      0.00         5
       I-ORG       0.40      0.59      0.48        17
       I-PER       0.50      0.75      0.60        12
           O       0.93      0.94      0.93       442

    accuracy                           0.83       542
   macro avg       0.33      0.39      0.35       542
weighted avg       0.82      0.83      0.82       542
```

## Common Error Patterns
From the confusion matrix:

B-ORG often → O or B-PER

B-PER sometimes → B-ORG or O

B-MISC almost always → O

Rare classes (LOC, MISC) have almost zero I-recall.
This indicates the model struggles both to decide where an entity begins and what type it is.

1. Boundary Errors: Missing B-tags (false negatives) but catching interior tokens → over-extension without a proper start.
2. Type Confusion: ORG ↔ PER confusion: e.g. “Apple” labeled as PER or O.
3. Data Sparsity: LOC and MISC under-represented, yielding zero I-tag predictions.

## Improvements
External Knowledge: Leverage publicly-available gazetteers (e.g. lists of organizations, locations) or Wikipedia anchors.

Contextualized Pretraining: Fine-tune contextual models on the named domains to better disambiguate entity types.


# Chunking Model
## Classification Report:
```
              precision    recall  f1-score   support

        B-PP       0.00      0.00      0.00         0
        B-NP       0.74      0.23      0.35       151
        I-NP       0.31      0.95      0.46       130
        B-VP       0.91      0.12      0.22        80
           O       0.36      0.03      0.05       148
        I-VP       0.00      0.00      0.00         1
      B-ADVP       0.00      0.00      0.00         0
      B-SBAR       0.00      0.00      0.00         0
      B-ADJP       0.00      0.00      0.00        27
       B-PRT       0.00      0.00      0.00         0
        I-PP       0.00      0.00      0.00         0
      I-ADJP       0.00      0.00      0.00         4
      I-SBAR       0.00      0.00      0.00         0
      I-ADVP       0.00      0.00      0.00         0
     B-CONJP       0.00      0.00      0.00         0
     I-CONJP       0.00      0.00      0.00         0
       B-LST       0.00      0.00      0.00         0
      B-INTJ       0.00      0.00      0.00         0
      I-INTJ       0.00      0.00      0.00         0
       I-PRT       0.00      0.00      0.00         0
       B-UCP       0.00      0.00      0.00         0
       I-UCP       0.00      0.00      0.00         0

   micro avg       0.32      0.32      0.32       541
   macro avg       0.11      0.06      0.05       541
weighted avg       0.52      0.32      0.26       541
```

## Error Analysis
NP boundaries (B-NP) high precision (74 %) but very low recall (23 %) → model only mark starts when model’s extremely confident, missing 77 % of NPs.

NP interiors (I-NP) complementary: model over-mark interior tokens (95 % recall) but low precision (31 %) → model absorb too many tokens into NPs.

VP boundaries (B-VP) follow the same pattern: conservative start detection (high P, low R).

The “interior” rules (once a chunk is begun) do a good job of swallowing all the right tokens, hence the high I-* recall.

The “start” rules—likely based on single POS cues like “DT NN” for NPs or “VB” for VPs—are too narrow, missing many valid chunk heads.

### Challenging Scenarios
**Nested Constituents**
E.g. NP → NP PP (“the edge [of the table]”) often splits incorrectly at the PP.

**Coordination**
“NP and NP and NP” sequences require careful B-NP / I-NP alternation around conjunctions.

**Rare Chunk Types**
ADJP, ADVP, SBAR almost never found, the rule set lacks coverage for these

## Improvements
Handle Rare Types: Either collapse very rare chunk labels into an “OTHER” category or write specific rules for ADJP (e.g. JJ+ sequences) and SBAR (subordinating conjunctions).

Post-processing Constraints: Enforce that every B-* is followed by at least one I-* or proper transition to O, to avoid zero-length chunks.


