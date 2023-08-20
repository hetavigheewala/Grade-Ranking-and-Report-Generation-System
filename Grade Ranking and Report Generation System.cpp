
// @brief This program process a file of grades for ranking
//        and generates a report

#include <iostream>     // Add screen and keyboard input output capability
#include <fstream>      // Add file input output capability
#include <string>       // Add features for working with strings
#include <iomanip>      // add output formatting features

// set namespace
using namespace std;


/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Local constant definition(s)
    const int MAGIC = 34;                       // Indicates valid file
    const double SCORE_COUNT = 3;               // maximum num of scores
    const int A = 90;                           // cutoff for 'A'
    const int B = 80;                           // cutoff for 'B'
    const int C = 70;                           // cutoff for 'C'
    const int D = 60;                           // cutoff for 'D'

    const string LINE = "---------";            // presentation dividing line
    const int CW = 9;                           // column width
    const int GAP = 2;                          // gutter width

    const string OFN = "report.txt";            // report file name

    // Variable declarations(s)
    int exitState;                  // tracks the exit code for the process
    exitState = EXIT_SUCCESS;       // set state to successful run

    bool validFile;                             // tracks data file validity
    string message;                             // holds file error message


    // file access variables
    ifstream fin;                               // file input handler
    ofstream fout;                              // file output handler
    string   finName;                           // user supplied data source

    // file input variables
    // vars start with "l", to indicate line number in data file
    // line 0 holds magic number
    int magicNum = 0;                           // number identifying valid file

    string  l1name = "";                        // line 1 student name
    int     l1s1 = 0;                           // line 1 first score
    int     l1s2 = 0;                           // line 1 second score
    int     l1s3 = 0;                           // line 1 third score

    string  l2name = "";                        // line 2 student name
    int     l2s1 = 0;                           // line 2 first score
    int     l2s2 = 0;                           // line 2 second score
    int     l2s3 = 0;                           // line 2 third score

    // processing variables
    int     a1 = 0;                             // line 1 average score
    int     a2 = 0;                             // line 2 average score
    char    g1 = '\0';                          // line 1 grade
    char    g2 = '\0';                          // line 2 grade
    string  rank;                               // holds name of top student

    /* ******* User Input Phase ****************************************** */
    // get input file name
    cout << endl;
    cout << "Enter input file name: ";
    getline(cin, finName);
    cout << endl;

    /* ******* File Input Phase ****************************************** */
    // Open the file
    fin.open(finName);

    // set up environment for program continuation based on whether or not
    // the file is open
    if (fin.is_open()) {
        // just in case the file is the wrong type
        // set the error message so that we can use the message later
        message = "File does not pass the Magic Number Test...";

        // get the file type indicator (magic number)
        fin >> magicNum;
        fin.ignore(100, '\n');                   // ignore rest of line

        // test file for validity
        validFile = magicNum == MAGIC ? true : false;

    } else {
        // file did not open
        validFile = false;

        // set the error message because the file was not found
        message = "File not found...";
    }

    // if the magic number test passed read in the data
    if (validFile) {
        // populate data variables
        fin >> l1name >> l1s1 >> l1s2 >> l1s3;
        fin >> l2name >> l2s1 >> l2s2 >> l2s3;
    }


    /* ******* Processing Phase ****************************************** */
    if (validFile) {
        // calculate average scores for both lines and round up to int
        a1 = static_cast<int>((static_cast<double>(l1s1 + l1s2 + l1s3)
                               / SCORE_COUNT) + 0.999999);
        a2 = static_cast<int>((static_cast<double>(l2s1 + l2s2 + l2s3)
                               / SCORE_COUNT) + 0.999999);

        // find grade for line 1 using if then else
        if (a1 <  D) {
            g1 = 'F';
        } else if (a1 < C) {
            g1 = 'D';
        } else if (a1 < B) {
            g1 = 'C';
        } else if (a1 < A) {
            g1 = 'B';
        } else {
            g1 = 'A';
        }

        // find grade for line 2 using switch case
        // evaluation using switch
        // integer divide the score by to get the most significant digit
        switch (static_cast<int>(a2) / 10) {
            case 10:
            case  9:
                g2 = 'A';
                break;

            case 8:
                g2 = 'B';
                break;

            case 7:
                g2 = 'C';
                break;

            case 6:
                g2 = 'D';
                break;

            case 5:
                g2 = 'F';
                break;

            default:
                g2 = 'F';
                break;
        }

        // rank the lines
        rank = a1 > a2 ? l1name : l2name;
    }

    /* ******* Screen Output Phase *************************************** */
    if (validFile) {

        cout << "Grade calculated using if-then-else:" << endl;
        cout << l1name << ": " << a1 << " = " << g1 << endl << endl;
        cout << "Grade calculated using switch case:" << endl;
        cout << l2name << ": " << a2 << " = " << g2 << endl << endl;
        cout << "Ranking processed using a ternary operator:" << endl;
        cout << rank << " had the best score." << endl << endl;
    }

    /* ******* File Output Phase ***************************************** */
    if (validFile) {
        fout.open(OFN);

        // write heading
        fout << left << setw(CW + GAP) << "NAME"
        << setw(CW + GAP) << "GRADE"
        << setw(CW + GAP) << "BEST" << endl;

        // write separator
        fout << left << setw(CW + GAP) << LINE
        << setw(CW + GAP) << LINE
        << setw(CW + GAP) << LINE << endl;

        // write line 1
        fout << left << setw(CW + GAP) << l1name
        << setw(CW + GAP) << g1;

        // if student is best, print in Asterix
        if (rank == l1name) {
            fout << setw(CW + GAP) << " *";
        }

        // finish the line
        fout << endl;

        // write line 2
        fout << left << setw(CW + GAP) << l2name
        << setw(CW + GAP) << g2;

        // if student is best, print in Asterix
        if (rank == l2name) {
            fout << setw(CW + GAP) << " *";
        }

        // finish the line
        fout << endl;

    }

    /* ******* Error Output Phase **************************************** */
    if (!validFile) {
        // There was something wrong. Print the error message.
        cout << message << endl << endl;

    }

    // done with files.
    fin.close();
    fout.close();

    return exitState;
}
