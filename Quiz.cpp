#include "Quiz.hpp"

Quiz::Quiz(std::string nameIn, std::string descriptionIn, std::string answerIn, Interactable* rewardIn) : Interactable(nameIn, descriptionIn), correctAnswer(answerIn), reward(rewardIn) {
	type = 2;
}

Interactable* Quiz::solve(char* ans){
	wmove(win, 0, 0);

	if(strlen(ans) == correctAnswer.length()-1){
		bool same = true;

		for (unsigned int i = 0; same && i < correctAnswer.length() - 1; i++){
			//if incorrect will break out of loop
			if (tolower(ans[i]) != tolower(correctAnswer[i]))
				same = false;
		}

		if(same)
			return reward;
	}

	//wrong answer output
	return nullptr;

}
