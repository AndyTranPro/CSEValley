// z5352187
// CSE Valley
// cse_valley.c
//
// This program was written by Tan-Tai-Tran (Andy Tran) (z5352187)
// on 10-13-2021
//
// Version 1.0.0 (2021-10-04): Assignment Released.
//
// DESCRIPTION: This program is a farming game that allows you to play as a
// real farmer who plants and waters the seeds as well as taking care of them
// day by day until they are harvestable. ENJOY IT! ^-^

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_NAME_SIZE 50
#define MAX_NUM_SEED_TYPES 26
#define LAND_SIZE 8
#define NO_SEED ' '
#define TRUE 1
#define FALSE 0

struct land {
    int is_watered;
    char seed_name;
};

struct seeds {
    char name;
    int amount;
};

struct farmer {
    int curr_col;
    int curr_row;
    char curr_dir;
};

int lowercase_checking (char a);

struct farmer moving_around (char command, struct farmer cse_farmer);

void printing_all_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES], 
int n);

void printing_one_seed(struct seeds seed_collection[MAX_NUM_SEED_TYPES], 
char command_2, int n);

struct farmer boundaries(struct farmer cse_farmer);

void watering_land (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct farmer cse_farmer);

void planting_seed (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], struct farmer cse_farmer, 
char command_3, int n);

int changed_amount (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], char command_2, int correct, 
int x, int y);

void in_bound (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], char command_2, char dir, 
int i, int correct, int x, int y);

void planting_multiple (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], struct farmer cse_farmer, 
char command_2, int n);

void square_watering (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct farmer cse_farmer, int size);

int seed_name_checking (char a, 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], int n);

struct land tomorrow (struct land farm_land[LAND_SIZE][LAND_SIZE], 
int i, int j, char s_name);

void next_day (struct land farm_land[LAND_SIZE][LAND_SIZE], int day);

void harvesting (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct farmer cse_farmer, struct seeds seed_collection [MAX_NUM_SEED_TYPES], 
int n);

int num_checking (int num_trade, 
struct seeds seed_collection[MAX_NUM_SEED_TYPES], int identity);

void trading_seed(struct seeds seed_collection[MAX_NUM_SEED_TYPES], 
char command_3, int identity, int num_trade, int n);

int trade_checking (struct seeds seed_collection[MAX_NUM_SEED_TYPES], 
char command_3, int identity, int num_trade, int n, int check_1, int check_2, 
int check_3);

int valid (struct land farm_land[LAND_SIZE][LAND_SIZE], char plant, 
int start_r, int start_c);

int disaster_checking (struct land farm_land[LAND_SIZE][LAND_SIZE], 
int min_num, int col, int row, char plant);

void drought (struct land farm_land[LAND_SIZE][LAND_SIZE], int min_num);

void wind_storm (struct land farm_land[LAND_SIZE][LAND_SIZE], int min_num_2);

// USING THIS IN STAGE 2
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct farmer cse_farmer);

// GAME SETUP FUNCTIONS
struct farmer initialise_farmer(struct farmer cse_farmer);
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]);
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]);
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row);
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE], 
                      struct farmer cse_farmer);

