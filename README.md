# DecafCompiler
A compiler for Decaf Language.

Specifications of Grammer can be seen in Decaf Manual.pdf

decaf.l contails tokenizer and decaf.y contails grammer for Decaf Programming Language.

To compile => Enter `make -B` in terminal

To run => Enter `./a.out <inputFileName>`

After running you will see "Success" or "Syntax Error" as output.

docker run -it -v /Users/chandan5/Projects/DecafCompiler:/DecafCompiler ubuntu14.04:llvm-flex-bison

If you see "Success" `bison_output.txt` will contain the order in which non-terminals were found.
