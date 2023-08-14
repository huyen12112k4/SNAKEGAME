#include"snake.h"


#pragma comment(lib, "winmm.lib")


int main() {
    system("Color 50");
    PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
            
            while (1) {
                temp = toupper(_getch());
                if (STATE == 1) {
                    if (temp == 'P') {
                        PauseGame(handle_t1);
                    }
                    else if (temp == 27) {
                        STATE = 0;
                        system("cls");
                        mainMenu(option);
                        break;
                    }
                    else {

                        ResumeThread(handle_t1);
                        if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')) {
                            colorKeyBoard(temp);
                            if (temp == 'D') CHAR_LOCK = 'A';
                            else if (temp == 'W') CHAR_LOCK = 'S';
                            else if (temp == 'S') CHAR_LOCK = 'W';
                            else CHAR_LOCK = 'D';

                            MOVING = temp;
                        }
                    }
                }
                else {
                    if (temp == 'Y') {
                        
                        STATE = 1;
                        
                        StartGame();
                    }
                    else {
                        // ResumeThread(handle_t1);
                        system("cls");
                        mainMenu(option);
                        StartGame();
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

    std::cout << "fdfd" << endl;

    return 0;

}
