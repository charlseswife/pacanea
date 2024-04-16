#include <iostream>
#include <cstdlib>
#include <ctime>

class SlotMachine {
public:
    SlotMachine() : balance(1000.0) {}

    void play() {
        std::cout << "Starting balance: " << balance << std::endl;
        while (balance > 0) {
            double bet;
            std::cout << "Current balance: " << static_cast<int>(balance) << ". Enter your bet (0 to quit): ";
            std::cin >> bet;

            if (bet == 0) {
                std::cout << "Exiting the game. Final balance: " << static_cast<int>(balance) << std::endl;
                return;
            }

            if (bet > balance) {
                std::cout << "Insufficient balance. Please enter a smaller bet." << std::endl;
                continue;
            }

            spin(bet);
        }
        std::cout << "You're out of money! Game over." << std::endl;
    }

private:
    double balance;

    char randomSymbol() {
        char symbols[] = { '#', '@', '$', '&', '7' };
        int index = std::rand() % 5;
        return symbols[index];
    }

    void printColoredSymbol(char symbol) {
        switch (symbol) {
        case '#':
            std::cout << "\033[1;31m" << symbol << "\033[0m"; // Rosu
            break;
        case '@':
            std::cout << "\033[1;32m" << symbol << "\033[0m"; // Verde
            break;
        case '$':
            std::cout << "\033[1;33m" << symbol << "\033[0m"; // Galben
            break;
        case '&':
            std::cout << "\033[1;34m" << symbol << "\033[0m"; // Albastru
            break;
        case '7':
            std::cout << "\033[1;35m" << symbol << "\033[0m"; // Mov
            break;
        default:
            std::cout << symbol;
        }
    }

    void spin(double bet) {
        char reel1 = randomSymbol();
        char reel2 = randomSymbol();
        char reel3 = randomSymbol();

        std::cout << "Reels: ";
        printColoredSymbol(reel1);
        std::cout << " | ";
        printColoredSymbol(reel2);
        std::cout << " | ";
        printColoredSymbol(reel3);
        std::cout << std::endl;

        double winnings = 0;

        if (reel1 == reel2 && reel2 == reel3 && reel1 == '7') {
            winnings = 10 * bet;
            std::cout << "Jackpot! You won " << winnings << " credits!" << std::endl;
        }
        else if (reel1 == reel2 && reel2 == reel3) {
            winnings = 2 * bet;
            std::cout << "Triple symbols matched! You won " << winnings << " credits!" << std::endl;
        }
        else if (reel1 == reel2 || reel2 == reel3 || reel1 == reel3) {
            winnings = 1.5 * bet;
            std::cout << "Two symbols matched! You won " << winnings << " credits!" << std::endl;
        }
        else {
            std::cout << "No luck this time. You lost " << bet << " credits." << std::endl;
            balance -= bet; // scade pariul din balance dupa pierdere
            return;
        }

        doubleWinnings(bet, winnings);
    }

    void doubleWinnings(double bet, double& winnings) {
        char choice;
        int multiplier = 2;
        while (true) {
            std::cout << "Do you want to double your winnings? (r for red, b for black, s to skip): ";
            std::cin >> choice;

            if (choice == 'r' || choice == 'b') {
                char color = randomCardColor();
                if (choice == color) {
                    double potentialWinnings = winnings * multiplier; // Calcularea potentialului castig
                    std::cout << "If you pick the right card, your potential winnings will be " << potentialWinnings << " credits." << std::endl;
                    if (multiplier == 2) {
                        std::cout << "This will double your current winnings." << std::endl;
                    }
                    else {
                        std::cout << "This will multiply your current winnings by " << multiplier << "." << std::endl;
                    }
                    if (multiplier < 5) {
                        ++multiplier; // Creste multiplicatorul pt urmatoarea runda
                    }
                    winnings = potentialWinnings; // Update la winnings cu potentialul
                }
                else {
                    std::cout << "You picked the wrong card! Your winnings are lost." << std::endl;
                    balance -= bet; // Scade pariul initial din balance
                    return;
                }
            }
            else if (choice == 's') {
                std::cout << "You chose to skip. Your winnings have been added to the balance!" << std::endl;
                balance += winnings; // Adauga winningurile la balance dupa ce dai skip
                return;
            }
            else {
                std::cout << "Invalid choice. Please choose 'r', 'b', or 's'." << std::endl;
            }
        }
    }

    char randomCardColor() {
        return (std::rand() % 2 == 0) ? 'r' : 'b';
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed pt rng
    SlotMachine slotMachine;
    slotMachine.play();
    return 0;
}
