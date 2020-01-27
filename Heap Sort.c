#include <stdio.h>;
#define SIZE 9
int A[SIZE] = {24,13,26,1,2,27,38,15,10};
void print_array(int *, int);
void hsort(void);
void ins(int x);
void swap(int i, int j);
int del(void);
static n = 0;
void main(void)
{
printf(&quot;Original: \n&quot;);
print_array(A, SIZE);
hsort();
printf(&quot;\nSorted: \n&quot;);
print_array(A, SIZE);
}
void hsort()
{
int i;
for(i = 0; i &lt; SIZE; i++) // n
ins(A[i]); // log n
for(i = SIZE - 1; i &gt;=0; i--) // n
A[i] = del(); // log n
}
int del(void)
{
int p, cl, cr;
int temp;
temp = A[0]; // delete the root (to return it)
A[0] = A[n - 1]; // swap root with the last node
n--;
// starting at the root,
// swap the parent node with the smaller child node,
// until the parent is smaller than either child
// (tricky part is making sure children exist)


p = 0; cl = 2 * p + 1; cr = 2 * (p + 1);
while(1) {
// determine how many children
if(cr + 1 &lt;= n) { // two children
// is one of the children smaller than parent?
if(A[p] &gt; A[cl] || A[p] &gt; A[cr]){
// swap parent with smaller child
if(A[cl] &lt; A[cr]) {
swap(p, cl);
p = cl;
} else {
swap(p, cr);
p = cr;
}
cl = 2 * p + 1; cr = 2 * (p + 1);
} else
break;
} else if(cl + 1 &lt;= n) { // one child
// is this only child smaller than parent?
if(A[p] &gt; A[cl])
swap(p, cl);
break; // (at bottom of tree)
} else // no children
break; // (at bottom of tree)
}
return temp;
}
void ins(int x)
{
int p, c;
c = n;
p = (n-1)/2;
A[n] = x; // insert at next position
// swap the child with the parent
// until the parent is smaller than the child
while(A[p] &gt; A[c]) {
swap(p, c);
c = p;
p = (c - 1)/2;
}
n++; // increment next position


}
void swap(int i, int j)
{
int temp;
temp = A[i];
A[i] = A[j];
A[j] = temp;
}
void print_array(int * X, int)
{
for(int i=0; i&lt;SIZE; i++)
printf(&quot;%d \t&quot;, X[i]);
printf(&quot;\n&quot;);
}
