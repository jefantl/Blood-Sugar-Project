#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

//Custom linked list class

/*
Linked list node class:
This is the node to store the next node and the value, stored as a double for this situation
*/
class ListNode
{

public:
    double value;
    ListNode *nextNode;
    ListNode(double inNum)
    {
        value = inNum;
        nextNode = NULL;
    }
};

/*
Linked list class:
This class organizes and stores the nodes that keep track of the blood sugar records

This class stores:
    Length of the list

This class has the ability to:
    Add a new record
    Access a node
*/
class LinkedList
{
private:
    ListNode *head, *tail;
public:
    int length = 0;
    LinkedList()
    {
        head = NULL;
        tail = head;
    }

    void addNode(double inInt)
    {
        length++;
        ListNode *newNode = new ListNode(inInt);
        if(head == NULL)
            head = newNode;
        else
        {
            tail->nextNode = newNode;
        }
        tail = newNode;
    }

    ListNode getNode(int index)
    {
        if(index >= length)
        {
            cout << "List index out of bounds error" << endl;
            return NULL;
        }
        int counter = 0;
        ListNode *returnNode = head;
        while(counter != index)
        {
            counter++;
            returnNode = returnNode->nextNode;
        }
        return *returnNode;
    }

    double sum()
    {
        double finalSum(0);
        ListNode *tempNode = head;
        while(tempNode != NULL)
        {
            finalSum += tempNode->value;
            tempNode = tempNode->nextNode;
        }
        return finalSum;
    }

};


/*
Blood sugar record for a day:
This class keeps track of all the records for each day and can report information

This class stores:
    The linked list of records

This class has the ability to:
    Add a record
    Sum all the records into a value
    Find the largest value of the day
    Find the smallest value of the day
    Find the number of records stored
    Print a summary of all the records of the day
*/
class bloodSugarDayRecord
{
public:

    bloodSugarDayRecord()
    {
    }
    LinkedList bloodSugarRecords;

    void addRecord(double inValue)
    {
        bloodSugarRecords.addNode(inValue);
    }
    double sum()
    {
        return bloodSugarRecords.sum();
    }

    double maxBloodSugarLevel()
    {
        if(bloodSugarRecords.length > 0)
        {
            double largestValue = bloodSugarRecords.getNode(0).value;
            for(int i = 1; i < bloodSugarRecords.length; i++)
            {
                double value = bloodSugarRecords.getNode(i).value;
                if(value > largestValue)
                {
                    largestValue = value;
                }
            }
            return largestValue;
        }
        return -1;
    }
    double minBloodSugarLevel()
    {
        if(bloodSugarRecords.length > 0)
        {
            double smallestValue = bloodSugarRecords.getNode(0).value;
            for(int i = 1; i < bloodSugarRecords.length; i++)
            {
                double value = bloodSugarRecords.getNode(i).value;
                if(value < smallestValue)
                {
                    smallestValue = value;
                }
            }
            return smallestValue;
        }
        return -1;
    }
    int count()
    {
        return bloodSugarRecords.length;
    }
    void printDaySummary()
    {
        cout << "Number of blood sugar readings so far: " << count() << endl;
        cout << "Max blood sugar reading so far: " << maxBloodSugarLevel() << endl;
        cout << "Min blood sugar reading so far: " << minBloodSugarLevel() << endl;
        cout << "Sum blood sugar reading so far: " << sum() << endl;

    }
};


/*
Blood sugar record for a week:
This class keeps track of all the records for each week and can report information

This class stores:
    The linked list of daily records

This class has the ability to:
    Add a record to a specific day
    Sum all the records into a value
    Find the largest value of the week
    Find the smallest value of the week
    Find the number of records stored
    Find the day with the largest change in blood sugar
    Print a summary of all the records of the week
*/
class bloodSugarWeekRecord
{
    bloodSugarDayRecord dayRecords[7];
    int counter;

public:

