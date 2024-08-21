#pragma once
#include <vector>
#include <stdexcept>

class Board
{
    int n_rows, n_columns;  // number of rows and columns
    std::vector<std::vector<int>> _pokemons;  // pokemons

public:
    // Constructor
    Board(int n_rows, int n_columns, int n_types, std::vector<int> count)
        : n_rows(n_rows), n_columns(n_columns)
    {
        if (count.size() != n_types) {
            throw std::invalid_argument("Size of count vector must match n_types.");
        }

        // Initialize the board with -1 (indicating no pokemon)
        _pokemons = std::vector<std::vector<int>>(n_rows, std::vector<int>(n_columns, -1));

        int total_slots = n_rows * n_columns;
        int total_pokemons = 0;
        for (int c : count) {
            total_pokemons += c;
        }

        if (total_pokemons > total_slots) {
            throw std::invalid_argument("Too many pokemons for the given board size.");
        }

        // Fill the board with pokemons according to count
        int type_index = 0;
        for (int i = 0; i < n_rows; ++i) {
            for (int j = 0; j < n_columns; ++j) {
                if (count[type_index] == 0) {
                    ++type_index;
                }
                if (type_index >= n_types) {
                    break;
                }
                _pokemons[i][j] = type_index;
                --count[type_index];
            }
        }
    }

    int getNRows() {
        return n_rows;
    }

    int getNColumns() {
        return n_columns;
    }

    void addPokemon(int x, int y, int type) {
        if (x < 0 || x >= n_rows || y < 0 || y >= n_columns) {
            throw std::out_of_range("Position out of bounds.");
        }
        _pokemons[x][y] = type;
    }

    int getPokemon(int x, int y) {
        if (x < 0 || x >= n_rows || y < 0 || y >= n_columns) {
            throw std::out_of_range("Position out of bounds.");
        }
        return _pokemons[x][y];
    }

    void removePokemon(int x, int y) {
        if (x < 0 || x >= n_rows || y < 0 || y >= n_columns) {
            throw std::out_of_range("Position out of bounds.");
        }
        _pokemons[x][y] = -1;
    }
};

