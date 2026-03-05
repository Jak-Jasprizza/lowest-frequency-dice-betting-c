// Lowest-Frequency Dice Betting Game (C)
// By Jak Jasprizza


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define SIDES 6

// Set to 5 for "fair odds" (+5 on hit, -1 on miss) => expected value 0
#define WIN_PAYOUT 5
#define LOSE_PAYOUT 1

static void print_table(const long counts[SIDES], long rolls_done) {
    printf("\nRolls completed: %ld\n", rolls_done);
    printf("---------------------------------\n");
    printf("%6s %10s\n", "Face", "Count");
    printf("---------------------------------\n");
    for (int i = 0; i < SIDES; i++) {
        printf("%6d %10ld\n", i + 1, counts[i]);
    }
    printf("---------------------------------\n");
}

static long min_count(const long counts[SIDES]) {
    long m = counts[0];
    for (int i = 1; i < SIDES; i++) {
        if (counts[i] < m) m = counts[i];
    }
    return m;
}

static int collect_lowest_faces(const long counts[SIDES], int lowest_faces[SIDES]) {
    long m = min_count(counts);
    int k = 0;
    for (int i = 0; i < SIDES; i++) {
        if (counts[i] == m) {
            lowest_faces[k++] = i + 1; // faces are 1..6
        }
    }
    return k;
}

static int face_is_in_list(int face, const int list[SIDES], int k) {
    for (int i = 0; i < k; i++) {
        if (list[i] == face) return 1;
    }
    return 0;
}

static int read_int_choice(void) {
    int x;
    if (scanf("%d", &x) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            // discard
        }
        return -999999; // sentinel for invalid input
    }
    return x;
}

static char read_yn(void) {
    char c;
    if (scanf(" %c", &c) != 1) return '?';

    // If the user typed a word like "yes", discard the rest of that line
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // discard
    }

    return (char)toupper((unsigned char)c);
}

static int roll_die(void) {
    return (rand() % SIDES) + 1;
}

int main(void) {
    long total_rolls;

    printf("--- Lowest-Frequency Dice Betting Game ---\n\n");
    printf("Enter total number of rolls: ");
    if (scanf("%ld", &total_rolls) != 1 || total_rolls < 1) {
        printf("Total rolls must be >= 1.\n");
        return 1;
    }

    srand(time(NULL));

    long counts[SIDES] = {0, 0, 0, 0, 0, 0};
    long profit = 0;

    int bet = 0; // 0 = HOLD, otherwise 1..6
    long rolls_done = 0;

    printf("\nRules:\n");
    printf("- If betting on a face: +$%d if the roll matches your bet, -$%d otherwise.\n",
           WIN_PAYOUT, LOSE_PAYOUT);
    printf("- If HOLDING: no profit/loss until you place a bet.\n");

    while (rolls_done < total_rolls) {
        // Roll once
        int outcome = roll_die();
        counts[outcome - 1]++;
        rolls_done++;

        // Update profit if a bet is active
        if (bet != 0) {
            if (outcome == bet) profit += WIN_PAYOUT;
            else profit -= LOSE_PAYOUT;
        }

        // Recompute lowest faces after every roll
        int lowest_faces[SIDES];
        int k = collect_lowest_faces(counts, lowest_faces);


        int should_prompt = 0;

        if (bet == 0) {
            if (k == 1) should_prompt = 1;
        } else {
            if (!face_is_in_list(bet, lowest_faces, k)) should_prompt = 1;
        }

        if (!should_prompt) {
            continue;
        }

        // Print current state
        print_table(counts, rolls_done);
        printf("Current profit/loss: $%ld\n", profit);

        if (k == 1) {
            int lowest = lowest_faces[0];
            printf("Lowest rolled number is: %d\n", lowest);

            printf("Would you like to bet %d? (Y/N): ", lowest);
            char yn = read_yn();

            if (yn == 'Y') {
                bet = lowest;
                printf("Bet set to %d.\n", bet);

            } else if (yn == 'N') {
                printf("Pick a number to bet (1-6), 0 to HOLD");
                if (bet != 0) printf(", or -1 to KEEP your current bet (%d)", bet);
                printf(": ");

                int choice = read_int_choice();

                if (choice == -1 && bet != 0) {
                    printf("Keeping current bet: %d\n", bet);

                } else if (choice == 0) {
                    bet = 0;
                    printf("You are HOLDING (no bet).\n");

                } else if (choice >= 1 && choice <= 6) {
                    bet = choice;
                    printf("Bet set to %d.\n", bet);

                } else {
                    printf("Invalid choice. Keeping current bet (%s).\n",
                           bet == 0 ? "HOLD" : "unchanged");
                }

            } else {
                printf("Invalid input. Keeping current bet (%s).\n",
                       bet == 0 ? "HOLD" : "unchanged");
            }

                } else {
            printf("There are multiple lowest numbers tied: ");
            for (int i = 0; i < k; i++) {
                printf("%d", lowest_faces[i]);
                if (i != k - 1) printf(", ");
            }
            printf("\n");

            printf("Choose a bet from the lowest set above, or enter any 1-6, or 0 to HOLD: ");

            int choice = read_int_choice();

            if (choice == 0) {
                bet = 0;
                printf("You are HOLDING (no bet).\n");

            } else if (choice >= 1 && choice <= 6) {
                bet = choice;
                printf("Bet set to %d.\n", bet);

            } else {
                printf("Invalid choice. Keeping current bet (%s).\n",
                       bet == 0 ? "HOLD" : "unchanged");
            }
        }
    }

    // Final summary
    print_table(counts, rolls_done);
    printf("Final profit/loss: $%ld\n", profit);
    if (bet == 0) printf("Final bet: HOLD\n");
    else printf("Final bet: %d\n", bet);

    return 0;
}
