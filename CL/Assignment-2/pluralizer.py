import re

def preserve_case(original: str, result: str):
    if original.isupper():
        return result.upper()
    elif original[0].isupper() and original[1:].islower():
        return result.capitalize()
    else:
        return result


def make_plural(word: str) -> str:
    word_lower = word.lower()

    reg_to_add = {"(?:s|sh|ch|x|z)$": "es", "[aeiou]y$": "s"}    
    reg_to_replace = {"(?:f|fe)$": "ves", "us$": "i", "(?<=[^aeiou])y$": "ies"}
    compound_words = {
        "mother-in-law": "mothers-in-law",
        "attorney-at-law": "attorneys-at-law",
        "court-martial": "courts-martial",
        "runner-up": "runners-up",
        "brother-in-law": "brothers-in-law"
    }
    irregular_plurals = {
        "child": "children",
        "man": "men",
        "woman": "women",
        "person": "people",
        "mouse": "mice",
        "goose": "geese",
        "tooth": "teeth",
        "foot": "feet",
        "ox": "oxen",
        "louse": "lice",
        "die": "dice",
        "cactus": "cacti",
        "analysis": "analyses",
        "thesis": "theses",
        "crisis": "crises",
        "phenomenon": "phenomena",
        "criterion": "criteria",
        "appendix": "appendices",
        "index": "indices",
        "matrix": "matrices",
        "vertex": "vertices",
        "radius": "radii",
        "stimulus": "stimuli",
        "bacterium": "bacteria",
        "curriculum": "curricula",
        "datum": "data",
        "alumnus": "alumni"
    }
    same_singular_plural = ["sheep", "deer", "fish", "species", "series"]
    o_exceptions = ["photo", "piano", "halo", "solo", "zero"]
    f_exceptions = ["roof", "belief", "chef", "chief", "cliff"]

    if word_lower in same_singular_plural:
        return word

    if word_lower in compound_words:
        return preserve_case(word, compound_words[word_lower])

    if word_lower in irregular_plurals:
        return preserve_case(word, irregular_plurals[word_lower])
    
    if word_lower in f_exceptions:
        return preserve_case(word, word + "s")

    for reg, add in reg_to_add.items():
        if re.search(reg, word):
            return preserve_case(word, word + add)
        
    for reg, replace in reg_to_replace.items():
        if re.search(reg, word):
            return preserve_case(word, re.sub(reg, replace, word))

    if re.search("o$", word_lower):
        if word_lower in o_exceptions or re.search("[aeiou]o$", word_lower):
            return preserve_case(word, word + "s")
        else:
            return preserve_case(word, word + "es")


    return preserve_case(word, word + "s")