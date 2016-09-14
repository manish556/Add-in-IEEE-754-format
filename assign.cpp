
#include<iostream>
#include<math.h>
#include<fstream>
#include<cmath>

using namespace std;

int main()
{
    int index=1,success=0,counter=0;
    unsigned int x,y,z;
   
    fstream ifile;
    ifile.open("input.txt");

while(1)
{
    ifile>>index;
    if(!ifile)
       break;
    ifile>>hex>>x;
    ifile>>hex>>y;
    ifile>>hex>>z;

      unsigned int sum;
      int sign,sign1,final_sign,exp,exp1,mentissa,mentissa1,mentissa_sum,significand,significand1,significand_sum;

      sign=((x & 0x80000000)>>31);
      sign1=((y & 0x80000000)>>31);
      exp=((x & 0x7f800000)>>23);
      exp1=((y & 0x7f800000)>>23);
      mentissa=(x & 0x007fffff);
      mentissa1=(y & 0x007fffff);
      significand=mentissa+pow(2,23);
      significand1=mentissa1+pow(2,23);


      int final_exp,sticky;

   if(abs(exp-exp1)>25 || min(x,y)==0)
    {
     sum=exp>exp1?x:y;
    }

   else
    {
        significand=(significand<<6);
        significand1=(significand1<<6);
      if(exp>exp1)
      {
          final_exp=exp;

          if (exp-exp1>6)
          {
              int flag=0;
              flag=significand1&(int)(pow(2,exp-exp1-6)-1);
              significand1=(significand1>>(exp-exp1));
              if(flag>0)
              {
                  if(significand1%2==0)
                  significand1+=1;
              }

          }
          else
          {
              significand1=(significand1>>(exp-exp1));
          }

      }
      else if(exp1>exp)
      {
          final_exp=exp1;
          if (exp1-exp>6)
            {
              int flag=0;
              flag=significand&(int)(pow(2,exp1-exp-6)-1);
              significand=(significand>>(exp1-exp));
              if(flag>0)
              {
                  if(significand%2==0)
                  significand+=1;
              }
            }
          else
          {
              significand=(significand>>(exp1-exp));
          }
      }

      else
      {
          final_exp=exp;
      }

      significand=significand*pow(-1,sign);
      significand1=significand1*pow(-1,sign1);

      significand_sum=significand+significand1;

      if(significand_sum<0)
          final_sign=1;
      else
          final_sign=0;

      significand_sum=significand_sum*pow(-1,final_sign);

      if(significand_sum>=pow(2,30))
      {
        sticky=(significand_sum&(int)(pow(2,7)-1));
        significand_sum=(significand_sum>>7);
        final_exp+=1;
        if( sticky>pow(2,6) || ( sticky==pow(2,6) && significand_sum%2==1 ) )
        {
          significand_sum+=1;
          if(significand_sum>=pow(2,24))
           {
              significand_sum=(significand_sum>>1);   // last bit must be 0 this time
              final_exp+=1;
           }
        }
      }

      else
       {
          if(significand_sum<pow(2,29))  // make 30 bit word
          {
            int shift=0;
            while(significand_sum<pow(2,29))
            {
              significand_sum=(significand_sum<<1);
              shift++;
            }
            final_exp-=shift;
          }

           sticky=(significand_sum&(int)(pow(2,6)-1));
           significand_sum=(significand_sum>>6);
           if( sticky>pow(2,5) || ( sticky==pow(2,5) && significand_sum%2==1 ) )
           {
               significand_sum+=1;
               if(significand_sum>=pow(2,24))
                {
                 significand_sum=(significand_sum>>1);   // last bit must be 0 this time
                 final_exp+=1;
                }
           }
       }

     mentissa_sum=significand_sum-pow(2,23);

     sum=mentissa_sum;
    // cout<<"ment "<<mentissa_sum<<" exp "<<final_exp<<" sign "<<sign<<endl;
     sum=sum+(final_exp*pow(2,23))+(final_sign*pow(2,31));

   }   // end of else

   //  cout<<" a"<<final_exp<<endl;

     if(z==sum)
     {
         cout<<"Test "<<++counter<<" PASSED\n";
         success++;
     }
     else
     {
         cout<<"Test "<<++counter<<" FAILED\n";
     }

}// end of while

   cout<<"Total "<<success<<" PASSED "<<counter-success<<" FAILED\n";

   return 0;
}
