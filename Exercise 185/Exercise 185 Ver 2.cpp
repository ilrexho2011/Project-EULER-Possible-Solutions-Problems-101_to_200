#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

const int LINES=22;
const int COLS=16;
struct guess_data
{
   int correct;
   char digits[COLS];
} guess_data_obj[LINES]=
{
   {0,{2,3,2,1,3,8,6,1,0,4,3,0,3,8,4,5}}, ///0 correct
   {1,{4,8,9,5,7,2,2,6,5,2,1,9,0,3,0,6}}, ///1 correct
   {1,{3,8,4,7,4,3,9,6,4,7,2,9,3,0,4,7}}, ///1 correct
   {1,{3,1,7,4,2,4,8,4,3,9,4,6,5,8,5,8}}, ///1 correct
   {1,{6,3,7,5,7,1,1,9,1,5,0,7,7,0,5,0}}, ///1 correct
   {1,{6,9,1,3,8,5,9,1,7,3,1,2,1,3,6,0}}, ///1 correct
   {1,{8,1,5,7,3,5,6,3,4,4,1,1,8,4,8,3}}, ///1 correct
   {3,{1,7,4,8,2,7,0,4,7,6,7,5,8,2,7,6}}, ///3 correct
   {3,{1,8,4,1,2,3,6,4,5,4,3,2,4,5,8,9}}, ///3 correct
   {3,{3,0,4,1,6,3,1,1,1,7,2,2,4,6,3,5}}, ///3 correct
   {3,{4,2,9,6,8,4,9,6,4,3,6,0,7,5,4,3}}, ///3 correct
   {3,{5,8,5,5,4,6,2,9,4,0,8,1,0,5,8,7}}, ///3 correct
   {3,{7,8,9,0,9,7,1,5,4,8,9,0,8,0,6,7}}, ///3 correct
   {3,{8,6,9,0,0,9,5,8,5,1,5,2,6,2,5,4}}, ///3 correct
   {3,{9,7,4,2,8,5,5,5,0,7,0,6,8,3,5,3}}, ///3 correct
   {2,{2,3,2,6,5,0,9,4,7,1,2,7,1,4,4,8}}, ///2 correct
   {2,{2,6,1,5,2,5,0,7,4,4,3,8,6,8,9,9}}, ///2 correct
   {2,{2,6,5,9,8,6,2,6,3,7,3,1,6,8,6,7}}, ///2 correct
   {2,{4,5,1,3,5,5,9,0,9,4,1,4,6,1,1,7}}, ///2 correct
   {2,{5,2,5,1,5,8,3,3,7,9,6,4,4,3,2,2}}, ///2 correct
   {2,{5,6,1,6,1,8,5,6,5,0,5,1,8,2,9,3}}, ///2 correct
   {2,{6,4,4,2,8,8,9,0,5,5,0,4,2,7,6,8}}, ///2 correct
};

char solution[COLS+1];
struct guessed_digit
{
   int line, digit;
   bool impossible_digits_map[LINES][10];
   guessed_digit()
   {
      this->line=this->digit=-1;
      memset(impossible_digits_map,false,sizeof(impossible_digits_map));
   }
   void assume_correct(int line, int digit)
   {
      this->line=line;
      this->digit=digit;
   }
   void assume_incorrect()
   {
      this->impossible_digits_map[this->line][this->digit]=true;
      this->line=-1;
      this->digit=-1;
   }
} guessed_digits[COLS];

inline int set_impossible_digits(int line)
{
   int i=-1, nt=0;
   while (++i<COLS)
   {
      int digit=guess_data_obj[line].digits[i];
      if (guessed_digits[i].digit<0)
      {
         guessed_digits[i].impossible_digits_map[line][digit]=true;
      }
      else if (guessed_digits[i].digit==digit)
         ++nt;
   }
   return nt;
}
inline void unset_impossible_digits(int line)
{
   int i=-1;
   while (++i<COLS)
   {
      if (guessed_digits[i].digit<0)
      {
         int digit=guess_data_obj[line].digits[i];
         guessed_digits[i].impossible_digits_map[line][digit]=false;
      }
   }
}
struct corrector
{
   guessed_digit* pgd;
   int line, col, nt;
   corrector(int line, int col)
   {
      this->pgd=guessed_digits+col;
      this->line=line;
      this->col=col;
      int digit=guess_data_obj[line].digits[col];
      pgd->assume_correct(this->line, digit);
      solution[this->col]=0x30+digit;
      this->nt=set_impossible_digits(this->line);
   }
   ~corrector()
   {
      solution[this->col]='.';
      this->pgd->assume_incorrect();
      unset_impossible_digits(this->line);
   }
};

