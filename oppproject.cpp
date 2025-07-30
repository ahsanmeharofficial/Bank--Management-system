#include <iostream>
#include <string>
using namespace std;

// Max number of voters
const int MAX_VOTERS = 15;

// Voter class
class Voter {
private:
    string name;
    bool hasVoted;
public:
    // Constructor to initialize hasVoted as false
    Voter() {
        hasVoted = false;
    }

    // Voter ka name set karne ka method
    void setName(string n) {
        name = n;
    }

    // Voter ka name get karne ka method
    string getName() {
        return name;
    }

    // Vote karne ka method
    bool vote() {
        if (!hasVoted) {
            hasVoted = true;
            return true; // Vote successful
        }
        return false; // Voter ne pehle hi vote de diya
    }

    // Check if voter has voted
    bool alreadyVoted() {
        return hasVoted;
    }
};

// Election System class
class ElectionSystem {
private:
    Voter voters[MAX_VOTERS];
    int numVoters;
    int votesAhmad;
    int votesFawad;
    int neutralVotes;

public:
    // Constructor to initialize
    ElectionSystem() {
        numVoters = 0;
        votesAhmad = 0;
        votesFawad = 0;
        neutralVotes = 0;
    }

    // Voter ko add karne ka method
    void addVoter(string name) {
        if (numVoters < MAX_VOTERS) {
            voters[numVoters].setName(name);
            numVoters++;
        } else {
            cout << "Max number of voters reached!" << endl;
        }
    }

    // Voting process ko handle karna
    void vote(string voterName, int candidateChoice) {
        for (int i = 0; i < numVoters; i++) {
            if (voters[i].getName() == voterName) {
                if (voters[i].alreadyVoted()) {
                    cout << "Aap ne pehle hi vote de diya hai!" << endl;
                    return;
                }

                if (voters[i].vote()) {
                    if (candidateChoice == 1) {
                        votesAhmad++;
                    } else if (candidateChoice == 2) {
                        votesFawad++;
                    } else {
                        neutralVotes++;
                        cout << "Neutral vote casted!" << endl;
                    }
                    cout << "Thank you!" << endl;
                    return;
                }
            }
        }
        cout << "Voter nahi mila!" << endl;
    }

    // Election results ko show karna
    void showResults() {
        cout << "\nElection Results:\n";
        cout << "Votes for Ahmad: " << votesAhmad << endl;
        cout << "Votes for Fawad: " << votesFawad << endl;
        cout << "Neutral votes: " << neutralVotes << endl;

        cout << "\nTotal voters: " << numVoters << endl;

        // Winner ka pata lagana
        if (votesAhmad > votesFawad) {
            cout << "Ahmad jeet gaya hai aur class representative ban gaya!" << endl;
        } else if (votesFawad > votesAhmad) {
            cout << "Fawad jeet gaya hai aur class representative ban gaya!" << endl;
        } else {
            cout << "Election mein tie hai!" << endl;
        }
    }

    // Getter for voters array
    Voter* getVoters() {
        return voters;
    }

    // Get number of voters
    int getNumVoters() {
        return numVoters;
    }
};

// Main function
int main() {
    ElectionSystem election;
    int numStudents;

    cout << "Enter number of students voting (max 15): ";
    cin >> numStudents;
    cin.ignore();  // Newline ignore karna taake getline kaam kare

    // Check for max limit
    if (numStudents > MAX_VOTERS) {
        cout << "Aap sirf " << MAX_VOTERS << " students ko vote dene ki ijaazat hai." << endl;
        return 1; // Exit if more than max voters
    }

    // Students ka input lena
    for (int i = 0; i < numStudents; ++i) {
        string studentName;
        cout << "Enter name of student " << i + 1 << ": ";
        getline(cin, studentName);
        election.addVoter(studentName);
    }

    // Voting process
    for (int i = 0; i < election.getNumVoters(); ++i) {
        int candidateChoice;
        cout << "\n" << election.getVoters()[i].getName() << ", kis ko vote karna chahte hain? (1: Ahmad, 2: Fawad): ";
        cin >> candidateChoice;
        cin.ignore();  // Newline ignore karna taake getline kaam kare
        election.vote(election.getVoters()[i].getName(), candidateChoice);
    }

    // Results display karna
    election.showResults();

    return 0;
}