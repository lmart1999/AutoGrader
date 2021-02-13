/*Name: Luke Martin
 * 
 * Purpose: The purpose of this program is to find the grades and questions missed for each student, the average grade, the answers for each question and percent correct, the median, the mode, the frequency and a sorted array of the grades from highest to lowest  
 *
 * Assumption: an input file that contains student IDs, names, and answers starting on the 76th column with no more than 29 questions, 100 students, or 5 possible answer choices
 *
 * Input: an input file that contains student IDs, names, and answers starting on the 76th column with no more than 29 questions, 100 students, or 5 possible answer choices, assumes first line is the answer key
 *
 * Output: an array of students with their answers, grade, and questions missed, an array of questions with correct choices, percent correct, and amount of each choice chosen, the average grade, a sorted list of grades, the median, a sorted unique list of grades with frequencys
 *
 * Algorithm: read in file, put first line of 29 ints into answer key, read in subsequent lines and put them into 2d array, first part is for student, second for answers,
 * Compare answers recieved with key, total number of each question missed and what each student put for each question, output student with questions missed and grade, num correct/total
 * go through each question and each student and answer choice to find percent correct and which answers were chosen, use double nested for loop
 * sort the array, find the median, count the frequency of each answer, output each unique answer with its frequency by skipping non-unique answers 
 *
 * Programmer: Luke Martin
 *
 *
 *
 *
 */
#include <stdio.h>

#define MAX_STUDENTS 100
#define TOTAL_QUESTIONS 29
const int MAX_CHOICES = 5;

void readKey(int key[TOTAL_QUESTIONS]);
int readAnswer(int answer[MAX_STUDENTS][TOTAL_QUESTIONS]);
char convertChar (int ans);
void PrintKeyHeading();
void PrintAnswerHeading(void);
void outputKey(int key[], int n);
void outputData(int answer[MAX_STUDENTS][TOTAL_QUESTIONS], int miss[][TOTAL_QUESTIONS], double grade[], int n);
void findGrade(int key[TOTAL_QUESTIONS],int answer[MAX_STUDENTS][TOTAL_QUESTIONS],int miss[MAX_STUDENTS][TOTAL_QUESTIONS],int correct[TOTAL_QUESTIONS], double grade[MAX_STUDENTS],int n);
double findAvg(double grade[MAX_STUDENTS], int n);
void findQuestion(int key[TOTAL_QUESTIONS], int answer[][TOTAL_QUESTIONS],int question_response[][MAX_CHOICES+1], int question_correct[TOTAL_QUESTIONS],int n);

void outputQuestionResult(int key[TOTAL_QUESTIONS], int answer[][TOTAL_QUESTIONS], int question_correct[], int question_response[][MAX_CHOICES+1], int coint);
void sortGrades(double grade[MAX_STUDENTS], int n);
void outputSort(double grade[MAX_STUDENTS], int n);
void findFrequency(double grade[MAX_STUDENTS], int frequency[MAX_STUDENTS],int n);
void findMedian(double grade[TOTAL_QUESTIONS], int n);
void printFrequency(double grade[MAX_STUDENTS], int frequency[MAX_STUDENTS],int n);
void findMode(double grade[MAX_STUDENTS], int frequency[MAX_STUDENTS], int n);

int main(void) {
	
	char c;
	int n;
	
	int key[TOTAL_QUESTIONS];
	int answer[MAX_STUDENTS][TOTAL_QUESTIONS];
	int miss[MAX_STUDENTS][TOTAL_QUESTIONS];
	int correct[TOTAL_QUESTIONS];
	double grade[MAX_STUDENTS];
	int question_response[TOTAL_QUESTIONS][MAX_CHOICES+1];
	int question_correct[TOTAL_QUESTIONS];
	int frequency[MAX_STUDENTS];
	
	readKey(key);
	n = readAnswer(answer);
	findGrade(key, answer, miss,correct, grade, n);

	findQuestion(key, answer, question_response, question_correct, n);
	PrintKeyHeading();
	outputKey(key, n);
	PrintAnswerHeading();
	outputData(answer, miss, grade, n);
	outputQuestionResult(key, answer, question_correct, question_response, n); 
	sortGrades(grade,n);   
	outputSort(grade,n); 
	findMedian(grade, n);
	findFrequency(grade, frequency,n);	
	printFrequency(grade, frequency,n);
	findMode(grade, frequency, n );

   return 0;
} // main


