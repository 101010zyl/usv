#include<stdio.h>
struct Key{
   char* keyword;
   int keyno;
};
void main()
{
   struct Key kd[]={{"are",123},{"my",456},{"you",789}};
   struct Key *p;
   char chr;

   p = kd;
   chr = *p->keyword;
   printf("p=%d,chr=%c(adr+%d)",p,chr,p->keyword);

   chr = *p->keyword++;
   printf("p=%d,chr=%c(adr+%d)",p,chr,p->keyword);

   chr =(*p->keyword)++;
   printf("p=%d,chr=%c(adr+%d)",p,chr,p->keyword);

   chr =*p++->keyword;
   printf("p=%d,chr=%c(adr+%d)",p,chr,p->keyword);

   chr =*++p->keyword;
   printf("p=%d,chr=%c(adr+%d)",p,chr,p->keyword);
}

