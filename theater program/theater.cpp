#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
using namespace std;

const int rows = 15, columns = 30;

void menu_display(); // Ian
void ticketpriceread(double seatprices[rows]);
void sell_ticket();
void choice_5();
void seat_overwrite(char seating_chart[rows][columns]);
void total_price();
void show_price_per_row();
void seatingarray_data(char seating_chart[rows][columns]); // Ian
void show_seatingchart(char seating_chart[rows][columns]); // Ian
bool yes_no_validation(char choice); // Walker
void set_price(); // Walker & Ian
void show_summary();
void file_read();

int main() 
{
  double seatprices[rows];
  int choice;
  bool seating_chart_bool[rows][columns];
  
  char seating_chart[rows][columns]; // The updating seating chart

  seatingarray_data(seating_chart); // This function collects data for the seating_chart array
  cout << "======== Theater Seating System Program ========" << endl;
  cout << endl;
  do
  {
    menu_display();
    cout << "Enter your choice: " << endl;
    cin >> choice;
    cout << endl;
    if (choice == 1) // Sell seats
    {
      sell_ticket();
      
    }
    if (choice == 2) // Show seating chart
    {
      show_seatingchart(seating_chart);
    }
    if (choice == 3) // Summary
    {
      show_summary();
    }
    if (choice == 4) // Change ticket price
    {
      set_price();
    }
    if (choice == 5)
    {
      choice_5();
    }
  }while (choice != 6);
  
  return 0;
} 

void menu_display() // Ian
{
  cout << "           ========= Menu =========" << endl;
  cout << "1. Sell seats" << endl;
  cout << "2. Show seating chart" << endl;
  cout << "3. Summary" << endl;
  cout << "4. Change ticket price" << endl;
  cout << "5. Choose Theater Layouts" << endl;
  cout << "6. Exit the program" << endl;
}


void sell_ticket()
{
  int choice_row, choice_column;
  char seating_chart[rows][columns];
  char available = '#';
  char unavailable = '*';

  bool flag = false;
  char choice;

  
  double seatprices[rows];

  do
  {
    show_seatingchart(seating_chart);
    cout << "Enter what seat you want to buy: " << endl;
    do
    {
      cout << "Enter the row: " << endl;
      cin >> choice_row;
      if (choice_row < 1 || choice_row > 15)
      {
        cin.clear();
        cout << "Only rows 1-15 exist. Try again." << endl;
      }
    }while (choice_row < 1 || choice_row > 15);
    choice_row = choice_row - 1;
    do
    {
      cout << "Enter the column" << endl;
      cin >> choice_column;
      if (choice_column < 1 || choice_column > 30)
      {
        cin.clear();
        cout << "Only columns 1-30 exist. Try again." << endl;
      }
    }while (choice_column < 1 || choice_column > 30);

    choice_column = choice_column - 1;
    seatingarray_data(seating_chart);
    ticketpriceread(seatprices);

    if (seating_chart[choice_row][choice_column] == unavailable)
    {
      cout << "Seat is unavailable. Try again." << endl;
    }
    
    if (seating_chart[choice_row][choice_column] == available)
    {
      cout << "Seat is available. The price is: $" << seatprices[choice_row] << endl;
      cout << "Would you like to buy this seat? [Y/N] " << endl;
      cin >> choice;
      flag = yes_no_validation(choice);

      seating_chart[choice_row][choice_column] = '*';
      
      seat_overwrite(seating_chart);
      
      cout << "Would you like another ticket? [Y/N]" << endl;
      cin >> choice;
      if (choice == 'Y' || choice == 'y')
      {
        flag = false;
      }
    }
  } while (flag == false);
  cout << endl;
}

void seat_overwrite(char seating_chart[rows][columns])
{
  std::ofstream file;
      file.open("seatingchart.txt", std::ofstream::out | std::ofstream::trunc);
      for (int i = 0; i < 15; i++) // i is the row
      { 
        for (int j = 0; j < 30; j++) // j is the seat for that row
        {
          file << seating_chart[i][j];
        }
      }
      file.close();
}

void ticketpriceread(double seatprices[rows])
{
  ifstream inputFile; //need this to open the seating chart file
  inputFile.open("ticketprice.txt");
  for (int i = 0; i < 15; i++)
  {
    inputFile >> seatprices[i];
  }
  inputFile.close();
}

void seatingarray_data(char seating_chart[rows][columns]) // Ian !call this function after you change the value of something in the seatingchart.txt so that the seating chart array can update (when you change seats from available to unavailable)
{
  ifstream inputFile; //need this to open the seating chart file
  inputFile.open("seatingchart.txt"); //Open the seatingchart.txt file
  
  for (int i = 0; i < 15; i++) // i is the row
  { 
    for (int j = 0; j < 30; j++) // j is the seat for that row
    {
      inputFile >> seating_chart[i][j]; //gets the character from the input file
    }
  }
  inputFile.close();
}