/*
 *calculates class average, and percent right per question and outputs them
 *input from main: grades, num students 
 *output to main: Average
*/
double findAvg(double grade[MAX_STUDENTS], int n){
	double classAvg; 

	for(int i =0;i<n;i++) {
		classAvg = classAvg+grade[i];

	}
 	classAvg = classAvg/n;
	return classAvg;
}


/*
 *finds and prints out the mode of the set 
 *input from main: grade, grequency, num students
 *output to main: none
*/

void findMode(double grade[MAX_STUDENTS], int frequency[MAX_STUDENTS], int n){
	double mode;
	for(int i =0;i<n;i++) {
                if(frequency[i]<frequency[i+1]) 
			mode = grade[i+1];

        }
	printf("\nThe Mode is: %.2lf\n", mode);


}

/*
 *finds frequency of each grade
 *input from main: grades, frequency, num students
 *output to main: frequency
*/

void findFrequency(double grade[MAX_STUDENTS], int frequency[MAX_STUDENTS],int n){
       int i,j;
	for(i=0;i<n;i++) {

	     for(j=0;j<n;j++)
		if(grade[i]==grade[j])
	 	     frequency[i]++;	
        }

}


/*
 *prints frequency array
 *input from main: grades, frequency, num students
 *output to main: none
*/

void printFrequency(double grade[MAX_STUDENTS], int frequency[MAX_STUDENTS],int n){
       int i;
	printf("Grade\tFrequency\n");
        for(i=0;i<n;i++) {
                if(grade[i]!=grade[i+1])
       		     printf("%.2lf\t%i\n", grade[i], frequency[i]);
	 }

}



/*
 *outputs grades in descending order
 *input from main: grades
 *output to main: none
*/

void outputSort(double grade[MAX_STUDENTS], int n){
	double median;
	printf("\n\nAfter sort:\n");
	for(int i=0;i<n;i++) {
	    
	     printf("%.2lf\n", grade[i]);
	}

}

/*
 *finds and outputs median
 *input from main: grades
 *output to main: none
*/

void findMedian(double grade[MAX_STUDENTS], int n){
        double median;

        if(n%2==1){
            
             median = grade[(n+1)/2-1];
           
        }else {
	     median =(grade[n/2-1]+grade[n/2])/2;
        }

        printf("The Median is: %.2lf\n", median);
}




/*
 *Sorts grades in descending order
 *input from main: grades
 *output to main: sorted grades
*/

void sortGrades(double grade[MAX_STUDENTS], int n){
        int i,j;
        for(j=0;j<n-1;j++) {
            for(i=0;i<n-j-1;i++) {
		if(grade[i]<grade[i+1]) {
		    double temp = grade[i];
		    grade[i]=grade[i+1];
		    grade[i+1]=temp;

		}

            }
        }

}



/*
 *finds number of students that have correctly answered each question
 *input from main, num students, answers, key
 *output to main: none
*/

void findQuestion(int key[TOTAL_QUESTIONS], int answer[][TOTAL_QUESTIONS],int question_response[][MAX_CHOICES+1], int question_correct[TOTAL_QUESTIONS],int n){
	int i,j,k;
	for(j=0;j<TOTAL_QUESTIONS;j++) {
	    for(k=0;k<MAX_CHOICES+1;k++) {
		for(i=0;i<n;i++) {
		     if(answer[i][j]==k){
		     	question_response[j][k]++;
			if(answer[i][j]==key[j]) {
                             question_correct[j]++;
                    	 
		        }
		    }

		}
	    }

	}

	

}
/*
 *prints each question with the percent correct, correct answer, and number of times each answer choice was selected
 *input from main: key, answers, num students, how hany of each question was correct, number of each response per question
 *output to main: none
*/

void outputQuestionResult(int key[TOTAL_QUESTIONS], int answer[][TOTAL_QUESTIONS], int question_correct[], int question_response[][MAX_CHOICES+1], int n) {
	int i,j;
	printf("Question\tKey\tCorrect %% \tNumber of Responses");
	printf("\n\t\t\tStudents\tBlank\tA\tB\tC\tD\tE\n");
	double perCorrect;
	for(i=0;i<TOTAL_QUESTIONS;i++) {
		perCorrect=100.0*question_correct[i]/n;

		printf("%i\t\t%c\t%.2lf\t\t",i+1, convertChar(key[i]), perCorrect);
		for (j=0; j<MAX_CHOICES+1;j++) {
		    printf("%i\t",question_response[i][j]);
	
		}
		printf("\n");
	}

}

