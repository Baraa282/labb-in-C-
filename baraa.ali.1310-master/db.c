#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define MAX_DB_SIZE 16

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
    strcat(buf, array2[rand() % size]);    //strcat : concatenates two strings and returns a string in which the two strings are appended
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


void print_menu(){
    puts("[L] ägga till en vara");
    puts("[T] a bort en vara ");
    puts("[R]edigare en vara ");
    puts("Ån[g]ra senaste ändringen ");
    puts("Lista [h]ela varukatalogen");
    puts("[A]vsluta ");

}



// Function to display the menu and get the user's choice
char ask_question_menu() {
    const char valid_choices[] = "LlTtRrGgHhAa";
    char choice;

    do {
        print_menu();
        /*printf("\n"); // Add a newline for better formatting
        // Print the menu
        puts("Menu:");
        printf("[L]ägga till en vara \n"
               "[T]a bort en vara \n"
               "[R]edigare en vara \n"
               "Ån[g]ra senaste ändringen\n"
               "Lista [h]ela varukatalogen\n"
               "[A]vsluta \n");*/
        
        // Prompt the user for input
        printf("Please enter your choice: ");
        choice = tolower(getchar()); // Read the choice and convert it to lowercase
        
        // Clear the input buffer
        while (getchar() != '\n');

    } while (strchr(valid_choices, choice) == NULL); // Check if the choice is valid

    return toupper(choice); // Convert the choice to uppercase and return it
}


item_t* add_item_to_db(item_t db[], int *db_size) {
    if (*db_size >= MAX_DB_SIZE) {
        // Database is full, cannot add more items
        printf("Database is full. Cannot add more items.\n");
        return NULL;
    }

    // Create a new item by taking user input
    item_t *new_item = input_item();
    
    if (new_item == NULL) {
        // Error in creating the item (e.g., memory allocation failed)
        printf("Failed to create the item.\n");
        return NULL;
    }

    // Add the new item to the database
    db[*db_size] = *new_item;
    (*db_size)++; // Increment the database size

    return new_item;
}


// Function to remove an item from the database
void remove_item_from_db(item_t db[], int *db_size) {
    if (*db_size <= 0) {
        // Database is empty, nothing to remove
        printf("Database is empty. Nothing to remove.\n");
        return;
    }

    // Print the current database for the user to select an item to remove
    list_db(db, *db_size);
    
    // Ask the user for the index of the item to remove
    int index_to_remove = ask_question_int("Enter the index of the item to remove (1 to 16): ");

    if (index_to_remove >= 1 && index_to_remove <= *db_size) {
        printf("Removing item at index %d:\n", index_to_remove);
        print_item(&db[index_to_remove - 1]); // Index is 1-based

        // Shift elements to the left to remove the selected item
        for (int i = index_to_remove; i < *db_size; ++i) {
            db[i - 1] = db[i];
        }

        // Decrease the database size
        (*db_size)--;
        
        printf("Item removed successfully!\n");
    } else {
        printf("Invalid index. Please enter a number between 1 and %d.\n", *db_size);
    }
}



// Function to display the menu and handle user actions
void event_loop(item_t db[], int *db_size) {
    char choice;

    do {
        choice = ask_question_menu(); // Display the menu and get the user's choice

        switch (choice) {
            case 'L':
                add_item_to_db(db, db_size); // Add an item to the database
                break;
            case 'T':
                remove_item_from_db(db, db_size); // Remove an item from the database
                break;
            case 'R':
                edit_db(db, *db_size); // Edit an item in the database
                break;
            case 'G':
                printf("Redo not yet implemented!\n"); // Undo latest change
                break;
            case 'H':
                list_db(db, *db_size); // List the whole product catalog
                break;
            case 'A':
                printf("Exiting program.\n"); // Exit the program
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 'E'); // Continue until the user chooses to exit
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
        remove_item_from_db( db ,&db_siz);
        add_item_to_db(db,&db_siz);
        print_menu();


       for (int i = 0; i < db_siz; ++i) {
           print_item(&db[i]);
        }
    }
    return 0;
}






