void show_seatingchart(char seating_chart[rows][columns]) // Ian
{
  seatingarray_data(seating_chart);
  cout << "       " << "123456789012345678901234567890" << endl;
  for (int i = 0; i < 15; i++) // 
  {
    cout << "Row " << (i+1) << " ";    
    if (i < 9) // output alignment 
    {
      cout << " ";
    }    
    for (int j = 0; j < 30; j++)
      {
        cout << seating_chart[i][j];
      }
    cout << endl;
  }
  cout << endl;
}

bool yes_no_validation(char choice) // Walker
{

    choice = toupper(choice);

    while (choice != 'Y' && choice != 'N')
    {

        cout << "Invalid input." << endl
            << "Please enter [Y/N]: ";
        cin >> choice;
        choice = toupper(choice);
    }

    if (choice == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void set_price() // Walker & Ian
{
  bool flag = false;
  char choice;
  double price;
  
  std::ofstream file;
  file.open("ticketprice.txt", std::ofstream::out | std::ofstream::trunc); //clear ticket prices to change everything

  
  do
  {
    for (int i = 0; i < 15; i++)
    {
      do
      {
        cout << "Enter the price for seats in Row "
        << i + 1 << ": $";
        cin >> price;
        if (price < 0)
        {
          cout << "Try again. Must be a positive price." << endl;
          cin.clear();
        }
        if (price > 0)
        {
          file << price << " ";
        }
      } while (price < 0);
    }
    cout << endl
    << "Would you like to comfirm the seat prices?[Y/N]: ";
    cin >> choice;
    cout << endl;
    flag = yes_no_validation(choice);
  }while (flag == false);
}

bool seating_chart_search(char seating_chart[rows][columns])
{
/* for() 
    {
      
    }*/
}

void seat_count()
{
  char filename[30], ch, str[1000];
  int tot=0, i=0, tot_sold=0;
  ifstream fp;
  fp.open("seatingchart.txt");
  while(fp>>noskipws>>ch)
  {
    str[tot] = ch;
    tot++;
  }
  fp.close();
  str[tot]='\0';
  while(str[i]!='\0')
  {
    if(str[i]=='*')
        tot_sold++;
    i++;
  }
  cout<<endl<<"Number of seats sold: "<<tot_sold<<endl;
  cout<<endl;
}

void show_summary() // ==================================================+++++++
{
  int total_seats, seats_sold;
  float total_revenue;
  
  total_seats = rows * columns; //total seat count
  cout << "Total number of seats: " << total_seats << endl;

  seat_count();
  total_price();
  cout << endl;
  show_price_per_row();
  cout << endl;
}

void show_price_per_row()
{
  double seatprices[rows];
  ticketpriceread(seatprices);
  for (int i = 0; i < 15; i++)
  {
    cout << "Price for seats on row " << i+1 << " is $" << seatprices[i] << endl;  
  }
}

void total_price()
{
  
  float price;
  float total_price = 0;
  double seatprices[rows];
  char seating_chart[rows][columns];
  for (int i = 0; i < 15; i++)
  {
    ticketpriceread(seatprices);
    price = seatprices[i]; //ticket price for that row
    for (int j = 0; j < 30; j++)
    {
      seatingarray_data(seating_chart);
      if (seating_chart[i][j] == '*')
      {
        total_price = total_price + price;
      }
    }
  }
  cout << "Total revenue from seats is: $" << total_price << endl;
}



void choice_5()
{
  char seating_chart[rows][columns];
  int choice1;
  do
  {
    cout << "Choose a scenario layout to set the theater to: " << endl;
    cout << "1. Default Layout (Original Scenario) " << endl;
    cout << "2. Empty Theater" << endl;
    cout << "3. Go back to menu" << endl;
    cout << "Enter your choice: " << endl;
    cin >> choice1;
    if (choice1 == 1)
    {
      ifstream inputFile;
      inputFile.open("default_seatingchart.txt");
      for (int i = 0; i < 15; i++) 
      { 
        for (int j = 0; j < 30; j++) 
        {
          inputFile >> seating_chart[i][j]; 
        }
      }
      inputFile.close();
      seat_overwrite(seating_chart);
      cout << endl;
      cout << "---------Theater layout set to default---------" << endl;
      choice1 = 3;
    }
    if (choice1 == 2)
    {
      for (int i = 0; i < 15; i++) 
      { 
        for (int j = 0; j < 30; j++) 
        {
          seating_chart[i][j] = '#'; 
        }
      }
      seat_overwrite(seating_chart);
      cout << endl;
      cout << "---------Theater layout set to empty---------" << endl;
      choice1 = 3;
    }
    
  }while (choice1 != 3);
  cout << endl;
}