/*
 *compares student answers to answer key and returns grade and missed question
 *input from main: number of students and their answers and the key
 *output to main: 2d array for missed, 1d array for correct and grade  
*/

void findGrade(int key[TOTAL_QUESTIONS],int answer[MAX_STUDENTS][TOTAL_QUESTIONS],int miss[MAX_STUDENTS][TOTAL_QUESTIONS],int correct[TOTAL_QUESTIONS], double grade[MAX_STUDENTS],int n) {
	int i, j;
	double right;
	for(i=0; i<n;i++) {
		right=0;
		for(j=0;j<TOTAL_QUESTIONS;j++) {

			
			if(key[j]!=answer[i][j]) {
				miss[i][j] = j+1;
			} else {
				correct[j]= correct[j]++;
				miss[i][j] =0;
				right++;
			
			}
			grade[i] = right/TOTAL_QUESTIONS*100;
			
		}
	}

}

/* 
 * readKey:read keys of all questions into a 1D array
 * input from main: none
 * output to main: a 1D key array (int)
*/

void readKey(int key[TOTAL_QUESTIONS]) {
	int i;
	char c;
	char garbage[1000];

	scanf("%75c",garbage);
	for (i=0;i<TOTAL_QUESTIONS; i++){
		scanf("%c",&c);
		key[i] = c - '0';
	 //  printf("%i  ", key[i]);
   }
  	scanf("%[^\n]", garbage); // skip reading the rest line
	scanf("%c", &c); // skip reading '\n'
   
} // readKey



/* 
 * readAnswer:read answers of all questions into a 2D array
 * input from main: none
 * output to main: a 2D answer array (int)
*/

int readAnswer(int answer[MAX_STUDENTS][TOTAL_QUESTIONS]) {
   int i=0, j;
   char c;
   char garbage[1000];


	while (scanf("%c", &c) != EOF) {
		scanf("%74c",garbage);
		for (j=0;j<TOTAL_QUESTIONS; j++){
			scanf("%c",&c);
				if (c == ' ' || c == '*')
					answer[i][j]=0;
				else
					answer[i][j] = c - '0';
		}// for
		scanf("%[^\n]", garbage); // skip reading the rest line
		scanf("%c", &c); // skip reading '\n'
		i++;
	} // while


	return i;
   
} // readAnswer



/* 
 * PrintKeyHeading:print a Key heading
 * input from main: none
 * output to main: none
*/

void PrintKeyHeading(){

	printf("%s", "Key:\t");
	
}

/* 
 * PrintAnswerHeading:print answer heading
 * input from main: none
 * output to main: none
*/

void PrintAnswerHeading(void){
	
	printf("%s", "\nStudent\t Grade\t Answer\t\t\t\t Wrong Questions\n");

}


/* 
 * outputKey: print a 1D key array
 * input from main: a 1D key array (int), array size n(int)
 * output to main: none
*/

void outputKey(int key[], int n) {
 
	int i;
 
	for (i=0; i< TOTAL_QUESTIONS; i++){
		printf("%c", convertChar(key[i]));
	}
	printf("%s", "\n");


} // outputKey


/* 
 * outputData:print answers, miss, grade arrays
 * input from main: answers(int), miss(int), grade(double) arrays
 * output to main: none
*/

void outputData(int answer[MAX_STUDENTS][TOTAL_QUESTIONS], int miss[][TOTAL_QUESTIONS], double grade[], int n) {

	int i, j;

   for (i=0; i<n; i++) {
	   
	   printf("%i\t", i+1);
	   printf("%.2lf\t", grade[i]);
		for (j=0; j<TOTAL_QUESTIONS; j++){
			printf("%c" , convertChar(answer[i][j]));	
		}
		printf("%s","\t");
		for (j=0; j<TOTAL_QUESTIONS; j++){
			
			if(miss[i][j]!=0){
				printf("%i ", miss[i][j]);
			}else{
				printf("%s"," ");
			}
		}
		printf("%s", "\n");
   } // for
	printf("%s", "\n");
        double classAvg=findAvg(grade,n);
        printf("Class Average: %.2lf\n", classAvg);
} // outputData

char convertChar (int ans) {
   switch (ans) {
      case 1:
	 return 'A';
	 break;
      case 2:
	 return 'B';
	 break;
      case 3:
	 return 'C';
	 break;
      case 4:
	 return 'D';
	 break;
      case 5:
	 return 'E';
	 break;
      default:
	 return ' ';
   }
}


