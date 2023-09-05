#include <bits/stdc++.h>

// X is -1 O is 1
std::vector<int> tictactoe(9, 0);
int computer;

// returns the -1 if X wins, returns 0 if tie, returns 1 if O wins
int check(std::vector<int> board)
{
    if (board[0] && board[0] == board[3] && board[0] == board[6])
        return board[0];
    if (board[1] && board[1] == board[4] && board[1] == board[7])
        return board[1];
    if (board[2] && board[2] == board[5] && board[2] == board[8])
        return board[2];
    if (board[0] && board[0] == board[1] && board[0] == board[2])
        return board[0];
    if (board[3] && board[3] == board[4] && board[3] == board[5])
        return board[3];
    if (board[6] && board[6] == board[7] && board[6] == board[8])
        return board[6];
    if (board[0] && board[0] == board[4] && board[0] == board[8])
        return board[0];
    if (board[2] && board[2] == board[4] && board[2] == board[6])
        return board[2];
    return 0;
}

void printBoard(std::vector<int> board)
{
    std::cout << board[0] << " " << board[1] << " " << board[2] << "\n"
              << board[3] << " " << board[4] << " " << board[5] << "\n"
              << board[6] << " " << board[7] << " " << board[8] << "\n";
}

// returns the evalutation of the current position
// maximizing is true when you want to maximize the current board, and false when you want to minimize the result
// returns 1 if the maximizing player is winning, returns 0 if tie, returns -1 the maximizing player is losing
int evaluation(std::vector<int> board, int movesLeft, int alpha, int beta, bool maximizing)
{
    if (movesLeft == 0)
    {
        // returns 1 if X wins returns -1 if O wins
        // printBoard(board);
        // std::cout << "eval:" << check(board) << "\n";
        int eval = check(board);
        if (eval)
        {
            if (computer == eval)
                return 1;
            else
                return -1;
        }
        else
            return 0;
    }

    if (maximizing)
    {
        int currEval = check(board);
        // if not a tie (ie game has ended), return the winner
        if (currEval)
            if (computer == currEval)
                return 1;
            else
                return -1;
        int maxEval = -2;
        for (int i = 0; i < board.size(); i++)
        {
            // i is occupied
            if (board[i])
                continue;
            board[i] = computer;
            int eval = evaluation(board, movesLeft - 1, alpha, beta, !maximizing);
            // resets the board for the next iteration
            board[i] = 0;
            maxEval = std::max(eval, maxEval);
            alpha = std::max(alpha, maxEval);
            // branch is the less optimal choice, so prune it
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int currEval = check(board);
        // if not a tie (ie game has ended), return the winner
        if (currEval)
        {
            if (computer == currEval)
                return 1;
            else
                return -1;
        }
        int minEval = 2;
        for (int i = 0; i < board.size(); i++)
        {
            // i is occupied
            if (board[i])
                continue;
            board[i] = computer * -1;
            int eval = evaluation(board, movesLeft - 1, alpha, beta, !maximizing);
            // resets the board for the next iteration
            board[i] = 0;
            minEval = std::min(eval, minEval);
            beta = std::min(beta, minEval);
            // branch is the less optimal choice, so prune it
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

int nextMove(std::vector<int> board, int movesLeft)
{
    // records the last position for a tie, in case a winning position isn't found, play this move
    int tie = -1;
    // records the last position for a loss
    int lose = -1;
    for (int i = 0; i < board.size(); i++)
    {
        // i is occupied
        if (board[i])
            continue;
        board[i] = computer;
        int eval = evaluation(board, movesLeft - 1, -2, 2, false);
        if (eval == 1)
        {
            std::cout << "computer is winning\n";
            return i;
        }
        else if (eval == 0)
        {
            tie = i;
        }
        else if (eval == -1)
        {
            lose = i;
        }
        board[i] = 0;
    }
    if (tie != -1)
        std::cout << "tie\n";
    else
        std::cout << "player is winning\n";
    return tie == -1 ? lose : tie;
}

int main()
{
    // computer = 1;
    // std::vector<int> test = {0, 0, -1, -1, 1, 1, -1, 0, 0};
    // std::cout << check(test);
    // std::cout << evaluation(test, 4, -2, 2, true);
    // return 0;
    std::cout << "Computer plays as: (-1 for X, 1 for O)\n";
    std::cin >> computer;
    if (computer == -1)
    {
        for (int moveNum = 0; moveNum < 8; moveNum++)
        {
            int eval = check(tictactoe);
            if (eval == -1)
            {
                printBoard(tictactoe);
                std::cout << "computer wins!";
                return 0;
            }
            else if (eval == 1)
            {
                printBoard(tictactoe);
                std::cout << "player wins!";
                return 0;
            }
            if (moveNum % 2 == 0)
            {
                int move = nextMove(tictactoe, tictactoe.size() - moveNum);
                std::cout << move << "\n";
                tictactoe[move] = computer;
                printBoard(tictactoe);
                continue;
            }

            else
            {
                int move;
                std::cin >> move;
                tictactoe[move] = computer * -1;
                printBoard(tictactoe);
                continue;
            }
        }
        int eval = check(tictactoe);
        if (eval == -1)
        {
            printBoard(tictactoe);
            std::cout << "computer wins!";
            return 0;
        }
        else if (eval == 1)
        {
            printBoard(tictactoe);
            std::cout << "player wins!";
            return 0;
        }

        else
        {
            printBoard(tictactoe);
            std::cout << "tie!";
            return 0;
        }
    }

    else
    {
        for (int moveNum = 0; moveNum < 8; moveNum++)
        {
            int eval = check(tictactoe);
            if (eval == -1)
            {
                printBoard(tictactoe);
                std::cout << "player wins!";
                return 0;
            }
            else if (eval == 1)
            {

                printBoard(tictactoe);
                std::cout << "computer wins!";
                return 0;
            }
            if (moveNum % 2 == 0)
            {
                int move;
                std::cin >> move;
                tictactoe[move] = computer * -1;
                printBoard(tictactoe);
                continue;
            }

            else
            {
                int move = nextMove(tictactoe, tictactoe.size() - moveNum);
                std::cout << move << "\n";
                tictactoe[move] = computer;
                printBoard(tictactoe);
                continue;
            }
        }

        int eval = check(tictactoe);
        if (eval == -1)
        {
            printBoard(tictactoe);
            std::cout << "player wins!";
            return 0;
        }
        else if (eval == 1)
        {
            printBoard(tictactoe);
            std::cout << "computer wins!";
            return 0;
        }

        else
        {
            printBoard(tictactoe);
            std::cout << "tie!";
            return 0;
        }
    }

    return 0;
}
