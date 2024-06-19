#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

// Define OS-specific commands
#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR_COMMAND "cls"
    #define FULLSCREEN_COMMAND "mode con: cols=120 lines=30"
#elif defined(__APPLE__)
    #define CLEAR_COMMAND "clear"
    #define FULLSCREEN_COMMAND "osascript -e 'tell application \"Terminal\" to set bounds of front window to {0, 0, 1920, 1080}'"
#else
    #define CLEAR_COMMAND "clear"
    #define FULLSCREEN_COMMAND "echo -e \"\\e[8;30;120t\""
#endif

using namespace std;

class Node
{
public:
    char data;
    Node* next;

    Node(char val)
    {
        data = val;
        next = nullptr;
    }
};

class LinkedList
{
public:
    Node* start;

    LinkedList()
    {
        start = nullptr;
    }

    void insertRandomly(char data)
    {
        Node* newNode = new Node(data);

        if (start == nullptr)
        {
            start = newNode;
        }
        else
        {
            int listSize = 0;
            Node* temp = start;
            while (temp)
            {
                listSize++;
                temp = temp -> next;
            }

            int randomPosition = rand() % (listSize + 1);
            if (randomPosition == 0)
            {
                newNode -> next = start;
                start = newNode;
            }
            else
            {
                temp = start;
                for (int i = 1; i < randomPosition; i++)
                {
                    temp = temp -> next;
                }
                newNode -> next = temp -> next;
                temp -> next = newNode;
            }
        }
    }

    void printList()
    {
        Node* temp = start;
        while (temp)
        {
            cout << temp -> data << " ";
            temp = temp -> next;
        }
    }

    ~LinkedList()
    {
        while (start)
        {
            Node* temp1 = start;
            start = start -> next;
            delete temp1;
        }
    }

    int count_nodes()
    {
        Node* temp = start;
        int count = 0;
        while(temp != NULL)
        {
            count++;
            temp = temp -> next;
        }
        return count;
    }

    void deletePosition(int position)
    {
        if (position == 0)
        {
            Node* temp = start;
            start = start -> next;
            delete temp;
        }
        else
        {
            int count = 0;
            Node* curr = start;

            while (count != position - 1)
            {
                curr = curr -> next;
                count++;
            }

            Node* actualNode = curr -> next;
            curr -> next = actualNode -> next;
            delete actualNode;
        }
    }

    char getnodedata(int pos)
    {
        Node* temp = start;
        int count=0;
        while(temp != NULL)
        {
            if(count == pos)
            {
                return temp -> data;
            }
            else
            {
                temp = temp -> next;
                count++;
            }
        }
    }
};

void loadingbar()
{
    cout << "\n\n\n\n";
    cout << "\n\n\n\n\t\t\t\t\t";
    cout << "Loading...\n\n\n";
    cout << "\t\t\t\t\t";
    for (int i = 0; i < 26; i++)
    {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main()
{
    system(CLEAR_COMMAND); // Clear the screen

    // Run OS-specific command for full-screen
    system(FULLSCREEN_COMMAND);

    loadingbar();
    system(CLEAR_COMMAND); // Clear the screen

    cout << "WELCOME TO THE MEMORY GAME" << endl;

    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);
    cout << endl;
    cout << endl;
    cout << "The time of playing is = " << asctime(ti);
    this_thread::sleep_for(chrono::seconds(5));
    system(CLEAR_COMMAND);

    int n;
    cout << "Enter the number of players : ";
    cin >> n;
    int arr_scores[n];
    string arr_names[n];
    system(CLEAR_COMMAND);
    for(int i=0; i<n; i++)
    {
        cout << "Enter the name of player " << i+1 << ": ";
        cin >> arr_names[i];
        system(CLEAR_COMMAND);

        srand(static_cast<unsigned>(time(0)));
        LinkedList linkedlist;
        char characters[5];

        int score=0;

        cout << "Enter the 5 characters you want to make a part of the memory game" << endl;
        cout << endl;
        for (int i = 0; i < 5; i++)
        {
            cin >> characters[i];
        }

        for (int i = 0; i < 5; i++)
        {
            linkedlist.insertRandomly(characters[i]);
            linkedlist.insertRandomly(characters[i]);
        }

        cout << "You will now be shown the randomly generated sequence for a short amount of time" << endl;
        linkedlist.printList();
        cout << endl;

        this_thread::sleep_for(chrono::seconds(5));
        system(CLEAR_COMMAND);

        int pos1, pos2;
        char alphabet1, alphabet2;
        int flag=5;
        int no_of_asterisks;
        while (flag != 0)
        {
            no_of_asterisks = linkedlist.count_nodes();
            for(int i=0; i<no_of_asterisks; i++)
            {
                cout << "* ";
            }
            cout << endl;
            cout << "Enter the 2 positions of which the character matches" << endl;
            cin >> pos1 >> pos2;
            if(pos1 >= 1 && pos1 <= no_of_asterisks && pos2 >= 1 && pos2 <= no_of_asterisks)
            {
                alphabet1 = linkedlist.getnodedata(pos1-1);
                alphabet2 = linkedlist.getnodedata(pos2-1);
                if(alphabet1 == alphabet2)
                {
                    flag--;
                    cout << "The alphabets at the two positions entered match" << endl;
                    linkedlist.deletePosition(pos1-1);
                    if (pos1 - 1 < pos2 - 1)
                    {
                        linkedlist.deletePosition(pos2 - 2);
                    }
                    else
                    {
                        linkedlist.deletePosition(pos2 - 1);
                    }
                    cout << "The element removed from the game is = " << alphabet1 << endl;
                }
                else
                {
                    cout << "The alphabets at the 2 positions entered do not match" << endl;
                }
            }
            else
            {
                cout << "Entered positions are not valid as the positions should be between 1 and " << no_of_asterisks << endl;
                cout << "Re-enter proper positions again" << endl;
            }
            score++;
            this_thread::sleep_for(chrono::seconds(4));
            system(CLEAR_COMMAND);
        }

        cout << "CONGRATULATIONS !!! YOU FINISHED THE GAME !!!" << endl;
        cout << "Your score for this game is = " << score << endl;
        this_thread::sleep_for(chrono::seconds(3));
        system(CLEAR_COMMAND);
        arr_scores[i] = score;
    }

    cout << "LEADERBOARD" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Player\t\tScore" << endl;
    cout << "--------------------------------------" << endl;
    for(int i=0; i<n; i++)
    {
        cout << arr_names[i] << "\t\t" << arr_scores[i] << endl;
    }
    cout << "--------------------------------------" << endl;
    cout << "The WINNER of the game is:" << endl;

    int min = arr_scores[0];
    int index = 0;
    for(int i=0; i<n; i++)
    {
        if(arr_scores[i] < min)
        {
            min = arr_scores[i];
            index = i;
        }
    }
    cout << arr_names[index] << " with a score of " << min << endl;

    return 0;
}
