# Random Composition Generator

- - This was a project I made in Year 12 to troll my music teacher. I used it to randomly generate parts of compositions for some of our tasks, which ended up being an interesting challenge composing with non-standard chord changes.
- - The project also ended up leading into an interesting discussion about training AI on my compositions only, then using it to generate new ones.
  - It runs in C++ and uses a similar console interface to the Enigma Machine. Warning, it takes a lot of memory.
  - The high memory usage is due to an 11(?) dimensional array that I used to HARD CODE the allowed progressions and flowcharts in the code.
  - Looking back, a tree would have been a more appropriate data structure...
  - It is unfinished, but if I were to rewrite it I would add an interface and remove that horrible array.
  - I hardcoded far too much here, and it runs extremely slowly as a result.