int main(void) {
    int n;
    int i = 0;
    struct farmer cse_farmer = {};
    cse_farmer = initialise_farmer(cse_farmer);

    struct land farm_land[LAND_SIZE][LAND_SIZE];
    initialise_land(farm_land);
    
    
    struct seeds seed_collection[MAX_NUM_SEED_TYPES];
    initialise_seeds(seed_collection);

    printf("Welcome to CSE Valley, farmer!\n");
    printf("Congratulations, you have received 60 seeds.\n");
    printf("How many different seeds do you wish to have? ");
    scanf("%d", &n);
    
    printf("Enter the names of the seeds to be given: \n");
    while (i < n) {
        scanf(" %c", &seed_collection[i].name);
        seed_collection[i].amount += 60/n;
        i++;
    }
    
    
    printf("Game Started!\n");

    char command;
    char command_2;
    char command_3;
    int min_num;
    int min_num_2;
    int num_trade;
    int size;
    int day = 2;
    int identity;
    int check_1, check_2, check_3;
    printf("Enter command: ");
    while (scanf(" %c", &command) != EOF) {
        if (command == 'a') {
            printing_all_seeds(seed_collection, n);
            
        } else if (command == 's') {
            scanf(" %c", &command_2);
            if (command_2 >= 'a' && command_2 <= 'z') {
                printing_one_seed(seed_collection, command_2, n);
            } else {
                printf("  Seed name has to be a lowercase letter\n");
            }
            
        } else if (command == 'l') {
            print_land(farm_land, cse_farmer);
            
        } else if (command == '>' || command == '<' || \
        command == 'v' || command == '^') {
            cse_farmer = moving_around(command, cse_farmer);
            
        } else if (command == 'o') {
            scanf(" %c", &command_2);
            if (command_2 == 'w') {
                watering_land(farm_land, cse_farmer);
            } else if (command_2 == 'p') {
                scanf(" %c", &command_3);
                planting_seed(farm_land, seed_collection, \
                cse_farmer, command_3, n);
            }
             
        } else if (command == 'p') {
            scanf(" %c", &command_2);
            if (command_2 >= 'a' && command_2 <= 'z') {
                planting_multiple(farm_land, seed_collection, cse_farmer, 
                command_2, n);
            } else {
                printf("  Seed name has to be a lowercase letter\n");
            }
            
        } else if (command == 'w') {
            scanf(" %d", &size);
            if (size >= 0) {
                square_watering(farm_land, cse_farmer, size);
            } else {
                printf("  The size argument needs to be a non-negative integer\n");
            }
            
        } else if (command == 'n') {
            next_day(farm_land, day);
            cse_farmer.curr_col = 0;
            cse_farmer.curr_row = 0;
            cse_farmer.curr_dir = '>';
            day++;
            
        } else if (command == 'h') {
            harvesting(farm_land, cse_farmer, seed_collection, n);
            
        } else if (command == 't') {
            scanf(" %c %d %c", &command_2, &num_trade, &command_3);
            identity = seed_name_checking(command_2, seed_collection, n);
            if (identity != -1 ) {
                check_1 = num_checking(num_trade, seed_collection, identity);
                check_2 = lowercase_checking(command_2);
                check_3 = lowercase_checking(command_3);
                
                n = trade_checking(seed_collection, command_3, identity, 
                num_trade, n, check_1, check_2, check_3);

            } else {
                printf("  You don't have the seeds to be traded\n");
            }
            
        } else if (command == 'd') {
            scanf(" %c", &command_2);
            if (command_2 == 'd') {
                scanf(" %d", &min_num);
                drought(farm_land, min_num);
            } else {
                scanf(" %d", &min_num_2);
                wind_storm(farm_land, min_num_2);
            }
        }
        printf("Enter command: ");
        
    }

    return 0;
}

void wind_storm (struct land farm_land[LAND_SIZE][LAND_SIZE], int min_num_2) {
    int checking = 0;
    int row_2, col_2;
    int col;
    int row;
    struct land storm[LAND_SIZE][LAND_SIZE];
    initialise_land(storm);
    char plant;
    row = 0;
    while (row < LAND_SIZE) {
        col = 0;
        while (col < LAND_SIZE) {
            if (farm_land[row][col].seed_name != NO_SEED) {
                plant = farm_land[row][col].seed_name;                    
                checking = disaster_checking(farm_land, 
                min_num_2, col, row, plant);
            }
            if (checking == 2) {
                storm[row][col] = farm_land[row][col];
                 
            }
            col++; 
        }
        row++;
    }
    row_2 = 0;
    while (row_2 < LAND_SIZE) {
        col_2 = 0;
        while (col_2 < LAND_SIZE) {
            if (storm[row_2][col_2].seed_name != NO_SEED) {
                farm_land[row_2][col_2].seed_name = NO_SEED;
            }
            col_2++;
        }
        row_2++;
    }
    return;
}



