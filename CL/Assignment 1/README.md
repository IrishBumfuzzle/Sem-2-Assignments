# CL Assignment 1
Description of everything done for each subtask.

## Basic Cleaning
- **Removing extra whitespace**: Match space at the beginning and end of line, spaces which have a space ahead of them and remove them. ***EXTRA:*** Also removing empty lines  
- **Convert text to lowercase**: No way of doing with regex without manually writing the A: a mapping so .lower() used  
- **Removing special characters**: The special characters removed are `$%^&\*()_+=~. ***EXTRA***: There is also an occurence of '--' in the corpus which is removed
- **Handle common abbreviation**: The abbreviations handled are [won't, can't, i'm, (any n't ending abbreviation *except ain't*), you/i/they've, she/he/there/that's, you/we/they're]

## Advanced Cleaning
- **Remove HTML tags**: Removing anything between < > remove any HTML tag but may have consequences if text has math stuff or French quotation marks but the dataset doesn't have any
- **Placeholders**:  
    - **Mail Ids**: Match any string that has atleast one character before an '@' and one character before and after a '.'
    - **URL**: *Assumes that a url either starts with a www/https or ends with a .com/a two letter domain ending since matching any 3 letter TLD may lead to matching of file names which is not desirable. Also corpus has no URLs.* Makes sure before matching that after TLD there is a space.
    - **Hashtags**: Match anything after a '#'
    - **Mentions**: Makes sure there is a whitespace before '@' to prevent mail IDs from being matches and matches anything after that.
- **Standardize quotation**: FIX
- **Standardize ellipses**: Matches any '.' with a space before it ***EXTRA***: Removes spaces after sentence fullstops.

## Basic Tokenization

- **Sentence Tokenization**: Splits based on the sentence ending with '!?.' with the optional inclusion of '"', does not split the sentence if there is a mr/dr/mrs behind.

- **Word Tokenization**: Splits on the occurence of whitespace character. Stops the word from splitting if there is a punctuation between two digits to handle for dates and numbers. Does not split word for abbreviations such mr., mrs., dr.