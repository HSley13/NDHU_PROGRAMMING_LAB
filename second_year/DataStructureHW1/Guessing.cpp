#include <cstdlib>
#include <ctime>
#include <iostream>

class NumberGuessing {
  public:
    void Set(int v) {
        value = v;
    }

    int Get() const {
        return value;
    }

    int Guesser(int v) {
        if (v < value) {
            attempts++;
            return -1;
        } else if (v > value) {
            attempts++;
            return 1;
        } else {
            return 0;
        }
    }

    int Attempts() const {
        return attempts;
    }

    void Reset() {
        attempts = 0;
    }

  private:
    int value;
    int attempts{0};
};

int main(void) {
    NumberGuessing new_game;
    new_game.Set(80);

    int guess;
    std::cout << "Guess a number between 1 and 100: ";

    int result;
    do {
        std::cin >> guess;

        result = new_game.Guesser(guess);

        if (result == -1) {
            std::cout << "Too low! Try again: ";
        } else if (result == 1) {
            std::cout << "Too high! Try again: ";
        } else {
            std::cout << "Congratulations! You've guessed the correct number in " << new_game.Attempts() << " attempts.\n";
            new_game.Reset();
            break;
        }
    } while (result != 0);
}