int valid (struct land farm_land[LAND_SIZE][LAND_SIZE], char plant, 
int start_r, int start_c) {
    int value = 0;
    if (start_r >= 0 && start_c >= 0 && 
    start_r < LAND_SIZE && start_c < LAND_SIZE) {
        value++;
        if (farm_land[start_r][start_c].seed_name == plant) {
            value++;
        }
    }
    return value;
}


int disaster_checking (struct land farm_land[LAND_SIZE][LAND_SIZE], 
int min_num, int col, int row, char plant) {
    int consideration = 0;
    int start_c, end_c;
    int start_r, end_r;
    int min_plant = 0;
    
    end_c = col + 1;
    end_r = row + 1;
    start_r = row - 1;
    while (start_r <= end_r) {
        start_c = col - 1;
        while (start_c <= end_c) {
            if (valid(farm_land, plant, start_r, start_c) == 2) {
                min_plant++;
            }
            start_c++;
        }
        start_r++;
    }
    if (min_plant - 1 >= min_num) {
        consideration = 1;
    } else {
        consideration = 2;
    }
    return consideration;
}


void drought (struct land farm_land[LAND_SIZE][LAND_SIZE], int min_num) {
    int checking = 0;
    int row_2, col_2;
    int col;
    int row;
    struct land plants_die[LAND_SIZE][LAND_SIZE];
    initialise_land(plants_die);
    char plant;
    row = 0;
    while (row < LAND_SIZE) {
        col = 0;
        while (col < LAND_SIZE) {
            if (farm_land[row][col].seed_name != NO_SEED) {
                plant = farm_land[row][col].seed_name;                    
                checking = disaster_checking(farm_land, 
                min_num, col, row, plant);
            }
            if (checking == 1) {
                plants_die[row][col] = farm_land[row][col];
                 
            }
            col++; 
        }
        row++;
    }
    row_2 = 0;
    while (row_2 < LAND_SIZE) {
        col_2 = 0;
        while (col_2 < LAND_SIZE) {
            if (plants_die[row_2][col_2].seed_name != NO_SEED) {
                farm_land[row_2][col_2].seed_name = NO_SEED;
            }
            col_2++;
        }
        row_2++;
    }
    return;
}



int trade_checking (struct seeds seed_collection[MAX_NUM_SEED_TYPES], 
char command_3, int identity, int num_trade, int n, int check_1, int check_2, 
int check_3) {
    int value = 0;
    if (check_1 > 0 && check_2 > 0 && check_3 > 0) {
        trading_seed(seed_collection, command_3, identity, \
        num_trade, n);
        if (seed_collection[n].name != NO_SEED) {
            n++;
        }
    }
    if (check_1 == 0) {
        printf("  You can't trade negative seeds\n");
    }
    if (check_1 < 0) {
        printf("  You don't have enough seeds to be traded\n");
    }
    if (check_2 == 0 || check_3 == 0) {
        printf("  Seed name has to be a lowercase letter\n");
    }
    value = n;
    return value;
}


struct farmer moving_around (char command, struct farmer cse_farmer) {
    struct farmer new_farmer;
    new_farmer.curr_col = cse_farmer.curr_col;
    new_farmer.curr_row = cse_farmer.curr_row;
    new_farmer.curr_dir = cse_farmer.curr_dir;
    
