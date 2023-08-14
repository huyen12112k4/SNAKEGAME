#include"snake.h"


#pragma comment(lib, "winmm.lib")


int main() {
  
    int temp, option;
    FixConsoleWindow();
    
    mainMenu(option);
    thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();
    
    bool isRun = true;
    string s;
    
    while (isRun) {
        
        if (option == 4) {
            ExitGame(handle_t1);
            break;
        }

        STATE = 1;
        switch (option) {

        case 1:
            STATE = 0;
            s = InputName();
            STATE = 1;

            StartGame();
            // Print name
            color(15);
            GotoXY(112, 9);
            cout << s;

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
                    else {
                        ResumeThread(handle_t1);
                        // Delete pause
                        color(249);
                        GotoXY(106, 23);
                        UINT old_cp = GetConsoleOutputCP();
                        SetConsoleOutputCP(CP_UTF8);
                        cout << u8"                   ";
                        GotoXY(106, 24);
                        cout << u8"                   ";
                        SetConsoleOutputCP(old_cp);

                        // Delete pause notice
                        GotoXY(20, 30);
                        cout << u8"                                                                                                                ";
                        GotoXY(20, 31);
                        cout << u8"                                                                                                                ";

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
                    if (temp == 'Y') {
                        
                        STATE = 1;
                        color(15);
                        StartGame();
                        // Print name again
                        color(15);
                        GotoXY(112, 9);
                        cout << s;

                        color(15);
                        GotoXY(106, 12);
                        cout << "ROUND: " << SPEED << "/3";

                        GotoXY(106, 15);
                        cout << "LENGTH: " << SIZE_SNAKE << " /32";
                    }
                    else {
                        system("cls");
                        mainMenu(option);
                        StartGame();

                        color(15);
                        GotoXY(112, 9);
                        cout << s;

                        color(15);
                        GotoXY(106, 12);
                        cout << "ROUND: " << SPEED << "/3";

                        GotoXY(106, 15);
                        cout << "LENGTH: " << SIZE_SNAKE << " /32";
                    }
                }
            }
            break;
        case 2:
            mainMenu(option);
            break;
        case 3:
            mainMenu(option);
            break;
        case 4:
            ExitGame(handle_t1);
            isRun = false;
            break;
        }
    }


    return 0;

}
