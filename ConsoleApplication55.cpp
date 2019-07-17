#include<iostream>
#include <array>
#include<string>
#include <iomanip>


class GradeBook {
public:
	static const size_t students{ 10 };
	static const size_t tests{ 3 };

	GradeBook(const std::string& name,
		std::array<std::array<int, tests>, students>& gradesArray) 
		: courseName(name), grades(gradesArray) {}

	void setCourseName(const std::string& name){
		courseName = name;
	}
	const std::string& getCourseName() const {
		return courseName;
	}

	void displayMessage() const {
		std::cout << "Welcome\n" << getCourseName() << std::endl;
	}

	void processGrades() const {
		outputGrades();
		std::cout << "\nLowest grade is " << getMinimum()
		<< "\nHighest grade is " << getMaximum() << std::endl;
		outputBarChart();
	}

	int getMinimum() const {
		int lowGrade{ 100 };
		for (auto const& student : grades) {
			for (auto const& grade : student) {
				if (grade < lowGrade) {
					lowGrade = grade;
				}
			}
		}
		return lowGrade;
	}
	int getMaximum() const {
		int highGrade{0};
		for (auto const& student : grades) {
			for (auto const& grade : student) {
				if (grade > highGrade) {
					highGrade = grade;
				}
			}
		}
		return highGrade;
	}

	double getAverage(const std::array<int, tests>& setOfGrades) const {
		int total{ 0 };
		for (int grade : setOfGrades) {
			total += grade;
		}
		return static_cast<double>(total) / setOfGrades.size();
	}

	void outputBarChart() const {
		std::cout << "Overal grade distribution: " << std::endl;
		const size_t frequencySize{ 11 };
		std::array<unsigned int, frequencySize> frequency{};
		for (auto const& student : grades) {
			for (auto const& test : student) {
				++frequency[test / 10];
			}
		}
		for (size_t count{ 0 }; count < frequencySize; count++) {
			if (0 == count) {
				std::cout << " 100: ";
			}
			else {
				std::cout << count * 10 << "-" << (count * 10) + 9 << ": ";
			}
			for (unsigned int stars{ 0 }; stars < frequency[count]; stars++)
				std::cout << '*';
			std::cout << std::endl;
		}
	}

	void outputGrades() const {
		std::cout << "\nThe grades are:\n\n";
		std::cout << "        ";
		for (size_t test{ 0 }; test < tests; test++) {
			std::cout << "Test " << test + 1 << "  ";
		}
		std::cout << "Awerage" << std::endl;

		for (size_t student{ 0 }; student < grades.size(); student++) {
			std::cout << "Student " << std::setw(2) << student + 1;

			for (size_t test{ 0 }; test < grades[student].size(); test++) {
				std::cout << std::setw(8) << grades[student][test];
			}

			double average{ getAverage(grades[student]) };
			std::cout << std::setw(9) << std::setprecision(2) << std::fixed << average
				<< std::endl;
		}
	}



private:
	std::string courseName;
	std::array<std::array<int, tests>, students>grades;
};


int main() {
	std::array<std::array<int, GradeBook::tests>, GradeBook::students> grades{
		{88, 96 ,72}};
	GradeBook myGB("Test", grades);
	myGB.displayMessage();
	myGB.processGrades();
	system("pause");
	return 0;
}