    if (command == '>') {
        if (new_farmer.curr_dir == '>') {
            new_farmer.curr_col += 1;
            if (new_farmer.curr_col >= LAND_SIZE) {
                new_farmer = boundaries(new_farmer);
            }
        } else {
            new_farmer.curr_dir = '>';
        }
        
    } else if (command == '<') {
        if (new_farmer.curr_dir == '<') {
            new_farmer.curr_col -= 1;
            if (new_farmer.curr_col < 0) {
                new_farmer = boundaries(new_farmer);
            }
        } else {
            new_farmer.curr_dir = '<';
        }
        
    } else if (command == 'v') {
        if (new_farmer.curr_dir == 'v') {
            new_farmer.curr_row += 1;
            if (new_farmer.curr_row >= LAND_SIZE) {
                new_farmer = boundaries(new_farmer);
            }
        } else {
            new_farmer.curr_dir = 'v';
        }
        
    } else if (command == '^') {
        if (new_farmer.curr_dir == '^') {
            new_farmer.curr_row -= 1;
            if (new_farmer.curr_row < 0) {
                new_farmer = boundaries(new_farmer);
            }
        } else {
            new_farmer.curr_dir = '^';
        }
    }
    return new_farmer; 
};


int num_checking (int num_trade, \
struct seeds seed_collection[MAX_NUM_SEED_TYPES], int identity) {
    int x = 0;
    if (num_trade >= 0 && num_trade <= seed_collection[identity].amount) {
        x = 1;
    }
    if (num_trade < 0) {
        x = 0;
    }
    if (num_trade > seed_collection[identity].amount) {
        x = -1;
    }
    return x;
}

int lowercase_checking (char a) {
    if (a >= 'a' && a <= 'z') {
        return 1;
    } else {
        return 0;
    }
}


void trading_seed(struct seeds seed_collection[MAX_NUM_SEED_TYPES], \
char command_3, int identity, int num_trade, int n) {
    int x;
    int i = 0;
    int j = 0;
    struct seeds new_collection[MAX_NUM_SEED_TYPES];
    new_collection[i].name = command_3;
    new_collection[i].amount = num_trade;
    seed_collection[identity].amount -= num_trade;
    x = seed_name_checking(command_3, seed_collection, n);
    if (x == -1) {
        n++;
        while (i < n - 1) {
            new_collection[i + 1].name = seed_collection[i].name;
            new_collection[i + 1].amount = seed_collection[i].amount; 
            i++;
        } 
        while (j < n) {
            seed_collection[j].name = new_collection[j].name;
            seed_collection[j].amount = new_collection[j].amount;
            j++;
        }
    } else {
        seed_collection[x].amount += num_trade;
    }
    
    return;
}


int seed_name_checking (char a, \
struct seeds seed_collection [MAX_NUM_SEED_TYPES], int n) {
    int correct = -1;
    int i = 0;
    while (i < n) {
        if (tolower(a) == seed_collection[i].name) {
            correct = i;
        }
        i++;
    }
    return correct;
}


void harvesting (struct land farm_land[LAND_SIZE][LAND_SIZE], \
struct farmer cse_farmer, struct seeds seed_collection [MAX_NUM_SEED_TYPES], \
int n) {
    char dir = cse_farmer.curr_dir;
    int x = cse_farmer.curr_row;
    int y = cse_farmer.curr_col;
    int num_check;
    if (dir == '>') {
        if (x < LAND_SIZE && y + 1 < LAND_SIZE) {
            if (farm_land[x][y + 1].seed_name >= 'A' && \
            farm_land[x][y + 1].seed_name <= 'Z') {
                
                num_check = seed_name_checking(farm_land[x][y + 1].seed_name, \
                seed_collection, n);
                
                seed_collection[num_check].amount += 5;
                
                printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s) \n", 
                farm_land[x][y + 1].seed_name, 
                tolower(farm_land[x][y + 1].seed_name));
                
                farm_land[x][y + 1].seed_name = NO_SEED;
            }
        }
        
    }
    if (dir == '<') {
        if (x < LAND_SIZE && y - 1 < LAND_SIZE) {
            if (farm_land[x][y - 1].seed_name >= 'A' && \
            farm_land[x][y - 1].seed_name <= 'Z') {
                
                num_check = seed_name_checking(farm_land[x][y - 1].seed_name, \
                seed_collection, n);
                
                seed_collection[num_check].amount += 5;
                
                printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s) \n", 
                farm_land[x][y - 1].seed_name, 
                tolower(farm_land[x][y - 1].seed_name));
                
                farm_land[x][y - 1].seed_name = NO_SEED;
            }
        }
    }
    if (dir == '^') {
        if (x - 1 < LAND_SIZE && y < LAND_SIZE) {
            if (farm_land[x - 1][y].seed_name >= 'A' && \
            farm_land[x - 1][y].seed_name <= 'Z') {
                
                num_check = seed_name_checking(farm_land[x-1][y].seed_name, \
                seed_collection, n);
                
                seed_collection[num_check].amount += 5;
                
                printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s) \n", 
                farm_land[x - 1][y].seed_name, 
                tolower(farm_land[x - 1][y].seed_name));
                
                farm_land[x - 1][y].seed_name = NO_SEED;
            } 
        }
    }
    if (dir == 'v') {
        if (x + 1 < LAND_SIZE && y < LAND_SIZE) {
            if (farm_land[x + 1][y].seed_name >= 'A' && \
            farm_land[x + 1][y].seed_name <= 'Z') {
                
                num_check = seed_name_checking(farm_land[x + 1][y].seed_name, \
                seed_collection, n);
                
                seed_collection[num_check].amount += 5;
                
                printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s) \n", 
                farm_land[x + 1][y].seed_name, 
                tolower(farm_land[x + 1][y].seed_name));
                
                farm_land[x + 1][y].seed_name = NO_SEED;
            }
        }
    }
    return;
}

