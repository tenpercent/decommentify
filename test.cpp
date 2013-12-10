#include <iostream>

using std::cin;

int main() {
// test cpp single comment line
c
//.............................................
c
// test cpp multi comment line
c
//.............................................\
...............................................\
...............................................
c
// test cpp multi comment line with text
c
test cpp multi comment line with text //.......\
...............................................\
...............................................
c
// test c comment
c
/*.............................................*/
c
// test c comment on multiple lines
c
/*.............................................
...............................................
...............................................
.............................................*/
c
// test c comment on multiple empty lines
c
/*


*/
/**/
c
// test c comment many times on a line
c
/*...*/test c comment/*.....*/ many times on a line
c
test c comment/*.....*/ many times on a line/*....*/
c
// test mixed comment 1
c
/*.....*/test mixed comment 1 //.................
c
// test mixed comment 2
c
test /*....*/mixed comment 2 //..................
// test mixed comment 3
c
test /*....*/mixed comment 3 //..................\
.................................................
c
// test nested
c
/*.....//...//......*/test nested//.../*test*//..
с
// test quote
с
"test quote"//...................................
с
// test comment inside quote 
"test // comment inside quote"/*.......*///......
с
"test /* comment inside quote"
с
"test // \" // comment inside quote"
с
// weird cases
// one
/\
*
weird multi line comment
*\
/
// two
/\
/\
you must be asshole to write such comments though it's correct
}
