#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>



struct item {
    char *name;
    char *description;
    int price;                  // does not require dynamic memory allocate or poninters
    char *shelf;                // used to store string which the best represented as pointers to dyn all char arrys
};


typedef struct item item_t;    //create new type item_t as an alias for struct item


void print_item(item_t *item) {
    printf("Name: %s\n", item->name);
    printf("Desc: %s\n", item->description);
    printf("Price: %d.%d SEK\n", item->price / 100, item->price % 100);
    printf("Shelf: %s\n", item->shelf);
    printf("\n");
}

item_t* make_item(const char* name, const char* description, int price, const char* shelf) {
    item_t* new_item = malloc(sizeof(item_t));   //allocates memory for new item
    if (new_item != NULL) {
        new_item->name = strdup(name); //allocates memory and copies the name string into it
        new_item->description = strdup(description);
        new_item->price = price;
        new_item->shelf = strdup(shelf);
    }
    return new_item;
}

int ask_question_int(char *question) {  //ask user input and reads an integer
    int result = 0;
    int conversions = 0;
    do {
        printf("%s\n", question);
        conversions = scanf("%d", &result); //try to read an int from input
        int c;
        do {
            c = getchar();     // read char untill a newline 
        } while (c != '\n');
        putchar('\n');
    } while (conversions < 1);  //repeat if no successfull conversion took a place
    return result;
}

char *ask_question_string(char *question, char *buf, int buf_siz) {
    printf("%s\n", question);
    fgets(buf, buf_siz, stdin);           // Read string from the user's input and store it in 'buf'
    buf[strcspn(buf, "\n")] = 0;        // remove trailing newline
    return strdup(buf);                // return a dynamicaly allocated copy of buf
}

char *ask_question_shelf(char *question, char *buf, int buf_siz) {
    do {
        ask_question_string(question, buf, buf_siz);
        if (isalpha(buf[0]) && isdigit(buf[1])) { // check if first character is a letter and second character is a digit
            break;
        } else {
            printf("Invalid shelf format. Please enter a letter followed by one or more numbers.\n");
        }
    } while (1);

    return strdup(buf);
}

item_t *input_item() {
    char buf[256];
    
    char *name = ask_question_string("Enter item name: ", buf, sizeof(buf));
    char *desc = ask_question_string("Enter item description: ", buf, sizeof(buf));
    int price = ask_question_int("Enter item price in öre: ");
    char *shelf = ask_question_shelf("Enter item shelf (e.g., A25): ", buf, sizeof(buf));

    return make_item(name, desc, price, shelf);
}


// Function to generate a random phrase from three input arrays

char* magick(char *array1[], char *array2[], char *array3[], int size) {
    char buf[255] = {0}; // Initialize a character buffer to store the generated phrase

    // pick a random word from each array and concatenate them in buf
    strcat(buf, array1[rand() % size]); // Randomly select a word from array1 and append it to 'buf'
    strcat(buf, "-"); // Add a hyphen separator
    strcat(buf, array2[rand() % size]);
    strcat(buf, " "); //Add a space separator
    strcat(buf, array3[rand() % size]);

    return strdup(buf); // duplicate the string to return it
}




void list_db(item_t *items, int no_items) {
    for (int i = 0; i < no_items; ++i) {
        printf("%d. %s\n", i + 1, items[i].name);
    }
}
 


//this function asks the user for the index of the item to edit
void edit_db(item_t db[], int db_siz) {
    int index = ask_question_int("Enter the index of the item to edit (1 to 16): ");
    
    if (index >= 1 && index <= db_siz) {
        printf("Editing item at index %d:\n", index);
        print_item(&db[index - 1]); // Index is 1-based
        
        // Create a new item with user input
        item_t *new_item = input_item();
        
        // Deallocate memory for the old item
        free(db[index - 1].name);
        free(db[index - 1].description);
        free(db[index - 1].shelf);
        
        // Replace the old item with the new one
        db[index - 1] = *new_item;
        
        printf("Item edited successfully!\n");
    } else {
        printf("Invalid index. Please enter a number between 1 and %d.\n", db_siz);
    }
}


int ask_question_menu() {
    int choice;
    
    printf("Menu:\n");
    printf("1. Add item\n");
    printf("2. List items\n");
    printf("3. Edit item\n");
    printf("4. Undo\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);
    getchar(); // Consume the newline character
    
    return choice;
}


void event_loop(item_t *db, int *db_siz) {
    int choice;

    do {
        choice = ask_question_menu(); // Implement ask_question_menu() to display the menu and get the user's choice.

        switch (choice) {
            case 1:
                if (*db_siz < 16) {
                    // Add an item to the database
                    item_t *item = input_item();
                    db[*db_siz] = *item;
                    ++(*db_siz);
                    free(item);
                    printf("Item added successfully!\n");
                } else {
                    printf("Sorry, the database is full.\n");
                }
                break;
            case 2:
                list_db(db, *db_siz); // List items in the database
                break;
            case 3:
                edit_db(db, *db_siz); // Edit an item in the database
                break;
            case 4:
                printf("Not yet implemented!\n"); // Undo selection
                break;
            case 5:
                printf("Exiting the program.\n"); // Exit
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 5); // Continue until the user selects the exit option (5)
}



// ... (include your struct and function definitions here) ...

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char *array1[] = { "Laser", "Polka", "Extra" };
    char *array2[] = { "fornicklad", "smakande", "ordinar" };
    char *array3[] = { "skruvdragare", "kola", "uppgift" };
    int array_size = sizeof(array1) / sizeof(array1[0]); // size of the arrays

    if (argc < 2) {
        printf("Usage: %s number\n", argv[0]);
    } else {
        item_t db[16]; // Array with space for 16 items
        int db_siz = 0; // The number of items in the array right now

        int items = atoi(argv[1]); // The number of items to be created
        
        if (items > 0 && items <= 16) {
            for (int i = 0; i < items; ++i) {
                // Read in an item, add it to the array, increase the size counter
                item_t *item = input_item();
                db[db_siz] = *item;
                ++db_siz;
            }
        } else {
            puts("Sorry, must have [1-16] items in database.");
            return 1; // Ends the program!
        }

        for (int i = db_siz; i < 16; ++i) {
            char *name = magick(array1, array2, array3, array_size);
            char *desc = magick(array1, array2, array3, array_size);
            int price = random() % 200000;
            char shelf[] = { rand() % ('Z'-'A') + 'A',
                             rand() % 10 + '0',
                             rand() % 10 + '0',
                             '\0' };
            item_t *item = make_item(name, desc, price, shelf);

            db[db_siz] = *item;
            ++db_siz;
            free(name);
            free(desc);
        }

        // Print out the contents
        list_db(db,db_siz);
        edit_db(db, db_siz);
        event_loop(db, &db_siz);


       for (int i = 0; i < db_siz; ++i) {
           print_item(&db[i]);
        }
    }
    return 0;
}






















