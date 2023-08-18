#include"snake.h"

#pragma comment(lib, "winmm.lib")

int main() {
  
    int temp, option;
    FixConsoleWindow();
    
    mainMenu(option);
    thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();
    int key = 1;
    bool isRun = true;
    string s, filename;
    while (isRun) {
        // thoat
        if (option == 4) {
            ExitGame(handle_t1);
            break;
        }

        STATE = 1;
        switch (option) {
        case 1: // Start game
            system("cls");
            STATE = 0;
            s = InputName();
            NAME = s;
            
            STATE = 1;

            StartGame(key);
            // Print name
            color(15);
            GotoXY(112, 9);
            cout << NAME;

            color(15);
            GotoXY(106, 12);
            cout << "ROUND: " << SPEED << "/3";

            GotoXY(106, 15);
            cout << "LENGTH: " << SIZE_SNAKE << " /32";
   
            while (1) {
                
                temp = toupper(_getch());
                if (STATE == 1) {
                    if (temp == 'P') {
                        PauseGame(handle_t1);
                    }
                    else if (temp == 27) { // esc
                        STATE = 0;
                        system("cls");
                        mainMenu(option);
                        break;
                    }
                    else if (temp == 'L') {
                        PauseGame(handle_t1);
                        SaveGame();
                    }
                    else if (temp == 'T') {
                        
                        STATE = 0;
                        system("cls");
                        filename = InputName();
                        NAME = LoadGame(filename);
                        StartGame(2);
                   

                    }
                    else {
                        ResumeThread(handle_t1);
                        // Delete pause
                        color(249);
                        GotoXY(106, 23);
                        
                        cout << "                   ";
                        GotoXY(106, 24);
                        cout << "                   ";

                        // Delete pause notice
                        GotoXY(20, 30);
                        cout << "                                                                                                                ";
                        GotoXY(20, 31);
                        cout << "                                                                                                                ";

                        ProcessDead();

                        color(15);
                        GotoXY(106, 12);
                        cout << "ROUND: " << SPEED << "/3";

                        
                        if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')) {
                            if (temp == 'D') CHAR_LOCK = 'A';
                            else if (temp == 'W') CHAR_LOCK = 'S';
                            else if (temp == 'S') CHAR_LOCK = 'W';
                            else CHAR_LOCK = 'D';

                            MOVING = temp;

                            color(15);
                            GotoXY(106, 15);
                            cout << "LENGTH: " << SIZE_SNAKE << " /32";
                        }
                    }
                }
               
                else {
                    SaveGame();
                    if (temp == 'Y') {
                        key = 1;
                        STATE = 1;
                        color(15);
                        StartGame(key);

                        // Print name again
                        color(15);
                        GotoXY(112, 9);
                        cout << NAME;

                        color(15);
                        GotoXY(106, 12);
                        cout << "ROUND: " << SPEED << "/3";

                        GotoXY(106, 15);
                        cout << "LENGTH: " << SIZE_SNAKE << " /32";
                    }
                    else {
                        system("cls");
                        mainMenu(option);
                        StartGame(key);

                        color(15);
                        
                        GotoXY(112, 9);
                        cout << NAME;

                        GotoXY(106, 12);
                        cout << "ROUND: " << SPEED << "/3";

                        GotoXY(106, 15);
                        cout << "LENGTH: " << SIZE_SNAKE << " /32";
                    }
                }
            }
            break;
        case 2:
            STATE = 0;
            if (music == 1)
                music = 0;
            else if (music == 0)
                music = 1;
            mainMenu(option);
            break;
        case 3:
            STATE = 0;
            showLeaderboard();
            system("cls");
            mainMenu(option);
            break;
        case 4: // 
            ExitGame(handle_t1);
            isRun = false;
            break;
        }
    }



    return 0;
}