    bloodSugarWeekRecord ()
    {
        counter = 0;
    }
    void addRecord(double newRecord, int day)
    {
        if(day >= 0 && day < 7 && newRecord > 0)
        {
            dayRecords[day].addRecord(newRecord);
            counter++;
        }
    }
    int count()
    {
        return counter;
    }
    double sum()
    {
        double summedValue = 0;
        for(int i = 0; i < 7; i++)
        {
            summedValue += dayRecords[i].sum();
        }
        return summedValue;
    }
    double maxBloodSugarLevel()
    {
        double largestValue = dayRecords[0].maxBloodSugarLevel();
        for(int i = 1; i < 7; i++)
        {
            double maxVal = dayRecords[i].maxBloodSugarLevel();
            if(maxVal > largestValue)
            {
                largestValue = maxVal;
            }
        }
        return largestValue;
    }
    double minBloodSugarLevel()
    {
        double smallestValue = dayRecords[0].minBloodSugarLevel();
        for(int i = 1; i < 7; i++)
        {
            double minVal = dayRecords[i].minBloodSugarLevel();
            if(minVal > 0 && (smallestValue < 0 || minVal < smallestValue))
        {
            smallestValue = minVal;
        }
    }
    return smallestValue;
}

int dayWithLargestDelta()
    {
        int day = 1;
        int delta = abs(dayRecords[1].count() - dayRecords[0].count());
        for(int i = 2; i < 7; i++)
        {
            int newDelta = dayRecords[i].count() - dayRecords[i].count();
            if(newDelta > delta)
            {
                delta = newDelta;
                day = i;
            }
        }
        return day;
    }

    void printWeekSummary()
    {
        cout << "Number of blood sugar readings so far: " << count() << endl;
        cout << "Max blood sugar reading so far: " << maxBloodSugarLevel() << endl;
        cout << "Min blood sugar reading so far: " << minBloodSugarLevel() << endl;
        cout << "Day with largest change in blood sugar readings so far: day " << dayWithLargestDelta() + 1 << endl;
    }
    void printDaySummary(int day)
    {
        dayRecords[day].printDaySummary();
    }
};

int main()
{
    int currentDay = 0;

    bloodSugarWeekRecord weeks[2];
    int currentWeekIndex = 0;

    string userInput;
    while(true)
    {
        bloodSugarWeekRecord *currentWeek = &weeks[currentWeekIndex];

        cout << "to quit: Q, Quit" << endl << "to move to the next day: N, Next" << endl;
        cout << "to get weekly summary: W, Week" << endl << "to get daily summary: D, Day" << endl;
        cout << "to enter a new record just type in the value (must be between 0 - 1.7*10^308" << endl;
        cin >> userInput;

        std::stringstream ss;
        double possibleNewInput;
        ss << userInput;
        if(ss >> possibleNewInput && possibleNewInput > 0) //this will only happen if the user inputs a valid number
        {
            currentWeek->addRecord(possibleNewInput, currentDay);
            cout << "added record of " << possibleNewInput << " on day " << currentDay + 1 << " of week " << currentWeekIndex + 1<<endl;
        }
        else if(userInput.compare("N") == 0 || userInput.compare("Next") == 0)
        {
            cout << "Summary for day " << currentDay + 1 << " of week " << currentWeekIndex + 1 << endl;
            currentWeek->printDaySummary(currentDay);
            currentDay++;
            if(currentDay > 6)
            {
                currentDay = 0;
                currentWeekIndex++;
            }
            cout << "its now day: " << currentDay + 1 << " of week " << currentWeekIndex + 1 << endl;

        }
        else if(userInput.compare("D") == 0 || userInput.compare("Day") == 0)
        {
            cout << "Summary for day " << currentDay + 1 << " of week " << currentWeekIndex + 1 << endl;
            currentWeek->printDaySummary(currentDay);
        }
        else if(userInput.compare("W") == 0 || userInput.compare("Week") == 0)
        {
            cout << "Summary for week " << currentWeekIndex + 1 << endl;
            currentWeek->printWeekSummary();
        }
        else if (!(!(userInput.compare("Q") == 0) && !(userInput.compare("Quit") == 0)))
        {
            cout << "quitting";
            break;
        }
        else
        {
            cout << "Command not recognized, please re-enter" << endl;
        }
        cout << endl;
    }
    return 0;
}
