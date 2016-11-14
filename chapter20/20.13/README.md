Notice
======

The `dictionaries` subdirectory contains six dictionaries for testing
the solution presented here. A dictionary file named `dictionary-N.txt` contains
(approximately) `N` words, one per line.

The solution implemented uses backtracking similarly to what is described
in [this page](http://stackoverflow.com/a/8515078). On an Intel i5-4210U CPU, the
following execution times were observed:

| Dictionary size (words) | Execution time |
|-------------------------|----------------|
| 100                     | < 0.005s       |
| 1000                    | ~0.02s         |
| 10000                   | ~2s            |
| 20000                   | 1min           |
| 50000                   | 9min           |
| 100000                  | 40min          |
