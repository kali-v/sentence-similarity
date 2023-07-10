# Sentence similarity

Hashing table-based solution for the sentence similarity problem, achieving near-linear time complexity - considering 0 and 1 distances (distance-1 defined as "addition or deletion of a single word" with input from dist-0)

compile using:
`g++ main.cc hashtable.cc -Ofast -funroll-all-loops -fopenmp -o main`


## Distance 0

Hash is computed using `(31 · hash + 7 · c) mod cap`, while iterating over the sentence
- hash is the current value of hash
- c is the current character in the sentence
- the cap is big number limiting overflow.

The sentence is sent to output only if a computed hash appears for the first time.

## Distance 1

When processing a sentence, we stored a several pieces of information: the number of words,
the number of characters, and the sum of the character values in the first and second parts of the
sentence. We know that distance-1 sentences can only be obtained by adding or removing
a single word. Therefore, to find distance-1 sentences for any given sentence, we will focus on
sentences that have one more or one fewer word than the original sentence. We also want to inspect
only sentences that have just a few more or fewer characters that should correspond with the change
of adding/removing a single word. With this information, we can construct our hash table. The first
level of the table will be organized based on the number of words in each sentence. In the second
level, the sentences will be divided into buckets according to: number of chars/5. This way we can
quickly filter a lot of sentences. After identifying buckets in a hash table, we iterate
over a list of hashes, and we declare sentences are distance-1 iff the sum of chars is equal for one-half
of the sentences, and the difference in sums of characters in the whole sentence differs by <600.
