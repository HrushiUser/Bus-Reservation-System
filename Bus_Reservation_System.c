#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 5
#define COLS 4
typedef struct
{
    char name[50];
    char phone[15];
    char email[50];
    char gender[10];
    int seatNumber;
} Booking;
typedef struct
{
    int serviceNumber;
    char busName[50];
    char type[50];
    char departure[10];
    char arrival[10];
    char routeFrom[20];
    char routeTo[20];
    int price;
} BusService;
BusService busServices[] =
{
    {12345, "Amaravati", "Volvo Multi Axle A/C", "09:00", "05:00", "Vijayawada", "Hyderabad", 650},
    {23456, "Airavat", "Volvo Multi Axle A/C", "07:00", "08:00", "Bangalore", "Hyderabad", 1050},
    {34567, "Garuda Plus", "Scania A/C Semi Sleeper", "11:00", "09:00", "Hyderabad", "Visakhapatnam", 800},
    {45678, "Intercity Smart", "Scania A/C Sleeper", "11:45", "09:30", "Vijayawada", "Bangalore", 1020},
    {56789, "SETC", "A/C Sleeper", "07:00", "11:00", "Bangalore", "Chennai", 500},
    {67890, "Nuego", "A/C Semi Sleeper", "08:00", "05:00", "Chennai", "Hyderabad", 800}
};
int seats[ROWS][COLS] = {0};
void displayRoutes()
{
    printf("\nAvailable Bus Routes:\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < sizeof(busServices) / sizeof(busServices[0]); i++)
    {
        printf("%d. %s -> %s\n", i + 1, busServices[i].routeFrom, busServices[i].routeTo);
    }
    printf("-----------------------------------------------\n");
}
int displayBusServices(const char *from, const char *to)
{
    printf("\nAvailable Bus Services from %s to %s:\n", from, to);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Service No | Bus Name      | Type                      | Departure | Arrival | Source      | Destination | Price \n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    int found = 0;
    for (int i = 0; i < sizeof(busServices) / sizeof(busServices[0]); i++)
    {
        if (strcmp(busServices[i].routeFrom, from) == 0 && strcmp(busServices[i].routeTo, to) == 0)
        {
            found = 1;
            printf("%-11d| %-13s | %-25s | %-9s | %-7s | %-10s | %-12s | %d\n", 
                   busServices[i].serviceNumber, 
                   busServices[i].busName, 
                   busServices[i].type,
                   busServices[i].departure, 
                   busServices[i].arrival,
                   busServices[i].routeFrom, 
                   busServices[i].routeTo, 
                   busServices[i].price);
        }
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    return found;
}
void displaySeats()
{
    printf("\n[ ] - Available   [o] - Booked   [W] - Window Seat\n");
    printf("  -----------------------\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf(" |");
        for (int j = 0; j < COLS; j++)
        {
            char isWindow = (j == 0 || j == COLS - 1) ? 'W' : ' ';
            if (seats[i][j] == 0)
                printf(" [%c%d] ", isWindow, (i * COLS) + j + 1);
            else
                printf(" [o%c%d] ", isWindow, (i * COLS) + j + 1);
        }
        printf(" |\n");
    }
}
void waitForEnter()
{
    int ch;
    while ((ch = getchar()) != '\n') { }
    printf("\nPress Enter to proceed...\n");
    getchar();
}
int main()
{
    char from[20], to[20];
    int seatNumber, row, col, paymentOption;
    Booking user;
    printf("Welcome to the Bus Reservation System!\n");
    printf("---------------------------------------------------\n");
    while (1)
    {
        displayRoutes();
        printf("\nEnter Source City: ");
        scanf("%s", from);
        printf("Enter Destination City: ");
        scanf("%s", to);
        if (displayBusServices(from, to))
            break;
        else
            printf("No Bus Services Available for this Route! Please enter a valid route.\n");
    }
    waitForEnter();
    printf("\nSeat Layout:\n");
    displaySeats();
    while (1)
    {
        printf("\nEnter your seat number (1-30): ");
        scanf("%d", &seatNumber);
        row = (seatNumber - 1) / COLS;
        col = (seatNumber - 1) % COLS;
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS || seats[row][col] != 0)
        {
            printf("Invalid or Already Booked Seat!\n");
        }
        else
        {
            seats[row][col] = 1;
            user.seatNumber = seatNumber;
            break;
        }
    }
    printf("\nEnter Your Name: ");
    scanf("%s", user.name);
    printf("Enter Your Phone Number: ");
    scanf("%s", user.phone);
    printf("Enter Your Email: ");
    scanf("%s", user.email);
    printf("Enter Your Gender (Male/Female/Other): ");
    scanf("%s", user.gender);
    printf("\nPayment Options:\n");
    printf("1. Google Pay\n2. Phone Pay\n3. Credit Card\n4. Razorpay\n");
    printf("Select payment method (1-4): ");
    scanf("%d", &paymentOption);
    printf("\nBooking Confirmed!\n");
    printf("Route: %s to %s | Seat No: %d\n", from, to, user.seatNumber);
    printf("Passenger: %s | Phone: %s | Email: %s\n", user.name, user.phone, user.email);
    printf("Payment: %s\n", paymentOption == 1 ? "Google Pay" :
                             paymentOption == 2 ? "Phone Pay" :
                             paymentOption == 3 ? "Credit Card" : "Razorpay");
    printf("\nMessage Sent to Your Phone Number: Your ticket from %s to %s is confirmed.\n", from, to);
    printf("Thank you for using our service!\n");
    return 0;
}
