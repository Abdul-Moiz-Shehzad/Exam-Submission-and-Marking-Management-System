#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
using namespace std;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
class stack {
	int* arr;
	int size;
	int top;
public:
	stack(int val) {
		this->size = val;
		arr = new int[size];
		top = -1;
	}
	void pushStack(int val) {
		if (isFullStack()) {
			return;
		}
		else {
			top++;
			arr[top] = val;
		}
	}
	void popStack() {
		if (isEmptyStack()) {
			return;
		}
		else {
			top--;
		}
	}
	bool isEmptyStack() {
		if (top == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isFullStack() {
		if (top == size - 1) {
			return true;
		}
		else {
			return false;
		}
	}
	void printStack() {
		for (int i = 0; i <= top; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	int getTop() {
		return arr[top];
	}
	void sortStack() {
		for (int i = 0; i <= top; i++) {
			for (int j = 0; j < i; j++) {
				if (arr[i] > arr[j]) {
					swap(arr[i], arr[j]);
				}
			}
		}
	}
	int findKelementTop(int k) {
		for (int i = top; i >= 0; i--) {
			if (arr[i] == k) {
				return top-i;
				break;
			}
		}
	}
	int findKelementBottom(int k) {
		for (int i = 0; i <= top; i++) {
			if (arr[i] == k) {
				return i;
				break;
			}
		}
	}
	void deleteKelement(int k) {
		stack temp(top + 1);
		while (!isEmptyStack()) {
			if (getTop() == k) {
				popStack();
			}
			else {
				temp.pushStack(getTop());
				popStack();
			}
		}
		while (!temp.isEmptyStack()) {
			pushStack(temp.getTop());
			temp.popStack();
		}
	}
};
class queue {
	int* arr;
	int front;
	int rear;
	int size;
public:
	queue(int val) {
		this->size = val;
		arr = new int[size];
		front = rear = -1;
	}
	queue(queue& obj) {
				this->size = obj.size;
		arr = new int[size];
		front = rear = -1;
		for (int i = 0; i <= obj.rear; i++) {
			pushInQueue(obj.arr[i]);
		}
	}
	void pushInQueue(int val) {
		if (isFullQueue()) {
			return;
		}
		else {
			if (isEmptyQueue()) {
				front++;
				rear++;
			}
			else {
				rear++;
			}
			arr[rear] = val;
		}
	}
	void popFromQueue() {
		if (isEmptyQueue()) {
			return;
		}
		else {
			for (int i = 0; i <= rear; i++) {
				arr[i] = arr[i + 1];
			}
			rear--;
		}
	}
	bool isEmptyQueue() {
		if (front == -1 && rear == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isFullQueue() {
		if (rear == size - 1) {
			return true;
		}
		else {
			return false;
		}
	}
	void printQueue() {
		for (int i = 0; i <= rear; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	int getFront() {
		if (!isEmptyQueue()) {
		return arr[front];
		}
	}
	int getRear() {
		if (!isEmptyQueue()) {
		return arr[rear];
		}
	}
	void sortQueue() {
		for (int i = 0; i <= rear; i++) {
			for (int j = 0; j < i; j++) {
				if (arr[i] < arr[j]) {
					swap(arr[i], arr[j]);
				}
			}
		}
	}
	void deleteKelementQueue(int k,queue &queueB4Submission) {
		queue temp(this->rear + 1);
		for (int i = 0; i <= rear; i++) {
			if (arr[i] != k) {
				temp.pushInQueue(arr[i]);
			}
			else {
				queueB4Submission.pushInQueue(arr[i]);
			}
		}
		
		*this = temp;
	}
	int queueSize() {
		return rear + 1;
	}
};

void readData(vector<pair<int, string>>(&data), int& num) {
	try {
		bool found = 0;
		bool duplicates = 0;
		ifstream rdr("data.txt");
		if (!rdr) {
			throw exception();
		}
		int roll;
		string name;
		char comma;
		while (!rdr.eof()) {
			rdr >> roll;
			rdr >> comma;
			rdr >> name;
			if (comma != ',') {
				throw exception();
			}
			data.push_back(make_pair(roll, name));
			num++;
		}
		for (int i = 0; i < num; i++) {
			if (data[i].first == 420) {
				found = 1;
			}
		}
		if (found == 0) {
			cout << "John not found ";
			throw exception();
		}
		for (int i = 0; i < data.size(); i++) {
			for (int j = i + 1; j < data.size(); j++) {
				if (data[i] == data[j]) {
					duplicates = true;
					break;
				}
			}
		}
		if (duplicates == true) {
			cout<<"Duplicates found ";
			throw exception();
		}
	}
	catch (exception e) {
		cout << "Invalid Input/File not found" << endl;
		system("pause");
	}
		
		
		/*for (int i = 0; i < data.size(); i++) { //TO PRINT THE DATA
			cout<<data[i].first<<" "<<data[i].second<<endl;
		}*/
	}
int findJohn(queue sittingPlan, int numberOfPeople) {
	queue temp(sittingPlan);// had to use copy constructor because the original sittingPlan was getting changed
	for (int i = 0; i < numberOfPeople; i++) {
		if (temp.getFront() == 420) {
			return i;
			break;
		}
		else {
			temp.popFromQueue();
		}
	}
}
void processExam(queue &sittingPlan, queue &queueB4Submission, stack &submissionPile,stack &resultantPile,int numberOfPeople) {
	cout<<RED<<"Processing the exam"<<RESET<<endl;
	//sittingPlan.sortQueue(); //sort karne ke liye sitting plan according to roll number 
	cout <<CYAN<< "Students Sitiing plan:"<<RESET<<endl;
	sittingPlan.printQueue();
	int countOfIndexforPeopleOtherThanJohn = 0;
	cout << YELLOW << "John received exam after " << findJohn(sittingPlan, numberOfPeople) << " students" << RESET << endl;
	int peopleCompletedExam = 0.69 * numberOfPeople; //69% of people completed exam before john
	for (int i = 0; i < peopleCompletedExam && sittingPlan.getRear() != 402; i++) {
		queueB4Submission.pushInQueue(sittingPlan.getFront());
		sittingPlan.popFromQueue();
	}
	cout <<CYAN<< "69% of students who have completed their exam before john:" <<RESET<< endl;
	queueB4Submission.printQueue();
	int peoplegoingtoPlaceExams=0.03*numberOfPeople; //3% pepole in queue b4 john out of 69% of total people completed exam
	for (int i = 0; i < peopleCompletedExam-peoplegoingtoPlaceExams; i++) {
		submissionPile.pushStack(queueB4Submission.getFront());
		queueB4Submission.popFromQueue();
	}
	sittingPlan.deleteKelementQueue(420,queueB4Submission); //remove john from sitting plan and places in queueB4Submission
	cout <<CYAN<< "John joins the queue with 3% present already in line" <<RESET<< endl;
	queueB4Submission.printQueue();
	cout<<YELLOW<<"John had to wait "<< findJohn(queueB4Submission, queueB4Submission.queueSize())<<" unit times in queue to submit exam"<<RESET<<endl;
	//submitting the papers 
	for (int i = 0; i <  peoplegoingtoPlaceExams+1; i++) { 
		submissionPile.pushStack(queueB4Submission.getFront());
		queueB4Submission.popFromQueue();
	}
	//remaining people in sitting plan
	cout<<CYAN<<"Consider all people completes the exam and have to go through queue to submit exam\nNow"<<RESET<<endl;
	peopleCompletedExam++;//include john
	int remainingPeople = numberOfPeople - peopleCompletedExam;
	for (int i = 0; i < remainingPeople; i++) {
		queueB4Submission.pushInQueue(sittingPlan.getFront());
		sittingPlan.popFromQueue();
	}
	for (int i = 0; i < remainingPeople; i++) {
		submissionPile.pushStack(queueB4Submission.getFront());
		queueB4Submission.popFromQueue();
	}
	cout<<CYAN<<"Submission pile after all the papers are submitted:"<<RESET<<endl;
	submissionPile.printStack();
	cout<<YELLOW<<"John exam was found in in the submission stack after "<<submissionPile.findKelementBottom(420)<<" papers from bottom"<<RESET<<endl;
	cout<<YELLOW<<"John exam was found in in the submission stack after "<<submissionPile.findKelementTop(420)<<" papers from top"<<RESET<<endl;
	cout << GREEN << "To move on to the checking process "<<RESET;
	system("pause");
}
void markExams(queue& sittingPlan, queue& queueB4Submission, stack& submissionPile, stack& resultantPile, int numberOfPeople) {
	cout<<RED<<"Marking the exams"<<RESET<<endl;
	cout<<YELLOW<<"John exam was marked after "<<submissionPile.findKelementTop(420)<<" papers"<<RESET << endl;
	cout << CYAN << "In checking process, examiner picks the paper on top from the pile of submission and place on top of the resultant pile"<<RESET<<endl;
	for (int i = 0; i < numberOfPeople; i++) {
		resultantPile.pushStack(submissionPile.getTop());
		submissionPile.popStack();
	}
	cout << CYAN << "Resultant pile after checking all the papers:" << RESET << endl;
	resultantPile.printStack();
	cout << YELLOW << "John exam was found in in the submission stack at " << resultantPile.findKelementBottom(420) << " papers from bottom" << RESET << endl;
	cout << YELLOW << "John exam was found in in the submission stack after " << resultantPile.findKelementTop(420) << " papers from top" << RESET << endl;
	cout << GREEN << "To move on to the paper returning process " << RESET;
	system("pause");
}
void returningPaper(queue& sittingPlan, queue& queueB4Submission, stack& submissionPile, stack& resultantPile, int numberOfPeople) {
	cout<<RED<<"Returning the papers"<<RESET<<endl;
	cout<<CYAN<<"37% of total students came before john to receive their exam back"<<RESET<<endl;
	int peopleGoingB4John = 0.37 * numberOfPeople;
	//57 people go 
	for (int i = 0; i < peopleGoingB4John; i++) {
		if(resultantPile.getTop()==420){
			continue;
		}
		else {
			resultantPile.popStack();
		}
	}
	cout << CYAN << "37% received their exams, remaining stack:" << RESET << endl;
	resultantPile.printStack();
	int johnSearch= resultantPile.findKelementTop(420);
	cout << YELLOW << "John received his exam after " << peopleGoingB4John << " students (37% students received b4 john)" << RESET << endl;
	cout << YELLOW << "John went through " << johnSearch << " minimum and maximum papers while seaching for his paper" << RESET << endl;
	resultantPile.deleteKelement(420);
	cout<<CYAN<<"John received his exam"<<RESET<<endl;
	resultantPile.printStack();	
	cout << CYAN << "After that rest of students receive their papers"<<RESET;
	while (!resultantPile.isEmptyStack()) {
		resultantPile.popStack();
	}
}
int main() {
	cout << "INSTRUCTIONS\nRed is the current scenario\nYellow is answer to questions\nblue is the explanation\nGrey is the stack/queue\n";
	system("pause");
	system("cls");
	vector<pair<int, string>>data;
	int numberOfPeople = 0;
	readData(data, numberOfPeople);
	queue SittingPlan(numberOfPeople);
	for (int i = 0; i < numberOfPeople; i++) {
		SittingPlan.pushInQueue(data[i].first);
	}
	queue queueB4Submission(numberOfPeople);
	stack submissionPile(numberOfPeople);
	stack resultantPile(numberOfPeople);
	processExam(SittingPlan, queueB4Submission, submissionPile, resultantPile, numberOfPeople);
	markExams(SittingPlan, queueB4Submission, submissionPile, resultantPile, numberOfPeople);
	returningPaper(SittingPlan, queueB4Submission, submissionPile, resultantPile, numberOfPeople);
}