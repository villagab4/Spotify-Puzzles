#include <iostream>
#include <map>
#include <vector>

/** This is a solution to the Spotify Zipf's Song puzzle.
 *  @author Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date:  May 25, 2017 
 */

/** Reads from stdin and populates map.
 *  @param numOfSongs sets limit 
 *  @param songs is reference to map which is populated
 */

void populateMap(int numOfSongs, std::map<double, std::vector<std::string> > &songs) {

	// Initialize variables

	double i = 1, timesListened = 0;
	std::string nameOfSong = "";

	// Iterate through list of songs

	while (i <= numOfSongs) {
		std::cin >> timesListened >> nameOfSong;

		// Store appropriate song in its intended Zipf ratio

		songs[i * timesListened].push_back(nameOfSong);

		i++;
	}
}

/** Prints most popular songs according to Zipf's law.
 *  @param topSongs sets limit
 *  @param songs is reference to map containing songs
 */

void printTop(int topSongs, std::map<double, std::vector<std::string> > &songs) {

	// Count keeps track of how many songs are required to print

	int count = 0;

	// Call const iterator to obtain most popular songs

	for (auto it = songs.rbegin(); count < topSongs; ++it) {

		// Checks if there are multiple songs with same Zipf ratio

		if (it->second.size() > 1) {

			unsigned int i = 0;

			// Run through vector until end of vector or count reached

			while (i < it->second.size() && count < topSongs) {
				std::cout << it->second.at(i) << std::endl;
				i++;
				count++;
			}
		} else {


			// Otherwise, just print single value at that ratio's index

			std::cout << it->second.at(0) << std::endl;
			count++;
			
		}
	}
}

int main() {

	int numOfSongs, topSongs;

	// Read from stdin n and m

	std::cin >> numOfSongs >> topSongs;

	// Construct a map with key being the ratio.
	// Value of key is a map that holds the names of songs
	// with that ratio.

	std::map<double, std::vector<std::string> > songs;

	populateMap(numOfSongs, songs);
	printTop(topSongs, songs);
}