struct impossible_digits_resetter
{
   int line;
   impossible_digits_resetter(int line) { this->line=line; }
   ~impossible_digits_resetter()
   {
      int i=-1;
      while (++i<COLS)
         memset(guessed_digits[i].impossible_digits_map[this->line],false,10);
   }
};

inline bool is_impossible(int line, int col)
{
   int i=-1;
   int digit=guess_data_obj[line].digits[col];
   while (++i<line)
   {
      if (guessed_digits[col].impossible_digits_map[i][digit]!=false)
         return true;
   }
   return false;
}
inline bool is_already_guessed(int col)
{
   return guessed_digits[col].line>=0; // already guessed
}
bool is_found()
{
   int i=-1;
   while (++i<COLS)
   {
      if (guessed_digits[i].line<0)
      {
         int j=-1, k=0;
         bool a[10]={false};
         while (++j<LINES)
         {
            int digit=guess_data_obj[j].digits[i];
            k+=a[digit]==false;
            a[digit]=true;
         }
         if (k==9)
         {
            j=-1;
            while (++j<10 && a[j]!=false)
               ;
            guessed_digits[i].line=LINES;
            guessed_digits[i].digit=j;
            solution[i]=0x30+j;
            continue;
         }
         return false;
      }
   }
   return true;
}
int f185(const int line);
int f185a(const int line, const int digits_to_guess, const int* pinx, const int ninx)
{
   int correct_digits=guess_data_obj[line].correct;
   int i=-1;
   while (++i<ninx-digits_to_guess+1)
   {
      corrector c(line, pinx[i]);
      if (c.nt>correct_digits) // sanity check
         continue;
      if (digits_to_guess>1)
      {
         int return_line=f185a(line, digits_to_guess-1, pinx+i+1, ninx-i-1);
         if (return_line<line)
            return return_line;
      }
      else
      {
         int return_line=f185(line+1);
         if (return_line<line)
            return return_line;
      }
   }
   return line-1;
}
int f185(const int line=0)
{
   if (line==LINES)
   {
      printf("found -- %s\n",solution);
      if (is_found())
      {
         return -1;
      }
      else
         return -1;
   }
   impossible_digits_resetter impossible_digits_resetter_obj(line);
   int correct_digits=guess_data_obj[line].correct;
   int i=-1, digits_left=0, digits_to_guess=correct_digits;
   int a[COLS]; // available positions
   while (++i<COLS)
   {
      if (is_already_guessed(i))
      {
         if (guessed_digits[i].digit == guess_data_obj[line].digits[i])
            --digits_to_guess;
      }
      else
      {
         if ( !is_impossible(line, i) ) // possible to guess?
            a[digits_left++]=i; // this one may be be guessed
      }
   }
   if (digits_to_guess<0 || digits_left<digits_to_guess)
      return line-1;
   if (digits_left==0) // no digits left to guess
   {
      int nt=set_impossible_digits(line);
      int return_line=f185(line+1);
      if (return_line<line)
         return return_line;
      return line-1;
   }
   if (digits_to_guess==0)
   {
      int nt=set_impossible_digits(line);
      int return_line=f185(line+1);
      if (return_line<line)
         return return_line;
      return line-1;
   }
   // digits_left>=digits_to_guess>0
   int return_line=f185a(line,digits_to_guess,a,digits_left);
   if (return_line<line)
      return return_line;
   return line-1;
}

int main(int argc, char**argv)
{
   timer t;
   f185();
   return 0;
}