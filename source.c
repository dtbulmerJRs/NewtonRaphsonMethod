/* Onur YILMAZ		*/


#include <stdio.h>
#include <math.h>

int main (void)
{

	int selector; 			/* selector for calculating n,L,p or r	*/
	double oku[3];

	/* function prototypes for calculators			*/	
	void loan_f(double month,double payment,double interest);
	void month_f(double loan, double payment, double interest);
	void payment_f(double loan, double month, double interest);
	void interest_f(double loan, double month, double payment);

	/* read data from standard input */
	scanf(" %d", &selector);
	scanf(" %lf", &oku[0]);
	scanf(" %lf", &oku[1]);
	scanf(" %lf", &oku[2]);


/* cases for calculating	*/
switch (selector) {

case 1:
loan_f(oku[0],oku[1],oku[2]);
break;

case 2:
month_f(oku[0],oku[1],oku[2]);
break;

case 3:
payment_f(oku[0],oku[1],oku[2]);
break;

case 4:
interest_f(oku[0],oku[1],oku[2]);
break;

default:
break;
}


return 0;

/* end of main function */
}


/* function for calculating total loan with the given parameters: month, payment and interest rate 	*/

void loan_f(double month,double payment,double interest) 

{

		double epsilon, epsilon_ust_n, loan;

		epsilon=interest+1.0; 		        /* for simplifying the final "loan equation"	*/ 
		epsilon_ust_n=pow(epsilon, month); 	/* for simplifying the final "loan equation"	*/

		loan= ( ( (epsilon_ust_n-1.0) *payment )/(epsilon-1.0) ) / epsilon_ust_n; 	/* loan equation (gathered directly from question)	*/
		printf("%f", loan);

return;
}



/* function for calculating total number of months with the given parameters: loan, payment and interest rate 	*/

void month_f(double loan, double payment, double interest)

{
		double epsilon, month;

		epsilon=interest+1.0;		/* for simplifying the final "month equation"	*/ 

		month= - log (1- interest*loan/payment) / log(epsilon);		/* equation for number of months (calculated by taking natural logarithm of both sides */
		printf("%f", month);	

return;
}



/* function for calculating the payment with the given parameters: loan, months and interest rate 	*/

void payment_f(double loan, double month, double interest) 

{
		double epsilon, epsilon_ust_n, payment;

		epsilon=interest+1.0;				/* for simplifying the final "payment equation"	*/ 
		epsilon_ust_n=pow(epsilon, month);		/* for simplifying the final "payment equation"	*/ 


		payment= (loan*epsilon_ust_n*(epsilon-1.0)) / (epsilon_ust_n-1.0); 	/* payment equation (directly taken from question)	*/
		printf("%f", payment);

return;
}


/* function for calculating the interest rate with the given parameters: loan, months and payment 			*/
/* In this function Newton–Raphson method is used for finding the root of equation					*/
/* All the implementation and information about the method is gathered from en.wikipedia.org/wiki/Newton's_method	*/

void interest_f(double loan, double month, double payment) 

{

		double normal, fark, turevli;		
		double next,simdi;			/* next is used for the number which will be used in next iteration, whereas "simdi" for the current iteration */
		int flag;				/* flag for the loop of iterations	*/
		
		flag=1;				
		simdi=1; 				/* an arbitrary number for the first iteration, 1 is taken considering it is a interest rate */
		

		while(flag)

{
		/* 'simdi' is used in equations instead of interest rate(r) for iteration		*/	
		/* original equation which have a "zero equality" in the question			*/
		normal= pow(1+simdi,month)*loan-payment*(pow(1+simdi,month)-1)/simdi;
		
		/* derivative of the original function (calculated by quotient and chain rule)		*/
		turevli= loan*month*pow(simdi+1, month-1) + payment*simdi*simdi*(-month*simdi*pow(simdi+1,month-1)+pow(simdi+1,month)-1);

		/* iteration for the next value of interest rate */
		/* according to the method, it is found by subtracting f(x)/df(x) from the current iteration	*/
		next=simdi-(normal/turevli);

		/* calculating the accuracy of iteration 	*/
		fark=fabs(next-simdi)/next;
		
		/* checking whether the iteration is accurate enough 10^-5	*/
		if(fark < 0.000001) 
			{
			printf("%f",next);
			flag=0;
			}
		
		else simdi=next;
		
}
}
/* end of code */

