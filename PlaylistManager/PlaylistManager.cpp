#include <iostream>
#include <cstdlib>
#include <string>
#include "Song.h"

Song* head = nullptr; // The `head` of the playlist - The latest song you added
Song* first = nullptr; // The first song you add.

void dispose() {
    Song* current = head;

    do {
        Song* temp = current;
        current = current->prev;
        delete temp;
    } while (current != first);
}

int main()
{
    Song* current = nullptr;
    atexit(dispose);
    // Loop for configuring songs
    while (true) {
        std::cout << "Do you want to add a song (a), Remove a song (b), cycle playlist forwards (f), or cycle backwards? (r)\n";
        char input;
        std::cin >> input;
        std::cout << std::endl;
        // Makes sure you input the right char
        if (input != 'a' && input != 'b' && input != 'f' && input != 'r') {
                std::cout << "Invalid input\n";
                continue;
        }

        // Does all the pointy stuff to set the previous and next songs for each song respectively
        if (input == 'a') {
            Song* newSong = new Song; // Current song being created
            std::string name;
            std::cout << "Enter song name: ";
            std::cin >> name;
            std::cout << std::endl;
            newSong->name = name;
            // If this is the first song, then initialize it
            if (head == nullptr) {
                first = newSong;
                newSong->prev = first;
                current = first;
            } 
            else
                newSong->prev = head;

            // The First song should loop back to the new song
            first->prev = newSong;
            newSong->prev->next = newSong;
            // Every new song should loop forward to the first song.
            newSong->next = first;
            
            head = newSong;
        }
        // Redoes all the pointy stuff you made me setup all for nothing :(
        else if (input == 'b' && head != nullptr) {
            std::string name;
            std::cout << "Enter song name to Delete: ";
            std::cin >> name;
            std::cout << std::endl;
            Song* songDel = head;
            bool del = false;
            do {
                if (songDel->name == name) {
                    // Reconnects the loop at the song being broken
                    songDel->prev->next = songDel->next;
                    songDel->next->prev = songDel->prev;
                    // If you delete the only song, reset the head to nullptr and the current song
                    if (songDel == songDel->next) {
                        head = nullptr;
                        current = nullptr;
                    }
                    // If you delete the selected song then go forward
                    if (current == songDel && current != nullptr) {
                        current = current->next;
                    }
                    // If you delete the first song then the first song goes forward
                    if (first == songDel && first != nullptr) {
                        first = first->next;
                    }
                    // If you delete the head the first song goes backward
                    if (head == songDel && head != nullptr) {
                        head = head->prev;
                    }
                    delete songDel;
                    del = true;
                    break;
                }
                else
                    songDel = songDel->prev;
            } while (songDel->name != first->prev->name);

            if (!del)
                std::cout << "No available song with that name.\n";
            else
                std::cout << "Successfully removed: " << name << "!\n\n";
        }
        // Edge case
        else if (input == 'b' && head == nullptr) {
            std::cout << "You cannot remove songs you don't already have!\n";
        }
        // For Cycling
        else if (input == 'f' || input == 'r') {
            
            if (input == 'f' && current != nullptr) {
                current = current->next;
            }
            else if (input == 'r' && current != nullptr) {
                current = current->prev;
            }
            else if (current == nullptr)
            {
                std::cout << "You cannot cycle without any songs!\n";
                continue;
            }

            std::cout << "New song: " << current->name << std::endl << std::endl;
        }
    }
    
    return 0;
}