struct land tomorrow (struct land farm_land[LAND_SIZE][LAND_SIZE], 
int i, int j, char s_name) {
    s_name = farm_land[i][j].seed_name;
    if (s_name >= 'a' && s_name <= 'z') {
        if (farm_land[i][j].is_watered == TRUE) {
            farm_land[i][j].seed_name = toupper(s_name);
            farm_land[i][j].is_watered = FALSE;  
        } else {
            farm_land[i][j].seed_name = NO_SEED;
        }     
    } else {
        farm_land[i][j].seed_name = NO_SEED;
        farm_land[i][j].is_watered = FALSE;
    }
    return farm_land[i][j];

}; 


void next_day (struct land farm_land[LAND_SIZE][LAND_SIZE], int day) {
    int i, j;
    char s_name;
    printf("  Advancing to the next day... Day %d, let's go!\n", day);
    i = 0;
    while (i < LAND_SIZE) {
        j = 0;
        while (j < LAND_SIZE) {
            s_name = farm_land[i][j].seed_name;
            farm_land[i][j] = tomorrow(farm_land, i, j, s_name);
            j++;
        }
        i++;
    }

    return;
}


void square_watering (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct farmer cse_farmer, int size) {
    int x = cse_farmer.curr_row;
    int y = cse_farmer.curr_col;
    int start_row;
    int start_col = 0;
    int end_r = x + size;
    int end_c = y + size;
    start_row = x - size;
    while (start_row <= end_r) {
        start_col = y - size;
        while (start_col <= end_c) {
        
            if (start_row >= 0 && start_col >= 0 && 
            start_row < LAND_SIZE && start_col < LAND_SIZE) {
            
                farm_land[start_row][start_col].is_watered = TRUE;
            }
            start_col++;
        }
        start_row++;
    }
    return;
}


int changed_amount (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], char command_2, int correct, 
int x, int y) {
    int amount = 0;
    if (farm_land[x][y].seed_name == command_2) {
        seed_collection[correct].amount++;
    }
    amount = seed_collection[correct].amount;
    return amount;
}

