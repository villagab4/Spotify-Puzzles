#include <iostream>
#include <map>
#include <list>
#include <string>
#include <utility>
#include <algorithm>

/** This is not a correct solution to the Spotify Cat vs Dog puzzle.
 *  While this solution is erroneous, I gained valuable knowledge
 *  from writing this piece of software. My mistake lies in that 
 *  after each removal from the vector of voters, the voters removed
 *  should not have their votes counted. Yet, this would require
 *  updating the list as I iterate through it, which would only break
 *  the driver. Thus this is an invalid answer to the problem. 
 *  @author Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date:  May 26, 2017 
 */

 struct sortDescending {
 	bool operator()(const std::pair<int, std::string> &left, const std::pair<int, std::string> &right) const {
 		return left.first < right.first;
 	}
 }

 struct CompareKeep {
 	CompareKeep(std::string val): val_(val) {}
 	bool operator()(const std::pair<std::string, std::string> &element) const {
 		return val_ == element.first;
 	}
 	private:
 	std::string val_;
 };

 struct CompareKick {
 	CompareKick(std::string val): val_(val) {}
 	bool operator()(const std::pair<std::string, std::string> &element) const {
 		return val_ == element.second;
 	}
 	private:
 	std::string val_;
 };

 int keepVote = 501;
 int kickVote = 1;

/** This method constructs a map with an animal and its total votes. 
 *  Using a number theory technique, the first value of the pair stores 
 *  a number which can be modded to determine how many keep votes were cast
 *  and how many kick votes were cast. Then, the second part of the pair will
 *  hold the number of times this animal was cast as a vote. Then, when determining
 *  which animals are most important, the program simply sorts the map by the second
 *  pair integer, and determines if it is best to kick or keep that animal. 
 */

void populateMap(int numVoters, std::map<std::string, std::pair<int, int> > &votes, std::list<std::pair<std::string, std::string>> &voters) {

	//Initialize variables.
	std::string keep = "";
	std::string kick = "";
	int i = 0;

	while (i < numVoters) {

		std::cin >> keep >> kick;

		// Store voter in a list with 
		voters.emplace_back(keep, kick);

		// First number contains collection of votes incremented
		// by predetermined number. Will be used later to determine
		// how many votes were to keep and how many were to kick.
		votes[keep].first += keepVote;
		votes[kick].first += kickVote;

		// Second number tells how many votes were cast
		votes[keep].second++;
		votes[kick].second++;

		i++;
	}
}

/** This method returns the maximum number of satisfied customers. */

int getHappy(std::map<std::string, std::pair<int, int> > &votes, std::list<std::pair<std::string, std::string>> &voters) {

	// Create new map to determine most voted on animals.
	std::vector<std::pair<int, std::string>> votesPerAnimal;


	for (auto it = votes.begin(); it != votes.end(); ++it) {
		votesPerAnimal.emplace_back(it->second.second, it->first);
	}

	// Sort vector in ascending order, will access back element first.
	std::sort(votesPerAnimal.begin(), votesPerAnimal.end());

	// Iterate in descending order to get most voted
	// animals first.
	while (votesPerAnimal.size() > 0) 

		std::pair<int, std::string> it = votesPerAnimal.back();

	    //for (auto it = votesPerAnimal.begin(); it != votesPerAnimal.end(); ++it) {

		// Votes to keep that animal is found by taking the total
		// number of votes for that animal and dividing it by 
		// the set amount keepVote. This is a property used in 
		// higher level number theory and encryption.
		// Votes[it->second].first is sum of each vote for specific animal.
		int votesToKeep = votes[it->second].first / keepVote;

		// Votes to kick that animal is found by taking the mod 
		// of votesToKeep and total number of votes. Once again, 
		// this is found thanks to the same principle in
		// number theory. 
		int votesToKick = votes[it->second].first % keepVote;

		// If there were more votes to keep an animal than to kick
		// it off of the show, remove the voters who wished to kick said animal. 
		// In the event that the votesToKeep = votesToKick, it is arbitrary to 
		// keep or kick the animal, thus in this case, the program will keep
		// said animal. Need to check that there still exists a voter who actually
		// wants to keep said animal, otherwise no reason in worrying about it.
		if ( (votesToKeep >= votesToKick) && ( std::find_if(voters.begin(), voters.end(), CompareKeep(it->second)) != voters.end() ) ) {

			// Remove from the list if voter wants to kick animal 
			// that was chosen to be kept.
			voters.remove_if(CompareKick(it->second));

			// Iterate through voters who chose to keep said animal,

		}

		// If there were more votes to kick an animal than to keep
		// it on the show, remove all voters who chose to keep that animal.
		// However, if no voter remains who wishes to kick said animal, 
		// no action is taken.
		else if ( (votesToKeep < votesToKick) && ( std::find_if(voters.begin(), voters.end(), CompareKick(it->second)) != voters.end() ) ) {

			// Remove from the list if voter wants to keep animal
			// that was chosen to be kicked.
			voters.remove_if(CompareKeep(it->second));

		}

		// Remove animal just voted on. 
		votesPerAnimal.pop_back();

		// Sort vector again to ensure most up-to-date votes are 
		// in proper priority. 
		std::sort(votesPerAnimal.begin(), votesPerAnimal.end());

	}

	// Voters left in list represent maximum possible
	// satisfied voters.

	return voters.size();
}

int main() {

	// Initialize variables.
	int numCats, numDogs, numVoters, numTrials;
	std::cin >> numTrials;
	int y = 0;

	while (y < numTrials) {

		std::cin >> numCats >> numDogs >> numVoters;

		// This map will hold all the votes per animal.
		// The string will hold the animal voted on, within 
		// the pair of integers, the first integer is a sum of
		// the types of votes, while the second integer describes
		// how many votes were cast for this animal.
		std::map< std::string, std::pair<int, int> > votes;

		// This list will hold each voter along with their
		// animals to keep/kick.
		std::list< std::pair<std::string, std::string> > voters;

		// Populate the map properly based on voter input.
		populateMap(numVoters, votes, voters);

		// Print the maximum amount of voters satisfied.
		std::cout << getHappy(votes, voters) << std::endl;

		// Move on to next trial (if such trial exists).
		y++;

	}

}