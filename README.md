# Letter Value Sum
## r/dailyprogramming challenge [#399](https://www.reddit.com/r/dailyprogrammer/comments/onfehl/20210719_challenge_399_easy_letter_value_sum/) [EASY]
---
### Challenge
Assign every lowercase letter a value, from 1 for a to 26 for z. Given a string of lowercase letters, find the sum of the values of the letters in the string.

* lettersum("") => 0
* lettersum("a") => 1
* lettersum("z") => 26
* lettersum("cab") => 6
* lettersum("excellent") => 100
* lettersum("microspectrophotometries") => 317

### Additional Challenges
1) microspectrophotometries is the only word with a letter sum of 317. Find the only word with a letter sum of 319.
2) How many words have an odd letter sum?
3) There are 1921 words with a letter sum of 100, making it the second most common letter sum. What letter sum is most common, and how many words have it?
4) zyzzyva and biodegradabilities have the same letter sum as each other (151), and their lengths differ by 11 letters. Find the other pair of words with the same letter sum whose lengths differ by 11 letters.
5) cytotoxicity and unreservedness have the same letter sum as each other (188), and they have no letters in common. Find a pair of words that have no letters in common, and that have the same letter sum, which is larger than 188 (There are two such pairs, and one word appears in both pairs).
6) The list of word { geographically, eavesdropper, woodworker, oxymorons } contains 4 words. Each word in the list has both a different number of letters, and a different letter sum. The list is sorted both in descending order of word length, and ascending order of letter sum. What's the longest such list you can find?
---
### Building
Run CMake to configure the project and generate a native build system:

`cmake -S . -B bin`

Call the build system:

``cmake --build bin``

### Running
`./bin/letter_value_sum`

#### Program example
```
Welcome to Lettersum - r/dailyprogrammer challenge #399 [EASY]!
----------------
Write something: 
=> Sum of word '' is 0
Do you want to repeat? [ENTER/Y]es [N]o: 
----------------
Write something: a
=> Sum of word 'a' is 1
Do you want to repeat? [ENTER/Y]es [N]o: 
----------------
Write something: z  
=> Sum of word 'z' is 26
Do you want to repeat? [ENTER/Y]es [N]o: 
----------------
Write something: cab
=> Sum of word 'cab' is 6
Do you want to repeat? [ENTER/Y]es [N]o: 
----------------
Write something: excellent
=> Sum of word 'excellent' is 100
Do you want to repeat? [ENTER/Y]es [N]o: 
----------------
Write something: microspectrophotometries
=> Sum of word 'microspectrophotometries' is 317
Do you want to repeat? [ENTER/Y]es [N]o: n
Quitting...
```

---

### TODO
1. additional challenge #1-6
---