import re

def basic_cleaning(fileName='sample.txt') -> str:
    with open(fileName, 'r') as file:
        text = file.read()
        
        text = text.lower() # converts text to lowercase
        text = re.sub(r"--|[`$%^&*()_+=~]", " ", text) # Remove special characters
        # Handle abbreviations
        text = re.sub(r"won't", "will not", text)
        text = re.sub(r"can't", "cannot", text)
        text = re.sub(r"i'm", "i am", text)
        text = re.sub(r"(?<!ai)n't", " not", text)
        text = re.sub(r"(you|i|they)'ve", r"\1 have", text)
        text = re.sub(r"(she|he|there|that)'s", r"\1 is", text)
        text = re.sub(r"(you|we|they)'re", r"\1 are", text)

        text = re.sub(r"^\s+| +$| +(?= )|^\n", "", text, flags=re.MULTILINE) # removes leading, trailing and multiple spaces

        return text
        
    
def advanced_cleaning(text) -> str:
    text = re.sub(r"<[^>]*>", "", text) # removes html tags

    # PLACEHOLDERS
    text = re.sub(r"\b\w+@\w+\.\w+", "<MAIL>", text) # removes email addresses
    text = re.sub(r"(https?://|www\.)?(?(1).+|[A-z]+\.(?:[A-z]{2}|com)(?=\s))", "<URL>", text) # removes URLs
    text = re.sub(r"#[\S]+", "<HASHTAG>", text) # removes hashtags
    text = re.sub(r"(?<=\s)@[\S]+", "<MENTION>", text) # removes mentions

    text = re.sub(r"’+|“|”|``|'(?=\s)|(?<=\s)'", '"', text) # replaces different types of quotes with ", including the single quote ' with space before or after 
                                                          # indicating that it was not part of a contraction
    
    text = re.sub(r" \.", ".", text) # Standardises ellipses with the added benefit of removing space before fullstops

    return text

text = basic_cleaning()
text = advanced_cleaning(text)

print(text)