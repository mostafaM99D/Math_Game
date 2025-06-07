#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define endl '\n'

enum enQuestionLevel { Easy = 1, Miduim = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Substract = 2, Multiply = 3, Divide = 4, MixOp = 5 };

struct stGame {
	int NumberOfQuestions = 0;
	int QuestionLevel = 0;
	int OperationType = 0;
	int CurrentQuestion = 0;
};
stGame game;

int RandomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}

enOperationType OperationChoice(enOperationType operation) {
	if (operation == MixOp) {
		return (enOperationType)RandomNumber(1, 4);
	}
	return operation;
}

void GetTwoNumbers(int level, int& num1, int& num2) {
	if (level == Mix)
		level = RandomNumber(1, 3);

	if (level == Easy) {
		num1 = RandomNumber(1, 10);
		num2 = RandomNumber(1, 10);
	}
	else if (level == Miduim) {
		num1 = RandomNumber(10, 50);
		num2 = RandomNumber(10, 50);
	}
	else if (level == Hard) {
		num1 = RandomNumber(50, 100);
		num2 = RandomNumber(50, 100);
	}
}

void GenerateQuestion(int questionNumber) {
	int num1 = 0, num2 = 0;
	GetTwoNumbers(game.QuestionLevel, num1, num2);
	enOperationType op = OperationChoice((enOperationType)game.OperationType);
	int correctAnswer = 0;

	cout << "Question [" << questionNumber << "]: ";

	if (op == Add) {
		cout << num1 << " + " << num2 << " = ?" << endl;
		correctAnswer = num1 + num2;
	}
	else if (op == Substract) {
		cout << num1 << " - " << num2 << " = ?" << endl;
		correctAnswer = num1 - num2;
	}
	else if (op == Multiply) {
		cout << num1 << " * " << num2 << " = ?" << endl;
		correctAnswer = num1 * num2;
	}
	else if (op == Divide) {
		if (num2 == 0) num2 = 1;
		num1 = num1 * num2; 
		cout << num1 << " / " << num2 << " = ?" << endl;
		correctAnswer = num1 / num2;
	}

	int userAnswer;
	cout << "Your answer: ";
	cin >> userAnswer;

	if (userAnswer == correctAnswer)
		cout << " Correct!" << endl;
	else
		cout << " Wrong! The correct answer is: " << correctAnswer << endl;
}

void PlayGame() {
	cout << "Enter level of questions: [1]Easy [2]Miduim [3]Hard [4]Mix" << endl;
	cin >> game.QuestionLevel;
	cout << "Enter operation type: [1]Add [2]Substract [3]Multiply [4]Divide [5]Mix" << endl;
	cin >> game.OperationType;

	for (int i = 1; i <= game.NumberOfQuestions; ++i) {
		cout << "------------------------------" << endl;
		GenerateQuestion(i);
		cout << "------------------------------" << endl << endl;
	}
}

void StartGame() {
	char choice;
	do {
		cout << "How many questions do you want? ";
		cin >> game.NumberOfQuestions;

		PlayGame();

		cout << endl << "Play again? (y/n): ";
		cin >> choice;
		cout << endl;

	} while (choice == 'y' || choice == 'Y');
}

int main() {
	srand((unsigned)time(0));
	StartGame();
	return 0;
}