void in_bound (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], char command_2, char dir, 
int i, int correct, int x, int y) {

    while (i < LAND_SIZE && seed_collection[correct].amount > 0) {
        if (dir == '>') {
            if (x < LAND_SIZE && y < LAND_SIZE) {
                seed_collection[correct].amount = changed_amount (farm_land, 
                seed_collection, command_2, correct, x, y);
            }
            if (y == LAND_SIZE) {
                y = LAND_SIZE - 1;
                farm_land[x][y].seed_name = command_2;    
            } else if (y < LAND_SIZE) {
                farm_land[x][y].seed_name = command_2;
                seed_collection[correct].amount -= 1;
                y++;
            } 
        } else {
            if (x < LAND_SIZE && y < LAND_SIZE) {
                seed_collection[correct].amount = changed_amount (farm_land, 
                seed_collection, command_2, correct, x, y);
            }
            if (x == LAND_SIZE) {
                x = LAND_SIZE - 1;
                farm_land[x][y].seed_name = command_2;     
            } else if (x < LAND_SIZE) {
                farm_land[x][y].seed_name = command_2;
                seed_collection[correct].amount -= 1;
                x++;
            }
        }
        i++;
    }
    return;
}

void planting_multiple (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], struct farmer cse_farmer, 
char command_2, int n) {
    int j = 0;
    int i = 0;
    int correct = -1;
    int y = cse_farmer.curr_col;
    int x = cse_farmer.curr_row;
    char dir = cse_farmer.curr_dir;
    while (j < n) {
        if (command_2 == seed_collection[j].name) {
            correct = j;
        }
        j++;
    }
    if (correct != -1) {
        if (dir == '<' || dir == '^') {
            printf("  You cannot scatter seeds ^ or <\n");
        } else {
            in_bound(farm_land, seed_collection, command_2, dir, 
            i, correct, x, y);
        }
    } else {
        printf("  There is no seed with the name '%c'\n", command_2);
    }

    return;
}


void planting_seed (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct seeds seed_collection [MAX_NUM_SEED_TYPES], struct farmer cse_farmer, 
char command_3, int n) {
    int x = cse_farmer.curr_row;
    int y = cse_farmer.curr_col;
    char dir = cse_farmer.curr_dir;
    int check = 0;
    int check_1 = 0;
    
    while (check_1 < n) {
        if (command_3 == seed_collection[check_1].name) {
            check = check_1;
        }
        check_1++;
    }
    if (dir == '>') {
        y += 1;
        if (y < LAND_SIZE) {
            farm_land[x][y].seed_name = command_3;
            seed_collection[check].amount -= 1;
        }
    } else if (dir == '<') {
        y -= 1;
        if (y >= 0) {
            farm_land[x][y].seed_name = command_3;
            seed_collection[check].amount -= 1;
        }
    } else if (dir == 'v') {
        x += 1;
        if (x < LAND_SIZE) {
            farm_land[x][y].seed_name = command_3;
            seed_collection[check].amount -= 1;
        }
    } else if (dir == '^') {
        x -= 1;
        if (x >= 0) {
            farm_land[x][y].seed_name = command_3;
            seed_collection[check].amount -= 1;
        }
    }
    
    return;
}


void watering_land (struct land farm_land[LAND_SIZE][LAND_SIZE], 
struct farmer cse_farmer) {
    int x = cse_farmer.curr_row;
    int y = cse_farmer.curr_col;
    if (cse_farmer.curr_dir == '>') {
        y += 1;
        if (y < LAND_SIZE) {
            farm_land[x][y].is_watered = TRUE;
        }
    } else if (cse_farmer.curr_dir == '<') {
        y -= 1;
        if (y >= 0) {
            farm_land[x][y].is_watered = TRUE;
        }
    } else if (cse_farmer.curr_dir == 'v') {
        x += 1;
        if (x < LAND_SIZE) {
            farm_land[x][y].is_watered = TRUE;
        }
    } else if (cse_farmer.curr_dir == '^') {
        x -= 1;
        if (x >= 0) {
            farm_land[x][y].is_watered = TRUE;
        }
    }
    return;
}


struct farmer boundaries(struct farmer cse_farmer) {
    struct farmer staying;
    staying.curr_col = cse_farmer.curr_col;
    staying.curr_dir = cse_farmer.curr_dir;
    staying.curr_row = cse_farmer.curr_row;
    
