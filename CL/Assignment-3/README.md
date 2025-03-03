# Paradigms
There are 3 paradigms for nouns, 3 for adjectives and another 3 for verbs.
For verbs in English the general verb form works for all 1st, 2nd and 3rd person uses _except_ for 3rd person singular. For that case, the paradigm has been specified. The comments in the file specifies where past and present tenses for the verb are present.

# Dictionary
Based on the paradigms above, there are 9 nouns, 5 adjectives, and 10 verbs. The comments specify the location of each of these categories.

# Binary files
There are 2 binary files, one is the analyser which is compiled left to right for analysing morphemes and the second is the generator, compiler from right to left for generating morphemes. The tested examples are as follows:

## Nouns
### Analyser
```
$ echo "beers school computer babies child children houses schools abilities baby" | lt-proc analyser.bin

> ^beers/beer<n><pl>$ ^school/school<n><sg>$ ^computer/computer<n><sg>$ ^babies/baby<n><pl>$ ^child/child<n><sg>$ ^children/child<n><pl>$ ^houses/house<n><pl>$ ^schools/school<n><pl>$ ^abilities/ability<n><pl>$ ^baby/baby<n><sg>$
```
### Generator
```
$ echo "^beer<n><pl>$ ^child<n><pl>$ ^baby<n><pl>$ ^baby<n><sg>$" | lt-proc -g generator.bin

> beers children babies baby
```

## Adjectives
### Analyser
```
$ echo "flatter best flattest lovely loveliest" | lt-proc analyser.bin

> ^flatter/flat<adj><comp>$ ^best/good<adj><sup>$ ^flattest/flat<adj><sup>$ ^lovely/lovely<adj>$ ^loveliest/lovely<adj><sup>
```
### Generator
```
$ echo "^lovely<adj><sup>$ ^lovely<adj><comp>$ ^good<adj><comp>$ ^good<adj><sup>$" | lt-proc -g generator.bin

> loveliest lovelier better best
```

## Verbs
### Analyser
```
$ echo "walked walking doing done did forked" | lt-proc analyser.bin 

> ^walked/walk<vblex><past>/walk<vblex><pp>$ ^walking/walk<vblex><ger>$ ^doing/do<vblex><ger>$ ^done/do<vblex><pp>$ ^did/do<vblex><past>$ ^forked/fork<vblex><past>/fork<vblex><pp>$
```
### Generator
```
$ echo "^walk<vblex><ger>$ ^do<vblex><ger>$ ^do<vblex><past>$ ^do<vblex><pp>$" | lt-proc -g generator.bin 

> walking doing did done
```