with open("Nouns & Verbs.txt", "r") as f:
    words = f.read().rsplit()

with open("Nouns & Verbs_changed.txt", "w") as f:
    for i, w in enumerate(words):
        f.write(r"\begin{hindi} " + w + r" \end{hindi}")
        if (i+1) % 7 == 0 and i != 0:
            f.write(" \\\\ \\hline \n")
        else:
            f.write(" & ")