    if (staying.curr_col < 0 || staying.curr_col >= LAND_SIZE) {
        if (staying.curr_col < 0) {
            staying.curr_col = 0;
        } else {
            staying.curr_col = LAND_SIZE - 1;
        }
    } 
    if (staying.curr_row < 0 || staying.curr_row >= LAND_SIZE) {
        if (staying.curr_row < 0) {
            staying.curr_row = 0;
        } else {
            staying.curr_row = LAND_SIZE - 1;
        }
    }
    return staying;
};

void printing_one_seed(struct seeds seed_collection[MAX_NUM_SEED_TYPES], \
char command_2, int n) {
    int j = 0;
    int correct = -1;
    while (j < n) {
        if (command_2 == seed_collection[j].name) {
            correct = j;
        }
        j++;
    }
    if (correct != -1) {
        printf("  There are %d seeds with the name '%c'\n", \
        seed_collection[correct].amount, command_2);
    } else {
        printf("  There is no seed with the name '%c'\n", command_2);
    }
    return;
}



void printing_all_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES], \
int n) {
    int j = 0;
    printf("  Seeds at your disposal:\n");
    while (j < n) {
        printf("  - %d seed(s) with the name '%c'\n", \
        seed_collection[j].amount, seed_collection[j].name);
        j++;
    }
    return;
}
////////////////////////////////
//     Provided Functions     //
////////////////////////////////

// Prints the structs land (including locating where the
// farmer is)
// This is used for stage 2
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE],
                struct farmer cse_farmer) {
    printf("|---|---|---|---|---|---|---|---|\n");
    int i = 0;
    while (i < LAND_SIZE) {
        print_top_row(farm_land, i);
        // only prints mid and bottom row when the farmer
        // is in that row
        if (i == cse_farmer.curr_row) {
            print_farmer_row(farm_land, cse_farmer);
        }
        printf("|---|---|---|---|---|---|---|---|\n");
        i++;
    }
}

// NOTE: You do not need to directly call any of the functions
// below this point. You are allowed to modify them, but you
// do not need to.

// Initialises struct farmer to its default state upon starting
// in which the farmer will be on the top left of the farm
// facing to the right (as noted by '>')
struct farmer initialise_farmer(struct farmer cse_farmer) {
    cse_farmer.curr_col = 0;
    cse_farmer.curr_row = 0;
    cse_farmer.curr_dir = '>';
    return cse_farmer;
}

// Initialises a 2d array of struct land to its default state 
// upon starting, which is that all land is unwatered and
// contains no seed
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]) {
    int i = 0;
    while (i < LAND_SIZE) {
        int j = 0;
        while (j < LAND_SIZE) {
            farm_land[i][j].is_watered = FALSE;
            farm_land[i][j].seed_name = NO_SEED;
            j++;
        }
        i++;
    }
}

// Initialises struct farmer to its default state upon starting,
// which that all names are initialised as NO_SEED and its
// amount is 0
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]) {
    int i = 0;
    while (i < MAX_NUM_SEED_TYPES) {
        seed_collection[i].amount = 0;
        seed_collection[i].name = NO_SEED;
        i++;
    }
}

////////////////////////////////
//      Helper Functions      //
////////////////////////////////

// prints the top row of a particular struct land
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row) {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        printf("%c", farm_land[row][j].seed_name);
        printf(" ");
        if (farm_land[row][j].is_watered == TRUE) {
            printf("W");
        } else {
            printf(" ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}

// prints the 2 additional row when a farmer is in
// a particular row
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE], 
                      struct farmer cse_farmer)  {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            if (cse_farmer.curr_dir == '<') {
                printf("<");
            } else {
                printf(" ");
            }
            if (cse_farmer.curr_dir == '^') {
                printf("^");
            } else {
                printf("f");
            }
            if (cse_farmer.curr_dir == '>') {
                printf(">");
            } else {
                printf(" ");
            }
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
    j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            printf(" ");
            if (cse_farmer.curr_dir == 'v') {
                printf("v");
            } else if (cse_farmer.curr_dir == '^') {
                printf("f");
            } else {
                printf(" ");
            }
            printf(" ");
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}
