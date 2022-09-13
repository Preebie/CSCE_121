#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
using std::cin;
using std::cout;using std::endl;using std::string;using std::ifstream;
int numUps, numDowns, numLefts, numRights, Moves = 0;
/**
 * Creates internal representation of dungeon map.
 * @param   fileName    File name of dungeon map representation.
 * @param   width       Width of dungeon map.
 * @param   height      Height of dungeon map.
 * @param   currX       Player's starting x-position on dungeon map.
 * @param   currY       Player's starting y-position on dungeon map.
 * @return  2D dynamic array representation of dungeon map with player's location.
 */
 // STEP 1: Write code for createMap(...) function here.
int** createMap(string &filename, int &width, int &height, int &currX, int &currY) {
  ifstream ifs(filename);
  if (!ifs) {
    cout << "ERROR: unable to open: map_does_not_exist.txt" << endl;
    return nullptr;
  }
  ifs >> width >> height;
  ifs >> currX >> currY;
  int** map = new int* [width];
  for (int i = 0; i < width; ++i)
    map[i] = new int[height];

  for (int i = 0; i < width; i++) {
    for (int n = 0; n < height; n++) {
      ifs >> map[n][i];
    }
  }
  map[currX][currY] = 1;
  return map;
}
/**
 * Updates player's position and movement status for next turn.
 * @param   map         Dungeon map.
 * @param   width       Width of dungeon map.
 * @param   height      Height of dungeon map.
 * @param   direction   User's keyboard input for player's dungeon map direction.
 * @param   currX       Player's current x-position on dungeon map.
 * @param   currY       Player's current y-position on dungeon map.
 * @param   nextX       Player's next x-position on dungeon map.
 * @param   nextY       Player's next y-position on dungeon map.
 * @return  Player's movement status after updating player's position for next turn.
 */
 // STEP 2: Write code for updateNextPosition(...) function here.
int updateNextPosition(int** &map, int &width, int &height, char &direction, int &currX, int &currY, int &nextX, int &nextY) {
  if (direction == 'w') {
    nextY = currY - 1;
    nextX = currX;
    Moves++;

  }
  else if (direction == 'a') {
    nextY = currY;
    nextX = currX - 1;
    Moves++;

  }
  else if (direction == 's') {
    nextY = currY + 1;
    nextX = currX;
    Moves++;

  }
  else if (direction == 'd') {
    nextY = currY;
    nextX = currX + 1;
    Moves++;

  }
  if ((nextX > (width - 1)) || (nextY > (height - 1)) || (nextY < 0) || (nextX < 0) || (map[nextX][nextY] == 2)) {
    return 1;
  }
  else if (map[nextX][nextY] == 3) {
    return 2;
  }

  else {
    if (direction == 'w') {
      numUps++;
    }
    else if (direction == 'a') {
      numLefts++;
    }
    else if (direction == 's') {
      numDowns++;
    }
    else if (direction == 'd') {
      numRights++;
    }
    return 0;
    
  }
}
/**
 * Updates dungeon map representation with player's current position.
 * @param   currX       Player's current x-position on dungeon map.
 * @param   currY       Player's current y-position on dungeon map.
 * @param   nextX       Player's next x-position on dungeon map.
 * @param   nextY       Player's next y-position on dungeon map.
 */
 // STEP 3: Write code for updateMap(...) function here.
void updateMap(int** &map, int &currX, int &currY, int &nextX, int &nextY) {
  map[currX][currY] = 0;
  currX = nextX;
  currY = nextY;
  map[nextX][nextY] = 1;
  
}
void updateStatistics() {
  cout << "--- Statistics Information ---" << endl;
  cout << "- Moves:  " << Moves << endl;
  cout << "- Ups:    " << numUps << endl;
  cout << "- Downs:  " << numDowns << endl;
  cout << "- Lefts:  " << numLefts << endl;
  cout << "- Rights: " << numRights << endl;

}

int main() {

  // declare variables
  int width{}, height{}, currX{}, currY{}, nextX{}, nextY{};
  
  string fileName;

  // prompt user to enter dungeon file name
  cout << "Please enter dungeon map file: ";
  cin >> fileName;

  // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
  // create map, or quit if map load error
  int** map = createMap(fileName, width, height, currX, currY);
  if (map == nullptr) {
    cout << "This dungeon map does not exist. ";
    cout << "Returning you back to the real word, adventurer!" << endl;
    return 1;
  }

  // display greeting message
  cout << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << "Good day, adventurer! Your goal is to escape the dungeon!" << endl;
  cout << " --- SYMBOLS ---" << endl;
  cout << " o          : That is you, the adventurer!" << endl;
  cout << " x, -, |    : These are unpassable obstacles." << endl;
  cout << " !          : That is the door to escape the dungeon." << endl;
  cout << " --- CONTROLS ---" << endl;
  cout << " w, a, s, d : Keys for moving up, left, down, and right." << endl;
  cout << " q          : Key for abandoning your quest." << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << endl;

  // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
   // display map
  outputMap(map, width, height);

  // move player
  char input;
  int status;
  while (true) {
    // get user input
    cout << "Enter command (w,a,s,d: move, q: quit): ";
    cin >> input;

    if (input == 'i') {
      updateStatistics();
      continue;
    }

    // quit game if user inputs quit
    if (input == INPUT_QUIT) {
      cout << "Thank you for playing!" << endl;
      break;
    }

    // skip turn if user inputs 
    if (input != MOVE_UP && input != MOVE_LEFT && input != MOVE_DOWN && input != MOVE_RIGHT && input != 'i') {
      cout << "I did not understand your command, adventurer!" << endl;
      continue;
    }

    //--- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 2 ---
     // move player, if possible, and get map status
    status = updateNextPosition(map, width, height, input, currX, currY, nextX, nextY);

    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 3 ---
    // update map
    if (status == STATUS_MOVE || status == STATUS_ESCAPE) {
      updateMap(map, currX, currY, nextX, nextY);
    }

    // display map and status
    outputMap(map, width, height);
    outputStatus(status, currX, currY);

    // quit game if user escapes
    if (status == STATUS_ESCAPE) {
      break;
    }
  }

  // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
  // delete map
  deleteMap(map, width);

  return 0;
}
